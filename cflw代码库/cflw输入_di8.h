#pragma once
#define DIRECTINPUT_VERSION 0x0800
//自动链接
#pragma comment(lib, "dinput8.lib")
#pragma comment(lib, "dxguid.lib")
//头文件
#include <memory>
#include <dinput.h>
#include <wrl.h>
#include "cflw输入.h"
#include "cflw辅助.h"
//代码开始
#define DINPUT_BUFFERSIZE 16
namespace cflw::输入::di8 {
using namespace 输入;
using Microsoft::WRL::ComPtr;
//==============================================================================
// DirectInput键盘按键枚举(位于dinput.h)
//==============================================================================
enum class E键盘按键 {
	e逃脱			= 0x01,
	e1				= 0x02,
	e2				= 0x03,
	e3				= 0x04,
	e4				= 0x05,
	e5				= 0x06,
	e6				= 0x07,
	e7				= 0x08,
	e8				= 0x09,
	e9				= 0x0A,
	e0				= 0x0B,
	e减号			= 0x0C,	//主键盘的减号
	e等号			= 0x0D,	//主键盘的等于号
	e退格			= 0x0E,	//退格键
	e制表			= 0x0F,
	q				= 0x10,
	w				= 0x11,
	e				= 0x12,
	r				= 0x13,
	t				= 0x14,
	y				= 0x15,
	u				= 0x16,
	i				= 0x17,
	o				= 0x18,
	p				= 0x19,
	eLBRACKET		= 0x1A,
	eRBRACKET		= 0x1B,
	e回车			= 0x1C,	//主键盘的回车键
	e左控制			= 0x1D,
	a				= 0x1E,
	s				= 0x1F,
	d				= 0x20,
	f				= 0x21,
	g				= 0x22,
	h				= 0x23,
	j				= 0x24,
	k				= 0x25,
	l				= 0x26,
	eSEMICOLON		= 0x27,
	eAPOSTROPHE		= 0x28,
	eGRAVE			= 0x29,	// accent grave 
	e左上档			= 0x2A,
	eBACKSLASH		= 0x2B,
	z				= 0x2C,
	x				= 0x2D,
	c				= 0x2E,
	v				= 0x2F,
	b				= 0x30,
	n				= 0x31,
	m				= 0x32,
	eCOMMA			= 0x33,
	e点				= 0x34,	// 主键盘的"."
	e斜杠			= 0x35,	// 主键盘的"/"
	e右上档			= 0x36,
	e乘号			= 0x37,	// 主键盘的"*"
	e左交替			= 0x38,	// 左Alt 
	e空格			= 0x39,
	e大写锁			= 0x3A,	//capital
	e功能1			= 0x3B,
	e功能2			= 0x3C,
	e功能3			= 0x3D,
	e功能4			= 0x3E,
	e功能5			= 0x3F,
	e功能6			= 0x40,
	e功能7			= 0x41,
	e功能8			= 0x42,
	e功能9			= 0x43,
	e功能10			= 0x44,
	e数字锁			= 0x45,
	e滚动锁			= 0x46,	// 滚轮锁定
	e数字7			= 0x47,
	e数字8			= 0x48,
	e数字9			= 0x49,
	e数字减			= 0x4A,	// 数字键盘的"-"
	e数字4			= 0x4B,
	e数字5			= 0x4C,
	e数字6			= 0x4D,
	e数字加			= 0x4E,	// 数字键盘的"+"
	e数字1			= 0x4F,
	e数字2			= 0x50,
	e数字3			= 0x51,
	e数字0			= 0x52,
	eDECIMAL		= 0x53,	// 数字键盘的"."
	eOEM_102		= 0x56,	// <> or \| on RT 102-key keyboard (Non-U.S.) 
	e功能11			= 0x57,
	e功能12			= 0x58,
	e功能13			= 0x64,	// 						 (NEC PC98) 
	e功能14			= 0x65,	// 						 (NEC PC98) 
	e功能15			= 0x66,	// 						 (NEC PC98) 
	eKANA			= 0x70,	// (日本键盘) 
	eABNT_C1		= 0x73,	// 巴西键盘的"/?"
	eCONVERT		= 0x79,	// (日本键盘) 
	eNOCONVERT		= 0x7B,	// (日本键盘) 
	eYEN			= 0x7D,	// (日本键盘) 
	eABNT_C2		= 0x7E,	// 巴西数字键盘的"."
	eNUMPADEQUALS	= 0x8D,	// 数字键盘的"=" (NEC PC98) 
	ePREVTRACK		= 0x90,	// Previous Track (CIRCUMFLEX on Japanese keyboard) 
	eAT				= 0x91,	// 						 (NEC PC98) ,
	eCOLON			= 0x92,	// 						 (NEC PC98) 
	eUNDERLINE		= 0x93,	// 						 (NEC PC98) 
	eKANJI			= 0x94,	// (日本键盘) 
	eSTOP			= 0x95,	// 						 (NEC PC98) 
	eAX				= 0x96,	// 						 (Japan AX) 
	eUNLABELED		= 0x97,	// 						 (J3100) 
	eNEXTTRACK		= 0x99,	// Next Track 
	eNUMPADENTER	= 0x9C,	// 数字键盘的"回车"
	eRCONTROL		= 0x9D,
	eMUTE			= 0xA0,	// Mute 
	eCALCULATOR		= 0xA1,	// Calculator 
	ePLAYPAUSE		= 0xA2,	// Play / Pause 
	eMEDIASTOP		= 0xA4,	// Media Stop 
	eVOLUMEDOWN		= 0xAE,	// Volume - 
	eVOLUMEUP		= 0xB0,	// Volume + 
	eWEBHOME		= 0xB2,	// Web home 
	eNUMPADCOMMA	= 0xB3,	//  on numeric keypad (NEC PC98) 
	eDIVIDE			= 0xB5,	// 数字键盘的"/"
	eSYSRQ			= 0xB7,
	e右交替			= 0xB8,	// 右Alt 
	e暂停			= 0xC5,	// 暂停
	e主页			= 0xC7,	// 方向键盘上的"Home"
	e上				= 0xC8,	// 方向键盘上的"↑"
	e上页			= 0xC9,	// 方向键盘上的"PgUp"
	e左				= 0xCB,	// 方向键盘上的"←"
	e右				= 0xCD,	// 方向键盘上的"→"
	e结束			= 0xCF,	// 方向键盘上的"End"
	e下				= 0xD0,	// 方向键盘上的"↓"
	e下页			= 0xD1,	// 方向键盘上的"PgDn"
	e插入			= 0xD2,	// 方向键盘上的"Insert'
	e删除			= 0xD3,	// 方向键盘上的"Delete"
	e左视窗			= 0xDB,	// 左windows键
	e右视窗			= 0xDC,	// 右windows键
	e应用			= 0xDD,	// AppMenu key 
	e电源			= 0xDE,	// System Power 
	e睡眠			= 0xDF,	// System Sleep 
	e唤醒			= 0xE3,	// System Wake 
	e网络搜索		= 0xE5,	// Web Search 
	e网络收藏夹		= 0xE6,	// Web Favorites 
	e网络刷新		= 0xE7,	// Web Refresh 
	e网络暂停		= 0xE8,	// Web Stop 
	e网络前进		= 0xE9,	// Web Forward 
	e网络后退		= 0xEA,	// Web Back 
	e我的电脑		= 0xEB,	// My Computer 
	e邮箱			= 0xEC,	// Mail 
	e媒体选择		= 0xED,	// Media Select
};
enum class E手柄方向 {
	e方向键,
	e左摇杆 = e方向键,
	e右摇杆,
};
class C输入;
class C键盘;
class C鼠标;
class C手柄;
//==============================================================================
// 输入引擎
//==============================================================================
class C输入 {
public:
	HWND m窗口;
	ComPtr<IDirectInput8W> m接口;
	std::shared_ptr<C键盘> m键盘;
	std::shared_ptr<C鼠标> m鼠标;
	std::shared_ptr<C手柄> m手柄;
	static C输入 *g这;
	//构造/析构函数
	C输入();
	~C输入();
	//引擎控制
	HRESULT f初始化(HINSTANCE, HWND);
	void f窗口消息(UINT 消息, WPARAM 按键);
	void f更新();
	//设备控制
	HRESULT f创建键盘(tp键盘 &);
	HRESULT f创建鼠标(tp鼠标 &);
	HRESULT f创建手柄(tp手柄 &);
private:
	void f获得焦点();
	void f释放焦点();
	static BOOL CALLBACK f回调手柄(LPCDIDEVICEINSTANCE, LPVOID);
};
}