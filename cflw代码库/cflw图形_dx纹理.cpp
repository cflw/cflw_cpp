#include <cassert>
#include <unordered_map>
#include <unordered_set>
#include "cflw图形_dx纹理.h"
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
namespace cflw::图形::dx纹理 {
C图像工厂::~C图像工厂() {
	m工厂.Reset();
	CoUninitialize();
}
HRESULT C图像工厂::f初始化() {
	CoInitializeEx(nullptr, COINIT_MULTITHREADED);
	HRESULT hr = CoCreateInstance(CLSID_WICImagingFactory1, nullptr, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&m工厂));
	if (FAILED(hr)) {
		return hr;
	}
	return S_OK;
}
HRESULT C图像工厂::f读取图像(const wchar_t *p文件, IWICBitmapFrameDecode **p帧) {
	HRESULT hr;
	ComPtr<IWICBitmapDecoder> v解码器;
	hr = m工厂->CreateDecoderFromFilename(p文件, 0, GENERIC_READ, WICDecodeMetadataCacheOnDemand, &v解码器);
	if (FAILED(hr)) {
		return hr;
	}
	hr = v解码器->GetFrame(0, p帧);
	if (FAILED(hr)) {
		return hr;
	}
	return S_OK;
}
std::unique_ptr<std::byte[]> C图像工厂::f复制像素数据(IWICBitmapSource *a帧, size_t *ap像素大小, size_t *ap行距, size_t *ap图像大小) {
	const WICBitmapPlaneDescription v描述 = f取图像描述(a帧);
	const size_t v像素大小 = f像素大小(v描述.Format);
	const size_t v一排大小 = v描述.Width * v像素大小;
	const size_t v数据大小 = v一排大小 * v描述.Height;
	std::unique_ptr<std::byte[]> v数据 = std::make_unique<std::byte[]>(v数据大小);
	a帧->CopyPixels(0, v一排大小, v数据大小, (BYTE*)v数据.get());
	if (ap像素大小) {
		*ap像素大小 = v像素大小;
	}
	if (ap行距) {
		*ap行距 = v一排大小;
	}
	if (ap图像大小) {
		*ap图像大小 = v数据大小;
	}
	return v数据;
}
WICBitmapPlaneDescription C图像工厂::f取图像描述(IWICBitmapSource *a帧) {
	WICBitmapPlaneDescription v;
	a帧->GetPixelFormat(&v.Format);
	a帧->GetSize(&v.Width, &v.Height);
	return v;
}
size_t C图像工厂::f像素大小(const GUID &guid) {
	HRESULT hr;
	ComPtr<IWICComponentInfo> v组件信息;
	hr = m工厂->CreateComponentInfo(guid, &v组件信息);
	if (FAILED(hr)) {
		return 0;
	}
	WICComponentType v类型;
	v组件信息->GetComponentType(&v类型);
	if (v类型 != WICPixelFormat) {
		return 0;
	}
	ComPtr<IWICPixelFormatInfo> v格式信息;
	hr = v组件信息.As(&v格式信息);
	if (FAILED(hr)) {
		return 0;
	}
	UINT bpp;
	v格式信息->GetBitsPerPixel(&bpp);
	return bpp;
}
HRESULT C图像工厂::f图像尺寸变换(IWICBitmapSource *a帧, size_t a宽, size_t a高, IWICBitmapScaler **a输出) {
	HRESULT hr;
	IWICBitmapScaler *&v缩放 = *a输出;
	hr = m工厂->CreateBitmapScaler(&v缩放);
	if (FAILED(hr)) {
		return hr;
	}
	hr = v缩放->Initialize(a帧, a宽, a高, WICBitmapInterpolationModeFant);
	if (FAILED(hr)) {
		return hr;
	}
	return S_OK;
}
HRESULT C图像工厂::f图像格式变换(IWICBitmapSource *a图像, const GUID &a格式, IWICFormatConverter **a输出) {
	HRESULT hr;
	IWICFormatConverter *&v转换 = *a输出;
	hr = m工厂->CreateFormatConverter(&v转换);
	if (FAILED(hr)) {
		return hr;
	}
	hr = v转换->Initialize(a图像, a格式, WICBitmapDitherTypeErrorDiffusion, 0, 0, WICBitmapPaletteTypeCustom);
	if (FAILED(hr)) {
		return hr;
	}
	return S_OK;
}
std::unique_ptr<C只读纹理> C图像工厂::f一键读取(const wchar_t *a文件名) {
	ComPtr<IWICBitmapFrameDecode> v图像;
	HRESULT hr = f读取图像(a文件名, &v图像);
	if (FAILED(hr)) {
		return nullptr;
	}
	//格式转换并复制数据
	const WICBitmapPlaneDescription v描述 = f取图像描述(v图像.Get());
	std::unique_ptr<C只读纹理> v纹理 = std::make_unique<C只读纹理>();
	GUID v图像格式 = v描述.Format;
	v纹理->m宽 = v描述.Width;
	v纹理->m高 = v描述.Height;
	if (格式::fi通用格式(v图像格式)) {
		v纹理->mp数据 = f复制像素数据(v图像.Get(), &v纹理->m像素大小, &v纹理->m行距, nullptr);
	} else {
		ComPtr<IWICFormatConverter> v格式转换;
		v图像格式 = 格式::f到通用格式(v图像格式);
		f图像格式变换(v图像.Get(), v图像格式, &v格式转换);
		v纹理->mp数据 = f复制像素数据(v格式转换.Get(), &v纹理->m像素大小, &v纹理->m行距, nullptr);
	}
	v纹理->m格式 = 格式::f到dxgi(v图像格式);
	return v纹理;
}
//=============================================================================
// 格式
//=============================================================================
namespace 格式 {
bool f检查srgb(IWICBitmapFrameDecode *a图像) {
	HRESULT hr;
	ComPtr<IWICMetadataQueryReader> v读元数据;
	hr = a图像->GetMetadataQueryReader(&v读元数据);
	if (FAILED(hr)) {
		return false;
	}
	GUID v格式;
	hr = v读元数据->GetContainerFormat(&v格式);
	if (FAILED(hr)) {
		return false;
	}
	bool v = false;
	PROPVARIANT v值;
	PropVariantInit(&v值);
	if (memcmp(&v格式, &GUID_ContainerFormatPng, sizeof(GUID)) == 0) {
		hr = v读元数据->GetMetadataByName(L"/sRGB/RenderingIntent", &v值);
		if (SUCCEEDED(hr)) {
			if (v值.vt == VT_UI1) {
				v = true;
			}
		}
	} else {
		hr = v读元数据->GetMetadataByName(L"System.Image.ColorSpace", &v值);
		if (SUCCEEDED(hr)) {
			if (v值.vt == VT_UI2 && v值.uiVal == 1) {
				v = true;
			}
		}
	}
	PropVariantClear(&v值);
	return v;
}
DXGI_FORMAT f到dxgi(const GUID &guid) {
	static const std::unordered_map<GUID, DXGI_FORMAT> v图像格式 = {
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
	if (auto v格式 = v图像格式.find(guid); v格式 != v图像格式.end()) {
		return v格式->second;
	}
	return DXGI_FORMAT_UNKNOWN;
}
GUID f到通用格式(const GUID &guid) {
	static const std::unordered_map<GUID, GUID> v图像转换 = {
		// 注意目标GUID在这个转换表必须是那些直接支持的格式（段）中的一个。
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
	if (auto v格式 = v图像转换.find(guid); v格式 != v图像转换.end()) {
		return v格式->second;
	}
	return guid;
}
DXGI_FORMAT f到srgb(DXGI_FORMAT a格式) {
	static const std::unordered_map<DXGI_FORMAT, DXGI_FORMAT> v转换表 = {
		{DXGI_FORMAT_R8G8B8A8_UNORM, DXGI_FORMAT_R8G8B8A8_UNORM_SRGB},
	{DXGI_FORMAT_BC1_UNORM, DXGI_FORMAT_BC1_UNORM_SRGB},
	{DXGI_FORMAT_BC2_UNORM, DXGI_FORMAT_BC2_UNORM_SRGB},
	{DXGI_FORMAT_BC3_UNORM, DXGI_FORMAT_BC3_UNORM_SRGB},
	{DXGI_FORMAT_B8G8R8A8_UNORM, DXGI_FORMAT_B8G8R8A8_UNORM_SRGB},
	{DXGI_FORMAT_B8G8R8X8_UNORM, DXGI_FORMAT_B8G8R8X8_UNORM_SRGB},
	{DXGI_FORMAT_BC7_UNORM, DXGI_FORMAT_BC7_UNORM_SRGB}
	};
	if (auto v目标格式 = v转换表.find(a格式); v目标格式 != v转换表.end()) {
		return v目标格式->second;
	}
	return a格式;
}
bool fi通用格式(const GUID &a格式) {
	static const std::unordered_set<GUID> v格式表 = {
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
	return v格式表.count(a格式) != 0;
}
}
//=============================================================================
// 纹理接口
//=============================================================================
size_t I纹理::fg面积() const {
	return this->fg宽() * this->fg高();
}
size_t I纹理::fg行距() const {
	return this->fg宽() * this->fg像素大小();
}
size_t I纹理::fg图像大小() const {
	return this->fg面积() * this->fg像素大小();
}
S纹理描述 I纹理::fg描述() const {
	return S纹理描述{this->fg宽(), this->fg高(), this->fg像素大小(), this->fg格式()};
}
//=============================================================================
// 常量纹理
//=============================================================================
size_t C只读纹理::fg宽() const {
	return m宽;
}
size_t C只读纹理::fg高() const {
	return m高;
}
size_t C只读纹理::fg像素大小() const {
	return m像素大小;
}
size_t C只读纹理::fg面积() const {
	return m宽 * m高;
}
size_t C只读纹理::fg行距() const {
	return m宽 * m像素大小;
}
size_t C只读纹理::fg图像大小() const {
	return fg面积() * m像素大小;
}
DXGI_FORMAT C只读纹理::fg格式() const {
	return m格式;
}
const std::byte *C只读纹理::fg数据() const {
	return mp数据.get();
}
//=============================================================================
// 自定义纹理
//=============================================================================
void C自定义纹理::f初始化(size_t a宽, size_t a高) {
	m宽 = a宽;
	m高 = a高;
	mp像素 = std::make_unique<数学::S颜色[]>(m宽 * a高);
}
size_t C自定义纹理::fg宽() const {
	return m宽;
}
size_t C自定义纹理::fg高() const {
	return m高;
}
size_t C自定义纹理::fg像素大小() const {
	return c像素大小;
}
size_t C自定义纹理::fg面积() const {
	return m宽 * m高;
}
size_t C自定义纹理::fg行距() const {
	return m宽 * c像素大小;
}
size_t C自定义纹理::fg图像大小() const {
	return fg面积() * c像素大小;
}
DXGI_FORMAT C自定义纹理::fg格式() const {
	return c格式;
}
const std::byte *C自定义纹理::fg数据() const {
	return (std::byte*)fg颜色数据();
}
const 数学::S颜色 *C自定义纹理::fg颜色数据() const {
	return mp像素.get();
}
数学::S颜色 &C自定义纹理::fg像素(size_t u, size_t v) {
	return mp像素[v * m宽 + u];
}
const 数学::S颜色 &C自定义纹理::fg像素(size_t u, size_t v) const {
	return mp像素[v * m宽 + u];
}
数学::S颜色 C自定义纹理::f线性采样(float u, float v) const {
	const float v限制u = 数学::f求余(u, m宽);
	const float v限制v = 数学::f求余(v, m高);
	const float v地板u = floor(u);
	const float v地板v = floor(v);
	const size_t u0 = (size_t)v地板u;
	const size_t u1 = (size_t)(v地板u + 1);
	const size_t v0 = (size_t)v地板v;
	const size_t v1 = (size_t)(v地板v + 1);
	const float v差值u = v限制u - v地板u;
	const 数学::S颜色 v颜色0 = 数学::f插值<数学::S颜色>(fg像素(u0, v0), fg像素(u0, v0), v差值u);
	const 数学::S颜色 v颜色1 = 数学::f插值<数学::S颜色>(fg像素(u0, v1), fg像素(u0, v1), v差值u);
	const float v差值v = v限制v - v地板v;
	return 数学::f插值<数学::S颜色>(v颜色0, v颜色1, v差值v);
}
}	//namespace cflw::图形