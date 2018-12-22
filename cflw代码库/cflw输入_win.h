#pragma once
#include <vector>
#include <Windows.h>
#include "cflw输入.h"
namespace cflw::输入::win {
using namespace 输入;
//==============================================================================
// Windows键盘按键枚举(位于winuser.h)
//==============================================================================
enum class E键盘按键 {
	eLBUTTON = 0x01,
	eRBUTTON = 0x02,
	eCANCEL = 0x03,
	eMBUTTON = 0x04, /* NOT contiguous with L & RBUTTON */
	eXBUTTON1 = 0x05, /* NOT contiguous with L & RBUTTON */
	eXBUTTON2 = 0x06, /* NOT contiguous with L & RBUTTON */
	e退格 = 0x08,	//backspace
	e制表 = 0x09,	//tab
	e清除 = 0x0C,	//clear
	e回车 = 0x0D,	//enter
	e上档 = 0x10,	//不分左右的shift
	e控制 = 0x11,	//不分左右的ctrl
	e交替 = 0x12,	//不分左右的alt,这个键又叫menu
	e暂停 = 0x13,	//pause
	e大写锁 = 0x14,	//capital
	eKANA = 0x15,
	eHANGEUL = 0x15, /* old name - should be here for compatibility */
	eHANGUL = 0x15,
	eJUNJA = 0x17,
	eFINAL = 0x18,
	eHANJA = 0x19,
	eKANJI = 0x19,
	e逃脱 = 0x1B,	//escape
	eCONVERT = 0x1C,
	eNONCONVERT = 0x1D,
	eACCEPT = 0x1E,	//accept
	eMODECHANGE = 0x1F,	//modechange
	e空格 = 0x20,
	ePRIOR = 0x21,
	eNEXT = 0x22,
	eEND = 0x23,
	eHOME = 0x24,
	e左 = 0x25,
	e上 = 0x26,
	e右 = 0x27,
	e下 = 0x28,
	e选择 = 0x29,	//select
	e打印 = 0x2A,	//print
	e执行 = 0x2B,	//execute
	eSNAPSHOT = 0x2C,	//snapshot
	e插入 = 0x2D,	//insert
	e删除 = 0x2E,	//delete
	e帮助 = 0x2F,	//help
	e0 = '0',
	e1 = '1',
	e2 = '2',
	e3 = '3',
	e4 = '4',
	e5 = '5',
	e6 = '6',
	e7 = '7',
	e8 = '8',
	e9 = '9',
	a = 'A',
	b = 'B',
	c = 'C',
	d = 'D',
	e = 'E',
	f = 'F',
	g = 'G',
	h = 'H',
	i = 'I',
	j = 'J',
	k = 'K',
	l = 'L',
	m = 'M',
	n = 'N',
	o = 'O',
	p = 'P',
	q = 'Q',
	r = 'R',
	s = 'S',
	t = 'T',
	u = 'U',
	v = 'V',
	w = 'W',
	x = 'X',
	y = 'Y',
	z = 'Z',
	e左视窗 = 0x5B,
	e右视窗 = 0x5C,
	eAPPS = 0x5D,
	eSLEEP = 0x5F,
	e数字0 = 0x60,
	e数字1 = 0x61,
	e数字2 = 0x62,
	e数字3 = 0x63,
	e数字4 = 0x64,
	e数字5 = 0x65,
	e数字6 = 0x66,
	e数字7 = 0x67,
	e数字8 = 0x68,
	e数字9 = 0x69,
	eMULTIPLY = 0x6A,
	eADD = 0x6B,
	eSEPARATOR = 0x6C,
	eSUBTRACT = 0x6D,
	eDECIMAL = 0x6E,
	eDIVIDE = 0x6F,
	e功能1 = 0x70,
	e功能2 = 0x71,
	e功能3 = 0x72,
	e功能4 = 0x73,
	e功能5 = 0x74,
	e功能6 = 0x75,
	e功能7 = 0x76,
	e功能8 = 0x77,
	e功能9 = 0x78,
	e功能10 = 0x79,
	e功能11 = 0x7A,
	e功能12 = 0x7B,
	e功能13 = 0x7C,
	e功能14 = 0x7D,
	e功能15 = 0x7E,
	e功能16 = 0x7F,
	e功能17 = 0x80,
	e功能18 = 0x81,
	e功能19 = 0x82,
	e功能20 = 0x83,
	e功能21 = 0x84,
	e功能22 = 0x85,
	e功能23 = 0x86,
	e功能24 = 0x87,
	e数字锁 = 0x90,
	e滚动锁 = 0x91,
	eOEM_NEC_EQUAL = 0x92,// '=' key on numpad,
	eOEM_FJ_JISHO = 0x92, // 'Dictionary' key,
	eOEM_FJ_MASSHOU = 0x93, // 'Unregister word' key,
	eOEM_FJ_TOUROKU = 0x94, // 'Register word' key,
	eOEM_FJ_LOYA = 0x95, // 'Left OYAYUBI' key,
	eOEM_FJ_ROYA = 0x96, // 'Right OYAYUBI' key,
	e左上档 = 0xA0,
	e右上档 = 0xA1,
	e左控制 = 0xA2,
	e右控制 = 0xA3,
	e左交替 = 0xA4,
	e右交替 = 0xA5,
	eBROWSER_BACK = 0xA6,
	eBROWSER_FORWARD = 0xA7,
	eBROWSER_REFRESH = 0xA8,
	eBROWSER_STOP = 0xA9,
	eBROWSER_SEARCH = 0xAA,
	eBROWSER_FAVORITES = 0xAB,
	eBROWSER_HOME = 0xAC,
	eVOLUME_MUTE = 0xAD,
	eVOLUME_DOWN = 0xAE,
	eVOLUME_UP = 0xAF,
	eMEDIA_NEXT_TRACK = 0xB0,
	eMEDIA_PREV_TRACK = 0xB1,
	eMEDIA_STOP = 0xB2,
	eMEDIA_PLAY_PAUSE = 0xB3,
	eLAUNCH_MAIL = 0xB4,
	eLAUNCH_MEDIA_SELECT = 0xB5,
	eLAUNCH_APP1 = 0xB6,
	eLAUNCH_APP2 = 0xB7,
	eOEM_1 = 0xBA,  // ';:' for US,
	eOEM_PLUS = 0xBB,  // '+' any country,
	eOEM_COMMA = 0xBC,  // ',' any country,
	eOEM_MINUS = 0xBD,  // '-' any country,
	eOEM_PERIOD = 0xBE,  // '.' any country,
	eOEM_2 = 0xBF,  // '/?' for US,
	eOEM_3 = 0xC0,  // '`~' for US,
	eOEM_4 = 0xDB,  //  '[{' for US,
	eOEM_5 = 0xDC,  //  '\|' for US,
	eOEM_6 = 0xDD,  //  ']}' for US,
	eOEM_7 = 0xDE,  //  ''"' for US,
	eOEM_8 = 0xDF,
	eOEM_AX = 0xE1,  //  'AX' key on Japanese AX kbd,
	eOEM_102 = 0xE2,  //  "<>" or "\|" on RT 102-key kbd.,
	eICO_HELP = 0xE3,//Help key on ICO,
	eICO_00 = 0xE4,//00 key on ICO,
	ePROCESSKEY = 0xE5,
	eICO_CLEAR = 0xE6,
	ePACKET = 0xE7,
	eOEM_RESET = 0xE9,
	eOEM_JUMP = 0xEA,
	eOEM_PA1 = 0xEB,
	eOEM_PA2 = 0xEC,
	eOEM_PA3 = 0xED,
	eOEM_WSCTRL = 0xEE,
	eOEM_CUSEL = 0xEF,
	eOEM_ATTN = 0xF0,
	eOEM_FINISH = 0xF1,
	eOEM_COPY = 0xF2,
	eOEM_AUTO = 0xF3,
	eOEM_ENLW = 0xF4,
	eOEM_BACKTAB = 0xF5,
	eATTN = 0xF6,
	eCRSEL = 0xF7,
	eEXSEL = 0xF8,
	eEREOF = 0xF9,
	ePLAY = 0xFA,
	eZOOM = 0xFB,
	eNONAME = 0xFC,
	ePA1 = 0xFD,
	eOEM_CLEAR = 0xFE,
};
enum class E鼠标按键 {
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