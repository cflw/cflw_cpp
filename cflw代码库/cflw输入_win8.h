#pragma once
#include <Windows.h>
#include "cflw输入.h"
namespace cflw::输入::win8 {
using namespace 输入;
//==============================================================================
// 类声明
//==============================================================================
class C输入;
class C鼠标;
class C触摸;
class C笔;
class C笔点;
//==============================================================================
// 输入引擎,win8起支持
//==============================================================================
class C输入 {
public:
	C输入() = default;
	~C输入();
	void f初始化(HWND, float 缩放);
	void f销毁();
	bool f窗口消息(UINT 消息, WPARAM, LPARAM);	//有处理消息返回true
	bool f鼠标消息(UINT 消息, WPARAM, LPARAM);
	bool f触摸消息(UINT 消息, WPARAM, LPARAM);
	bool f笔消息(UINT 消息, WPARAM, LPARAM);
	void f更新();
	void fs缩放(float);
	输入::tp鼠标 f创建鼠标();
	输入::tp触摸 f创建触摸();
	输入::tp笔 f创建笔();
private:
	HWND m窗口;
	float m缩放 = 1;
	std::shared_ptr<C鼠标> m鼠标;
	std::shared_ptr<C触摸> m触摸;
	std::shared_ptr<C笔> m笔;
};
}	//namespace cflw::输入::win8