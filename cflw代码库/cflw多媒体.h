#pragma once
#include <mmstream.h>
#pragma comment(lib, "winmm.lib")
namespace cflw::��ý�� {
//==============================================================================
//mmsystem.h
//==============================================================================
typedef WAVEFORMATEX t���θ�ʽ;	//��:782-792
inline DWORD fȡ����ʱ��() {
	return timeGetTime();
};	//��:2205
//==============================================================================
//����
//==============================================================================
//���ʽ
constexpr DWORD c��RIFF = mmioFOURCC('R', 'I', 'F', 'F');
constexpr DWORD c��data = mmioFOURCC('d', 'a', 't', 'a');
constexpr DWORD c��fmt = mmioFOURCC('f', 'm', 't', ' ');
constexpr DWORD c��WAVE = mmioFOURCC('W', 'A', 'V', 'E');
constexpr DWORD c��XWMA = mmioFOURCC('X', 'W', 'M', 'A');
constexpr DWORD c��dpds = mmioFOURCC('d', 'p', 'd', 's');
//����
HRESULT FindChunk(HANDLE hFile, DWORD fourcc, DWORD &dwChunkSize, DWORD &dwChunkDataPosition);
HRESULT ReadChunkData(HANDLE hFile, void *buffer, DWORD buffersize, DWORD bufferoffset);
}	//namespace cflw::��ý��