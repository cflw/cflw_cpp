#pragma once
#ifndef ͷ�ļ�_cflwͼ��_d3d9
#define ͷ�ļ�_cflwͼ��_d3d9
//����
#ifdef _WINDOWS
#pragma comment(lib, "dxerr.lib")
#pragma comment(lib, "dxguid.lib")
#pragma comment(lib, "d3d9.lib")
#if defined(DEBUG) || defined(_DEBUG)
#pragma comment(lib, "d3dx9d.lib")
#else
#pragma comment(lib, "d3dx9.lib")
#endif //DEBUG
#endif
//����ͷ�ļ�
#include <d3d9.h>
#include <d3dx9.h>
#include "cflw�Ӵ�.h"
#include "cflw����_win.h"
//���Ŀ�ʼ
namespace cflw {
namespace ͼ�� {
namespace d3d9 {
//!--------------------------------------------------------------------------------
//!++����
//!--------------------------------------------------------------------------------
#define c���ڿ�� 640
#define c���ڸ߶� 480
#define c����ߴ�_�� D3DXVECTOR2(256,256)
#define c����ߴ�_�� D3DXVECTOR2(512,512)
#define c1����2 D3DXVECTOR2(1,1)
#define c0����3 D3DXVECTOR3(0,0,0)
#define c1������ D3DXVECTOR3(1,1,1)
//!--------------------------------------------------------------------------------
//!++direct3d����������
//!--------------------------------------------------------------------------------
//Direct3Dͼ�θ��ֽӿ�
typedef IDirect3D9				*t�ӿ�ָ��;
typedef IDirect3DDevice9		*t�豸ָ��;
typedef IDirect3DVertexBuffer9	*t����;
typedef IDirect3DTexture9		*t����;
typedef ID3DXSprite				*t����ָ��;
typedef ID3DXFont				*t����ָ��;
typedef ID3DXMesh				*t����ָ��;
//һ���ָ���============================================================
//Direct3Dͼ�θ��ֽṹ
typedef D3DXMATRIX t����;
typedef D3DXVECTOR2 t����2;
typedef D3DXVECTOR3 t����3;
typedef D3DXQUATERNION t��Ԫ��;
typedef D3DXCOLOR t��ɫ;
typedef D3DMATERIAL9 t����;
typedef D3DLIGHT9 t��;
//--------------------------------------------------------------------------------
//!++��
//--------------------------------------------------------------------------------
//!+����
class C�������3d;
typedef class C�������3d t�������, t�������3;
typedef class C�������2d t�������2;
//!+���νṹ
typedef struct S���� {
	t����2 v����;
	t����2 v��ߴ�;
	S����();
	S����(const t����2 &, const t����2 &);
	S����(const �Ӵ�::t���� &);
	S����(const float &��, const float &��, const float &��, const float &��);
}t����;
//!+����ṹ
typedef struct S��ά���� {
	S��ά���� (void);
	S��ά���� (const float &_x, const float &_y, const float &_u, const float &_v);
	S��ά���� (const float &_x, const float &_y, const float &_z, const float &_u, const float &_v);
	//�����ָ���========================================
	float	x, y, z;	// �����3Dλ��
	float	u, v;		// ��������
}t��ά����, *t��ά����ָ��;
//!+�������
class C�������3d {
public:
//����
	t����3 vƽ��;
	t����3 v��ת;
	t����3 v����;
//���캯��
	C�������3d ();
	C�������3d (const t����3 &, const t����3 &, const t����3 &);
//����
	void f����Ӧ�� ();
	void f����Ӧ��2 ();
	C�������3d& f����λ ();
	C�������3d& f������ת (const float &);	//ƽ����ת
	t�������2 fg�������2 ();
	inline C�������3d &fg�������3() {
		return *this;
	};
	inline void fs��ת2 (const float &p = 0) {
		v��ת.x = 0;
		v��ת.y = 0;
		v��ת.z = p;
	};
	inline void fs����2 (const float &px = 1, const float &py = 1) {
		v����.x = px;
		v����.y = py;
	}
};
class C�������2d {
public:
//����
	t����2 vƽ��;
	float v��ת;
	t����2 v����;
//���캯��
	C�������2d ();
	C�������2d (const t����2 &, const float &, const t����2 &);
//����
	void f����Ӧ�� ();
	C�������2d& f����λ ();
	C�������2d& f������ ();	//����ƽ��
};
//!+�����
typedef class C���
{
public:
//����
	t����3 vλ��;
	t����3 v����;
	t����3 v�Ϸ�;
//���캯��
	C��� ();
	C��� (const t����3 &, const t����3 &, const t����3 &);
//����
	void fӦ�� ();
	C���& f��λ ();
	C���& fƽ�� (const t����3 &);
}t���;
//!+ͶӰ����
class CͶӰ����	//�����������ͶӰ����Ļ��
{
public:
	float v�ӽ�;	//����,3d�ӽǷ�Χ
	float v��;		//2d���,3d���ڿ�߱�
	float v��;		//2d�߶�,3d���ڿ�߱�
	float v��z;		//���ü���
	float vԶz;		//Զ�ü���
	CͶӰ���� ();
	void fӦ��2d ();
	void fӦ��3d ();
};
//!+�ӿ�
class C�ӿ�	//����ͶӰ����Ļ�ϵ�����
{	//ע�����ʹ����ѧֱ������ϵ
public:
	t����2 v����;
	t����2 v����;
	C�ӿ� ();
	void fӦ�� ();
	void fs (const float &��, const float &��, const float &��, const float &��);
};
//+ͼ����
typedef class Cͼ�� tͼ��;
typedef void (*tͼ�κ���ָ��)(tͼ�� &);
class Cͼ��:public C�������3d
{
public:
//��Ա����
	t���� v����;	//�󶨵�����
	t���� v����;	//ʹ�õĶ���
	t���� v����;		//ʹ�õĲ���
//���캯��
	Cͼ�� (void);
//��Ա����
	void f����׼�� ();
	void f��ʾ2d ();
	void f��ʾ3d ();
};
//+���������
typedef class C���������_���� t��������_����;
typedef class C���������_����ex t��������_����ex;
class C���������_���� {
public:
	t����2 v����ߴ�;
	t����2 v��������;
	t����2 v���ΰ�ߴ�;
	float v��������;
	C���������_���� ();
	inline void f��������ߴ� (const float &x, const float &y) {
		v����ߴ�.x = x;
		v����ߴ�.y = y;
	};
	inline void f���þ������� (const float &x, const float &y) {
		v��������.x = x;
		v��������.y = y;
	};
	inline void f���þ��ΰ�ߴ� (const float &x, const float &y) {
		v���ΰ�ߴ�.x = x;
		v���ΰ�ߴ�.y = y;
	};
	void f���þ��� (const float &��, const float &��, const float &��, const float &��);
	bool f�������� (t���� &);
};
class C���������_����ex: public C���������_����
{
public:
	t����2 vƽ��;
	float v��ת;
	t����2 v����;
	C���������_����ex ();
	inline void f����ƽ�� (const float &x, const float &y)
	{
		vƽ��.x = x;
		vƽ��.y = y;
	};
	inline void f������ת (const float &����)
	{
		v��ת = ����;
	};
	inline void f�������� (const float &x, const float &y)
	{
		v����.x = x;
		v����.y = y;
	};
	inline void fex������� ()
	{
		vƽ��.x = 0;
		vƽ��.y = 0;
		v��ת = 0;
		v����.x = 0;
		v����.y = 0;
	};
	void f������ʾ���� (const float &��, const float &��, const float &��, const float &��);
	bool f��������ex (t���� &);
};
class C���������_��
{
public:
	t����3 v����;
	t����2 v����ӳ��;
	t����2 v����ߴ�;
	C���������_�� ();
	~C���������_�� ();
};
//+����������
class C����������
{
	t���� v��������;
	void **v�޸Ķ���;
public:
	C���������� ();
	~C���������� ();
	bool f����_ (const t���� &, void **);
	template<class t> inline bool f���� (const t���� &p��������, t &p�޸Ķ���)
	{
		return f����_ (p��������, (void**)&p�޸Ķ���);
	};
	bool f���� ();
};
//+�ı������
typedef class C�ı������ t�ı������;
class C�ı������
{
public:
	LONG ��;	//�������ֵĸ߶�
	LONG ��;	//�������ֵĿ��
	LONG ��;	//0-1000 ��ֵԽ��Խ��
	FLOAT ��;	//��Z������ĺ��
	BYTE б��;		//�Ƿ�б��
	BYTE �»���;	//�Ƿ����»���
	BYTE ɾ����;	//�Ƿ���ɾ����
	WCHAR ����[32];	//���������
	C�ı������ ();
	inline void f�������� (wchar_t* _����)
	{
		wcscpy_s (����, _����);
	};
	inline void f���ô��� (const bool &����)
	{
		�� = ���� ? FW_BOLD : FW_NORMAL;
	};
	bool f�����ı� (wchar_t* �ı�, t����ָ��&);
};
//--------------------------------------------------------------------------------
//!++direct3dö�ٺͳ���
//--------------------------------------------------------------------------------
//D3DPRIMITIVETYPEö��
enum EͼԪ����
{
	cͼԪ����_�б�� = D3DPT_POINTLIST,
	cͼԪ����_�б��߶� = D3DPT_LINELIST,
	cͼԪ����_�����߶� = D3DPT_LINESTRIP,
	cͼԪ����_�б������� = D3DPT_TRIANGLELIST,
	cͼԪ����_���������� = D3DPT_TRIANGLESTRIP,
	cͼԪ����_���������� = D3DPT_TRIANGLEFAN
};
typedef _D3DPRIMITIVETYPE tͼԪ����;
//D3DTEXTURESTAGESTATETYPEö��
enum E����ͼ��״̬����
{
	c����ͼ��״̬����_��ɫ���� = D3DTSS_COLOROP,
	c����ͼ��״̬����_��ɫ����1 = D3DTSS_COLORARG1,
	c����ͼ��״̬����_��ɫ����2 = D3DTSS_COLORARG2,
	c����ͼ��״̬����_���������� = D3DTSS_ALPHAOP,
	c����ͼ��״̬����_����������1 = D3DTSS_ALPHAARG1,
	c����ͼ��״̬����_����������2 = D3DTSS_ALPHAARG2
};
typedef _D3DTEXTURESTAGESTATETYPE t����ͼ��״̬����;
//D3DTEXTUREOPö��
enum E�������
{
	c�������_��ֹ = D3DTOP_DISABLE,
	c�������_ѡ��1 = D3DTOP_SELECTARG1,
	c�������_ѡ��2 = D3DTOP_SELECTARG2,
	c�������_��� = D3DTOP_MODULATE
};
typedef _D3DTEXTUREOP t�������;
//D3DLIGHTTYPE ö��
enum E������
{
	c������_���Դ = D3DLIGHT_POINT,
	c������_�۹�� = D3DLIGHT_SPOT,
	c������_ƽ�й� = D3DLIGHT_DIRECTIONAL
};
typedef _D3DLIGHTTYPE t������;
//D3DRENDERSTATETYPEö��
enum E��Ⱦ״̬
{
	c��Ⱦ״̬_Դ��� = D3DRS_SRCBLEND,
	c��Ⱦ״̬_Ŀ���� = D3DRS_DESTBLEND
};
typedef _D3DRENDERSTATETYPE t��Ⱦ״̬;
//D3DBLENDö��
enum E���
{
	c���_Դ��ɫ = D3DBLEND_SRCCOLOR,
	c���_Դ��ɫ�� = D3DBLEND_INVSRCCOLOR,
	c���_Դ������ = D3DBLEND_SRCALPHA,
	c���_Դ�������� = D3DBLEND_INVSRCALPHA,
	c���_Ŀ�갢���� = D3DBLEND_DESTALPHA,
	c���_Ŀ�갢������ = D3DBLEND_INVDESTALPHA,
	c���_Ŀ����ɫ = D3DBLEND_DESTCOLOR,
	c���_Ŀ����ɫ�� = D3DBLEND_INVDESTCOLOR
};
typedef _D3DBLEND t���;
enum E���ģʽ
{
	e���_����,
	e���_����
};
//--------------------------------------------------------------------------------
//ȫ�ֱ�������
//--------------------------------------------------------------------------------
extern t�ӿ�ָ�� vͼ�νӿ�;
extern t�豸ָ�� vͼ���豸;
extern const t��ɫ c��ɫ;
extern const t��ɫ c��ɫ;
extern const t��ɫ c��ɫ;
extern const t��ɫ c��ɫ;
extern const t��ɫ c��ɫ;
extern const t���� c��ɫ����;
extern const t���� cС͸����ɫ����;
extern const t���� c��͸����ɫ����;
extern const t���� c��͸����ɫ����;
extern const t���� c͸������;
extern const t���� c��ɫ����;
extern const t���� c��ɫ����;
extern const t���� c��ɫ����;
extern DWORD fvf��ά����;
extern t�� v��Ļ��;
extern t��� v��Ļ���;	//��׼������Ļ
extern t���� v��ʱ����;
extern EͼԪ���� v����ģʽ;
extern CͶӰ���� vĬ��ͶӰ;
extern t����2 v��Ļ�ߴ�;
extern C�ӿ� v��Ļ�ӿ�;
extern �Ӵ�::C�ؼ��� v�ؼ���;
extern t���� v2d����;
//����ͼ��
extern t���� v����;
//--------------------------------------------------------------------------------
//����
//--------------------------------------------------------------------------------
//�豸
bool f�����豸 (const HWND &���ھ��);
void f���ٳ�ʼ�� ();
void fͼ�θ�λ ();
void f�����豸 ();
void f���븽��ͼ�� ();
//��������
void f��_���� (const t���� &);
//����
inline t����2 fn������2 (const float &p���ű���)
{
	return t����2 (p���ű���, p���ű���);
};
inline t����3 fn������3 (const float &p���ű���)
{
	return t����3 (p���ű���, p���ű���, p���ű���);
};
�Ӵ�::t���� f���������� (const �Ӵ�::t���� &);
�Ӵ�::t���� f���� (const t����2 &��������, const t����2 &��ߴ�);
inline �Ӵ�::t���� f���� (const t���� &p����)
{
	return f���� (p����.v����, p����.v��ߴ�);
};
t���� f������ɫ���� (const t���� &, const t��ɫ &, const float &);
t���� f������״���� (const t���� &, const t���� &, const float & = 0.4f, const float & = 999.f);
//�豸״̬
inline HRESULT f������Ⱦ״̬(const _D3DRENDERSTATETYPE &״̬, const DWORD &ֵ)
{
	return vͼ���豸->SetRenderState(״̬,ֵ);
};
//����
inline void f���û���ģʽ (const EͼԪ���� &p����ģʽ)
{
	v����ģʽ = p����ģʽ;
};
inline void f����ͼԪ (const unsigned int &p�������, const unsigned int &pͼ������)
{
	vͼ���豸->DrawPrimitive((tͼԪ����)(int)v����ģʽ, p�������, pͼ������);
};
inline void f����ͼԪ (const unsigned int &pͼ������)
{
	vͼ���豸->DrawPrimitive((tͼԪ����)(int)v����ģʽ, 0, pͼ������);
};
inline void f����ͼԪ ()
{
	vͼ���豸->DrawPrimitive((tͼԪ����)(int)v����ģʽ, 0, 2);
};
//����
HRESULT f�������㻺�� (t���� *���ܻ������Ķ���ָ��, const int &��������);	//ʹ��ǰ��Ҫ���úö����С��fvf��ʽ
inline void f������Դ(const t���� ����)
{
	vͼ���豸->SetStreamSource (0, ����, 0, sizeof(S��ά����));
};
inline void f���ö���(const t���� ����)
{
	vͼ���豸->SetStreamSource (0, ����, 0, sizeof(S��ά����));
};
//��Ͳ���
#define f���ù�(����,��) vͼ���豸->SetLight(����,��)
#define f�⿪��(����,����) vͼ���豸->LightEnable(����,����)
inline void f���ò���(const t���� &p����)
{
	vͼ���豸->SetMaterial(&p����);
};
inline void f������ɫ(const t��ɫ &p��ɫ) {
	v2d����.Diffuse.a = p��ɫ.a;
	v2d����.Emissive.r = p��ɫ.r;
	v2d����.Emissive.g = p��ɫ.g;
	v2d����.Emissive.b = p��ɫ.b;
	vͼ���豸->SetMaterial(&v2d����);
};
inline void f����͸����(const float &a) {
	f������ɫ(t��ɫ(1,1,1,a));
};
t���� f������ (const t��ɫ &������ɫ, const t��ɫ &������ɫ, const t��ɫ &������ɫ, const t��ɫ &������ɫ, const float &����߹�);
t���� f������ (const t��ɫ &��ɫ, const bool &����ģʽ = false);
//����
inline bool f������� (t���� &���������ַ��ָ��, const wchar_t *������ļ���)
{
	if (FAILED(D3DXCreateTextureFromFile (vͼ���豸, ������ļ���, &���������ַ��ָ��)))
		throw;
	return true;
};
bool f�������� (t���� &��Ҫ����������);
inline void f��������ͼ��״̬ (const t����ͼ��״̬���� &p����, const int &pֵ)
{
	vͼ���豸->SetTextureStageState (0, p����, pֵ);
};
void f������ (const bool &����);
inline void f������_��()
{
	f��������ͼ��״̬(D3DTSS_COLOROP, D3DTOP_MODULATE);
	f��������ͼ��״̬(D3DTSS_ALPHAOP, D3DTOP_MODULATE);
};
inline void f������_��()
{
	f��������ͼ��״̬(D3DTSS_COLOROP, D3DTOP_SELECTARG2);
	f��������ͼ��״̬(D3DTSS_ALPHAOP, D3DTOP_SELECTARG2);
};
//�������
#define f�����������任(�������) vͼ���豸->SetTransform(D3DTS_WORLD,�������)
void f����������� (t����3*const&ƽ��, t����3*const&��ת, t����3*const&����);
void f��λ������� ();
//��ͼ����
void f��λ��ͼ���� ();
//���
void f��� (E���ģʽ);
inline void f���_���� () {
	f������Ⱦ״̬ (D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
};
inline void f���_���� () {
	f������Ⱦ״̬ (D3DRS_DESTBLEND, D3DBLEND_DESTALPHA);
};
//�����ָ���====================================================================================================
}}}	//�����ռ����
#endif