#include <D3Dcompiler.h>
#include "cflwͼ��_d3d12.h"
#include "d3dx12.h"
#include "cflw�Ӵ�.h"
#include "cflw����.h"
namespace cflw::ͼ��::d3d12 {
//=============================================================================
// ��ά
//=============================================================================
C��ά::~C��ά() {
	f����();
}
void C��ά::f����() {
	if (m�豸 == nullptr) {
		return;
	}
	m��Ⱦ����->f�ȴ����֡();

	m���幤��.reset();
	m�����豸.reset();
	m��Ⱦ״̬.reset();
	m��ȾĿ�����.reset();
	m��Ⱦ����.reset();

	m��ǩ��.Reset();
	m���������.Reset();
	m������.Reset();
	m�������.Reset();
	m�豸.Reset();
}
void C��ά::f��ʼ������(HWND a) {
	m���� = a;
	�Ӵ�::S�ͻ����ߴ� v�ߴ� = �Ӵ�::S�ͻ����ߴ�::fc����(m����);
	m���ڴ�С[0] = v�ߴ�.fg��();
	m���ڴ�С[1] = v�ߴ�.fg��();
}
HRESULT C��ά::f��ʼ���豸() {
	C�����豸 &v�����豸 = fg�����豸();
	if constexpr (c����) {
		m��־[e����] = v�����豸.f�������Բ�();
	}
	HRESULT hr = S_OK;
	ComPtr<IDXGIAdapter3> v�Կ�;
	hr = v�����豸.fȡ�Կ�(&v�Կ�);
	if (hr == DXGI_ERROR_UNSUPPORTED) {//0x887A0004 Ӳ����������֧��
		hr = v�����豸.fȡ���������(&v�Կ�);
		m��־[e����豸] = true;
	}
	if (FAILED(hr)) {
		return hr;
	}
	hr = v�����豸.f�����豸(v�Կ�.Get(), &m�豸);
	if (FAILED(hr)) {
		return hr;
	}
	return S_OK;
}
HRESULT C��ά::f��ʼ���������() {
	assert(m�豸);
	D3D12_COMMAND_QUEUE_DESC qd = {};
	qd.Flags = D3D12_COMMAND_QUEUE_FLAG_NONE;
	qd.Type = D3D12_COMMAND_LIST_TYPE_DIRECT;
	HRESULT hr = m�豸->CreateCommandQueue(&qd, IID_PPV_ARGS(&m�������));
	if (FAILED(hr)) {
		return hr;
	}
	hr = m�豸->CreateCommandAllocator(D3D12_COMMAND_LIST_TYPE_DIRECT, IID_PPV_ARGS(&m���������));
	if (FAILED(hr)) {
		return hr;
	}
	return S_OK;
}
HRESULT C��ά::f��ʼ��������() {
	assert(m�豸);
	//����������
	DXGI_SWAP_CHAIN_DESC1 sd = {};
	sd.BufferCount = c֡��;
	sd.Width = 0;
	sd.Height = 0;
	sd.Format = c��������ʽ;
	sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	sd.SwapEffect = DXGI_SWAP_EFFECT_FLIP_SEQUENTIAL;
	sd.SampleDesc.Count = 1;
	sd.SampleDesc.Quality = 0;
	sd.Stereo = false;
	sd.Flags = 0;
	sd.AlphaMode = DXGI_ALPHA_MODE_UNSPECIFIED;
	sd.Scaling = DXGI_SCALING_NONE;
	//����������
	C�����豸 &v�����豸 = fg�����豸();
	ComPtr<IDXGIFactory4> v���� = v�����豸.fg����();
	ComPtr<IDXGISwapChain1> v������;
	HRESULT hr = v����->CreateSwapChainForHwnd(m�������.Get(), m����, &sd, nullptr, nullptr, &v������);
	if (FAILED(hr)) {
		return hr;
	}
	v������.As(&m������);
	return S_OK;
}
HRESULT C��ά::f��ʼ����ȾĿ����ͼ() {
	assert(m�豸);
	m��ȾĿ����� = std::make_unique<C��ȾĿ�����>();
	//��
	D3D12_DESCRIPTOR_HEAP_DESC v���� = {};
	v����.NumDescriptors = c֡��;
	v����.Type = D3D12_DESCRIPTOR_HEAP_TYPE_RTV;
	v����.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_NONE;
	m�豸->CreateDescriptorHeap(&v����, IID_PPV_ARGS(&m��ȾĿ�����->m��ȾĿ���));
	m��ȾĿ�����->m��ȾĿ����ͼ��С = m�豸->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV);
	//ѭ��
	D3D12_CPU_DESCRIPTOR_HANDLE v��ȾĿ����ͼ��� = m��ȾĿ�����->m��ȾĿ���->GetCPUDescriptorHandleForHeapStart();
	for (UINT i = 0; i < c֡��; ++i) {
		auto &v��ȾĿ�� = m��ȾĿ�����->m��ȾĿ��[i];
		//��Դ
		m������->GetBuffer(i, IID_PPV_ARGS(&v��ȾĿ��));
		//��ͼ
		m�豸->CreateRenderTargetView(v��ȾĿ��.Get(), nullptr, v��ȾĿ����ͼ���);
		v��ȾĿ����ͼ���.ptr += m��ȾĿ�����->m��ȾĿ����ͼ��С;
		//����
		const std::wstring v���� = std::wstring(L"��ȾĿ��") + std::to_wstring(i);
		v��ȾĿ��->SetName(v����.c_str());
	}
	return S_OK;
}
HRESULT C��ά::f��ʼ�����ģ����ͼ() {
	m���ģ����� = std::make_unique<C���ģ�����>();
	//��
	D3D12_DESCRIPTOR_HEAP_DESC v������ = {};
	v������.NumDescriptors = 1;
	v������.Type = D3D12_DESCRIPTOR_HEAP_TYPE_DSV;
	v������.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_NONE;
	HRESULT hr = m�豸->CreateDescriptorHeap(&v������, IID_PPV_ARGS(&m���ģ�����->m���ģ���));
	if (FAILED(hr)) {
		return hr;
	}
	//��Դ׼��
	const D3D12_RESOURCE_DESC v��Դ���� = S��Դ����::fc����2(m���ڴ�С[0], m���ڴ�С[1], c���ģ���ʽ, D3D12_RESOURCE_FLAG_ALLOW_DEPTH_STENCIL);
	const D3D12_HEAP_PROPERTIES v������ = S������::fc����(D3D12_HEAP_TYPE_DEFAULT);
	const D3D12_CLEAR_VALUE v���ֵ = S���ֵ::fc���ģ��(c���ģ���ʽ, c�������r, 0);
	//��ͼ׼��
	D3D12_DEPTH_STENCIL_VIEW_DESC v��ͼ���� = {};
	v��ͼ����.Format = c���ģ���ʽ;
	v��ͼ����.ViewDimension = D3D12_DSV_DIMENSION_TEXTURE2D;
	v��ͼ����.Texture2D.MipSlice = 0;
	//ѭ��
	D3D12_CPU_DESCRIPTOR_HANDLE v���ģ����ͼ��� = m���ģ�����->m���ģ���->GetCPUDescriptorHandleForHeapStart();
	for (UINT i = 0; i != c֡��; ++i) {
		auto &v���ģ�� = m���ģ�����->m���ģ��[i];
		//��Դ
		hr = m�豸->CreateCommittedResource(&v������, D3D12_HEAP_FLAG_NONE, &v��Դ����, D3D12_RESOURCE_STATE_DEPTH_WRITE, &v���ֵ, IID_PPV_ARGS(&v���ģ��));
		if (FAILED(hr)) {
			return hr;
		}
		//��ͼ
		m�豸->CreateDepthStencilView(v���ģ��.Get(), &v��ͼ����, v���ģ����ͼ���);
		v���ģ����ͼ���.ptr += m���ģ�����->m���ģ����ͼ��С;
		//����
		const std::wstring v���� = std::wstring(L"���ģ��") + std::to_wstring(i);
		v���ģ��->SetName(v����.c_str());
	}
	return S_OK;
}
HRESULT C��ά::f��ʼ����ǩ��() {
	D3D12_ROOT_SIGNATURE_DESC v���� = {};
	v����.NumParameters = 0;
	v����.pParameters = nullptr;
	v����.NumStaticSamplers = 0;
	v����.pStaticSamplers = nullptr;
	v����.Flags = D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT;
	return f������ǩ��(m��ǩ��, v����);
}
bool C��ά::f��ʼ��(const HWND &a) {
	try {
		f��ʼ������(a);
		�Ӵ�::fʧ�����׳�(f��ʼ���豸());
		�Ӵ�::fʧ�����׳�(f��ʼ���������());
		�Ӵ�::fʧ�����׳�(f��ʼ��������());
		�Ӵ�::fʧ�����׳�(f��ʼ����ȾĿ����ͼ());
		�Ӵ�::fʧ�����׳�(f��ʼ�����ģ����ͼ());
		�Ӵ�::fʧ�����׳�(f��ʼ����ǩ��());
		return true;
	} catch (HRESULT hr) {
		return false;
	}
}
HRESULT C��ά::f����ͼ�ι���(tpͼ�ι��� &a, const D3D12_GRAPHICS_PIPELINE_STATE_DESC &a����) {
	assert(m�豸);
	//������
	if (a����.VS.pShaderBytecode) {
		assert(a����.InputLayout.pInputElementDescs && a����.InputLayout.NumElements);
	}
	assert(a����.PrimitiveTopologyType != D3D12_PRIMITIVE_TOPOLOGY_TYPE_UNDEFINED);
	//����
	HRESULT hr = m�豸->CreateGraphicsPipelineState(&a����, IID_PPV_ARGS(&a));
	if (FAILED(hr)) {
		return hr;
	}
	return S_OK;
}
HRESULT C��ά::f���������б�(tp�����б� &a, ID3D12PipelineState *aͼ�ι���) {
	assert(m�豸);
	HRESULT hr = m�豸->CreateCommandList(0, D3D12_COMMAND_LIST_TYPE_DIRECT, m���������.Get(), aͼ�ι���, IID_PPV_ARGS(&a));
	if (FAILED(hr)) {
		return hr;
	}
	hr = a->Close();
	if (FAILED(hr)) {
		return hr;
	}
	return S_OK;
}
HRESULT C��ά::f������ǩ��(tp��ǩ�� &a, const C��ǩ������ &a����) {
	D3D12_ROOT_SIGNATURE_DESC v����;
	v����.NumStaticSamplers = a����.ma������.size();
	v����.pStaticSamplers = a����.ma������.data();
	v����.Flags = a����.m��־;
	std::vector<D3D12_ROOT_PARAMETER> va����;
	for (const auto &v0 : a����.ma����) {
		switch (v0.m����) {
		case C��ǩ������::E����������::e��������:{
			const auto &v1 = a����.ma��������[v0.mλ��];
			D3D12_ROOT_PARAMETER v����;
			v����.ParameterType = D3D12_ROOT_PARAMETER_TYPE_DESCRIPTOR_TABLE;
			v����.DescriptorTable.NumDescriptorRanges = v1.m����;
			v����.DescriptorTable.pDescriptorRanges = &a����.ma������Χ[v1.m��ʼλ��];
			v����.ShaderVisibility = v1.m�ɼ���;
			va����.push_back(v����);
			break;
		}
		case C��ǩ������::E����������::e����:
		case C��ǩ������::E����������::e������:
			va����.push_back(a����.ma����[v0.mλ��]);
			break;
		default:
			return E_INVALIDARG;
		}
	}
	v����.NumParameters = va����.size();
	v����.pParameters = va����.data();
	return f������ǩ��(a, v����);
}
HRESULT C��ά::f������ǩ��(tp��ǩ�� &a, const D3D12_ROOT_SIGNATURE_DESC &a����) {
	ComPtr<ID3DBlob> vǩ��, v����;
	HRESULT hr = D3D12SerializeRootSignature(&a����, D3D_ROOT_SIGNATURE_VERSION_1, &vǩ��, &v����);
	if (FAILED(hr)) {
		return hr;
	}
	hr = m�豸->CreateRootSignature(0, vǩ��->GetBufferPointer(), vǩ��->GetBufferSize(), IID_PPV_ARGS(&a));
	if (FAILED(hr)) {
		return hr;
	}
	return S_OK;
}
HRESULT C��ά::f�����ϴ���Դ(tp��Դ &a, const void *a����, size_t a��С) {
	HRESULT hr = m�豸->CreateCommittedResource(&S������::fc����(D3D12_HEAP_TYPE_UPLOAD), D3D12_HEAP_FLAG_NONE, &S��Դ����::fc����(a��С), D3D12_RESOURCE_STATE_GENERIC_READ, nullptr, IID_PPV_ARGS(&a));
	if (FAILED(hr)) {
		return hr;
	}
	if (a����) {
		void *vp;
		hr = a->Map(0, nullptr, &vp);
		if (FAILED(hr)) {
			return hr;
		}
		memcpy(vp, a����, a��С);
		a->Unmap(0, nullptr);
	}
	return S_OK;
}
D3D12_VIEWPORT C��ά::fg�����ӿ�() {
	D3D12_VIEWPORT v�ӿ�;
	v�ӿ�.Width = (FLOAT)m���ڴ�С[0];
	v�ӿ�.Height = (FLOAT)m���ڴ�С[1];
	v�ӿ�.MinDepth = 0.0f;
	v�ӿ�.MaxDepth = 1.0f;
	v�ӿ�.TopLeftX = 0;
	v�ӿ�.TopLeftY = 0;
	return v�ӿ�;
}
D3D12_RECT C��ά::fg���ھ���() {
	return {0, 0, m���ڴ�С[0], m���ڴ�С[1]};
}
��ѧ::S����2 C��ά::fg���ڴ�С() const {
	return {(float)m���ڴ�С[0], (float)m���ڴ�С[1]};
}
C��Ⱦ���� &C��ά::fg��Ⱦ����() {
	if (m��Ⱦ���� == nullptr) {
		m��Ⱦ���� = std::make_unique<C��Ⱦ����>();
		f���������б�(m��Ⱦ����->m�����б�);
		m��Ⱦ����->m������� = m�������;
		m��Ⱦ����->m��������� = m���������;
		m��Ⱦ����->m��ǩ�� = m��ǩ��;
		m��Ⱦ����->m������ = m������;
		m��Ⱦ����->m��ȾĿ����� = m��ȾĿ�����.get();
		m��Ⱦ����->m���ģ����� = m���ģ�����.get();
		m��ȾĿ�����->m֡���� = &m��Ⱦ����->m֡����;
		m���ģ�����->m֡���� = &m��Ⱦ����->m֡����;
		m��Ⱦ����->m�ӿ� = fg�����ӿ�();
		m��Ⱦ����->m�ü����� = fg���ھ���();
		m��Ⱦ����->f��ʼ��Χ��(m�豸.Get());
	}
	return *m��Ⱦ����;
}
C��Ⱦ״̬ &C��ά::fg��Ⱦ״̬() {
	if (m��Ⱦ״̬ == nullptr) {
		m��Ⱦ״̬ = std::make_unique<C��Ⱦ״̬>();
	}
	return *m��Ⱦ״̬;
}
C�����豸 &C��ά::fg�����豸() {
	if (m�����豸 == nullptr) {
		m�����豸 = std::make_unique<C�����豸>();
	}
	return *m�����豸;
}
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
		m������->m��ά = this;
		m������->m�豸 = m�豸;
		m������->m��Ⱦ���� = &fg��Ⱦ����();
		m������->f��ʼ��();
	}
	return *m������;
}
ID3D12RootSignature *C��ά::fgĬ�ϸ�ǩ��() {
	return m��ǩ��.Get();
}
ComPtr<ID3D12Device> C��ά::fg�豸() const {
	return m�豸;
}
//=============================================================================
// �����豸
//=============================================================================
ComPtr<IDXGIFactory4> C�����豸::fg����() {
	if (m���� == nullptr) {
		HRESULT hr = CreateDXGIFactory1(IID_PPV_ARGS(&m����));
		if (FAILED(hr)) {
			throw;
		}
	}
	return m����;
}
bool C�����豸::f�������Բ�() {
	ComPtr<ID3D12Debug> v����;
	if (SUCCEEDED(D3D12GetDebugInterface(IID_PPV_ARGS(&v����)))) {
		v����->EnableDebugLayer();
		return true;
	}
	return false;
}
HRESULT C�����豸::fȡ�Կ�(IDXGIAdapter3**a�Կ�) {
	HRESULT hr = S_OK;
	fg����();
	ComPtr<IDXGIAdapter1> v�Կ�, vĿ���Կ�;
	*a�Կ� = nullptr;
	SIZE_T v�Դ� = 0;
	for (UINT i = 0; DXGI_ERROR_NOT_FOUND != m����->EnumAdapters1(i, &v�Կ�); ++i) {
		DXGI_ADAPTER_DESC1 v����;
		v�Կ�->GetDesc1(&v����);
		if (v����.Flags & DXGI_ADAPTER_FLAG_SOFTWARE) {
			continue;
		}
		hr = D3D12CreateDevice(v�Կ�.Get(), D3D_FEATURE_LEVEL_11_0, __uuidof(ID3D12Device), nullptr);
		if (FAILED(hr)) {
			continue;
		}
		if (v����.DedicatedVideoMemory > v�Դ�) {
			vĿ���Կ� = v�Կ�;
			v�Դ� = v����.DedicatedVideoMemory;
		}
	}
	if (vĿ���Կ�) {
		ComPtr<IDXGIAdapter3> v���;
		vĿ���Կ�.As(&v���);
		*a�Կ� = v���.Detach();
		return S_OK;
	} else {
		return hr;
	}
}
HRESULT C�����豸::fȡ���������(IDXGIAdapter3 **a�Կ�) {
	return m����->EnumWarpAdapter(IID_PPV_ARGS(a�Կ�));
}
HRESULT C�����豸::f�����豸(IDXGIAdapter3 *a�Կ�, ID3D12Device **a�豸) {
	HRESULT hr = D3D12CreateDevice(a�Կ�, D3D_FEATURE_LEVEL_11_0, IID_PPV_ARGS(a�豸));
	return hr;
}
//=============================================================================
// ��Ⱦ����
//=============================================================================
C��Ⱦ����::~C��Ⱦ����() {
	f����();
}
void C��Ⱦ����::f����() {
	CloseHandle(mΧ���¼�);
}
HRESULT C��Ⱦ����::f��ʼ��Χ��(ID3D12Device *a�豸) {
	HRESULT hr = a�豸->CreateFence(0, D3D12_FENCE_FLAG_NONE, IID_PPV_ARGS(&mΧ��));
	mΧ��ֵ = 1;
	mΧ���¼� = CreateEventW(nullptr, FALSE, FALSE, nullptr);
	if (mΧ���¼� == nullptr) {
		hr = HRESULT_FROM_WIN32(GetLastError());
		if (FAILED(hr)) {
			return hr;
		}
	}
	f�ȴ����֡();
	return S_OK;
}
void C��Ⱦ����::f��ʼ() {
	m�����б�->SetGraphicsRootSignature(m��ǩ��.Get());
	m�����б�->RSSetViewports(1, &m�ӿ�);
	m�����б�->RSSetScissorRects(1, &m�ü�����);
	const D3D12_RESOURCE_BARRIER vդ�� = fc��Ⱦ��ͼդ���任(D3D12_RESOURCE_STATE_PRESENT, D3D12_RESOURCE_STATE_RENDER_TARGET);
	m�����б�->ResourceBarrier(1, &vդ��);
	m��ȾĿ�����->f������ͼ();
	m���ģ�����->f������ͼ();
	m�����б�->OMSetRenderTargets(1, &m��ȾĿ�����->fg��ǰ��ͼ(), FALSE, &m���ģ�����->fg��ǰ��ͼ());
}
void C��Ⱦ����::f����() {
	const D3D12_RESOURCE_BARRIER vդ�� = fc��Ⱦ��ͼդ���任(D3D12_RESOURCE_STATE_RENDER_TARGET, D3D12_RESOURCE_STATE_PRESENT);
	m�����б�->ResourceBarrier(1, &vդ��);
}
void C��Ⱦ����::f����() {
	m�����б�->ClearRenderTargetView(m��ȾĿ�����->fg��ǰ��ͼ(), m������ɫ.v, 0, nullptr);
	constexpr D3D12_CLEAR_FLAGS c������ģ���־ = D3D12_CLEAR_FLAG_DEPTH | D3D12_CLEAR_FLAG_STENCIL;
	m�����б�->ClearDepthStencilView(m���ģ�����->fg��ǰ��ͼ(), c������ģ���־, m�������, m����ģ��, 0, nullptr);
}
void C��Ⱦ����::f��ʾ() {
	m������->Present(1, 0);
	f�ȴ����֡();
	f����֡����();
	ma������Դ.clear();
}
void C��Ⱦ����::f��������() {
	m���������->Reset();
	m�����б�->Reset(m���������.Get(), mͼ�ι���.Get());
}
void C��Ⱦ����::fִ������() {
	m�����б�->Close();
	ID3D12CommandList* v�����б�[] = {m�����б�.Get()};
	m�������->ExecuteCommandLists(_countof(v�����б�), v�����б�);
}
void C��Ⱦ����::fִ������ȴ�() {
	fִ������();
	f�ȴ����֡();
	ma������Դ.clear();
}
void C��Ⱦ����::fִ�������ʾ() {
	fִ������();
	f��ʾ();
}
void C��Ⱦ����::f����(UINT a������, UINT a��ʼ) {
	m�����б�->DrawInstanced(a������, 1, a��ʼ, 0);
}
void C��Ⱦ����::f��������(UINT a������, UINT a��ʼ����, INT a��ʼ����) {
	m�����б�->DrawIndexedInstanced(a������, 1, a��ʼ����, a��ʼ����, 0);
}
void C��Ⱦ����::f�ȴ����֡() {
	const UINT64 vΧ��ֵ = mΧ��ֵ;
	m�������->Signal(mΧ��.Get(), vΧ��ֵ);
	mΧ��ֵ++;
	// �ȵ�ǰһ֡��ɡ�
	if (mΧ��->GetCompletedValue() < vΧ��ֵ) {
		mΧ��->SetEventOnCompletion(vΧ��ֵ, mΧ���¼�);
		WaitForSingleObject(mΧ���¼�, INFINITE);
	}
}
UINT C��Ⱦ����::f����֡����() {
	m֡���� = m������->GetCurrentBackBufferIndex();
	return m֡����;
}
UINT C��Ⱦ����::fg֡����() const {
	return m֡����;
}
void C��Ⱦ����::f������Դ(ID3D12Resource *aĿ��, ID3D12Resource *aԴ) {
	m�����б�->CopyResource(aĿ��, aԴ);
	ma������Դ.emplace_back(aԴ);
}
void C��Ⱦ����::f��������(ID3D12Resource *aĿ��, ID3D12Resource *aԴ, D3D12_SUBRESOURCE_DATA &a��Դ����) {
	UpdateSubresources(m�����б�.Get(), aĿ��, aԴ, 0, 0, 1, &a��Դ����);
	m�����б�->ResourceBarrier(1, &S��Դդ��::fc�任(aĿ��, D3D12_RESOURCE_STATE_COPY_DEST, D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE));
	ma������Դ.emplace_back(aԴ);
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
void C��Ⱦ����::fsͼ�ι���(ID3D12PipelineState *a) {
	mͼ�ι��� = a;
	m�����б�->SetPipelineState(a);
}
void C��Ⱦ����::fs��ǩ��(ID3D12RootSignature *a) {
	m��ǩ�� = a;
	m�����б�->SetGraphicsRootSignature(a);
}
void C��Ⱦ����::fsͼԪ����(EͼԪ���� a) {
	m�����б�->IASetPrimitiveTopology((D3D_PRIMITIVE_TOPOLOGY)a);
}
void C��Ⱦ����::fs���㻺��(const D3D12_VERTEX_BUFFER_VIEW &a) {
	m�����б�->IASetVertexBuffers(0, 1, &a);
}
void C��Ⱦ����::fs��������(const D3D12_INDEX_BUFFER_VIEW &a) {
	m�����б�->IASetIndexBuffer(&a);
}
void C��Ⱦ����::fs�̶�����(UINT a��, const D3D12_GPU_VIRTUAL_ADDRESS &aλ��) {
	m�����б�->SetGraphicsRootConstantBufferView(a��, aλ��);
}
void C��Ⱦ����::fs����(UINT a��, const D3D12_GPU_VIRTUAL_ADDRESS &aλ��) {
	m�����б�->SetGraphicsRootShaderResourceView(a��, aλ��);
}
void C��Ⱦ����::fs��������(UINT a��, ID3D12DescriptorHeap *a��) {
	m�����б�->SetDescriptorHeaps(1, &a��);
	m�����б�->SetGraphicsRootDescriptorTable(a��, a��->GetGPUDescriptorHandleForHeapStart());
}
//void C��Ⱦ����::fs��������(const std::initializer_list<ID3D12DescriptorHeap*> &a) {
//	m�����б�->SetDescriptorHeaps(a.size(), a.begin());
//	UINT i = 0;
//	for (const auto &v : a) {
//		m�����б�->SetGraphicsRootDescriptorTable(i++, v->GetGPUDescriptorHandleForHeapStart());
//	}
//}
D3D12_RESOURCE_BARRIER C��Ⱦ����::fc��Ⱦ��ͼդ���任(D3D12_RESOURCE_STATES aǰ, D3D12_RESOURCE_STATES a��) {
	return S��Դդ��::fc�任(m��ȾĿ�����->fg��ǰ��Դ(), aǰ, a��);
}
//=============================================================================
// ��ȾĿ��
//=============================================================================
const D3D12_CPU_DESCRIPTOR_HANDLE &C��ȾĿ�����::f������ͼ() {
	m��ǰ��ȾĿ����ͼ = m��ȾĿ���->GetCPUDescriptorHandleForHeapStart();
	m��ǰ��ȾĿ����ͼ.ptr += *m֡���� * m��ȾĿ����ͼ��С;
	return m��ǰ��ȾĿ����ͼ;
}
const D3D12_CPU_DESCRIPTOR_HANDLE &C��ȾĿ�����::fg��ǰ��ͼ() const {
	return m��ǰ��ȾĿ����ͼ;
}
ID3D12Resource *C��ȾĿ�����::fg��ǰ��Դ() const {
	return m��ȾĿ��[*m֡����].Get();
}
const D3D12_CPU_DESCRIPTOR_HANDLE &C���ģ�����::f������ͼ() {
	m��ǰ���ģ����ͼ = m���ģ���->GetCPUDescriptorHandleForHeapStart();
	m��ǰ���ģ����ͼ.ptr += *m֡���� * m���ģ����ͼ��С;
	return m��ǰ���ģ����ͼ;

}
const D3D12_CPU_DESCRIPTOR_HANDLE &C���ģ�����::fg��ǰ��ͼ() const {
	return m��ǰ���ģ����ͼ;

}
ID3D12Resource *C���ģ�����::fg��ǰ��Դ() const {
	return m���ģ��[*m֡����].Get();
}

//=============================================================================
// ��Դ
//=============================================================================
void C�̶�����::f����(void *a����, size_t a��С) {
	assert(mӳ��);
	memcpy(mӳ��, a����, a��С);
}
//==============================================================================
// ��Ⱦ״̬
//==============================================================================
C��Ⱦ״̬::C��Ⱦ״̬() {
	//Ĭ�Ϲ�դ��
	m��դ��.mĬ��.FillMode = D3D12_FILL_MODE_SOLID;
	m��դ��.mĬ��.CullMode = D3D12_CULL_MODE_BACK;
	m��դ��.mĬ��.FrontCounterClockwise = FALSE;
	m��դ��.mĬ��.DepthBias = D3D12_DEFAULT_DEPTH_BIAS;
	m��դ��.mĬ��.DepthBiasClamp = D3D12_DEFAULT_DEPTH_BIAS_CLAMP;
	m��դ��.mĬ��.SlopeScaledDepthBias = D3D12_DEFAULT_SLOPE_SCALED_DEPTH_BIAS;
	m��դ��.mĬ��.DepthClipEnable = TRUE;
	m��դ��.mĬ��.MultisampleEnable = FALSE;
	m��դ��.mĬ��.AntialiasedLineEnable = FALSE;
	m��դ��.mĬ��.ForcedSampleCount = 0;
	m��դ��.mĬ��.ConservativeRaster = D3D12_CONSERVATIVE_RASTERIZATION_MODE_OFF;
	//�߿���Ⱦ
	m��դ��.m�߿���Ⱦ = m��դ��.mĬ��;
	m��դ��.m�߿���Ⱦ.CullMode = D3D12_CULL_MODE_BACK;
	m��դ��.m�߿���Ⱦ.FillMode = D3D12_FILL_MODE_WIREFRAME;
	m��դ��.m�߿���Ⱦ.FrontCounterClockwise = false;
	m��դ��.m�߿���Ⱦ.DepthClipEnable = true;
	m��դ��.m�߿���Ⱦ.MultisampleEnable = true;
	//��ʾ������
	m��դ��.m��ʾ������ = m��դ��.mĬ��;
	m��դ��.m��ʾ������.CullMode = D3D12_CULL_MODE_NONE;
	m��դ��.m��ʾ������.FillMode = D3D12_FILL_MODE_SOLID;
	//������ʱ��Ϊ����
	m��դ��.m������Ⱦ = m��դ��.mĬ��;
	m��դ��.m������Ⱦ.FrontCounterClockwise = true;

	//Ĭ�ϻ��
	m���.mĬ��.AlphaToCoverageEnable = false;
	m���.mĬ��.IndependentBlendEnable = false;
	const D3D12_RENDER_TARGET_BLEND_DESC vĬ����ȾĿ���� = {
		FALSE, FALSE,
		D3D12_BLEND_ONE, D3D12_BLEND_ZERO, D3D12_BLEND_OP_ADD,
		D3D12_BLEND_ONE, D3D12_BLEND_ZERO, D3D12_BLEND_OP_ADD,
		D3D12_LOGIC_OP_NOOP,
		D3D12_COLOR_WRITE_ENABLE_ALL,
	};
	for (UINT i = 0; i < D3D12_SIMULTANEOUS_RENDER_TARGET_COUNT; ++i) {
		m���.mĬ��.RenderTarget[i] = vĬ����ȾĿ����;
	}
	//����͸��
	m���.m����͸��.AlphaToCoverageEnable = false;
	m���.m����͸��.IndependentBlendEnable = false;
	const D3D12_RENDER_TARGET_BLEND_DESC v͸����ȾĿ���� = {
		FALSE, FALSE,
		D3D12_BLEND_SRC_ALPHA, D3D12_BLEND_INV_SRC_ALPHA, D3D12_BLEND_OP_ADD,
		D3D12_BLEND_ONE, D3D12_BLEND_ZERO, D3D12_BLEND_OP_ADD,
		D3D12_LOGIC_OP_NOOP,
		D3D12_COLOR_WRITE_ENABLE_ALL,
	};
	for (UINT i = 0; i < D3D12_SIMULTANEOUS_RENDER_TARGET_COUNT; ++i) {
		m���.m����͸��.RenderTarget[i] = v͸����ȾĿ����;
	}
	//�������
	m���ģ��.mĬ�� = {FALSE, D3D12_DEPTH_WRITE_MASK_ALL, D3D12_COMPARISON_FUNC_LESS, FALSE, D3D12_DEFAULT_STENCIL_READ_MASK, D3D12_DEFAULT_STENCIL_WRITE_MASK, {D3D12_STENCIL_OP_KEEP, D3D12_STENCIL_OP_KEEP, D3D12_STENCIL_OP_KEEP, D3D12_COMPARISON_FUNC_ALWAYS}, {D3D12_STENCIL_OP_KEEP, D3D12_STENCIL_OP_KEEP, D3D12_STENCIL_OP_KEEP, D3D12_COMPARISON_FUNC_ALWAYS}};
	m���ģ��.m�������l = m���ģ��.mĬ��;
	m���ģ��.m�������l.DepthEnable = true;
	m���ģ��.m�������l.DepthWriteMask = D3D12_DEPTH_WRITE_MASK_ALL;
	m���ģ��.m�������l.DepthFunc = D3D12_COMPARISON_FUNC_LESS_EQUAL;
	m���ģ��.m�������l.StencilEnable = false;
	m���ģ��.m�������r = m���ģ��.m�������l;
	m���ģ��.m�������r.DepthFunc = D3D12_COMPARISON_FUNC_GREATER_EQUAL;
	m���ģ��.m���Ǹ��� = m���ģ��.m�������l;
	m���ģ��.m���Ǹ���.DepthFunc = D3D12_COMPARISON_FUNC_ALWAYS;
	//������
	m������.m����.Filter = D3D12_FILTER_MIN_MAG_MIP_LINEAR;
	m������.m����.AddressU = D3D12_TEXTURE_ADDRESS_MODE_WRAP;
	m������.m����.AddressV = D3D12_TEXTURE_ADDRESS_MODE_WRAP;
	m������.m����.AddressW = D3D12_TEXTURE_ADDRESS_MODE_WRAP;
	m������.m����.ComparisonFunc = D3D12_COMPARISON_FUNC_NEVER;
	m������.m����.BorderColor[0] = 0;
	m������.m����.BorderColor[1] = 0;
	m������.m����.BorderColor[2] = 0;
	m������.m����.BorderColor[3] = 0;
	m������.m����.MinLOD = 0;
	m������.m����.MaxLOD = D3D12_FLOAT32_MAX;
	m������.m����.MipLODBias = 0;
	m������.m����.MaxAnisotropy = 16;

	m������.mͼ�� = m������.m����;
	m������.mͼ��.AddressU = D3D12_TEXTURE_ADDRESS_MODE_CLAMP;
	m������.mͼ��.AddressV = D3D12_TEXTURE_ADDRESS_MODE_CLAMP;
	m������.mͼ��.AddressW = D3D12_TEXTURE_ADDRESS_MODE_CLAMP;

	m������.m�������Թ��� = m������.m����;
	m������.m�������Թ���.Filter = D3D12_FILTER_ANISOTROPIC;
}
C��Ⱦ״̬::~C��Ⱦ״̬() {
}
D3D12_SAMPLER_DESC C��Ⱦ״̬::ft������(const D3D12_STATIC_SAMPLER_DESC &a) {
	return {a.Filter, a.AddressU, a.AddressV, a.AddressW, a.MipLODBias, a.MaxAnisotropy, a.ComparisonFunc, {0, 0, 0, 0}, a.MinLOD, a.MaxLOD};
}
D3D12_STATIC_SAMPLER_DESC C��Ⱦ״̬::ft��̬������(const D3D12_SAMPLER_DESC &a, UINT a�Ĵ���, UINT a�ռ�, D3D12_SHADER_VISIBILITY a������) {
	return {a.Filter, a.AddressU, a.AddressV, a.AddressW, a.MipLODBias, a.MaxAnisotropy, a.ComparisonFunc, D3D12_STATIC_BORDER_COLOR_TRANSPARENT_BLACK, a.MinLOD, a.MaxLOD, a�Ĵ���, a�ռ�, a������};
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
	static const char*const v����[] = {
		"POSITION",
		"NORMAL",
		"BINORMAL",
		"COLOR",
		"TEXCOORD",
		"PSIZE",
		"TANGENT"
	};
	f���(v����[a����], a��С);
}
void C�����ʽ::f���(const char *a����, int a��С) {
	static const DXGI_FORMAT v��ʽ[] = {
		DXGI_FORMAT_R32_FLOAT,
		DXGI_FORMAT_R32G32_FLOAT,
		DXGI_FORMAT_R32G32B32_FLOAT,
		DXGI_FORMAT_R32G32B32A32_FLOAT
	};
	D3D12_INPUT_ELEMENT_DESC v;
	v.AlignedByteOffset = m�ֽ��ۼ�;
	v.Format = v��ʽ[a��С - 1];
	m�ֽ��ۼ� += a��С * 4;
	v.SemanticName = a����;
	auto &v�������� = m�����ۼ�[a����];
	v.SemanticIndex = v��������;
	v�������� += 1;
	v.InputSlot = 0;
	v.InputSlotClass = D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA;
	v.InstanceDataStepRate = 0;
	m����.push_back(v);
}
D3D12_INPUT_LAYOUT_DESC C�����ʽ::fg���������() const {
	return {m����.data(), (UINT)m����.size()};
}
//==============================================================================
// ��ǩ��
//==============================================================================
C��ǩ������ &C��ǩ������::f���������(E���� a����, UINT a�Ĵ���, UINT a�ռ�, E��ɫ�� a�ɼ���) {
	fʵ��_�������(E����������::e������);
	D3D12_ROOT_PARAMETER v����;
	v����.ParameterType = f�������������(a����);
	v����.Descriptor.ShaderRegister = a�Ĵ���;
	v����.Descriptor.RegisterSpace = a�ռ�;
	v����.ShaderVisibility = f����ɼ���(a�ɼ���);
	ma����.push_back(v����);
	return *this;
}
C��ǩ������ &C��ǩ������::f��Ӳ�����(const D3D12_SAMPLER_DESC &a������, UINT a�Ĵ���, UINT a�ռ�, E��ɫ�� a�ɼ���) {
	ma������.push_back(C��Ⱦ״̬::ft��̬������(a������, a�Ĵ���, a�ռ�, f����ɼ���(a�ɼ���)));
	return *this;
}
C��ǩ������ &C��ǩ������::f��ӷ�Χ(E���� a����, UINT a����, UINT a��ʼ�Ĵ���, UINT a�Ĵ����ռ�, UINT aƫ��, E��ɫ�� a�ɼ���) {
	assert(mi������� == false);	//������ӷ�Χʱ������ӵ�����Χ
	assert(a���� > 0);
	fʵ��_�������(E����������::e��������);
	S�������� v������;
	v������.m��ʼλ�� = ma������Χ.size();
	v������.m���� = 1;
	v������.m�ɼ��� = f����ɼ���(a�ɼ���);
	ma��������.push_back(v������);
	fʵ��_��ӷ�Χ(a����, a����, a��ʼ�Ĵ���, a�Ĵ����ռ�, aƫ��);
	return *this;
}
C��ǩ������ &C��ǩ������::f������ӷ�Χ(E���� a����, UINT a����, UINT a��ʼ�Ĵ���, UINT a�Ĵ����ռ�, UINT aƫ��) {
	assert(mi������� == true);
	fʵ��_��ӷ�Χ(a����, a����, a��ʼ�Ĵ���, a�Ĵ����ռ�, aƫ��);
	++m�������.m����;
	return *this;
}
C��ǩ������ &C��ǩ������::f������ӷ�Χ��ʼ(E��ɫ�� a�ɼ���) {
	assert(mi������� == false);
	fʵ��_�������(E����������::e��������);
	m�������.m��ʼλ�� = ma������Χ.size();
	m�������.m���� = 0;
	m�������.m�ɼ��� = f����ɼ���(a�ɼ���);
	mi������� = true;
	return *this;
}
C��ǩ������ &C��ǩ������::f������ӷ�Χ����() {
	assert(mi������� == true);
	ma��������.push_back(m�������);
	mi������� = false;
	return *this;
}
void C��ǩ������::fs��־(E��ǩ����־ a) {
	fs��־((D3D12_ROOT_SIGNATURE_FLAGS)a);
}
void C��ǩ������::fs��־(D3D12_ROOT_SIGNATURE_FLAGS a) {

}
void C��ǩ������::fʵ��_��ӷ�Χ(E���� a����, UINT a����, UINT a��ʼ�Ĵ���, UINT a�Ĵ����ռ�, UINT aƫ��) {
	D3D12_DESCRIPTOR_RANGE v��Χ;
	v��Χ.RangeType = f����������Χ����(a����);
	v��Χ.NumDescriptors = a����;
	v��Χ.BaseShaderRegister = a��ʼ�Ĵ���;
	v��Χ.RegisterSpace = a�Ĵ����ռ�;
	v��Χ.OffsetInDescriptorsFromTableStart = aƫ��;
	ma������Χ.push_back(v��Χ);
}
void C��ǩ������::fʵ��_�������(E���������� a����) {
	S���������� v���� = {};
	v����.m���� = a����;
	switch (a����) {
	case E����������::e��������:
		v����.mλ�� = ma��������.size();
		break;
	case E����������::e����:
	case E����������::e������:
		v����.mλ�� = ma����.size();
		break;
	default:
		throw;
	}
	ma����.push_back(v����);
}
D3D12_SHADER_VISIBILITY C��ǩ������::f����ɼ���(E��ɫ�� a) {
	switch (a) {
	case E��ɫ��::e������ɫ��:
		return D3D12_SHADER_VISIBILITY_VERTEX;
	case E��ɫ��::e�����ɫ��:
		return D3D12_SHADER_VISIBILITY_HULL;
	case E��ɫ��::e����ɫ��:
		return D3D12_SHADER_VISIBILITY_DOMAIN;
	case E��ɫ��::e������ɫ��:
		return D3D12_SHADER_VISIBILITY_GEOMETRY;
	case E��ɫ��::e������ɫ��:
		return D3D12_SHADER_VISIBILITY_PIXEL;
	default:
		return D3D12_SHADER_VISIBILITY_ALL;
	}
}
D3D12_ROOT_PARAMETER_TYPE C��ǩ������::f�������������(E���� a) {
	switch (a) {
	case E����::e��ɫ����Դ��ͼ:
		return D3D12_ROOT_PARAMETER_TYPE_SRV;
	case E����::e�̶�������ͼ:
		return D3D12_ROOT_PARAMETER_TYPE_CBV;
	case E����::e���������ͼ:
		return D3D12_ROOT_PARAMETER_TYPE_UAV;
	case E����::e������:
		return D3D12_ROOT_PARAMETER_TYPE_32BIT_CONSTANTS;
	default:
		throw;
	}
}
D3D12_DESCRIPTOR_RANGE_TYPE C��ǩ������::f����������Χ����(E���� a) {
	switch (a) {
	case E����::e��ɫ����Դ��ͼ:
		return D3D12_DESCRIPTOR_RANGE_TYPE_SRV;
	case E����::e�̶�������ͼ:
		return D3D12_DESCRIPTOR_RANGE_TYPE_CBV;
	case E����::e���������ͼ:
		return D3D12_DESCRIPTOR_RANGE_TYPE_UAV;
	case E����::e������:
		return D3D12_DESCRIPTOR_RANGE_TYPE_SAMPLER;
	default:
		throw;
	}
}
//==============================================================================
// �޸�
//==============================================================================
C�Զ�ӳ��::C�Զ�ӳ��(ID3D12Resource *a):
	m��Դ(a) {
	HRESULT hr = m��Դ->Map(0, nullptr, &mָ��);
	if (FAILED(hr)) {
		throw;
	}
}
C�Զ�ӳ��::~C�Զ�ӳ��() {
	m��Դ->Unmap(0, nullptr);
}
//==============================================================================
// ��Դ����
//==============================================================================
DXGI_FORMAT C���幤��::f����������ʽ(UINT a���ʹ�С) {
	switch (a���ʹ�С) {
	case 2:
		return DXGI_FORMAT_R16_UINT;
	case 4:
		return DXGI_FORMAT_R32_UINT;
	default:
		return DXGI_FORMAT_UNKNOWN;
	}
}
void C���幤��::f��ʼ��(ID3D12Device *a�豸) {
	m�豸 = a�豸;
}
HRESULT C���幤��::f����ֻ����Դ(ComPtr<ID3D12Resource> &a, const void *a����, UINT a���ݴ�С) {
	//������Դ
	const D3D12_HEAP_PROPERTIES v������ = {D3D12_HEAP_TYPE_UPLOAD, D3D12_CPU_PAGE_PROPERTY_UNKNOWN, D3D12_MEMORY_POOL_UNKNOWN, 1, 1};
	const D3D12_RESOURCE_DESC v��Դ���� = S��Դ����::fc����(a���ݴ�С);
	HRESULT hr = m�豸->CreateCommittedResource(&v������, D3D12_HEAP_FLAG_NONE, &v��Դ����, D3D12_RESOURCE_STATE_GENERIC_READ, nullptr, IID_PPV_ARGS(&a));
	if (FAILED(hr)) {
		return hr;
	}
	//��������
	UINT8 *vp����;
	const D3D12_RANGE v��Χ{0, 0};
	hr = a->Map(0, &v��Χ, (void**)(&vp����));
	if (FAILED(hr)) {
		return hr;
	}
	memcpy(vp����, a����, a���ݴ�С);
	a->Unmap(0, nullptr);
	return S_OK;
}
HRESULT C���幤��::f��������(tp���� &a, const void *a����, UINT a���ʹ�С, UINT a���ݴ�С) {
	tp���� v = std::make_shared<C���㻺��>();
	HRESULT hr = f����ֻ����Դ(v->m��Դ, a����, a���ݴ�С);
	if (FAILED(hr)) {
		return hr;
	}
	v->m��Դ->SetName(L"����");
	//���㻺����ͼ
	v->m��ͼ.BufferLocation = v->m��Դ->GetGPUVirtualAddress();
	v->m��ͼ.StrideInBytes = a���ʹ�С;
	v->m��ͼ.SizeInBytes = a���ݴ�С;
	//����
	a = std::move(v);
	return S_OK;
}
HRESULT C���幤��::f��������(tp���� &a, const void *a����, UINT a���ʹ�С, UINT a���ݴ�С) {
	//������
	const DXGI_FORMAT v������ʽ = f����������ʽ(a���ʹ�С);
	if (v������ʽ == DXGI_FORMAT_UNKNOWN) {
		return E_INVALIDARG;
	}
	//��Դ
	tp���� v = std::make_shared<C��������>();
	HRESULT hr = f����ֻ����Դ(v->m��Դ, a����, a���ݴ�С);
	if (FAILED(hr)) {
		return hr;
	}
	v->m��Դ->SetName(L"����");
	//���㻺����ͼ
	v->m��ͼ.BufferLocation = v->m��Դ->GetGPUVirtualAddress();
	v->m��ͼ.SizeInBytes = a���ݴ�С;
	v->m��ͼ.Format = v������ʽ;
	//����
	a = std::move(v);
	return S_OK;
}
HRESULT C���幤��::f�����̶�(tp�̶� &a, const void *a����, UINT a���ʹ�С, UINT a���ݴ�С) {
	//��������
	D3D12_DESCRIPTOR_HEAP_DESC cbvHeapDesc = {};
	cbvHeapDesc.NumDescriptors = 1;
	cbvHeapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE;
	cbvHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV;
	tp�̶� v = std::make_shared<C�̶�����>();
	HRESULT hr = m�豸->CreateDescriptorHeap(&cbvHeapDesc, IID_PPV_ARGS(&v->m��������));
	if (FAILED(hr)) {
		return hr;
	}
	//��Դ
	const S������ v������ = S������::fc����(D3D12_HEAP_TYPE_UPLOAD);
	const UINT v���ݴ�С = (a���ݴ�С + 255) & ~255;	// 256�ֽڶ���
	const D3D12_RESOURCE_DESC v��Դ���� = S��Դ����::fc����(v���ݴ�С);
	hr = m�豸->CreateCommittedResource(&v������, D3D12_HEAP_FLAG_NONE, &v��Դ����, D3D12_RESOURCE_STATE_GENERIC_READ, nullptr, IID_PPV_ARGS(&v->m��Դ));
	if (FAILED(hr)) {
		return hr;
	}
	v->m��Դ->SetName(L"�̶�");
	//��ͼ
	D3D12_CONSTANT_BUFFER_VIEW_DESC cbvd = {};
	cbvd.BufferLocation = v->m��Դ->GetGPUVirtualAddress();
	cbvd.SizeInBytes = v���ݴ�С;
	m�豸->CreateConstantBufferView(&cbvd, v->m��������->GetCPUDescriptorHandleForHeapStart());
	if (FAILED(hr)) {
		return hr;
	}
	const D3D12_RANGE v��Χ{0, 0};
	v->m��Դ->Map(0, &v��Χ, (void**)&v->mӳ��);
	memcpy(v->mӳ��, &a����, a���ݴ�С);
	//����
	a = std::move(v);
	return S_OK;
}
//==============================================================================
// ��ɫ������
//==============================================================================
HRESULT C��ɫ������::f���붥����ɫ��(ComPtr<ID3DBlob> &a, const wchar_t *a�ļ���, const char *a������) {
	return f������ɫ��(a�ļ���, a������, "vs_5_0", &a);
}
HRESULT C��ɫ������::f����������ɫ��(ComPtr<ID3DBlob> &a, const wchar_t *a�ļ���, const char *a������) {
	return f������ɫ��(a�ļ���, a������, "ps_5_0", &a);
}
HRESULT C��ɫ������::f���뼸����ɫ��(ComPtr<ID3DBlob> &a, const wchar_t *a�ļ���, const char *a������) {
	return f������ɫ��(a�ļ���, a������, "gs_5_0", &a);
}
HRESULT C��ɫ������::f���������ɫ��(ComPtr<ID3DBlob> &a, const wchar_t *a�ļ���, const char *a������) {
	return f������ɫ��(a�ļ���, a������, "hs_5_0", &a);
}
HRESULT C��ɫ������::f��������ɫ��(ComPtr<ID3DBlob> &a, const wchar_t *a�ļ���, const char *a������) {
	return f������ɫ��(a�ļ���, a������, "ds_5_0", &a);
}
HRESULT C��ɫ������::f������ɫ��(const wchar_t *a�ļ���, const char *a���, const char *a��ɫģ��, ID3DBlob** a���) {
	HRESULT hr = S_OK;
	DWORD v��ɫ��־ = D3DCOMPILE_ENABLE_STRICTNESS;
#if defined( DEBUG ) || defined( _DEBUG )
	v��ɫ��־ |= D3DCOMPILE_DEBUG;
#endif
	ComPtr<ID3DBlob> v����;
	hr = D3DCompileFromFile(a�ļ���, nullptr, nullptr, a���, a��ɫģ��, v��ɫ��־, 0, a���, &v����);
	if (FAILED(hr)) {
		if (v���� != nullptr) {
			OutputDebugStringA((char*)v����->GetBufferPointer());
		}
		return hr;
	}
	return S_OK;
}
HRESULT C��ɫ������::f��ȡ��ɫ��(const wchar_t *a�ļ���, std::unique_ptr<std::byte[]> &a����, DWORD &a��С) {
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
//==============================================================================
// ������
//==============================================================================
C������::~C������() {}
HRESULT C������::f��ʼ��() {
	m���� = std::make_unique<����::Cͼ�񹤳�>();
	return m����->f��ʼ��();
}
HRESULT C������::f���ļ���������(tp���� &a���, const wchar_t *a�ļ�) {
	std::unique_ptr<����::C�̶�����> v���� = m����->fһ����ȡ(a�ļ�);
	if (v���� == nullptr) {
		return E_FAIL;
	}
	return f��������󴴽�����(a���, *v����);
}
HRESULT C������::f��������󴴽�����(tp���� &a���, const ����::I���� &a����) {
	tp���� v = std::make_shared<C������Դ>();
	HRESULT hr = f��������󴴽�������Դ(v->m��Դ, a����);
	if (FAILED(hr)) {
		return hr;
	}
	hr = f��������Դ����������ͼ(v->m��������, v->m��Դ, a����.fg��ʽ());
	if (FAILED(hr)) {
		return hr;
	}
	//����
	a��� = std::move(v);
	return S_OK;
}
HRESULT C������::f���ڴ洴��������Դ(tp��Դ &a���, const void *a����, DXGI_FORMAT a��ʽ, UINT a��, UINT a��, UINT a�о�, UINT a��С) {
	//������Դ
	D3D12_RESOURCE_DESC v�������� = {};
	v��������.Dimension = D3D12_RESOURCE_DIMENSION_TEXTURE2D;
	v��������.Width = a��;
	v��������.Height = a��;
	v��������.DepthOrArraySize = 1;
	v��������.MipLevels = 1;
	v��������.Format = a��ʽ;
	v��������.SampleDesc.Count = 1;
	v��������.SampleDesc.Quality = 0;
	v��������.Layout = D3D12_TEXTURE_LAYOUT_UNKNOWN;
	v��������.Flags = D3D12_RESOURCE_FLAG_NONE;
	HRESULT hr = m�豸->CreateCommittedResource(&S������::fc����(D3D12_HEAP_TYPE_DEFAULT), D3D12_HEAP_FLAG_NONE, &v��������, D3D12_RESOURCE_STATE_COPY_DEST, nullptr, IID_PPV_ARGS(&a���));
	if (FAILED(hr)) {
		return hr;
	}
	a���->SetName(L"����");
	//��������
	const UINT64 v�ϴ���С = GetRequiredIntermediateSize(a���.Get(), 0, 1);
	ComPtr<ID3D12Resource> v�ϴ���Դ;
	hr = m��ά->f�����ϴ���Դ(v�ϴ���Դ, nullptr, v�ϴ���С);
	if (FAILED(hr)) {
		return hr;
	}
	D3D12_SUBRESOURCE_DATA v��Դ���� = {};
	v��Դ����.pData = a����;
	v��Դ����.RowPitch = a�о�;
	v��Դ����.SlicePitch = a��С;
	m��Ⱦ����->f��������(a���.Get(), v�ϴ���Դ.Get(), v��Դ����);
	return S_OK;
}
HRESULT C������::f��������󴴽�������Դ(tp��Դ &a���, const ����::I���� &a����) {
	return f���ڴ洴��������Դ(a���, a����.fg����(), a����.fg��ʽ(), a����.fg��(), a����.fg��(), a����.fg�о�(), a����.fgͼ���С());
}
HRESULT C������::f��������Դ����������ͼ(tp�������� &a���, const tp��Դ &a��Դ, DXGI_FORMAT a��ʽ) {
	D3D12_DESCRIPTOR_HEAP_DESC v������ = {};
	v������.NumDescriptors = 1;
	v������.Type = D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV;
	v������.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE;
	HRESULT hr = m�豸->CreateDescriptorHeap(&v������, IID_PPV_ARGS(&a���));
	if (FAILED(hr)) {
		return hr;
	}
	D3D12_SHADER_RESOURCE_VIEW_DESC v��ͼ���� = {};
	v��ͼ����.Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;
	v��ͼ����.Format = a��ʽ;
	v��ͼ����.ViewDimension = D3D12_SRV_DIMENSION_TEXTURE2D;
	v��ͼ����.Texture2D.MipLevels = 1;
	m�豸->CreateShaderResourceView(a��Դ.Get(), &v��ͼ����, a���->GetCPUDescriptorHandleForHeapStart());
	return S_OK;
}
//==============================================================================
// ��Դ����
//==============================================================================
S��ɫ���ֽڴ��� S��ɫ���ֽڴ���::fc�����ƴ����(ID3DBlob *a) {
	return {a->GetBufferPointer(), a->GetBufferSize()};
}
S��Դ���� S��Դ����::fc����(UINT64 a��) {
	S��Դ���� v = {};
	v.Dimension = D3D12_RESOURCE_DIMENSION_BUFFER;
	v.Alignment = 0;
	v.Width = a��;
	v.Height = 1;
	v.DepthOrArraySize = 1;
	v.MipLevels = 1;
	v.Format = DXGI_FORMAT_UNKNOWN;
	v.SampleDesc.Count = 1;
	v.SampleDesc.Quality = 0;
	v.Layout = D3D12_TEXTURE_LAYOUT_ROW_MAJOR;
	v.Flags = D3D12_RESOURCE_FLAG_NONE;
	return v;
}
S��Դ���� S��Դ����::fc����2(UINT64 a��, UINT a��, DXGI_FORMAT a��ʽ, D3D12_RESOURCE_FLAGS a��־) {
	S��Դ���� v = {};
	v.Dimension = D3D12_RESOURCE_DIMENSION_TEXTURE2D;
	v.Alignment = 0;
	v.Width = a��;
	v.Height = a��;
	v.DepthOrArraySize = 1;
	v.MipLevels = 1;
	v.Format = a��ʽ;
	v.SampleDesc.Count = 1;
	v.SampleDesc.Quality = 0;
	v.Layout = D3D12_TEXTURE_LAYOUT_UNKNOWN;
	v.Flags = a��־;
	return v;
}
//==============================================================================
// ͼ�ι��߲���
//==============================================================================
Sͼ�ι��߲���::Sͼ�ι��߲���():
	D3D12_GRAPHICS_PIPELINE_STATE_DESC() {
	NumRenderTargets = 1;
	RTVFormats[0] = c��������ʽ;
	SampleDesc.Count = 1;
	SampleMask = UINT_MAX;
}
void Sͼ�ι��߲���::fs���벼��(const C�����ʽ &a) {
	InputLayout = a.fg���������();
}
void Sͼ�ι��߲���::fs��ǩ��(ID3D12RootSignature *a) {
	pRootSignature = a;
}
void Sͼ�ι��߲���::fs������ɫ��(ID3DBlob *a) {
	VS = S��ɫ���ֽڴ���::fc�����ƴ����(a);
}
void Sͼ�ι��߲���::fs������ɫ��(ID3DBlob *a) {
	PS = S��ɫ���ֽڴ���::fc�����ƴ����(a);
}
void Sͼ�ι��߲���::fs������ɫ��(ID3DBlob *a) {
	GS = S��ɫ���ֽڴ���::fc�����ƴ����(a);
}
void Sͼ�ι��߲���::fs�����ɫ��(ID3DBlob *a) {
	HS = S��ɫ���ֽڴ���::fc�����ƴ����(a);
}
void Sͼ�ι��߲���::fs����ɫ��(ID3DBlob *a) {
	DS = S��ɫ���ֽڴ���::fc�����ƴ����(a);
}
void Sͼ�ι��߲���::fs��դ��(const D3D12_RASTERIZER_DESC &a) {
	RasterizerState = a;
}
void Sͼ�ι��߲���::fs���(const D3D12_BLEND_DESC &a) {
	BlendState = a;
}
void Sͼ�ι��߲���::fs���ģ��(const D3D12_DEPTH_STENCIL_DESC &a) {
	DSVFormat = c���ģ���ʽ;
	DepthStencilState = a;
}
void Sͼ�ι��߲���::f�ر����ģ��() {
	DepthStencilState.DepthEnable = FALSE;
	DepthStencilState.StencilEnable = FALSE;
}
void Sͼ�ι��߲���::fsͼԪ��������(EͼԪ�������� a) {
	PrimitiveTopologyType = (D3D12_PRIMITIVE_TOPOLOGY_TYPE)a;
}
S��Դդ�� S��Դդ��::fc�任(ID3D12Resource* a��Դ, D3D12_RESOURCE_STATES aǰ, D3D12_RESOURCE_STATES a��, UINT a����Դ, D3D12_RESOURCE_BARRIER_FLAGS a��־) {
	S��Դդ�� vդ��{};
	vդ��.Type = D3D12_RESOURCE_BARRIER_TYPE_TRANSITION;
	vդ��.Flags = a��־;
	vդ��.Transition.StateBefore = aǰ;
	vդ��.Transition.StateAfter = a��;
	vդ��.Transition.pResource = a��Դ;
	vդ��.Transition.Subresource = a����Դ;
	return vդ��;
}
//==============================================================================
// ������
//==============================================================================
S������ S������::fc����(D3D12_HEAP_TYPE a����, UINT a�����ڵ�����, UINT a�ɼ��ڵ�����) {
	S������ v������ = {};
	v������.Type = a����;
	v������.CPUPageProperty = D3D12_CPU_PAGE_PROPERTY_UNKNOWN;
	v������.MemoryPoolPreference = D3D12_MEMORY_POOL_UNKNOWN;
	v������.CreationNodeMask = a�����ڵ�����;
	v������.VisibleNodeMask = a�ɼ��ڵ�����;
	return v������;
}
//==============================================================================
// ��������
//==============================================================================
S�������� S��������::fc��ӡ(ID3D12Resource *a��Դ, const D3D12_PLACED_SUBRESOURCE_FOOTPRINT &a��ӡ) {
	S�������� v = {};
	v.pResource = a��Դ;
	v.Type = D3D12_TEXTURE_COPY_TYPE_PLACED_FOOTPRINT;
	v.PlacedFootprint = a��ӡ;
	return v;
}
S�������� S��������::fc����(ID3D12Resource *a��Դ, UINT a����) {
	S�������� v = {};
	v.pResource = a��Դ;
	v.Type = D3D12_TEXTURE_COPY_TYPE_SUBRESOURCE_INDEX;
	v.SubresourceIndex = a����;
	return v;
}
//==============================================================================
// ���ֵ
//==============================================================================
S���ֵ S���ֵ::fc��ɫ(DXGI_FORMAT a��ʽ, const ��ѧ::S��ɫ &a��ɫ) {
	S���ֵ v = {};
	v.Format = a��ʽ;
	v.Color[0] = a��ɫ.r;
	v.Color[1] = a��ɫ.g;
	v.Color[2] = a��ɫ.b;
	v.Color[3] = a��ɫ.a;
	return v;
}
S���ֵ S���ֵ::fc���ģ��(DXGI_FORMAT a��ʽ, float a���, UINT8 aģ��) {
	S���ֵ v = {};
	v.Format = a��ʽ;
	v.DepthStencil.Depth = a���;
	v.DepthStencil.Stencil = aģ��;
	return v;
}
}	//namespace cflw::ͼ��::d3d12