#pragma once
#include <dsound.h>
#include "cflw多媒体.h"
#pragma comment(lib, "dsound.lib")
namespace cflw::音频::ds8 {
//==============================================================================
//类型
typedef class C音频引擎 t音频引擎;
typedef struct S声音 t声音;
//==============================================================================
// 音频
//==============================================================================
class C音频引擎 {
private:
	IDirectSound8 *v设备;
	IDirectSoundBuffer8 *v主要;
	HRESULT f注册缓存 (S声音 &, 多媒体::C波形文件 &);
	HRESULT f填充声音 (S声音 &, 多媒体::C波形文件 &);
public:
	C音频引擎();
	~C音频引擎();
	HRESULT f初始化 (HWND);
	void f释放 ();
	HRESULT f载入音乐 (S声音 &, WCHAR *文件名, WCHAR *文件名2);
	HRESULT f载入音效 (S声音 &, WCHAR *文件名);
	void f播放音乐 ();	//音乐只能同时播放一首
	void f播放音效 ();	//音效可以同时重复播放
};
//==============================================================================
// 声音
//==============================================================================
struct S声音 {
private:
	IDirectSoundBuffer8 *v缓存;
	unsigned int v大小;
	friend C音频引擎;
public:
	S声音 ();
	~S声音 ();
	void f释放 ();
};
//==============================================================================
// 波形文件
//==============================================================================
class C波形文件 {	//适用于DirectSound8
public:
	C波形文件();
	~C波形文件();
	HRESULT f打开(WCHAR *文件名);
	HRESULT f重置();
	HRESULT f读取(UINT 要读取大小, BYTE* 数据, UINT* 读取大小);
	HRESULT f关闭();
	WAVEFORMATEX*	m格式;			// 指向WAVEFORMATEX结构
	HMMIO			m多媒体io;		// 波MM的I/O处理
	MMCKINFO		m块信息;		// 
	MMCKINFO		m块信息riff;	// 多媒体RIFF块
};
}	//命名空间结束
#endif