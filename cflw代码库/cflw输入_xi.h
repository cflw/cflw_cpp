#pragma once
#include <array>
#include <memory>
#include <windef.h>
#include "cflw输入.h"
#pragma comment(lib, "xinput.lib")
namespace cflw::输入::xi {
using namespace cflw::输入;
bool IsXInputDevice(const GUID *pGuidProductFromDirectInput);
//==============================================================================
enum class E手柄按键 {
	e上,
	e下,
	e左,
	e右,
	e开始,
	e后退,
	e左摇杆,
	e右摇杆,
	e左肩,
	e右肩,
	e保留0,
	e保留1,
	a,
	b,
	x,
	y,
};
enum class E手柄方向 {
	e方向键,
	e左摇杆,
	e右摇杆,
	e合并
};
enum class E手柄触发 {
	e左,
	e右
};
//==============================================================================
class C手柄;
class C输入 {
public:
	C输入();
	~C输入();
	void f创建手柄(tp手柄 &, DWORD = 0);
	void f更新();
private:
	std::array<std::shared_ptr<C手柄>, 4> ma手柄;
};
//==============================================================================
}	//namespace cflw::输入::xi