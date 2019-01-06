#include "cflwͼ��_d3d11��12.h"
#include "cflwͼ��_d3d12.h"
#include "cflw����.h"
namespace cflw::ͼ��::d3d11��12 {
HRESULT C��ά::f��ʼ��(d3d12::C��ά &a��ά) {
	constexpr UINT c������־ = D3D11_CREATE_DEVICE_BGRA_SUPPORT |
		(c���� ? D3D11_CREATE_DEVICE_DEBUG : 0);
	ComPtr<ID3D11Device> v�豸;
	HRESULT hr = D3D11On12CreateDevice(a��ά.m�豸.Get(), c������־, nullptr, 0, (IUnknown**)a��ά. m�������.GetAddressOf(), 1, 0, &v�豸, &m������, nullptr);
	if (FAILED(hr)) {
		return hr;
	}
	v�豸.As(&m�豸);
	return S_OK;
}
HRESULT C��ά::f������ȾĿ����Դ(ID3D12Resource *a��Դ) {
	static const D3D11_RESOURCE_FLAGS c��Դ��־ = {D3D11_BIND_RENDER_TARGET};
	ComPtr<ID3D11Resource> v��Դ;
	HRESULT hr = m�豸->CreateWrappedResource(a��Դ, &c��Դ��־, D3D12_RESOURCE_STATE_RENDER_TARGET, D3D12_RESOURCE_STATE_PRESENT, IID_PPV_ARGS(&v��Դ));
	if (FAILED(hr)) {
		return hr;
	}
	ma��ȾĿ����Դ.push_back(v��Դ);
	return S_OK;
}
void C��ά::f��ʼ(UINT a֡����) {
	m֡���� = a֡����;
	m�豸->AcquireWrappedResources(ma��ȾĿ����Դ[m֡����].GetAddressOf(), 1);
}
void C��ά::f����() {
	m�豸->ReleaseWrappedResources(ma��ȾĿ����Դ[m֡����].GetAddressOf(), 1);
	m������->Flush();
}
ComPtr<IDXGIDevice> C��ά::fg�����豸() const {
	ComPtr<IDXGIDevice> v�豸;
	m�豸.As(&v�豸);
	return v�豸;
}
std::vector<ComPtr<ID3D11Resource>> &C��ά::fe��ȾĿ����Դ() {
	return ma��ȾĿ����Դ;
}
}