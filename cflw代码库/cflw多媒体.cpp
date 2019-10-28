#include "cflw多媒体.h"
#include "cflw辅助.h"
namespace cflw {
namespace 多媒体{
//--------------------------------------------------------------------------------
// 以下内容来自DirectX SDK
// cflw版权没有
//--------------------------------------------------------------------------------
//ReadMMIO
HRESULT ReadMMIO(HMMIO hmmioIn, MMCKINFO* pckInRIFF, WAVEFORMATEX** ppwfxInfo) {
	MMCKINFO ckIn;           // chunk info. for general use.
	PCMWAVEFORMAT pcmWaveFormat;  // Temp PCM structure to load in.
	*ppwfxInfo = nullptr;
	if((0 != mmioDescend(hmmioIn, pckInRIFF, nullptr, 0)))
		return E_FAIL;
	if((pckInRIFF->ckid != FOURCC_RIFF) || (pckInRIFF->fccType != mmioFOURCC('W','A','V','E')))
		return E_FAIL;
	// Search the input file for for the 'fmt ' chunk.
	ckIn.ckid = mmioFOURCC('f', 'm', 't', ' ');
	if (0 != mmioDescend(hmmioIn, &ckIn, pckInRIFF, MMIO_FINDCHUNK))
		return E_FAIL;
	// Expect the 'fmt' chunk to be at least as large as <PCMWAVEFORMAT>;
	// if there are extra parameters at the end, we'll ignore them
	   if (ckIn.cksize < (LONG)sizeof(PCMWAVEFORMAT))
		   return E_FAIL;
	// Read the 'fmt ' chunk into <pcmWaveFormat>.
	if (mmioRead(hmmioIn, (HPSTR) &pcmWaveFormat, sizeof(pcmWaveFormat)) != sizeof(pcmWaveFormat))
		return E_FAIL;
	// Allocate the waveformatex, but if its not pcm format, read the next
	// word, and thats how many extra bytes to allocate.
	if (pcmWaveFormat.wf.wFormatTag == WAVE_FORMAT_PCM) {
		if (nullptr == (*ppwfxInfo = new WAVEFORMATEX))
			return E_FAIL;
		// Copy the bytes from the pcm structure to the waveformatex structure
		memcpy(*ppwfxInfo, &pcmWaveFormat, sizeof(pcmWaveFormat));
		(*ppwfxInfo)->cbSize = 0;
	} else {
		// Read in length of extra bytes.
		WORD cbExtraBytes = 0L;
		if(mmioRead( hmmioIn, (CHAR*)&cbExtraBytes, sizeof(WORD)) != sizeof(WORD))
			return E_FAIL;
		*ppwfxInfo = (WAVEFORMATEX*)new CHAR[sizeof(WAVEFORMATEX) + cbExtraBytes];
		if(nullptr == *ppwfxInfo )
			return E_FAIL;
		// Copy the bytes from the pcm structure to the waveformatex structure
		memcpy( *ppwfxInfo, &pcmWaveFormat, sizeof(pcmWaveFormat) );
		(*ppwfxInfo)->cbSize = cbExtraBytes;
		// Now, read those extra bytes into the structure, if cbExtraAlloc != 0.
		if(mmioRead(hmmioIn, (CHAR*)(((BYTE*)&((*ppwfxInfo)->cbSize))+sizeof(WORD)), cbExtraBytes) != cbExtraBytes) {
			delete *ppwfxInfo;
			*ppwfxInfo = nullptr;
			return E_FAIL;
		}
	}
	// Ascend the input file out of the 'fmt ' chunk.
	if(0 != mmioAscend(hmmioIn, &ckIn, 0)) {
		delete *ppwfxInfo;
		*ppwfxInfo = nullptr;
		return E_FAIL;
	}
	return S_OK;
}
//WaveOpenFile
HRESULT WaveOpenFile (TCHAR* strFileName, HMMIO* phmmioIn, WAVEFORMATEX** ppwfxInfo, MMCKINFO* pckInRIFF) {
	HRESULT hr;
	HMMIO hmmioIn = nullptr;
	if(nullptr == (hmmioIn = mmioOpen(strFileName, nullptr, MMIO_ALLOCBUF|MMIO_READ)))
		return E_FAIL;
	if(FAILED(hr = ReadMMIO(hmmioIn, pckInRIFF, ppwfxInfo))) {
		mmioClose(hmmioIn, 0);
		return hr;
	}
	*phmmioIn = hmmioIn;
	return S_OK;
}
//WaveStartDataRead
HRESULT WaveStartDataRead (HMMIO* phmmioIn, MMCKINFO* pckIn,  MMCKINFO* pckInRIFF){
	// Seek to the data
	if(-1 == mmioSeek(*phmmioIn, pckInRIFF->dwDataOffset + sizeof(FOURCC), SEEK_SET))
		return E_FAIL;
	// Search the input file for for the 'data' chunk.
	pckIn->ckid = mmioFOURCC('d', 'a', 't', 'a');
	if(0 != mmioDescend(*phmmioIn, pckIn, pckInRIFF, MMIO_FINDCHUNK))
		return E_FAIL;
	return S_OK;
}
//WaveReadFile
HRESULT WaveReadFile(HMMIO hmmioIn, UINT cbRead, BYTE* pbDest, MMCKINFO* pckIn, UINT* cbActualRead) {
	MMIOINFO mmioinfoIn;         // current status of <hmmioIn>
	*cbActualRead = 0;
	if (0 != mmioGetInfo(hmmioIn, &mmioinfoIn, 0))
		return E_FAIL;
	UINT cbDataIn = cbRead;
	if (cbDataIn > pckIn->cksize) 
		cbDataIn = pckIn->cksize;
	pckIn->cksize -= cbDataIn;
	for(DWORD cT = 0; cT < cbDataIn; cT++) {
		// Copy the bytes from the io to the buffer.
		if (mmioinfoIn.pchNext == mmioinfoIn.pchEndRead) {
			if (0 != mmioAdvance(hmmioIn, &mmioinfoIn, MMIO_READ))
				return E_FAIL;
			if(mmioinfoIn.pchNext == mmioinfoIn.pchEndRead)
				return E_FAIL;
		}
		// Actual copy.
		*((BYTE*)pbDest+cT) = *((BYTE*)mmioinfoIn.pchNext);
		mmioinfoIn.pchNext++;
	}
	if(0 != mmioSetInfo(hmmioIn, &mmioinfoIn, 0))
		return E_FAIL;
	*cbActualRead = cbDataIn;
	return S_OK;
}
//FindChunk
HRESULT FindChunk(HANDLE hFile, DWORD fourcc, DWORD &dwChunkSize, DWORD &dwChunkDataPosition) {
	HRESULT hr = S_OK;
	if( INVALID_SET_FILE_POINTER == SetFilePointer( hFile, 0, NULL, FILE_BEGIN ) )
		return HRESULT_FROM_WIN32( GetLastError() );
	DWORD dwChunkType;
	DWORD dwChunkDataSize;
	DWORD dwRIFFDataSize = 0;
	DWORD dwFileType;
	DWORD bytesRead = 0;
	DWORD dwOffset = 0;
	while (hr == S_OK) {
		DWORD dwRead;
		if( 0 == ReadFile( hFile, &dwChunkType, sizeof(DWORD), &dwRead, NULL ) )
			hr = HRESULT_FROM_WIN32( GetLastError() );
		if( 0 == ReadFile( hFile, &dwChunkDataSize, sizeof(DWORD), &dwRead, NULL ) )
			hr = HRESULT_FROM_WIN32( GetLastError() );
		switch (dwChunkType) {
		case c块RIFF:
			dwRIFFDataSize = dwChunkDataSize;
			dwChunkDataSize = 4;
			if( 0 == ReadFile( hFile, &dwFileType, sizeof(DWORD), &dwRead, NULL ) )
				hr = HRESULT_FROM_WIN32( GetLastError() );
			break;
		default:
			if( INVALID_SET_FILE_POINTER == SetFilePointer( hFile, dwChunkDataSize, NULL, FILE_CURRENT ) )
			return HRESULT_FROM_WIN32( GetLastError() );            
		}
		dwOffset += sizeof(DWORD) * 2;
		if (dwChunkType == fourcc) {
			dwChunkSize = dwChunkDataSize;
			dwChunkDataPosition = dwOffset;
			return S_OK;
		}
		dwOffset += dwChunkDataSize;
		if (bytesRead >= dwRIFFDataSize) return S_FALSE;
	}
	return S_OK;
}
//ReadChunkData
HRESULT ReadChunkData(HANDLE hFile, void * buffer, DWORD buffersize, DWORD bufferoffset)
{
	HRESULT hr = S_OK;
	if( INVALID_SET_FILE_POINTER == SetFilePointer( hFile, bufferoffset, NULL, FILE_BEGIN ) )
		return HRESULT_FROM_WIN32( GetLastError() );
	DWORD dwRead;
	if( 0 == ReadFile( hFile, buffer, buffersize, &dwRead, NULL ) )
		hr = HRESULT_FROM_WIN32( GetLastError() );
	return hr;
}
}}	//命名空间结束