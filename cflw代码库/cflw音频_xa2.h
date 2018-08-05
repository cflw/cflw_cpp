#pragma once
#include <map>
#include <chrono>
#include <memory>
#include <Windows.h>
#include <wrl.h>
#include <xaudio2.h>
#include "cflw多媒体.h"
//链接
#pragma comment(lib, "xaudio2.lib")
//命名空间
namespace cflw::音频::xa2 {
using Microsoft::WRL::ComPtr;
using t时间点 = std::chrono::time_point<std::chrono::system_clock>;
using tp子混声音 = std::shared_ptr<IXAudio2SubmixVoice>;
using tp源声音 = std::shared_ptr<IXAudio2SourceVoice>;
class C声音;
class C混合;
using tp声音 = std::shared_ptr<C声音>;
using tp混合 = std::shared_ptr<C混合>;
using tp播放 = size_t;	//句柄
//==============================================================================
// 音频引擎
//==============================================================================
class C音频 {
public:
	C音频();
	~C音频();
	HRESULT f初始化();
	void f销毁();
	HRESULT f创建声音(tp声音 &, const wchar_t *文件名);
	HRESULT f创建源声音(tp源声音 &, const C声音 &, const C混合 &);
	HRESULT f创建混合(tp混合 &);
private:
	ComPtr<IXAudio2> m音频;
	IXAudio2MasteringVoice *m声音控制 = nullptr;
};
//==============================================================================
// 控制
//==============================================================================
class C播放控制 {
public:
	C播放控制(C音频 &);
	void f刷新();
	tp播放 f播放(const C声音 &, const C混合 &);
	void f暂停(tp播放);
	void f恢复(tp播放);
	void f停止(tp播放);
	void f停止全部();
	bool fi播放(tp播放);
	void fs重复播放间隔(float = 0);
private:
	C音频 *m音频;
	std::map<tp播放, tp源声音> ma播放;
	std::map<const C声音 *, t时间点> m声音去重;	//防止短一时间内播放大量同一个声音
	float m声音间隔 = 0;	//多少时间后可以播放同一个声音
	t时间点 m当前时间;
	tp播放 m序号 = 1;
};
//==============================================================================
// 声音类
//==============================================================================
class C声音 {
public:
	WAVEFORMATEXTENSIBLE m格式;
	XAUDIO2_BUFFER m缓冲;
	std::unique_ptr<std::byte> m数据;
	size_t m大小;
};
class C混合 {
public:
	~C混合();
	void f销毁();
	void fs音量(float);
	float fg音量() const;
	IXAudio2SubmixVoice *m声音 = nullptr;
	XAUDIO2_SEND_DESCRIPTOR m发送;
	XAUDIO2_VOICE_SENDS m列表;
};
//==============================================================================
// 声音文件
//==============================================================================
class C波形文件 {
public:
	HRESULT f打开(const wchar_t *);
	bool f检查类型() const;
	WAVEFORMATEXTENSIBLE f读取格式() const;
	std::pair<std::byte*, size_t> f读取数据() const;
	bool f关闭();
	HANDLE m文件;
};
}	//namespace cflw::音频::xa2