#pragma once
#include <vector>
#include <Windows.h>
#include "cflw输入.h"
namespace cflw::输入::win {
using namespace 输入;
//==============================================================================
// Windows键盘按键枚举(位于winuser.h)
//==============================================================================
enum E键盘按键 {
	e键LBUTTON = 0x01,
	e键RBUTTON = 0x02,
	e键CANCEL = 0x03,
	e键MBUTTON = 0x04, /* NOT contiguous with L & RBUTTON */
	e键XBUTTON1 = 0x05, /* NOT contiguous with L & RBUTTON */
	e键XBUTTON2 = 0x06, /* NOT contiguous with L & RBUTTON */
	e键退格 = 0x08,
	e键tab = 0x09,
	e键CLEAR = 0x0C,
	e键回车 = 0x0D,
	e键shift = 0x10,	//不分左右的shift
	e键ctrl = 0x11,	//不分左右的ctrl
	e键alt = 0x12,	//不分左右的alt,这个键又叫menu
	e键PAUSE = 0x13,
	e键CAPITAL = 0x14,
	e键KANA = 0x15,
	e键HANGEUL = 0x15, /* old name - should be here for compatibility */
	e键HANGUL = 0x15,
	e键JUNJA = 0x17,
	e键FINAL = 0x18,
	e键HANJA = 0x19,
	e键KANJI = 0x19,
	e键esc = 0x1B,
	e键CONVERT = 0x1C,
	e键NONCONVERT = 0x1D,
	e键ACCEPT = 0x1E,
	e键MODECHANGE = 0x1F,
	e键空格 = 0x20,
	e键PRIOR = 0x21,
	e键NEXT = 0x22,
	e键END = 0x23,
	e键HOME = 0x24,
	e键左 = 0x25,
	e键上 = 0x26,
	e键右 = 0x27,
	e键下 = 0x28,
	e键SELECT = 0x29,
	e键PRINT = 0x2A,
	e键EXECUTE = 0x2B,
	e键SNAPSHOT = 0x2C,
	e键INSERT = 0x2D,
	e键DELETE = 0x2E,
	e键HELP = 0x2F,
	e键0 = '0',
	e键1 = '1',
	e键2 = '2',
	e键3 = '3',
	e键4 = '4',
	e键5 = '5',
	e键6 = '6',
	e键7 = '7',
	e键8 = '8',
	e键9 = '9',
	e键a = 'A',
	e键b = 'B',
	e键c = 'C',
	e键d = 'D',
	e键e = 'E',
	e键f = 'F',
	e键g = 'G',
	e键h = 'H',
	e键i = 'I',
	e键j = 'J',
	e键k = 'K',
	e键l = 'L',
	e键m = 'M',
	e键n = 'N',
	e键o = 'O',
	e键p = 'P',
	e键q = 'Q',
	e键r = 'R',
	e键s = 'S',
	e键t = 'T',
	e键u = 'U',
	e键v = 'V',
	e键w = 'W',
	e键x = 'X',
	e键y = 'Y',
	e键z = 'Z',
	e键左win = 0x5B,
	e键右win = 0x5C,
	e键APPS = 0x5D,
	e键SLEEP = 0x5F,
	e键数字0 = 0x60,
	e键数字1 = 0x61,
	e键数字2 = 0x62,
	e键数字3 = 0x63,
	e键数字4 = 0x64,
	e键数字5 = 0x65,
	e键数字6 = 0x66,
	e键数字7 = 0x67,
	e键数字8 = 0x68,
	e键数字9 = 0x69,
	e键MULTIPLY = 0x6A,
	e键ADD = 0x6B,
	e键SEPARATOR = 0x6C,
	e键SUBTRACT = 0x6D,
	e键DECIMAL = 0x6E,
	e键DIVIDE = 0x6F,
	e键f1 = 0x70,
	e键f2 = 0x71,
	e键f3 = 0x72,
	e键f4 = 0x73,
	e键f5 = 0x74,
	e键f6 = 0x75,
	e键f7 = 0x76,
	e键f8 = 0x77,
	e键f9 = 0x78,
	e键f10 = 0x79,
	e键f11 = 0x7A,
	e键f12 = 0x7B,
	e键f13 = 0x7C,
	e键f14 = 0x7D,
	e键f15 = 0x7E,
	e键f16 = 0x7F,
	e键f17 = 0x80,
	e键f18 = 0x81,
	e键f19 = 0x82,
	e键f20 = 0x83,
	e键f21 = 0x84,
	e键f22 = 0x85,
	e键f23 = 0x86,
	e键f24 = 0x87,
	e键NUMLOCK = 0x90,
	e键SCROLL = 0x91,
	e键OEM_NEC_EQUAL = 0x92,// '=' key on numpad,
	e键OEM_FJ_JISHO = 0x92, // 'Dictionary' key,
	e键OEM_FJ_MASSHOU = 0x93, // 'Unregister word' key,
	e键OEM_FJ_TOUROKU = 0x94, // 'Register word' key,
	e键OEM_FJ_LOYA = 0x95, // 'Left OYAYUBI' key,
	e键OEM_FJ_ROYA = 0x96, // 'Right OYAYUBI' key,
	e键左shift = 0xA0,
	e键右shift = 0xA1,
	e键左ctrl = 0xA2,
	e键右ctrl = 0xA3,
	e键左alt = 0xA4,
	e键右alt = 0xA5,
	e键BROWSER_BACK = 0xA6,
	e键BROWSER_FORWARD = 0xA7,
	e键BROWSER_REFRESH = 0xA8,
	e键BROWSER_STOP = 0xA9,
	e键BROWSER_SEARCH = 0xAA,
	e键BROWSER_FAVORITES = 0xAB,
	e键BROWSER_HOME = 0xAC,
	e键VOLUME_MUTE = 0xAD,
	e键VOLUME_DOWN = 0xAE,
	e键VOLUME_UP = 0xAF,
	e键MEDIA_NEXT_TRACK = 0xB0,
	e键MEDIA_PREV_TRACK = 0xB1,
	e键MEDIA_STOP = 0xB2,
	e键MEDIA_PLAY_PAUSE = 0xB3,
	e键LAUNCH_MAIL = 0xB4,
	e键LAUNCH_MEDIA_SELECT = 0xB5,
	e键LAUNCH_APP1 = 0xB6,
	e键LAUNCH_APP2 = 0xB7,
	e键OEM_1 = 0xBA,  // ';:' for US,
	e键OEM_PLUS = 0xBB,  // '+' any country,
	e键OEM_COMMA = 0xBC,  // ',' any country,
	e键OEM_MINUS = 0xBD,  // '-' any country,
	e键OEM_PERIOD = 0xBE,  // '.' any country,
	e键OEM_2 = 0xBF,  // '/?' for US,
	e键OEM_3 = 0xC0,  // '`~' for US,
	e键OEM_4 = 0xDB,  //  '[{' for US,
	e键OEM_5 = 0xDC,  //  '\|' for US,
	e键OEM_6 = 0xDD,  //  ']}' for US,
	e键OEM_7 = 0xDE,  //  ''"' for US,
	e键OEM_8 = 0xDF,
	e键OEM_AX = 0xE1,  //  'AX' key on Japanese AX kbd,
	e键OEM_102 = 0xE2,  //  "<>" or "\|" on RT 102-key kbd.,
	e键ICO_HELP = 0xE3,//Help key on ICO,
	e键ICO_00 = 0xE4,//00 key on ICO,
	e键PROCESSKEY = 0xE5,
	e键ICO_CLEAR = 0xE6,
	e键PACKET = 0xE7,
	e键OEM_RESET = 0xE9,
	e键OEM_JUMP = 0xEA,
	e键OEM_PA1 = 0xEB,
	e键OEM_PA2 = 0xEC,
	e键OEM_PA3 = 0xED,
	e键OEM_WSCTRL = 0xEE,
	e键OEM_CUSEL = 0xEF,
	e键OEM_ATTN = 0xF0,
	e键OEM_FINISH = 0xF1,
	e键OEM_COPY = 0xF2,
	e键OEM_AUTO = 0xF3,
	e键OEM_ENLW = 0xF4,
	e键OEM_BACKTAB = 0xF5,
	e键ATTN = 0xF6,
	e键CRSEL = 0xF7,
	e键EXSEL = 0xF8,
	e键EREOF = 0xF9,
	e键PLAY = 0xFA,
	e键ZOOM = 0xFB,
	e键NONAME = 0xFC,
	e键PA1 = 0xFD,
	e键OEM_CLEAR = 0xFE,
};
enum E鼠标按键 {
	e左键,
	e右键,
	e中键,
	e前进,
	e后退,
};
//==============================================================================
// 设备
//==============================================================================
class C输入;
class C键盘;
class C鼠标;
class C触摸;
class C触控点;
//输入
class C输入 {
public:
	~C输入();
	//引擎控制
	void f初始化(HWND, float 缩放 = 0);
	void f销毁();
	void f窗口消息(UINT 消息, WPARAM, LPARAM);
	void f更新();
	//设备控制
	void f创建键盘(tp键盘 &);
	void f创建鼠标(tp鼠标 &);
	void f创建触摸(tp触摸 &);
public:
	HWND m窗口;
	float m缩放 = 1;
	std::shared_ptr<C键盘> m键盘;
	std::shared_ptr<C鼠标> m鼠标;
	std::shared_ptr<C触摸> m触摸;
};
}	//namespace cflw::输入::win