#pragma once
#ifndef 头文件_cflw图形_d3d9
#define 头文件_cflw图形_d3d9
//链接
#ifdef _WINDOWS
#pragma comment(lib, "dxerr.lib")
#pragma comment(lib, "dxguid.lib")
#pragma comment(lib, "d3d9.lib")
#if defined(DEBUG) || defined(_DEBUG)
#pragma comment(lib, "d3dx9d.lib")
#else
#pragma comment(lib, "d3dx9.lib")
#endif //DEBUG
#endif
//包括头文件
#include <d3d9.h>
#include <d3dx9.h>
#include "cflw视窗.h"
#include "cflw辅助_win.h"
//正文开始
namespace cflw {
namespace 图形 {
namespace d3d9 {
//!--------------------------------------------------------------------------------
//!++常量
//!--------------------------------------------------------------------------------
#define c窗口宽度 640
#define c窗口高度 480
#define c纹理尺寸_中 D3DXVECTOR2(256,256)
#define c纹理尺寸_大 D3DXVECTOR2(512,512)
#define c1向量2 D3DXVECTOR2(1,1)
#define c0向量3 D3DXVECTOR3(0,0,0)
#define c1倍缩放 D3DXVECTOR3(1,1,1)
//!--------------------------------------------------------------------------------
//!++direct3d类型另命名
//!--------------------------------------------------------------------------------
//Direct3D图形各种接口
typedef IDirect3D9				*t接口指针;
typedef IDirect3DDevice9		*t设备指针;
typedef IDirect3DVertexBuffer9	*t顶点;
typedef IDirect3DTexture9		*t纹理;
typedef ID3DXSprite				*t精灵指针;
typedef ID3DXFont				*t字体指针;
typedef ID3DXMesh				*t网格指针;
//一级分割线============================================================
//Direct3D图形各种结构
typedef D3DXMATRIX t矩阵;
typedef D3DXVECTOR2 t向量2;
typedef D3DXVECTOR3 t向量3;
typedef D3DXQUATERNION t四元数;
typedef D3DXCOLOR t颜色;
typedef D3DMATERIAL9 t材质;
typedef D3DLIGHT9 t光;
//--------------------------------------------------------------------------------
//!++类
//--------------------------------------------------------------------------------
//!+声明
class C世界矩阵3d;
typedef class C世界矩阵3d t世界矩阵, t世界矩阵3;
typedef class C世界矩阵2d t世界矩阵2;
//!+矩形结构
typedef struct S矩形 {
	t向量2 v坐标;
	t向量2 v半尺寸;
	S矩形();
	S矩形(const t向量2 &, const t向量2 &);
	S矩形(const 视窗::t矩形 &);
	S矩形(const float &左, const float &上, const float &右, const float &下);
}t矩形;
//!+顶点结构
typedef struct S三维顶点 {
	S三维顶点 (void);
	S三维顶点 (const float &_x, const float &_y, const float &_u, const float &_v);
	S三维顶点 (const float &_x, const float &_y, const float &_z, const float &_u, const float &_v);
	//二级分割线========================================
	float	x, y, z;	// 顶点的3D位置
	float	u, v;		// 纹理坐标
}t三维顶点, *t三维顶点指针;
//!+世界矩阵
class C世界矩阵3d {
public:
//变量
	t向量3 v平移;
	t向量3 v旋转;
	t向量3 v缩放;
//构造函数
	C世界矩阵3d ();
	C世界矩阵3d (const t向量3 &, const t向量3 &, const t向量3 &);
//函数
	void f矩阵应用 ();
	void f矩阵应用2 ();
	C世界矩阵3d& f矩阵复位 ();
	C世界矩阵3d& f矩阵旋转 (const float &);	//平面旋转
	t世界矩阵2 fg世界矩阵2 ();
	inline C世界矩阵3d &fg世界矩阵3() {
		return *this;
	};
	inline void fs旋转2 (const float &p = 0) {
		v旋转.x = 0;
		v旋转.y = 0;
		v旋转.z = p;
	};
	inline void fs缩放2 (const float &px = 1, const float &py = 1) {
		v缩放.x = px;
		v缩放.y = py;
	}
};
class C世界矩阵2d {
public:
//变量
	t向量2 v平移;
	float v旋转;
	t向量2 v缩放;
//构造函数
	C世界矩阵2d ();
	C世界矩阵2d (const t向量2 &, const float &, const t向量2 &);
//函数
	void f矩阵应用 ();
	C世界矩阵2d& f矩阵复位 ();
	C世界矩阵2d& f矩阵反向 ();	//反向平移
};
//!+相机类
typedef class C相机
{
public:
//变量
	t向量3 v位置;
	t向量3 v看向;
	t向量3 v上方;
//构造函数
	C相机 ();
	C相机 (const t向量3 &, const t向量3 &, const t向量3 &);
//函数
	void f应用 ();
	C相机& f复位 ();
	C相机& f平移 (const t向量3 &);
}t相机;
//!+投影矩阵
class C投影矩阵	//定义物体如何投影到屏幕上
{
public:
	float v视角;	//弧度,3d视角范围
	float v宽;		//2d宽度,3d用于宽高比
	float v高;		//2d高度,3d用于宽高比
	float v近z;		//近裁剪面
	float v远z;		//远裁剪面
	C投影矩阵 ();
	void f应用2d ();
	void f应用3d ();
};
//!+视口
class C视口	//定义投影到屏幕上的区域
{	//注意必须使用数学直角坐标系
public:
	t向量2 v左上;
	t向量2 v右下;
	C视口 ();
	void f应用 ();
	void fs (const float &左, const float &上, const float &右, const float &下);
};
//+图形类
typedef class C图形 t图形;
typedef void (*t图形函数指针)(t图形 &);
class C图形:public C世界矩阵3d
{
public:
//成员变量
	t纹理 v纹理;	//绑定的纹理
	t顶点 v顶点;	//使用的顶点
	t材质 v材质;		//使用的材质
//构造函数
	C图形 (void);
//成员函数
	void f绘制准备 ();
	void f显示2d ();
	void f显示3d ();
};
//+顶点制造机
typedef class C顶点制造机_矩形 t顶点制造_矩形;
typedef class C顶点制造机_矩形ex t顶点制造_矩形ex;
class C顶点制造机_矩形 {
public:
	t向量2 v纹理尺寸;
	t向量2 v矩形坐标;
	t向量2 v矩形半尺寸;
	float v矩形扩张;
	C顶点制造机_矩形 ();
	inline void f设置纹理尺寸 (const float &x, const float &y) {
		v纹理尺寸.x = x;
		v纹理尺寸.y = y;
	};
	inline void f设置矩形坐标 (const float &x, const float &y) {
		v矩形坐标.x = x;
		v矩形坐标.y = y;
	};
	inline void f设置矩形半尺寸 (const float &x, const float &y) {
		v矩形半尺寸.x = x;
		v矩形半尺寸.y = y;
	};
	void f设置矩形 (const float &左, const float &上, const float &右, const float &下);
	bool f创建顶点 (t顶点 &);
};
class C顶点制造机_矩形ex: public C顶点制造机_矩形
{
public:
	t向量2 v平移;
	float v旋转;
	t向量2 v缩放;
	C顶点制造机_矩形ex ();
	inline void f设置平移 (const float &x, const float &y)
	{
		v平移.x = x;
		v平移.y = y;
	};
	inline void f设置旋转 (const float &弧度)
	{
		v旋转 = 弧度;
	};
	inline void f设置缩放 (const float &x, const float &y)
	{
		v缩放.x = x;
		v缩放.y = y;
	};
	inline void fex属性清空 ()
	{
		v平移.x = 0;
		v平移.y = 0;
		v旋转 = 0;
		v缩放.x = 0;
		v缩放.y = 0;
	};
	void f设置显示矩形 (const float &左, const float &上, const float &右, const float &下);
	bool f创建顶点ex (t顶点 &);
};
class C顶点制造机_点
{
public:
	t向量3 v坐标;
	t向量2 v纹理映射;
	t向量2 v纹理尺寸;
	C顶点制造机_点 ();
	~C顶点制造机_点 ();
};
//+顶点锁定机
class C顶点锁定机
{
	t顶点 v锁定顶点;
	void **v修改顶点;
public:
	C顶点锁定机 ();
	~C顶点锁定机 ();
	bool f锁定_ (const t顶点 &, void **);
	template<class t> inline bool f锁定 (const t顶点 &p锁定顶点, t &p修改顶点)
	{
		return f锁定_ (p锁定顶点, (void**)&p修改顶点);
	};
	bool f解锁 ();
};
//+文本制造机
typedef class C文本制造机 t文本制造机;
class C文本制造机
{
public:
	LONG 高;	//单个文字的高度
	LONG 宽;	//单个文字的宽度
	LONG 粗;	//0-1000 数值越大越粗
	FLOAT 厚;	//往Z轴延伸的厚度
	BYTE 斜体;		//是否斜体
	BYTE 下划线;	//是否有下划线
	BYTE 删除线;	//是否有删除线
	WCHAR 字体[32];	//字体的名称
	C文本制造机 ();
	inline void f设置字体 (wchar_t* _字体)
	{
		wcscpy_s (字体, _字体);
	};
	inline void f设置粗体 (const bool &粗体)
	{
		粗 = 粗体 ? FW_BOLD : FW_NORMAL;
	};
	bool f创建文本 (wchar_t* 文本, t网格指针&);
};
//--------------------------------------------------------------------------------
//!++direct3d枚举和常量
//--------------------------------------------------------------------------------
//D3DPRIMITIVETYPE枚举
enum E图元类型
{
	c图元类型_列表点 = D3DPT_POINTLIST,
	c图元类型_列表线段 = D3DPT_LINELIST,
	c图元类型_连续线段 = D3DPT_LINESTRIP,
	c图元类型_列表三角形 = D3DPT_TRIANGLELIST,
	c图元类型_连续三角形 = D3DPT_TRIANGLESTRIP,
	c图元类型_扇形三角形 = D3DPT_TRIANGLEFAN
};
typedef _D3DPRIMITIVETYPE t图元类型;
//D3DTEXTURESTAGESTATETYPE枚举
enum E纹理图层状态类型
{
	c纹理图层状态类型_颜色操作 = D3DTSS_COLOROP,
	c纹理图层状态类型_颜色参数1 = D3DTSS_COLORARG1,
	c纹理图层状态类型_颜色参数2 = D3DTSS_COLORARG2,
	c纹理图层状态类型_阿尔法操作 = D3DTSS_ALPHAOP,
	c纹理图层状态类型_阿尔法参数1 = D3DTSS_ALPHAARG1,
	c纹理图层状态类型_阿尔法参数2 = D3DTSS_ALPHAARG2
};
typedef _D3DTEXTURESTAGESTATETYPE t纹理图层状态类型;
//D3DTEXTUREOP枚举
enum E纹理操作
{
	c纹理操作_禁止 = D3DTOP_DISABLE,
	c纹理操作_选择1 = D3DTOP_SELECTARG1,
	c纹理操作_选择2 = D3DTOP_SELECTARG2,
	c纹理操作_相乘 = D3DTOP_MODULATE
};
typedef _D3DTEXTUREOP t纹理操作;
//D3DLIGHTTYPE 枚举
enum E光类型
{
	c光类型_点光源 = D3DLIGHT_POINT,
	c光类型_聚光灯 = D3DLIGHT_SPOT,
	c光类型_平行光 = D3DLIGHT_DIRECTIONAL
};
typedef _D3DLIGHTTYPE t光类型;
//D3DRENDERSTATETYPE枚举
enum E渲染状态
{
	c渲染状态_源混合 = D3DRS_SRCBLEND,
	c渲染状态_目标混合 = D3DRS_DESTBLEND
};
typedef _D3DRENDERSTATETYPE t渲染状态;
//D3DBLEND枚举
enum E混合
{
	c混合_源颜色 = D3DBLEND_SRCCOLOR,
	c混合_源颜色反 = D3DBLEND_INVSRCCOLOR,
	c混合_源阿尔法 = D3DBLEND_SRCALPHA,
	c混合_源阿尔法反 = D3DBLEND_INVSRCALPHA,
	c混合_目标阿尔法 = D3DBLEND_DESTALPHA,
	c混合_目标阿尔法反 = D3DBLEND_INVDESTALPHA,
	c混合_目标颜色 = D3DBLEND_DESTCOLOR,
	c混合_目标颜色反 = D3DBLEND_INVDESTCOLOR
};
typedef _D3DBLEND t混合;
enum E混合模式
{
	e混合_正常,
	e混合_叠加
};
//--------------------------------------------------------------------------------
//全局变量声明
//--------------------------------------------------------------------------------
extern t接口指针 v图形接口;
extern t设备指针 v图形设备;
extern const t颜色 c白色;
extern const t颜色 c红色;
extern const t颜色 c绿色;
extern const t颜色 c蓝色;
extern const t颜色 c无色;
extern const t材质 c白色材质;
extern const t材质 c小透明白色材质;
extern const t材质 c半透明白色材质;
extern const t材质 c大透明白色材质;
extern const t材质 c透明材质;
extern const t材质 c红色材质;
extern const t材质 c绿色材质;
extern const t材质 c蓝色材质;
extern DWORD fvf三维顶点;
extern t光 v屏幕光;
extern t相机 v屏幕相机;	//对准整个屏幕
extern t材质 v临时材质;
extern E图元类型 v画出模式;
extern C投影矩阵 v默认投影;
extern t向量2 v屏幕尺寸;
extern C视口 v屏幕视口;
extern 视窗::C关键段 v关键段;
extern t材质 v2d材质;
//辅助图形
extern t顶点 v矩形;
//--------------------------------------------------------------------------------
//函数
//--------------------------------------------------------------------------------
//设备
bool f创建设备 (const HWND &窗口句柄);
void f快速初始化 ();
void f图形复位 ();
void f销毁设备 ();
void f载入附加图形 ();
//辅助函数
void f画_矩形 (const t矩形 &);
//其他
inline t向量2 fn倍缩放2 (const float &p缩放倍数)
{
	return t向量2 (p缩放倍数, p缩放倍数);
};
inline t向量3 fn倍缩放3 (const float &p缩放倍数)
{
	return t向量3 (p缩放倍数, p缩放倍数, p缩放倍数);
};
视窗::t矩形 f到窗口坐标 (const 视窗::t矩形 &);
视窗::t矩形 f矩形 (const t向量2 &中心坐标, const t向量2 &半尺寸);
inline 视窗::t矩形 f矩形 (const t矩形 &p矩形)
{
	return f矩形 (p矩形.v坐标, p矩形.v半尺寸);
};
t材质 f材质颜色渐变 (const t材质 &, const t颜色 &, const float &);
t矩形 f矩形形状渐变 (const t矩形 &, const t矩形 &, const float & = 0.4f, const float & = 999.f);
//设备状态
inline HRESULT f设置渲染状态(const _D3DRENDERSTATETYPE &状态, const DWORD &值)
{
	return v图形设备->SetRenderState(状态,值);
};
//绘制
inline void f设置画出模式 (const E图元类型 &p画出模式)
{
	v画出模式 = p画出模式;
};
inline void f绘制图元 (const unsigned int &p顶点起点, const unsigned int &p图形数量)
{
	v图形设备->DrawPrimitive((t图元类型)(int)v画出模式, p顶点起点, p图形数量);
};
inline void f绘制图元 (const unsigned int &p图形数量)
{
	v图形设备->DrawPrimitive((t图元类型)(int)v画出模式, 0, p图形数量);
};
inline void f绘制图元 ()
{
	v图形设备->DrawPrimitive((t图元类型)(int)v画出模式, 0, 2);
};
//顶点
HRESULT f创建顶点缓冲 (t顶点 *接受缓冲区的顶点指针, const int &顶点数量);	//使用前需要设置好顶点大小和fvf格式
inline void f设置流源(const t顶点 顶点)
{
	v图形设备->SetStreamSource (0, 顶点, 0, sizeof(S三维顶点));
};
inline void f设置顶点(const t顶点 顶点)
{
	v图形设备->SetStreamSource (0, 顶点, 0, sizeof(S三维顶点));
};
//光和材质
#define f设置光(索引,光) v图形设备->SetLight(索引,光)
#define f光开关(索引,开关) v图形设备->LightEnable(索引,开关)
inline void f设置材质(const t材质 &p材质)
{
	v图形设备->SetMaterial(&p材质);
};
inline void f设置颜色(const t颜色 &p颜色) {
	v2d材质.Diffuse.a = p颜色.a;
	v2d材质.Emissive.r = p颜色.r;
	v2d材质.Emissive.g = p颜色.g;
	v2d材质.Emissive.b = p颜色.b;
	v图形设备->SetMaterial(&v2d材质);
};
inline void f设置透明度(const float &a) {
	f设置颜色(t颜色(1,1,1,a));
};
t材质 f填充材质 (const t颜色 &漫射颜色, const t颜色 &环境颜色, const t颜色 &镜面颜色, const t颜色 &放射颜色, const float &镜面高光);
t材质 f填充材质 (const t颜色 &颜色, const bool &环境模式 = false);
//纹理
inline bool f添加纹理 (t纹理 &接受纹理地址的指针, const wchar_t *纹理的文件名)
{
	if (FAILED(D3DXCreateTextureFromFile (v图形设备, 纹理的文件名, &接受纹理地址的指针)))
		throw;
	return true;
};
bool f设置纹理 (t纹理 &需要画出的纹理);
inline void f设置纹理图层状态 (const t纹理图层状态类型 &p参数, const int &p值)
{
	v图形设备->SetTextureStageState (0, p参数, p值);
};
void f纹理开关 (const bool &开关);
inline void f纹理开关_开()
{
	f设置纹理图层状态(D3DTSS_COLOROP, D3DTOP_MODULATE);
	f设置纹理图层状态(D3DTSS_ALPHAOP, D3DTOP_MODULATE);
};
inline void f纹理开关_关()
{
	f设置纹理图层状态(D3DTSS_COLOROP, D3DTOP_SELECTARG2);
	f设置纹理图层状态(D3DTSS_ALPHAOP, D3DTOP_SELECTARG2);
};
//世界矩阵
#define f设置世界矩阵变换(世界矩阵) v图形设备->SetTransform(D3DTS_WORLD,世界矩阵)
void f设置世界矩阵 (t向量3*const&平移, t向量3*const&旋转, t向量3*const&缩放);
void f复位世界矩阵 ();
//视图矩阵
void f复位视图矩阵 ();
//混合
void f混合 (E混合模式);
inline void f混合_正常 () {
	f设置渲染状态 (D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
};
inline void f混合_叠加 () {
	f设置渲染状态 (D3DRS_DESTBLEND, D3DBLEND_DESTALPHA);
};
//超级分割线====================================================================================================
}}}	//命名空间结束
#endif