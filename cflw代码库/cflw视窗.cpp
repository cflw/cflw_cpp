#include <math.h>
#include <string.h>
#include <algorithm>
#include "cflw�Ӵ�.h"
namespace cflw::�Ӵ� {
//==============================================================================
// ���ڿ���
//==============================================================================
void fs���ڴ�С(HWND a����, int a��, int a��) {
	RECT v����;
	GetWindowRect(a����, &v����);
	const auto[v��ʽ, v��ʽex] = fg������ʽ(a����);
	const S�ͻ����ߴ� v�ߴ� = S�ͻ����ߴ�::fc�ߴ���ʽ(a��, a��, v��ʽ, v��ʽex);
	MoveWindow(a����, v����.left, v����.top, v�ߴ�.fg��(), v�ߴ�.fg��(), false);
}
std::pair<DWORD, DWORD> fg������ʽ(HWND a����) {
	const DWORD v��ʽ = (DWORD)GetWindowLongW(a����, GWL_STYLE);
	const DWORD v��ʽex = (DWORD)GetWindowLongW(a����, GWL_EXSTYLE);
	return {v��ʽ, v��ʽex};
}
//==============================================================================
// ��ʱ��
//==============================================================================
C��ʱ��::C��ʱ��() :mʱ��(0), m��ʱ(0), m���(0) {};
void C��ʱ��::f����(float p���) {
	mʱ�� = timeGetTime() / 1000.f;
	m��ʱ = 0;
	m��� = p���;
}
void C��ʱ��::f��ʱ() {
	float v�ϴ�ʱ�� = mʱ��;
	mʱ�� = timeGetTime() / 1000.f;
	m��ʱ += mʱ�� - v�ϴ�ʱ��;
}
int C��ʱ��::fg����() {
	return m����;
}
float C��ʱ��::fg��ʱ() {
	return m��εδ� - m�ϴεδ�;
}
int C��ʱ��::f�δ�() {
	f��ʱ();
	m���� = (int)floor(m��ʱ / m���);
	if (m����) {
		m�ϴεδ� = m��εδ�;
		m��εδ� = mʱ��;
		m��ʱ -= m���� * m���;
	}
	return m����;
}
int C��ʱ��::f���εδ�() {
	f��ʱ();
	if (m��ʱ >= m���) {
		m��ʱ -= m���;
		m�ϴεδ� = m��εδ�;
		m��εδ� = mʱ��;
		return m���� = 1;
	} else {
		return m���� = 0;
	}
}
int C��ʱ��::f��Ϸ�δ�() {
	f��ʱ();
	m���� = (int)floor(m��ʱ / m���);
	if (m����) {
		m��ʱ -= m���� * m���;
		m�ϴεδ� = m��εδ�;
		m��εδ� = mʱ��;
		if (m���� >= 2) {
			m��ʱ += m���;
		}
	}
	return m����;
}
//==============================================================================
// �ؼ���
//==============================================================================
C�ؼ���::C�ؼ���() {
	InitializeCriticalSection(&m�ؼ���);
}
C�ؼ���::~C�ؼ���() {
	LeaveCriticalSection(&m�ؼ���);
	DeleteCriticalSection(&m�ؼ���);
}
void C�ؼ���::f����() {
	EnterCriticalSection(&m�ؼ���);
}
void C�ؼ���::f�뿪() {
	LeaveCriticalSection(&m�ؼ���);
}
//==============================================================================
// ������ʽ
//==============================================================================
const S������ʽ S������ʽ::c������� = {WS_OVERLAPPEDWINDOW, WS_EX_OVERLAPPEDWINDOW};
const S������ʽ S������ʽ::c�������� = {WS_POPUPWINDOW, 0};
const S������ʽ S������ʽ::c�Ӵ��� = {WS_CHILDWINDOW, 0};
const S������ʽ S������ʽ::c��Ϸ���� = {
	WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX,
	WS_EX_APPWINDOW | WS_EX_WINDOWEDGE
};
void S������ʽ::fs���(bool) {}
void S������ʽ::fs����(bool) {}
void S������ʽ::fs�˵�(bool) {}
void S������ʽ::fs�ť(bool /*��*/, bool /*С*/) {}
void S������ʽ::fs������(bool /*��ֱ*/, bool /*ˮƽ*/) {}
//==============================================================================
// �ͻ����ߴ�
//==============================================================================
S�ͻ����ߴ�::S�ͻ����ߴ�(long a��, long a��):
	m����{0, 0, a��, a��} {
}
S�ͻ����ߴ�::S�ͻ����ߴ�(RECT p����):
	m����{p����} {
}
S�ͻ����ߴ� S�ͻ����ߴ�::fc����(HWND p����) {
	RECT rc;
	GetClientRect(p����, &rc);
	return S�ͻ����ߴ�{rc.right - rc.left, rc.bottom - rc.top};
}
S�ͻ����ߴ� S�ͻ����ߴ�::fc�ߴ���ʽ(long px, long py, DWORD p��ʽ, DWORD p��ʽex) {
	RECT v���ڳߴ� = {0, 0, px, py};
	AdjustWindowRectEx(&v���ڳߴ�, p��ʽ, FALSE, p��ʽex);
	return S�ͻ����ߴ�{v���ڳߴ�.right - v���ڳߴ�.left, v���ڳߴ�.bottom - v���ڳߴ�.top};
}
long S�ͻ����ߴ�::fg��() const {
	return m����.right - m����.left;
}
long S�ͻ����ߴ�::fg��() const {
	return m����.bottom - m����.top;
}
float S�ͻ����ߴ�::f���Գߴ�(long a��, long a��) const {
	const float v�� = (float)fg��() / (float)a��;
	const float v�� = (float)fg��() / (float)a��;
	return std::min<float>(v��, v��);
}
//==============================================================================
// �������
//==============================================================================
C��Ļ���굽�ͻ����������::C��Ļ���굽�ͻ����������(HWND a����) {
	GetClientRect(a����, &m�ͻ���);
	GetWindowRect(a����, &m������);
	m�߿� = (m������.right - m������.left - m�ͻ���.right) / 2;
}
long C��Ļ���굽�ͻ����������::f��������xl(long x) const {
	return x - m������.left - m�߿�;
}
long C��Ļ���굽�ͻ����������::f��������yl(long y) const {
	return y - m������.bottom + m�߿� + m�ͻ���.bottom;
}
float C��Ļ���굽�ͻ����������::f��������xf(float x) const {
	return x - m������.left - m�߿�;
}
float C��Ļ���굽�ͻ����������::f��������yf(float y) const {
	return y - m������.bottom + m�߿� + m�ͻ���.bottom;
}
long C��Ļ���굽�ͻ����������::fֱ������xl(long x) const {
	return f��������xl(x) - m�ͻ���.right / 2;
}
long C��Ļ���굽�ͻ����������::fֱ������yl(long y) const {
	return m�ͻ���.bottom / 2 - f��������yl(y);
}
float C��Ļ���굽�ͻ����������::fֱ������xf(float x) const {
	return f��������xf(x) - (float)m�ͻ���.right / 2.f;
}
float C��Ļ���굽�ͻ����������::fֱ������yf(float y) const {
	return (float)m�ͻ���.bottom / 2.f - f��������yf(y);
}
//==============================================================================
// ��������ť
//==============================================================================
const TBPFLAG C��������ť::c״̬ӳ��[] = {
	TBPF_NOPROGRESS,
	TBPF_INDETERMINATE,
	TBPF_NORMAL,
	TBPF_ERROR,
	TBPF_PAUSED,
};
void C��������ť::f��ʼ��(HWND p����) {
	m���� = p����;
	HRESULT hr = CoCreateInstance(CLSID_TaskbarList, nullptr, CLSCTX_INPROC_SERVER, __uuidof(ITaskbarList3), &m������);
	if (FAILED(hr)) {
		return;
	}
}
void C��������ť::fs״̬(int p) {
	m״̬ = p;
	m������->SetProgressState(m����, c״̬ӳ��[p]);
	//fˢ��();
}
void C��������ť::fs����(double p) {
	m���� = p;
	m������->SetProgressValue(m����, (int)(m���� * 100), 100);
	//fˢ��();
}
TBPFLAG C��������ť::fg״̬���() const {
	return c״̬ӳ��[m״̬];
}
void C��������ť::fˢ��() {
	m������->SetProgressValue(m����, (int)(m���� * 100), 100);
	m������->SetProgressState(m����, c״̬ӳ��[m״̬]);
}
UINT C��������ť::fע����Ϣ() {
	return RegisterWindowMessageW(L"TaskbarButtonCreated");
}
//==============================================================================
// ����
//==============================================================================
SYSTEM_INFO &C����::fgϵͳ��Ϣ() {
	SYSTEM_INFO si;
	GetSystemInfo(&si);
	return si;
}
std::wstring C����::fg���������() {
	WCHAR v�ı�[256];
	DWORD v��С = 256;
	GetComputerNameW(v�ı�, &v��С);
	return v�ı�;
}
std::wstring C����::fg�û�����() {
	WCHAR v�ı�[256];
	DWORD v��С = 256;
	GetUserNameW(v�ı�, &v��С);
	return v�ı�;
}
std::wstring C����::fgִ�г���Ŀ¼() {
	wchar_t exeFullPath[MAX_PATH] = {0};
	GetModuleFileNameW(NULL, exeFullPath, MAX_PATH);
	wchar_t *p = wcsrchr(exeFullPath, L'\\');
	*p = 0;
	return {exeFullPath};
}
std::wstring C����::fgִ�г���·��() {
	wchar_t exeFullPath[MAX_PATH] = {0};
	GetModuleFileNameW(NULL, exeFullPath, MAX_PATH);
	return {exeFullPath};
}
std::wstring C����::fg����Ŀ¼() {
	wchar_t exeFullPath[MAX_PATH] = {0};
	GetCurrentDirectoryW(MAX_PATH, exeFullPath);  //�õ���ǰ����·��  
	return {exeFullPath};
}
int C����::fg����������() {
	return fgϵͳ��Ϣ().dwNumberOfProcessors;
}
UINT C����::fgÿӢ�����() {
	return GetDpiForSystem();
}
float C����::fg����() {
	return (float)fgÿӢ�����() / 96.f;
}
//==============================================================================
// ���뷨
//==============================================================================
void C���뷨����::f��ʼ��(HWND p����) {
	m���� = p����;
}
void C���뷨����::f����(bool p) {
	if (p) {
		f����();
	} else {
		f�ر�();
	}
}
void C���뷨����::f����() {
	ImmAssociateContext(m����, m���뷨);
}
void C���뷨����::f�ر�() {
	m���뷨 = ImmAssociateContext(m����, nullptr);
}
//==============================================================================
// ���뷨
//==============================================================================
LANGID C��������::f��ȡ�����Ա�ʶ(LANGID a) {
	return a & 0x3ff;
}
LANGID C��������::f��ȡ�����Ա�ʶ(LANGID a) {
	return a >> 10;
}
LANGID C��������::f�ϲ����Ա�ʶ(LANGID a��, LANGID a��) {
	return a�� + (a�� << 10);
}
LANGID C��������::fg���Ա�ʶ() {
	return GetUserDefaultLangID();
}
std::wstring C��������::fg��������() {
	ULONG v������;
	WCHAR v�ı�[256];
	ULONG v�ı���С = 256;
	GetUserPreferredUILanguages(MUI_LANGUAGE_NAME, &v������, v�ı�, &v�ı���С);
	return v�ı�;
}

}	//namespace cflw::�Ӵ�