#pragma once
#include <vector>
#include <Windows.h>
#include "cflw����.h"
namespace cflw::����::win {
using namespace ����;
//==============================================================================
// Windows���̰���ö��(λ��winuser.h)
//==============================================================================
enum E���̰��� {
	e��LBUTTON = 0x01,
	e��RBUTTON = 0x02,
	e��CANCEL = 0x03,
	e��MBUTTON = 0x04, /* NOT contiguous with L & RBUTTON */
	e��XBUTTON1 = 0x05, /* NOT contiguous with L & RBUTTON */
	e��XBUTTON2 = 0x06, /* NOT contiguous with L & RBUTTON */
	e���˸� = 0x08,
	e��tab = 0x09,
	e��CLEAR = 0x0C,
	e���س� = 0x0D,
	e��shift = 0x10,	//�������ҵ�shift
	e��ctrl = 0x11,	//�������ҵ�ctrl
	e��alt = 0x12,	//�������ҵ�alt,������ֽ�menu
	e��PAUSE = 0x13,
	e��CAPITAL = 0x14,
	e��KANA = 0x15,
	e��HANGEUL = 0x15, /* old name - should be here for compatibility */
	e��HANGUL = 0x15,
	e��JUNJA = 0x17,
	e��FINAL = 0x18,
	e��HANJA = 0x19,
	e��KANJI = 0x19,
	e��esc = 0x1B,
	e��CONVERT = 0x1C,
	e��NONCONVERT = 0x1D,
	e��ACCEPT = 0x1E,
	e��MODECHANGE = 0x1F,
	e���ո� = 0x20,
	e��PRIOR = 0x21,
	e��NEXT = 0x22,
	e��END = 0x23,
	e��HOME = 0x24,
	e���� = 0x25,
	e���� = 0x26,
	e���� = 0x27,
	e���� = 0x28,
	e��SELECT = 0x29,
	e��PRINT = 0x2A,
	e��EXECUTE = 0x2B,
	e��SNAPSHOT = 0x2C,
	e��INSERT = 0x2D,
	e��DELETE = 0x2E,
	e��HELP = 0x2F,
	e��0 = '0',
	e��1 = '1',
	e��2 = '2',
	e��3 = '3',
	e��4 = '4',
	e��5 = '5',
	e��6 = '6',
	e��7 = '7',
	e��8 = '8',
	e��9 = '9',
	e��a = 'A',
	e��b = 'B',
	e��c = 'C',
	e��d = 'D',
	e��e = 'E',
	e��f = 'F',
	e��g = 'G',
	e��h = 'H',
	e��i = 'I',
	e��j = 'J',
	e��k = 'K',
	e��l = 'L',
	e��m = 'M',
	e��n = 'N',
	e��o = 'O',
	e��p = 'P',
	e��q = 'Q',
	e��r = 'R',
	e��s = 'S',
	e��t = 'T',
	e��u = 'U',
	e��v = 'V',
	e��w = 'W',
	e��x = 'X',
	e��y = 'Y',
	e��z = 'Z',
	e����win = 0x5B,
	e����win = 0x5C,
	e��APPS = 0x5D,
	e��SLEEP = 0x5F,
	e������0 = 0x60,
	e������1 = 0x61,
	e������2 = 0x62,
	e������3 = 0x63,
	e������4 = 0x64,
	e������5 = 0x65,
	e������6 = 0x66,
	e������7 = 0x67,
	e������8 = 0x68,
	e������9 = 0x69,
	e��MULTIPLY = 0x6A,
	e��ADD = 0x6B,
	e��SEPARATOR = 0x6C,
	e��SUBTRACT = 0x6D,
	e��DECIMAL = 0x6E,
	e��DIVIDE = 0x6F,
	e��f1 = 0x70,
	e��f2 = 0x71,
	e��f3 = 0x72,
	e��f4 = 0x73,
	e��f5 = 0x74,
	e��f6 = 0x75,
	e��f7 = 0x76,
	e��f8 = 0x77,
	e��f9 = 0x78,
	e��f10 = 0x79,
	e��f11 = 0x7A,
	e��f12 = 0x7B,
	e��f13 = 0x7C,
	e��f14 = 0x7D,
	e��f15 = 0x7E,
	e��f16 = 0x7F,
	e��f17 = 0x80,
	e��f18 = 0x81,
	e��f19 = 0x82,
	e��f20 = 0x83,
	e��f21 = 0x84,
	e��f22 = 0x85,
	e��f23 = 0x86,
	e��f24 = 0x87,
	e��NUMLOCK = 0x90,
	e��SCROLL = 0x91,
	e��OEM_NEC_EQUAL = 0x92,// '=' key on numpad,
	e��OEM_FJ_JISHO = 0x92, // 'Dictionary' key,
	e��OEM_FJ_MASSHOU = 0x93, // 'Unregister word' key,
	e��OEM_FJ_TOUROKU = 0x94, // 'Register word' key,
	e��OEM_FJ_LOYA = 0x95, // 'Left OYAYUBI' key,
	e��OEM_FJ_ROYA = 0x96, // 'Right OYAYUBI' key,
	e����shift = 0xA0,
	e����shift = 0xA1,
	e����ctrl = 0xA2,
	e����ctrl = 0xA3,
	e����alt = 0xA4,
	e����alt = 0xA5,
	e��BROWSER_BACK = 0xA6,
	e��BROWSER_FORWARD = 0xA7,
	e��BROWSER_REFRESH = 0xA8,
	e��BROWSER_STOP = 0xA9,
	e��BROWSER_SEARCH = 0xAA,
	e��BROWSER_FAVORITES = 0xAB,
	e��BROWSER_HOME = 0xAC,
	e��VOLUME_MUTE = 0xAD,
	e��VOLUME_DOWN = 0xAE,
	e��VOLUME_UP = 0xAF,
	e��MEDIA_NEXT_TRACK = 0xB0,
	e��MEDIA_PREV_TRACK = 0xB1,
	e��MEDIA_STOP = 0xB2,
	e��MEDIA_PLAY_PAUSE = 0xB3,
	e��LAUNCH_MAIL = 0xB4,
	e��LAUNCH_MEDIA_SELECT = 0xB5,
	e��LAUNCH_APP1 = 0xB6,
	e��LAUNCH_APP2 = 0xB7,
	e��OEM_1 = 0xBA,  // ';:' for US,
	e��OEM_PLUS = 0xBB,  // '+' any country,
	e��OEM_COMMA = 0xBC,  // ',' any country,
	e��OEM_MINUS = 0xBD,  // '-' any country,
	e��OEM_PERIOD = 0xBE,  // '.' any country,
	e��OEM_2 = 0xBF,  // '/?' for US,
	e��OEM_3 = 0xC0,  // '`~' for US,
	e��OEM_4 = 0xDB,  //  '[{' for US,
	e��OEM_5 = 0xDC,  //  '\|' for US,
	e��OEM_6 = 0xDD,  //  ']}' for US,
	e��OEM_7 = 0xDE,  //  ''"' for US,
	e��OEM_8 = 0xDF,
	e��OEM_AX = 0xE1,  //  'AX' key on Japanese AX kbd,
	e��OEM_102 = 0xE2,  //  "<>" or "\|" on RT 102-key kbd.,
	e��ICO_HELP = 0xE3,//Help key on ICO,
	e��ICO_00 = 0xE4,//00 key on ICO,
	e��PROCESSKEY = 0xE5,
	e��ICO_CLEAR = 0xE6,
	e��PACKET = 0xE7,
	e��OEM_RESET = 0xE9,
	e��OEM_JUMP = 0xEA,
	e��OEM_PA1 = 0xEB,
	e��OEM_PA2 = 0xEC,
	e��OEM_PA3 = 0xED,
	e��OEM_WSCTRL = 0xEE,
	e��OEM_CUSEL = 0xEF,
	e��OEM_ATTN = 0xF0,
	e��OEM_FINISH = 0xF1,
	e��OEM_COPY = 0xF2,
	e��OEM_AUTO = 0xF3,
	e��OEM_ENLW = 0xF4,
	e��OEM_BACKTAB = 0xF5,
	e��ATTN = 0xF6,
	e��CRSEL = 0xF7,
	e��EXSEL = 0xF8,
	e��EREOF = 0xF9,
	e��PLAY = 0xFA,
	e��ZOOM = 0xFB,
	e��NONAME = 0xFC,
	e��PA1 = 0xFD,
	e��OEM_CLEAR = 0xFE,
};
enum E��갴�� {
	e���,
	e�Ҽ�,
	e�м�,
	eǰ��,
	e����,
};
//==============================================================================
// �豸
//==============================================================================
class C����;
class C����;
class C���;
class C����;
class C���ص�;
//����
class C���� {
public:
	~C����();
	//�������
	void f��ʼ��(HWND, float ���� = 0);
	void f����();
	void f������Ϣ(UINT ��Ϣ, WPARAM, LPARAM);
	void f����();
	//�豸����
	void f��������(tp���� &);
	void f�������(tp��� &);
	void f��������(tp���� &);
public:
	HWND m����;
	float m���� = 1;
	std::shared_ptr<C����> m����;
	std::shared_ptr<C���> m���;
	std::shared_ptr<C����> m����;
};
}	//namespace cflw::����::win