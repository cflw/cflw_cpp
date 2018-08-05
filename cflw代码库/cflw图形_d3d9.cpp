//--------------------------------------------------------------------------------
//头文件
//--------------------------------------------------------------------------------
#include <d3dx9.h>
#include "cflw图形_d3d9.h"
#include "cflw数学.h"
namespace cflw {
namespace 图形 {
namespace d3d9 {
//--------------------------------------------------------------------------------
//DirectX
//--------------------------------------------------------------------------------
t接口指针 v图形接口 = nullptr;	//Direct3D9接口
t设备指针 v图形设备 = nullptr;	//Direct3D9设备
//--------------------------------------------------------------------------------
//全局变量
//--------------------------------------------------------------------------------
DWORD fvf三维顶点 = (D3DFVF_XYZ | D3DFVF_TEX1);
E图元类型 v画出模式 = c图元类型_连续三角形;
t矩阵 v当前世界矩阵;
t矩阵 v当前视图矩阵;
const t颜色 c白色(1,1,1,1);
const t颜色 c红色(1,0,0,1);
const t颜色 c绿色(0,1,0,1);
const t颜色 c蓝色(0,0,1,1);
const t颜色 c无色(1,1,1,0);
const t材质 c白色材质 = f填充材质 (t颜色(1,1,1,1));
const t材质 c小透明白色材质 = f填充材质 (t颜色(1,1,1,0.8f));
const t材质 c半透明白色材质 = f填充材质 (t颜色(1,1,1,0.5f));
const t材质 c大透明白色材质 = f填充材质 (t颜色(1,1,1,0.3f));
const t材质 c透明材质 = f填充材质 (t颜色(1,1,1,0));
const t材质 c红色材质 = f填充材质 (t颜色(1,0,0,1));
const t材质 c绿色材质 = f填充材质 (t颜色(0,1,0,1));
const t材质 c蓝色材质 = f填充材质 (t颜色(0,0,1,1));
t光 v屏幕光;	//平行光,直射到屏幕上
t相机 v屏幕相机;	//对准整个窗口屏幕
t纹理 v当前设置纹理;
t材质 v2d材质;	//用于2d图像的材质
t向量2 v屏幕尺寸;
C视口 v屏幕视口;	//对准整个窗口屏幕
//辅助图形
bool v辅助图形载入完毕 = false;
t顶点 v矩形;
C投影矩阵 v默认投影;
视窗::C关键段 v关键段;
//--------------------------------------------------------------------------------
//简单结构
//--------------------------------------------------------------------------------
S矩形::S矩形(): v坐标(0, 0), v半尺寸(0, 0) {};
S矩形::S矩形(const t向量2 &p坐标, const t向量2 &p半尺寸): v坐标(p坐标), v半尺寸(p半尺寸){};
S矩形::S矩形(const 视窗::t矩形 &p矩形): 
	v坐标((p矩形.right + p矩形.left) / 2.f, (p矩形.top + p矩形.bottom) / 2.f),
	v半尺寸(abs(p矩形.right - p矩形.left) / 2.f, abs(p矩形.top - p矩形.bottom) / 2.f){};
S矩形::S矩形(const float &左, const float &上, const float &右, const float &下):
	v坐标((右+左)/2.f, (上+下)/2.f), v半尺寸(abs(右-左)/2.f, abs(上-下)/2.f){};
//--------------------------------------------------------------------------------
//顶点结构
//--------------------------------------------------------------------------------
//顶点格式的构造函数
S三维顶点::S三维顶点 (void):
	x (0), y (0), z (0), u (0), v (0)
{};
S三维顶点::S三维顶点 (const float &_x, const float &_y, const float &_u, const float &_v):
	x (_x), y (_y) ,z (0), u (_u), v (_v)
{};
S三维顶点::S三维顶点 (const float &_x, const float &_y, const float &_z, const float &_u, const float &_v):
	x (_x), y (_y) ,z (_z), u (_u), v (_v)
{};
//--------------------------------------------------------------------------------
//动画类
//--------------------------------------------------------------------------------
//图形类的函数
C图形::C图形 (void):
	v纹理 (0),
	v顶点 (0),
	v材质 ()
{};
void C图形::f显示2d ()
{
	fg世界矩阵2().f矩阵应用();
	f绘制准备 ();
	f绘制图元 ();
};
void C图形::f显示3d ()
{
	fg世界矩阵3().f矩阵应用();
	f绘制准备 ();
	f绘制图元 ();
};
void C图形::f绘制准备 ()
{	//设置顶点纹理,材质
	f设置材质 (v材质);
	f设置纹理 (v纹理);
	f设置流源 (v顶点);
};
//--------------------------------------------------------------------------------
//世界矩阵3d
//--------------------------------------------------------------------------------
C世界矩阵3d::C世界矩阵3d ():
	v平移 (0, 0, 0),
	v旋转 (0, 0, 0),
	v缩放 (1, 1, 1)
{};
C世界矩阵3d::C世界矩阵3d (const t向量3 &p平移, const t向量3 &p旋转, const t向量3 &p缩放):
	v平移 (p平移),
	v旋转 (p旋转),
	v缩放 (p缩放)
{};
void C世界矩阵3d::f矩阵应用 ()
{
	t矩阵 v矩阵;
	t四元数 v四元数;
	v图形设备->SetTransform(D3DTS_WORLD, D3DXMatrixTransformation(&v矩阵, nullptr, nullptr, &v缩放, nullptr, 
		D3DXQuaternionRotationYawPitchRoll(&v四元数, v旋转.y, v旋转.x, v旋转.z), &v平移));
}
void C世界矩阵3d::f矩阵应用2 ()
{
	fg世界矩阵2().f矩阵应用();
};
C世界矩阵3d& C世界矩阵3d::f矩阵复位 ()
{
	v平移 = t向量3 (0, 0, 0);
	v旋转 = t向量3 (0, 0, 0);
	v缩放 = t向量3 (1, 1, 1);
	return *this;
};
C世界矩阵3d& C世界矩阵3d::f矩阵旋转 (const float &p)
{
	数学::S向量2 v(v旋转.x, v旋转.y);
	v.fs旋转r(p);
	v旋转.x = v.x;
	v旋转.y = v.y;
	return *this;
};
t世界矩阵2 C世界矩阵3d::fg世界矩阵2 ()
{
	return t世界矩阵2((t向量2)v平移, v旋转.z, (t向量2)v缩放);
};
//--------------------------------------------------------------------------------
//世界矩阵2d
//--------------------------------------------------------------------------------
C世界矩阵2d::C世界矩阵2d ():
	v平移 (0, 0),
	v旋转 (0),
	v缩放 (1, 1)
{};
C世界矩阵2d::C世界矩阵2d (const t向量2 &p平移, const float &p旋转, const t向量2 &p缩放):
	v平移 (p平移),
	v旋转 (p旋转),
	v缩放 (p缩放)
{};
void C世界矩阵2d::f矩阵应用 ()
{
	v图形设备->SetTransform(D3DTS_WORLD, D3DXMatrixTransformation2D (&v当前世界矩阵, 0, 0, &v缩放, 0, v旋转, &v平移));
};
C世界矩阵2d& C世界矩阵2d::f矩阵复位 ()
{
	v平移 = t向量2 (0, 0);
	v旋转 = 0;
	v缩放 = t向量2 (1, 1);
	return *this;
};
C世界矩阵2d& C世界矩阵2d::f矩阵反向 ()
{
	v平移 = -v平移;
	return *this;
};
//--------------------------------------------------------------------------------
//相机类
//--------------------------------------------------------------------------------
C相机::C相机 ():
	v位置 (0, 0, 1),
	v看向 (0, 0, -1),
	v上方 (0, 1, 0)
{};
C相机::C相机 (const t向量3 &p位置, const t向量3 &p看向, const t向量3 &p上方):
	v位置 (p位置),
	v看向 (p看向),
	v上方 (p上方)
{};
void C相机::f应用 ()
{
	v图形设备->SetTransform(D3DTS_VIEW, D3DXMatrixLookAtRH(&v当前视图矩阵, &v位置, &v看向, &v上方));
};
C相机& C相机::f复位 ()
{
	v位置 = t向量3 (0, 0, 1);
	v看向 = t向量3 (0, 0, -1);
	v上方 = t向量3 (0, 1, 0);
	return *this;
};
C相机& C相机::f平移 (const t向量3 &p)
{
	v位置 += p;
	v看向 += p;
	return *this;
};
//--------------------------------------------------------------------------------
//投影矩阵
//--------------------------------------------------------------------------------
C投影矩阵::C投影矩阵():v视角((float)数学::π / 2),v宽(64),v高(48),v近z(0.1f),v远z(1000.f){};
void C投影矩阵::f应用2d()
{
	D3DXMATRIX v矩阵;
	v图形设备->SetTransform (D3DTS_PROJECTION, D3DXMatrixPerspectiveRH(&v矩阵, v宽, v高, v近z, v远z));
};
void C投影矩阵::f应用3d()
{
	D3DXMATRIX v矩阵;
	v图形设备->SetTransform (D3DTS_PROJECTION, D3DXMatrixPerspectiveFovRH(&v矩阵, v视角, 1, v近z, v远z));
};
//--------------------------------------------------------------------------------
//视口
//--------------------------------------------------------------------------------
C视口::C视口():v左上(),v右下(){};
void C视口::f应用 ()
{
	t向量2 v半屏幕尺寸(v屏幕尺寸 / 2.f);
	D3DVIEWPORT9 v视口 = {(DWORD)(v左上.x + v半屏幕尺寸.x), (DWORD)(v半屏幕尺寸.y - v左上.y), (DWORD)(v右下.x - v左上.x), (DWORD)(v左上.y - v右下.y), 0, 1};
	v图形设备->SetViewport (&v视口);
};
void C视口::fs (const float &p左, const float &p上, const float &p右, const float &p下)
{
	v左上.x = p左;
	v左上.y = p上;
	v右下.x = p右;
	v右下.y = p下;
};
//--------------------------------------------------------------------------------
//顶点制造机
//--------------------------------------------------------------------------------
//矩形
C顶点制造机_矩形::C顶点制造机_矩形 ():
	v纹理尺寸(256, 256), 
	v矩形坐标(128, 128), 
	v矩形半尺寸(128, 128),
	v矩形扩张(0)
{};
void C顶点制造机_矩形::f设置矩形 (const float &左, const float &上, const float &右, const float &下) {
	v矩形坐标.x = (左 + 右) / 2;
	v矩形坐标.y = (上 + 下) / 2;
	v矩形半尺寸.x = (右 - 左) / 2;
	v矩形半尺寸.y = (下 - 上) / 2;
};
bool C顶点制造机_矩形::f创建顶点 (t顶点 &p) {
	//计算纹理映射坐标
	const float v纹理l = (v矩形坐标.x - v矩形半尺寸.x - v矩形扩张) / v纹理尺寸.x;
	const float v纹理r = (v矩形坐标.x + v矩形半尺寸.x + v矩形扩张) / v纹理尺寸.x;
	const float v纹理t = (v矩形坐标.y - v矩形半尺寸.y - v矩形扩张) / v纹理尺寸.y;
	const float v纹理b = (v矩形坐标.y + v矩形半尺寸.y + v矩形扩张) / v纹理尺寸.y;
	//计算纹理顶点坐标
	const float v顶点l = -v矩形半尺寸.x;
	const float v顶点r =  v矩形半尺寸.x;
	const float v顶点t =  v矩形半尺寸.y;
	const float v顶点b = -v矩形半尺寸.y;
	//开始填充
	if(FAILED(f创建顶点缓冲 (&p, 4)))
		return false;
	t三维顶点 *v顶点;
	C顶点锁定机 v锁定;
	v锁定.f锁定 (p, v顶点);
	v顶点[0] = t三维顶点 (v顶点l, v顶点t, v纹理l, v纹理t);	//左上角
	v顶点[1] = t三维顶点 (v顶点r, v顶点t, v纹理r, v纹理t);	//右上角
	v顶点[2] = t三维顶点 (v顶点l, v顶点b, v纹理l, v纹理b);	//左下角
	v顶点[3] = t三维顶点 (v顶点r, v顶点b, v纹理r, v纹理b);	//右下角
	v锁定.f解锁 ();
	return true;
};
//矩形ex
C顶点制造机_矩形ex::C顶点制造机_矩形ex ():
	C顶点制造机_矩形(),
	v平移 (0, 0),
	v旋转 (0),
	v缩放 (1, 1)
{};
void C顶点制造机_矩形ex::f设置显示矩形 (const float &左, const float &上, const float &右, const float &下) {
	v平移.x = (左 + 右) / 2;
	v平移.y = (上 + 下) / 2;
	const t向量2 v半尺寸 = t向量2 ((右 - 左) / 2, (上 - 下) / 2);
	v缩放.x = v半尺寸.x / v矩形半尺寸.x;
	v缩放.y = v半尺寸.y / v矩形半尺寸.y;
};
bool C顶点制造机_矩形ex::f创建顶点ex (t顶点 &p) {
	//计算纹理映射坐标
	const float v纹理l = (v矩形坐标.x - v矩形半尺寸.x - v矩形扩张) / v纹理尺寸.x;
	const float v纹理r = (v矩形坐标.x + v矩形半尺寸.x + v矩形扩张) / v纹理尺寸.x;
	const float v纹理t = (v矩形坐标.y - v矩形半尺寸.y - v矩形扩张) / v纹理尺寸.y;
	const float v纹理b = (v矩形坐标.y + v矩形半尺寸.y + v矩形扩张) / v纹理尺寸.y;
	//计算顶点坐标
	const float v顶点l = (-v矩形半尺寸.x + v平移.x) * v缩放.x;
	const float v顶点r = ( v矩形半尺寸.x + v平移.x) * v缩放.x;
	const float v顶点t = ( v矩形半尺寸.y + v平移.y) * v缩放.y;
	const float v顶点b = (-v矩形半尺寸.y + v平移.y) * v缩放.y;
	//开始填充
	t三维顶点 *v顶点;
	数学::S向量2 v顶点坐标;
	if(视窗::f失败(f创建顶点缓冲(&p, 4)))
		return false;
	C顶点锁定机 v锁定;
	v锁定.f锁定(p, v顶点);
	//左上角
	v顶点坐标.x = v顶点l;
	v顶点坐标.y = v顶点t;
	v顶点坐标.fs旋转r(v旋转);
	v顶点[0] = t三维顶点(v顶点坐标.x, v顶点坐标.y, v纹理l, v纹理t);
	//右上角
	v顶点坐标.x = v顶点r;
	v顶点坐标.y = v顶点t;
	v顶点坐标.fs旋转r(v旋转);
	v顶点[1] = t三维顶点(v顶点坐标.x, v顶点坐标.y, v纹理r, v纹理t);
	//左下角
	v顶点坐标.x = v顶点l;
	v顶点坐标.y = v顶点b;
	v顶点坐标.fs旋转r(v旋转);
	v顶点[2] = t三维顶点(v顶点坐标.x, v顶点坐标.y, v纹理l, v纹理b);
	//右下角
	v顶点坐标.x = v顶点r;
	v顶点坐标.y = v顶点b;
	v顶点坐标.fs旋转r(v旋转);
	v顶点[3] = t三维顶点(v顶点坐标.x, v顶点坐标.y, v纹理r, v纹理b);	
	v锁定.f解锁();
	return true;
};
//--------------------------------------------------------------------------------
//顶点锁定机
//--------------------------------------------------------------------------------
C顶点锁定机::C顶点锁定机():v锁定顶点(nullptr){};
C顶点锁定机::~C顶点锁定机 (){f解锁();};
bool C顶点锁定机::f锁定_ (const t顶点 &p顶点指针, void **p修改指针)
{
	if (v锁定顶点 != nullptr)
		return false;
	v锁定顶点 = p顶点指针;
	v修改顶点 = p修改指针;
	v关键段.f进入();
	HRESULT hr = v锁定顶点->Lock(0, 0, v修改顶点, 0);
	v关键段.f离开();
	if(FAILED(hr))
		return false;	//无法锁定
	return true;
};
bool C顶点锁定机::f解锁 ()
{
	if (v锁定顶点 == nullptr)
		return false;
	v锁定顶点->Unlock ();
	v锁定顶点 = nullptr;
	*v修改顶点 = nullptr;
	return true;
};
//--------------------------------------------------------------------------------
//文本制造机
//--------------------------------------------------------------------------------
C文本制造机::C文本制造机 (): 高(0), 宽(0), 粗(0), 厚(0), 斜体(FALSE), 下划线(FALSE), 删除线(FALSE)
{
	f设置字体 (L"微软雅黑");
};
bool C文本制造机::f创建文本 (wchar_t* 文本, t网格指针& 网格)
{
	if (文本 == nullptr)	//空指针
		return false;
	辅助::f释放 (网格);	//清空网格资源避免内存浪费
	HDC hdc = CreateCompatibleDC( NULL );
	HFONT hFont = CreateFontW (高, 宽, 0, 0, 粗, 斜体, 下划线, 删除线, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS,
				CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, 字体);
	HFONT hFontOld = (HFONT)SelectObject(hdc, hFont);	//替换字体
	D3DXCreateTextW(v图形设备, hdc, 文本, 0.01f, 厚, &网格, nullptr, nullptr);
	SelectObject(hdc, hFontOld);	//恢复字体
	DeleteObject( hFont );
	DeleteDC( hdc );
	return true;
};
//--------------------------------------------------------------------------------
//其他函数
//--------------------------------------------------------------------------------
bool f创建设备 (const HWND &窗口句柄)
{
	v图形接口 = Direct3DCreate9(D3D_SDK_VERSION);
	if (v图形接口 == nullptr)
		return false;
	D3DPRESENT_PARAMETERS d3dpp; 
	ZeroMemory(&d3dpp, sizeof(d3dpp));
	d3dpp.Windowed = TRUE;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;
	d3dpp.EnableAutoDepthStencil = TRUE;
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;
	if( FAILED(v图形接口->CreateDevice (D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, 窗口句柄, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dpp, &v图形设备)))
	{
		return false;
	};
	return true;
};
void f快速初始化 ()
{
	// 关闭挑选
	v图形设备->SetRenderState( D3DRS_CULLMODE, D3DCULL_NONE );
	// 开启照明
	v图形设备->SetRenderState( D3DRS_LIGHTING, TRUE );
	// 开启z缓冲
	v图形设备->SetRenderState( D3DRS_ZENABLE, TRUE );
	// 开启帧alpha
	v图形设备->SetRenderState( D3DRS_ALPHABLENDENABLE, TRUE);
	v图形设备->SetRenderState( D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	v图形设备->SetRenderState( D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	//设置屏幕光
	v屏幕光.Type = (t光类型)(int)c光类型_平行光;
	v屏幕光.Diffuse = v屏幕光.Ambient = v屏幕光.Specular = t颜色 (1,1,1,1);
	v屏幕光.Direction = t向量3 (0,0,-1);
	v图形设备->SetLight (0, &v屏幕光);
	v图形设备->LightEnable(0, TRUE);
	//设置视口
	v屏幕视口.fs (-320, 240, 320, -240);
	//纹理
	v图形设备->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE );
	v图形设备->SetTextureStageState(0, D3DTSS_COLORARG2, D3DTA_DIFFUSE );
	v图形设备->SetTextureStageState(0, D3DTSS_COLOROP,   D3DTOP_MODULATE);
	v图形设备->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	v图形设备->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_DIFFUSE);
	v图形设备->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
	//设置纹理过滤模式
	v图形设备->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
};
void f图形复位 ()
{
	//顶点
	v图形设备->SetFVF( fvf三维顶点 );
	//矩阵变换
	C世界矩阵3d().f矩阵应用();
	v屏幕相机.f应用 ();
	v默认投影.f应用3d ();
	//灯光
	v图形设备->SetLight (0, &v屏幕光);
	v图形设备->SetRenderState( D3DRS_LIGHTING, TRUE );
	v图形设备->LightEnable(0, TRUE);
	//材质
	v图形设备->SetMaterial (&c白色材质);
	//纹理
	v图形设备->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE );
	v图形设备->SetTextureStageState(0, D3DTSS_COLORARG2, D3DTA_DIFFUSE );
	v图形设备->SetTextureStageState(0, D3DTSS_COLOROP,   D3DTOP_MODULATE);
	v图形设备->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	v图形设备->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_DIFFUSE);
	v图形设备->SetTextureStageState(0, D3DTSS_ALPHAOP,   D3DTOP_MODULATE);
	//视口
	v屏幕视口.f应用 ();
};
void f销毁设备 ()
{
	辅助::f释放 (v图形设备);
	辅助::f释放 (v图形接口);
};
//
void f载入附加图形 ()
{
	if (v辅助图形载入完毕)
		return;
	t三维顶点 *v顶点;
	C顶点锁定机 v锁定;
	//矩形
	f创建顶点缓冲 (&v矩形, 4);
	v锁定.f锁定 (v矩形, v顶点);
	v顶点[0] = t三维顶点 (-1, 1, 0, 0);
	v顶点[1] = t三维顶点 (1, 1, 1, 0);
	v顶点[2] = t三维顶点 (-1, -1, 0, 1);
	v顶点[3] = t三维顶点 (1, -1, 1, 1);
	v锁定.f解锁 ();
	//结束
	v辅助图形载入完毕 = true;
};
void f画_矩形 (const t矩形 &p矩形)
{
	if (!v辅助图形载入完毕)
		return;
	t世界矩阵2 v矩阵;
	v矩阵.v平移 = p矩形.v坐标;
	v矩阵.v缩放 = p矩形.v半尺寸;
	v矩阵.f矩阵应用();
	f设置顶点 (v矩形);
	f绘制图元 ();
};
//--------------------------------------------------------------------------------
//其他函数
//--------------------------------------------------------------------------------
视窗::t矩形 f到窗口坐标 (const 视窗::t矩形 &rect) {
	//请确定游戏分辨率是640x480才能用此函数
	视窗::t矩形 v = rect;
	v.left = 320 + rect.left;
	v.right = 320 + rect.right;
	v.top = 240 - rect.top;
	v.bottom = 240 - rect.bottom;
	return v;
};
视窗::t矩形 f矩形 (const t向量2 &p坐标, const t向量2 &p半尺寸) {
	视窗::t矩形 v矩形;
	v矩形.left   = (long)(p坐标.x - p半尺寸.x);
	v矩形.right  = (long)(p坐标.x + p半尺寸.x);
	v矩形.top    = (long)(p坐标.y + p半尺寸.y);
	v矩形.bottom = (long)(p坐标.y - p半尺寸.y);
	return v矩形;
};
t材质 f材质颜色渐变 (const t材质 &p材质, const t颜色 &p颜色, const float &p渐变值) {
	t材质 v材质 = p材质;
	v材质.Diffuse.a = 数学::f倍数渐变<float>(v材质.Diffuse.a, p颜色.a, p渐变值);
	v材质.Emissive.r = 数学::f倍数渐变<float>(v材质.Emissive.r, p颜色.r, p渐变值);
	v材质.Emissive.g = 数学::f倍数渐变<float>(v材质.Emissive.g, p颜色.g, p渐变值);
	v材质.Emissive.b = 数学::f倍数渐变<float>(v材质.Emissive.b, p颜色.b, p渐变值);
	return v材质;
};
t矩形 f矩形形状渐变 (const t矩形 &p源, const t矩形 &p目标, const float &p渐变倍数, const float &p最大值) {
	t矩形 v矩形 = p源;
	v矩形.v坐标.x   = 数学::f倍数渐变<float>(v矩形.v坐标.x,   p目标.v坐标.x,   p渐变倍数, 0, p最大值);
	v矩形.v坐标.y   = 数学::f倍数渐变<float>(v矩形.v坐标.y,   p目标.v坐标.y,   p渐变倍数, 0, p最大值);
	v矩形.v半尺寸.x = 数学::f倍数渐变<float>(v矩形.v半尺寸.x, p目标.v半尺寸.x, p渐变倍数, 0, p最大值);
	v矩形.v半尺寸.y = 数学::f倍数渐变<float>(v矩形.v半尺寸.y, p目标.v半尺寸.y, p渐变倍数, 0, p最大值);
	return v矩形;
};
//--------------------------------------------------------------------------------
//绘制
//--------------------------------------------------------------------------------

//--------------------------------------------------------------------------------
//顶点
//--------------------------------------------------------------------------------
HRESULT f创建顶点缓冲 (t顶点 *p顶点指针, const int &p顶点数量)
{
	HRESULT hr;
	if(FAILED(hr = v图形设备 -> CreateVertexBuffer(p顶点数量 * sizeof(S三维顶点), 0 , fvf三维顶点, D3DPOOL_DEFAULT, p顶点指针, NULL)))
		return hr;
	return hr;
};
//--------------------------------------------------------------------------------
//光和材质
//--------------------------------------------------------------------------------
t材质 f填充材质 (const t颜色 &pd, const t颜色 &pa, const t颜色 &ps, const t颜色 &pe, const float &pp)
{
	t材质 v;
	v.Diffuse = pd;
	v.Ambient = pa;
	v.Specular = ps;
	v.Emissive = pe;
	v.Power = pp;
	return v;
};
t材质 f填充材质 (const t颜色 &pc, const bool &环境模式)
{
	t材质 v;
	if (环境模式)
	{
		v.Diffuse = v.Specular = v.Ambient = pc;
		v.Emissive = t颜色(0.0f, 0.0f, 0.0f, 0.0f);
	}
	else
	{	//发光
		v.Diffuse = v.Specular = v.Emissive = pc;
		v.Ambient = t颜色(0.0f, 0.0f, 0.0f, 0.0f);
	};
	v.Power = 0;
	return v;
};
//--------------------------------------------------------------------------------
//纹理
//--------------------------------------------------------------------------------
bool f设置纹理 (t纹理 &p纹理指针)
{
	if (p纹理指针 == v当前设置纹理)
		return false;
	else
	{
		v图形设备->SetTexture(0, p纹理指针);
		v当前设置纹理 = p纹理指针;
		return true;
	}
};
void f纹理开关 (const bool &开关)
{
	if (开关)
	{	//开
		f设置纹理图层状态( D3DTSS_COLOROP, D3DTOP_MODULATE);
		f设置纹理图层状态( D3DTSS_ALPHAOP, D3DTOP_MODULATE);
	}
	else
	{	//关
		f设置纹理图层状态( D3DTSS_COLOROP, D3DTOP_SELECTARG2);
		f设置纹理图层状态( D3DTSS_ALPHAOP, D3DTOP_SELECTARG2);
	}
};
//--------------------------------------------------------------------------------
//矩阵
//--------------------------------------------------------------------------------
void f设置世界矩阵 (t向量3*const&p平移, t向量3*const&p旋转, t向量3*const &p缩放)
{
	//计算旋转
	t四元数 v旋转;
	t四元数 *v旋转指针 = 0;
	if (p旋转 != 0)
	{
		v旋转 = t四元数 (p旋转->x, p旋转->y, p旋转->z, 1);
		v旋转指针 = &v旋转;
	};
	//变换
	v图形设备->SetTransform(D3DTS_WORLD, D3DXMatrixTransformation (&v当前世界矩阵, 0, 0, p缩放, 0, v旋转指针, p平移));
};
void f复位视图矩阵 ()
{
	v图形设备->SetTransform (D3DTS_VIEW, D3DXMatrixIdentity (&v当前视图矩阵));
};
void f复位世界矩阵 ()
{
	v图形设备->SetTransform (D3DTS_WORLD, D3DXMatrixIdentity(&v当前世界矩阵));
};
//--------------------------------------------------------------------------------
// 混合
//--------------------------------------------------------------------------------
void f混合 (E混合模式 p) {
	switch (p) {
	case e混合_正常:
		return f混合_正常();
	case e混合_叠加:
		return f混合_叠加();
	};
};
}}}	//命名空间结束