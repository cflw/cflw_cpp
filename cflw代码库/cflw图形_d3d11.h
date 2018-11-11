#pragma once
//链接
#ifdef _WINDOWS
#pragma comment(lib, "dxguid.lib")
#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "D3dcompiler.lib")
#pragma comment(lib, "d3d11.lib")
#endif
//包括头文件
#include <vector>
#include <string>
#include <map>
#include <memory>
#include <bitset>
#include <d3d11.h>
#include <wrl.h>
#include "cflw辅助.h"
#include "cflw数学.h"
#include "cflw数学_图形.h"
#include "cflw图形_d3d纹理.h"
//命名空间
namespace cflw::图形::d3d11 {
//=============================================================================
// 前置声明
//=============================================================================
using Microsoft::WRL::ComPtr;
typedef ID3D11Device t设备;
typedef ID3D11DeviceContext t设备上下文;
typedef ID3D11VertexShader t顶点着色器;
typedef ID3D11PixelShader t像素着色器;
typedef ID3D11GeometryShader t几何着色器;
typedef ID3D11HullShader t外壳着色器;
typedef ID3D11DomainShader t域着色器;
typedef ID3D11Buffer t缓冲;
typedef ID3D11InputLayout t输入布局;
typedef ID3D11ShaderResourceView t纹理;
typedef ID3D11RasterizerState t光栅化;
typedef ID3D11BlendState t混和;
typedef ID3D11SamplerState t采样器;
typedef ID3D11DepthStencilState t深度模板;
typedef ID3D11Texture2D t纹理2;
typedef ComPtr<ID3D11Device> tp设备;
typedef ComPtr<ID3D11DeviceContext> tp设备上下文;
typedef ComPtr<ID3D11VertexShader> tp顶点着色器;
typedef ComPtr<ID3D11PixelShader> tp像素着色器;
typedef ComPtr<ID3D11GeometryShader> tp几何着色器;
typedef ComPtr<ID3D11HullShader> tp外壳着色器;
typedef ComPtr<ID3D11DomainShader> tp域着色器;
typedef ComPtr<ID3D11Buffer> tp缓冲;
typedef ComPtr<ID3D11InputLayout> tp输入布局;
typedef ComPtr<ID3D11ShaderResourceView> tp纹理;
typedef ComPtr<ID3D11RasterizerState> tp光栅化;
typedef ComPtr<ID3D11BlendState> tp混和;
typedef ComPtr<ID3D11SamplerState> tp采样器;
typedef ComPtr<ID3D11DepthStencilState> tp深度模板;
typedef ComPtr<ID3D11Texture2D> tp纹理2;
typedef ComPtr<ID3DBlob> tp着色器;
//本文件
class C渲染控制;
class C渲染状态;
class C顶点格式;
class C纹理工厂;
class C缓冲工厂;
class C着色器工厂;
class C图形管线;
struct S图形管线参数;
typedef std::shared_ptr<C图形管线> tp图形管线;
//==============================================================================
// 常量
//==============================================================================
enum E图元拓扑 {
	e列表点 = D3D11_PRIMITIVE_TOPOLOGY_POINTLIST,
	e列表线段 = D3D11_PRIMITIVE_TOPOLOGY_LINELIST,
	e连续线段 = D3D11_PRIMITIVE_TOPOLOGY_LINESTRIP,
	e列表三角形 = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST,
	e连续三角形 = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP
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
	e固定 = D3D11_BIND_CONSTANT_BUFFER,
	e着色器 = D3D11_BIND_SHADER_RESOURCE
};
//常量
typedef uint16_t t索引;
constexpr DXGI_FORMAT c索引格式 = DXGI_FORMAT_R16_UINT;
constexpr DXGI_FORMAT c交换链格式 = DXGI_FORMAT_R8G8B8A8_UNORM;
constexpr DXGI_FORMAT c深度模板格式 = DXGI_FORMAT_D32_FLOAT_S8X24_UINT;
constexpr float c清屏深度l = 1;
constexpr float c清屏深度r = 0;
//==============================================================================
// 结构
//==============================================================================
struct S着色器字节代码 {
	const void *m数据 = nullptr;
	size_t m大小 = 0;
	static S着色器字节代码 fc二进制大对象(ID3DBlob *);	//返回的结构的生命周期不能超过参数的生命周期
	operator bool() const;
};
struct S图形管线参数 {
	const C顶点格式 *m顶点格式 = nullptr;
	S着色器字节代码 m顶点着色器;
	S着色器字节代码 m像素着色器;
	S着色器字节代码 m几何着色器;
	S着色器字节代码 m外壳着色器;
	S着色器字节代码 m域着色器;
	ID3D11RasterizerState *m光栅化 = nullptr;
	ID3D11BlendState *m混合 = nullptr;
	ID3D11DepthStencilState *m深度模板 = nullptr;
	void fs输入布局(const C顶点格式 &);
	void fs顶点着色器(const S着色器字节代码 &);
	void fs像素着色器(const S着色器字节代码 &);
	void fs几何着色器(const S着色器字节代码 &);
	void fs外壳着色器(const S着色器字节代码 &);
	void fs域着色器(const S着色器字节代码 &);
	void fs光栅化(ID3D11RasterizerState *);
	void fs混合(ID3D11BlendState *);
	void fs深度模板(ID3D11DepthStencilState *);
};
//==============================================================================
// 图形引擎
//==============================================================================
class C创建设备;
class C三维 {
public:
	enum E标志 {
		e调试,
		e软件设备
	};
	~C三维();
	//手动初始化
	void f初始化窗口(HWND p);
	HRESULT f初始化设备();
	HRESULT f初始化交换链();
	HRESULT f初始化渲染目标视图();
	HRESULT f初始化深度模板视图();
	//一键初始化
	bool f初始化(HWND);
	void f销毁();
	// 资源
	C渲染控制 &fg渲染控制();	//必须在初始化完成之后才能调用
	C渲染状态 &fg渲染状态();
	ComPtr<ID3D11Device> fg设备();
	ComPtr<ID3D11DeviceContext> fg上下文();
	ComPtr<IDXGISwapChain> fg交换链();
	D3D11_VIEWPORT fg窗口视口() const;
	数学::S向量2 fg窗口大小() const;
	// 设置
	HRESULT f创建输入布局(tp输入布局 &输出, C顶点格式 &输入, const void *p着色器数据, size_t);
	HRESULT f创建图形管线(tp图形管线 &, const S图形管线参数 &);
	HRESULT f设置抗锯齿(UINT);
	DXGI_SAMPLE_DESC f计算抗锯齿(UINT);
	void f设置视口();	//直接铺满屏幕
	//工厂
	C缓冲工厂 &fg缓冲工厂();
	C纹理工厂 &fg纹理工厂();
	C着色器工厂 &fg着色器工厂();
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
	std::unique_ptr<C着色器工厂> m着色器工厂;
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
	void fs光栅化(ID3D11RasterizerState *);
	void fs顶点缓冲(ID3D11Buffer *, UINT 单位大小);
	void fs索引缓冲(ID3D11Buffer *);
	void fs固定缓冲(UINT, ID3D11Buffer *);
	void fs固定缓冲v(UINT, ID3D11Buffer *);
	void fs固定缓冲p(UINT, ID3D11Buffer *);
	void fs固定缓冲g(UINT, ID3D11Buffer *);
	void fs固定缓冲h(UINT, ID3D11Buffer *);
	void fs固定缓冲d(UINT, ID3D11Buffer *);
	void fs纹理(UINT, ID3D11ShaderResourceView *);
	void fs采样器(UINT, ID3D11SamplerState *);
	void fs输入布局(ID3D11InputLayout *);
	void fs图元拓扑(E图元拓扑);
	void f更新资源(ID3D11Buffer *, const void *);
private:
	//图形设备
	ComPtr<ID3D11DeviceContext> m上下文;
	ComPtr<IDXGISwapChain> m交换链;
	ComPtr<ID3D11RenderTargetView> m渲染目标视图;
	ComPtr<ID3D11DepthStencilView> m深度模板视图;
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
			m总是覆盖;
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
			m总是覆盖;
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
//着色器工厂
class C着色器工厂 {
public:
	void f初始化(ID3D11Device*);
	//从文件中编译着色器
	HRESULT f编译并创建顶点着色器(tp顶点着色器 &, const wchar_t *文件名, const char *函数名, tp输入布局 &, const C顶点格式 &);
	HRESULT f编译并创建像素着色器(tp像素着色器 &, const wchar_t *文件名, const char *函数名);
	HRESULT f编译并创建几何着色器(tp几何着色器 &, const wchar_t *文件名, const char *函数名);
	HRESULT f编译并创建外壳着色器(tp外壳着色器 &, const wchar_t *文件名, const char *函数名);
	HRESULT f编译并创建域着色器(tp域着色器 &, const wchar_t *文件名, const char *函数名);
	//从文件中读取着色器
	HRESULT f读取并创建顶点着色器(tp顶点着色器 &, const wchar_t *文件名, tp输入布局 &, const C顶点格式 &);
	HRESULT f读取并创建像素着色器(tp像素着色器 &, const wchar_t *文件名);
	HRESULT f读取并创建几何着色器(tp几何着色器 &, const wchar_t *文件名);
	HRESULT f读取并创建外壳着色器(tp外壳着色器 &, const wchar_t *文件名);
	HRESULT f读取并创建域着色器(tp域着色器 &, const wchar_t *文件名);
	//创建
	HRESULT f创建顶点着色器(tp顶点着色器 &, const S着色器字节代码 &);
	HRESULT f创建像素着色器(tp像素着色器 &, const S着色器字节代码 &);
	HRESULT f创建几何着色器(tp几何着色器 &, const S着色器字节代码 &);
	HRESULT f创建外壳着色器(tp外壳着色器 &, const S着色器字节代码 &);
	HRESULT f创建域着色器(tp域着色器 &, const S着色器字节代码 &);
	HRESULT f创建输入布局(tp输入布局 &, const S着色器字节代码 &, const C顶点格式 &);
	//编译
	static HRESULT f编译顶点着色器(ComPtr<ID3DBlob> &, const wchar_t *文件名, const char *函数名);
	static HRESULT f编译像素着色器(ComPtr<ID3DBlob> &, const wchar_t *文件名, const char *函数名);
	static HRESULT f编译几何着色器(ComPtr<ID3DBlob> &, const wchar_t *文件名, const char *函数名);
	static HRESULT f编译外壳着色器(ComPtr<ID3DBlob> &, const wchar_t *文件名, const char *函数名);
	static HRESULT f编译域着色器(ComPtr<ID3DBlob> &, const wchar_t *文件名, const char *函数名);
	//静态函数
	static HRESULT f编译着色器(const wchar_t *a文件名, const char *a入口, const char *a着色模型, ID3DBlob** a输出);
	static HRESULT f读取着色器(const wchar_t *a文件名, std::unique_ptr<std::byte[]> &a数据, DWORD &a大小);
	static HRESULT f读取着色器(ComPtr<ID3DBlob> &, const wchar_t *a文件名);
private:
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
	HRESULT f创建纹理资源视图(tp纹理 &a输出, tp纹理2, DXGI_FORMAT 格式);
	const D3D11_TEXTURE2D_DESC &fg最近纹理描述() const;
private:
	std::unique_ptr<纹理::C图像工厂> m工厂;
	ComPtr<ID3D11Device> m设备;
	D3D11_TEXTURE2D_DESC m纹理描述;
};
}	//namespace cflw::图形::d3d11
