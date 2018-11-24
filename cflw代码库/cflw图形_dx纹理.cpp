#include <cassert>
#include <unordered_map>
#include <unordered_set>
#include "cflwͼ��_dx����.h"
namespace std {
template<> struct hash<GUID> {
	size_t operator()(const GUID &a) const {
		const size_t v0 = a.Data1;
		const size_t v1 = (size_t)a.Data2 * (size_t)a.Data3;
		const size_t v2 = (size_t)a.Data4[0] * (size_t)a.Data4[1] * (size_t)a.Data4[2] * (size_t)a.Data4[3] * (size_t)a.Data4[4] * (size_t)a.Data4[5] * (size_t)a.Data4[6] * (size_t)a.Data4[7];
		return v0 ^ v1 ^ v2;
	}
};
}
namespace cflw::ͼ��::dx���� {
Cͼ�񹤳�::~Cͼ�񹤳�() {
	m����.Reset();
	CoUninitialize();
}
HRESULT Cͼ�񹤳�::f��ʼ��() {
	CoInitializeEx(nullptr, COINIT_MULTITHREADED);
	HRESULT hr = CoCreateInstance(CLSID_WICImagingFactory1, nullptr, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&m����));
	if (FAILED(hr)) {
		return hr;
	}
	return S_OK;
}
HRESULT Cͼ�񹤳�::f��ȡͼ��(const wchar_t *p�ļ�, IWICBitmapFrameDecode **p֡) {
	HRESULT hr;
	ComPtr<IWICBitmapDecoder> v������;
	hr = m����->CreateDecoderFromFilename(p�ļ�, 0, GENERIC_READ, WICDecodeMetadataCacheOnDemand, &v������);
	if (FAILED(hr)) {
		return hr;
	}
	hr = v������->GetFrame(0, p֡);
	if (FAILED(hr)) {
		return hr;
	}
	return S_OK;
}
std::unique_ptr<std::byte[]> Cͼ�񹤳�::f������������(IWICBitmapSource *a֡, size_t *ap���ش�С, size_t *ap�о�, size_t *apͼ���С) {
	const WICBitmapPlaneDescription v���� = fȡͼ������(a֡);
	const size_t v���ش�С = f���ش�С(v����.Format);
	const size_t vһ�Ŵ�С = v����.Width * v���ش�С;
	const size_t v���ݴ�С = vһ�Ŵ�С * v����.Height;
	std::unique_ptr<std::byte[]> v���� = std::make_unique<std::byte[]>(v���ݴ�С);
	a֡->CopyPixels(0, vһ�Ŵ�С, v���ݴ�С, (BYTE*)v����.get());
	if (ap���ش�С) {
		*ap���ش�С = v���ش�С;
	}
	if (ap�о�) {
		*ap�о� = vһ�Ŵ�С;
	}
	if (apͼ���С) {
		*apͼ���С = v���ݴ�С;
	}
	return v����;
}
WICBitmapPlaneDescription Cͼ�񹤳�::fȡͼ������(IWICBitmapSource *a֡) {
	WICBitmapPlaneDescription v;
	a֡->GetPixelFormat(&v.Format);
	a֡->GetSize(&v.Width, &v.Height);
	return v;
}
size_t Cͼ�񹤳�::f���ش�С(const GUID &guid) {
	HRESULT hr;
	ComPtr<IWICComponentInfo> v�����Ϣ;
	hr = m����->CreateComponentInfo(guid, &v�����Ϣ);
	if (FAILED(hr)) {
		return 0;
	}
	WICComponentType v����;
	v�����Ϣ->GetComponentType(&v����);
	if (v���� != WICPixelFormat) {
		return 0;
	}
	ComPtr<IWICPixelFormatInfo> v��ʽ��Ϣ;
	hr = v�����Ϣ.As(&v��ʽ��Ϣ);
	if (FAILED(hr)) {
		return 0;
	}
	UINT bpp;
	v��ʽ��Ϣ->GetBitsPerPixel(&bpp);
	return bpp;
}
HRESULT Cͼ�񹤳�::fͼ��ߴ�任(IWICBitmapSource *a֡, size_t a��, size_t a��, IWICBitmapScaler **a���) {
	HRESULT hr;
	IWICBitmapScaler *&v���� = *a���;
	hr = m����->CreateBitmapScaler(&v����);
	if (FAILED(hr)) {
		return hr;
	}
	hr = v����->Initialize(a֡, a��, a��, WICBitmapInterpolationModeFant);
	if (FAILED(hr)) {
		return hr;
	}
	return S_OK;
}
HRESULT Cͼ�񹤳�::fͼ���ʽ�任(IWICBitmapSource *aͼ��, const GUID &a��ʽ, IWICFormatConverter **a���) {
	HRESULT hr;
	IWICFormatConverter *&vת�� = *a���;
	hr = m����->CreateFormatConverter(&vת��);
	if (FAILED(hr)) {
		return hr;
	}
	hr = vת��->Initialize(aͼ��, a��ʽ, WICBitmapDitherTypeErrorDiffusion, 0, 0, WICBitmapPaletteTypeCustom);
	if (FAILED(hr)) {
		return hr;
	}
	return S_OK;
}
std::unique_ptr<Cֻ������> Cͼ�񹤳�::fһ����ȡ(const wchar_t *a�ļ���) {
	ComPtr<IWICBitmapFrameDecode> vͼ��;
	HRESULT hr = f��ȡͼ��(a�ļ���, &vͼ��);
	if (FAILED(hr)) {
		return nullptr;
	}
	//��ʽת������������
	const WICBitmapPlaneDescription v���� = fȡͼ������(vͼ��.Get());
	std::unique_ptr<Cֻ������> v���� = std::make_unique<Cֻ������>();
	GUID vͼ���ʽ = v����.Format;
	v����->m�� = v����.Width;
	v����->m�� = v����.Height;
	if (��ʽ::fiͨ�ø�ʽ(vͼ���ʽ)) {
		v����->mp���� = f������������(vͼ��.Get(), &v����->m���ش�С, &v����->m�о�, nullptr);
	} else {
		ComPtr<IWICFormatConverter> v��ʽת��;
		vͼ���ʽ = ��ʽ::f��ͨ�ø�ʽ(vͼ���ʽ);
		fͼ���ʽ�任(vͼ��.Get(), vͼ���ʽ, &v��ʽת��);
		v����->mp���� = f������������(v��ʽת��.Get(), &v����->m���ش�С, &v����->m�о�, nullptr);
	}
	v����->m��ʽ = ��ʽ::f��dxgi(vͼ���ʽ);
	return v����;
}
//=============================================================================
// ��ʽ
//=============================================================================
namespace ��ʽ {
bool f���srgb(IWICBitmapFrameDecode *aͼ��) {
	HRESULT hr;
	ComPtr<IWICMetadataQueryReader> v��Ԫ����;
	hr = aͼ��->GetMetadataQueryReader(&v��Ԫ����);
	if (FAILED(hr)) {
		return false;
	}
	GUID v��ʽ;
	hr = v��Ԫ����->GetContainerFormat(&v��ʽ);
	if (FAILED(hr)) {
		return false;
	}
	bool v = false;
	PROPVARIANT vֵ;
	PropVariantInit(&vֵ);
	if (memcmp(&v��ʽ, &GUID_ContainerFormatPng, sizeof(GUID)) == 0) {
		hr = v��Ԫ����->GetMetadataByName(L"/sRGB/RenderingIntent", &vֵ);
		if (SUCCEEDED(hr)) {
			if (vֵ.vt == VT_UI1) {
				v = true;
			}
		}
	} else {
		hr = v��Ԫ����->GetMetadataByName(L"System.Image.ColorSpace", &vֵ);
		if (SUCCEEDED(hr)) {
			if (vֵ.vt == VT_UI2 && vֵ.uiVal == 1) {
				v = true;
			}
		}
	}
	PropVariantClear(&vֵ);
	return v;
}
DXGI_FORMAT f��dxgi(const GUID &guid) {
	static const std::unordered_map<GUID, DXGI_FORMAT> vͼ���ʽ = {
		{GUID_WICPixelFormat128bppRGBAFloat, DXGI_FORMAT_R32G32B32A32_FLOAT},

	{GUID_WICPixelFormat64bppRGBAHalf, DXGI_FORMAT_R16G16B16A16_FLOAT},
	{GUID_WICPixelFormat64bppRGBA, DXGI_FORMAT_R16G16B16A16_UNORM},

	{GUID_WICPixelFormat32bppRGBA, DXGI_FORMAT_R8G8B8A8_UNORM},
	{GUID_WICPixelFormat32bppBGRA, DXGI_FORMAT_B8G8R8A8_UNORM}, // DXGI 1.1
	{GUID_WICPixelFormat32bppBGR, DXGI_FORMAT_B8G8R8X8_UNORM}, // DXGI 1.1

	{GUID_WICPixelFormat32bppRGBA1010102XR, DXGI_FORMAT_R10G10B10_XR_BIAS_A2_UNORM}, // DXGI 1.1
	{GUID_WICPixelFormat32bppRGBA1010102, DXGI_FORMAT_R10G10B10A2_UNORM},

#ifdef DXGI_1_2_FORMATS

	{GUID_WICPixelFormat16bppBGRA5551, DXGI_FORMAT_B5G5R5A1_UNORM},
	{GUID_WICPixelFormat16bppBGR565, DXGI_FORMAT_B5G6R5_UNORM},

#endif // DXGI_1_2_FORMATS

	{GUID_WICPixelFormat32bppGrayFloat, DXGI_FORMAT_R32_FLOAT},
	{GUID_WICPixelFormat16bppGrayHalf, DXGI_FORMAT_R16_FLOAT},
	{GUID_WICPixelFormat16bppGray, DXGI_FORMAT_R16_UNORM},
	{GUID_WICPixelFormat8bppGray, DXGI_FORMAT_R8_UNORM},

	{GUID_WICPixelFormat8bppAlpha, DXGI_FORMAT_A8_UNORM},
	};
	if (auto v��ʽ = vͼ���ʽ.find(guid); v��ʽ != vͼ���ʽ.end()) {
		return v��ʽ->second;
	}
	return DXGI_FORMAT_UNKNOWN;
}
GUID f��ͨ�ø�ʽ(const GUID &guid) {
	static const std::unordered_map<GUID, GUID> vͼ��ת�� = {
		// ע��Ŀ��GUID�����ת�����������Щֱ��֧�ֵĸ�ʽ���Σ��е�һ����
		{GUID_WICPixelFormatBlackWhite, GUID_WICPixelFormat8bppGray}, // DXGI_FORMAT_R8_UNORM
	{GUID_WICPixelFormat1bppIndexed, GUID_WICPixelFormat32bppRGBA}, // DXGI_FORMAT_R8G8B8A8_UNORM
	{GUID_WICPixelFormat2bppIndexed, GUID_WICPixelFormat32bppRGBA}, // DXGI_FORMAT_R8G8B8A8_UNORM
	{GUID_WICPixelFormat4bppIndexed, GUID_WICPixelFormat32bppRGBA}, // DXGI_FORMAT_R8G8B8A8_UNORM
	{GUID_WICPixelFormat8bppIndexed, GUID_WICPixelFormat32bppRGBA}, // DXGI_FORMAT_R8G8B8A8_UNORM
	{GUID_WICPixelFormat2bppGray, GUID_WICPixelFormat8bppGray}, // DXGI_FORMAT_R8_UNORM 
	{GUID_WICPixelFormat4bppGray, GUID_WICPixelFormat8bppGray}, // DXGI_FORMAT_R8_UNORM 
	{GUID_WICPixelFormat16bppGrayFixedPoint, GUID_WICPixelFormat16bppGrayHalf}, // DXGI_FORMAT_R16_FLOAT 
	{GUID_WICPixelFormat32bppGrayFixedPoint, GUID_WICPixelFormat32bppGrayFloat}, // DXGI_FORMAT_R32_FLOAT 

#ifdef DXGI_1_2_FORMATS
	{GUID_WICPixelFormat16bppBGR555, GUID_WICPixelFormat16bppBGRA5551}, // DXGI_FORMAT_B5G5R5A1_UNORM
#else
	{GUID_WICPixelFormat16bppBGR555, GUID_WICPixelFormat32bppRGBA}, // DXGI_FORMAT_R8G8B8A8_UNORM
	{GUID_WICPixelFormat16bppBGRA5551, GUID_WICPixelFormat32bppRGBA}, // DXGI_FORMAT_R8G8B8A8_UNORM
	{GUID_WICPixelFormat16bppBGR565, GUID_WICPixelFormat32bppRGBA}, // DXGI_FORMAT_R8G8B8A8_UNORM
#endif // DXGI_1_2_FORMATS

	{GUID_WICPixelFormat32bppBGR101010, GUID_WICPixelFormat32bppRGBA1010102}, // DXGI_FORMAT_R10G10B10A2_UNORM

	{GUID_WICPixelFormat24bppBGR, GUID_WICPixelFormat32bppRGBA}, // DXGI_FORMAT_R8G8B8A8_UNORM 
	{GUID_WICPixelFormat24bppRGB, GUID_WICPixelFormat32bppRGBA}, // DXGI_FORMAT_R8G8B8A8_UNORM 
	{GUID_WICPixelFormat32bppPBGRA, GUID_WICPixelFormat32bppRGBA}, // DXGI_FORMAT_R8G8B8A8_UNORM 
	{GUID_WICPixelFormat32bppPRGBA, GUID_WICPixelFormat32bppRGBA}, // DXGI_FORMAT_R8G8B8A8_UNORM 

	{GUID_WICPixelFormat48bppRGB, GUID_WICPixelFormat64bppRGBA}, // DXGI_FORMAT_R16G16B16A16_UNORM
	{GUID_WICPixelFormat48bppBGR, GUID_WICPixelFormat64bppRGBA}, // DXGI_FORMAT_R16G16B16A16_UNORM
	{GUID_WICPixelFormat64bppBGRA, GUID_WICPixelFormat64bppRGBA}, // DXGI_FORMAT_R16G16B16A16_UNORM
	{GUID_WICPixelFormat64bppPRGBA, GUID_WICPixelFormat64bppRGBA}, // DXGI_FORMAT_R16G16B16A16_UNORM
	{GUID_WICPixelFormat64bppPBGRA, GUID_WICPixelFormat64bppRGBA}, // DXGI_FORMAT_R16G16B16A16_UNORM

	{GUID_WICPixelFormat48bppRGBFixedPoint, GUID_WICPixelFormat64bppRGBAHalf}, // DXGI_FORMAT_R16G16B16A16_FLOAT 
	{GUID_WICPixelFormat48bppBGRFixedPoint, GUID_WICPixelFormat64bppRGBAHalf}, // DXGI_FORMAT_R16G16B16A16_FLOAT 
	{GUID_WICPixelFormat64bppRGBAFixedPoint, GUID_WICPixelFormat64bppRGBAHalf}, // DXGI_FORMAT_R16G16B16A16_FLOAT 
	{GUID_WICPixelFormat64bppBGRAFixedPoint, GUID_WICPixelFormat64bppRGBAHalf}, // DXGI_FORMAT_R16G16B16A16_FLOAT 
	{GUID_WICPixelFormat64bppRGBFixedPoint, GUID_WICPixelFormat64bppRGBAHalf}, // DXGI_FORMAT_R16G16B16A16_FLOAT 
	{GUID_WICPixelFormat64bppRGBHalf, GUID_WICPixelFormat64bppRGBAHalf}, // DXGI_FORMAT_R16G16B16A16_FLOAT 
	{GUID_WICPixelFormat48bppRGBHalf, GUID_WICPixelFormat64bppRGBAHalf}, // DXGI_FORMAT_R16G16B16A16_FLOAT 

	{GUID_WICPixelFormat128bppPRGBAFloat, GUID_WICPixelFormat128bppRGBAFloat}, // DXGI_FORMAT_R32G32B32A32_FLOAT 
	{GUID_WICPixelFormat128bppRGBFloat, GUID_WICPixelFormat128bppRGBAFloat}, // DXGI_FORMAT_R32G32B32A32_FLOAT 
	{GUID_WICPixelFormat128bppRGBAFixedPoint, GUID_WICPixelFormat128bppRGBAFloat}, // DXGI_FORMAT_R32G32B32A32_FLOAT 
	{GUID_WICPixelFormat128bppRGBFixedPoint, GUID_WICPixelFormat128bppRGBAFloat}, // DXGI_FORMAT_R32G32B32A32_FLOAT 
	{GUID_WICPixelFormat32bppRGBE, GUID_WICPixelFormat128bppRGBAFloat}, // DXGI_FORMAT_R32G32B32A32_FLOAT 

	{GUID_WICPixelFormat32bppCMYK, GUID_WICPixelFormat32bppRGBA}, // DXGI_FORMAT_R8G8B8A8_UNORM 
	{GUID_WICPixelFormat64bppCMYK, GUID_WICPixelFormat64bppRGBA}, // DXGI_FORMAT_R16G16B16A16_UNORM
	{GUID_WICPixelFormat40bppCMYKAlpha, GUID_WICPixelFormat64bppRGBA}, // DXGI_FORMAT_R16G16B16A16_UNORM
	{GUID_WICPixelFormat80bppCMYKAlpha, GUID_WICPixelFormat64bppRGBA}, // DXGI_FORMAT_R16G16B16A16_UNORM

#if (_WIN32_WINNT >= _WIN32_WINNT_WIN8) || defined(_WIN7_PLATFORM_UPDATE)
	{GUID_WICPixelFormat32bppRGB, GUID_WICPixelFormat32bppRGBA}, // DXGI_FORMAT_R8G8B8A8_UNORM
	{GUID_WICPixelFormat64bppRGB, GUID_WICPixelFormat64bppRGBA}, // DXGI_FORMAT_R16G16B16A16_UNORM
	{GUID_WICPixelFormat64bppPRGBAHalf, GUID_WICPixelFormat64bppRGBAHalf}, // DXGI_FORMAT_R16G16B16A16_FLOAT 
#endif
	};
	if (auto v��ʽ = vͼ��ת��.find(guid); v��ʽ != vͼ��ת��.end()) {
		return v��ʽ->second;
	}
	return guid;
}
DXGI_FORMAT f��srgb(DXGI_FORMAT a��ʽ) {
	static const std::unordered_map<DXGI_FORMAT, DXGI_FORMAT> vת���� = {
		{DXGI_FORMAT_R8G8B8A8_UNORM, DXGI_FORMAT_R8G8B8A8_UNORM_SRGB},
	{DXGI_FORMAT_BC1_UNORM, DXGI_FORMAT_BC1_UNORM_SRGB},
	{DXGI_FORMAT_BC2_UNORM, DXGI_FORMAT_BC2_UNORM_SRGB},
	{DXGI_FORMAT_BC3_UNORM, DXGI_FORMAT_BC3_UNORM_SRGB},
	{DXGI_FORMAT_B8G8R8A8_UNORM, DXGI_FORMAT_B8G8R8A8_UNORM_SRGB},
	{DXGI_FORMAT_B8G8R8X8_UNORM, DXGI_FORMAT_B8G8R8X8_UNORM_SRGB},
	{DXGI_FORMAT_BC7_UNORM, DXGI_FORMAT_BC7_UNORM_SRGB}
	};
	if (auto vĿ���ʽ = vת����.find(a��ʽ); vĿ���ʽ != vת����.end()) {
		return vĿ���ʽ->second;
	}
	return a��ʽ;
}
bool fiͨ�ø�ʽ(const GUID &a��ʽ) {
	static const std::unordered_set<GUID> v��ʽ�� = {
		GUID_WICPixelFormat128bppRGBAFloat,

		GUID_WICPixelFormat64bppRGBAHalf,
		GUID_WICPixelFormat64bppRGBA,

		GUID_WICPixelFormat32bppRGBA,
		GUID_WICPixelFormat32bppBGRA, // DXGI 1.1
		GUID_WICPixelFormat32bppBGR, // DXGI 1.1

		GUID_WICPixelFormat32bppRGBA1010102XR, // DXGI 1.1
		GUID_WICPixelFormat32bppRGBA1010102,

#ifdef DXGI_1_2_FORMATS

		GUID_WICPixelFormat16bppBGRA5551,
		GUID_WICPixelFormat16bppBGR565,

#endif // DXGI_1_2_FORMATS

		GUID_WICPixelFormat32bppGrayFloat,
		GUID_WICPixelFormat16bppGrayHalf,
		GUID_WICPixelFormat16bppGray,
		GUID_WICPixelFormat8bppGray,

		GUID_WICPixelFormat8bppAlpha,
	};
	return v��ʽ��.count(a��ʽ) != 0;
}
}
//=============================================================================
// ����ӿ�
//=============================================================================
size_t I����::fg���() const {
	return this->fg��() * this->fg��();
}
size_t I����::fg�о�() const {
	return this->fg��() * this->fg���ش�С();
}
size_t I����::fgͼ���С() const {
	return this->fg���() * this->fg���ش�С();
}
S�������� I����::fg����() const {
	return S��������{this->fg��(), this->fg��(), this->fg���ش�С(), this->fg��ʽ()};
}
//=============================================================================
// ��������
//=============================================================================
size_t Cֻ������::fg��() const {
	return m��;
}
size_t Cֻ������::fg��() const {
	return m��;
}
size_t Cֻ������::fg���ش�С() const {
	return m���ش�С;
}
size_t Cֻ������::fg���() const {
	return m�� * m��;
}
size_t Cֻ������::fg�о�() const {
	return m�� * m���ش�С;
}
size_t Cֻ������::fgͼ���С() const {
	return fg���() * m���ش�С;
}
DXGI_FORMAT Cֻ������::fg��ʽ() const {
	return m��ʽ;
}
const std::byte *Cֻ������::fg����() const {
	return mp����.get();
}
//=============================================================================
// �Զ�������
//=============================================================================
void C�Զ�������::f��ʼ��(size_t a��, size_t a��) {
	m�� = a��;
	m�� = a��;
	mp���� = std::make_unique<��ѧ::S��ɫ[]>(m�� * a��);
}
size_t C�Զ�������::fg��() const {
	return m��;
}
size_t C�Զ�������::fg��() const {
	return m��;
}
size_t C�Զ�������::fg���ش�С() const {
	return c���ش�С;
}
size_t C�Զ�������::fg���() const {
	return m�� * m��;
}
size_t C�Զ�������::fg�о�() const {
	return m�� * c���ش�С;
}
size_t C�Զ�������::fgͼ���С() const {
	return fg���() * c���ش�С;
}
DXGI_FORMAT C�Զ�������::fg��ʽ() const {
	return c��ʽ;
}
const std::byte *C�Զ�������::fg����() const {
	return (std::byte*)fg��ɫ����();
}
const ��ѧ::S��ɫ *C�Զ�������::fg��ɫ����() const {
	return mp����.get();
}
��ѧ::S��ɫ &C�Զ�������::fg����(size_t u, size_t v) {
	return mp����[v * m�� + u];
}
const ��ѧ::S��ɫ &C�Զ�������::fg����(size_t u, size_t v) const {
	return mp����[v * m�� + u];
}
��ѧ::S��ɫ C�Զ�������::f���Բ���(float u, float v) const {
	const float v����u = ��ѧ::f����(u, m��);
	const float v����v = ��ѧ::f����(v, m��);
	const float v�ذ�u = floor(u);
	const float v�ذ�v = floor(v);
	const size_t u0 = (size_t)v�ذ�u;
	const size_t u1 = (size_t)(v�ذ�u + 1);
	const size_t v0 = (size_t)v�ذ�v;
	const size_t v1 = (size_t)(v�ذ�v + 1);
	const float v��ֵu = v����u - v�ذ�u;
	const ��ѧ::S��ɫ v��ɫ0 = ��ѧ::f��ֵ<��ѧ::S��ɫ>(fg����(u0, v0), fg����(u0, v0), v��ֵu);
	const ��ѧ::S��ɫ v��ɫ1 = ��ѧ::f��ֵ<��ѧ::S��ɫ>(fg����(u0, v1), fg����(u0, v1), v��ֵu);
	const float v��ֵv = v����v - v�ذ�v;
	return ��ѧ::f��ֵ<��ѧ::S��ɫ>(v��ɫ0, v��ɫ1, v��ֵv);
}
}	//namespace cflw::ͼ��