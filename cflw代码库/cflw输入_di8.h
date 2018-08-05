#pragma once
#define DIRECTINPUT_VERSION 0x0800
//�Զ�����
#pragma comment(lib, "dinput8.lib")
#pragma comment(lib, "dxguid.lib")
//ͷ�ļ�
#include <memory>
#include <dinput.h>
#include <wrl.h>
#include "cflw����.h"
#include "cflw����.h"
#include "cflw����_win.h"
//���뿪ʼ
#define DINPUT_BUFFERSIZE 16
namespace cflw::����::di8 {
using namespace ����;
using Microsoft::WRL::ComPtr;
//==============================================================================
// DirectInput���̰���ö��(λ��dinput.h)
//==============================================================================
enum class E���̰��� {
	e��esc			= 0x01,
	e��1			= 0x02,
	e��2			= 0x03,
	e��3			= 0x04,
	e��4			= 0x05,
	e��5			= 0x06,
	e��6			= 0x07,
	e��7			= 0x08,
	e��8			= 0x09,
	e��9			= 0x0A,
	e��0			= 0x0B,
	e��MINUS		= 0x0C,	//�����̵ļ���
	e��EQUALS		= 0x0D,	//�����̵ĵ��ں�
	e���˸�			= 0x0E,	//�˸��
	e��tab			= 0x0F,
	e��q			= 0x10,
	e��w			= 0x11,
	e��e			= 0x12,
	e��r			= 0x13,
	e��t			= 0x14,
	e��y			= 0x15,
	e��u			= 0x16,
	e��i			= 0x17,
	e��o			= 0x18,
	e��p			= 0x19,
	e��LBRACKET		= 0x1A,
	e��RBRACKET		= 0x1B,
	e���س�			= 0x1C,	//�����̵Ļس���
	e����ctrl		= 0x1D,
	e��a			= 0x1E,
	e��s			= 0x1F,
	e��d			= 0x20,
	e��f			= 0x21,
	e��g			= 0x22,
	e��h			= 0x23,
	e��j			= 0x24,
	e��k			= 0x25,
	e��l			= 0x26,
	e��SEMICOLON	= 0x27,
	e��APOSTROPHE	= 0x28,
	e��GRAVE		= 0x29,	// accent grave 
	e����shift		= 0x2A,
	e��BACKSLASH	= 0x2B,
	e��z			= 0x2C,
	e��x			= 0x2D,
	e��c			= 0x2E,
	e��v			= 0x2F,
	e��b			= 0x30,
	e��n			= 0x31,
	e��m			= 0x32,
	e��COMMA		= 0x33,
	e����			= 0x34,	// �����̵�"."
	e��б��			= 0x35,	// �����̵�"/"
	e����shift		= 0x36,
	e���˺�			= 0x37,	// �����̵�"*"
	e����alt		= 0x38,	// ��Alt 
	e���ո�			= 0x39,
	e��CAPITAL		= 0x3A,
	e��f1			= 0x3B,
	e��f2			= 0x3C,
	e��f3			= 0x3D,
	e��f4			= 0x3E,
	e��f5			= 0x3F,
	e��f6			= 0x40,
	e��f7			= 0x41,
	e��f8			= 0x42,
	e��f9			= 0x43,
	e��f10			= 0x44,
	e��������		= 0x45,
	e��SCROLL		= 0x46,	// ��������
	e������7		= 0x47,
	e������8		= 0x48,
	e������9		= 0x49,
	e�����ּ�		= 0x4A,	// ���ּ��̵�"-"
	e������4		= 0x4B,
	e������5		= 0x4C,
	e������6		= 0x4D,
	e�����ּ�		= 0x4E,	// ���ּ��̵�"+"
	e������1		= 0x4F,
	e������2		= 0x50,
	e������3		= 0x51,
	e������0		= 0x52,
	e��DECIMAL		= 0x53,	// ���ּ��̵�"."
	e��OEM_102		= 0x56,	// <> or \| on RT 102-key keyboard (Non-U.S.) 
	e��f11			= 0x57,
	e��f12			= 0x58,
	e��f13			= 0x64,	// 						 (NEC PC98) 
	e��f14			= 0x65,	// 						 (NEC PC98) 
	e��f15			= 0x66,	// 						 (NEC PC98) 
	e��KANA			= 0x70,	// (�ձ�����) 
	e��ABNT_C1		= 0x73,	// �������̵�"/?"
	e��CONVERT		= 0x79,	// (�ձ�����) 
	e��NOCONVERT	= 0x7B,	// (�ձ�����) 
	e��YEN			= 0x7D,	// (�ձ�����) 
	e��ABNT_C2		= 0x7E,	// �������ּ��̵�"."
	e��NUMPADEQUALS	= 0x8D,	// ���ּ��̵�"=" (NEC PC98) 
	e��PREVTRACK	= 0x90,	// Previous Track (CIRCUMFLEX on Japanese keyboard) 
	e��AT			= 0x91,	// 						 (NEC PC98) ,
	e��COLON		= 0x92,	// 						 (NEC PC98) 
	e��UNDERLINE	= 0x93,	// 						 (NEC PC98) 
	e��KANJI		= 0x94,	// (�ձ�����) 
	e��STOP			= 0x95,	// 						 (NEC PC98) 
	e��AX			= 0x96,	// 						 (Japan AX) 
	e��UNLABELED	= 0x97,	// 						 (J3100) 
	e��NEXTTRACK	= 0x99,	// Next Track 
	e��NUMPADENTER	= 0x9C,	// ���ּ��̵�"�س�"
	e��RCONTROL		= 0x9D,
	e��MUTE			= 0xA0,	// Mute 
	e��CALCULATOR	= 0xA1,	// Calculator 
	e��PLAYPAUSE	= 0xA2,	// Play / Pause 
	e��MEDIASTOP	= 0xA4,	// Media Stop 
	e��VOLUMEDOWN	= 0xAE,	// Volume - 
	e��VOLUMEUP		= 0xB0,	// Volume + 
	e��WEBHOME		= 0xB2,	// Web home 
	e��NUMPADCOMMA	= 0xB3,	//  on numeric keypad (NEC PC98) 
	e��DIVIDE		= 0xB5,	// ���ּ��̵�"/"
	e��SYSRQ		= 0xB7,
	e����alt		= 0xB8,	// ��Alt 
	e����ͣ			= 0xC5,	// ��ͣ
	e����ҳ			= 0xC7,	// ��������ϵ�"Home"
	e����			= 0xC8,	// ��������ϵ�"��"
	e����ҳ			= 0xC9,	// ��������ϵ�"PgUp"
	e����			= 0xCB,	// ��������ϵ�"��"
	e����			= 0xCD,	// ��������ϵ�"��"
	e������			= 0xCF,	// ��������ϵ�"End"
	e����			= 0xD0,	// ��������ϵ�"��"
	e����ҳ			= 0xD1,	// ��������ϵ�"PgDn"
	e������			= 0xD2,	// ��������ϵ�"Insert'
	e��ɾ��			= 0xD3,	// ��������ϵ�"Delete"
	e����win		= 0xDB,	// ��windows��
	e����win		= 0xDC,	// ��windows��
	e��Ӧ��			= 0xDD,	// AppMenu key 
	e����Դ			= 0xDE,	// System Power 
	e��˯��			= 0xDF,	// System Sleep 
	e������			= 0xE3,	// System Wake 
	e����������		= 0xE5,	// Web Search 
	e�������ղؼ�	= 0xE6,	// Web Favorites 
	e������ˢ��		= 0xE7,	// Web Refresh 
	e��������ͣ		= 0xE8,	// Web Stop 
	e������ǰ��		= 0xE9,	// Web Forward 
	e���������		= 0xEA,	// Web Back 
	e���ҵĵ���		= 0xEB,	// My Computer 
	e������			= 0xEC,	// Mail 
	e��ý��ѡ��		= 0xED,	// Media Select
};
enum class E�ֱ����� {
	e�����,
	e��ҡ�� = e�����,
	e��ҡ��,
};
class C����;
class C����;
class C���;
class C�ֱ�;
//==============================================================================
// ��������
//==============================================================================
class C���� {
public:
	HWND m����;
	ComPtr<IDirectInput8W> m�ӿ�;
	std::shared_ptr<C����> m����;
	std::shared_ptr<C���> m���;
	std::shared_ptr<C�ֱ�> m�ֱ�;
	static C���� *g��;
	//����/��������
	C����();
	~C����();
	//�������
	HRESULT f��ʼ��(HINSTANCE, HWND);
	void f������Ϣ(UINT ��Ϣ, WPARAM ����);
	void f����();
	//�豸����
	HRESULT f��������(tp���� &);
	HRESULT f�������(tp��� &);
	HRESULT f�����ֱ�(tp�ֱ� &);
private:
	void f��ý���();
	void f�ͷŽ���();
	static BOOL CALLBACK f�ص��ֱ�(LPCDIDEVICEINSTANCE, LPVOID);
};
}