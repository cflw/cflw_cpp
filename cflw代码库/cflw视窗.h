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
inline void *f内存移动(void *a目标, void *a源, size_t a大小) {
	return memmove(a目标, a源, a大小);
};	//行:103
inline void *f内存复制(void *a目标, void *a源, size_t a大小) {
	return memcpy(a目标, a源, a大小);
};	//行:104
inline void *f内存填充(void *a目标, int a值, size_t a大小) {
	return memset(a目标, a值, a大小);
};	//行:105
inline void *f内存清空(void *a目标, size_t a大小) {
	return memset(a目标, 0, a大小);
};	//行:106
inline DWORD f设置文件指针(HANDLE a文件, LONG a移动距离, PLONG a移动高度距离, DWORD a移动方式) {
	return SetFilePointer(a文件, a移动距离, a移动高度距离, a移动方式);
};	//行:4984-4992
inline BOOL f关闭句柄(HANDLE a句柄) {
	return CloseHandle(a句柄);
};	//行:5068
//==============================================================================
// winuser.h
//==============================================================================
typedef WNDPROC tf窗口过程;//行:62
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
	e层叠 = WS_OVERLAPPED,	//产生一个层叠的窗口。一个层叠的窗口有一个标题条和一个边框。与WS_TILED样式相同
	e弹出 = WS_POPUP,	//创建一个弹出式窗口。该样式不能与WS_CHLD样式同时使用
	e子 = WS_CHILD,	//创建一个子窗口。这个样式不能与WS_POPUP样式合用
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
// winnls.h
//==============================================================================
inline std::wstring fg用户语言() {
	wchar_t v[LOCALE_NAME_MAX_LENGTH];
	GetUserDefaultLocaleName(v, LOCALE_NAME_MAX_LENGTH);
	return v;
}
//==============================================================================
// processenv.h
//==============================================================================
inline std::wstring fg环境变量(std::wstring_view a名称) {
	wchar_t v缓存[512] = {0};	//xp,2003环境变量最大32767字符,vista之后无限制.这里取1kb缓存
	GetEnvironmentVariableW(a名称.data(), v缓存, sizeof(v缓存));
	return v缓存;
}
inline HRESULT fs环境变量(std::wstring_view a名称, std::wstring_view a值) {
	SetEnvironmentVariableW(a名称.data(), a值.data());
	return GetLastError();
}
//==============================================================================
// 窗口控制&计算
//==============================================================================
void fs窗口大小(HWND, int 宽, int 高);
constexpr auto fs窗口标题 = SetWindowTextW;
std::pair<DWORD, DWORD> fg窗口样式(HWND);
//==============================================================================
// winerror.h
//==============================================================================
inline void f失败则抛出(HRESULT hr) {
	if (FAILED(hr)) {
		__debugbreak();
		throw hr;
	}
}
inline bool fi成功(HRESULT hr) {
	return SUCCEEDED(hr);
}
inline bool fi失败(HRESULT hr) {
	return FAILED(hr);
}
//==============================================================================
// COM组件对象模型
//==============================================================================
/*
template<typename t> concept T未知 = std::is_base_of<IUnknown, std::remove_pointer<t>::type>::value;
*/
template<typename t> void f释放(t &a对象) {
	static_assert(std::is_base_of<IUnknown, std::remove_pointer<t>::type>::value, "必需是IUnknown的派生类");
	if (a对象) {
		a对象->Release();
		a对象 = nullptr;
	}
}
template<typename t> void f释放1(t *a对象, int a1) {
	for (int i = 0; i < a1; ++i) {
		f释放(a对象[i]);
	}
}
template<typename t> void f释放2(t *a对象, int a1, int a2) {
	for (int i1 = 0; i1 < a1; ++i1) {
		f释放1(a对象[i1], a2);
	}
}
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
	float m时间;
	float m计时;
	float m间隔;	//滴答间隔
	float m上次滴答;	//上次成功滴答的时间
	float m这次滴答;
	int m次数;
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
// 样式&尺寸&坐标
//==============================================================================
//窗口样式
struct S窗口样式 {
	DWORD m一般, m扩展;
	static const S窗口样式 c层叠窗口, c弹出窗口, c子窗口, c游戏窗口;
	//一般样式
	void fs层叠(bool);	//有一个标题栏和边框
	void fs标题(bool);
	void fs菜单(bool);
	void fs最按钮(bool 大, bool 小);	//最大化最小化按钮
	void fs滚动条(bool 垂直, bool 水平);
	//扩展样式
};
//客户区尺寸
struct S客户区尺寸 {
	RECT m矩形;
	S客户区尺寸(long, long);
	S客户区尺寸(RECT);
	static S客户区尺寸 fc窗口(HWND);
	static S客户区尺寸 fc尺寸样式(long x, long y, DWORD 样式, DWORD 样式ex = 0);//计算客户区尺寸,变量用作CreateWindow的参数
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
	static SYSTEM_INFO fg系统信息();
	static std::wstring fg计算机名称();
	static std::wstring fg用户名称();
	static std::wstring fg执行程序目录();
	static std::wstring fg执行程序路径();
	static std::wstring fg工作目录();
	static int fg处理器数量();
	//分辨率
	static UINT fg显示精度();
	static UINT fg显示精度(HWND);
	static float fg缩放();
	static UINT f缩放到显示精度(float);
	static float f显示精度到缩放(UINT);
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
//==============================================================================
// 区域
//==============================================================================
class C语言区域 {
public:
	static LANGID f提取主语言标识(LANGID);
	static LANGID f提取子语言标识(LANGID);
	static LANGID f合并语言标识(LANGID 主, LANGID 子);
	static LANGID fg语言标识();
	static std::wstring fg语言名称();
};
}	//namespace cflw::视窗