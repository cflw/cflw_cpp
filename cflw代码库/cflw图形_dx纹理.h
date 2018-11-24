#pragma once
#include <memory>
#include <wincodec.h>
#include <wrl.h>
#include <dxgi.h>
#include "cflw数学_图形.h"
namespace cflw::图形::dx纹理 {
//格式
namespace 格式 {
bool f检查srgb(IWICBitmapFrameDecode *);
DXGI_FORMAT f到dxgi(const GUID &);
GUID f到通用格式(const GUID &);
DXGI_FORMAT f到srgb(DXGI_FORMAT);
bool fi通用格式(const GUID &);
}
//声明
using Microsoft::WRL::ComPtr;
class C只读纹理;
//==============================================================================
// 工厂
//==============================================================================
class C图像工厂 {
public:
	~C图像工厂();
	HRESULT f初始化();
	HRESULT f读取图像(const wchar_t *, IWICBitmapFrameDecode **);
	std::unique_ptr<std::byte[]> f复制像素数据(IWICBitmapSource *, size_t *像素大小 = nullptr, size_t *行距 = nullptr, size_t *图像大小 = nullptr);
	size_t f像素大小(const GUID &);
	WICBitmapPlaneDescription f取图像描述(IWICBitmapSource *);
	HRESULT f图像尺寸变换(IWICBitmapSource *, size_t, size_t, IWICBitmapScaler **);
	HRESULT f图像格式变换(IWICBitmapSource *, const GUID &, IWICFormatConverter **);
	std::unique_ptr<C只读纹理> f一键读取(const wchar_t *);
	//格式转换&计算
public:
	ComPtr<IWICImagingFactory> m工厂;
};
//==============================================================================
// 结构
//==============================================================================
struct S纹理描述 {
	size_t fg宽() const { return m宽; }
	size_t fg高() const { return m高; }
	size_t fg面积() const { return m宽 * m高; }
	size_t fg像素大小() const { return m像素大小; }
	size_t fg行距() const { return m宽 * m像素大小; }
	size_t fg图像大小() const { return m宽 * m高 * m像素大小; }
	size_t fg格式() const { return m格式; }
	size_t m宽;
	size_t m高;
	size_t m像素大小;
	DXGI_FORMAT m格式;
};
//==============================================================================
// 各种纹理
//==============================================================================
class I纹理 {
public:
	virtual size_t fg宽() const = 0;
	virtual size_t fg高() const = 0;
	virtual size_t fg像素大小() const = 0;
	virtual size_t fg面积() const;
	virtual size_t fg行距() const;
	virtual size_t fg图像大小() const;
	virtual DXGI_FORMAT fg格式() const = 0;
	virtual const std::byte *fg数据() const = 0;
	virtual S纹理描述 fg描述() const;
};
class C只读纹理 : public I纹理 {
	friend class C图像工厂;
public:
	size_t fg宽() const override;
	size_t fg高() const override;
	size_t fg像素大小() const override;
	size_t fg面积() const override;
	size_t fg行距() const override;
	size_t fg图像大小() const override;
	DXGI_FORMAT fg格式() const override;
	const std::byte *fg数据() const override;
private:
	std::unique_ptr<std::byte[]> mp数据;
	DXGI_FORMAT m格式 = DXGI_FORMAT_UNKNOWN;
	size_t m宽 = 0, m高 = 0, m行距 = 0, m大小 = 0, m像素大小 = 0;
};
//自定义纹理
class C自定义纹理 : public I纹理 {
public:
	static constexpr DXGI_FORMAT c格式 = DXGI_FORMAT_R32G32B32A32_FLOAT;
	static constexpr size_t c像素大小 = sizeof(数学::S颜色);
	void f初始化(size_t, size_t);
	size_t fg宽() const override;
	size_t fg高() const override;
	size_t fg像素大小() const override;
	size_t fg面积() const override;
	size_t fg行距() const override;
	size_t fg图像大小() const override;
	DXGI_FORMAT fg格式() const override;
	const std::byte *fg数据() const override;
	const 数学::S颜色 *fg颜色数据() const;
	数学::S颜色 &fg像素(size_t, size_t);
	const 数学::S颜色 &fg像素(size_t, size_t) const;
	数学::S颜色 f线性采样(float, float) const;
private:
	std::unique_ptr<数学::S颜色[]> mp像素;
	size_t m宽 = 0, m高 = 0;
};
}