#include "cflw图形_d3d11上12.h"
#include "cflw图形_d3d12.h"
#include "cflw辅助.h"
namespace cflw::图形::d3d11上12 {
HRESULT C三维::f初始化(d3d12::C三维 &a三维) {
	constexpr UINT c创建标志 = D3D11_CREATE_DEVICE_BGRA_SUPPORT |
		(c调试 ? D3D11_CREATE_DEVICE_DEBUG : 0);
	ComPtr<ID3D11Device> v设备;
	HRESULT hr = D3D11On12CreateDevice(a三维.m设备.Get(), c创建标志, nullptr, 0, (IUnknown**)a三维. m命令队列.GetAddressOf(), 1, 0, &v设备, &m上下文, nullptr);
	if (FAILED(hr)) {
		return hr;
	}
	v设备.As(&m设备);
	return S_OK;
}
HRESULT C三维::f创建渲染目标资源(ID3D12Resource *a资源) {
	static const D3D11_RESOURCE_FLAGS c资源标志 = {D3D11_BIND_RENDER_TARGET};
	ComPtr<ID3D11Resource> v资源;
	HRESULT hr = m设备->CreateWrappedResource(a资源, &c资源标志, D3D12_RESOURCE_STATE_RENDER_TARGET, D3D12_RESOURCE_STATE_PRESENT, IID_PPV_ARGS(&v资源));
	if (FAILED(hr)) {
		return hr;
	}
	ma渲染目标资源.push_back(v资源);
	return S_OK;
}
void C三维::f开始(UINT a帧索引) {
	m帧索引 = a帧索引;
	m设备->AcquireWrappedResources(ma渲染目标资源[m帧索引].GetAddressOf(), 1);
}
void C三维::f结束() {
	m设备->ReleaseWrappedResources(ma渲染目标资源[m帧索引].GetAddressOf(), 1);
	m上下文->Flush();
}
ComPtr<IDXGIDevice> C三维::fg基础设备() const {
	ComPtr<IDXGIDevice> v设备;
	m设备.As(&v设备);
	return v设备;
}
std::vector<ComPtr<ID3D11Resource>> &C三维::fe渲染目标资源() {
	return ma渲染目标资源;
}
}