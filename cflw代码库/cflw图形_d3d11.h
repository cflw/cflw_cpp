#pragma once
//链接
#ifdef _WINDOWS
#pragma comment(lib, "dxguid.lib")
#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "d3d11.lib")
#endif
//包括头文件
#include <vector>
#include <string>
#include <map>
#include <memory>
#include <bitset>
#include <variant>
#include <span>
#include <d3d11.h>
#include <wrl.h>
#include "cflw辅助.h"
#include "cflw工具_运算.h"
#include "cflw数学.h"
#include "cflw数学_图形.h"
#include "cflw图形_dx纹理.h"
//命名空间
namespace cflw::图形::d3d11 {
namespace 纹理 = dx纹理;
//=============================================================================
// 前置声明
//=============================================================================
using Microsoft::WRL::ComPtr;
using tp设备 = ComPtr<ID3D11Device>;
using tp设备上下文 = ComPtr<ID3D11DeviceContext>;
using tp顶点着色器 = ComPtr<ID3D11VertexShader>;
using tp像素着色器 = ComPtr<ID3D11PixelShader>;
using tp几何着色器 = ComPtr<ID3D11GeometryShader>;
using tp外壳着色器 = ComPtr<ID3D11HullShader>;
using tp域着色器 = ComPtr<ID3D11DomainShader>;
using tp计算着色器 = ComPtr<ID3D11ComputeShader>;
using tp缓冲 = ComPtr<ID3D11Buffer>;
using tp输入布局 = ComPtr<ID3D11InputLayout>;
using tp纹理 = ComPtr<ID3D11ShaderResourceView>;
using tp光栅化 = ComPtr<ID3D11RasterizerState>;
using tp混和 = ComPtr<ID3D11BlendState>;
using tp采样器 = ComPtr<ID3D11SamplerState>;
using tp深度模板 = ComPtr<ID3D11DepthStencilState>;
using tp纹理2 = ComPtr<ID3D11Texture2D>;
//本文件
class C渲染控制;
class C渲染状态;
class C顶点格式;
class C纹理工厂;
class C缓冲工厂;
class C图形管线;
struct S图形管线参数;
using tp图形管线 = std::shared_ptr<C图形管线>;
using t索引 = uint16_t;
//==============================================================================
// 常量
//==============================================================================
enum E图元拓扑 {
	e列表点 = D3D11_PRIMITIVE_TOPOLOGY_POINTLIST,
	e列表线段 = D3D11_PRIMITIVE_TOPOLOGY_LINELIST,
	e连续线段 = D3D11_PRIMITIVE_TOPOLOGY_LINESTRIP,
	e列表三角形 = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST,
	e连续三角形 = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP,
	e邻接列表线段 = D3D11_PRIMITIVE_TOPOLOGY_LINELIST_ADJ,
	e邻接连续线段 = D3D11_PRIMITIVE_TOPOLOGY_LINESTRIP_ADJ,
	e邻接列表三角形 = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST_ADJ,
	e邻接连接三角形 = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP_ADJ,
	e补丁1 = D3D11_PRIMITIVE_TOPOLOGY_1_CONTROL_POINT_PATCHLIST,
	e补丁2 = D3D11_PRIMITIVE_TOPOLOGY_2_CONTROL_POINT_PATCHLIST,
	e补丁3 = D3D11_PRIMITIVE_TOPOLOGY_3_CONTROL_POINT_PATCHLIST,
	e补丁4 = D3D11_PRIMITIVE_TOPOLOGY_4_CONTROL_POINT_PATCHLIST,
	e补丁5 = D3D11_PRIMITIVE_TOPOLOGY_5_CONTROL_POINT_PATCHLIST,
	e补丁6 = D3D11_PRIMITIVE_TOPOLOGY_6_CONTROL_POINT_PATCHLIST,
	e补丁7 = D3D11_PRIMITIVE_TOPOLOGY_7_CONTROL_POINT_PATCHLIST,
	e补丁8 = D3D11_PRIMITIVE_TOPOLOGY_8_CONTROL_POINT_PATCHLIST,
	e补丁9 = D3D11_PRIMITIVE_TOPOLOGY_9_CONTROL_POINT_PATCHLIST,
	e补丁10 = D3D11_PRIMITIVE_TOPOLOGY_10_CONTROL_POINT_PATCHLIST,
	e补丁11 = D3D11_PRIMITIVE_TOPOLOGY_11_CONTROL_POINT_PATCHLIST,
	e补丁12 = D3D11_PRIMITIVE_TOPOLOGY_12_CONTROL_POINT_PATCHLIST,
	e补丁13 = D3D11_PRIMITIVE_TOPOLOGY_13_CONTROL_POINT_PATCHLIST,
	e补丁14 = D3D11_PRIMITIVE_TOPOLOGY_14_CONTROL_POINT_PATCHLIST,
	e补丁15 = D3D11_PRIMITIVE_TOPOLOGY_15_CONTROL_POINT_PATCHLIST,
	e补丁16 = D3D11_PRIMITIVE_TOPOLOGY_16_CONTROL_POINT_PATCHLIST,
	e补丁17 = D3D11_PRIMITIVE_TOPOLOGY_17_CONTROL_POINT_PATCHLIST,
	e补丁18 = D3D11_PRIMITIVE_TOPOLOGY_18_CONTROL_POINT_PATCHLIST,
	e补丁19 = D3D11_PRIMITIVE_TOPOLOGY_19_CONTROL_POINT_PATCHLIST,
	e补丁20 = D3D11_PRIMITIVE_TOPOLOGY_20_CONTROL_POINT_PATCHLIST,
	e补丁21 = D3D11_PRIMITIVE_TOPOLOGY_21_CONTROL_POINT_PATCHLIST,
	e补丁22 = D3D11_PRIMITIVE_TOPOLOGY_22_CONTROL_POINT_PATCHLIST,
	e补丁23 = D3D11_PRIMITIVE_TOPOLOGY_23_CONTROL_POINT_PATCHLIST,
	e补丁24 = D3D11_PRIMITIVE_TOPOLOGY_24_CONTROL_POINT_PATCHLIST,
	e补丁25 = D3D11_PRIMITIVE_TOPOLOGY_25_CONTROL_POINT_PATCHLIST,
	e补丁26 = D3D11_PRIMITIVE_TOPOLOGY_26_CONTROL_POINT_PATCHLIST,
	e补丁27 = D3D11_PRIMITIVE_TOPOLOGY_27_CONTROL_POINT_PATCHLIST,
	e补丁28 = D3D11_PRIMITIVE_TOPOLOGY_28_CONTROL_POINT_PATCHLIST,
	e补丁29 = D3D11_PRIMITIVE_TOPOLOGY_29_CONTROL_POINT_PATCHLIST,
	e补丁30 = D3D11_PRIMITIVE_TOPOLOGY_30_CONTROL_POINT_PATCHLIST,
	e补丁31 = D3D11_PRIMITIVE_TOPOLOGY_31_CONTROL_POINT_PATCHLIST,
	e补丁32 = D3D11_PRIMITIVE_TOPOLOGY_32_CONTROL_POINT_PATCHLIST,
};
enum E资源用法 {
	e默认 = D3D11_USAGE_DEFAULT,
	e只读 = D3D11_USAGE_IMMUTABLE,
	e动态 = D3D11_USAGE_DYNAMIC,
	e暂存 = D3D11_USAGE_STAGING
};
enum E缓冲 {
	e顶点 = D3D11_BIND_VERTEX_BUFFER,
	e索引 = D3D11_BIND_INDEX_BUFFER,
	e常量 = D3D11_BIND_CONSTANT_BUFFER,
	e着色器 = D3D11_BIND_SHADER_RESOURCE
};
constexpr D3D11_COMPARISON_FUNC ft比较(工具::E比较 a比较) {
	switch (a比较) {
	case 工具::E比较::e永不:
		return D3D11_COMPARISON_NEVER;
	case 工具::E比较::e小于:
		return D3D11_COMPARISON_LESS;
	case 工具::E比较::e等于:
		return D3D11_COMPARISON_EQUAL;
	case 工具::E比较::e小于等于:
		return D3D11_COMPARISON_LESS_EQUAL;
	case 工具::E比较::e大于:
		return D3D11_COMPARISON_GREATER;
	case 工具::E比较::e不等于:
		return D3D11_COMPARISON_NOT_EQUAL;
	case 工具::E比较::e大于等于:
		return D3D11_COMPARISON_GREATER_EQUAL;
	case 工具::E比较::e总是:
		return D3D11_COMPARISON_ALWAYS;
	default:
		return D3D11_COMPARISON_NEVER;
	}
}
constexpr DXGI_FORMAT c索引格式 = DXGI_FORMAT_R16_UINT;
constexpr DXGI_FORMAT c交换链格式 = DXGI_FORMAT_R8G8B8A8_UNORM;
constexpr DXGI_FORMAT c深度模板格式 = DXGI_FORMAT_D32_FLOAT_S8X24_UINT;
constexpr float c清屏深度l = 1;
constexpr float c清屏深度r = 0;
constexpr D3D11_RASTERIZER_DESC c默认光栅化 = {D3D11_FILL_SOLID, D3D11_CULL_BACK, FALSE, D3D11_DEFAULT_DEPTH_BIAS, D3D11_DEFAULT_DEPTH_BIAS_CLAMP, D3D11_DEFAULT_SLOPE_SCALED_DEPTH_BIAS, TRUE, FALSE, true, FALSE};
constexpr D3D11_BLEND_DESC c默认混合 = {FALSE, FALSE, {
	{FALSE, D3D11_BLEND_ONE, D3D11_BLEND_ZERO, D3D11_BLEND_OP_ADD, D3D11_BLEND_ONE, D3D11_BLEND_ZERO, D3D11_BLEND_OP_ADD, D3D11_COLOR_WRITE_ENABLE_ALL}, {0}, {0}, {0}, {0}, {0}, {0}, {0}
}};
constexpr D3D11_DEPTH_STENCIL_DESC c默认深度模板 = {FALSE, D3D11_DEPTH_WRITE_MASK_ALL, D3D11_COMPARISON_LESS, FALSE, D3D11_DEFAULT_STENCIL_READ_MASK, D3D11_DEFAULT_STENCIL_WRITE_MASK, {D3D11_STENCIL_OP_KEEP, D3D11_STENCIL_OP_KEEP, D3D11_STENCIL_OP_KEEP, D3D11_COMPARISON_ALWAYS}, {D3D11_STENCIL_OP_KEEP, D3D11_STENCIL_OP_KEEP, D3D11_STENCIL_OP_KEEP, D3D11_COMPARISON_ALWAYS}};
//==============================================================================
// 结构
//==============================================================================
struct S图形管线参数 {
	const C顶点格式 *m顶点格式 = nullptr;
	std::span<const std::byte> m顶点着色器, m像素着色器, m几何着色器, m外壳着色器, m域着色器;	
	std::variant<D3D11_RASTERIZER_DESC, ID3D11RasterizerState*> m光栅化 = nullptr;
	std::variant<D3D11_BLEND_DESC, ID3D11BlendState*> m混合 = nullptr;
	std::variant<D3D11_DEPTH_STENCIL_DESC, ID3D11DepthStencilState*> m深度模板 = nullptr;
	void fs输入布局(const C顶点格式 &);
	void fs顶点着色器(const std::span<const std::byte> &);
	void fs像素着色器(const std::span<const std::byte> &);
	void fs几何着色器(const std::span<const std::byte> &);
	void fs外壳着色器(const std::span<const std::byte> &);
	void fs域着色器(const std::span<const std::byte> &);
	void fs光栅化(const D3D11_RASTERIZER_DESC &);
	void fs混合(const D3D11_BLEND_DESC &);
	void fs深度模板(const D3D11_DEPTH_STENCIL_DESC &);
	void fs光栅化(ID3D11RasterizerState *);
	void fs混合(ID3D11BlendState *);
	void fs深度模板(ID3D11DepthStencilState *);
};
struct S深度模板参数 : public D3D11_DEPTH_STENCIL_DESC {
	S深度模板参数();
	void fs深度部分(const D3D11_DEPTH_STENCIL_DESC &);
	void fs模板部分(const D3D11_DEPTH_STENCIL_DESC &);
};
//==============================================================================
// 图形引擎
//==============================================================================
class C创建设备;
class C三维 {
	friend C渲染控制;
public:
	enum E标志 {
		e调试,
		e软件设备,
	};
	~C三维();
	//手动初始化
	void f初始化窗口(HWND p);
	HRESULT f初始化设备();
	HRESULT f初始化交换链();
	HRESULT f初始化渲染目标视图();
	HRESULT f初始化深度模板视图();
	HRESULT f重置屏幕资源();	//重置交换链和视图
	HRESULT f重置交换链();	//注意:会清除所有状态
	HRESULT f调整目标大小();	//调窗口大小
	//一键初始化
	bool f初始化(HWND);
	void f销毁();
	//创建
	HRESULT f创建顶点着色器(tp顶点着色器 &, const std::span<const std::byte> &);
	HRESULT f创建像素着色器(tp像素着色器 &, const std::span<const std::byte> &);
	HRESULT f创建几何着色器(tp几何着色器 &, const std::span<const std::byte> &);
	HRESULT f创建外壳着色器(tp外壳着色器 &, const std::span<const std::byte> &);
	HRESULT f创建域着色器(tp域着色器 &, const std::span<const std::byte> &);
	HRESULT f创建输入布局(tp输入布局 &, const std::span<const std::byte> &, const C顶点格式 &);
	HRESULT f创建图形管线(tp图形管线 &, const S图形管线参数 &);
	//属性
	D3D11_VIEWPORT fg窗口视口() const;
	数学::S向量2 fg窗口大小() const;
	void fs窗口大小();	//根据窗口自动设置
	HRESULT fs窗口大小(int 宽, int 高);	//调用IDXGISwapChain::ResizeTarget
	void fs窗口大小_(int, int);
	void fs抗锯齿(UINT);	//(已废弃)需要重置屏幕资源
	DXGI_SAMPLE_DESC f计算抗锯齿(UINT);	//(已废弃)
	void fs视口();	//直接铺满屏幕
	bool fi全屏() const;
	bool fi窗口() const;
	void fs全屏(bool);
	//对象
	C渲染控制 &fg渲染控制();	//必须在初始化完成之后才能调用
	C渲染状态 &fg渲染状态();
	C创建设备 &fg创建设备();
	ComPtr<ID3D11Device> fg设备() const;
	ComPtr<IDXGIDevice> fg基础设备() const;
	ComPtr<ID3D11DeviceContext> fg上下文() const;
	ComPtr<IDXGISwapChain> fg交换链() const;
	C缓冲工厂 &fg缓冲工厂();
	C纹理工厂 &fg纹理工厂();
private:	//窗口
	HWND m窗口 = nullptr;
	int m窗口大小[2];
	std::bitset<32> m标志;
	//图形设备
	ComPtr<ID3D11Device> m设备;
	std::unique_ptr<C创建设备> m创建设备;	//在f初始化设备()中创建
	std::unique_ptr<C渲染控制> m渲染控制;
	ComPtr<ID3D11DeviceContext> m上下文;
	ComPtr<IDXGISwapChain> m交换链;
	ComPtr<ID3D11RenderTargetView> m渲染目标视图;
	ComPtr<ID3D11Texture2D> m深度模板;
	ComPtr<ID3D11DepthStencilView> m深度模板视图;
	//图形状态
	D3D_FEATURE_LEVEL m功能级别;
	UINT m抗锯齿等级 = 0;
	UINT m当前抗锯齿等级 = 0;
	UINT m纹理最大尺寸 = 0;
	//资源管理
	std::unique_ptr<C渲染状态> m渲染状态;
	std::unique_ptr<C纹理工厂> m纹理工厂;
	std::unique_ptr<C缓冲工厂> m缓冲工厂;
};
//创建设备
class C创建设备 {
public:
	static const D3D_FEATURE_LEVEL c功能级别组[3];
	static const UINT c功能级别数 = 3;
	static const UINT c创建标志;
public:
	C创建设备() = default;
	ComPtr<IDXGIFactory1> fg工厂();
	HRESULT f检查兼容性();
	HRESULT f取显卡(IDXGIAdapter1**);
	void fs调试标志(bool);
	HRESULT f创建设备(IDXGIAdapter1*, ID3D11Device**, ID3D11DeviceContext**);
	HRESULT f创建软件设备(ID3D11Device**, ID3D11DeviceContext**);
public:
	ComPtr<IDXGIFactory1> m工厂 = nullptr;
	UINT m创建标志 = c创建标志;
	D3D_FEATURE_LEVEL m功能级别 = D3D_FEATURE_LEVEL_10_0;
};
//==============================================================================
// 渲染控制
//==============================================================================
class C渲染控制 {
	friend C三维;
public:
	C渲染控制();
	C渲染控制(const C渲染控制 &) = delete;
	C渲染控制(C渲染控制 &&) = delete;
	//设备控制
	void f清屏();
	void f显示();
	void f绘制(unsigned int 顶点数, unsigned int 开始 = 0);
	void f绘制索引(unsigned int 索引数, unsigned int 开始索引 = 0, int 开始顶点 = 0);
	void fs清屏颜色(const 数学::S颜色 &);
	void fs清屏深度(float);
	void fs清屏模板(UINT8);
	void fs图形管线(const C图形管线 &);
	//设置着色器
	void f重置着色器();
	void fs顶点着色器(ID3D11VertexShader *);
	void fs像素着色器(ID3D11PixelShader *);
	void fs几何着色器(ID3D11GeometryShader *);
	void fs外壳着色器(ID3D11HullShader *);
	void fs域着色器(ID3D11DomainShader *);
	//状态控制
	void fs混合(ID3D11BlendState * = nullptr, const 数学::S颜色 & = {0, 0, 0, 0}, UINT = 0xffffffff);
	void fs深度模板(ID3D11DepthStencilState * = nullptr, UINT = 1);
	void fs模板参考值(UINT);
	void fs光栅化(ID3D11RasterizerState *);
	void fs顶点缓冲(ID3D11Buffer *, UINT 单位大小);
	void fs索引缓冲(ID3D11Buffer *);
	void fs常量缓冲(UINT, ID3D11Buffer *);
	void fs常量缓冲v(UINT, ID3D11Buffer *);
	void fs常量缓冲p(UINT, ID3D11Buffer *);
	void fs常量缓冲g(UINT, ID3D11Buffer *);
	void fs常量缓冲h(UINT, ID3D11Buffer *);
	void fs常量缓冲d(UINT, ID3D11Buffer *);
	void fs纹理(UINT, ID3D11ShaderResourceView *);
	void fs采样器(UINT, ID3D11SamplerState *);
	void fs输入布局(ID3D11InputLayout *);
	void fs图元拓扑(E图元拓扑);
	void f更新资源(ID3D11Buffer *, const void *);
private:
	const C三维 *m三维 = nullptr;
	//清屏
	数学::S颜色 m清屏颜色 = 数学::S颜色::c黑;
	float m清屏深度 = c清屏深度r;
	UINT8 m清屏模板 = 0;
};
class C自动缓冲 {
public:
	class C缓冲 {
	public:
		C缓冲工厂 *m缓冲工厂;
		ID3D11DeviceContext *m上下文;
		ComPtr<ID3D11Buffer> m缓冲;
		std::byte *m映射 = nullptr;
		UINT m缓冲大小 = 0;
		UINT m单位大小 = 0;
		UINT m修改 = 0;	//修改的位置
		E缓冲 m标志;
		C缓冲(ID3D11DeviceContext &, C缓冲工厂 &, E缓冲);
		void f初始化(size_t 单位大小, size_t 数量);	//索引数一般是顶点数的2倍
		bool f映射();
		bool f取消映射();
		bool f复制(const void *, size_t);
		UINT fg数量();
	};
	ID3D11DeviceContext *m上下文;
	C缓冲工厂 *m缓冲工厂;
	C缓冲 m顶点缓冲;
	C缓冲 m索引缓冲;
	std::function<void()> mf刷新回调;
	C自动缓冲(C三维 &);
	bool f刷新();
	void f复制(const void *顶点数据, size_t 顶点大小, const void *索引数据, size_t 索引大小);
	bool fi修改() const;
};
//==============================================================================
// 状态
//==============================================================================
class C渲染状态 {
public:
	//值
	struct S光栅化参数 {
		D3D11_RASTERIZER_DESC m默认, 
			m线框渲染, 
			m显示隐藏面, 
			m反面渲染;
	} m光栅化参数;
	struct S混合参数 {
		D3D11_BLEND_DESC m默认,
			m开启透明,
			m颜色叠加,
			m禁止写颜色;
	} m混合参数;
	struct S深度模板参数 {
		D3D11_DEPTH_STENCIL_DESC m默认,
			m正常深度l,
			m正常深度r,
			m总是覆盖,
			m模板标记,
			m模板比较;
	} m深度模板参数;
	struct S采样器参数 {
		D3D11_SAMPLER_DESC m纹理,
			m图案,
			m各向异性过滤;
	} m采样器参数;
	//对象
	struct S光栅化 {
		ComPtr<ID3D11RasterizerState> m默认,
			m线框渲染,	//只有线框
			m显示隐藏面,	//正背面都显示
			m反面渲染;	//只显示背面,正面被剔除
	} m光栅化;
	struct S混合 {
		ComPtr<ID3D11BlendState> m默认,
			m开启透明,
			m颜色叠加,
			m禁止写颜色;
	} m混合;
	struct S深度模板 {
		ComPtr<ID3D11DepthStencilState> m默认,
			m正常深度l,
			m正常深度r,
			m总是覆盖,
			m模板标记;
	} m深度模板;
	struct S采样器 {
		ComPtr<ID3D11SamplerState> m纹理,
			m图案,
			m各向异性过滤;
	} m采样器;
	C渲染状态(ID3D11Device *);
	~C渲染状态();
};
class C图形管线 {
public:
	ComPtr<ID3D11VertexShader> m顶点着色器;
	ComPtr<ID3D11PixelShader> m像素着色器;
	ComPtr<ID3D11GeometryShader> m几何着色器;
	ComPtr<ID3D11HullShader> m外壳着色器;
	ComPtr<ID3D11DomainShader> m域着色器;
	ComPtr<ID3D11InputLayout> m输入布局;
	ComPtr<ID3D11RasterizerState> m光栅化;
	ComPtr<ID3D11BlendState> m混合;
	ComPtr<ID3D11SamplerState> m采样器;
	ComPtr<ID3D11DepthStencilState> m深度模板;
};
//==============================================================================
// 工厂
//==============================================================================
//输入布局
class C顶点格式 {
public:
	enum E类型 {
		e位置,
		e法线,
		e副法线,
		e颜色,
		e纹理,
		e点大小,
		e切线
	};
	std::vector<D3D11_INPUT_ELEMENT_DESC> m数组;
	std::map<std::string, int> m类型累计;
	int m字节累计 = 0;
	void f清空();
	void f添加(E类型, int 大小);
	void f添加(const char *, int 大小);
};
//创建缓存
class C缓冲工厂 {
public:
	void f初始化(ID3D11Device *);
	HRESULT f创建缓冲(tp缓冲 &, const void *a数据, UINT 大小, E缓冲 标志, E资源用法 = e默认);
public:
	ComPtr<ID3D11Device> m设备;
};
//纹理工厂
class C纹理工厂 {
public:
	~C纹理工厂();
	HRESULT f初始化(ID3D11Device *);
public:	//创建纹理
	HRESULT f从文件创建纹理(tp纹理 &输出, const wchar_t *文件);
	HRESULT f从内存创建纹理2(tp纹理2 &输出, const void *数据, DXGI_FORMAT 格式, UINT 宽, UINT 高, UINT 行距, UINT 图像大小);
	HRESULT f从纹理对象创建纹理2(tp纹理2 &输出, const 纹理::I纹理 &纹理);
	HRESULT f创建纹理资源视图(tp纹理 &输出, tp纹理2, DXGI_FORMAT 格式);
	const D3D11_TEXTURE2D_DESC &fg最近纹理描述() const;
private:
	std::unique_ptr<纹理::C图像工厂> m工厂;
	ComPtr<ID3D11Device> m设备;
	D3D11_TEXTURE2D_DESC m纹理描述;
};
}	//namespace cflw::图形::d3d11
