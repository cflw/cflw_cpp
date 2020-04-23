#include <math.h>
#include <string.h>
#include <algorithm>
#include "cflw视窗.h"
namespace cflw::视窗 {
//==============================================================================
// 窗口控制
//==============================================================================
void fs窗口大小(HWND a窗口, int a宽, int a高) {
	RECT v矩形;
	GetWindowRect(a窗口, &v矩形);
	const auto[v样式, v样式ex] = fg窗口样式(a窗口);
	const S客户区尺寸 v尺寸 = S客户区尺寸::fc尺寸样式(a宽, a高, v样式, v样式ex);
	MoveWindow(a窗口, v矩形.left, v矩形.top, v尺寸.fg宽(), v尺寸.fg高(), false);
}
std::pair<DWORD, DWORD> fg窗口样式(HWND a窗口) {
	const DWORD v样式 = (DWORD)GetWindowLongW(a窗口, GWL_STYLE);
	const DWORD v样式ex = (DWORD)GetWindowLongW(a窗口, GWL_EXSTYLE);
	return {v样式, v样式ex};
}
//==============================================================================
// 计时器
//==============================================================================
C计时器::C计时器() :m时间(0), m计时(0), m间隔(0) {};
void C计时器::f重置(float p间隔) {
	m时间 = timeGetTime() / 1000.f;
	m计时 = 0;
	m间隔 = p间隔;
}
void C计时器::f计时() {
	float v上次时间 = m时间;
	m时间 = timeGetTime() / 1000.f;
	m计时 += m时间 - v上次时间;
}
int C计时器::fg次数() {
	return m次数;
}
float C计时器::fg用时() {
	return m这次滴答 - m上次滴答;
}
int C计时器::f滴答() {
	f计时();
	m次数 = (int)floor(m计时 / m间隔);
	if (m次数) {
		m上次滴答 = m这次滴答;
		m这次滴答 = m时间;
		m计时 -= m次数 * m间隔;
	}
	return m次数;
}
int C计时器::f单次滴答() {
	f计时();
	if (m计时 >= m间隔) {
		m计时 -= m间隔;
		m上次滴答 = m这次滴答;
		m这次滴答 = m时间;
		return m次数 = 1;
	} else {
		return m次数 = 0;
	}
}
int C计时器::f游戏滴答() {
	f计时();
	m次数 = (int)floor(m计时 / m间隔);
	if (m次数) {
		m计时 -= m次数 * m间隔;
		m上次滴答 = m这次滴答;
		m这次滴答 = m时间;
		if (m次数 >= 2) {
			m计时 += m间隔;
		}
	}
	return m次数;
}
//==============================================================================
// 关键段
//==============================================================================
C关键段::C关键段() {
	InitializeCriticalSection(&m关键段);
}
C关键段::~C关键段() {
	LeaveCriticalSection(&m关键段);
	DeleteCriticalSection(&m关键段);
}
void C关键段::f进入() {
	EnterCriticalSection(&m关键段);
}
void C关键段::f离开() {
	LeaveCriticalSection(&m关键段);
}
//==============================================================================
// 窗口样式
//==============================================================================
const S窗口样式 S窗口样式::c层叠窗口 = {WS_OVERLAPPEDWINDOW, WS_EX_OVERLAPPEDWINDOW};
const S窗口样式 S窗口样式::c弹出窗口 = {WS_POPUPWINDOW, 0};
const S窗口样式 S窗口样式::c子窗口 = {WS_CHILDWINDOW, 0};
const S窗口样式 S窗口样式::c游戏窗口 = {
	WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX,
	WS_EX_APPWINDOW | WS_EX_WINDOWEDGE
};
void S窗口样式::fs层叠(bool) {}
void S窗口样式::fs标题(bool) {}
void S窗口样式::fs菜单(bool) {}
void S窗口样式::fs最按钮(bool /*大*/, bool /*小*/) {}
void S窗口样式::fs滚动条(bool /*垂直*/, bool /*水平*/) {}
//==============================================================================
// 客户区尺寸
//==============================================================================
S客户区尺寸::S客户区尺寸(long a宽, long a高):
	m矩形{0, 0, a宽, a高} {
}
S客户区尺寸::S客户区尺寸(RECT p矩形):
	m矩形{p矩形} {
}
S客户区尺寸 S客户区尺寸::fc窗口(HWND p窗口) {
	RECT rc;
	GetClientRect(p窗口, &rc);
	return S客户区尺寸{rc.right - rc.left, rc.bottom - rc.top};
}
S客户区尺寸 S客户区尺寸::fc尺寸样式(long px, long py, DWORD p样式, DWORD p样式ex) {
	RECT v窗口尺寸 = {0, 0, px, py};
	AdjustWindowRectEx(&v窗口尺寸, p样式, FALSE, p样式ex);
	return S客户区尺寸{v窗口尺寸.right - v窗口尺寸.left, v窗口尺寸.bottom - v窗口尺寸.top};
}
long S客户区尺寸::fg宽() const {
	return m矩形.right - m矩形.left;
}
long S客户区尺寸::fg高() const {
	return m矩形.bottom - m矩形.top;
}
float S客户区尺寸::f除以尺寸(long a宽, long a高) const {
	const float v宽 = (float)fg宽() / (float)a宽;
	const float v高 = (float)fg高() / (float)a高;
	return std::min<float>(v宽, v高);
}
//==============================================================================
// 坐标计算
//==============================================================================
C屏幕坐标到客户区坐标计算::C屏幕坐标到客户区坐标计算(HWND a窗口) {
	GetClientRect(a窗口, &m客户区);
	GetWindowRect(a窗口, &m窗口区);
	m边框 = (m窗口区.right - m窗口区.left - m客户区.right) / 2;
}
long C屏幕坐标到客户区坐标计算::f窗口坐标xl(long x) const {
	return x - m窗口区.left - m边框;
}
long C屏幕坐标到客户区坐标计算::f窗口坐标yl(long y) const {
	return y - m窗口区.bottom + m边框 + m客户区.bottom;
}
float C屏幕坐标到客户区坐标计算::f窗口坐标xf(float x) const {
	return x - m窗口区.left - m边框;
}
float C屏幕坐标到客户区坐标计算::f窗口坐标yf(float y) const {
	return y - m窗口区.bottom + m边框 + m客户区.bottom;
}
long C屏幕坐标到客户区坐标计算::f直角坐标xl(long x) const {
	return f窗口坐标xl(x) - m客户区.right / 2;
}
long C屏幕坐标到客户区坐标计算::f直角坐标yl(long y) const {
	return m客户区.bottom / 2 - f窗口坐标yl(y);
}
float C屏幕坐标到客户区坐标计算::f直角坐标xf(float x) const {
	return f窗口坐标xf(x) - (float)m客户区.right / 2.f;
}
float C屏幕坐标到客户区坐标计算::f直角坐标yf(float y) const {
	return (float)m客户区.bottom / 2.f - f窗口坐标yf(y);
}
//==============================================================================
// 任务栏按钮
//==============================================================================
const TBPFLAG C任务栏按钮::c状态映射[] = {
	TBPF_NOPROGRESS,
	TBPF_INDETERMINATE,
	TBPF_NORMAL,
	TBPF_ERROR,
	TBPF_PAUSED,
};
void C任务栏按钮::f初始化(HWND p窗口) {
	m窗口 = p窗口;
	HRESULT hr = CoCreateInstance(CLSID_TaskbarList, nullptr, CLSCTX_INPROC_SERVER, __uuidof(ITaskbarList3), &m任务栏);
	if (FAILED(hr)) {
		return;
	}
}
void C任务栏按钮::fs状态(int p) {
	m状态 = p;
	m任务栏->SetProgressState(m窗口, c状态映射[p]);
	//f刷新();
}
void C任务栏按钮::fs进度(double p) {
	m进度 = p;
	m任务栏->SetProgressValue(m窗口, (int)(m进度 * 100), 100);
	//f刷新();
}
TBPFLAG C任务栏按钮::fg状态标记() const {
	return c状态映射[m状态];
}
void C任务栏按钮::f刷新() {
	m任务栏->SetProgressValue(m窗口, (int)(m进度 * 100), 100);
	m任务栏->SetProgressState(m窗口, c状态映射[m状态]);
}
UINT C任务栏按钮::f注册消息() {
	return RegisterWindowMessageW(L"TaskbarButtonCreated");
}
//==============================================================================
// 环境
//==============================================================================
SYSTEM_INFO C环境::fg系统信息() {
	SYSTEM_INFO si;
	GetSystemInfo(&si);
	return si;
}
std::wstring C环境::fg计算机名称() {
	WCHAR v文本[256];
	DWORD v大小 = 256;
	GetComputerNameW(v文本, &v大小);
	return v文本;
}
std::wstring C环境::fg用户名称() {
	WCHAR v文本[256];
	DWORD v大小 = 256;
	GetUserNameW(v文本, &v大小);
	return v文本;
}
std::wstring C环境::fg执行程序目录() {
	wchar_t exeFullPath[MAX_PATH] = {0};
	GetModuleFileNameW(NULL, exeFullPath, MAX_PATH);
	wchar_t *p = wcsrchr(exeFullPath, L'\\');
	*p = 0;
	return {exeFullPath};
}
std::wstring C环境::fg执行程序路径() {
	wchar_t exeFullPath[MAX_PATH] = {0};
	GetModuleFileNameW(NULL, exeFullPath, MAX_PATH);
	return {exeFullPath};
}
std::wstring C环境::fg工作目录() {
	wchar_t exeFullPath[MAX_PATH] = {0};
	GetCurrentDirectoryW(MAX_PATH, exeFullPath);  //得到当前工作路径  
	return {exeFullPath};
}
int C环境::fg处理器数量() {
	return fg系统信息().dwNumberOfProcessors;
}
UINT C环境::fg每英寸点数() {
	return GetDpiForSystem();
}
float C环境::fg缩放() {
	return (float)fg每英寸点数() / 96.f;
}
//==============================================================================
// 输入法
//==============================================================================
void C输入法开关::f初始化(HWND p窗口) {
	m窗口 = p窗口;
}
void C输入法开关::f开关(bool p) {
	if (p) {
		f开启();
	} else {
		f关闭();
	}
}
void C输入法开关::f开启() {
	ImmAssociateContext(m窗口, m输入法);
}
void C输入法开关::f关闭() {
	m输入法 = ImmAssociateContext(m窗口, nullptr);
}
//==============================================================================
// 输入法
//==============================================================================
LANGID C语言区域::f提取主语言标识(LANGID a) {
	return a & 0x3ff;
}
LANGID C语言区域::f提取子语言标识(LANGID a) {
	return a >> 10;
}
LANGID C语言区域::f合并语言标识(LANGID a主, LANGID a子) {
	return a主 + (a子 << 10);
}
LANGID C语言区域::fg语言标识() {
	return GetUserDefaultLangID();
}
std::wstring C语言区域::fg语言名称() {
	ULONG v语言数;
	WCHAR v文本[256];
	ULONG v文本大小 = 256;
	GetUserPreferredUILanguages(MUI_LANGUAGE_NAME, &v语言数, v文本, &v文本大小);
	return v文本;
}

}	//namespace cflw::视窗