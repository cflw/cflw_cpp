#include <wrl.h>
#include "cflw工具.h"
#include "cflw图形_d2d.h"
#include "cflw视窗.h"
#include "cflw图形_dx纹理.h"
//声明
using Microsoft::WRL::ComPtr;
namespace cflw::图形::d2d {
//==============================================================================
// 二维
//==============================================================================
C二维 *C二维::g这 = nullptr;
//函数
C二维::C二维() {
	assert(g这 == nullptr);	//单例
	g这 = this;
}
HRESULT C二维::f初始化(HWND a窗口, float a缩放) {
	const 视窗::S客户区尺寸 v尺寸 = 视窗::S客户区尺寸::fc窗口(a窗口);
	f初始化_窗口大小(v尺寸.fg宽() / a缩放, v尺寸.fg高() / a缩放);
	HRESULT hr;
	hr = f初始化_工厂();
	if (FAILED(hr)) {
		return hr;
	}
	const 数学::S向量2 dpi = fg每英寸点数(a缩放);
	const D2D1_RENDER_TARGET_PROPERTIES v渲染目标属性 = D2D1::RenderTargetProperties(
		D2D1_RENDER_TARGET_TYPE_DEFAULT,
		D2D1::PixelFormat(),
		dpi.x, dpi.y
	);
	ComPtr<ID2D1HwndRenderTarget> v窗口渲染目标;
	hr = m二维工厂->CreateHwndRenderTarget(
		v渲染目标属性,
		D2D1::HwndRenderTargetProperties(
			a窗口, D2D1::SizeU(v尺寸.fg宽(), v尺寸.fg高())
		),
		&v窗口渲染目标);
	if (FAILED(hr)) {
		return hr;
	}
	f初始化_渲染目标(v窗口渲染目标.Get());
	return S_OK;
}
HRESULT C二维::f初始化(IDXGISwapChain *a交换链, float a缩放) {
	// 注意：不支持d3d12创建的交换链
	ComPtr<IDXGISurface> v后台缓冲 = nullptr;
	HRESULT hr = a交换链->GetBuffer(0, IID_PPV_ARGS(&v后台缓冲));
	if (FAILED(hr)) {
		return hr;
	}
	hr = f初始化_工厂();
	if (FAILED(hr)) {
		return hr;
	}
	const 数学::S向量2 dpi = fg每英寸点数(a缩放);
	const D2D1_RENDER_TARGET_PROPERTIES v渲染目标属性 = D2D1::RenderTargetProperties(
		D2D1_RENDER_TARGET_TYPE_DEFAULT,
		D2D1::PixelFormat(DXGI_FORMAT_R8G8B8A8_UNORM, D2D1_ALPHA_MODE_PREMULTIPLIED),
		dpi.x, dpi.y);
	ComPtr<ID2D1RenderTarget> v后台渲染目标;
	hr = m二维工厂->CreateDxgiSurfaceRenderTarget(v后台缓冲.Get(), v渲染目标属性, &v后台渲染目标);
	if (FAILED(hr)) {
		return hr;
	}
	const D2D1_SIZE_F v大小 = v后台渲染目标->GetSize();
	f初始化_窗口大小(v大小.width, v大小.height);
	f初始化_渲染目标(v后台渲染目标.Get());
	return S_OK;
}
HRESULT C二维::f初始化_工厂() {
	if (m二维工厂 == nullptr) {
		HRESULT hr = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, m二维工厂.GetAddressOf());
		return hr;
	} else {
		return S_OK;
	}
}
HRESULT C二维::f初始化_设备(IDXGIDevice *a设备) {
	HRESULT hr = f初始化_工厂();
	if (FAILED(hr)) {
		return hr;
	}
	m二维工厂->CreateDevice(a设备, &m设备);
	if (FAILED(hr)) {
		return hr;
	}
	hr = m设备->CreateDeviceContext(D2D1_DEVICE_CONTEXT_OPTIONS_NONE, &m上下文);
	if (FAILED(hr)) {
		return hr;
	}
	f初始化_渲染目标(m上下文.Get());
	return S_OK;
}
void C二维::f初始化_窗口大小(float x, float y) {
	m窗口大小.x = x;
	m窗口大小.y = y;
	if (m坐标计算 == nullptr) {
		m坐标计算 = std::make_unique<C坐标转换>();
	}
	m坐标计算->fs大小(m窗口大小);
}
void C二维::f初始化_渲染目标(ID2D1RenderTarget *a) {
	m渲染目标 = a;
	m渲染目标->SetAntialiasMode(D2D1_ANTIALIAS_MODE_ALIASED);
}
HRESULT C二维::f初始化_单个位图(IDXGISwapChain *a交换链, float a缩放) {
	ComPtr<IDXGISurface> v后台缓冲 = nullptr;
	HRESULT hr = a交换链->GetBuffer(0, IID_PPV_ARGS(&v后台缓冲));
	if (FAILED(hr)) {
		return hr;
	}
	const 数学::S向量2 dpi = fg每英寸点数(a缩放);
	const D2D1_BITMAP_PROPERTIES1 v位图属性 = D2D1::BitmapProperties1(
		D2D1_BITMAP_OPTIONS_TARGET | D2D1_BITMAP_OPTIONS_CANNOT_DRAW,
		D2D1::PixelFormat(DXGI_FORMAT_UNKNOWN, D2D1_ALPHA_MODE_PREMULTIPLIED),
		dpi.x, dpi.y
	);
	m上下文->SetDpi(dpi.x, dpi.y);
	ComPtr<ID2D1Bitmap1> v位图目标;
	hr = m上下文->CreateBitmapFromDxgiSurface(v后台缓冲.Get(), &v位图属性, &v位图目标);
	if (FAILED(hr)) {
		return hr;
	}
	m上下文->SetTarget(v位图目标.Get());
	const D2D1_SIZE_F v大小 = v位图目标->GetSize();
	f初始化_窗口大小(v大小.width, v大小.height);
	return S_OK;
}
void C二维::f销毁() {
	m默认文本格式.Reset();
	m渲染目标.Reset();
	m文本工厂.reset();
	m坐标计算.reset();
	m渲染控制.reset();
	ma位图目标.clear();
	m上下文.Reset();
	m设备.Reset();
}
void C二维::fs缩放(float a) {
	float v = 96 * a;
	m渲染目标->SetDpi(v, v);
}
//画图
std::shared_ptr<C画图形> C二维::fc画图形(const ComPtr<ID2D1Brush> &a画笔, float a宽度) {
	std::shared_ptr<C画图形> v新 = std::make_shared<C画图形>();
	v新->f初始化(m渲染目标.Get(), fg坐标计算());
	if (a画笔) {
		v新->fs画笔(a画笔);
	} else {
		v新->f初始化_纯色画笔(数学::S颜色::c白);
	}
	v新->fs线条宽度(a宽度);
	return v新;
}
std::shared_ptr<C画文本> C二维::fc画文本(const ComPtr<ID2D1Brush> &a画笔) {
	std::shared_ptr<C画文本> v新 = std::make_shared<C画文本>();
	v新->f初始化(m渲染目标.Get(), fg坐标计算());
	if (a画笔) {
		v新->fs画笔(a画笔);
	} else {
		v新->f初始化_纯色画笔(数学::S颜色::c白);
	}
	v新->m格式 = fg默认文本格式();
	return v新;
}
ComPtr<ID2D1SolidColorBrush> C二维::fc纯色画笔(const 数学::S颜色 &a颜色) const {
	ComPtr<ID2D1SolidColorBrush> v画笔;
	m渲染目标->CreateSolidColorBrush(C类型转换::f颜色(a颜色), &v画笔);
	return v画笔;
}
ComPtr<ID2D1Bitmap> C二维::fc位图(const dx纹理::I纹理 &a纹理) {
	const D2D1_SIZE_U v大小 = {a纹理.fg宽(), a纹理.fg宽()};
	const D2D1_BITMAP_PROPERTIES v属性 = {{a纹理.fg格式(), D2D1_ALPHA_MODE_STRAIGHT}, 96, 96};
	ComPtr<ID2D1Bitmap> v位图;
	HRESULT hr = m渲染目标->CreateBitmap(v大小, a纹理.fg数据(), a纹理.fg行距(), v属性, &v位图);
	return v位图;
}
ComPtr<ID2D1Bitmap> C二维::fc位图(const ComPtr<IWICBitmapSource> &a源) {
	ComPtr<ID2D1Bitmap> v位图;
	HRESULT hr = m渲染目标->CreateBitmapFromWicBitmap(a源.Get(), &v位图);
	return v位图;
}
ComPtr<ID2D1BitmapBrush> C二维::fc位图画笔(const ComPtr<ID2D1Bitmap> &a位图) {
	ComPtr<ID2D1BitmapBrush> v画笔;
	HRESULT hr = m渲染目标->CreateBitmapBrush(a位图.Get(), &v画笔);
	return v画笔;
}
ComPtr<ID2D1GradientStopCollection> C二维::fc渐变点集(const std::vector<S渐变点> &a) const {
	std::vector<D2D1_GRADIENT_STOP> va渐变点 = C类型转换::f渐变点(a);
	ComPtr<ID2D1GradientStopCollection> v渐变点集;
	m渲染目标->CreateGradientStopCollection(va渐变点.data(), va渐变点.size(), &v渐变点集);
	return v渐变点集;
}
ComPtr<ID2D1LinearGradientBrush> C二维::fc线性渐变画笔(const std::vector<S渐变点> &a) const {
	ComPtr<ID2D1GradientStopCollection> v渐变点集 = fc渐变点集(a);
	ComPtr<ID2D1LinearGradientBrush> v画笔;
	//未完成
	return v画笔;
}
ComPtr<ID2D1RadialGradientBrush> C二维::fc径向渐变画笔(const std::vector<S渐变点> &a) const {
	ComPtr<ID2D1GradientStopCollection> v渐变点集 = fc渐变点集(a);
	ComPtr<ID2D1RadialGradientBrush> v画笔;
	//未完成
	return v画笔;
}
ComPtr<ID2D1PathGeometry> C二维::fc路径几何() const {
	ComPtr<ID2D1PathGeometry> v路径几何;
	m二维工厂->CreatePathGeometry(&v路径几何);
	return v路径几何;
}
ComPtr<ID2D1Layer> C二维::fc层() const {
	ComPtr<ID2D1Layer> v层;
	m渲染目标->CreateLayer(&v层);
	return v层;
}
C修改路径几何 C二维::f修改路径几何(const ComPtr<ID2D1PathGeometry> &a) const {
	return C修改路径几何(a.Get(), fg坐标计算());
}
ComPtr<C文本效果> C二维::fc文本效果(const 数学::S颜色 &a描边, const 数学::S颜色 &a填充) const {
	C文本效果 *v0 = new C文本效果();
	v0->m二维工厂 = m二维工厂;
	v0->m渲染目标 = fg渲染目标();
	m渲染目标->CreateSolidColorBrush(C类型转换::f颜色(a填充), &v0->m填充画笔);
	m渲染目标->CreateSolidColorBrush(C类型转换::f颜色(a描边), &v0->m轮廓画笔);
	ComPtr<C文本效果> v1;
	*v1.GetAddressOf() = v0;
	return v1;
}
ComPtr<ID2D1Effect> C二维::fc效果(const GUID &a) {
	ComPtr<ID2D1Effect> v;
	m上下文->CreateEffect(a, &v);
	return v;
}
ComPtr<ID2D1Factory3> C二维::fg二维工厂() {
	if (m二维工厂 == nullptr) {
		HRESULT hr = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, m二维工厂.GetAddressOf());
	}
	return m二维工厂;
}
ComPtr<ID2D1RenderTarget> C二维::fg渲染目标() const {
	return m渲染目标;
}
C坐标转换 &C二维::fg坐标计算() const {
	return *m坐标计算;
}
C文本工厂 &C二维::fg文本工厂() {
	if (m文本工厂 == nullptr) {
		m文本工厂 = std::make_unique<C文本工厂>();
		m文本工厂->f初始化();
	}
	return *m文本工厂;
}
C渲染控制 &C二维::fg渲染控制() {
	if (m渲染控制 == nullptr) {
		m渲染控制 = std::make_unique<C渲染控制>();
		m渲染控制->m二维 = this;
	}
	return *m渲染控制;
}
ComPtr<IDWriteTextFormat> C二维::fg默认文本格式() {
	if (m默认文本格式 == nullptr) {
		C文本工厂 &v文本工厂 = fg文本工厂();
		m默认文本格式 = v文本工厂.fc文本格式(S文本格式参数());
	}
	return m默认文本格式;
}
数学::S向量2 C二维::fg每英寸点数(float a缩放) const {
	数学::S向量2 dpi;
	if (a缩放) {
		dpi = 数学::S向量2::fc相同(96 * a缩放);
	} else {
		m二维工厂->GetDesktopDpi(&dpi.x, &dpi.y);
	}
	return dpi;
}
//==============================================================================
// 渲染控制
//==============================================================================
void C渲染控制::f开始() {
	m二维->m渲染目标->BeginDraw();
}
void C渲染控制::f开始(UINT a) {
	m二维->m上下文->SetTarget(m二维->ma位图目标[a].Get());
	m二维->m上下文->BeginDraw();
}
void C渲染控制::f清屏() {
	m二维->m渲染目标->Clear(m清屏颜色);
}
void C渲染控制::f结束() {
	m二维->m渲染目标->EndDraw();
}
void C渲染控制::f绘制图像(ID2D1Image *a) {
	m二维->m上下文->DrawImage(a);
}
void C渲染控制::f绘制图像(ID2D1Effect *a) {
	m二维->m上下文->DrawImage(a);
}
void C渲染控制::fs清屏颜色(const 数学::S颜色 &a颜色) {
	m清屏颜色 = C类型转换::f颜色(a颜色);
}
//==============================================================================
// 画图形
//==============================================================================
C画图形::~C画图形() {
	m画笔.Reset();
	m渲染目标.Reset();
}
void C画图形::f初始化(ID2D1RenderTarget *a渲染目标, const C坐标转换 &a坐标计算) {
	m渲染目标 = a渲染目标;
	m坐标计算 = &a坐标计算;
}
void C画图形::f初始化_纯色画笔(const 数学::S颜色 &a颜色) {
	const auto &v颜色 = C类型转换::f颜色(a颜色);
	ComPtr<ID2D1SolidColorBrush> v画笔;
	m渲染目标->CreateSolidColorBrush(v颜色, &v画笔);
	m画笔 = v画笔;
}
void C画图形::fs画笔(const ComPtr<ID2D1Brush> &a) {
	m画笔 = a;
}
void C画图形::fs线条宽度(float a) {
	m线条宽度 = a;
}
void C画图形::fs颜色(const 数学::S颜色 &a) {
	const D2D1_COLOR_F v颜色 = C类型转换::f颜色(a);
	ComPtr<ID2D1SolidColorBrush> v画笔;
	m画笔.As(&v画笔);
	v画笔->SetColor(v颜色);
}
void C画图形::fs透明度(float a) {
	m画笔->SetOpacity(a);
}
//画线条
void C画图形::f绘制点(const 数学::S向量2 &a) {
	m渲染目标->FillRectangle(m坐标计算->f矩形_中心半径(a, {0.5f, 0.5f}), m画笔.Get());
}
void C画图形::f绘制线条(const 数学::S线段2 &a线段) {
	m渲染目标->DrawLine(m坐标计算->f点(a线段.m点[0]), m坐标计算->f点(a线段.m点[1]), m画笔.Get(), m线条宽度);
}
void C画图形::f绘制矩形(const 数学::S矩形 &a矩形) {
	m渲染目标->DrawRectangle(m坐标计算->f矩形_中心半径(a矩形.m坐标, a矩形.m半尺寸), m画笔.Get());
}
void C画图形::f绘制旋转矩形(const 数学::S旋转矩形 &a矩形) {
	const auto v画笔 = m画笔.Get();
	if (a矩形.m方向 == 0 || a矩形.m方向 == 数学::cπ<float>) {
		m渲染目标->DrawRectangle(m坐标计算->f矩形_中心半径(a矩形.m坐标, a矩形.m半尺寸), v画笔, m线条宽度);
	} else {	// 任意角度
		数学::S向量2 v点[4] = {
			a矩形.m半尺寸,
			{a矩形.m半尺寸.x, -a矩形.m半尺寸.y},
			{-a矩形.m半尺寸.x, -a矩形.m半尺寸.y},
			{-a矩形.m半尺寸.x, a矩形.m半尺寸.y}
		};
		for (auto &v : v点) {
			v.fs旋转r(a矩形.m方向);
			v += a矩形.m坐标;
		}
		D2D1_POINT_2F m转换点[4] = {
			m坐标计算->f点(v点[0]),
			m坐标计算->f点(v点[1]),
			m坐标计算->f点(v点[2]),
			m坐标计算->f点(v点[3])
		};
		m渲染目标->DrawLine(m转换点[0], m转换点[1], v画笔, m线条宽度);
		m渲染目标->DrawLine(m转换点[1], m转换点[2], v画笔, m线条宽度);
		m渲染目标->DrawLine(m转换点[2], m转换点[3], v画笔, m线条宽度);
		m渲染目标->DrawLine(m转换点[3], m转换点[0], v画笔, m线条宽度);
	}
}
void C画图形::f绘制圆形(const 数学::S圆形 &a圆形) {
	m渲染目标->DrawEllipse(m坐标计算->f圆形(a圆形.m坐标, a圆形.m半径), m画笔.Get(), m线条宽度);
}
void C画图形::f绘制椭圆(const 数学::S椭圆 &a椭圆) {
	m渲染目标->DrawEllipse(m坐标计算->f椭圆(a椭圆.m坐标, a椭圆.m半径), m画笔.Get(), m线条宽度);
}
void C画图形::f绘制圆角矩形(const 数学::S圆角矩形 &a) {
	m渲染目标->DrawRoundedRectangle(m坐标计算->f圆角矩形(a.m坐标, a.m半尺寸, a.m角半径), m画笔.Get(), m线条宽度);
}
//填充
void C画图形::f填充矩形(const 数学::S矩形 &a) {
	m渲染目标->FillRectangle(m坐标计算->f矩形_中心半径(a.m坐标, a.m半尺寸), m画笔.Get());
}
void C画图形::f填充圆形(const 数学::S圆形 &a) {
	m渲染目标->FillEllipse(m坐标计算->f圆形(a.m坐标, a.m半径), m画笔.Get());
}
void C画图形::f填充椭圆(const 数学::S椭圆 &a) {
	m渲染目标->FillEllipse(m坐标计算->f椭圆(a.m坐标, a.m半径), m画笔.Get());
}
void C画图形::f填充圆角矩形(const 数学::S圆角矩形 &a) {
	m渲染目标->FillRoundedRectangle(m坐标计算->f圆角矩形(a.m坐标, a.m半尺寸, a.m角半径), m画笔.Get());
}
//==============================================================================
// 画文本
//==============================================================================
void C画文本::f初始化(ID2D1RenderTarget *p渲染目标, const C坐标转换 &a坐标计算) {
	m渲染目标 = p渲染目标;
	m坐标计算 = &a坐标计算;
	fs区域(0, 0);
}
void C画文本::f初始化_纯色画笔(const 数学::S颜色 &a颜色) {
	const auto &v颜色 = C类型转换::f颜色(a颜色);
	ComPtr<ID2D1SolidColorBrush> v画笔;
	m渲染目标->CreateSolidColorBrush(v颜色, &v画笔);
	m画笔 = v画笔;
}
void C画文本::fs格式(IDWriteTextFormat *a) {
	m格式 = a;
}
void C画文本::fs样式(C修改文本格式 &a) {
	fs格式(a.m格式);
}
void C画文本::fs画笔(const ComPtr<ID2D1Brush> &a) {
	m画笔 = a;
}
void C画文本::fs颜色(const 数学::S颜色 &a) {
	const D2D1_COLOR_F v颜色 = C类型转换::f颜色(a);
	ComPtr<ID2D1SolidColorBrush> v画笔;
	m画笔.As(&v画笔);
	v画笔->SetColor(v颜色);
}
void C画文本::fs透明度(float a) {
	m画笔->SetOpacity(a);
}
void C画文本::fs区域(const 数学::S向量2 &a) {
	m矩形 = m坐标计算->f矩形_点(a.x, a.y);
}
void C画文本::fs区域(const 数学::S向量2 &a坐标, const 数学::S向量2 &a半尺寸) {
	m矩形 = m坐标计算->f矩形_中心半径(a坐标, a半尺寸);
}
void C画文本::fs区域(float x, float y) {
	m矩形 = m坐标计算->f矩形_点(x, y);
}
void C画文本::fs区域(float l, float t, float r, float b) {
	m矩形 = m坐标计算->f矩形_左上右下(l, t, r, b);
}
void C画文本::fs区域(const 数学::S矩形 &a) {
	m矩形 = m坐标计算->f矩形_中心半径(a.m坐标, a.m半尺寸);
}
void C画文本::f绘制文本(const std::wstring_view &a文本) const {
	m渲染目标->DrawTextW(a文本.data(), a文本.size(), m格式.Get(), m矩形, m画笔.Get());
}
void C画文本::f绘制文本布局(IDWriteTextLayout *a布局) const {
	m渲染目标->DrawTextLayout({m矩形.left, m矩形.top}, a布局, m画笔.Get());
}
void C画文本::f绘制文本布局(IDWriteTextLayout *a布局, IDWriteTextRenderer *a文本渲染) const {
	assert(a文本渲染);
	ComPtr<ID2D1Layer> v层;
	m渲染目标->CreateLayer(&v层);
	m渲染目标->PushLayer({D2D1::InfiniteRect(), nullptr, D2D1_ANTIALIAS_MODE_ALIASED, D2D1::IdentityMatrix(), 1, m画笔.Get(), D2D1_LAYER_OPTIONS_NONE}, v层.Get());
	a布局->Draw(nullptr, a文本渲染, m矩形.left, m矩形.top);
	m渲染目标->PopLayer();
}
void C画文本::f绘制文本布局(C修改文本布局 &a布局) const {
	f绘制文本布局(a布局.m布局);
}
//==============================================================================
// 二维结构
//==============================================================================
D2D1_POINT_2F C类型转换::f点(const 数学::S向量2 &a) {
	return {a.x, a.y};
}
D2D1_COLOR_F C类型转换::f颜色(const 数学::S颜色 &a) {
	return {a.r, a.g, a.b, a.a};
}
std::vector<D2D1_GRADIENT_STOP> C类型转换::f渐变点(const std::vector<S渐变点> &a) {
	const int n = a.size();
	std::vector<D2D1_GRADIENT_STOP> v数组(n);
	for (int i = 0; i != n; ++i) {
		const S渐变点 &v0 = a[i];
		D2D1_GRADIENT_STOP &v1 = v数组[i];
		v1.position = v0.m位置;
		v1.color = C类型转换::f颜色(v0.m颜色);
	}
	return v数组;
}
//二维结构坐标
void C坐标转换::fs大小(const 数学::S向量2 &a窗口大小) {
	m窗口大小 = a窗口大小;
}
float C坐标转换::x(float X) const {
	return 数学::f窗口坐标x(X, m窗口大小.x);
}
float C坐标转换::y(float Y) const {
	return 数学::f窗口坐标y(Y, m窗口大小.y);
}
float C坐标转换::f百分比x(float X) const {
	return (X + 1) / 2 * m窗口大小.x;
}
float C坐标转换::f百分比y(float Y) const {
	return (1 - Y) / -2 * m窗口大小.y;
}
D2D1_POINT_2F C坐标转换::f点(const 数学::S向量2 &a) const {
	return {x(a.x), y(a.y)};
}
D2D_RECT_F C坐标转换::f矩形(const 数学::S矩形 &a) const {
	return f矩形_中心半径(a.m坐标, a.m半尺寸);
}
D2D_RECT_F C坐标转换::f矩形_窗口() const {
	return {0, 0, m窗口大小.x, m窗口大小.y};
}
D2D_RECT_F C坐标转换::f矩形_中心半径(const 数学::S向量2 &a, const 数学::S向量2 &r) const {
	return f矩形_左上右下(a.x-r.x, a.y+r.y, a.x+r.x, a.y-r.y);
}
D2D_RECT_F C坐标转换::f矩形_左上右下(const 数学::S向量2 &lt, const 数学::S向量2 &rb) const {
	return {x(lt.x), y(lt.y), x(rb.x), y(rb.y)};
}
D2D_RECT_F C坐标转换::f矩形_左上右下(float l, float t, float r, float b) const {
	return {x(l), y(t), x(r), y(b)};
}
D2D_RECT_F C坐标转换::f矩形_点(float X, float Y) const {
	return f矩形_左上右下(X, Y, X, Y);
}
D2D1_ELLIPSE C坐标转换::f圆形(const 数学::S圆形 &a) const {
	return {f点(a.m坐标), a.m半径, a.m半径};
}
D2D1_ELLIPSE C坐标转换::f圆形(const 数学::S向量2 &a, float r) const {
	return {f点(a), r, r};
}
D2D1_ELLIPSE C坐标转换::f椭圆(const 数学::S椭圆 &a) const {
	return f椭圆(a.m坐标, a.m半径);
}
D2D1_ELLIPSE C坐标转换::f椭圆(const 数学::S向量2 &a, const 数学::S向量2 &r) const {
	return {f点(a), r.x, r.y};
}
D2D1_ROUNDED_RECT C坐标转换::f圆角矩形(const 数学::S圆角矩形 &a) const {
	return {f矩形_中心半径(a.m坐标, a.m半尺寸), a.m角半径.x, a.m角半径.y};
}
D2D1_ROUNDED_RECT C坐标转换::f圆角矩形(const 数学::S向量2 &a, const 数学::S向量2 &r, const 数学::S向量2 &rr) const {
	return {f矩形_中心半径(a, r), rr.x, rr.y};
}
//==============================================================================
// 路径
//==============================================================================
C修改路径几何::C修改路径几何(ID2D1PathGeometry *a路径几何, const C坐标转换 &a坐标计算):
	m坐标计算(&a坐标计算) {
	assert(a路径几何);
	HRESULT hr = a路径几何->Open(&m几何槽);
	assert(SUCCEEDED(hr));
}
C修改路径几何::~C修改路径几何() {
	f结束();
}
void C修改路径几何::f结束() {
	if (m几何槽) {
		if (mw开始) {
			m几何槽->EndFigure(D2D1_FIGURE_END_OPEN);
		}
		m几何槽->Close();
		m几何槽 = nullptr;
	}
}
void C修改路径几何::f点(const 数学::S向量2 &a) {
	if (!mw开始) {
		m几何槽->BeginFigure(m坐标计算->f点(a), D2D1_FIGURE_BEGIN_HOLLOW);
		m当前点 = a;
		mw开始 = true;
	}
	if (m当前点 != a) {
		m几何槽->AddLine(m坐标计算->f点(a));
		m当前点 = a;
	}
}
void C修改路径几何::f直线(const 数学::S向量2 &a0, const 数学::S向量2 &a1) {
	f点(a0);
	f点(a1);
}
void C修改路径几何::f圆弧(const 数学::S向量2 &a圆心, float a半径, float a始, float a弧度, bool a顺时针) {
	assert(a弧度 <= 数学::c二π<float>);
	const float v方向符号 = a顺时针 ? -1 : 1;
	const 数学::S向量2 v开始点 = a圆心 + 数学::S向量2::fc方向r(a半径, a始);
	const 数学::S向量2 v结束点 = a圆心 + 数学::S向量2::fc方向r(a半径, a始 + v方向符号 * a弧度);
	const D2D1_SWEEP_DIRECTION v顺时针 = a顺时针 ? D2D1_SWEEP_DIRECTION_CLOCKWISE : D2D1_SWEEP_DIRECTION_COUNTER_CLOCKWISE;
	f点(v开始点);
	const D2D1_SIZE_F v半径 = D2D1::SizeF(a半径, a半径);
	if (a弧度 > 数学::cπ<float>) {	//弧度大于π时分割，避免弧度接近2π出现图形错乱问题
		const 数学::S向量2 v中点 = a圆心 + 数学::S向量2::fc方向r(a半径, a始 + a弧度 / 2 * v方向符号);
		m几何槽->AddArc(D2D1::ArcSegment(m坐标计算->f点(v中点), v半径, 0, v顺时针, D2D1_ARC_SIZE_SMALL));
	}
	m几何槽->AddArc(D2D1::ArcSegment(m坐标计算->f点(v结束点), v半径, 0, v顺时针, D2D1_ARC_SIZE_SMALL));
	m当前点 = v结束点;
}
void C修改路径几何::f连续直线(const std::vector<数学::S向量2> &a) {
	if (!mw开始) {
		m几何槽->BeginFigure(m坐标计算->f点(a[0]), D2D1_FIGURE_BEGIN_HOLLOW);
		mw开始 = true;
	} else {
		m几何槽->AddLine(m坐标计算->f点(a[0]));
	}
	const int n = a.size();
	for (int i = 1; i != n; ++i) {
		m几何槽->AddLine(m坐标计算->f点(a[i]));
	}
}
void C修改路径几何::f平滑曲线(const std::vector<数学::S向量2> &a) {
	assert(a.size() > 1);
	std::vector<D2D1_POINT_2F> v点;
	v点.reserve(a.size());
	for (const 数学::S向量2 &v : a) {
		v点.push_back(m坐标计算->f点(v));
	}
	const int n = v点.size();
	std::vector<D2D1_POINT_2F> v控制点1(n - 1);
	std::vector<D2D1_POINT_2F> v控制点2(n - 1);
	GetCurveControlPoints(v点, v控制点1, v控制点2);
	if (!mw开始) {
		m几何槽->BeginFigure(v点[0], D2D1_FIGURE_BEGIN_HOLLOW);
		mw开始 = true;
	} else {
		m几何槽->AddLine(v点[0]);
	}
	for (int i = 1; i != n; ++i) {
		m几何槽->AddBezier(D2D1::BezierSegment(v控制点1[i - 1], v控制点2[i - 1], v点[i]));
	}
}
void C修改路径几何::f闭合() {
	assert(mw开始);
	m几何槽->EndFigure(D2D1_FIGURE_END_CLOSED);
	mw开始 = false;
}
void C修改路径几何::f断开() {
	assert(mw开始);
	m几何槽->EndFigure(D2D1_FIGURE_END_OPEN);
	mw开始 = false;
}

//==============================================================================
// 文本工厂
//==============================================================================
C文本工厂::C文本工厂():
	m写字工厂(nullptr) {
	f初始化();
}
C文本工厂::~C文本工厂() {
	f销毁();
}
HRESULT C文本工厂::f初始化() {
	if (m写字工厂) {
		return S_OK;
	}
	HRESULT hr = DWriteCreateFactory(DWRITE_FACTORY_TYPE_SHARED, __uuidof(IDWriteFactory), &m写字工厂);
	assert(SUCCEEDED(hr));
	return hr;
}
void C文本工厂::f销毁() {
	m写字工厂.Reset();
}
tp文本格式 C文本工厂::fc文本格式(const S文本格式参数 &a格式) const {
	ComPtr<IDWriteTextFormat> v格式;
	HRESULT hr = m写字工厂->CreateTextFormat(a格式.m字体.c_str(), nullptr,
		a格式.m粗体, a格式.m斜体, a格式.m拉伸, a格式.m字号, a格式.m语言区域.c_str(), &v格式);
	assert(SUCCEEDED(hr));
	v格式->SetTextAlignment(a格式.m水平对齐);
	v格式->SetParagraphAlignment(a格式.m垂直对齐);
	v格式->SetWordWrapping(a格式.m自动换行);
	return v格式;
}
tp文本布局 C文本工厂::fc文本布局(const std::wstring_view &a文本, IDWriteTextFormat *a格式) const {
	if (a格式 == nullptr) {
		a格式 = C二维::g这->fg默认文本格式().Get();
	}
	ComPtr<IDWriteTextLayout> v布局;
	HRESULT hr = m写字工厂->CreateTextLayout(a文本.data(), a文本.size(), a格式, 0, 0, &v布局);
	return v布局;
}
tp文本布局 C文本工厂::fc文本布局(const std::wstring_view &a文本, const S文本格式参数 &a格式) const {
	tp文本格式 v格式 = fc文本格式(a格式);
	return fc文本布局(a文本, v格式.Get());
}
tp文本布局 C文本工厂::fc文本布局_小数(double a数字, int a小数位数, IDWriteTextFormat *a格式) {
	const float v字号 = a格式->GetFontSize();
	const float v小数字号 = v字号 * 0.6f;
	std::wstring v字符串 = std::to_wstring(a数字);
	v字符串 = 工具::C文本::f小数位数(v字符串, a小数位数);
	tp文本布局 v布局 = fc文本布局(v字符串, a格式);
	const size_t v小数点位置 = v字符串.find(L".");
	v布局->SetFontSize(v小数字号, {(UINT32)v小数点位置, (UINT32)(a小数位数 + 1)});
	return v布局;
}
C修改文本布局 C文本工厂::f修改文本布局(const tp文本布局 &a布局) {
	return C修改文本布局(a布局.Get());
}
//==============================================================================
// 文本格式结构
//==============================================================================
void S文本格式参数::fs字体(const std::wstring_view &a) {
	m字体 = std::wstring(a);
}
void S文本格式参数::fs语言区域(const std::wstring_view &a) {
	m语言区域 = std::wstring(a);
}
void S文本格式参数::fs字号(float a) {
	m字号 = a;
}
void S文本格式参数::fs粗体(int a) {
	m粗体 = C文本格式转换::f粗体(a);
}
void S文本格式参数::fs斜体(int a) {
	m斜体 = C文本格式转换::f斜体(a);
}
void S文本格式参数::fs拉伸(int a) {
	m拉伸 = C文本格式转换::f拉伸(a);
}
void S文本格式参数::fs自动换行(bool a) {
	m自动换行 = C文本格式转换::f自动换行(a);
}
void S文本格式参数::fs水平对齐(E文本水平对齐 a) {
	m水平对齐 = C文本格式转换::f水平对齐(a);
}
void S文本格式参数::fs垂直对齐(E文本垂直对齐 a) {
	m垂直对齐 = C文本格式转换::f垂直对齐(a);
}

//==============================================================================
// 文本格式
//==============================================================================
DWRITE_FONT_WEIGHT C文本格式转换::f粗体(int a) {
	static const DWRITE_FONT_WEIGHT ca粗体[] = {
		DWRITE_FONT_WEIGHT_THIN,
		DWRITE_FONT_WEIGHT_EXTRA_LIGHT,
		DWRITE_FONT_WEIGHT_LIGHT,
		DWRITE_FONT_WEIGHT_NORMAL,
		DWRITE_FONT_WEIGHT_MEDIUM,
		DWRITE_FONT_WEIGHT_DEMI_BOLD,
		DWRITE_FONT_WEIGHT_BOLD,
		DWRITE_FONT_WEIGHT_EXTRA_BOLD,
		DWRITE_FONT_WEIGHT_BLACK,
		DWRITE_FONT_WEIGHT_EXTRA_BLACK
	};
	if (a >= 0 && a <= 9) {
		return ca粗体[a];
	} else {
		__debugbreak();
		return DWRITE_FONT_WEIGHT_NORMAL;
	}
}
DWRITE_FONT_STYLE C文本格式转换::f斜体(int a) {
	static const DWRITE_FONT_STYLE ca斜体[] = {
		DWRITE_FONT_STYLE_NORMAL,
		DWRITE_FONT_STYLE_OBLIQUE,
		DWRITE_FONT_STYLE_ITALIC
	};
	if (a >= 0 && a <= 2) {
		return ca斜体[a];
	} else {
		__debugbreak();
		return DWRITE_FONT_STYLE_NORMAL;
	}
}
DWRITE_FONT_STRETCH C文本格式转换::f拉伸(int a) {
	static const DWRITE_FONT_STRETCH ca拉伸[] = {
		DWRITE_FONT_STRETCH_UNDEFINED,
		DWRITE_FONT_STRETCH_ULTRA_CONDENSED,
		DWRITE_FONT_STRETCH_EXTRA_CONDENSED,
		DWRITE_FONT_STRETCH_CONDENSED,
		DWRITE_FONT_STRETCH_SEMI_CONDENSED,
		DWRITE_FONT_STRETCH_NORMAL,
		DWRITE_FONT_STRETCH_MEDIUM,
		DWRITE_FONT_STRETCH_SEMI_EXPANDED,
		DWRITE_FONT_STRETCH_EXPANDED,
		DWRITE_FONT_STRETCH_EXTRA_EXPANDED,
		DWRITE_FONT_STRETCH_ULTRA_EXPANDED 
	};
	if (a >= 0 && a <= 9) {
		return ca拉伸[a];
	} else {
		__debugbreak();
		return DWRITE_FONT_STRETCH_NORMAL;
	}
}
DWRITE_TEXT_ALIGNMENT C文本格式转换::f水平对齐(E文本水平对齐 a) {
	switch (a) {
	case E文本水平对齐::e左:
		return DWRITE_TEXT_ALIGNMENT_LEADING;
	case E文本水平对齐::e右:
		return DWRITE_TEXT_ALIGNMENT_TRAILING;
	case E文本水平对齐::e中:
		return DWRITE_TEXT_ALIGNMENT_CENTER;
	default:
		throw;
	}
}
DWRITE_TEXT_ALIGNMENT C文本格式转换::f水平对齐(int a) {
	if (a < 0) {
		return DWRITE_TEXT_ALIGNMENT_LEADING;
	} else if (a > 0) {
		return DWRITE_TEXT_ALIGNMENT_TRAILING;
	} else {
		return DWRITE_TEXT_ALIGNMENT_CENTER;
	}
}
DWRITE_PARAGRAPH_ALIGNMENT C文本格式转换::f垂直对齐(E文本垂直对齐 a) {
	switch (a) {
	case E文本垂直对齐::e上:
		return DWRITE_PARAGRAPH_ALIGNMENT_NEAR;
	case E文本垂直对齐::e下:
		return DWRITE_PARAGRAPH_ALIGNMENT_FAR;
	case E文本垂直对齐::e中:
		return DWRITE_PARAGRAPH_ALIGNMENT_CENTER;
	default:
		throw;
	}
}
DWRITE_PARAGRAPH_ALIGNMENT C文本格式转换::f垂直对齐(int a) {
	if (a < 0) {
		return DWRITE_PARAGRAPH_ALIGNMENT_FAR;
	} else if (a > 0) {
		return DWRITE_PARAGRAPH_ALIGNMENT_NEAR;
	} else {
		return DWRITE_PARAGRAPH_ALIGNMENT_CENTER;
	}

}
DWRITE_TRIMMING C文本格式转换::f剪裁(int a) {
	DWRITE_TRIMMING v剪裁选项;
	ZeroMemory(&v剪裁选项, sizeof(v剪裁选项));
	switch (a) {
	case 0:
		v剪裁选项.granularity = DWRITE_TRIMMING_GRANULARITY_NONE;
		break;
	case 1:
		v剪裁选项.granularity = DWRITE_TRIMMING_GRANULARITY_CHARACTER;
		break;
	case 2:
		v剪裁选项.granularity = DWRITE_TRIMMING_GRANULARITY_WORD;
		break;
	}
	return v剪裁选项;
}
DWRITE_WORD_WRAPPING C文本格式转换::f自动换行(bool a) {
	if (a) {
		return DWRITE_WORD_WRAPPING_WRAP;
	} else {
		return DWRITE_WORD_WRAPPING_NO_WRAP;
	}
}
//==============================================================================
// 文本样式
//==============================================================================
C修改文本格式::C修改文本格式(IDWriteTextFormat *a): m格式(a) {}
C修改文本格式::~C修改文本格式() {
}
C修改文本格式 &C修改文本格式::fs水平对齐(E文本水平对齐 a) {
	m格式->SetTextAlignment(C文本格式转换::f水平对齐(a));
	return *this;
}
C修改文本格式 &C修改文本格式::fs垂直对齐(E文本垂直对齐 a) {
	m格式->SetParagraphAlignment(C文本格式转换::f垂直对齐(a));
	return *this;
}
C修改文本格式 &C修改文本格式::fs对齐(E文本水平对齐 a水平, E文本垂直对齐 a垂直) {
	fs水平对齐(a水平);
	fs垂直对齐(a垂直);
	return *this;
}
C修改文本格式 &C修改文本格式::fs剪裁(int a) {
	auto m剪裁选项 = C文本格式转换::f剪裁(a);
	m格式->SetTrimming(&m剪裁选项, nullptr);
	return *this;
}
//==============================================================================
// 文本样式
//==============================================================================
C修改文本布局::C修改文本布局(IDWriteTextLayout *a布局): 
	m布局(a布局) {
}
C修改文本布局::~C修改文本布局() {
}
C修改文本布局 &C修改文本布局::fs粗体(DWRITE_FONT_WEIGHT a, DWRITE_TEXT_RANGE a范围) {
	m布局->SetFontWeight(a, a范围);
	return *this;
}
C修改文本布局 &C修改文本布局::fs斜体(DWRITE_FONT_STYLE a, DWRITE_TEXT_RANGE a范围) {
	m布局->SetFontStyle(a, a范围);
	return *this;
}
C修改文本布局 &C修改文本布局::fs拉伸(DWRITE_FONT_STRETCH a, DWRITE_TEXT_RANGE a范围) {
	m布局->SetFontStretch(a, a范围);
	return *this;
}
F文本范围计算::F文本范围计算(UINT32 a): m文本长度(a) {}
DWRITE_TEXT_RANGE F文本范围计算::operator()(int a左, int a右) const {
	const int v文本长度 = (int)m文本长度;
	assert(a左 >= -v文本长度);
	assert(a左 < v文本长度);
	assert(a右 > -v文本长度);
	assert(a右 <= v文本长度);
	const int v左 = (a左 < 0) ? (v文本长度 + a左) : a左;
	const int v右 = (a右 <= 0) ? (v文本长度 + a右) : a右;
	const int v长度 = v右 - v左;
	assert(v长度 > 0);
	return {(UINT32)v左, (UINT32)v长度};
}
//==============================================================================
// 画文本
//==============================================================================
unsigned long C文本效果::AddRef() {
	++m引用计数;
	return m引用计数;
}
unsigned long C文本效果::Release() {
	--m引用计数;
	if (m引用计数 == 0) {
		delete this;
		return 0;
	} else {
		return m引用计数;
	}
}
HRESULT C文本效果::QueryInterface(IID const &riid, void **a) {
	if (__uuidof(IDWriteTextRenderer) == riid) {
		*a = this;
	} else if (__uuidof(IDWritePixelSnapping) == riid) {
		*a = this;
	} else if (__uuidof(IUnknown) == riid) {
		*a = this;
	} else {
		*a = nullptr;
		return E_FAIL;
	}
	this->AddRef();
	return S_OK;
}
HRESULT C文本效果::IsPixelSnappingDisabled(void*, BOOL*a) {
	*a = FALSE;
	return S_OK;
}
HRESULT C文本效果::GetCurrentTransform(void*, DWRITE_MATRIX *a矩阵) {
	m渲染目标->GetTransform(reinterpret_cast<D2D1_MATRIX_3X2_F*>(a矩阵));
	return S_OK;
}
HRESULT C文本效果::GetPixelsPerDip(void*, FLOAT *a) {
	float x, y;
	m渲染目标->GetDpi(&x, &y);
	*a = x / 96;
	return S_OK;
}
HRESULT C文本效果::DrawGlyphRun(void* a上下文, FLOAT x, FLOAT y, DWRITE_MEASURING_MODE a测量, DWRITE_GLYPH_RUN const* a字形, DWRITE_GLYPH_RUN_DESCRIPTION const* a字形描述, IUnknown* a效果) {
	HRESULT hr;
	ComPtr<ID2D1PathGeometry> v几何;
	hr = m二维工厂->CreatePathGeometry(&v几何);
	if (FAILED(hr)) {
		return hr;
	}
	ComPtr<ID2D1GeometrySink> v路径;
	v几何->Open(&v路径);
	a字形->fontFace->GetGlyphRunOutline(a字形->fontEmSize, a字形->glyphIndices, a字形->glyphAdvances, a字形->glyphOffsets, a字形->glyphCount, a字形->isSideways, a字形->bidiLevel%2, v路径.Get());
	v路径->Close();
	return f绘制几何(v几何.Get(), x, y);
}
HRESULT C文本效果::DrawUnderline(void* a上下文, FLOAT x, FLOAT y, DWRITE_UNDERLINE const* a下划线, IUnknown* a效果) {
	HRESULT hr;
	D2D1_RECT_F v矩形{0, a下划线->offset, a下划线->width, a下划线->offset + a下划线->thickness};
	ComPtr<ID2D1RectangleGeometry> v矩形几何;
	hr = m二维工厂->CreateRectangleGeometry(&v矩形, &v矩形几何);
	if (FAILED(hr)) {
		return hr;
	}
	return f绘制几何(v矩形几何.Get(), x, y);
}
HRESULT C文本效果::DrawStrikethrough(void* a上下文, FLOAT x, FLOAT y, DWRITE_STRIKETHROUGH const* a删除线,  IUnknown* a效果) {
	HRESULT hr;
	D2D1_RECT_F v矩形{0, a删除线->offset, a删除线->width, a删除线->offset + a删除线->thickness};
	ComPtr<ID2D1RectangleGeometry> v矩形几何;
	hr = m二维工厂->CreateRectangleGeometry(&v矩形, &v矩形几何);
	if (FAILED(hr)) {
		return hr;
	}
	return f绘制几何(v矩形几何.Get(), x, y);
}
HRESULT C文本效果::DrawInlineObject(void* a上下文, FLOAT x, FLOAT y, IDWriteInlineObject* inlineObject, BOOL ai旁边, BOOL ai反向, IUnknown* a效果) {
	return E_NOTIMPL;
}
HRESULT C文本效果::f绘制几何(ID2D1Geometry *a几何, float x, float y) {
	const D2D1_MATRIX_3X2_F v矩阵{1.0f, 0.0f, 0.0f, 1.0f, x, y};
	ComPtr<ID2D1TransformedGeometry> v变换几何;
	HRESULT hr = m二维工厂->CreateTransformedGeometry(a几何, &v矩阵, &v变换几何);
	if (FAILED(hr)) {
		return hr;
	}
	m渲染目标->DrawGeometry(v变换几何.Get(), m轮廓画笔.Get(), m轮廓宽度);
	m渲染目标->FillGeometry(v变换几何.Get(), m填充画笔.Get());
	return S_OK;
}
void C文本效果::fs填充颜色(const 数学::S颜色 &a) {
	m填充画笔->SetColor(C类型转换::f颜色(a));
}
void C文本效果::fs轮廓颜色(const 数学::S颜色 &a) {
	m轮廓画笔->SetColor(C类型转换::f颜色(a));
}
void C文本效果::fs轮廓宽度(float a) {
	//因为画线条位于轮廓居中位置，所以宽度乘2（把内轮廓也一起显示出来（虽然会被遮住））
	m轮廓宽度 = a * 2;
}
void C文本效果::fs透明度(float a) {
	m填充画笔->SetOpacity(a);
	m轮廓画笔->SetOpacity(a);
}
}	//namespace cflw::图形::d2d