#pragma once
//引用
#include <vector>
#include <string>
#include <string_view>
#include <d2d1_3.h>
#include <d2d1effectauthor_1.h>
#include <DWrite.h>
#include <dxgi1_4.h>
#include <wrl.h>
#include "cflw辅助.h"
#include "cflw数学.h"
#include "cflw数学_图形.h"
#include "cflw数学_平面几何.h"
//链接
#ifdef _WINDOWS
#pragma comment(lib, "dxguid.lib")
#pragma comment(lib, "d2d1.lib")
#pragma comment(lib, "dwrite.lib")
#endif
//
void GetCurveControlPoints(
	__in const std::vector<D2D1_POINT_2F>& knots,
	__out std::vector<D2D1_POINT_2F>& firstCtrlPt,
	__out std::vector<D2D1_POINT_2F>& secondCtrlPt);
HRESULT CreateBezierSpline(
	__in ID2D1Factory* pD2dFactory,
	__in const std::vector<D2D1_POINT_2F>& points,
	__out ID2D1PathGeometry** ppPathGeometry);
//命名空间
namespace cflw::图形::dx纹理 {
class I纹理;
}
namespace cflw::图形::d2d {
//外部
using Microsoft::WRL::ComPtr;
using tp渲染目标 = ComPtr<ID2D1RenderTarget>;
using tp画笔 = ComPtr<ID2D1Brush>;
using tp纯色画笔 = ComPtr<ID2D1SolidColorBrush>;
using tp位图 = ComPtr<ID2D1Bitmap>;
using tp位图画笔 = ComPtr<ID2D1BitmapBrush>;
using tp渐变点集 = ComPtr<ID2D1GradientStopCollection>;
using tp线性渐变画笔 = ComPtr<ID2D1LinearGradientBrush>;
using tp径向渐变画笔 = ComPtr<ID2D1RadialGradientBrush>;
using tp文本格式 = ComPtr<IDWriteTextFormat>;
using tp文本布局 = ComPtr<IDWriteTextLayout>;
using tp路径几何 = ComPtr<ID2D1PathGeometry>;
using tp几何槽 = ComPtr<ID2D1GeometrySink>;
using tp层 = ComPtr<ID2D1Layer>;
using tp效果 = ComPtr<ID2D1Effect>;
using t点2f = D2D1_POINT_2F;
using t矩形f = D2D_RECT_F;
using t椭圆 = D2D1_ELLIPSE;
using t颜色f = D2D1_COLOR_F;
using t圆角矩形 = D2D1_ROUNDED_RECT;
using t文本范围 = DWRITE_TEXT_RANGE;
using ta渐变点 = std::vector<D2D1_GRADIENT_STOP>;
//本文件
class C渲染控制;
class C画图形;
class C画文本;
class C类型转换;
class C修改文本格式;
class C修改文本布局;
class C中文字号格式;
class C坐标转换;
class C修改路径几何;
class C文本工厂;
class C文本效果;
using tp画图形 = std::shared_ptr<C画图形>;
using tp画文本 = std::shared_ptr<C画文本>;
using tp坐标转换 = std::shared_ptr<C坐标转换>;
using tp文本效果 = ComPtr<C文本效果>;
//枚举
enum class E文本水平对齐 {
	e左,
	e右,
	e中,
};
enum class E文本垂直对齐 {
	e上,
	e下,
	e中,
};
//函数
数学::S向量2 f计算每英寸点数(float 缩放);
//==============================================================================
// 结构
//==============================================================================
struct S渐变点 {
	float m位置;	//m位置∈[0,1]
	数学::S颜色 m颜色;
};
//==============================================================================
// 二维引擎
//==============================================================================
class C二维 {
	friend class C渲染控制;
public:
	static C二维 *g这;
//函数
	C二维();
	~C二维();
	HRESULT f初始化(HWND, float 缩放);	//废弃.注意:此函数不创建上下文
	HRESULT f初始化(IDXGISwapChain*, float 缩放);	//废弃.注意:此函数不创建上下文
	HRESULT f初始化_工厂();
	HRESULT f初始化_设备(IDXGIDevice *);
	void f初始化_窗口大小(float x, float y);
	void f初始化_渲染目标(ID2D1RenderTarget*);
	HRESULT f初始化_单个位图(IDXGISwapChain *, float 缩放);
	//template<std::ranges::Range t范围> HRESULT f初始化_多个位图(const t范围 &, float 缩放 = 0);
	template<typename t范围> HRESULT f初始化_多个位图(const t范围 &, float 缩放);
	void f销毁();
	void fs缩放(float = 1);
	//画图对象
	std::shared_ptr<C画图形> fc画图形(const ComPtr<ID2D1Brush> & = nullptr, float 宽度 = 1) const;
	std::shared_ptr<C画文本> fc画文本(const ComPtr<ID2D1Brush> & = nullptr);
	ComPtr<ID2D1SolidColorBrush> fc纯色画笔(const 数学::S颜色 &) const;
	ComPtr<ID2D1Bitmap> fc位图(const ComPtr<IWICBitmapSource> &);
	ComPtr<ID2D1Bitmap> fc位图(const dx纹理::I纹理 &);
	ComPtr<ID2D1BitmapBrush> fc位图画笔(const ComPtr<ID2D1Bitmap> &);
	ComPtr<ID2D1GradientStopCollection> fc渐变点集(const std::vector<S渐变点> &) const;
	ComPtr<ID2D1LinearGradientBrush> fc线性渐变画笔(const std::vector<S渐变点> &) const;
	ComPtr<ID2D1RadialGradientBrush> fc径向渐变画笔(const std::vector<S渐变点> &) const;
	ComPtr<ID2D1PathGeometry> fc路径几何() const;
	ComPtr<ID2D1Layer> fc层() const;
	C修改路径几何 f修改路径几何(const ComPtr<ID2D1PathGeometry> &) const;
	ComPtr<C文本效果> fc文本效果(const 数学::S颜色 &描边 = 数学::S颜色::c白, const 数学::S颜色 &填充 = 数学::S颜色::c黑) const;
	ComPtr<ID2D1Effect> fc效果(const GUID &);
	//其它对象
	ComPtr<ID2D1Factory3> fg二维工厂();
	ComPtr<ID2D1RenderTarget> fg渲染目标() const;
	C坐标转换 &fg坐标计算() const;
	C文本工厂 &fg文本工厂();
	ComPtr<IDWriteTextFormat> fg默认文本格式();
	C渲染控制 &fg渲染控制();
	ComPtr<ID2D1DeviceContext> fg上下文() const;
private:
	数学::S向量2 m窗口大小;
	ComPtr<ID2D1Factory3> m二维工厂;
	ComPtr<ID2D1Device1> m设备;
	ComPtr<ID2D1DeviceContext> m上下文;
	std::vector<ComPtr<ID2D1Bitmap1>> ma位图目标;
	ComPtr<ID2D1RenderTarget> m渲染目标;	//主要目标
	std::unique_ptr<C坐标转换> m坐标计算;
	std::unique_ptr<C文本工厂> m文本工厂;
	ComPtr<IDWriteTextFormat> m默认文本格式;
	std::unique_ptr<C渲染控制> m渲染控制;
};
class C渲染控制 {
public:
	void f开始();
	void f开始(UINT);	//使用位图目标
	void f清屏();
	void f结束();
	//画
	void f绘制图像(ID2D1Image *);
	void f绘制图像(ID2D1Effect *);
	//属性
	void fs清屏颜色(const 数学::S颜色 &);
public:
	C二维 *m二维 = nullptr;
	D2D1_COLOR_F m清屏颜色 = D2D1::ColorF(D2D1::ColorF::Black);
};
//==============================================================================
// 各种画
//==============================================================================
class C画图形 {
public:
	~C画图形();
	void f初始化(ID2D1RenderTarget *, const C坐标转换 &);
	void f初始化_纯色画笔(const 数学::S颜色 &颜色);
	//设置
	void fs画笔(const ComPtr<ID2D1Brush> &);
	void fs线条宽度(float);
	void fs颜色(const 数学::S颜色 &);
	void fs透明度(float);
	//描线
	void f绘制点(const 数学::S向量2 &);
	void f绘制线条(const 数学::S线段2 &);
	void f绘制矩形(const 数学::S矩形 &);
	void f绘制旋转矩形(const 数学::S旋转矩形 &);
	void f绘制圆形(const 数学::S圆形 &);
	void f绘制椭圆(const 数学::S椭圆 &);
	void f绘制圆角矩形(const 数学::S圆角矩形 &);
	void f绘制十字(const 数学::S圆形 &);
	//填充
	void f填充矩形(const 数学::S矩形 &);
	void f填充圆形(const 数学::S圆形 &);
	void f填充椭圆(const 数学::S椭圆 &);
	void f填充圆角矩形(const 数学::S圆角矩形 &);
public:
	ComPtr<ID2D1RenderTarget> m渲染目标;
	ComPtr<ID2D1Brush> m画笔;
	const C坐标转换 *m坐标计算;
	float m线条宽度 = 1;
};
class C画文本 {
public:
	void f初始化(ID2D1RenderTarget *, const C坐标转换 &);
	void f初始化_纯色画笔(const 数学::S颜色 &);
	//设置
	void fs格式(IDWriteTextFormat *);
	void fs样式(C修改文本格式 &);
	void fs画笔(const ComPtr<ID2D1Brush> &);
	void fs颜色(const 数学::S颜色 &);
	void fs透明度(float);
	void fs区域(const 数学::S向量2 &);
	void fs区域(const 数学::S向量2 &, const 数学::S向量2 &);
	void fs区域(float, float);
	void fs区域(float, float, float, float);
	void fs区域(const 数学::S矩形 &);
	//画
	void f绘制文本(const std::wstring_view &) const;
	void f绘制文本布局(IDWriteTextLayout *) const;
	void f绘制文本布局(IDWriteTextLayout *, IDWriteTextRenderer *) const;
	void f绘制文本布局(C修改文本布局 &) const;
public:
	ComPtr<ID2D1RenderTarget> m渲染目标;
	ComPtr<ID2D1Brush> m画笔;
	ComPtr<IDWriteTextFormat> m格式;
	const C坐标转换 *m坐标计算;
	D2D1_RECT_F m矩形;
};
//==============================================================================
// 二维结构计算&转换
//==============================================================================
class C类型转换 {
public:
	static D2D1_COLOR_F f颜色(const 数学::S颜色 &);
	static D2D1_POINT_2F f点(const 数学::S向量2 &);
	static std::vector<D2D1_GRADIENT_STOP> f渐变点(const std::vector<S渐变点> &);
};
class C坐标转换 {
public:	//输入直角坐标然后转换成窗口坐标
	void fs大小(const 数学::S向量2 &);
	float x(float) const;
	float y(float) const;
	float f百分比x(float) const;
	float f百分比y(float) const;
	D2D1_POINT_2F f点(const 数学::S向量2 &) const;
	D2D_RECT_F f矩形(const 数学::S矩形 &) const;
	D2D_RECT_F f矩形_窗口() const;
	D2D_RECT_F f矩形_中心半径(const 数学::S向量2 &, const 数学::S向量2 &) const;
	D2D_RECT_F f矩形_左上右下(const 数学::S向量2 &, const 数学::S向量2 &) const;
	D2D_RECT_F f矩形_左上右下(float, float, float, float) const;
	D2D_RECT_F f矩形_点(float, float) const;
	D2D1_ELLIPSE f圆形(const 数学::S向量2 &, float) const;
	D2D1_ELLIPSE f圆形(const 数学::S圆形 &) const;
	D2D1_ELLIPSE f椭圆(const 数学::S向量2 &, const 数学::S向量2 &) const;
	D2D1_ELLIPSE f椭圆(const 数学::S椭圆 &) const;
	D2D1_ROUNDED_RECT f圆角矩形(const 数学::S圆角矩形 &) const;
	D2D1_ROUNDED_RECT f圆角矩形(const 数学::S向量2 &, const 数学::S向量2 &, const 数学::S向量2 &) const;
private:
	数学::S向量2 m窗口大小;
};
//==============================================================================
// 路径
//==============================================================================
class C修改路径几何 {
public:
	C修改路径几何(ID2D1PathGeometry *, const C坐标转换 &);
	~C修改路径几何();
	void f点(const 数学::S向量2 &);
	void f直线(const 数学::S向量2 &a点0, const 数学::S向量2 &a点1);
	void f圆弧(const 数学::S向量2 &圆心, float 半径, float 开始, float 弧度, bool 顺时针 = true);
	void f连续直线(const std::vector<数学::S向量2> &);
	void f平滑曲线(const std::vector<数学::S向量2> &);
	void f闭合();
	void f断开();
	void f结束();
private:
	ComPtr<ID2D1GeometrySink> m几何槽;
	const C坐标转换 *m坐标计算;
	数学::S向量2 m当前点;
	bool mi开始 = false;
};
//==============================================================================
// 文本工厂
//==============================================================================
struct S文本格式参数 {
	std::wstring m字体 = L"微软雅黑";
	std::wstring m语言区域 = L"zh-cn";
	float m字号 = 36;
	DWRITE_FONT_WEIGHT m粗体 = DWRITE_FONT_WEIGHT_REGULAR;
	DWRITE_FONT_STYLE m斜体 = DWRITE_FONT_STYLE_NORMAL;
	DWRITE_FONT_STRETCH m拉伸 = DWRITE_FONT_STRETCH_NORMAL;
	DWRITE_TEXT_ALIGNMENT m水平对齐 = DWRITE_TEXT_ALIGNMENT_LEADING;//默认左对齐
	DWRITE_PARAGRAPH_ALIGNMENT m垂直对齐 = DWRITE_PARAGRAPH_ALIGNMENT_CENTER;
	DWRITE_WORD_WRAPPING m自动换行 = DWRITE_WORD_WRAPPING_NO_WRAP;
	void fs字体(const std::wstring_view &);
	void fs语言区域(const std::wstring_view &);
	void fs字号(float);
	void fs粗体(bool);
	void fs粗体(int);
	void fs斜体(bool);
	void fs斜体(int);
	void fs拉伸(int);
	void fs自动换行(bool);
	void fs水平对齐(E文本水平对齐);
	void fs垂直对齐(E文本垂直对齐);
};
class C文本工厂 {
public:
//构造函数
	C文本工厂();
	~C文本工厂();
//函数
	HRESULT f初始化();
	void f销毁();
	tp文本格式 fc文本格式(const S文本格式参数 &) const;
	tp文本布局 fc文本布局(const std::wstring_view &文本, IDWriteTextFormat *格式 = nullptr) const;
	tp文本布局 fc文本布局(const std::wstring_view &文本, const S文本格式参数 &格式) const;
	tp文本布局 fc文本布局_小数(double, int 小数位数, IDWriteTextFormat *格式);
	C修改文本布局 f修改文本布局(const tp文本布局 &);
public:
	ComPtr<IDWriteFactory> m写字工厂;
};
class C文本格式转换 {
public:
	static DWRITE_FONT_WEIGHT f粗体(bool);
	static DWRITE_FONT_WEIGHT f粗体(int);	//0~9
	static DWRITE_FONT_STYLE f斜体(bool);
	static DWRITE_FONT_STYLE f斜体(int);	//0~2
	static DWRITE_FONT_STRETCH f拉伸(int);	//0~9
	static DWRITE_TEXT_ALIGNMENT f水平对齐(E文本水平对齐);
	static DWRITE_TEXT_ALIGNMENT f水平对齐(int);
	static DWRITE_PARAGRAPH_ALIGNMENT f垂直对齐(E文本垂直对齐);
	static DWRITE_PARAGRAPH_ALIGNMENT f垂直对齐(int);
	static DWRITE_TRIMMING f剪裁(int);	//0~2
	static DWRITE_WORD_WRAPPING f自动换行(bool);
};
//==============================================================================
// 中文字号
//==============================================================================
enum E中文字号 {
	e大特号,e特号,
	e初号, e小初号,
	e大一号, e一号, e小一号,
	e二号, e小二号,
	e三号, e小三号,
	e四号, e小四号,
	e五号, e小五号,
	e六号, e小六号,
	e七号, e小七号,
	e八号,
};
constexpr float ca中文字号[] = {
	63, 54,	//特号
	42, 36,	//初号
	31.5, 26, 24,	//一号
	22, 18,	//二号
	16, 15,	//三号
	14, 12,	//四号
	10.5, 9,	//五号
	7.5, 6.5,	//六号
	5.5, 5.25,	//七号
	5	//八号
};
//==============================================================================
// 文本样式&文本布局
//==============================================================================
class C修改文本格式 {
public:
	IDWriteTextFormat *m格式;
	C修改文本格式(IDWriteTextFormat *);
	~C修改文本格式();
	C修改文本格式 &fs水平对齐(E文本水平对齐 = E文本水平对齐::e左);
	C修改文本格式 &fs垂直对齐(E文本垂直对齐 = E文本垂直对齐::e上);
	C修改文本格式 &fs对齐(E文本水平对齐 = E文本水平对齐::e左, E文本垂直对齐 = E文本垂直对齐::e上);
	C修改文本格式 &fs剪裁(int = 0);
};
class C修改文本布局 {
public:
	IDWriteTextLayout *m布局;
	C修改文本布局(IDWriteTextLayout *);
	~C修改文本布局();
	C修改文本布局 &fs粗体(DWRITE_FONT_WEIGHT, DWRITE_TEXT_RANGE = {0, 0});
	C修改文本布局 &fs斜体(DWRITE_FONT_STYLE, DWRITE_TEXT_RANGE = {0, 0});
	C修改文本布局 &fs拉伸(DWRITE_FONT_STRETCH, DWRITE_TEXT_RANGE = {0, 0});
};
class F文本范围计算 {
public:
	UINT32 m文本长度;
	F文本范围计算(UINT32);
	DWRITE_TEXT_RANGE operator()(int = 0, int = 0) const;
};
//==============================================================================
// 画文本
//==============================================================================
class C文本效果 : public IDWriteTextRenderer {
	friend C二维;
	C文本效果() = default;
public:
	//IUnknown
	unsigned long __stdcall AddRef() override;
	unsigned long __stdcall Release() override;
	HRESULT __stdcall QueryInterface(IID const&,void**) override;
	//IDWriteTextRenderer
	HRESULT __stdcall IsPixelSnappingDisabled(void*, BOOL*) override;
	HRESULT __stdcall GetCurrentTransform(void*, DWRITE_MATRIX*) override;
	HRESULT __stdcall GetPixelsPerDip(void*, FLOAT*) override;
	HRESULT __stdcall DrawGlyphRun(void*, FLOAT, FLOAT, DWRITE_MEASURING_MODE, DWRITE_GLYPH_RUN const*, DWRITE_GLYPH_RUN_DESCRIPTION const*, IUnknown*) override;
	HRESULT __stdcall DrawUnderline(void*, FLOAT, FLOAT, DWRITE_UNDERLINE const*, IUnknown*) override;
	HRESULT __stdcall DrawStrikethrough(void*, FLOAT, FLOAT, DWRITE_STRIKETHROUGH const*,  IUnknown*) override;
	HRESULT __stdcall DrawInlineObject(void*, FLOAT, FLOAT, IDWriteInlineObject*, BOOL, BOOL, IUnknown*) override;
	//画文本
	void fs填充颜色(const 数学::S颜色 &);
	void fs轮廓颜色(const 数学::S颜色 &);
	void fs轮廓宽度(float);
	void fs透明度(float);
private:
	HRESULT f绘制几何(ID2D1Geometry *, float x, float y);
	ComPtr<ID2D1Factory> m二维工厂;
	ComPtr<ID2D1RenderTarget> m渲染目标;
	ComPtr<ID2D1SolidColorBrush> m填充画笔;
	ComPtr<ID2D1SolidColorBrush> m轮廓画笔;
	float m轮廓宽度 = 2;
	unsigned long m引用计数 = 1;
};
//==============================================================================
// 着色器效果
//==============================================================================
//class C像素效果 : public ID2D1EffectImpl, public ID2D1DrawTransform {
//public:
//	static GUID f生成着色器标识(size_t);
//	static GUID f生成类标识(size_t);
//	C像素效果() = default;
//	//IUnknown
//	unsigned long __stdcall AddRef() override;
//	unsigned long __stdcall Release() override;
//	HRESULT __stdcall QueryInterface(IID const &, void **) override;
//	//ID2D1EffectImpl
//	HRESULT __stdcall Initialize(ID2D1EffectContext *pContextInternal, ID2D1TransformGraph *pTransformGraph) override;
//	HRESULT __stdcall PrepareForRender(D2D1_CHANGE_TYPE changeType) override;
//	HRESULT __stdcall SetGraph(ID2D1TransformGraph *pGraph) override;
//	//ID2D1DrawTransform
//	HRESULT __stdcall SetDrawInfo(ID2D1DrawInfo *pRenderInfo) override;
//	//ID2D1Transform
//	HRESULT __stdcall MapOutputRectToInputRects( const D2D1_RECT_L *pOutputRect, D2D1_RECT_L *pInputRects, UINT32 inputRectCount) const override;
//	HRESULT __stdcall MapInputRectsToOutputRect(const D2D1_RECT_L *pInputRects, const D2D1_RECT_L *pInputOpaqueSubRects, UINT32 inputRectCount, D2D1_RECT_L *pOutputRect, D2D1_RECT_L *pOutputOpaqueSubRect) override;
//	HRESULT __stdcall MapInvalidRect(UINT32 inputIndex, D2D1_RECT_L invalidInputRect, D2D1_RECT_L *pInvalidOutputRect) const override;
//	// Declare ID2D1TransformNode implementation methods.
//	UINT32 __stdcall GetInputCount() const override;
//private:
//	ComPtr<ID2D1DrawInfo> m画信息;
//	ComPtr<ID2D1EffectContext> m效果上下文;
//};
}	//namespace cflw::图形::d2d
#include "cflw图形_d2d.inl"