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
#include "cflw辅助_win.h"
//代码开始
#define DINPUT_BUFFERSIZE 16
namespace cflw::输入::di8 {
using namespace 输入;
using Microsoft::WRL::ComPtr;
//==============================================================================
// DirectInput键盘按键枚举(位于dinput.h)
//==============================================================================
enum class E键盘按键 {
	e键esc			= 0x01,
	e键1			= 0x02,
	e键2			= 0x03,
	e键3			= 0x04,
	e键4			= 0x05,
	e键5			= 0x06,
	e键6			= 0x07,
	e键7			= 0x08,
	e键8			= 0x09,
	e键9			= 0x0A,
	e键0			= 0x0B,
	e键MINUS		= 0x0C,	//主键盘的减号
	e键EQUALS		= 0x0D,	//主键盘的等于号
	e键退格			= 0x0E,	//退格键
	e键tab			= 0x0F,
	e键q			= 0x10,
	e键w			= 0x11,
	e键e			= 0x12,
	e键r			= 0x13,
	e键t			= 0x14,
	e键y			= 0x15,
	e键u			= 0x16,
	e键i			= 0x17,
	e键o			= 0x18,
	e键p			= 0x19,
	e键LBRACKET		= 0x1A,
	e键RBRACKET		= 0x1B,
	e键回车			= 0x1C,	//主键盘的回车键
	e键左ctrl		= 0x1D,
	e键a			= 0x1E,
	e键s			= 0x1F,
	e键d			= 0x20,
	e键f			= 0x21,
	e键g			= 0x22,
	e键h			= 0x23,
	e键j			= 0x24,
	e键k			= 0x25,
	e键l			= 0x26,
	e键SEMICOLON	= 0x27,
	e键APOSTROPHE	= 0x28,
	e键GRAVE		= 0x29,	// accent grave 
	e键左shift		= 0x2A,
	e键BACKSLASH	= 0x2B,
	e键z			= 0x2C,
	e键x			= 0x2D,
	e键c			= 0x2E,
	e键v			= 0x2F,
	e键b			= 0x30,
	e键n			= 0x31,
	e键m			= 0x32,
	e键COMMA		= 0x33,
	e键点			= 0x34,	// 主键盘的"."
	e键斜杠			= 0x35,	// 主键盘的"/"
	e键右shift		= 0x36,
	e键乘号			= 0x37,	// 主键盘的"*"
	e键左alt		= 0x38,	// 左Alt 
	e键空格			= 0x39,
	e键CAPITAL		= 0x3A,
	e键f1			= 0x3B,
	e键f2			= 0x3C,
	e键f3			= 0x3D,
	e键f4			= 0x3E,
	e键f5			= 0x3F,
	e键f6			= 0x40,
	e键f7			= 0x41,
	e键f8			= 0x42,
	e键f9			= 0x43,
	e键f10			= 0x44,
	e键数字锁		= 0x45,
	e键SCROLL		= 0x46,	// 滚轮锁定
	e键数字7		= 0x47,
	e键数字8		= 0x48,
	e键数字9		= 0x49,
	e键数字减		= 0x4A,	// 数字键盘的"-"
	e键数字4		= 0x4B,
	e键数字5		= 0x4C,
	e键数字6		= 0x4D,
	e键数字加		= 0x4E,	// 数字键盘的"+"
	e键数字1		= 0x4F,
	e键数字2		= 0x50,
	e键数字3		= 0x51,
	e键数字0		= 0x52,
	e键DECIMAL		= 0x53,	// 数字键盘的"."
	e键OEM_102		= 0x56,	// <> or \| on RT 102-key keyboard (Non-U.S.) 
	e键f11			= 0x57,
	e键f12			= 0x58,
	e键f13			= 0x64,	// 						 (NEC PC98) 
	e键f14			= 0x65,	// 						 (NEC PC98) 
	e键f15			= 0x66,	// 						 (NEC PC98) 
	e键KANA			= 0x70,	// (日本键盘) 
	e键ABNT_C1		= 0x73,	// 巴西键盘的"/?"
	e键CONVERT		= 0x79,	// (日本键盘) 
	e键NOCONVERT	= 0x7B,	// (日本键盘) 
	e键YEN			= 0x7D,	// (日本键盘) 
	e键ABNT_C2		= 0x7E,	// 巴西数字键盘的"."
	e键NUMPADEQUALS	= 0x8D,	// 数字键盘的"=" (NEC PC98) 
	e键PREVTRACK	= 0x90,	// Previous Track (CIRCUMFLEX on Japanese keyboard) 
	e键AT			= 0x91,	// 						 (NEC PC98) ,
	e键COLON		= 0x92,	// 						 (NEC PC98) 
	e键UNDERLINE	= 0x93,	// 						 (NEC PC98) 
	e键KANJI		= 0x94,	// (日本键盘) 
	e键STOP			= 0x95,	// 						 (NEC PC98) 
	e键AX			= 0x96,	// 						 (Japan AX) 
	e键UNLABELED	= 0x97,	// 						 (J3100) 
	e键NEXTTRACK	= 0x99,	// Next Track 
	e键NUMPADENTER	= 0x9C,	// 数字键盘的"回车"
	e键RCONTROL		= 0x9D,
	e键MUTE			= 0xA0,	// Mute 
	e键CALCULATOR	= 0xA1,	// Calculator 
	e键PLAYPAUSE	= 0xA2,	// Play / Pause 
	e键MEDIASTOP	= 0xA4,	// Media Stop 
	e键VOLUMEDOWN	= 0xAE,	// Volume - 
	e键VOLUMEUP		= 0xB0,	// Volume + 
	e键WEBHOME		= 0xB2,	// Web home 
	e键NUMPADCOMMA	= 0xB3,	//  on numeric keypad (NEC PC98) 
	e键DIVIDE		= 0xB5,	// 数字键盘的"/"
	e键SYSRQ		= 0xB7,
	e键右alt		= 0xB8,	// 右Alt 
	e键暂停			= 0xC5,	// 暂停
	e键主页			= 0xC7,	// 方向键盘上的"Home"
	e键上			= 0xC8,	// 方向键盘上的"↑"
	e键上页			= 0xC9,	// 方向键盘上的"PgUp"
	e键左			= 0xCB,	// 方向键盘上的"←"
	e键右			= 0xCD,	// 方向键盘上的"→"
	e键结束			= 0xCF,	// 方向键盘上的"End"
	e键下			= 0xD0,	// 方向键盘上的"↓"
	e键下页			= 0xD1,	// 方向键盘上的"PgDn"
	e键插入			= 0xD2,	// 方向键盘上的"Insert'
	e键删除			= 0xD3,	// 方向键盘上的"Delete"
	e键左win		= 0xDB,	// 左windows键
	e键右win		= 0xDC,	// 右windows键
	e键应用			= 0xDD,	// AppMenu key 
	e键电源			= 0xDE,	// System Power 
	e键睡眠			= 0xDF,	// System Sleep 
	e键唤醒			= 0xE3,	// System Wake 
	e键网络搜索		= 0xE5,	// Web Search 
	e键网络收藏夹	= 0xE6,	// Web Favorites 
	e键网络刷新		= 0xE7,	// Web Refresh 
	e键网络暂停		= 0xE8,	// Web Stop 
	e键网络前进		= 0xE9,	// Web Forward 
	e键网络后退		= 0xEA,	// Web Back 
	e键我的电脑		= 0xEB,	// My Computer 
	e键邮箱			= 0xEC,	// Mail 
	e键媒体选择		= 0xED,	// Media Select
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