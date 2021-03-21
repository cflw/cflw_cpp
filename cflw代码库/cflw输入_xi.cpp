#include <string>
#include <wbemidl.h>
#include <oleauto.h>
#include <wrl.h>
#include <xinput.h>
#include "cflw输入_xi.h"
#include "cflw时间.h"
#include "cflw数学.h"
namespace cflw::输入::xi {
using Microsoft::WRL::ComPtr;
constexpr float c死区 = 1.f / 16.f;
//==============================================================================
// 函数
//==============================================================================
bool IsXInputDevice(const GUID *pGuidProductFromDirectInput) {
	auto SAFE_RELEASE = [](IUnknown *p) {
		if (p) {
			p->Release();
		}
	};
	IWbemLocator*           pIWbemLocator = nullptr;
	IEnumWbemClassObject*   pEnumDevices = nullptr;
	IWbemClassObject*       pDevices[20] = {0};
	IWbemServices*          pIWbemServices = nullptr;
	BSTR                    bstrNamespace = nullptr;
	BSTR                    bstrDeviceID = nullptr;
	BSTR                    bstrClassName = nullptr;
	DWORD                   uReturned = 0;
	bool                    bIsXinputDevice = false;
	UINT                    iDevice = 0;
	VARIANT                 var;
	HRESULT                 hr;
	// CoInit if needed
	hr = CoInitialize(nullptr);
	bool bCleanupCOM = SUCCEEDED(hr);
	// Create WMI
	hr = CoCreateInstance(__uuidof(WbemLocator),
		nullptr,
		CLSCTX_INPROC_SERVER,
		__uuidof(IWbemLocator),
		(LPVOID*)&pIWbemLocator);
	if (FAILED(hr) || pIWbemLocator == nullptr)
		goto LCleanup;
	bstrNamespace = SysAllocString(L"\\\\.\\root\\cimv2");
	if (bstrNamespace == nullptr) goto LCleanup;
	bstrClassName = SysAllocString(L"Win32_PNPEntity");
	if (bstrClassName == nullptr) goto LCleanup;
	bstrDeviceID = SysAllocString(L"DeviceID");
	if (bstrDeviceID == nullptr)  goto LCleanup;

	// Connect to WMI 
	hr = pIWbemLocator->ConnectServer(bstrNamespace, nullptr, nullptr, 0L,
		0L, nullptr, nullptr, &pIWbemServices);
	if (FAILED(hr) || pIWbemServices == nullptr)
		goto LCleanup;
	// Switch security level to IMPERSONATE. 
	CoSetProxyBlanket(pIWbemServices, RPC_C_AUTHN_WINNT, RPC_C_AUTHZ_NONE, nullptr,
		RPC_C_AUTHN_LEVEL_CALL, RPC_C_IMP_LEVEL_IMPERSONATE, nullptr, EOAC_NONE);
	hr = pIWbemServices->CreateInstanceEnum(bstrClassName, 0, nullptr, &pEnumDevices);
	if (FAILED(hr) || pEnumDevices == nullptr)
		goto LCleanup;
	// Loop over all devices
	for (;; ) {
		// Get 20 at a time
		hr = pEnumDevices->Next(10000, 20, pDevices, &uReturned);
		if (FAILED(hr))
			goto LCleanup;
		if (uReturned == 0)
			break;
		for (iDevice = 0; iDevice<uReturned; iDevice++) {
			// For each device, get its device ID
			hr = pDevices[iDevice]->Get(bstrDeviceID, 0L, &var, nullptr, nullptr);
			if (SUCCEEDED(hr) && var.vt == VT_BSTR && var.bstrVal != nullptr) {
				// Check if the device ID contains "IG_".  If it does, then it's an XInput device
				// This information can not be found from DirectInput 
				if (wcsstr(var.bstrVal, L"IG_")) {
					// If it does, then get the VID/PID from var.bstrVal
					DWORD dwPid = 0, dwVid = 0;
					WCHAR* strVid = wcsstr(var.bstrVal, L"VID_");
					if (strVid && swscanf_s(strVid, L"VID_%4X", &dwVid) != 1)
						dwVid = 0;
					WCHAR* strPid = wcsstr(var.bstrVal, L"PID_");
					if (strPid && swscanf_s(strPid, L"PID_%4X", &dwPid) != 1)
						dwPid = 0;
					// Compare the VID/PID to the DInput device
					DWORD dwVidPid = MAKELONG(dwVid, dwPid);
					if (dwVidPid == pGuidProductFromDirectInput->Data1) {
						bIsXinputDevice = true;
						VariantClear(&var);
						goto LCleanup;
					}
				}
			}
			VariantClear(&var);
			SAFE_RELEASE(pDevices[iDevice]);
		}
	}
LCleanup:
	if (bstrNamespace)
		SysFreeString(bstrNamespace);
	if (bstrDeviceID)
		SysFreeString(bstrDeviceID);
	if (bstrClassName)
		SysFreeString(bstrClassName);
	for (iDevice = 0; iDevice<20; iDevice++)
		SAFE_RELEASE(pDevices[iDevice]);
	SAFE_RELEASE(pEnumDevices);
	SAFE_RELEASE(pIWbemLocator);
	SAFE_RELEASE(pIWbemServices);
	if (bCleanupCOM)
		CoUninitialize();
	return bIsXinputDevice;
}
float f计算方向无死区(SHORT a单向) {
	if (a单向 == 0) {
		return 0;
	}
	constexpr float c范围 = ((float)SHORT_MAX - (float)SHORT_MIN);
	return ((float)a单向 - (float)SHORT_MIN) / (c范围 / 2) - 1;
}
float f计算方向有死区(SHORT a单向, float a死区 = c死区) {
	const float v = f计算方向无死区(a单向);
	if (abs(v) <= a死区) {
		return 0;
	} else {
		return v;
	}
}
void f处理方向向量无死区(C方向3 &a方向, SHORT x, SHORT y) {
	const float vx = f计算方向无死区(x);
	const float vy = f计算方向无死区(y);
	a方向.m方向[0] = vx;
	a方向.m方向[1] = vy;
}
void f处理方向向量有死区(C方向3 &a方向, SHORT x, SHORT y, float a死区 = c死区) {
	const float vx = f计算方向无死区(x);
	const float vy = f计算方向无死区(y);
	if (hypotf(vx, vy) <= a死区) {
		a方向.m方向[0] = 0;
		a方向.m方向[1] = 0;
	} else {
		a方向.m方向[0] = vx;
		a方向.m方向[1] = vy;
	}
}
//==============================================================================
// 设备
//==============================================================================
class C手柄 : public I手柄 {
public:
	enum class E摇杆 {
		e左, e右
	};
	enum class E方向键 {
		x, y
	};
	C手柄(DWORD);
	void f更新() override;
	S按键 fg按键(t索引) const override;
	S方向 fg方向(t索引) const override;
	float fg触发(t索引) const override;
private:
	DWORD m序号, m包数 = 0, m上次状态 = 0;
	C按键组 m按键{16};
	C方向3 m摇杆[2] = {};
	C方向键 m方向键[2] = {
		{(int)E手柄按键::e右, (int)E手柄按键::e左}, 
		{(int)E手柄按键::e上, (int)E手柄按键::e下}
	};
	float m触发[2] = {};
	时间::C计时器 m计时器;	//手柄失效时延长取状态时间
};
//==============================================================================
// 输入
//==============================================================================
C输入::C输入() {
}
C输入::~C输入() {
}
输入::tp手柄 C输入::f创建手柄(DWORD a序号) {
	if (a序号 >= 4) {
		return nullptr;
	}
	std::shared_ptr<C手柄> &v手柄 = ma手柄[a序号];
	if (v手柄 == nullptr) {
		v手柄 = std::make_shared<C手柄>(a序号);
	}
	return v手柄;
}
void C输入::f更新() {
	for (const std::shared_ptr<C手柄> &v : ma手柄) {
		if (v) {
			v->f更新();
		}
	}
}
//==============================================================================
// 手柄
//==============================================================================
C手柄::C手柄(DWORD p序号) :
	m序号{p序号} {
}
S按键 C手柄::fg按键(t索引 i) const {
	return m按键.fg按键(i);
}
S方向 C手柄::fg方向(t索引 i) const {
	switch (i) {
	case (int)E手柄方向::e方向键:
		return {m方向键[(int)E方向键::x].m方向, m方向键[(int)E方向键::y].m方向, 0};
	case (int)E手柄方向::e左摇杆:
		return m摇杆[(int)E摇杆::e左].fg方向();
	case (int)E手柄方向::e右摇杆:
		return m摇杆[(int)E摇杆::e右].fg方向();
	default: {
		const float v最大x = 数学::f绝对值最大值(
			m方向键[(int)E方向键::x].m方向, 
			m摇杆[(int)E摇杆::e左].m方向[0], 
			m摇杆[(int)E摇杆::e右].m方向[0]);
		const float v最大y = 数学::f绝对值最大值(
			m方向键[(int)E方向键::y].m方向,
			m摇杆[(int)E摇杆::e左].m方向[1],
			m摇杆[(int)E摇杆::e右].m方向[1]);
		return {v最大x, v最大y, 0};
	}
	}
}
float C手柄::fg触发(t索引 i) const {
	return m触发[i];
}
void C手柄::f更新() {
	m按键.f覆盖上次();
	if (m计时器.f滴答()) {
		XINPUT_STATE v状态 = {};
		DWORD dr = XInputGetState(m序号, &v状态);
		if (dr == ERROR_SUCCESS) {
			if (m包数 != v状态.dwPacketNumber) {
				m包数 = v状态.dwPacketNumber;
				//按键
				for (t索引 i = 0; i != 16; ++i) {
					m按键.m这次[i] = v状态.Gamepad.wButtons & (1 << i);
				}
				//方向键
				m方向键[(int)E方向键::x].f更新(m按键);
				m方向键[(int)E方向键::y].f更新(m按键);
				//摇杆
				f处理方向向量无死区(m摇杆[(int)E摇杆::e左], v状态.Gamepad.sThumbLX, v状态.Gamepad.sThumbLY);
				f处理方向向量无死区(m摇杆[(int)E摇杆::e右], v状态.Gamepad.sThumbRX, v状态.Gamepad.sThumbRY);
				//触发
				m触发[0] = v状态.Gamepad.bLeftTrigger / 255.f;
				m触发[1] = v状态.Gamepad.bRightTrigger / 255.f;
			}
			if (m上次状态 != dr) {
				m计时器.fs间隔(0);
			}
		} else {
			m按键.f清空这次();
			if (m上次状态 != dr) {
				m计时器.fs间隔(2);
			}
		}
		m上次状态 = dr;
	}
}
}	//namespace cflw::输入::xi