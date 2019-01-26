#pragma once
#include "cflwͼ��_d2d.h"
namespace cflw::ͼ��::d2d {
template<typename t> ComPtr<IDXGISurface> fȡ����(const ComPtr<t> &a) {
	ComPtr<IDXGISurface> v����;
	a.As(&v����);
	return v����;
}
template<typename t> ComPtr<IDXGISurface> fȡ����(t *a) {
	static_assert(std::is_base_of<IUnknown, t>::value);
	ComPtr<IDXGISurface> v����;
	a->QueryInterface(IID_PPV_ARGS(&v����));
	return v����;
}
template<typename t��Χ>
HRESULT C��ά::f��ʼ��_���λͼ(const t��Χ &a��Χ, float a����) {
	maλͼĿ��.clear();
	const ��ѧ::S����2 dpi = fgÿӢ�����(a����);
	const D2D1_BITMAP_PROPERTIES1 vλͼ���� = D2D1::BitmapProperties1(
		D2D1_BITMAP_OPTIONS_TARGET | D2D1_BITMAP_OPTIONS_CANNOT_DRAW,
		D2D1::PixelFormat(DXGI_FORMAT_UNKNOWN, D2D1_ALPHA_MODE_PREMULTIPLIED),
		dpi.x, dpi.y
	);
	m������->SetDpi(dpi.x, dpi.y);
	auto v��ʼ = std::begin(a��Χ);
	auto v���� = std::end(a��Χ);
	for (auto i = v��ʼ; i != v����; ++i) {
		ComPtr<IDXGISurface> v���� = fȡ����(*i);
		ComPtr<ID2D1Bitmap1> vλͼĿ��;
		HRESULT hr = m������->CreateBitmapFromDxgiSurface(v����.Get(), &vλͼ����, &vλͼĿ��);
		if (FAILED(hr)) {
			return hr;
		}
		maλͼĿ��.push_back(vλͼĿ��);
	}
	const ComPtr<ID2D1Bitmap1> &vλͼĿ��0 = maλͼĿ��.front();
	m������->SetTarget(vλͼĿ��0.Get());
	const auto v��С = vλͼĿ��0->GetSize();
	f��ʼ��_���ڴ�С(v��С.width, v��С.height);
	return S_OK;
}

}
