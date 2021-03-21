#include <assert.h>
#include "cflw输入_di8.h"
#include "cflw数学.h"
namespace cflw::输入::di8 {
//==============================================================================
// 函数
//==============================================================================
void f按键判断(bool *a数组, BYTE *a数据, int p数量) {
	for (int i = 0; i != p数量; ++i) {
		a数组[i] = (bool)(a数据[i] & 0x80);
	}
}
//==============================================================================
// 类定义
//==============================================================================
// 键盘
class C键盘 : public I键盘 {
	friend class C输入;
public:
	S按键 fg按键(t索引 i) const override;
	void f更新() override;
private:
	ComPtr<IDirectInputDevice8W> m设备;
	C按键组 m按键{c按键数量};
};
// 鼠标
class C鼠标 : public I鼠标 {
	friend class C输入;
public:
	static const size_t c按键数量 = 4;
	C鼠标();
	S按键 fg按键(t索引 i) const override;
	S方向 fg坐标() const override;
	S方向 fg移动() const override;
	S方向 fg滚轮() const override;
	void f更新() override;
private:
	ComPtr<IDirectInputDevice8W> m设备;
	C按键组 m按键{c按键数量};
	float m移动[3];
};
// 手柄
class C手柄 : public I手柄 {
	friend class C输入;
public:
	static const size_t c按键数量 = 32;
	S按键 fg按键(t索引) const override;
	S方向 fg方向(t索引) const override;
	float fg触发(t索引) const override;
	void f更新() override;
private:
	ComPtr<IDirectInputDevice8W> m设备;
	C按键组 m按键{c按键数量};
	C方向3 m摇杆, m右摇杆;
};
//==============================================================================
// 输入引擎
//==============================================================================
C输入 *C输入::g这 = nullptr;
C输入::C输入() {
	g这 = this;
}
C输入::~C输入() {
	f释放焦点();
}
HRESULT C输入::f初始化(HINSTANCE a实例, HWND a窗口) {
	HRESULT hr;
	hr = DirectInput8Create(a实例, DIRECTINPUT_VERSION, IID_IDirectInput8W, (void**)&m接口, nullptr);
	if (FAILED(hr)) {
		return hr;
	}
	m窗口 = a窗口;
	return S_OK;
}
bool C输入::f窗口消息(UINT a消息, WPARAM w) {
	switch (a消息) {
	case WM_ACTIVATE:
		if (w == WA_INACTIVE) {//释放焦点
			f释放焦点();
		} else {//获得焦点
			f获得焦点();
		}
		return true;
	}
	return false;
}
void C输入::f获得焦点() {
	if(m键盘) m键盘->m设备->Acquire();
	if(m鼠标) m鼠标->m设备->Acquire();
	if(m手柄) m手柄->m设备->Acquire();
}
void C输入::f释放焦点() {
	if(m键盘) m键盘->m设备->Unacquire();
	if(m鼠标) m鼠标->m设备->Unacquire();
	if(m手柄) m手柄->m设备->Unacquire();
}
void C输入::f更新 () {
	if (m键盘) {
		m键盘->f更新();
	}
	if (m鼠标) {
		m鼠标->f更新();
	}
	if (m手柄) {
		m手柄->f更新();
	}
}
输入::tp键盘 C输入::f创建键盘() {
	if (m键盘) {	//键盘已存在
		return m键盘;
	}
	std::shared_ptr<C键盘> v新键盘 = std::make_shared<C键盘>();
	HRESULT hr;
	hr = m接口->CreateDevice(GUID_SysKeyboard, &m键盘->m设备, nullptr);
	if(FAILED(hr)) {
		return nullptr;
	}
	hr = m键盘->m设备->SetDataFormat(&c_dfDIKeyboard);
	if(FAILED(hr)){
		return nullptr;
	}
	const DWORD c协作模式 = DISCL_NONEXCLUSIVE | DISCL_FOREGROUND;
	hr = m键盘->m设备->SetCooperativeLevel(m窗口, c协作模式);
	if(FAILED(hr)) {
		return nullptr;
	}
	DIPROPDWORD v属性;
	v属性.diph.dwSize = sizeof(DIPROPDWORD); 
	v属性.diph.dwHeaderSize = sizeof(DIPROPHEADER); 
	v属性.diph.dwObj = 0; 
	v属性.diph.dwHow = DIPH_DEVICE; 
	v属性.dwData = DINPUT_BUFFERSIZE; 
	hr = m键盘->m设备->SetProperty(DIPROP_BUFFERSIZE, &v属性.diph);
	if(FAILED(hr)) {
		return nullptr;
	}
	v新键盘->m设备->Acquire();
	m键盘 = std::move(v新键盘);
	return m键盘;
}
输入::tp鼠标 C输入::f创建鼠标() {
	if (m鼠标) {	//鼠标已存在
		return m鼠标;
	}
	std::shared_ptr<C鼠标> v新鼠标 = std::make_shared<C鼠标>();
	HRESULT hr;
	hr = m接口->CreateDevice(GUID_SysMouse, &v新鼠标->m设备, nullptr);
	if (FAILED(hr)) {
		return nullptr;	//创建失败
	}
	const DWORD c协作模式 = DISCL_NONEXCLUSIVE | DISCL_FOREGROUND;
	hr = v新鼠标->m设备->SetCooperativeLevel(m窗口, c协作模式);
	if(FAILED(hr)) {
		return nullptr;
	}
	hr = v新鼠标->m设备->SetDataFormat(&c_dfDIMouse)!=DI_OK;
	if(FAILED(hr)) {
		return nullptr;
	}
	v新鼠标->m设备->Acquire();
	m鼠标 = std::move(v新鼠标);
	return m鼠标;
}
输入::tp手柄 C输入::f创建手柄() {
	if (m手柄) {	//手柄已存在
		return m手柄;
	}
	std::shared_ptr<C手柄> v新手柄 = std::make_shared<C手柄>();
	HRESULT hr;
	hr = m接口->EnumDevices(DI8DEVCLASS_GAMECTRL, f回调手柄, v新手柄->m设备.GetAddressOf(), DIEDFL_ATTACHEDONLY);
	if (FAILED(hr)) {	//创建失败
		return nullptr;
	}
	if (v新手柄->m设备 == nullptr) {	//没有安装手柄
		return nullptr;
	}
	//设置数据格式
	hr = v新手柄->m设备->SetDataFormat(&c_dfDIJoystick);
	if(FAILED(hr)) {
		return nullptr;
	}
	//设置协作模式
	const DWORD c协作模式 = DISCL_NONEXCLUSIVE | DISCL_FOREGROUND;
	hr = v新手柄->m设备->SetCooperativeLevel(m窗口, c协作模式);
	if(FAILED(hr)) {
		return nullptr;
	}
	//设置摇杆
	DIPROPRANGE v摇杆范围;
	v摇杆范围.diph.dwSize = sizeof(DIPROPRANGE);
	v摇杆范围.diph.dwHeaderSize = sizeof(DIPROPHEADER);
	v摇杆范围.diph.dwObj = DIJOFS_X;
	v摇杆范围.diph.dwHow = DIPH_BYOFFSET;
	v摇杆范围.lMin = -256;
	v摇杆范围.lMax = 256;
	hr = v新手柄->m设备->SetProperty(DIPROP_RANGE,&v摇杆范围.diph);
	if(FAILED(hr)) {
		return nullptr;
	}
	v摇杆范围.diph.dwObj = DIJOFS_Y;
	hr = v新手柄->m设备->SetProperty(DIPROP_RANGE,&v摇杆范围.diph);
	if(FAILED(hr)) {
		return nullptr;
	}
	//创建手柄成功
	v新手柄->m设备->Acquire();
	m手柄 = std::move(v新手柄);
	return m手柄;
}
BOOL CALLBACK C输入::f回调手柄(LPCDIDEVICEINSTANCE a设备, LPVOID a引用) {
	HRESULT hr = g这->m接口->CreateDevice(a设备->guidInstance, (IDirectInputDevice8**)a引用, nullptr);
	if (FAILED(hr)) {
		return DIENUM_CONTINUE;
	} else {
		return DIENUM_STOP;
	}
}
//==============================================================================
// 键盘
//==============================================================================
S按键 C键盘::fg按键(t索引 i) const {
	return m按键.fg按键(i);
}
void C键盘::f更新() {
	assert(m设备);
	BYTE v数据[c按键数量];
	m按键.f覆盖上次();
	HRESULT hr = m设备->GetDeviceState(sizeof(v数据), v数据);
	if (SUCCEEDED(hr)) {
		f按键判断(m按键.m这次, v数据, c按键数量);
	}
}
//==============================================================================
// 鼠标
//==============================================================================
C鼠标::C鼠标() {
}
S按键 C鼠标::fg按键(t索引 i) const {
	return m按键.fg按键(i);
}
S方向 C鼠标::fg坐标() const {
	return S方向{};
}
S方向 C鼠标::fg移动() const {
	return S方向{m移动[0], m移动[1], m移动[2]};
}
S方向 C鼠标::fg滚轮() const {
	return S方向{};
}
void C鼠标::f更新() {
	assert(m设备);
	m按键.f覆盖上次();
	DIMOUSESTATE v数据;
	HRESULT hr = m设备->GetDeviceState(sizeof(v数据), &v数据);
	if (SUCCEEDED(hr)) {
		//移动
		m移动[0] = (float)v数据.lX;
		m移动[1] = (float)-v数据.lY;
		m移动[2] = (float)v数据.lZ;
		//按键
		f按键判断(m按键.m这次, v数据.rgbButtons, c按键数量);
	}
}
//==============================================================================
// 手柄
//==============================================================================
S按键 C手柄::fg按键(t索引 i) const {
	return m按键.fg按键(i);
}
S方向 C手柄::fg方向(t索引 i) const {
	switch (i) {
	case (t索引)E手柄方向::e方向键:
		return m摇杆.fg方向();
	case (t索引)E手柄方向::e右摇杆:
		return m右摇杆.fg方向();
	default:
		return m摇杆.fg方向();
	}
}
float C手柄::fg触发(t索引) const {
	return 0;	//不支持
}
void C手柄::f更新() {
	assert(m设备);
	DIJOYSTATE v数据;
	m按键.f覆盖上次();
	HRESULT hr = m设备->GetDeviceState(sizeof(v数据), &v数据);
	if (FAILED(hr)) {
		hr = m设备->Poll();
		if (FAILED(hr)) {
			hr = m设备->Acquire();
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
	f(m摇杆.m方向, v数据.lX, v数据.lY, v数据.lZ);
	f(m右摇杆.m方向, v数据.lRx, v数据.lRy, v数据.lRz);
	f按键判断(m按键.m这次, v数据.rgbButtons, c按键数量);
}
}	//namespace cflw::输入::di8