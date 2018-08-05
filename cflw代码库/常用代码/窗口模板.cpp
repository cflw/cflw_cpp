//注意:这只是一个模板,供程序复制代码,不会被编译
//包含头文件
#include <Windows.h>
class C程序 {
public:
	C程序() {
		g这 = this;
	}
	void f初始化(HINSTANCE hInst, HINSTANCE = nullptr, LPSTR = nullptr, int = 0) {
		m实例 = hInst;
		f创建窗口();
	}
	void f运行() {
		f消息循环();
	}
	void f关闭() {
		f关闭窗口();
	}
private:
	static LRESULT WINAPI f窗口过程(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {
		switch(msg) {
		case WM_DESTROY:
			PostQuitMessage(0);
			return 0;
		default:
			return DefWindowProc(hWnd, msg, wParam, lParam);
		}
	}
	//创建窗口
	void f创建窗口() {
		//注册窗口
		WNDCLASSEX wc;
		wc.cbSize = sizeof(WNDCLASSEX);			//使用sizeof(WNDCLASSEX)
		wc.style = CS_CLASSDC;					//窗口类型
		wc.lpfnWndProc = f窗口过程;					//窗口过程
		wc.cbClsExtra = 0L;							//扩展:
		wc.cbWndExtra = 0L;							//扩展:
		wc.hInstance = m实例;						//实例句柄
		wc.hIcon = LoadIcon(nullptr, IDI_WINLOGO);	//载入默认图标
		wc.hCursor = LoadCursor(nullptr, IDC_ARROW);	//载入默认光标
		wc.hbrBackground = nullptr;							//不需要背景
		wc.lpszMenuName = nullptr;							//不需要菜单
		wc.lpszClassName = c窗口类名;					//设置类名
		wc.hIconSm = nullptr;
		RegisterClassEx(&wc);
		//计算窗口大小
		RECT v窗口矩形 = {0, 0, m窗口大小[0], m窗口大小[1]};
		AdjustWindowRectEx(&v窗口矩形, c窗口风格, FALSE, c窗口风格ex);
		m窗口大小[0] = v窗口矩形.right - v窗口矩形.left;
		m窗口大小[1] = v窗口矩形.bottom - v窗口矩形.top;
		//创建窗口
		m窗口 = CreateWindowExW(
			c窗口风格ex,
			c窗口类名,					//窗口类名
			c窗口标题,					//窗口标题
			c窗口风格,					//窗口风格
			CW_USEDEFAULT, CW_USEDEFAULT,	//坐标
			m窗口大小[0], m窗口大小[1],		//窗口尺寸
			GetDesktopWindow(),			//窗口句柄参数
			nullptr,					//菜单句柄
			m实例,						//实例句柄
			nullptr);					//参数
		//显示窗口
		ShowWindow(m窗口, SW_SHOWDEFAULT);
		UpdateWindow(m窗口);
		//取窗口客户区大小
		GetClientRect(m窗口, &v窗口矩形);
		m窗口大小[0] = v窗口矩形.right - v窗口矩形.left;
		m窗口大小[1] = v窗口矩形.bottom - v窗口矩形.top;
	}
	//消息循环
	void f消息循环() {
		MSG msg = {};
		while (msg.message != WM_QUIT) {	//消息循环
			if (PeekMessage(&msg, nullptr, 0U, 0U, PM_REMOVE)) {	//有消息时的处理,不要修改
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			} else {	//没有消息时的处理

			}
		}	//消息循环结束
	}
	void f关闭窗口() {
		UnregisterClassW(c窗口类名, m实例);
	}
private:	//常量
	const wchar_t *c窗口类名 = L"W窗口";
	const wchar_t *c窗口标题 = L"窗口标题";
	const DWORD	c窗口风格 = WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX;
	const DWORD	c窗口风格ex = WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;
private:	//变量
	HINSTANCE m实例;
	HWND m窗口;
	int m窗口大小[2] = {640, 480};
	static C程序 *g这;
};
C程序 *C程序::g这 = nullptr;
//主函数
int WINAPI wWinMain(HINSTANCE hInst, HINSTANCE, LPWSTR, int) {
	C程序 v程序;
	v程序.f初始化(hInst);
	v程序.f运行();
	v程序.f关闭();
}