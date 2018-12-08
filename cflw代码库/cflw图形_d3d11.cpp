#include <array>
#include <wrl.h>
#include <D3Dcompiler.h>
#include "cflwͼ��_d3d11.h"
#include "cflw�Ӵ�.h"
using Microsoft::WRL::ComPtr;
namespace cflw::ͼ��::d3d11 {
//==============================================================================
// ͼ������
//==============================================================================
C��ά::~C��ά() {
	f����();
}
void C��ά::f����() {
	//��ͨ����
	m��ɫ������.reset();
	m���幤��.reset();
	m������.reset();
	m��Ⱦ״̬.reset();
	m��Ⱦ����.reset();
	m��Ⱦ����.reset();
	//com����
	m������.Reset();
	m��ȾĿ����ͼ.Reset();
	m���ģ��.Reset();
	m���ģ����ͼ.Reset();
	m������.Reset();
	if (c���� && m�豸) {
		ComPtr<ID3D11Debug> v����;
		HRESULT hr = m�豸->QueryInterface(IID_PPV_ARGS(&v����));
		if (SUCCEEDED(hr)) {
			hr = v����->ReportLiveDeviceObjects(D3D11_RLDO_DETAIL);
		}
	}
	m�豸.Reset();
}
void C��ά::f��ʼ������(HWND a) {
	assert(a);
	m���� = a;
	�Ӵ�::S�ͻ����ߴ� v�ߴ� = �Ӵ�::S�ͻ����ߴ�::fc����(m����);
	m���ڴ�С[0] = v�ߴ�.fg��();
	m���ڴ�С[1] = v�ߴ�.fg��();
}
HRESULT C��ά::f��ʼ���豸() {
	m�����豸 = std::make_unique<C�����豸>();
	//��������
	m��־[e����] = c����;
	HRESULT hr = m�����豸->f��������();
	if (FAILED(hr)) {
		if (hr == DXGI_ERROR_SDK_COMPONENT_MISSING) {
			m�����豸->fs���Ա�־(false);
			m��־[e����] = false;
		} else {
			return hr;
		}
	}
	//ö��������
	ComPtr<IDXGIAdapter1> v�Կ�;
	hr = m�����豸->fȡ�Կ�(&v�Կ�);
	if (hr == DXGI_ERROR_UNSUPPORTED) {//0x887A0004 Ӳ����������֧��
		hr = m�����豸->f��������豸(&m�豸, &m������);
		if (FAILED(hr)) {
			return hr;
		}
		m��־[e����豸] = true;
	} else {
		hr = m�����豸->f�����豸(v�Կ�.Get(), &m�豸, &m������);
		if (FAILED(hr)) {
			return hr;
		}
	}
	//��鿹��ݵȼ�
	m�豸->CheckMultisampleQualityLevels(c��������ʽ, 4, &m����ݵȼ�);
	if (m��ǰ����ݵȼ� > m����ݵȼ�) {
		m��ǰ����ݵȼ� = m����ݵȼ�;
	}
	//����
	return S_OK;
}
HRESULT C��ά::f��ʼ��������() {
	//����������
	DXGI_SWAP_CHAIN_DESC sd;
	����::f����(sd);
	sd.BufferCount = 1;
	sd.BufferDesc.Width = m���ڴ�С[0];
	sd.BufferDesc.Height = m���ڴ�С[1];
	sd.BufferDesc.Format = c��������ʽ;
	sd.BufferDesc.RefreshRate.Numerator = 60;
	sd.BufferDesc.RefreshRate.Denominator = 1;
	sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	sd.OutputWindow = m����;
	sd.SampleDesc = f���㿹���(m��ǰ����ݵȼ�);
	sd.Windowed = TRUE;
	//����������
	ComPtr<IDXGIFactory1> v�������� = m�����豸->fg����();
	HRESULT hr = hr = v��������->CreateSwapChain(m�豸.Get(), &sd, &m������);
	if(FAILED(hr)) {
		return hr;
	}
	return S_OK;
}
HRESULT C��ά::f��ʼ����ȾĿ����ͼ() {
	ComPtr<ID3D11Texture2D> v��̨����;
	HRESULT hr = m������->GetBuffer(0, IID_PPV_ARGS(&v��̨����));
	if(FAILED(hr)) {
		return hr;
	}
	hr = m�豸->CreateRenderTargetView(v��̨����.Get(), nullptr, &m��ȾĿ����ͼ);
	return S_OK;
}
HRESULT C��ά::f��ʼ�����ģ����ͼ() {
	// �������ģ��
	D3D11_TEXTURE2D_DESC v��������;
	ZeroMemory(&v��������, sizeof(v��������));
	v��������.Width = m���ڴ�С[0];
	v��������.Height = m���ڴ�С[1];
	v��������.MipLevels = 1;
	v��������.ArraySize = 1;
	v��������.Format = c���ģ���ʽ;
	v��������.SampleDesc = f���㿹���(m��ǰ����ݵȼ�);
	v��������.Usage = D3D11_USAGE_DEFAULT;
	v��������.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	v��������.CPUAccessFlags = 0;
	v��������.MiscFlags = 0;
	HRESULT hr = m�豸->CreateTexture2D(&v��������, nullptr, &m���ģ��);
	if(FAILED(hr)) {
		return hr;
	}
	// �������ģ����ͼ
	D3D11_DEPTH_STENCIL_VIEW_DESC v���ģ����ͼ����;
	ZeroMemory(&v���ģ����ͼ����, sizeof(v���ģ����ͼ����));
	v���ģ����ͼ����.Format = v��������.Format;
	v���ģ����ͼ����.ViewDimension = (m��ǰ����ݵȼ� > 0) ? D3D11_DSV_DIMENSION_TEXTURE2DMS :  D3D11_DSV_DIMENSION_TEXTURE2D;
	v���ģ����ͼ����.Texture2D.MipSlice = 0;
	hr = m�豸->CreateDepthStencilView(m���ģ��.Get(), &v���ģ����ͼ����, &m���ģ����ͼ);
	if (FAILED(hr)) {
		return hr;
	}
	m������->OMSetRenderTargets(1, m��ȾĿ����ͼ.GetAddressOf(), m���ģ����ͼ.Get());
	return S_OK;
}
//��ʼ��
bool C��ά::f��ʼ��(HWND a) {
	try {
		f��ʼ������(a);
		�Ӵ�::fʧ�����׳�(f��ʼ���豸());
		�Ӵ�::fʧ�����׳�(f��ʼ��������());
		�Ӵ�::fʧ�����׳�(f��ʼ����ȾĿ����ͼ());
		�Ӵ�::fʧ�����׳�(f��ʼ�����ģ����ͼ());
		m������->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
		f�����ӿ�();
		return true;
	} catch (HRESULT hr) {
		return false;
	}
}
HRESULT C��ά::f�������벼��(tp���벼�� &a���벼��, C�����ʽ &a�����ʽ, const void *a����, size_t a��С) {
	return m�豸->CreateInputLayout(a�����ʽ.m����.data(), a�����ʽ.m����.size(), a����, a��С, &a���벼��);
}
HRESULT C��ά::f����ͼ�ι���(tpͼ�ι��� &a, const Sͼ�ι��߲��� &a����) {
	C��ɫ������ &v��ɫ������ = fg��ɫ������();
	HRESULT hr;
	std::shared_ptr<Cͼ�ι���> v = std::make_shared<Cͼ�ι���>();
	if (a����.m������ɫ��) {
		hr = v��ɫ������.f����������ɫ��(v->m������ɫ��, a����.m������ɫ��);
		if (FAILED(hr)) {
			return hr;
		}
		if (a����.m�����ʽ) {
			hr = v��ɫ������.f�������벼��(v->m���벼��, a����.m������ɫ��, *a����.m�����ʽ);
			if (FAILED(hr)) {
				return hr;
			}
		}
	}
	if (a����.m������ɫ��) {
		hr = v��ɫ������.f����������ɫ��(v->m������ɫ��, a����.m������ɫ��);
		if (FAILED(hr)) {
			return hr;
		}
	}
	if (a����.m�����ɫ��) {
		hr = v��ɫ������.f���������ɫ��(v->m�����ɫ��, a����.m�����ɫ��);
		if (FAILED(hr)) {
			return hr;
		}
	}
	if (a����.m����ɫ��) {
		hr = v��ɫ������.f��������ɫ��(v->m����ɫ��, a����.m����ɫ��);
		if (FAILED(hr)) {
			return hr;
		}
	}
	if (a����.m������ɫ��) {
		hr = v��ɫ������.f����������ɫ��(v->m������ɫ��, a����.m������ɫ��);
		if (FAILED(hr)) {
			return hr;
		}
	}
	if (std::holds_alternative<D3D11_RASTERIZER_DESC>(a����.m��դ��)) {
		m�豸->CreateRasterizerState(&std::get<D3D11_RASTERIZER_DESC>(a����.m��դ��), &v->m��դ��);
	} else {
		v->m��դ�� = std::get<ID3D11RasterizerState*>(a����.m��դ��);
	}
	if (std::holds_alternative<D3D11_BLEND_DESC>(a����.m���)) {
		m�豸->CreateBlendState(&std::get<D3D11_BLEND_DESC>(a����.m���), &v->m���);
	} else {
		v->m��� = std::get<ID3D11BlendState*>(a����.m���);
	}
	if (std::holds_alternative<D3D11_DEPTH_STENCIL_DESC>(a����.m���ģ��)) {
		m�豸->CreateDepthStencilState(&std::get<D3D11_DEPTH_STENCIL_DESC>(a����.m���ģ��), &v->m���ģ��);
	} else {
		v->m���ģ�� = std::get<ID3D11DepthStencilState*>(a����.m���ģ��);
	}
	a = std::move(v);
	return S_OK;
}
void C��ά::f�����ӿ�() {
	const D3D11_VIEWPORT &v�����ӿ� = fg�����ӿ�();
	m������->RSSetViewports(1, &v�����ӿ�);
}
//�����
HRESULT C��ά::f���ÿ����(UINT a) {
	assert(m�豸 != nullptr);
	assert(m����ݵȼ� >= a);
	HRESULT hr;
	if (m����ݵȼ� < a) {
		m��ǰ����ݵȼ� = m����ݵȼ�;
	} else {
		m��ǰ����ݵȼ� = a;
	}
	if (m������) {
		m������ = nullptr;
		hr = f��ʼ��������();
		if(FAILED(hr)) {
			return hr;
		}
	}
	if (m���ģ��) {
		hr = f��ʼ�����ģ����ͼ();
		if(FAILED(hr)) {
			return hr;
		}
	}
	return S_OK;
}
DXGI_SAMPLE_DESC C��ά::f���㿹���(UINT a) {
	DXGI_SAMPLE_DESC v;
	v.Count = (a < 1) ? 1 : 4;
	v.Quality = (a < 1) ? 0 : (a - 1);
	return v;
}
C��Ⱦ���� &C��ά::fg��Ⱦ����() {
	if (m��Ⱦ���� == nullptr) {
		m��Ⱦ���� = std::make_unique<C��Ⱦ����>();
		m��Ⱦ����->m������ = m������;
		m��Ⱦ����->m������ = m������;
		m��Ⱦ����->m��ȾĿ����ͼ = m��ȾĿ����ͼ;
		m��Ⱦ����->m���ģ����ͼ = m���ģ����ͼ;
	}
	return *m��Ⱦ����;
}
C��Ⱦ״̬ &C��ά::fg��Ⱦ״̬() {
	if (m��Ⱦ״̬ == nullptr) {
		m��Ⱦ״̬ = std::make_unique<C��Ⱦ״̬>(m�豸.Get());
	}
	return *m��Ⱦ״̬;
}
ComPtr<ID3D11Device> C��ά::fg�豸() const {
	return m�豸;
}
ComPtr<IDXGIDevice> C��ά::fg�����豸() const {
	ComPtr<IDXGIDevice> v�豸;
	m�豸.As(&v�豸);
	return v�豸;
}
ComPtr<ID3D11DeviceContext> C��ά::fg������() const {
	return m������;
}
ComPtr<IDXGISwapChain> C��ά::fg������() const {
	return m������;
}
D3D11_VIEWPORT C��ά::fg�����ӿ�() const {
	D3D11_VIEWPORT vp;
	vp.Width = (FLOAT)m���ڴ�С[0];
	vp.Height = (FLOAT)m���ڴ�С[1];
	vp.MinDepth = 0.0f;
	vp.MaxDepth = 1.0f;
	vp.TopLeftX = 0;
	vp.TopLeftY = 0;
	return vp;
}
��ѧ::S����2 C��ά::fg���ڴ�С() const {
	return {(float)m���ڴ�С[0], (float)m���ڴ�С[1]};
}
//����
C���幤�� &C��ά::fg���幤��() {
	if (m���幤�� == nullptr) {
		m���幤�� = std::make_unique<C���幤��>();
		m���幤��->f��ʼ��(m�豸.Get());
	}
	return *m���幤��;
}
C������ &C��ά::fg������() {
	if (m������ == nullptr) {
		m������ = std::make_unique<C������>();
		m������->f��ʼ��(m�豸.Get());
	}
	return *m������;
}
C��ɫ������ &C��ά::fg��ɫ������() {
	if (m��ɫ������ == nullptr) {
		m��ɫ������ = std::make_unique<C��ɫ������>();
		m��ɫ������->f��ʼ��(m�豸.Get());
	}
	return *m��ɫ������;
}
//==============================================================================
// �����豸
//==============================================================================
const D3D_FEATURE_LEVEL C�����豸::c���ܼ�����[3] = {
	D3D_FEATURE_LEVEL_11_0,
	D3D_FEATURE_LEVEL_10_1,
	D3D_FEATURE_LEVEL_10_0
};
const UINT C�����豸::c������־ = D3D11_CREATE_DEVICE_BGRA_SUPPORT | (c���� ? D3D11_CREATE_DEVICE_DEBUG : 0);
HRESULT C�����豸::f��������() {
	HRESULT hr = D3D11CreateDevice(nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr, m������־, c���ܼ�����, c���ܼ�����, D3D11_SDK_VERSION, nullptr, &m���ܼ���, nullptr);
	return hr;
}
ComPtr<IDXGIFactory1> C�����豸::fg����() {
	if (m���� == nullptr) {
		HRESULT hr = CreateDXGIFactory1(IID_PPV_ARGS(&m����));
		if (FAILED(hr)) {
			return nullptr;
		}
	}
	return m����;
}
HRESULT C�����豸::fȡ�Կ�(IDXGIAdapter1 **a���) {
	HRESULT hr = S_OK;
	if (m���� == nullptr) {
		hr = CreateDXGIFactory1(IID_PPV_ARGS(&m����));
		if (FAILED(hr)) {
			return hr;
		}
	}
	ComPtr<IDXGIAdapter1> v������;
	ComPtr<IDXGIAdapter1> vĿ���Կ�;
	D3D_FEATURE_LEVEL vĿ��ȼ� = D3D_FEATURE_LEVEL_10_0;
	SIZE_T v�Դ� = 0;
	for (UINT i = 0; m����->EnumAdapters1(i, &v������) != DXGI_ERROR_NOT_FOUND; ++i) {
		DXGI_ADAPTER_DESC1 v����;
		v������->GetDesc1(&v����);
		D3D_FEATURE_LEVEL v֧�ּ���;
		hr = D3D11CreateDevice(v������.Get(), D3D_DRIVER_TYPE_UNKNOWN, nullptr, m������־, c���ܼ�����, c���ܼ�����, D3D11_SDK_VERSION, nullptr, &v֧�ּ���, nullptr);
		if (FAILED(hr)) {
			//0x887a002dӦ�ó�������Ĳ�����������ȱʧ��ƥ��� SDK ���
			__debugbreak();
			continue;
		}
		if (v����.Flags & DXGI_ADAPTER_FLAG_SOFTWARE) {
			continue;
		}
		bool v���� = false;
		if (v֧�ּ��� > vĿ��ȼ�) {
			if (v����.DedicatedVideoMemory > 0) {
				v���� = true;
			}
		} else if (v֧�ּ��� == vĿ��ȼ�) {
			if (v����.DedicatedVideoMemory > v�Դ�) {
				v���� = true;
			}
		}
		if (v����) {
			vĿ���Կ� = v������;
			vĿ��ȼ� = v֧�ּ���;
			v�Դ� = v����.DedicatedVideoMemory;
		}
	}
	*a��� = vĿ���Կ�.Detach();
	return hr;
}
void C�����豸::fs���Ա�־(bool a) {
	m������־ = ����::fλ��ֵ<UINT>(m������־, D3D11_CREATE_DEVICE_DEBUG, a);
}
HRESULT C�����豸::f�����豸(IDXGIAdapter1 *p�Կ�, ID3D11Device **a�豸, ID3D11DeviceContext **p������) {
	HRESULT hr = D3D11CreateDevice(p�Կ�, D3D_DRIVER_TYPE_UNKNOWN, nullptr, m������־, c���ܼ�����, c���ܼ�����, D3D11_SDK_VERSION, a�豸, &m���ܼ���, p������);
	return hr;
}
HRESULT C�����豸::f��������豸(ID3D11Device **a�豸, ID3D11DeviceContext **p������) {
	HRESULT hr = D3D11CreateDevice(nullptr, D3D_DRIVER_TYPE_WARP, nullptr, m������־, c���ܼ�����, c���ܼ�����, D3D11_SDK_VERSION, a�豸, &m���ܼ���, p������);
	return hr;
}
//==============================================================================
// ��Ⱦ����
//==============================================================================
//����
C��Ⱦ����::C��Ⱦ����() {
}
void C��Ⱦ����::f����() {
	m������->ClearRenderTargetView(m��ȾĿ����ͼ.Get(), m������ɫ.mֵ);
	if (m���ģ����ͼ) {
		m������->ClearDepthStencilView(m���ģ����ͼ.Get(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, m�������, m����ģ��);
	}
}
//��ʾ
void C��Ⱦ����::f��ʾ() {
	m������->Present(0, 0);
}
//����
void C��Ⱦ����::f����(unsigned int a������, unsigned int a��ʼ) {
	m������->Draw(a������, a��ʼ);
}
void C��Ⱦ����::f��������(unsigned int a������, unsigned int a��ʼ, int a��ʼ����) {
	m������->DrawIndexed(a������, a��ʼ, a��ʼ����);
}
void C��Ⱦ����::fs������ɫ(const ��ѧ::S��ɫ &a) {
	m������ɫ = a;
}
void C��Ⱦ����::fs�������(float a) {
	m������� = a;
}
void C��Ⱦ����::fs����ģ��(UINT8 a) {
	m����ģ�� = a;
}
void C��Ⱦ����::fsͼ�ι���(const Cͼ�ι��� &a) {
	fs������ɫ��(a.m������ɫ��.Get());
	fs�����ɫ��(a.m�����ɫ��.Get());
	fs����ɫ��(a.m����ɫ��.Get());
	fs������ɫ��(a.m������ɫ��.Get());
	fs������ɫ��(a.m������ɫ��.Get());
	fs���벼��(a.m���벼��.Get());
	fs���(a.m���.Get());
	fs���ģ��(a.m���ģ��.Get());
	fs��դ��(a.m��դ��.Get());
}
//������ɫ��
void C��Ⱦ����::f������ɫ��() {
	m������->VSSetShader(nullptr, nullptr, 0);
	m������->HSSetShader(nullptr, nullptr, 0);
	m������->DSSetShader(nullptr, nullptr, 0);
	m������->GSSetShader(nullptr, nullptr, 0);
	m������->PSSetShader(nullptr, nullptr, 0);
	m������->CSSetShader(nullptr, nullptr, 0);
}
void C��Ⱦ����::fs������ɫ��(ID3D11VertexShader *a) {
	m������->VSSetShader(a, nullptr, 0);
}
void C��Ⱦ����::fs������ɫ��(ID3D11PixelShader *a) {
	m������->PSSetShader(a, nullptr, 0);
}
void C��Ⱦ����::fs������ɫ��(ID3D11GeometryShader *a) {
	m������->GSSetShader(a, nullptr, 0);
}
void C��Ⱦ����::fs�����ɫ��(ID3D11HullShader *a) {
	m������->HSSetShader(a, nullptr, 0);
}
void C��Ⱦ����::fs����ɫ��(ID3D11DomainShader *a) {
	m������->DSSetShader(a, nullptr, 0);
}
//״̬
void C��Ⱦ����::fs���(ID3D11BlendState *a���, const ��ѧ::S��ɫ &a��ɫ, UINT a����) {
	m������->OMSetBlendState(a���, (float*)&a��ɫ, a����);
}
void C��Ⱦ����::fs���ģ��(ID3D11DepthStencilState *a���ģ��, UINT a�ο�) {
	m������->OMSetDepthStencilState(a���ģ��, a�ο�);
}
void C��Ⱦ����::fsģ��ο�ֵ(UINT a�ο�) {
	ComPtr<ID3D11DepthStencilState> v���ģ��;
	UINT v�ο�;
	m������->OMGetDepthStencilState(&v���ģ��, &v�ο�);
	v�ο� = a�ο�;
	m������->OMSetDepthStencilState(v���ģ��.Get(), v�ο�);
}
void C��Ⱦ����::fs��դ��(ID3D11RasterizerState *a��դ��) {
	m������->RSSetState(a��դ��);
}
void C��Ⱦ����::fs���㻺��(ID3D11Buffer *a, UINT a��λ��С) {
	UINT vƫ�� = 0;
	m������->IASetVertexBuffers(0, 1, &a, &a��λ��С, &vƫ��);
}
void C��Ⱦ����::fs��������(ID3D11Buffer *a) {
	m������->IASetIndexBuffer(a, DXGI_FORMAT_R16_UINT, 0);
}
void C��Ⱦ����::fs��������(UINT aλ��, ID3D11Buffer *a����) {
	m������->VSSetConstantBuffers(aλ��, 1, &a����);
	m������->PSSetConstantBuffers(aλ��, 1, &a����);
	m������->HSSetConstantBuffers(aλ��, 1, &a����);
	m������->DSSetConstantBuffers(aλ��, 1, &a����);
	m������->GSSetConstantBuffers(aλ��, 1, &a����);
}
void C��Ⱦ����::fs��������v(UINT aλ��, ID3D11Buffer *a����) {
	m������->VSSetConstantBuffers(aλ��, 1, &a����);
}
void C��Ⱦ����::fs��������p(UINT aλ��, ID3D11Buffer *a����) {
	m������->PSSetConstantBuffers(aλ��, 1, &a����);
}
void C��Ⱦ����::fs��������g(UINT aλ��, ID3D11Buffer *a����) {
	m������->GSSetConstantBuffers(aλ��, 1, &a����);
}
void C��Ⱦ����::fs��������h(UINT aλ��, ID3D11Buffer *a����) {
	m������->HSSetConstantBuffers(aλ��, 1, &a����);
}
void C��Ⱦ����::fs��������d(UINT aλ��, ID3D11Buffer *a����) {
	m������->DSSetConstantBuffers(aλ��, 1, &a����);
}
void C��Ⱦ����::fs����(UINT aλ��, ID3D11ShaderResourceView *a����) {
	m������->PSSetShaderResources(aλ��, 1, &a����);
}
void C��Ⱦ����::fs������(UINT aλ��, ID3D11SamplerState *a������) {
	m������->PSSetSamplers(aλ��, 1, &a������);
}
void C��Ⱦ����::fs���벼��(ID3D11InputLayout *a����) {
	m������->IASetInputLayout(a����);
}
void C��Ⱦ����::fsͼԪ����(EͼԪ���� a����) {
	m������->IASetPrimitiveTopology((D3D11_PRIMITIVE_TOPOLOGY)a����);
}
void C��Ⱦ����::f������Դ(ID3D11Buffer *a����, const void *a��Դ) {
	assert(a����);
	m������->UpdateSubresource(a����, 0, nullptr, a��Դ, 0, 0);
}

//==============================================================================
// ͼ�ι���
//==============================================================================
C�Զ�����::C�Զ�����(C��ά &a��ά) : 
	m������(a��ά.fg������().Get()),
	m���幤��(&a��ά.fg���幤��()),
	m���㻺��(*m������, *m���幤��, E����::e����),
	m��������(*m������, *m���幤��, E����::e����) {
}
bool C�Զ�����::fˢ��() {
	if (m���㻺��.m�޸� == 0 && m��������.m�޸� == 0) {
		return false;
	}
	const bool vȡ��ӳ�䶥�� = m���㻺��.fȡ��ӳ��();
	const bool vȡ��ӳ������ = m��������.fȡ��ӳ��();
	const bool vˢ�� = vȡ��ӳ�䶥�� || vȡ��ӳ������;
	if (vˢ��) {
		if (mfˢ�»ص�) {
			mfˢ�»ص�();
		}
		UINT v����ƫ�� = 0;
		m������->IASetVertexBuffers(0, 1, m���㻺��.m����.GetAddressOf(), &m���㻺��.m��λ��С, &v����ƫ��);
		m������->IASetIndexBuffer(m��������.m����.Get(), DXGI_FORMAT_R16_UINT, 0);
		//���������EXECUTION WARNING #355: DEVICE_DRAW_VERTEX_BUFFER_STRIDE_TOO_SMALL������ʼ��ʱ���õĶ��㻺�嵥λ��С
		m������->DrawIndexed(m��������.m�޸� / m��������.m��λ��С, 0, 0);
		m���㻺��.m�޸� = 0;
		m��������.m�޸� = 0;
	}
	return vˢ��;
}
void C�Զ�����::f����(const void *a����, size_t a�����С, const void *a����, size_t a������С) {
	const unsigned int v����Ŀ�� = m���㻺��.m�޸� + a�����С;
	const unsigned int v����Ŀ�� = m��������.m�޸� + a������С;
	if ((v����Ŀ�� > m���㻺��.m�����С) || (v����Ŀ�� > m��������.m�����С)) {
		fˢ��();
	} else {
		const unsigned int v�������� = m���㻺��.fg����();
		if (v�������� != 0) {
			const unsigned int v�������� = a������С / sizeof(t����);
			std::vector<t����> va����(v��������);
			const t���� *vp���� = (t����*)a����;
			for (unsigned int i = 0; i != v��������; ++i) {
				va����[i] = vp����[i] + (t����)v��������;
			}
			m���㻺��.f����(a����, a�����С);
			m��������.f����(va����.data(), a������С);
			return;
		}
	}
	m���㻺��.f����(a����, a�����С);
	m��������.f����(a����, a������С);
}
bool C�Զ�����::fi�޸�() const {
	return m���㻺��.m�޸� != 0 || m��������.m�޸� != 0;
}
//����
C�Զ�����::C����::C����(ID3D11DeviceContext &a������, C���幤�� &a���幤��, E���� a��־) :
	m������(&a������), m���幤��(&a���幤��), m��־(a��־) {
}
void C�Զ�����::C����::f��ʼ��(size_t a��λ��С, size_t a����) {
	m��λ��С = a��λ��С;
	m�����С = m��λ��С * a����;
	m���幤��->f��������(m����, nullptr, m�����С, m��־, e��̬);
	m�޸� = 0;
}
bool C�Զ�����::C����::fӳ��() {
	assert(m���� != nullptr);
	if (mӳ�� != nullptr) {
		return false;
	}
	D3D11_MAPPED_SUBRESOURCE vӳ����Դ;
	m������->Map(m����.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &vӳ����Դ);
	mӳ�� = (std::byte*)vӳ����Դ.pData;
	return true;
}
bool C�Զ�����::C����::fȡ��ӳ��() {
	if (mӳ�� == nullptr) {
		return false;
	}
	m������->Unmap(m����.Get(), 0);
	mӳ�� = nullptr;
	return true;
}
bool C�Զ�����::C����::f����(const void *pָ��, size_t a��С) {
	if (mӳ�� == nullptr) {
		fӳ��();
	}
	const unsigned int vĿ�� = m�޸� + a��С;
	const bool v���� = vĿ�� <= m�����С;
	assert(v����);
	if (v����) {
		memcpy(mӳ�� + m�޸�, pָ��, a��С);
		m�޸� = vĿ��;
	}
	return v����;
}
UINT C�Զ�����::C����::fg����() {
	return m�޸� / m��λ��С;
}
//==============================================================================
// ��Ⱦ״̬
//==============================================================================
C��Ⱦ״̬::~C��Ⱦ״̬() {
}
C��Ⱦ״̬::C��Ⱦ״̬(ID3D11Device *a�豸) {
	HRESULT hr;
	//��դ��	================================================================
	//�޹�դ��
	m��դ������.mĬ�� = cĬ�Ϲ�դ��;
	m��դ��.mĬ�� = nullptr;
	//�߿���Ⱦ
	m��դ������.m�߿���Ⱦ = cĬ�Ϲ�դ��;
	m��դ������.m�߿���Ⱦ.CullMode = D3D11_CULL_BACK;
	m��դ������.m�߿���Ⱦ.FillMode = D3D11_FILL_WIREFRAME;
	hr = a�豸->CreateRasterizerState(&m��դ������.m�߿���Ⱦ, &m��դ��.m�߿���Ⱦ);
	if(FAILED(hr)) {
		return;
	}
	//ȡ������������
	m��դ������.m��ʾ������ = cĬ�Ϲ�դ��;
	m��դ������.m��ʾ������.CullMode = D3D11_CULL_NONE;
	m��դ������.m��ʾ������.FillMode = D3D11_FILL_SOLID;
	hr = a�豸->CreateRasterizerState(&m��դ������.m��ʾ������, &m��դ��.m��ʾ������);
	if(FAILED(hr)) {
		return;
	}
	//������ʱ��Ϊ����
	m��դ������.m������Ⱦ = cĬ�Ϲ�դ��;
	m��դ������.m������Ⱦ.FrontCounterClockwise = true;
	hr = a�豸->CreateRasterizerState(&m��դ������.m������Ⱦ, &m��դ��.m������Ⱦ);
	if(FAILED(hr)) {
		return;
	}

	//���	====================================================================
	//�޻��
	m��ϲ���.mĬ�� = cĬ�ϻ��;
	m���.mĬ�� = nullptr;
	//����͸��
	m��ϲ���.m����͸�� = cĬ�ϻ��;
	m��ϲ���.m����͸��.RenderTarget[0].BlendEnable = true;
	m��ϲ���.m����͸��.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
	m��ϲ���.m����͸��.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
	m��ϲ���.m����͸��.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
	m��ϲ���.m����͸��.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_SRC_ALPHA;
	m��ϲ���.m����͸��.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_DEST_ALPHA;
	m��ϲ���.m����͸��.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_MAX;
	m��ϲ���.m����͸��.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
	hr = a�豸->CreateBlendState(&m��ϲ���.m����͸��, &m���.m����͸��);
	if(FAILED(hr)) {
		return;
	}
	//��ɫ����
	m��ϲ���.m��ɫ���� = m��ϲ���.m����͸��;
	m��ϲ���.m��ɫ����.RenderTarget[0].DestBlend = D3D11_BLEND_DEST_ALPHA;
	m��ϲ���.m��ɫ����.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_SRC_ALPHA;
	m��ϲ���.m��ɫ����.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_DEST_ALPHA;
	hr = a�豸->CreateBlendState(&m��ϲ���.m��ɫ����, &m���.m��ɫ����);
	if(FAILED(hr)) {
		return;
	}
	//��ֹд��ɫ
	m��ϲ���.m��ֹд��ɫ = cĬ�ϻ��;
	m��ϲ���.m��ֹд��ɫ.RenderTarget[0].BlendEnable = false;
	m��ϲ���.m��ֹд��ɫ.RenderTarget[0].RenderTargetWriteMask = 0;
	hr = a�豸->CreateBlendState(&m��ϲ���.m��ֹд��ɫ, &m���.m��ֹд��ɫ);
	if(FAILED(hr)) {
		return;
	}

	//���ģ��	================================================================
	//�����ģ��
	m���ģ�����.mĬ�� = cĬ�����ģ��;
	m���ģ��.mĬ�� = nullptr;
	//�������
	m���ģ�����.m�������l = cĬ�����ģ��;
	m���ģ�����.m�������l.DepthEnable = true;
	m���ģ�����.m�������l.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
	m���ģ�����.m�������l.DepthFunc = D3D11_COMPARISON_LESS_EQUAL;
	m���ģ�����.m�������l.StencilEnable = false;
	hr = a�豸->CreateDepthStencilState(&m���ģ�����.m�������l, &m���ģ��.m�������l);
	if(FAILED(hr)) {
		return;
	}
	m���ģ�����.m�������r = m���ģ�����.m�������l;
	m���ģ�����.m�������r.DepthFunc = D3D11_COMPARISON_GREATER_EQUAL;
	hr = a�豸->CreateDepthStencilState(&m���ģ�����.m�������r, &m���ģ��.m�������r);
	if (FAILED(hr)) {
		return;
	}
	m���ģ�����.m���Ǹ��� = m���ģ�����.m�������l;
	m���ģ�����.m���Ǹ���.DepthFunc = D3D11_COMPARISON_ALWAYS;
	hr = a�豸->CreateDepthStencilState(&m���ģ�����.m���Ǹ���, &m���ģ��.m���Ǹ���);
	if (FAILED(hr)) {
		return;
	}
	//ģ����
	m���ģ�����.mģ���� = cĬ�����ģ��;
	m���ģ�����.mģ����.DepthEnable = false;
	m���ģ�����.mģ����.StencilEnable = true;
	m���ģ�����.mģ����.FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
	m���ģ�����.mģ����.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_KEEP;
	m���ģ�����.mģ����.FrontFace.StencilPassOp = D3D11_STENCIL_OP_REPLACE;
	m���ģ�����.mģ����.FrontFace.StencilFunc = D3D11_COMPARISON_ALWAYS;
	m���ģ�����.mģ����.BackFace = m���ģ�����.mģ����.FrontFace;
	hr = a�豸->CreateDepthStencilState(&m���ģ�����.mģ����, &m���ģ��.mģ����);
	if (FAILED(hr)) {
		return;
	}
	//ģ��Ƚ�
	m���ģ�����.mģ��Ƚ� = cĬ�����ģ��;
	m���ģ�����.mģ��Ƚ�.StencilEnable = true;
	m���ģ�����.mģ��Ƚ�.FrontFace.StencilFunc = D3D11_COMPARISON_EQUAL;
	m���ģ�����.mģ��Ƚ�.BackFace.StencilFunc = D3D11_COMPARISON_EQUAL;

	//������	================================================================
	//����
	m����������.m����.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	m����������.m����.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	m����������.m����.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	m����������.m����.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	m����������.m����.ComparisonFunc = D3D11_COMPARISON_NEVER;
	m����������.m����.BorderColor[0] = 0;
	m����������.m����.BorderColor[1] = 0;
	m����������.m����.BorderColor[2] = 0;
	m����������.m����.BorderColor[3] = 0;
	m����������.m����.MinLOD = 0;
	m����������.m����.MaxLOD = D3D11_FLOAT32_MAX;
	m����������.m����.MipLODBias = 0;
	m����������.m����.MaxAnisotropy = 16;
	hr = a�豸->CreateSamplerState(&m����������.m����, &m������.m����);
	if(FAILED(hr)) {
		return;
	}
	//ͼ��
	m����������.mͼ�� = m����������.m����;
	m����������.mͼ��.AddressU = D3D11_TEXTURE_ADDRESS_CLAMP;
	m����������.mͼ��.AddressV = D3D11_TEXTURE_ADDRESS_CLAMP;
	m����������.mͼ��.AddressW = D3D11_TEXTURE_ADDRESS_CLAMP;
	hr = a�豸->CreateSamplerState(&m����������.mͼ��, &m������.mͼ��);
	if(FAILED(hr)) {
		return;
	}
	//�������Թ���
	m����������.m�������Թ��� = m����������.m����;
	m����������.m�������Թ���.Filter = D3D11_FILTER_ANISOTROPIC;
	hr = a�豸->CreateSamplerState(&m����������.m�������Թ���, &m������.m�������Թ���);
	if (FAILED(hr)) {
		return;
	}
}
//==============================================================================
// �����ʽ
//==============================================================================
void C�����ʽ::f���() {
	m����.clear();
	m�����ۼ�.clear();
	m�ֽ��ۼ� = 0;
}
void C�����ʽ::f���(E���� a����, int a��С) {
	static const char *const ca����[] = {
		"POSITION",
		"NORMAL",
		"BINORMAL",
		"COLOR",
		"TEXCOORD",
		"PSIZE",
		"TANGENT"
	};
	f���(ca����[a����], a��С);
}
void C�����ʽ::f���(const char *a����, int a��С) {
	static const DXGI_FORMAT v��ʽ[] = {
		DXGI_FORMAT_R32_FLOAT,
		DXGI_FORMAT_R32G32_FLOAT,
		DXGI_FORMAT_R32G32B32_FLOAT,
		DXGI_FORMAT_R32G32B32A32_FLOAT
	};
	D3D11_INPUT_ELEMENT_DESC v;
	v.AlignedByteOffset = m�ֽ��ۼ�;
	v.Format = v��ʽ[a��С-1];
	m�ֽ��ۼ� += a��С * 4;
	v.SemanticName = a����;
	auto &v�������� = m�����ۼ�[a����];
	v.SemanticIndex = v��������;
	v�������� += 1;
	v.InputSlot = 0;
	v.InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
	v.InstanceDataStepRate = 0;
	m����.push_back(v);
}
//==============================================================================
// ���幤��
//==============================================================================
void C���幤��::f��ʼ��(ID3D11Device *a�豸) {
	m�豸 = a�豸;
}
HRESULT C���幤��::f��������(tp���� &a���, const void *a����, UINT a��С, E���� a��־, E��Դ�÷� a�÷�) {
	D3D11_BUFFER_DESC v���� = {};
	v����.Usage = (D3D11_USAGE)a�÷�;
	switch (a�÷�) {
	case e�ݴ�:
		v����.CPUAccessFlags = D3D11_CPU_ACCESS_READ;
	case e��̬:
		v����.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		break;
	}
	//assert(a��С % 16 == 0);
	v����.ByteWidth = (a��С % 16 != 0) ? ((a��С / 16 + 1) * 16) : a��С;	//������16�ı���
	v����.BindFlags = a��־;
	HRESULT hr;
	if (a����) {
		D3D11_SUBRESOURCE_DATA v���� = {};
		v����.pSysMem = a����;
		hr = m�豸->CreateBuffer(&v����, &v����, &a���);
	} else {
		hr = m�豸->CreateBuffer(&v����, nullptr, &a���);
	}
	return hr;
}
//==============================================================================
// ��ɫ������
//==============================================================================
void C��ɫ������::f��ʼ��(ID3D11Device *a�豸) {
	m�豸 = a�豸;
}
//������ɫ��
HRESULT C��ɫ������::f���벢����������ɫ��(tp������ɫ�� &a, const wchar_t *a�ļ�, const char *a���, tp���벼�� &a���벼��, const C�����ʽ &a�����ʽ) {
	ComPtr<ID3DBlob> vs;
	HRESULT hr = f���붥����ɫ��(vs, a�ļ�, a���);
	if (FAILED(hr)) {
		return hr;
	}
	// ����������ɫ��
	tp������ɫ�� v����ɫ��;
	const S��ɫ���ֽڴ��� v���� = S��ɫ���ֽڴ���::fc�����ƴ����(vs.Get());
	hr = f����������ɫ��(v����ɫ��, v����);
	if (FAILED(hr)) {
		return hr;
	}
	// �������벼��
	hr = f�������벼��(a���벼��, v����, a�����ʽ);
	if (FAILED(hr)) {
		return hr;
	}
	a = std::move(v����ɫ��);
	return S_OK;
}
HRESULT C��ɫ������::f���벢����������ɫ��(tp������ɫ�� &a, const wchar_t *a�ļ�, const char *a���) {
	HRESULT hr;
	ComPtr<ID3DBlob> ps;
	hr = f����������ɫ��(ps, a�ļ�, a���);
	if (FAILED(hr)) {
		return hr;
	}
	hr = f����������ɫ��(a, S��ɫ���ֽڴ���::fc�����ƴ����(ps.Get()));
	if (FAILED(hr)) {
		return hr;
	}
	return hr;
}
HRESULT C��ɫ������::f���벢����������ɫ��(tp������ɫ�� &a, const wchar_t *a�ļ�, const char *a���) {
	HRESULT hr;
	ComPtr<ID3DBlob> gs;
	hr = f���뼸����ɫ��(gs, a�ļ�, a���);
	if (FAILED(hr)) {
		return hr;
	}
	// ����������ɫ��
	hr = f����������ɫ��(a, S��ɫ���ֽڴ���::fc�����ƴ����(gs.Get()));
	if (FAILED(hr)) {
		return hr;
	}
	return hr;
}
HRESULT C��ɫ������::f���벢���������ɫ��(tp�����ɫ�� &a, const wchar_t *a�ļ�, const char *a���) {
	HRESULT hr;
	ComPtr<ID3DBlob> hs;
	hr = f���������ɫ��(hs, a�ļ�, a���);
	if (FAILED(hr)) {
		return hr;
	}
	// ���������ɫ��
	hr = f���������ɫ��(a, S��ɫ���ֽڴ���::fc�����ƴ����(hs.Get()));
	if (FAILED(hr)) {
		return hr;
	}
	return hr;
}
HRESULT C��ɫ������::f���벢��������ɫ��(tp����ɫ�� &a, const wchar_t *a�ļ�, const char *a���) {
	HRESULT hr;
	ComPtr<ID3DBlob> ds;
	hr = f��������ɫ��(ds, a�ļ�, a���);
	if (FAILED(hr)) {
		return hr;
	}
	// ��������ɫ��
	hr = f��������ɫ��(a, S��ɫ���ֽڴ���::fc�����ƴ����(ds.Get()));
	if (FAILED(hr)) {
		return hr;
	}
	return hr;
}
//��ȡ��ɫ��
HRESULT C��ɫ������::f��ȡ������������ɫ��(tp������ɫ�� &a, const wchar_t *a�ļ���, tp���벼�� &a���벼��, const C�����ʽ &a�����ʽ) {
	HRESULT hr;
	std::unique_ptr<std::byte[]> v����;
	DWORD v��С;
	hr = f��ȡ��ɫ��(v����, v��С, a�ļ���);
	if (FAILED(hr)) {
		return hr;
	}
	tp������ɫ�� v����ɫ��;
	const S��ɫ���ֽڴ��� v���� = {v����.get(), v��С};
	hr = f����������ɫ��(v����ɫ��, v����);
	if (FAILED(hr)) {
		return hr;
	}
	hr = f�������벼��(a���벼��, v����, a�����ʽ);
	if(FAILED(hr)) {
		return hr;
	}
	a = v����ɫ��;
	return S_OK;
}
HRESULT C��ɫ������::f��ȡ������������ɫ��(tp������ɫ�� &a, const wchar_t *a�ļ���) {
	HRESULT hr;
	std::unique_ptr<std::byte[]> v����;
	DWORD v��С;
	hr = f��ȡ��ɫ��(v����, v��С, a�ļ���);
	if (FAILED(hr)) {
		return hr;
	}
	hr = f����������ɫ��(a, {v����.get(), v��С});
	if (FAILED(hr)) {
		return hr;
	}
	return S_OK;
}
HRESULT C��ɫ������::f��ȡ������������ɫ��(tp������ɫ�� &a, const wchar_t *a�ļ���) {
	HRESULT hr;
	std::unique_ptr<std::byte[]> v����;
	DWORD v��С;
	hr = f��ȡ��ɫ��(v����, v��С, a�ļ���);
	if (FAILED(hr)) {
		return hr;
	}
	hr = f����������ɫ��(a, {v����.get(), v��С});
	if (FAILED(hr)) {
		return hr;
	}
	return hr;
}
HRESULT C��ɫ������::f��ȡ�����������ɫ��(tp�����ɫ�� &a, const wchar_t *a�ļ���) {
	HRESULT hr;
	std::unique_ptr<std::byte[]> v����;
	DWORD v��С;
	hr = f��ȡ��ɫ��(v����, v��С, a�ļ���);
	if (FAILED(hr)) {
		return hr;
	}
	hr = f���������ɫ��(a, {v����.get(), v��С});
	if (FAILED(hr)) {
		return hr;
	}
	return hr;
}
HRESULT C��ɫ������::f��ȡ����������ɫ��(tp����ɫ�� &a, const wchar_t *a�ļ���) {
	HRESULT hr;
	std::unique_ptr<std::byte[]> v����;
	DWORD v��С;
	hr = f��ȡ��ɫ��(v����, v��С, a�ļ���);
	if (FAILED(hr)) {
		return hr;
	}
	hr = f��������ɫ��(a, {v����.get(), v��С});
	if (FAILED(hr)) {
		return hr;
	}
	return hr;
}
HRESULT C��ɫ������::f����������ɫ��(tp������ɫ�� &a, const S��ɫ���ֽڴ��� &a����) {
	return m�豸->CreateVertexShader(a����.m����, a����.m��С, nullptr, &a);
}
HRESULT C��ɫ������::f����������ɫ��(tp������ɫ�� &a, const S��ɫ���ֽڴ��� &a����) {
	return m�豸->CreatePixelShader(a����.m����, a����.m��С, nullptr, &a);
}
HRESULT C��ɫ������::f����������ɫ��(tp������ɫ�� &a, const S��ɫ���ֽڴ��� &a����) {
	return m�豸->CreateGeometryShader(a����.m����, a����.m��С, nullptr, &a);
}
HRESULT C��ɫ������::f���������ɫ��(tp�����ɫ�� &a, const S��ɫ���ֽڴ��� &a����) {
	return m�豸->CreateHullShader(a����.m����, a����.m��С, nullptr, &a);
}
HRESULT C��ɫ������::f��������ɫ��(tp����ɫ�� &a, const S��ɫ���ֽڴ��� &a����) {
	return m�豸->CreateDomainShader(a����.m����, a����.m��С, nullptr, &a);
}
HRESULT C��ɫ������::f�������벼��(tp���벼�� &a, const S��ɫ���ֽڴ��� &a����, const C�����ʽ &a�����ʽ) {
	return m�豸->CreateInputLayout(a�����ʽ.m����.data(), a�����ʽ.m����.size(), a����.m����, a����.m��С, &a);
}
HRESULT C��ɫ������::f���붥����ɫ��(ComPtr<ID3DBlob> &a, const wchar_t *a�ļ���, const char *a������) {
	return f������ɫ��(a, a�ļ���, a������, "vs_5_0");
}
HRESULT C��ɫ������::f����������ɫ��(ComPtr<ID3DBlob> &a, const wchar_t *a�ļ���, const char *a������) {
	return f������ɫ��(a, a�ļ���, a������, "ps_5_0");
}
HRESULT C��ɫ������::f���뼸����ɫ��(ComPtr<ID3DBlob> &a, const wchar_t *a�ļ���, const char *a������) {
	return f������ɫ��(a, a�ļ���, a������, "gs_5_0");
}
HRESULT C��ɫ������::f���������ɫ��(ComPtr<ID3DBlob> &a, const wchar_t *a�ļ���, const char *a������) {
	return f������ɫ��(a, a�ļ���, a������, "hs_5_0");
}
HRESULT C��ɫ������::f��������ɫ��(ComPtr<ID3DBlob> &a, const wchar_t *a�ļ���, const char *a������) {
	return f������ɫ��(a, a�ļ���, a������, "ds_5_0");
}
HRESULT C��ɫ������::f������ɫ��(ComPtr<ID3DBlob> &a, const wchar_t *a�ļ���, const char *a���, const char *a��ɫģ��) {
	HRESULT hr = S_OK;
	DWORD v��ɫ��־ = D3DCOMPILE_ENABLE_STRICTNESS;
#if defined( DEBUG ) || defined( _DEBUG )
	v��ɫ��־ |= D3DCOMPILE_DEBUG;
#endif
	ComPtr<ID3DBlob> v����;
	hr = D3DCompileFromFile(a�ļ���, nullptr, nullptr, a���, a��ɫģ��, v��ɫ��־, 0, &a, &v����);
	if(FAILED(hr)) {
		if (v���� != nullptr) {
			OutputDebugStringA((char*)v����->GetBufferPointer());
		}
		return hr;
	}
	return S_OK;
}
HRESULT C��ɫ������::f��ȡ��ɫ��(std::unique_ptr<std::byte[]> &a����, DWORD &a��С, const wchar_t *a�ļ���) {
	HANDLE v�ļ� = CreateFileW(a�ļ���, GENERIC_READ, FILE_SHARE_READ, nullptr, OPEN_ALWAYS, 0, nullptr);
	if (v�ļ� == INVALID_HANDLE_VALUE) {
		return ERROR_FILE_NOT_FOUND;
	}
	a��С = GetFileSize(v�ļ�, nullptr);
	a���� = std::make_unique<std::byte[]>(a��С);
	DWORD v����С;
	ReadFile(v�ļ�, a����.get(), a��С, &v����С, nullptr);
	CloseHandle(v�ļ�);
	return S_OK;
}
HRESULT C��ɫ������::f��ȡ��ɫ��(ComPtr<ID3DBlob> &a, const wchar_t *a�ļ���) {
	ComPtr<ID3DBlob> v;
	HANDLE v�ļ� = CreateFileW(a�ļ���, GENERIC_READ, FILE_SHARE_READ, nullptr, OPEN_ALWAYS, 0, nullptr);
	if (v�ļ� == INVALID_HANDLE_VALUE) {
		return ERROR_FILE_NOT_FOUND;
	}
	const DWORD v��С = GetFileSize(v�ļ�, nullptr);
	D3DCreateBlob(v��С, &v);
	ReadFile(v�ļ�, v->GetBufferPointer(), v��С, nullptr, nullptr);
	CloseHandle(v�ļ�);
	a = std::move(v);
	return S_OK;
}
//==============================================================================
// ���������
//==============================================================================
C������::~C������() {
	m����.reset();
}
HRESULT C������::f��ʼ��(ID3D11Device *a�豸) {
	if (m����) {
		return S_OK;
	}
	m�豸 = a�豸;
	m���� = std::make_unique<����::Cͼ�񹤳�>();
	return m����->f��ʼ��();
}
//��������
HRESULT C������::f���ļ���������(tp���� &a���, const wchar_t *a�ļ�) {
	std::unique_ptr<����::Cֻ������> v���� = m����->fһ����ȡ(a�ļ�);
	if (v���� == nullptr) {
		return E_FAIL;
	}
	tp����2 v����2;
	HRESULT hr = f��������󴴽�����2(v����2, *v����);
	if (FAILED(hr)) {
		return hr;
	}
	hr = f����������Դ��ͼ(a���, v����2.Get(), v����->fg��ʽ());
	return hr;
}
HRESULT C������::f���ڴ洴������2(tp����2 &a���, const void *a����, DXGI_FORMAT a��ʽ, UINT a��, UINT a��, UINT a�о�, UINT a��С) {
	m��������.Width = a��;
	m��������.Height = a��;
	m��������.MipLevels = 1;
	m��������.ArraySize = 1;
	m��������.Format = a��ʽ;
	m��������.SampleDesc.Count = 1;
	m��������.SampleDesc.Quality = 0;
	m��������.Usage = D3D11_USAGE_DEFAULT;
	m��������.BindFlags = D3D11_BIND_SHADER_RESOURCE;
	m��������.CPUAccessFlags = 0;
	m��������.MiscFlags = 0;
	D3D11_SUBRESOURCE_DATA v��Դ����;
	v��Դ����.pSysMem = a����;
	v��Դ����.SysMemPitch = a�о�;
	v��Դ����.SysMemSlicePitch = a��С;
	HRESULT hr = m�豸->CreateTexture2D(&m��������, &v��Դ����, &a���);
	return hr;
}
HRESULT C������::f��������󴴽�����2(tp����2 &a���, const ����::I���� &a����) {
	return f���ڴ洴������2(a���, a����.fg����(), a����.fg��ʽ(), a����.fg��(), a����.fg��(), a����.fg�о�(), a����.fgͼ���С());
}
HRESULT C������::f����������Դ��ͼ(tp���� &a���, tp����2 a����, DXGI_FORMAT a��ʽ) {
	D3D11_SHADER_RESOURCE_VIEW_DESC v���� = {};
	v����.Format = a��ʽ;
	v����.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
	v����.Texture2D.MipLevels = 1;
	HRESULT hr = m�豸->CreateShaderResourceView(a����.Get(), &v����, &a���);
	return hr;
}
const D3D11_TEXTURE2D_DESC &C������::fg�����������() const {
	return m��������;
}
//==============================================================================
// �ṹ
//==============================================================================
S��ɫ���ֽڴ��� S��ɫ���ֽڴ���::fc�����ƴ����(ID3DBlob *a) {
	return {a->GetBufferPointer(), a->GetBufferSize()};
}
S��ɫ���ֽڴ���::operator bool() const {
	return m���� != nullptr;
}
void Sͼ�ι��߲���::fs���벼��(const C�����ʽ &a) {
	m�����ʽ = &a;
}
void Sͼ�ι��߲���::fs������ɫ��(ID3DBlob *a) {
	m������ɫ�� = S��ɫ���ֽڴ���::fc�����ƴ����(a);
}
void Sͼ�ι��߲���::fs������ɫ��(ID3DBlob *a) {
	m������ɫ�� = S��ɫ���ֽڴ���::fc�����ƴ����(a);
}
void Sͼ�ι��߲���::fs������ɫ��(ID3DBlob *a) {
	m������ɫ�� = S��ɫ���ֽڴ���::fc�����ƴ����(a);
}
void Sͼ�ι��߲���::fs�����ɫ��(ID3DBlob *a) {
	m�����ɫ�� = S��ɫ���ֽڴ���::fc�����ƴ����(a);
}
void Sͼ�ι��߲���::fs����ɫ��(ID3DBlob *a) {
	m����ɫ�� = S��ɫ���ֽڴ���::fc�����ƴ����(a);
}
void Sͼ�ι��߲���::fs��դ��(const D3D11_RASTERIZER_DESC &a) {
	m��դ�� = a;
}
void Sͼ�ι��߲���::fs���(const D3D11_BLEND_DESC &a) {
	m��� = a;
}
void Sͼ�ι��߲���::fs���ģ��(const D3D11_DEPTH_STENCIL_DESC &a) {
	m���ģ�� = a;
}
void Sͼ�ι��߲���::fs��դ��(ID3D11RasterizerState *a) {
	m��դ�� = a;
}
void Sͼ�ι��߲���::fs���(ID3D11BlendState *a) {
	m��� = a;
}
void Sͼ�ι��߲���::fs���ģ��(ID3D11DepthStencilState *a) {
	m���ģ�� = a;
}
S���ģ�����::S���ģ�����():
	D3D11_DEPTH_STENCIL_DESC(cĬ�����ģ��) {
}
void S���ģ�����::fs��Ȳ���(const D3D11_DEPTH_STENCIL_DESC &a) {
	DepthEnable = a.DepthEnable;
	DepthWriteMask = a.DepthWriteMask;
	DepthFunc = a.DepthFunc;
}
void S���ģ�����::fsģ�岿��(const D3D11_DEPTH_STENCIL_DESC &a) {
	StencilEnable = a.StencilEnable;
	StencilReadMask = a.StencilReadMask;
	StencilWriteMask = a.StencilWriteMask;
	FrontFace = a.FrontFace;
	BackFace = a.BackFace;
}

}	//namespace cflw::ͼ��::d3d11