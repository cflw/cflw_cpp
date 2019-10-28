#pragma once
#include "cflw图形_d2d.h"
namespace cflw::图形::d2d {
template<typename t> ComPtr<IDXGISurface> f取表面(const ComPtr<t> &a) {
	ComPtr<IDXGISurface> v表面;
	a.As(&v表面);
	return v表面;
}
template<typename t> ComPtr<IDXGISurface> f取表面(t *a) {
	static_assert(std::is_base_of<IUnknown, t>::value);
	ComPtr<IDXGISurface> v表面;
	a->QueryInterface(IID_PPV_ARGS(&v表面));
	return v表面;
}
template<typename t范围>
HRESULT C二维::f初始化_多个位图(const t范围 &a范围, float a缩放) {
	ma位图目标.clear();
	const 数学::S向量2 dpi = fg每英寸点数(a缩放);
	const D2D1_BITMAP_PROPERTIES1 v位图属性 = D2D1::BitmapProperties1(
		D2D1_BITMAP_OPTIONS_TARGET | D2D1_BITMAP_OPTIONS_CANNOT_DRAW,
		D2D1::PixelFormat(DXGI_FORMAT_UNKNOWN, D2D1_ALPHA_MODE_PREMULTIPLIED),
		dpi.x, dpi.y
	);
	m上下文->SetDpi(dpi.x, dpi.y);
	auto v开始 = std::begin(a范围);
	auto v结束 = std::end(a范围);
	for (auto i = v开始; i != v结束; ++i) {
		ComPtr<IDXGISurface> v表面 = f取表面(*i);
		ComPtr<ID2D1Bitmap1> v位图目标;
		HRESULT hr = m上下文->CreateBitmapFromDxgiSurface(v表面.Get(), &v位图属性, &v位图目标);
		if (FAILED(hr)) {
			return hr;
		}
		ma位图目标.push_back(v位图目标);
	}
	const ComPtr<ID2D1Bitmap1> &v位图目标0 = ma位图目标.front();
	m上下文->SetTarget(v位图目标0.Get());
	const auto v大小 = v位图目标0->GetSize();
	f初始化_窗口大小(v大小.width, v大小.height);
	return S_OK;
}

}
