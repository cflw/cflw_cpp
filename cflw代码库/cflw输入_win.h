#pragma once
#include <vector>
#include <Windows.h>
#include "cflw����.h"
namespace cflw::����::win {
using namespace ����;
//==============================================================================
// Windows���̰���ö��(λ��winuser.h)
//==============================================================================
enum class E���̰��� {
	eLBUTTON = 0x01,
	eRBUTTON = 0x02,
	eCANCEL = 0x03,
	eMBUTTON = 0x04, /* NOT contiguous with L & RBUTTON */
	eXBUTTON1 = 0x05, /* NOT contiguous with L & RBUTTON */
	eXBUTTON2 = 0x06, /* NOT contiguous with L & RBUTTON */
	e�˸� = 0x08,	//backspace
	e�Ʊ� = 0x09,	//tab
	e��� = 0x0C,	//clear
	e�س� = 0x0D,	//enter
	e�ϵ� = 0x10,	//�������ҵ�shift
	e���� = 0x11,	//�������ҵ�ctrl
	e���� = 0x12,	//�������ҵ�alt,������ֽ�menu
	e��ͣ = 0x13,	//pause
	e��д�� = 0x14,	//capital
	eKANA = 0x15,
	eHANGEUL = 0x15, /* old name - should be here for compatibility */
	eHANGUL = 0x15,
	eJUNJA = 0x17,
	eFINAL = 0x18,
	eHANJA = 0x19,
	eKANJI = 0x19,
	e���� = 0x1B,	//escape
	eCONVERT = 0x1C,
	eNONCONVERT = 0x1D,
	eACCEPT = 0x1E,	//accept
	eMODECHANGE = 0x1F,	//modechange
	e�ո� = 0x20,
	ePRIOR = 0x21,
	eNEXT = 0x22,
	eEND = 0x23,
	eHOME = 0x24,
	e�� = 0x25,
	e�� = 0x26,
	e�� = 0x27,
	e�� = 0x28,
	eѡ�� = 0x29,	//select
	e��ӡ = 0x2A,	//print
	eִ�� = 0x2B,	//execute
	eSNAPSHOT = 0x2C,	//snapshot
	e���� = 0x2D,	//insert
	eɾ�� = 0x2E,	//delete
	e���� = 0x2F,	//help
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
	e���Ӵ� = 0x5B,
	e���Ӵ� = 0x5C,
	eAPPS = 0x5D,
	eSLEEP = 0x5F,
	e����0 = 0x60,
	e����1 = 0x61,
	e����2 = 0x62,
	e����3 = 0x63,
	e����4 = 0x64,
	e����5 = 0x65,
	e����6 = 0x66,
	e����7 = 0x67,
	e����8 = 0x68,
	e����9 = 0x69,
	eMULTIPLY = 0x6A,
	eADD = 0x6B,
	eSEPARATOR = 0x6C,
	eSUBTRACT = 0x6D,
	eDECIMAL = 0x6E,
	eDIVIDE = 0x6F,
	e����1 = 0x70,
	e����2 = 0x71,
	e����3 = 0x72,
	e����4 = 0x73,
	e����5 = 0x74,
	e����6 = 0x75,
	e����7 = 0x76,
	e����8 = 0x77,
	e����9 = 0x78,
	e����10 = 0x79,
	e����11 = 0x7A,
	e����12 = 0x7B,
	e����13 = 0x7C,
	e����14 = 0x7D,
	e����15 = 0x7E,
	e����16 = 0x7F,
	e����17 = 0x80,
	e����18 = 0x81,
	e����19 = 0x82,
	e����20 = 0x83,
	e����21 = 0x84,
	e����22 = 0x85,
	e����23 = 0x86,
	e����24 = 0x87,
	e������ = 0x90,
	e������ = 0x91,
	eOEM_NEC_EQUAL = 0x92,// '=' key on numpad,
	eOEM_FJ_JISHO = 0x92, // 'Dictionary' key,
	eOEM_FJ_MASSHOU = 0x93, // 'Unregister word' key,
	eOEM_FJ_TOUROKU = 0x94, // 'Register word' key,
	eOEM_FJ_LOYA = 0x95, // 'Left OYAYUBI' key,
	eOEM_FJ_ROYA = 0x96, // 'Right OYAYUBI' key,
	e���ϵ� = 0xA0,
	e���ϵ� = 0xA1,
	e����� = 0xA2,
	e�ҿ��� = 0xA3,
	e���� = 0xA4,
	e�ҽ��� = 0xA5,
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
enum class E��갴�� {
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