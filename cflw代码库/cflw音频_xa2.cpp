#include <cassert>
#include <algorithm>
#include "cflw音频_xa2.h"
namespace cflw::音频::xa2 {
using 多媒体::FindChunk;
using 多媒体::ReadChunkData;
//==============================================================================
// 辅助函数
//==============================================================================
void f销毁声音(IXAudio2Voice *a) {
	a->DestroyVoice();
}
//==============================================================================
// 音频引擎
//==============================================================================
C音频::C音频() {
};
C音频::~C音频() {
	if (m音频) {
		f销毁();
	}
};
HRESULT C音频::f初始化() {
	HRESULT hr;
	hr = CoInitializeEx(nullptr, COINIT_MULTITHREADED);
	if (FAILED(hr)) {
		return hr;
	}
	hr = XAudio2Create(&m音频, 0, XAUDIO2_DEFAULT_PROCESSOR);
	if (FAILED(hr)) {
		return hr;
	}
	hr = m音频->CreateMasteringVoice(&m声音控制);
	if (FAILED(hr)) {
		return hr;
	}
	return S_OK;
};
void C音频::f销毁() {
	f销毁声音(m声音控制);
	m声音控制 = nullptr;
	m音频.Reset();
	CoUninitialize();
};
HRESULT C音频::f创建声音(tp声音 &a声音, const std::wstring_view &a文件) {
	HRESULT hr;
	C波形文件 v文件;
	hr = v文件.f打开(a文件);
	if (FAILED(hr)) {
		return hr;
	}
	if (!v文件.f检查类型()) {
		return E_FAIL;	//不是波形格式
	}
	tp声音 v声音 = std::make_shared<C声音>();
	v声音->m格式 = v文件.f读取格式();
	const auto &[v数据, v数据大小] = v文件.f读取数据();
	v声音->m数据 = std::unique_ptr<std::byte>(v数据);
	v声音->m大小 = v数据大小;
	//填充缓冲
	v声音->m缓冲.AudioBytes = (UINT32)v数据大小;
	v声音->m缓冲.pAudioData = (BYTE*)v数据;
	v声音->m缓冲.Flags = XAUDIO2_END_OF_STREAM;
	v声音->m缓冲.LoopBegin = XAUDIO2_NO_LOOP_REGION;
	v声音->m缓冲.LoopLength = 0;
	v声音->m缓冲.LoopCount = 0;
	//结束
	a声音 = std::move(v声音);
	return S_OK;
};
HRESULT C音频::f创建源声音(tp源声音 &a源声音, const C声音 &a声音, const C混合 &a混合) {
	IXAudio2SourceVoice *v源声音;
	HRESULT hr = m音频->CreateSourceVoice(&v源声音, (WAVEFORMATEX*)&a声音.m格式, 0, 2, nullptr, &a混合.m列表);
	if (FAILED(hr)) {
		return hr;
	}
	a源声音 = std::shared_ptr<IXAudio2SourceVoice>(v源声音, &f销毁声音);
	return S_OK;
}
HRESULT C音频::f创建混合(tp混合 &a混合) {
	tp混合 v混合 = std::make_shared<C混合>();
	HRESULT hr = m音频->CreateSubmixVoice(&v混合->m声音, 1, 44100);
	if (FAILED(hr)) {
		return hr;
	}
	v混合->m发送.Flags = 0;
	v混合->m发送.pOutputVoice = v混合->m声音;
	v混合->m列表.pSends = &v混合->m发送;
	v混合->m列表.SendCount = 1;
	a混合 = std::move(v混合);
	return S_OK;
}
//==============================================================================
// 播放控制
//==============================================================================
C播放控制::C播放控制() {
}
void C播放控制::f初始化(C音频 &a) {
	m音频 = &a;
	m当前时间 = std::chrono::system_clock::now();
}
void C播放控制::f刷新() {
	for (auto v迭代 = ma播放.begin(); v迭代 != ma播放.end();) {
		const auto &[v播放, v源声音] = *v迭代;
		++v迭代;
		XAUDIO2_VOICE_STATE v状态;
		v源声音->GetState(&v状态);
		if (v状态.BuffersQueued <= 0) {
			ma播放.erase(v播放);
		}
	}
	m当前时间 = std::chrono::system_clock::now();
}
tp播放 C播放控制::f播放(const C声音 &a声音, const C混合 &a混合) {
	//去重
	if (const auto &v找声音 = m声音去重.find(&a声音); v找声音 != m声音去重.end()) {
		if (const float v时间差 = std::chrono::duration<float>(m当前时间 - v找声音->second).count(); v时间差 <= m声音间隔) {
			return 0;	//重复,不播放
		}
	}
	//播放
	tp播放 v播放 = (++m序号);
	tp源声音 v源声音;
	m音频->f创建源声音(v源声音, a声音, a混合);
	v源声音->SubmitSourceBuffer(&a声音.m缓冲);
	v源声音->Start();
	m声音去重[&a声音] = m当前时间;
	ma播放[v播放] = v源声音;
	return v播放;
}
void C播放控制::f暂停(tp播放 a) {
	if (const auto &v找播放 = ma播放.find(a); v找播放 != ma播放.end()) {
		v找播放->second->Stop();
	}
}
void C播放控制::f恢复(tp播放 a) {
	if (const auto &v找播放 = ma播放.find(a); v找播放 != ma播放.end()) {
		v找播放->second->Start();
	}
}
void C播放控制::f停止(tp播放 a) {
	if (const auto &v找播放 = ma播放.find(a); v找播放 != ma播放.end()) {
		v找播放->second->Stop();
		ma播放.erase(a);
	}
}
void C播放控制::f停止全部() {
	for (const auto &[v播放, v源声音] : ma播放) {
		v源声音->Stop();
	}
	ma播放.clear();
}
bool C播放控制::fi播放(tp播放 a) {
	const auto &v找播放 = ma播放.find(a);
	return v找播放 != ma播放.end();
}
void C播放控制::fs重复播放间隔(float a) {
	m声音间隔 = a;
}
//==============================================================================
// 声音
//==============================================================================
C混合::~C混合() {
	if (m声音) {
		f销毁声音(m声音);
	}
}
void C混合::f销毁() {
	f销毁声音(m声音);
	m声音 = nullptr;
}
void C混合::fs音量(float a) {
	m声音->SetVolume(a);
}
float C混合::fg音量() const {
	float v;
	m声音->GetVolume(&v);
	return v;
}
//==============================================================================
// 波形文件
//==============================================================================
HRESULT C波形文件::f打开(const std::wstring_view &a文件名) {
	m文件 = CreateFileW(a文件名.data(), GENERIC_READ, FILE_SHARE_READ, nullptr, OPEN_EXISTING, 0, nullptr);
	if (INVALID_HANDLE_VALUE == m文件)
		return HRESULT_FROM_WIN32(GetLastError());
	if (INVALID_SET_FILE_POINTER == SetFilePointer(m文件, 0, nullptr, FILE_BEGIN))
		return HRESULT_FROM_WIN32(GetLastError());
	return S_OK;
};
bool C波形文件::f检查类型() const {
	DWORD v块大小;
	DWORD v块位置;
	DWORD v文件类型;
	FindChunk(m文件, 多媒体::c块RIFF, v块大小, v块位置);
	ReadChunkData(m文件, &v文件类型, sizeof(DWORD), v块位置);
	return v文件类型 == 多媒体::c块WAVE;
};
WAVEFORMATEXTENSIBLE C波形文件::f读取格式() const {
	DWORD v块大小;
	DWORD v块位置;
	WAVEFORMATEXTENSIBLE v格式;
	FindChunk(m文件, 多媒体::c块fmt, v块大小, v块位置);
	ReadChunkData(m文件, &v格式, v块大小, v块位置);
	return v格式;
};
std::pair<std::byte*, size_t> C波形文件::f读取数据() const {
	DWORD v块大小;
	DWORD v块位置;
	FindChunk(m文件, 多媒体::c块data, v块大小, v块位置);
	std::byte *v数据 = new std::byte[v块大小];
	ReadChunkData(m文件, v数据, v块大小, v块位置);
	return {v数据, v块大小};
};
bool C波形文件::f关闭() {
	return CloseHandle(m文件);
}
}	//namespace cflw::音频::xa2