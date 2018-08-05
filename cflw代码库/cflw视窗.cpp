#include <math.h>
#include <string.h>
#include <algorithm>
#include "cflw�Ӵ�.h"
namespace cflw{
namespace �Ӵ�{
//--------------------------------------------------------------------------------
//��ʱ��
//--------------------------------------------------------------------------------
C��ʱ��::C��ʱ��() :vʱ��(0), v��ʱ(0), v���(0) {};
void C��ʱ��::f����(float p���) {
	vʱ�� = timeGetTime() / 1000.f;
	v��ʱ = 0;
	v��� = p���;
}
void C��ʱ��::f��ʱ() {
	float v�ϴ�ʱ�� = vʱ��;
	vʱ�� = timeGetTime() / 1000.f;
	v��ʱ += vʱ�� - v�ϴ�ʱ��;
}
int C��ʱ��::fg����() {
	return v����;
}
float C��ʱ��::fg��ʱ() {
	return v��εδ� - v�ϴεδ�;
}
int C��ʱ��::f�δ�() {
	f��ʱ();
	v���� = (int)floor(v��ʱ / v���);
	if (v����) {
		v�ϴεδ� = v��εδ�;
		v��εδ� = vʱ��;
		v��ʱ -= v���� * v���;
	}
	return v����;
}
int C��ʱ��::f���εδ�() {
	f��ʱ();
	if (v��ʱ >= v���) {
		v��ʱ -= v���;
		v�ϴεδ� = v��εδ�;
		v��εδ� = vʱ��;
		return v���� = 1;
	} else {
		return v���� = 0;
	}
}
int C��ʱ��::f��Ϸ�δ�() {
	f��ʱ();
	v���� = (int)floor(v��ʱ / v���);
	if (v����) {
		v��ʱ -= v���� * v���;
		v�ϴεδ� = v��εδ�;
		v��εδ� = vʱ��;
		if (v���� >= 2) {
			v��ʱ += v���;
		}
	}
	return v����;
}
//=============================================================================
// �ؼ���
//=============================================================================
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
//=============================================================================
// ���ڷ��
//=============================================================================
S���ڷ��::operator DWORD &() {
	return mһ����;
}
void S���ڷ��::fs���(bool) {}
void S���ڷ��::fs����(bool) {}
void S���ڷ��::fs�˵�(bool) {}
void S���ڷ��::fs�ť(bool /*��*/, bool /*С*/) {}
void S���ڷ��::fs������(bool /*��ֱ*/, bool /*ˮƽ*/) {}
void S���ڷ��::fs�������() {
	mһ���� = WS_OVERLAPPEDWINDOW;
}
void S���ڷ��::fs��������() {
	mһ���� = WS_POPUPWINDOW;
}
void S���ڷ��::fs�Ӵ���() {
	mһ���� = WS_CHILDWINDOW;
}
void S���ڷ��::fs��Ϸ����() {
	mһ���� = WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX;
	m��չ��� = WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;
}
//=============================================================================
// �ͻ����ߴ�
//=============================================================================
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
S�ͻ����ߴ� S�ͻ����ߴ�::fc�ߴ���(long px, long py, DWORD p���, DWORD p���ex) {
	RECT v���ڳߴ� = {0, 0, px, py};
	AdjustWindowRectEx(&v���ڳߴ�, p���, FALSE, p���ex);
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
//=============================================================================
// �������
//=============================================================================
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
//=============================================================================
// ��������ť
//=============================================================================
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
//=============================================================================
// ����
//=============================================================================
SYSTEM_INFO &C����::fgϵͳ��Ϣ() {
	static SYSTEM_INFO si = []()->SYSTEM_INFO {
		SYSTEM_INFO si;
		GetSystemInfo(&si);
		return si;
	}();
	return si;
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
//=============================================================================
// ���뷨
//=============================================================================
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
}}	//�����ռ����