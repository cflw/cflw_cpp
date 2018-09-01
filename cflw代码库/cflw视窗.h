#pragma once
#include <string>
#include <Windows.h>
#include <mmstream.h>
#include <imm.h>
#include <wrl.h>
#include <ShObjIdl.h>
#pragma comment(lib, "winmm.lib")
#pragma comment(lib, "imm32.lib")
#undef min
#undef max
namespace cflw::视窗 {
using Microsoft::WRL::ComPtr;
//==============================================================================
// windef.h
//==============================================================================
typedef DWORD t双字;	//行:152
typedef BYTE t字节;	//行:154
typedef WORD t字;	//行:155
typedef UINT t正整数;//行:173
typedef HWND t窗口句柄, tp窗口;	//行:208
typedef HHOOK t挂钩句柄, tp挂钩;	//行:209
typedef HBITMAP t位图句柄, tp位图;	//行:260
typedef HBRUSH t画刷句柄, tp画刷;	//行:261
typedef HFONT t字体句柄, tp字体;	//行:273
typedef HICON t图标句柄, tp图标;	//行:275
typedef HMENU t菜单句柄, tp菜单;	//行:277
typedef HINSTANCE t实例句柄, tp实例;//行:280
typedef HPEN t笔句柄, tp笔;	//行:284
typedef HCURSOR t光标句柄, tp光标;	//行:308
typedef tagRECT t矩形;	//行:319-325
typedef tagPOINT t点;	//行:339-343
typedef tagSIZE t大小;	//行:351-355
//==============================================================================
// winnt.h
//==============================================================================
typedef HANDLE t句柄, th;	//行:515
typedef HRESULT t结果;	//行:542
typedef LARGE_INTEGER t大整数;	//行:674-688
typedef ULARGE_INTEGER t无符号大整数;	//行:692-706
enum class E通用权限: unsigned long {	//行:6510-6513
	e读 = GENERIC_READ,
	e写 = GENERIC_WRITE,
	e执行 = GENERIC_EXECUTE,
	e全部 = GENERIC_ALL
};
//==============================================================================
// winbase.h
//==============================================================================
inline void *f内存移动(void *const&目标, void *const&源, const size_t &大小){
	return MoveMemory (目标, 源, 大小);
};	//行:103
inline void *f内存复制(void *const&目标, void *const&源, const size_t &大小){
	return CopyMemory (目标, 源, 大小);
};	//行:104
inline void *f内存填充(void *const&目标, const int &值, const size_t &大小){
	return FillMemory (目标, 值, 大小);
};	//行:105
inline void *f内存清空(void *const&目标, const size_t &大小){
	return ZeroMemory (目标, 大小);
};	//行:106
inline DWORD f设置文件指针(HANDLE 文件, LONG 移动距离, PLONG 移动高度距离, DWORD 移动方式){
	return SetFilePointer(文件, 移动距离, 移动高度距离, 移动方式);
};	//行:4984-4992
inline BOOL f关闭句柄(HANDLE 句柄){
	return CloseHandle(句柄);
};	//行:5068
//==============================================================================
// winuser.h
//==============================================================================
typedef WNDPROC t窗口过程;//行:62
enum class E窗口消息 : unsigned int {	//行:1723
	e无 = WM_NULL,
	e创建 = WM_CREATE,
	e销毁 = WM_DESTROY,
	e移动 = WM_MOVE,
	e大小 = WM_SIZE,
	e活动 = WM_ACTIVATE,
	e设置焦点 = WM_SETFOCUS,
	e自定义 = WM_USER
};
enum class E窗口样式 : unsigned long {
	e层叠 = WS_OVERLAPPED,	//产生一个层叠的窗口。一个层叠的窗口有一个标题条和一个边框。与WS_TILED风格相同
	e弹出 = WS_POPUP,	//创建一个弹出式窗口。该风格不能与WS_CHLD风格同时使用
	e子 = WS_CHILD,	//创建一个子窗口。这个风格不能与WS_POPUP风格合用
	e最大化 = WS_MINIMIZE,	//创建一个初始状态为最大化状态的窗口
	e可见 = WS_VISIBLE,	//创建一个初始状态为可见的窗口
	e禁止 = WS_DISABLED	//创建一个初始状态为禁止的子窗口
};
enum class E文本格式 : unsigned long {	//行:6594
	e顶部 = DT_TOP,
	e居左 = DT_LEFT,
	e水平居中 = DT_CENTER,
	e居右 = DT_RIGHT,
	e垂直居中 = DT_VCENTER,
	e底部 = DT_BOTTOM,
	e自动换行 = DT_WORDBREAK,
	e单行 = DT_SINGLELINE,
	e扩展制表符 = DT_EXPANDTABS,
	e设置制表 = DT_TABSTOP,
	e不裁剪 = DT_NOCLIP,
	e包含外部标头 = DT_EXTERNALLEADING,
	e确定矩形 = DT_CALCRECT,
	e关闭前缀 = DT_NOPREFIX,
	e系统字体计算 = DT_INTERNAL
};
//==============================================================================
// winerror.h
//==============================================================================
inline bool fi成功(HRESULT a结果) {
	return a结果 >= 0;
};	//行:23775
inline bool fi失败(HRESULT a结果) {
	return a结果 < 0;
};	//行:23775
//==============================================================================
// 使用类/结构
//==============================================================================
//计时器
class C计时器 {
public:
	C计时器();
	void f重置(float);	//单位:秒
	int f滴答();
	int f单次滴答();
	int f游戏滴答();	//如果计数大于1则保留1次到下次滴答
	int fg次数();		//得到上次滴答的次数
	float fg用时();	//当前成功滴答的实际过去时间
private:
	void f计时();
	float v时间;
	float v计时;
	float v间隔;	//滴答间隔
	float v上次滴答;	//上次成功滴答的时间
	float v这次滴答;
	int v次数;
};
//关键段
class C关键段 {
public:
	C关键段();
	~C关键段();
	void f进入();
	void f离开();
private:
	CRITICAL_SECTION m关键段;
};
//==============================================================================
// 风格&尺寸&坐标
//==============================================================================
//窗口风格
struct S窗口风格 {
	DWORD m一般风格, m扩展风格;
	operator DWORD &();
	//一般风格
	void fs层叠(bool);	//有一个标题栏和边框
	void fs标题(bool);
	void fs菜单(bool);
	void fs最按钮(bool 大, bool 小);	//最大化最小化按钮
	void fs滚动条(bool 垂直, bool 水平);
	//扩展风格
	//组合风格
	void fs层叠窗口();
	void fs弹出窗口();
	void fs子窗口();
	void fs游戏窗口();
};
//客户区尺寸
struct S客户区尺寸 {
	RECT m矩形;
	S客户区尺寸(long, long);
	S客户区尺寸(RECT);
	static S客户区尺寸 fc窗口(HWND);
	static S客户区尺寸 fc尺寸风格(long x, long y, DWORD 风格, DWORD 风格ex = 0);//计算客户区尺寸,变量用作CreateWindow的参数
	long fg宽() const;
	long fg高() const;
	float f除以尺寸(long, long) const;	//原宽和高除以参数的宽和高,取最小值
};
//坐标计算
class C屏幕坐标到客户区坐标计算 {
public:
	C屏幕坐标到客户区坐标计算(HWND);
	long f窗口坐标xl(long) const;
	long f窗口坐标yl(long) const;
	float f窗口坐标xf(float) const;
	float f窗口坐标yf(float) const;
	long f直角坐标xl(long) const;
	long f直角坐标yl(long) const;
	float f直角坐标xf(float) const;
	float f直角坐标yf(float) const;
	RECT m客户区, m窗口区;
	long m边框;
};
//==============================================================================
// 任务栏按钮
//==============================================================================
class C任务栏按钮 {
public:
	enum E状态 {
		e无,
		e不确定,
		e正常,
		e错误,
		e暂停,
	};
	static const TBPFLAG c状态映射[];
	void f初始化(HWND);
	void fs状态(int);
	void fs进度(double);
	TBPFLAG fg状态标记() const;
	void f刷新();
	static UINT f注册消息();
private:
	HWND m窗口 = nullptr;
	ComPtr<ITaskbarList3> m任务栏;
	int m状态 = 0;
	double m进度 = 0;
};
//==============================================================================
// 环境
//==============================================================================
class C环境 {
public:
	static SYSTEM_INFO &fg系统信息();
	static std::wstring fg执行程序目录();
	static std::wstring fg执行程序路径();
	static std::wstring fg工作目录();
	static int fg处理器数量();
	static UINT fg每英寸点数();
	static float fg缩放();
};
//==============================================================================
// 输入法
//==============================================================================
class C输入法开关 {
public:
	void f初始化(HWND);
	void f开关(bool);
	void f开启();
	void f关闭();
private:
	HWND m窗口 = nullptr;
	HIMC m输入法 = nullptr;
};
}	//namespace cflw::视窗