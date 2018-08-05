#pragma once
#include <Windows.h>
#include <Unknwn.h>
#include <assert.h>
//必须使用unicode
#ifndef UNICODE
	#define UNICODE
	#ifdef ANSI
		#error 必须使用Unicode
	#endif
#endif
namespace cflw::辅助 {
//=============================================================================
// Windows
//=============================================================================
inline void f失败则抛出(HRESULT hr) {
	if (FAILED(hr)) {
		__debugbreak();
		throw hr;
	}
}
inline bool fw成功(HRESULT hr) {
	return SUCCEEDED(hr);
}
inline bool fw失败(HRESULT hr) {
	return FAILED(hr);
}
//=============================================================================
// COM组件对象模型
//=============================================================================
//释放com
template<typename t> inline void f释放(t &p) {
	static_assert(std::is_base_of<IUnknown, std::remove_pointer<t>::type>::value, "必需是IUnknown的派生类");
	if (p) {
		p->Release();
		p = nullptr;
	}
}
template<typename t> inline void f释放1(t *p, int p1) {
	for (int i = 0; i < p1; ++i) {
		f释放(p[i]);
	}
}
template<typename t> inline void f释放2(t *p, int p1, int p2) {
	for (int i1 = 0; i1 < p1; ++i1) {
		f释放1(p[i1], p2);
	}
}
}	//namespace cflw::辅助
