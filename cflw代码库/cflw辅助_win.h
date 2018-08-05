#pragma once
#include <Windows.h>
#include <Unknwn.h>
#include <assert.h>
//����ʹ��unicode
#ifndef UNICODE
	#define UNICODE
	#ifdef ANSI
		#error ����ʹ��Unicode
	#endif
#endif
namespace cflw::���� {
//=============================================================================
// Windows
//=============================================================================
inline void fʧ�����׳�(HRESULT hr) {
	if (FAILED(hr)) {
		__debugbreak();
		throw hr;
	}
}
inline bool fw�ɹ�(HRESULT hr) {
	return SUCCEEDED(hr);
}
inline bool fwʧ��(HRESULT hr) {
	return FAILED(hr);
}
//=============================================================================
// COM�������ģ��
//=============================================================================
//�ͷ�com
template<typename t> inline void f�ͷ�(t &p) {
	static_assert(std::is_base_of<IUnknown, std::remove_pointer<t>::type>::value, "������IUnknown��������");
	if (p) {
		p->Release();
		p = nullptr;
	}
}
template<typename t> inline void f�ͷ�1(t *p, int p1) {
	for (int i = 0; i < p1; ++i) {
		f�ͷ�(p[i]);
	}
}
template<typename t> inline void f�ͷ�2(t *p, int p1, int p2) {
	for (int i1 = 0; i1 < p1; ++i1) {
		f�ͷ�1(p[i1], p2);
	}
}
}	//namespace cflw::����
