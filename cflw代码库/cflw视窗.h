#pragma once
#include <string>
#include <Windows.h>
#include <mmstream.h>
#include <imm.h>
#include <wrl.h>
#include <ShObjIdl.h>
#pragma comment(lib, "winmm.lib")
#pragma comment(lib, "imm32.lib")
#undef min
#undef max
namespace cflw::�Ӵ� {
using Microsoft::WRL::ComPtr;
//==============================================================================
// windef.h
//==============================================================================
typedef DWORD t˫��;	//��:152
typedef BYTE t�ֽ�;	//��:154
typedef WORD t��;	//��:155
typedef UINT t������;//��:173
typedef HWND t���ھ��, tp����;	//��:208
typedef HHOOK t�ҹ����, tp�ҹ�;	//��:209
typedef HBITMAP tλͼ���, tpλͼ;	//��:260
typedef HBRUSH t��ˢ���, tp��ˢ;	//��:261
typedef HFONT t������, tp����;	//��:273
typedef HICON tͼ����, tpͼ��;	//��:275
typedef HMENU t�˵����, tp�˵�;	//��:277
typedef HINSTANCE tʵ�����, tpʵ��;//��:280
typedef HPEN t�ʾ��, tp��;	//��:284
typedef HCURSOR t�����, tp���;	//��:308
typedef tagRECT t����;	//��:319-325
typedef tagPOINT t��;	//��:339-343
typedef tagSIZE t��С;	//��:351-355
//==============================================================================
// winnt.h
//==============================================================================
typedef HANDLE t���, th;	//��:515
typedef HRESULT t���;	//��:542
typedef LARGE_INTEGER t������;	//��:674-688
typedef ULARGE_INTEGER t�޷��Ŵ�����;	//��:692-706
enum class Eͨ��Ȩ��: unsigned long {	//��:6510-6513
	e�� = GENERIC_READ,
	eд = GENERIC_WRITE,
	eִ�� = GENERIC_EXECUTE,
	eȫ�� = GENERIC_ALL
};
//==============================================================================
// winbase.h
//==============================================================================
inline void *f�ڴ��ƶ�(void *aĿ��, void *aԴ, size_t a��С) {
	return MoveMemory(aĿ��, aԴ, a��С);
};	//��:103
inline void *f�ڴ渴��(void *aĿ��, void *aԴ, size_t a��С) {
	return CopyMemory(aĿ��, aԴ, a��С);
};	//��:104
inline void *f�ڴ����(void *aĿ��, int aֵ, size_t a��С) {
	return FillMemory(aĿ��, aֵ, a��С);
};	//��:105
inline void *f�ڴ����(void *aĿ��, size_t a��С) {
	return ZeroMemory(aĿ��, a��С);
};	//��:106
inline DWORD f�����ļ�ָ��(HANDLE a�ļ�, LONG a�ƶ�����, PLONG a�ƶ��߶Ⱦ���, DWORD a�ƶ���ʽ) {
	return SetFilePointer(a�ļ�, a�ƶ�����, a�ƶ��߶Ⱦ���, a�ƶ���ʽ);
};	//��:4984-4992
inline BOOL f�رվ��(HANDLE a���) {
	return CloseHandle(a���);
};	//��:5068
//==============================================================================
// winuser.h
//==============================================================================
typedef WNDPROC tf���ڹ���;//��:62
enum class E������Ϣ : unsigned int {	//��:1723
	e�� = WM_NULL,
	e���� = WM_CREATE,
	e���� = WM_DESTROY,
	e�ƶ� = WM_MOVE,
	e��С = WM_SIZE,
	e� = WM_ACTIVATE,
	e���ý��� = WM_SETFOCUS,
	e�Զ��� = WM_USER
};
enum class E������ʽ : unsigned long {
	e��� = WS_OVERLAPPED,	//����һ������Ĵ��ڡ�һ������Ĵ�����һ����������һ���߿���WS_TILED�����ͬ
	e���� = WS_POPUP,	//����һ������ʽ���ڡ��÷������WS_CHLD���ͬʱʹ��
	e�� = WS_CHILD,	//����һ���Ӵ��ڡ�����������WS_POPUP������
	e��� = WS_MINIMIZE,	//����һ����ʼ״̬Ϊ���״̬�Ĵ���
	e�ɼ� = WS_VISIBLE,	//����һ����ʼ״̬Ϊ�ɼ��Ĵ���
	e��ֹ = WS_DISABLED	//����һ����ʼ״̬Ϊ��ֹ���Ӵ���
};
enum class E�ı���ʽ : unsigned long {	//��:6594
	e���� = DT_TOP,
	e���� = DT_LEFT,
	eˮƽ���� = DT_CENTER,
	e���� = DT_RIGHT,
	e��ֱ���� = DT_VCENTER,
	e�ײ� = DT_BOTTOM,
	e�Զ����� = DT_WORDBREAK,
	e���� = DT_SINGLELINE,
	e��չ�Ʊ�� = DT_EXPANDTABS,
	e�����Ʊ� = DT_TABSTOP,
	e���ü� = DT_NOCLIP,
	e�����ⲿ��ͷ = DT_EXTERNALLEADING,
	eȷ������ = DT_CALCRECT,
	e�ر�ǰ׺ = DT_NOPREFIX,
	eϵͳ������� = DT_INTERNAL
};
//==============================================================================
// winerror.h
//==============================================================================
inline void fʧ�����׳�(HRESULT hr) {
	if (FAILED(hr)) {
		__debugbreak();
		throw hr;
	}
}
inline bool fi�ɹ�(HRESULT hr) {
	return SUCCEEDED(hr);
}
inline bool fiʧ��(HRESULT hr) {
	return FAILED(hr);
}
//==============================================================================
// COM�������ģ��
//==============================================================================
template<typename t> inline void f�ͷ�(t &a) {
	static_assert(std::is_base_of<IUnknown, std::remove_pointer<t>::type>::value, "������IUnknown��������");
	if (a) {
		a->Release();
		a = nullptr;
	}
}
template<typename t> inline void f�ͷ�1(t *a, int a1) {
	for (int i = 0; i < a1; ++i) {
		f�ͷ�(a[i]);
	}
}
template<typename t> inline void f�ͷ�2(t *a, int a1, int a2) {
	for (int i1 = 0; i1 < a1; ++i1) {
		f�ͷ�1(a[i1], a2);
	}
}
//==============================================================================
// ʹ����/�ṹ
//==============================================================================
//��ʱ��
class C��ʱ�� {
public:
	C��ʱ��();
	void f����(float);	//��λ:��
	int f�δ�();
	int f���εδ�();
	int f��Ϸ�δ�();	//�����������1����1�ε��´εδ�
	int fg����();		//�õ��ϴεδ�Ĵ���
	float fg��ʱ();	//��ǰ�ɹ��δ��ʵ�ʹ�ȥʱ��
private:
	void f��ʱ();
	float vʱ��;
	float v��ʱ;
	float v���;	//�δ���
	float v�ϴεδ�;	//�ϴγɹ��δ��ʱ��
	float v��εδ�;
	int v����;
};
//�ؼ���
class C�ؼ��� {
public:
	C�ؼ���();
	~C�ؼ���();
	void f����();
	void f�뿪();
private:
	CRITICAL_SECTION m�ؼ���;
};
//==============================================================================
// ���&�ߴ�&����
//==============================================================================
//���ڷ��
struct S���ڷ�� {
	DWORD mһ����, m��չ���;
	operator DWORD &();
	//һ����
	void fs���(bool);	//��һ���������ͱ߿�
	void fs����(bool);
	void fs�˵�(bool);
	void fs�ť(bool ��, bool С);	//�����С����ť
	void fs������(bool ��ֱ, bool ˮƽ);
	//��չ���
	//��Ϸ��
	void fs�������();
	void fs��������();
	void fs�Ӵ���();
	void fs��Ϸ����();
};
//�ͻ����ߴ�
struct S�ͻ����ߴ� {
	RECT m����;
	S�ͻ����ߴ�(long, long);
	S�ͻ����ߴ�(RECT);
	static S�ͻ����ߴ� fc����(HWND);
	static S�ͻ����ߴ� fc�ߴ���(long x, long y, DWORD ���, DWORD ���ex = 0);//����ͻ����ߴ�,��������CreateWindow�Ĳ���
	long fg��() const;
	long fg��() const;
	float f���Գߴ�(long, long) const;	//ԭ��͸߳��Բ����Ŀ�͸�,ȡ��Сֵ
};
//�������
class C��Ļ���굽�ͻ���������� {
public:
	C��Ļ���굽�ͻ����������(HWND);
	long f��������xl(long) const;
	long f��������yl(long) const;
	float f��������xf(float) const;
	float f��������yf(float) const;
	long fֱ������xl(long) const;
	long fֱ������yl(long) const;
	float fֱ������xf(float) const;
	float fֱ������yf(float) const;
	RECT m�ͻ���, m������;
	long m�߿�;
};
//==============================================================================
// ��������ť
//==============================================================================
class C��������ť {
public:
	enum E״̬ {
		e��,
		e��ȷ��,
		e����,
		e����,
		e��ͣ,
	};
	static const TBPFLAG c״̬ӳ��[];
	void f��ʼ��(HWND);
	void fs״̬(int);
	void fs����(double);
	TBPFLAG fg״̬���() const;
	void fˢ��();
	static UINT fע����Ϣ();
private:
	HWND m���� = nullptr;
	ComPtr<ITaskbarList3> m������;
	int m״̬ = 0;
	double m���� = 0;
};
//==============================================================================
// ����
//==============================================================================
class C���� {
public:
	static SYSTEM_INFO &fgϵͳ��Ϣ();
	static std::wstring fgִ�г���Ŀ¼();
	static std::wstring fgִ�г���·��();
	static std::wstring fg����Ŀ¼();
	static int fg����������();
	static UINT fgÿӢ�����();
	static float fg����();
};
//==============================================================================
// ���뷨
//==============================================================================
class C���뷨���� {
public:
	void f��ʼ��(HWND);
	void f����(bool);
	void f����();
	void f�ر�();
private:
	HWND m���� = nullptr;
	HIMC m���뷨 = nullptr;
};
//==============================================================================
// ����
//==============================================================================
class C�������� {
public:
	static LANGID f��ȡ�����Ա�ʶ(LANGID);
	static LANGID f��ȡ�����Ա�ʶ(LANGID);
	static LANGID f�ϲ����Ա�ʶ(LANGID ��, LANGID ��);
	static LANGID fg���Ա�ʶ();
	static std::wstring fg��������();
};
}	//namespace cflw::�Ӵ�