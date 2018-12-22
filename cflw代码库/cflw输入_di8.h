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
//���뿪ʼ
#define DINPUT_BUFFERSIZE 16
namespace cflw::����::di8 {
using namespace ����;
using Microsoft::WRL::ComPtr;
//==============================================================================
// DirectInput���̰���ö��(λ��dinput.h)
//==============================================================================
enum class E���̰��� {
	e����			= 0x01,
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
	e����			= 0x0C,	//�����̵ļ���
	e�Ⱥ�			= 0x0D,	//�����̵ĵ��ں�
	e�˸�			= 0x0E,	//�˸��
	e�Ʊ�			= 0x0F,
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
	e�س�			= 0x1C,	//�����̵Ļس���
	e�����			= 0x1D,
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
	e���ϵ�			= 0x2A,
	eBACKSLASH		= 0x2B,
	z				= 0x2C,
	x				= 0x2D,
	c				= 0x2E,
	v				= 0x2F,
	b				= 0x30,
	n				= 0x31,
	m				= 0x32,
	eCOMMA			= 0x33,
	e��				= 0x34,	// �����̵�"."
	eб��			= 0x35,	// �����̵�"/"
	e���ϵ�			= 0x36,
	e�˺�			= 0x37,	// �����̵�"*"
	e����			= 0x38,	// ��Alt 
	e�ո�			= 0x39,
	e��д��			= 0x3A,	//capital
	e����1			= 0x3B,
	e����2			= 0x3C,
	e����3			= 0x3D,
	e����4			= 0x3E,
	e����5			= 0x3F,
	e����6			= 0x40,
	e����7			= 0x41,
	e����8			= 0x42,
	e����9			= 0x43,
	e����10			= 0x44,
	e������			= 0x45,
	e������			= 0x46,	// ��������
	e����7			= 0x47,
	e����8			= 0x48,
	e����9			= 0x49,
	e���ּ�			= 0x4A,	// ���ּ��̵�"-"
	e����4			= 0x4B,
	e����5			= 0x4C,
	e����6			= 0x4D,
	e���ּ�			= 0x4E,	// ���ּ��̵�"+"
	e����1			= 0x4F,
	e����2			= 0x50,
	e����3			= 0x51,
	e����0			= 0x52,
	eDECIMAL		= 0x53,	// ���ּ��̵�"."
	eOEM_102		= 0x56,	// <> or \| on RT 102-key keyboard (Non-U.S.) 
	e����11			= 0x57,
	e����12			= 0x58,
	e����13			= 0x64,	// 						 (NEC PC98) 
	e����14			= 0x65,	// 						 (NEC PC98) 
	e����15			= 0x66,	// 						 (NEC PC98) 
	eKANA			= 0x70,	// (�ձ�����) 
	eABNT_C1		= 0x73,	// �������̵�"/?"
	eCONVERT		= 0x79,	// (�ձ�����) 
	eNOCONVERT		= 0x7B,	// (�ձ�����) 
	eYEN			= 0x7D,	// (�ձ�����) 
	eABNT_C2		= 0x7E,	// �������ּ��̵�"."
	eNUMPADEQUALS	= 0x8D,	// ���ּ��̵�"=" (NEC PC98) 
	ePREVTRACK		= 0x90,	// Previous Track (CIRCUMFLEX on Japanese keyboard) 
	eAT				= 0x91,	// 						 (NEC PC98) ,
	eCOLON			= 0x92,	// 						 (NEC PC98) 
	eUNDERLINE		= 0x93,	// 						 (NEC PC98) 
	eKANJI			= 0x94,	// (�ձ�����) 
	eSTOP			= 0x95,	// 						 (NEC PC98) 
	eAX				= 0x96,	// 						 (Japan AX) 
	eUNLABELED		= 0x97,	// 						 (J3100) 
	eNEXTTRACK		= 0x99,	// Next Track 
	eNUMPADENTER	= 0x9C,	// ���ּ��̵�"�س�"
	eRCONTROL		= 0x9D,
	eMUTE			= 0xA0,	// Mute 
	eCALCULATOR		= 0xA1,	// Calculator 
	ePLAYPAUSE		= 0xA2,	// Play / Pause 
	eMEDIASTOP		= 0xA4,	// Media Stop 
	eVOLUMEDOWN		= 0xAE,	// Volume - 
	eVOLUMEUP		= 0xB0,	// Volume + 
	eWEBHOME		= 0xB2,	// Web home 
	eNUMPADCOMMA	= 0xB3,	//  on numeric keypad (NEC PC98) 
	eDIVIDE			= 0xB5,	// ���ּ��̵�"/"
	eSYSRQ			= 0xB7,
	e�ҽ���			= 0xB8,	// ��Alt 
	e��ͣ			= 0xC5,	// ��ͣ
	e��ҳ			= 0xC7,	// ��������ϵ�"Home"
	e��				= 0xC8,	// ��������ϵ�"��"
	e��ҳ			= 0xC9,	// ��������ϵ�"PgUp"
	e��				= 0xCB,	// ��������ϵ�"��"
	e��				= 0xCD,	// ��������ϵ�"��"
	e����			= 0xCF,	// ��������ϵ�"End"
	e��				= 0xD0,	// ��������ϵ�"��"
	e��ҳ			= 0xD1,	// ��������ϵ�"PgDn"
	e����			= 0xD2,	// ��������ϵ�"Insert'
	eɾ��			= 0xD3,	// ��������ϵ�"Delete"
	e���Ӵ�			= 0xDB,	// ��windows��
	e���Ӵ�			= 0xDC,	// ��windows��
	eӦ��			= 0xDD,	// AppMenu key 
	e��Դ			= 0xDE,	// System Power 
	e˯��			= 0xDF,	// System Sleep 
	e����			= 0xE3,	// System Wake 
	e��������		= 0xE5,	// Web Search 
	e�����ղؼ�		= 0xE6,	// Web Favorites 
	e����ˢ��		= 0xE7,	// Web Refresh 
	e������ͣ		= 0xE8,	// Web Stop 
	e����ǰ��		= 0xE9,	// Web Forward 
	e�������		= 0xEA,	// Web Back 
	e�ҵĵ���		= 0xEB,	// My Computer 
	e����			= 0xEC,	// Mail 
	eý��ѡ��		= 0xED,	// Media Select
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