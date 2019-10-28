#pragma once
#include <mmstream.h>
#pragma comment(lib, "winmm.lib")
namespace cflw::多媒体 {
//==============================================================================
//mmsystem.h
//==============================================================================
typedef WAVEFORMATEX t波形格式;	//行:782-792
inline DWORD f取开机时间() {
	return timeGetTime();
};	//行:2205
//==============================================================================
//辅助
//==============================================================================
//块格式
constexpr DWORD c块RIFF = mmioFOURCC('R', 'I', 'F', 'F');
constexpr DWORD c块data = mmioFOURCC('d', 'a', 't', 'a');
constexpr DWORD c块fmt = mmioFOURCC('f', 'm', 't', ' ');
constexpr DWORD c块WAVE = mmioFOURCC('W', 'A', 'V', 'E');
constexpr DWORD c块XWMA = mmioFOURCC('X', 'W', 'M', 'A');
constexpr DWORD c块dpds = mmioFOURCC('d', 'p', 'd', 's');
//函数
HRESULT FindChunk(HANDLE hFile, DWORD fourcc, DWORD &dwChunkSize, DWORD &dwChunkDataPosition);
HRESULT ReadChunkData(HANDLE hFile, void *buffer, DWORD buffersize, DWORD bufferoffset);
}	//namespace cflw::多媒体