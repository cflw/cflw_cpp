//ע��:��ֻ��һ��ģ��,�������ƴ���,���ᱻ����
//����ͷ�ļ�
#include <Windows.h>
class C���� {
public:
	C����() {
		g�� = this;
	}
	void f��ʼ��(HINSTANCE hInst, HINSTANCE = nullptr, LPSTR = nullptr, int = 0) {
		mʵ�� = hInst;
		f��������();
	}
	void f����() {
		f��Ϣѭ��();
	}
	void f�ر�() {
		f�رմ���();
	}
private:
	static LRESULT WINAPI f���ڹ���(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {
		switch(msg) {
		case WM_DESTROY:
			PostQuitMessage(0);
			return 0;
		default:
			return DefWindowProc(hWnd, msg, wParam, lParam);
		}
	}
	//��������
	void f��������() {
		//ע�ᴰ��
		WNDCLASSEX wc;
		wc.cbSize = sizeof(WNDCLASSEX);			//ʹ��sizeof(WNDCLASSEX)
		wc.style = CS_CLASSDC;					//��������
		wc.lpfnWndProc = f���ڹ���;					//���ڹ���
		wc.cbClsExtra = 0L;							//��չ:
		wc.cbWndExtra = 0L;							//��չ:
		wc.hInstance = mʵ��;						//ʵ�����
		wc.hIcon = LoadIcon(nullptr, IDI_WINLOGO);	//����Ĭ��ͼ��
		wc.hCursor = LoadCursor(nullptr, IDC_ARROW);	//����Ĭ�Ϲ��
		wc.hbrBackground = nullptr;							//����Ҫ����
		wc.lpszMenuName = nullptr;							//����Ҫ�˵�
		wc.lpszClassName = c��������;					//��������
		wc.hIconSm = nullptr;
		RegisterClassEx(&wc);
		//���㴰�ڴ�С
		RECT v���ھ��� = {0, 0, m���ڴ�С[0], m���ڴ�С[1]};
		AdjustWindowRectEx(&v���ھ���, c���ڷ��, FALSE, c���ڷ��ex);
		m���ڴ�С[0] = v���ھ���.right - v���ھ���.left;
		m���ڴ�С[1] = v���ھ���.bottom - v���ھ���.top;
		//��������
		m���� = CreateWindowExW(
			c���ڷ��ex,
			c��������,					//��������
			c���ڱ���,					//���ڱ���
			c���ڷ��,					//���ڷ��
			CW_USEDEFAULT, CW_USEDEFAULT,	//����
			m���ڴ�С[0], m���ڴ�С[1],		//���ڳߴ�
			GetDesktopWindow(),			//���ھ������
			nullptr,					//�˵����
			mʵ��,						//ʵ�����
			nullptr);					//����
		//��ʾ����
		ShowWindow(m����, SW_SHOWDEFAULT);
		UpdateWindow(m����);
		//ȡ���ڿͻ�����С
		GetClientRect(m����, &v���ھ���);
		m���ڴ�С[0] = v���ھ���.right - v���ھ���.left;
		m���ڴ�С[1] = v���ھ���.bottom - v���ھ���.top;
	}
	//��Ϣѭ��
	void f��Ϣѭ��() {
		MSG msg = {};
		while (msg.message != WM_QUIT) {	//��Ϣѭ��
			if (PeekMessage(&msg, nullptr, 0U, 0U, PM_REMOVE)) {	//����Ϣʱ�Ĵ���,��Ҫ�޸�
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			} else {	//û����Ϣʱ�Ĵ���

			}
		}	//��Ϣѭ������
	}
	void f�رմ���() {
		UnregisterClassW(c��������, mʵ��);
	}
private:	//����
	const wchar_t *c�������� = L"W����";
	const wchar_t *c���ڱ��� = L"���ڱ���";
	const DWORD	c���ڷ�� = WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX;
	const DWORD	c���ڷ��ex = WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;
private:	//����
	HINSTANCE mʵ��;
	HWND m����;
	int m���ڴ�С[2] = {640, 480};
	static C���� *g��;
};
C���� *C����::g�� = nullptr;
//������
int WINAPI wWinMain(HINSTANCE hInst, HINSTANCE, LPWSTR, int) {
	C���� v����;
	v����.f��ʼ��(hInst);
	v����.f����();
	v����.f�ر�();
}