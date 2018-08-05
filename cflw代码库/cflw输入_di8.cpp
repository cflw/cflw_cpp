#include <assert.h>
#include "cflw����_di8.h"
#include "cflw��ѧ.h"
namespace cflw::����::di8 {
//==============================================================================
// ����
//==============================================================================
void f�����ж�(bool *a����, BYTE *a����, int p����) {
	for (int i = 0; i != p����; ++i) {
		a����[i] = (bool)(a����[i] & 0x80);
	}
}
//==============================================================================
// �ඨ��
//==============================================================================
// ����
class C���� : public I���� {
	friend class C����;
public:
	S���� f����(t���� i) const override;
	void f����() override;
private:
	ComPtr<IDirectInputDevice8W> m�豸;
	C������ m����{c��������};
};
// ���
class C��� : public I��� {
	friend class C����;
public:
	static const size_t c�������� = 4;
	C���();
	S���� f����(t���� i) const override;
	S���� f����() const override;
	S���� f�ƶ�() const override;
	S���� f����() const override;
	void f����() override;
private:
	ComPtr<IDirectInputDevice8W> m�豸;
	C������ m����{c��������};
	float m�ƶ�[3];
};
// �ֱ�
class C�ֱ� : public I�ֱ� {
	friend class C����;
public:
	static const size_t c�������� = 32;
	S���� f����(t����) const override;
	S���� f����(t����) const override;
	float f����(t����) const override;
	void f����() override;
private:
	ComPtr<IDirectInputDevice8W> m�豸;
	C������ m����{c��������};
	C����3 mҡ��, m��ҡ��;
};
//==============================================================================
// ��������
//==============================================================================
C���� *C����::g�� = nullptr;
C����::C����() {
	g�� = this;
}
C����::~C����() {
	f�ͷŽ���();
}
HRESULT C����::f��ʼ��(HINSTANCE aʵ��, HWND a����) {
	HRESULT hr;
	hr = DirectInput8Create(aʵ��, DIRECTINPUT_VERSION, IID_IDirectInput8W, (void**)&m�ӿ�, nullptr);
	if (FAILED(hr)) {
		return hr;
	}
	m���� = a����;
	return S_OK;
}
void C����::f������Ϣ(UINT a��Ϣ, WPARAM w) {
	switch (a��Ϣ) {
	case WM_ACTIVATE:
		if (w == WA_INACTIVE) {//�ͷŽ���
			f�ͷŽ���();
		} else {//��ý���
			f��ý���();
		}
		break;
	}
}
void C����::f��ý���() {
	if(m����) m����->m�豸->Acquire();
	if(m���) m���->m�豸->Acquire();
	if(m�ֱ�) m�ֱ�->m�豸->Acquire();
}
void C����::f�ͷŽ���() {
	if(m����) m����->m�豸->Unacquire();
	if(m���) m���->m�豸->Unacquire();
	if(m�ֱ�) m�ֱ�->m�豸->Unacquire();
}
void C����::f���� () {
	if (m����) {
		m����->f����();
	}
	if (m���) {
		m���->f����();
	}
	if (m�ֱ�) {
		m�ֱ�->f����();
	}
}
HRESULT C����::f��������(tp���� &a����) {
	if (m����) {
		a���� = m����;	//�����Ѵ���
		return S_OK;
	}
	std::shared_ptr<C����> v�¼��� = std::make_shared<C����>();
	HRESULT hr;
	hr = m�ӿ�->CreateDevice(GUID_SysKeyboard, &m����->m�豸, nullptr);
	if(FAILED(hr)) {
		return hr;
	}
	hr = m����->m�豸->SetDataFormat(&c_dfDIKeyboard);
	if(FAILED(hr)){
		return hr;
	}
	const DWORD cЭ��ģʽ = DISCL_NONEXCLUSIVE | DISCL_FOREGROUND;
	hr = m����->m�豸->SetCooperativeLevel(m����, cЭ��ģʽ);
	if(FAILED(hr)) {
		return hr;
	}
	DIPROPDWORD v����;
	v����.diph.dwSize = sizeof(DIPROPDWORD); 
	v����.diph.dwHeaderSize = sizeof(DIPROPHEADER); 
	v����.diph.dwObj = 0; 
	v����.diph.dwHow = DIPH_DEVICE; 
	v����.dwData = DINPUT_BUFFERSIZE; 
	hr = m����->m�豸->SetProperty(DIPROP_BUFFERSIZE, &v����.diph);
	if(FAILED(hr)) {
		return hr;
	}
	v�¼���->m�豸->Acquire();
	m���� = std::move(v�¼���);
	a���� = m����;
	return S_OK;
}
HRESULT C����::f�������(tp��� &a���) {
	if (m���) {
		a��� = m���;	//����Ѵ���
		return S_OK;
	}
	std::shared_ptr<C���> v����� = std::make_shared<C���>();
	HRESULT hr;
	hr = m�ӿ�->CreateDevice(GUID_SysMouse, &v�����->m�豸, nullptr);
	if (FAILED(hr)) {
		return hr;	//����ʧ��
	}
	const DWORD cЭ��ģʽ = DISCL_NONEXCLUSIVE | DISCL_FOREGROUND;
	hr = v�����->m�豸->SetCooperativeLevel(m����, cЭ��ģʽ);
	if(FAILED(hr)) {
		return hr;
	}
	hr = v�����->m�豸->SetDataFormat(&c_dfDIMouse)!=DI_OK;
	if(FAILED(hr)) {
		return hr;
	}
	v�����->m�豸->Acquire();
	m��� = std::move(v�����);
	a��� = m���;
	return S_OK;
}
HRESULT C����::f�����ֱ�(tp�ֱ� &a�ֱ�) {
	if (m�ֱ�) {
		a�ֱ� = m�ֱ�;	//�ֱ��Ѵ���
		return S_OK;
	}
	std::shared_ptr<C�ֱ�> v���ֱ� = std::make_shared<C�ֱ�>();
	HRESULT hr;
	hr = m�ӿ�->EnumDevices(DI8DEVCLASS_GAMECTRL, f�ص��ֱ�, v���ֱ�->m�豸.GetAddressOf(), DIEDFL_ATTACHEDONLY);
	if (FAILED(hr)) {	//����ʧ��
		return hr;
	}
	if (v���ֱ�->m�豸 == nullptr) {	//û�а�װ�ֱ�
		return S_FALSE;
	}
	//�������ݸ�ʽ
	hr = v���ֱ�->m�豸->SetDataFormat(&c_dfDIJoystick);
	if(FAILED(hr)) {
		return hr;
	}
	//����Э��ģʽ
	const DWORD cЭ��ģʽ = DISCL_NONEXCLUSIVE | DISCL_FOREGROUND;
	hr = v���ֱ�->m�豸->SetCooperativeLevel(m����, cЭ��ģʽ);
	if(FAILED(hr)) {
		return hr;
	}
	//����ҡ��
	DIPROPRANGE vҡ�˷�Χ;
	vҡ�˷�Χ.diph.dwSize = sizeof(DIPROPRANGE);
	vҡ�˷�Χ.diph.dwHeaderSize = sizeof(DIPROPHEADER);
	vҡ�˷�Χ.diph.dwObj = DIJOFS_X;
	vҡ�˷�Χ.diph.dwHow = DIPH_BYOFFSET;
	vҡ�˷�Χ.lMin = -256;
	vҡ�˷�Χ.lMax = 256;
	hr = v���ֱ�->m�豸->SetProperty(DIPROP_RANGE,&vҡ�˷�Χ.diph);
	if(FAILED(hr)) {
		return hr;
	}
	vҡ�˷�Χ.diph.dwObj = DIJOFS_Y;
	hr = v���ֱ�->m�豸->SetProperty(DIPROP_RANGE,&vҡ�˷�Χ.diph);
	if(FAILED(hr)) {
		return hr;
	}
	//�����ֱ��ɹ�
	v���ֱ�->m�豸->Acquire();
	m�ֱ� = std::move(v���ֱ�);
	a�ֱ� = m�ֱ�;
	return S_OK;
}
BOOL CALLBACK C����::f�ص��ֱ�(LPCDIDEVICEINSTANCE a�豸, LPVOID a����) {
	HRESULT hr = g��->m�ӿ�->CreateDevice(a�豸->guidInstance, (IDirectInputDevice8**)a����, nullptr);
	if (FAILED(hr)) {
		return DIENUM_CONTINUE;
	} else {
		return DIENUM_STOP;
	}
}
//==============================================================================
// ����
//==============================================================================
S���� C����::f����(t���� i) const {
	return m����.f����(i);
}
void C����::f����() {
	assert(m�豸);
	BYTE v����[c��������];
	m����.f�����ϴ�();
	HRESULT hr = m�豸->GetDeviceState(sizeof(v����), v����);
	if (SUCCEEDED(hr)) {
		f�����ж�(m����.m���, v����, c��������);
	}
}
//==============================================================================
// ���
//==============================================================================
C���::C���() {
}
S���� C���::f����(t���� i) const {
	return m����.f����(i);
}
S���� C���::f����() const {
	return S����{};
}
S���� C���::f�ƶ�() const {
	return S����{m�ƶ�[0], m�ƶ�[1], m�ƶ�[2]};
}
S���� C���::f����() const {
	return S����{};
}
void C���::f����() {
	assert(m�豸);
	m����.f�����ϴ�();
	DIMOUSESTATE v����;
	HRESULT hr = m�豸->GetDeviceState(sizeof(v����), &v����);
	if (SUCCEEDED(hr)) {
		//�ƶ�
		m�ƶ�[0] = (float)v����.lX;
		m�ƶ�[1] = (float)-v����.lY;
		m�ƶ�[2] = (float)v����.lZ;
		//����
		f�����ж�(m����.m���, v����.rgbButtons, c��������);
	}
}
//==============================================================================
// �ֱ�
//==============================================================================
S���� C�ֱ�::f����(t���� i) const {
	return m����.f����(i);
}
S���� C�ֱ�::f����(t���� i) const {
	switch (i) {
	case (t����)E�ֱ�����::e�����:
		return mҡ��.f����();
	case (t����)E�ֱ�����::e��ҡ��:
		return m��ҡ��.f����();
	default:
		return mҡ��.f����();
	}
}
float C�ֱ�::f����(t����) const {
	return 0;	//��֧��
}
void C�ֱ�::f����() {
	assert(m�豸);
	DIJOYSTATE v����;
	m����.f�����ϴ�();
	HRESULT hr = m�豸->GetDeviceState(sizeof(v����), &v����);
	if (FAILED(hr)) {
		hr = m�豸->Poll();
		if (FAILED(hr)) {
			hr = m�豸->Acquire();
		}
	}
	auto f = [](float (&p)[3], long x, long y, long z) {
		if (abs(x) < 32) {
			p[0] = 0;
		} else {
			p[0] = (float)x / 256.f;
		}
		if (abs(y) < 32) {
			p[1] = 0;
		} else {
			p[1] = (float)y / 256.f;
		}
		if (abs(z) < 32) {
			p[2] = 0;
		} else {
			p[2] = (float)z / 256.f;
		}
	};
	f(mҡ��.m����, v����.lX, v����.lY, v����.lZ);
	f(m��ҡ��.m����, v����.lRx, v����.lRy, v����.lRz);
	f�����ж�(m����.m���, v����.rgbButtons, c��������);
}
}	//namespace cflw::����::di8