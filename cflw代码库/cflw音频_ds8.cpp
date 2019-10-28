#include "cflw音频_ds8.h"
#include "cflw辅助.h"
#include "cflw辅助_win.h"
namespace cflw::音频::ds8 {
//--------------------------------------------------------------------------------
// 音频引擎
//--------------------------------------------------------------------------------
//构造函数
C音频引擎::C音频引擎() {
	辅助::f清零(*this);
};
//析构函数
C音频引擎::~C音频引擎() {
	if (v设备)
		f释放();
};
//初始化
HRESULT C音频引擎::f初始化 (HWND a窗口) {
	if (v设备)
		return S_FALSE;
	v主要 = nullptr;
	HRESULT hr;
	LPDIRECTSOUNDBUFFER v主缓存 = nullptr;
	hr = DirectSoundCreate8(nullptr, &v设备, nullptr);
	if(FAILED(hr))
		return hr;
	hr = v设备->SetCooperativeLevel(a窗口, DSSCL_PRIORITY);
	DSBUFFERDESC v缓存描述;
	v缓存描述.dwFlags = DSBCAPS_PRIMARYBUFFER;
	v缓存描述.dwBufferBytes = 0;
	v缓存描述.lpwfxFormat = nullptr;
	hr = v设备->CreateSoundBuffer(&v缓存描述, &v主缓存, nullptr);
	WAVEFORMATEX v波形格式;
	辅助::f清零(v波形格式); 
	v波形格式.wFormatTag = WAVE_FORMAT_PCM; 
	v波形格式.nChannels = 2; 
	v波形格式.nSamplesPerSec = 22050; 
	v波形格式.wBitsPerSample = 16; 
	v波形格式.nBlockAlign = v波形格式.wBitsPerSample / 8 * v波形格式.nChannels;
	v波形格式.nAvgBytesPerSec = v波形格式.nSamplesPerSec * v波形格式.nBlockAlign;
	hr = v主缓存->SetFormat(&v波形格式);
	if(FAILED(hr))
	   return hr;
	辅助::f释放(v主缓存);
	return S_OK;
}
//释放
void C音频引擎::f释放 () {
	辅助::f释放(v主要);
	辅助::f释放(v设备);
}
//载入音乐
HRESULT C音频引擎::f载入音乐 (S声音 &a声音, WCHAR *a文件名, WCHAR *a文件名2) {
	if (a声音.v缓存)
		a声音.f释放();
	C波形文件 v文件[2];
	v文件[0].f打开(a文件名);
	v文件[1].f打开(a文件名2);
	return S_OK;
}
//载入音效
HRESULT C音频引擎::f载入音效 (S声音 &a声音, WCHAR *a文件名) {
	if (a声音.v缓存)
		a声音.f释放();
	C波形文件 v文件;
	HRESULT hr;
	hr = v文件.f打开(a文件名);
	if (FAILED(hr))
		return hr;	//无法打开文件
	f注册缓存(a声音, v文件);
	return S_OK;
}
void C音频引擎::f播放音乐 () {

}
void C音频引擎::f播放音效 () {

}
HRESULT C音频引擎::f注册缓存 (S声音 &a声音, C波形文件 &a文件) {
	DSBUFFERDESC v缓存描述;
	v缓存描述.dwFlags = DSBCAPS_STATIC;
	v缓存描述.dwBufferBytes = a文件.v块信息.cksize;
	v缓存描述.lpwfxFormat = a文件.v格式;
	LPDIRECTSOUNDBUFFER v临时 = nullptr;
	HRESULT hr;
	hr = v设备->CreateSoundBuffer(&v缓存描述, &v临时, nullptr);
	if (FAILED(hr))
		return hr;
	v临时->QueryInterface(IID_IDirectSoundBuffer8, (void**)&a声音.v缓存);
	if (FAILED(hr))
		return hr;
	v临时->Release();
	a声音.v大小 = v缓存描述.dwBufferBytes;
	return S_OK;
}
HRESULT C音频引擎::f填充声音 (S声音 &a声音, C波形文件 &a文件) {
	HRESULT hr;
	BYTE* v波形数据;
	UINT v波形大小;
	void* v数据[2] = {nullptr, nullptr};
	ULONG v长度[2];
	const UINT v文件大小 = a文件.v块信息.cksize;
	v波形数据 = new BYTE[v文件大小];
	if (v波形数据 == nullptr) {
		delete[] v波形数据;
		return S_FALSE;	//内存不足
	}
	hr = a文件.f读取(v文件大小, v波形数据, &v波形大小);
	if (FAILED(hr)) {
		delete[] v波形数据;
		return hr;	//读取失败
	}
	a文件.f重置();
	hr = a声音.v缓存->Lock(0, a声音.v大小, &v数据[0], &v长度[0], &v数据[1], &v长度[1], 0);
	if (FAILED(hr)) {
		delete[] v波形数据;
		return hr;	//锁定失败
	}
	memcpy(v数据[0], v波形数据, a声音.v大小);
	a声音.v缓存->Unlock(v数据[0], a声音.v大小, nullptr, 0);
	delete[] v波形数据;
	return S_OK;
}
//==============================================================================
// 声音
//==============================================================================
S声音::S声音 () {
	辅助::f清零(*this);
}
S声音::~S声音 () {
	f释放();
}
void S声音::f释放 () {
	辅助::f释放(v缓存);
};
//==============================================================================
// 波形文件
//==============================================================================
C波形文件::C波形文件() {
	m格式 = nullptr;
}
C波形文件::~C波形文件() {
	f关闭();
	辅助::f删除(m格式);
};
HRESULT C波形文件::f打开(WCHAR *a文件名) {
	辅助::f删除(m格式);
	HRESULT  hr;
	hr = WaveOpenFile(a文件名, &m多媒体io, &m格式, &m块信息riff);
	if(FAILED(hr))
		return hr;
	hr = f重置();
	if(FAILED(hr))
		return hr;
	return hr;
}
HRESULT C波形文件::f重置() {
	return WaveStartDataRead(&m多媒体io, &m块信息, &m块信息riff);
}
HRESULT C波形文件::f读取(UINT a要读取大小, BYTE* a数据, UINT* a读取大小) {
	return WaveReadFile(m多媒体io, a要读取大小, a数据, &m块信息, a读取大小);
}
HRESULT C波形文件::f关闭() {
	mmioClose(m多媒体io, 0);
	return S_OK;
}

}	//命名空间结束