﻿#include <D3Dcompiler.h>
#include "cflw图形_d3d12.h"
#include "d3dx12.h"
#include "cflw视窗.h"
#include "cflw辅助.h"
namespace cflw::图形::d3d12 {
//==============================================================================
// 三维
//==============================================================================
C三维::~C三维() {
	f销毁();
}
void C三维::f销毁() {
	if (m设备 == nullptr) {
		return;
	}
	m渲染控制->f等待完成帧();

	m缓冲工厂.reset();
	m创建设备.reset();
	m渲染状态.reset();
	m渲染目标管理.reset();
	m渲染控制.reset();

	m默认根签名.Reset();
	m命令分配器.Reset();
	m交换链.Reset();
	m命令队列.Reset();
	m设备.Reset();
}
void C三维::f初始化窗口(HWND a) {
	m窗口 = a;
	fs窗口大小();
}
HRESULT C三维::f初始化设备(HRESULT(C创建设备::*af取显卡)(IDXGIAdapter3 **)) {
	C创建设备 &v创建设备 = fg创建设备();
	if constexpr (c调试) {
		m标志[e调试] = v创建设备.f开启调试层();
	}
	HRESULT hr = S_OK;
	ComPtr<IDXGIAdapter3> v显卡;
	if (af取显卡 == nullptr) {
		af取显卡 = &C创建设备::f取显卡_性能;
	}
	hr = (v创建设备.*af取显卡)(&v显卡);
	if (FAILED(hr)) {
		return hr;
	}
	hr = v创建设备.f创建设备(v显卡.Get(), &m设备);
	if (FAILED(hr)) {
		return hr;
	}
	m标志[e软件设备] = af取显卡 == &C创建设备::f取软件适配器;
	return S_OK;
}
HRESULT C三维::f初始化软件设备() {
	return f初始化设备(&C创建设备::f取软件适配器);
}
HRESULT C三维::f初始化命令队列() {
	assert(m设备);
	D3D12_COMMAND_QUEUE_DESC qd = {};
	qd.Flags = D3D12_COMMAND_QUEUE_FLAG_NONE;
	qd.Type = D3D12_COMMAND_LIST_TYPE_DIRECT;
	HRESULT hr = m设备->CreateCommandQueue(&qd, IID_PPV_ARGS(&m命令队列));
	if (FAILED(hr)) {
		return hr;
	}
	hr = m设备->CreateCommandAllocator(D3D12_COMMAND_LIST_TYPE_DIRECT, IID_PPV_ARGS(&m命令分配器));
	if (FAILED(hr)) {
		return hr;
	}
	return S_OK;
}
HRESULT C三维::f初始化交换链() {
	assert(m设备);
	C创建设备 &v创建设备 = fg创建设备();
	m标志[e撕裂] = v创建设备.f检查撕裂();
	const UINT v撕裂 = m标志[e撕裂] ? DXGI_SWAP_CHAIN_FLAG_ALLOW_TEARING : 0;
	m交换链标志 = v撕裂;
	//交换链描述
	DXGI_SWAP_CHAIN_DESC1 sd = {};
	sd.BufferCount = c帧数;
	sd.Width = m窗口大小[0];
	sd.Height = m窗口大小[1];
	sd.Format = c交换链格式;
	sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	sd.SwapEffect = DXGI_SWAP_EFFECT_FLIP_SEQUENTIAL;
	sd.SampleDesc.Count = 1;
	sd.SampleDesc.Quality = 0;
	sd.Stereo = false;
	sd.Flags = m交换链标志;
	sd.AlphaMode = DXGI_ALPHA_MODE_UNSPECIFIED;
	sd.Scaling = DXGI_SCALING_STRETCH;
	//创建交换链
	ComPtr<IDXGIFactory5> v工厂 = v创建设备.fg工厂();
	ComPtr<IDXGISwapChain1> v交换链;
	HRESULT hr = v工厂->CreateSwapChainForHwnd(m命令队列.Get(), m窗口, &sd, nullptr, nullptr, &v交换链);
	if (FAILED(hr)) {
		return hr;
	}
	//其它
	hr = v工厂->MakeWindowAssociation(m窗口, DXGI_MWA_NO_ALT_ENTER);
	if (FAILED(hr)) {
		return hr;
	}
	//返回
	v交换链.As(&m交换链);
	return S_OK;
}
HRESULT C三维::f初始化渲染目标视图() {
	assert(m设备);
	m渲染目标管理 = std::make_unique<C渲染目标管理>();
	//堆
	D3D12_DESCRIPTOR_HEAP_DESC v描述 = {};
	v描述.NumDescriptors = c帧数;
	v描述.Type = D3D12_DESCRIPTOR_HEAP_TYPE_RTV;
	v描述.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_NONE;
	m设备->CreateDescriptorHeap(&v描述, IID_PPV_ARGS(&m渲染目标管理->m渲染目标堆));
	m渲染目标管理->m渲染目标视图大小 = m设备->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV);
	//循环
	D3D12_CPU_DESCRIPTOR_HANDLE v渲染目标视图句柄 = m渲染目标管理->m渲染目标堆->GetCPUDescriptorHandleForHeapStart();
	for (UINT i = 0; i < c帧数; ++i) {
		auto &v渲染目标 = m渲染目标管理->m渲染目标[i];
		//资源
		m交换链->GetBuffer(i, IID_PPV_ARGS(&v渲染目标));
		//视图
		m设备->CreateRenderTargetView(v渲染目标.Get(), nullptr, v渲染目标视图句柄);
		v渲染目标视图句柄.ptr += m渲染目标管理->m渲染目标视图大小;
		//名称
		if constexpr (c调试) {
			const std::wstring v名称 = std::wstring(L"渲染目标") + std::to_wstring(i);
			v渲染目标->SetName(v名称.c_str());
		}
	}
	//结束
	if (m渲染控制) {
		m渲染目标管理->m帧索引 = &m渲染控制->m帧索引;
	}
	return S_OK;
}
HRESULT C三维::f初始化深度模板视图() {
	m深度模板管理 = std::make_unique<C深度模板管理>();
	//堆
	D3D12_DESCRIPTOR_HEAP_DESC v堆描述 = {};
	v堆描述.NumDescriptors = 1;
	v堆描述.Type = D3D12_DESCRIPTOR_HEAP_TYPE_DSV;
	v堆描述.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_NONE;
	HRESULT hr = m设备->CreateDescriptorHeap(&v堆描述, IID_PPV_ARGS(&m深度模板管理->m深度模板堆));
	if (FAILED(hr)) {
		return hr;
	}
	//资源准备
	const D3D12_RESOURCE_DESC v资源描述 = S资源描述::fc纹理2(m窗口大小[0], m窗口大小[1], c深度模板格式, D3D12_RESOURCE_FLAG_ALLOW_DEPTH_STENCIL);
	const D3D12_HEAP_PROPERTIES v堆属性 = S堆属性::fc类型(D3D12_HEAP_TYPE_DEFAULT);
	const D3D12_CLEAR_VALUE v清除值 = S清除值::fc深度模板(c深度模板格式, c清屏深度r, 0);
	//视图准备
	D3D12_DEPTH_STENCIL_VIEW_DESC v视图描述 = {};
	v视图描述.Format = c深度模板格式;
	v视图描述.ViewDimension = D3D12_DSV_DIMENSION_TEXTURE2D;
	v视图描述.Texture2D.MipSlice = 0;
	//循环
	D3D12_CPU_DESCRIPTOR_HANDLE v深度模板视图句柄 = m深度模板管理->m深度模板堆->GetCPUDescriptorHandleForHeapStart();
	for (UINT i = 0; i != c帧数; ++i) {
		auto &v深度模板 = m深度模板管理->m深度模板[i];
		//资源
		hr = m设备->CreateCommittedResource(&v堆属性, D3D12_HEAP_FLAG_NONE, &v资源描述, D3D12_RESOURCE_STATE_DEPTH_WRITE, &v清除值, IID_PPV_ARGS(&v深度模板));
		if (FAILED(hr)) {
			return hr;
		}
		//视图
		m设备->CreateDepthStencilView(v深度模板.Get(), &v视图描述, v深度模板视图句柄);
		v深度模板视图句柄.ptr += m深度模板管理->m深度模板视图大小;
		//名称
		if constexpr (c调试) {
			const std::wstring v名称 = std::wstring(L"深度模板") + std::to_wstring(i);
			v深度模板->SetName(v名称.c_str());
		}
	}
	//结束
	if (m渲染控制) {
		m深度模板管理->m帧索引 = &m渲染控制->m帧索引;
	}
	return S_OK;
}
HRESULT C三维::f初始化根签名() {
	D3D12_ROOT_SIGNATURE_DESC v描述 = {};
	v描述.NumParameters = 0;
	v描述.pParameters = nullptr;
	v描述.NumStaticSamplers = 0;
	v描述.pStaticSamplers = nullptr;
	v描述.Flags = D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT;
	return f创建根签名(m默认根签名, v描述);
}
bool C三维::f初始化(const HWND &a) {
	try {
		f初始化窗口(a);
		视窗::f失败则抛出(f初始化设备());
		视窗::f失败则抛出(f初始化命令队列());
		视窗::f失败则抛出(f初始化交换链());
		视窗::f失败则抛出(f初始化渲染目标视图());
		视窗::f失败则抛出(f初始化深度模板视图());
		视窗::f失败则抛出(f初始化根签名());
		return true;
	} catch (HRESULT hr) {
		return false;
	}
}
HRESULT C三维::f重置屏幕资源() {
	HRESULT hr;
	const bool v重置深度模板 = m深度模板管理.operator bool();
	if (m交换链) {
		hr = f重置交换链();
		if (FAILED(hr)) {
			return hr;
		}
		hr = f初始化渲染目标视图();
		if (FAILED(hr)) {
			return hr;
		}
	}
	if (v重置深度模板) {
		hr = f初始化深度模板视图();
		if (FAILED(hr)) {
			return hr;
		}
	}
	return S_OK;
}
HRESULT C三维::f重置交换链() {
	assert(m交换链);
	//m渲染控制->f重置命令();
	m渲染控制->m命令列表->Close();
	m渲染目标管理 = nullptr;
	m深度模板管理 = nullptr;
	HRESULT hr = m交换链->ResizeBuffers(c帧数, m窗口大小[0], m窗口大小[1], c交换链格式, m交换链标志);
	if (FAILED(hr)) {
		return hr;
	}
	m渲染控制->m帧索引 = m交换链->GetCurrentBackBufferIndex();
	return S_OK;
}
HRESULT C三维::f调整目标大小() {
	DXGI_MODE_DESC v模式描述 = {};
	v模式描述.Width = m窗口大小[0];
	v模式描述.Height = m窗口大小[1];
	HRESULT hr = m交换链->ResizeTarget(&v模式描述);
	return hr;
}
HRESULT C三维::f创建图形管线(tp图形管线 &a, const D3D12_GRAPHICS_PIPELINE_STATE_DESC &a描述) {
	assert(m设备);
	//检查参数
	if (a描述.VS.pShaderBytecode) {
		assert(a描述.InputLayout.pInputElementDescs && a描述.InputLayout.NumElements);
	}
	assert(a描述.PrimitiveTopologyType != D3D12_PRIMITIVE_TOPOLOGY_TYPE_UNDEFINED);
	//创建
	//注意：I卡可能会报错D3D12 ERROR: ID3D12Device::CreateVertexShader: Shader is corrupt or in an unrecognized format. [ STATE_CREATION ERROR #67: CREATEVERTEXSHADER_INVALIDSHADERBYTECODE]。换成其他显卡则正常。
	HRESULT hr = m设备->CreateGraphicsPipelineState(&a描述, IID_PPV_ARGS(&a));
	if (FAILED(hr)) {
		return hr;
	}
	return S_OK;
}
HRESULT C三维::f创建命令列表(tp命令列表 &a, ID3D12PipelineState *a图形管线) {
	assert(m设备);
	HRESULT hr = m设备->CreateCommandList(0, D3D12_COMMAND_LIST_TYPE_DIRECT, m命令分配器.Get(), a图形管线, IID_PPV_ARGS(&a));
	if (FAILED(hr)) {
		return hr;
	}
	hr = a->Close();
	if (FAILED(hr)) {
		return hr;
	}
	return S_OK;
}
HRESULT C三维::f创建根签名(tp根签名 &a, const C根签名参数 &a参数) {
	D3D12_ROOT_SIGNATURE_DESC v描述;
	v描述.NumStaticSamplers = a参数.ma采样器.size();
	v描述.pStaticSamplers = a参数.ma采样器.data();
	v描述.Flags = a参数.m标志;
	std::vector<D3D12_ROOT_PARAMETER> va参数;
	for (const auto &v0 : a参数.ma索引) {
		switch (v0.m类型) {
		case C根签名参数::E根参数类型::e描述符表:{
			const auto &v1 = a参数.ma描述符表[v0.m位置];
			D3D12_ROOT_PARAMETER v参数;
			v参数.ParameterType = D3D12_ROOT_PARAMETER_TYPE_DESCRIPTOR_TABLE;
			v参数.DescriptorTable.NumDescriptorRanges = v1.m数量;
			v参数.DescriptorTable.pDescriptorRanges = &a参数.ma描述范围[v1.m开始位置];
			v参数.ShaderVisibility = v1.m可见性;
			va参数.push_back(v参数);
			break;
		}
		case C根签名参数::E根参数类型::e常量:
		case C根签名参数::E根参数类型::e描述符:
			va参数.push_back(a参数.ma参数[v0.m位置]);
			break;
		default:
			return E_INVALIDARG;
		}
	}
	v描述.NumParameters = va参数.size();
	v描述.pParameters = va参数.data();
	return f创建根签名(a, v描述);
}
HRESULT C三维::f创建根签名(tp根签名 &a, const D3D12_ROOT_SIGNATURE_DESC &a描述) {
	ComPtr<ID3DBlob> v签名, v错误;
	HRESULT hr = D3D12SerializeRootSignature(&a描述, D3D_ROOT_SIGNATURE_VERSION_1, &v签名, &v错误);
	if (FAILED(hr)) {
		return hr;
	}
	hr = m设备->CreateRootSignature(0, v签名->GetBufferPointer(), v签名->GetBufferSize(), IID_PPV_ARGS(&a));
	if (FAILED(hr)) {
		return hr;
	}
	return S_OK;
}
D3D12_VIEWPORT C三维::fg窗口视口() {
	D3D12_VIEWPORT v视口;
	v视口.Width = (FLOAT)m窗口大小[0];
	v视口.Height = (FLOAT)m窗口大小[1];
	v视口.MinDepth = 0.0f;
	v视口.MaxDepth = 1.0f;
	v视口.TopLeftX = 0;
	v视口.TopLeftY = 0;
	return v视口;
}
D3D12_RECT C三维::fg窗口矩形() {
	return {0, 0, m窗口大小[0], m窗口大小[1]};
}
数学::S向量2 C三维::fg窗口大小() const {
	return {(float)m窗口大小[0], (float)m窗口大小[1]};
}
void C三维::fs窗口大小() {
	视窗::S客户区尺寸 v尺寸 = 视窗::S客户区尺寸::fc窗口(m窗口);
	fs窗口大小_(v尺寸.fg宽(), v尺寸.fg高());
}
HRESULT C三维::fs窗口大小(int a宽, int a高) {
	fs窗口大小_(a宽, a高);
	if (!fi全屏()) {
		HRESULT hr = f调整目标大小();
		if (FAILED(hr)) {
			return hr;
		}
	}
	return S_OK;
}
void C三维::fs窗口大小_(int a宽, int a高) {
	m窗口大小[0] = a宽;
	m窗口大小[1] = a高;
	m默认视口 = fg窗口视口();
	m默认裁剪矩形 = fg窗口矩形();
}
bool C三维::fi全屏() const {
	BOOL v;
	m交换链->GetFullscreenState(&v, nullptr);
	return v;
}
bool C三维::fi窗口() const {
	return !fi全屏();
}
void C三维::fs全屏(bool a) {
	m交换链->SetFullscreenState(a, nullptr);
	if (!a) {
		f调整目标大小();
	}
}
C渲染控制 &C三维::fg渲染控制() {
	if (m渲染控制 == nullptr) {
		m渲染控制 = std::make_unique<C渲染控制>();
		m渲染控制->m三维 = this;
		f创建命令列表(m渲染控制->m命令列表);
		m渲染控制->m根签名 = m默认根签名;
		m渲染目标管理->m帧索引 = &m渲染控制->m帧索引;
		m深度模板管理->m帧索引 = &m渲染控制->m帧索引;
		m渲染控制->f初始化围栏(m设备.Get());
	}
	return *m渲染控制;
}
C渲染状态 &C三维::fg渲染状态() {
	if (m渲染状态 == nullptr) {
		m渲染状态 = std::make_unique<C渲染状态>();
	}
	return *m渲染状态;
}
C创建设备 &C三维::fg创建设备() {
	if (m创建设备 == nullptr) {
		m创建设备 = std::make_unique<C创建设备>();
	}
	return *m创建设备;
}
C缓冲工厂 &C三维::fg缓冲工厂() {
	if (m缓冲工厂 == nullptr) {
		m缓冲工厂 = std::make_unique<C缓冲工厂>();
		m缓冲工厂->f初始化(m设备.Get());
	}
	return *m缓冲工厂;
}
C纹理工厂 &C三维::fg纹理工厂() {
	if (m纹理工厂 == nullptr) {
		m纹理工厂 = std::make_unique<C纹理工厂>();
		m纹理工厂->m缓冲工厂 = &fg缓冲工厂();
		m纹理工厂->m设备 = m设备;
		m纹理工厂->m渲染控制 = &fg渲染控制();
		m纹理工厂->f初始化();
	}
	return *m纹理工厂;
}
C渲染目标管理 &C三维::fg渲染目标管理() {
	return *m渲染目标管理;
}
C深度模板管理 &C三维::fg深度模板管理() {
	return *m深度模板管理;
}
ID3D12RootSignature *C三维::fg默认根签名() {
	return m默认根签名.Get();
}
ComPtr<ID3D12Device> C三维::fg设备() const {
	return m设备;
}
//==============================================================================
// 创建设备
//==============================================================================
ComPtr<IDXGIFactory5> C创建设备::fg工厂() {
	if (m工厂 == nullptr) {
		HRESULT hr = CreateDXGIFactory1(IID_PPV_ARGS(&m工厂));
		if (FAILED(hr)) {
			throw;
		}
	}
	return m工厂;
}
bool C创建设备::f开启调试层() {
	ComPtr<ID3D12Debug> v调试;
	if (SUCCEEDED(D3D12GetDebugInterface(IID_PPV_ARGS(&v调试)))) {
		v调试->EnableDebugLayer();
		return true;
	}
	return false;
}
bool C创建设备::f检查撕裂() {
	fg工厂();
	BOOL v撕裂 = FALSE;
	HRESULT hr = m工厂->CheckFeatureSupport(DXGI_FEATURE_PRESENT_ALLOW_TEARING, &v撕裂, sizeof(v撕裂));
	return SUCCEEDED(hr) && v撕裂;
}
HRESULT C创建设备::f取显卡_首选(IDXGIAdapter3 **a显卡) {
	HRESULT hr = S_OK;
	fg工厂();
	ComPtr<IDXGIAdapter1> v显卡, v目标显卡;
	*a显卡 = nullptr;
	for (UINT i = 0; DXGI_ERROR_NOT_FOUND != m工厂->EnumAdapters1(i, &v显卡); ++i) {
		DXGI_ADAPTER_DESC1 v描述;
		v显卡->GetDesc1(&v描述);
		if (v描述.Flags & DXGI_ADAPTER_FLAG_SOFTWARE) {
			continue;
		}
		hr = D3D12CreateDevice(v显卡.Get(), c最低功能级别, __uuidof(ID3D12Device), nullptr);
		if (FAILED(hr)) {
			continue;
		} else {
			v目标显卡 = v显卡;
			break;
		}
	}
	if (v目标显卡) {
		ComPtr<IDXGIAdapter3> v输出;
		v目标显卡.As(&v输出);
		*a显卡 = v输出.Detach();
		return S_OK;
	} else {
		return hr;
	}
}
HRESULT C创建设备::f取显卡_性能(IDXGIAdapter3 **a显卡) {
	HRESULT hr = S_OK;
	fg工厂();
	ComPtr<IDXGIAdapter1> v显卡, v目标显卡;
	*a显卡 = nullptr;
	SIZE_T v显存 = 0;
	for (UINT i = 0; DXGI_ERROR_NOT_FOUND != m工厂->EnumAdapters1(i, &v显卡); ++i) {
		DXGI_ADAPTER_DESC1 v描述;
		v显卡->GetDesc1(&v描述);
		if (v描述.Flags & DXGI_ADAPTER_FLAG_SOFTWARE) {
			continue;
		}
		hr = D3D12CreateDevice(v显卡.Get(), c最低功能级别, __uuidof(ID3D12Device), nullptr);
		if (FAILED(hr)) {
			continue;
		}
		if (v描述.DedicatedVideoMemory > v显存) {
			v目标显卡 = v显卡;
			v显存 = v描述.DedicatedVideoMemory;
		}
	}
	if (v目标显卡) {
		ComPtr<IDXGIAdapter3> v输出;
		v目标显卡.As(&v输出);
		*a显卡 = v输出.Detach();
		return S_OK;
	} else {
		return hr;
	}
}
HRESULT C创建设备::f取软件适配器(IDXGIAdapter3 **a显卡) {
	return m工厂->EnumWarpAdapter(IID_PPV_ARGS(a显卡));
}
HRESULT C创建设备::f创建设备(IDXGIAdapter3 *a显卡, ID3D12Device **a设备) {
	HRESULT hr = D3D12EnableExperimentalFeatures(1, &D3D12ExperimentalShaderModels, nullptr, nullptr);
	if (FAILED(hr)) {
		return hr;
	}
	hr = D3D12CreateDevice(a显卡, c最低功能级别, IID_PPV_ARGS(a设备));
	return hr;
}
//==============================================================================
// 渲染控制
//==============================================================================
C渲染控制::~C渲染控制() {
	f销毁();
}
void C渲染控制::f销毁() {
	CloseHandle(m围栏事件);
}
HRESULT C渲染控制::f初始化围栏(ID3D12Device *a设备) {
	HRESULT hr = a设备->CreateFence(0, D3D12_FENCE_FLAG_NONE, IID_PPV_ARGS(&m围栏));
	m围栏值 = 1;
	m围栏事件 = CreateEventW(nullptr, FALSE, FALSE, nullptr);
	if (m围栏事件 == nullptr) {
		hr = HRESULT_FROM_WIN32(GetLastError());
		if (FAILED(hr)) {
			return hr;
		}
	}
	f等待完成帧();
	return S_OK;
}
void C渲染控制::f开始() {
	m命令列表->SetGraphicsRootSignature(m根签名.Get());
	m命令列表->RSSetViewports(1, &m三维->m默认视口);
	m命令列表->RSSetScissorRects(1, &m三维->m默认裁剪矩形);
	const D3D12_RESOURCE_BARRIER v栅栏 = fc渲染视图栅栏变换(D3D12_RESOURCE_STATE_PRESENT, D3D12_RESOURCE_STATE_RENDER_TARGET);
	m命令列表->ResourceBarrier(1, &v栅栏);
	m三维->m渲染目标管理->f更新视图();
	m三维->m深度模板管理->f更新视图();
	m命令列表->OMSetRenderTargets(1, &m三维->m渲染目标管理->fg当前视图(), FALSE, &m三维->m深度模板管理->fg当前视图());
}
void C渲染控制::f结束() {
	const D3D12_RESOURCE_BARRIER v栅栏 = fc渲染视图栅栏变换(D3D12_RESOURCE_STATE_RENDER_TARGET, D3D12_RESOURCE_STATE_PRESENT);
	m命令列表->ResourceBarrier(1, &v栅栏);
}
void C渲染控制::f清屏() {
	m命令列表->ClearRenderTargetView(m三维->m渲染目标管理->fg当前视图(), m清屏颜色.fg数据(), 0, nullptr);
	constexpr D3D12_CLEAR_FLAGS c清除深度模板标志 = D3D12_CLEAR_FLAG_DEPTH | D3D12_CLEAR_FLAG_STENCIL;
	m命令列表->ClearDepthStencilView(m三维->m深度模板管理->fg当前视图(), c清除深度模板标志, m清屏深度, m清屏模板, 0, nullptr);
}
void C渲染控制::f显示() {
	const UINT v标志 = (m三维->m标志[C三维::e撕裂] && m三维->fi窗口()) ? DXGI_PRESENT_ALLOW_TEARING : 0;
	m三维->m交换链->Present(0, v标志);
	f等待完成帧();
	f更新帧索引();
	ma更新资源.clear();
}
void C渲染控制::f重置命令() {
	m三维->m命令分配器->Reset();
	m命令列表->Reset(m三维->m命令分配器.Get(), m图形管线.Get());
}
void C渲染控制::f执行命令() {
	m命令列表->Close();
	ID3D12CommandList* v命令列表[] = {m命令列表.Get()};
	m三维->m命令队列->ExecuteCommandLists(_countof(v命令列表), v命令列表);
}
void C渲染控制::f执行命令并等待() {
	f执行命令();
	f等待完成帧();
	ma更新资源.clear();
}
void C渲染控制::f执行命令并显示() {
	f执行命令();
	f显示();
}
void C渲染控制::f绘制(UINT a顶点数, UINT a开始) {
	m命令列表->DrawInstanced(a顶点数, 1, a开始, 0);
}
void C渲染控制::f绘制索引(UINT a索引数, UINT a开始索引, INT a开始顶点) {
	m命令列表->DrawIndexedInstanced(a索引数, 1, a开始索引, a开始顶点, 0);
}
void C渲染控制::f等待完成帧() {
	const UINT64 v围栏值 = m围栏值;
	m三维->m命令队列->Signal(m围栏.Get(), v围栏值);
	m围栏值++;
	// 等到前一帧完成。
	if (m围栏->GetCompletedValue() < v围栏值) {
		m围栏->SetEventOnCompletion(v围栏值, m围栏事件);
		WaitForSingleObject(m围栏事件, INFINITE);
	}
}
UINT C渲染控制::f更新帧索引() {
	m帧索引 = m三维->m交换链->GetCurrentBackBufferIndex();
	return m帧索引;
}
UINT C渲染控制::fg帧索引() const {
	return m帧索引;
}
void C渲染控制::f更新资源(ID3D12Resource *a目标, ID3D12Resource *a源) {
	m命令列表->CopyResource(a目标, a源);
	ma更新资源.emplace_back(a源);
}
void C渲染控制::f更新纹理(ID3D12Resource *a目标, ID3D12Resource *a源, D3D12_SUBRESOURCE_DATA &a资源描述) {
	UpdateSubresources(m命令列表.Get(), a目标, a源, 0, 0, 1, &a资源描述);
	const S资源栅栏 v资源栅栏 = S资源栅栏::fc变换(a目标, D3D12_RESOURCE_STATE_COPY_DEST, D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE);
	m命令列表->ResourceBarrier(1, &v资源栅栏);
	ma更新资源.emplace_back(a源);
}
void C渲染控制::fs清屏颜色(const 数学::S颜色 &a) {
	m清屏颜色 = a;
}
void C渲染控制::fs清屏深度(float a) {
	m清屏深度 = a;
}
void C渲染控制::fs清屏模板(UINT8 a) {
	m清屏模板 = a;
}
void C渲染控制::fs模板参考值(UINT a) {
	m命令列表->OMSetStencilRef(a);
}
void C渲染控制::fs图形管线(ID3D12PipelineState *a) {
	m图形管线 = a;
	m命令列表->SetPipelineState(a);
}
void C渲染控制::fs根签名(ID3D12RootSignature *a) {
	m根签名 = a;
	m命令列表->SetGraphicsRootSignature(a);
}
void C渲染控制::fs图元拓扑(E图元拓扑 a) {
	m命令列表->IASetPrimitiveTopology((D3D_PRIMITIVE_TOPOLOGY)a);
}
void C渲染控制::fs顶点缓冲(const D3D12_VERTEX_BUFFER_VIEW &a) {
	m命令列表->IASetVertexBuffers(0, 1, &a);
}
void C渲染控制::fs索引缓冲(const D3D12_INDEX_BUFFER_VIEW &a) {
	m命令列表->IASetIndexBuffer(&a);
}
void C渲染控制::fs常量缓冲(UINT a槽, const D3D12_GPU_VIRTUAL_ADDRESS &a位置) {
	m命令列表->SetGraphicsRootConstantBufferView(a槽, a位置);
}
void C渲染控制::fs纹理(UINT a槽, const D3D12_GPU_VIRTUAL_ADDRESS &a位置) {
	m命令列表->SetGraphicsRootShaderResourceView(a槽, a位置);
}
void C渲染控制::fs描述符表(UINT a槽, ID3D12DescriptorHeap *a堆) {
	m命令列表->SetDescriptorHeaps(1, &a堆);
	m命令列表->SetGraphicsRootDescriptorTable(a槽, a堆->GetGPUDescriptorHandleForHeapStart());
}
D3D12_RESOURCE_BARRIER C渲染控制::fc渲染视图栅栏变换(D3D12_RESOURCE_STATES a前, D3D12_RESOURCE_STATES a后) {
	return S资源栅栏::fc变换(m三维->m渲染目标管理->fg当前资源(), a前, a后);
}
//==============================================================================
// 渲染目标
//==============================================================================
const D3D12_CPU_DESCRIPTOR_HANDLE &C渲染目标管理::f更新视图() {
	m当前渲染目标视图 = m渲染目标堆->GetCPUDescriptorHandleForHeapStart();
	m当前渲染目标视图.ptr += *m帧索引 * m渲染目标视图大小;
	return m当前渲染目标视图;
}
const D3D12_CPU_DESCRIPTOR_HANDLE &C渲染目标管理::fg当前视图() const {
	return m当前渲染目标视图;
}
ID3D12Resource *C渲染目标管理::fg当前资源() const {
	return m渲染目标[*m帧索引].Get();
}
const D3D12_CPU_DESCRIPTOR_HANDLE &C深度模板管理::f更新视图() {
	m当前深度模板视图 = m深度模板堆->GetCPUDescriptorHandleForHeapStart();
	m当前深度模板视图.ptr += *m帧索引 * m深度模板视图大小;
	return m当前深度模板视图;

}
const D3D12_CPU_DESCRIPTOR_HANDLE &C深度模板管理::fg当前视图() const {
	return m当前深度模板视图;

}
ID3D12Resource *C深度模板管理::fg当前资源() const {
	return m深度模板[*m帧索引].Get();
}
//==============================================================================
// 渲染状态
//==============================================================================
C渲染状态::C渲染状态() {
	//光栅化	================================================================
	//线框渲染
	m光栅化.m线框渲染 = c默认光栅化;
	m光栅化.m线框渲染.CullMode = D3D12_CULL_MODE_BACK;
	m光栅化.m线框渲染.FillMode = D3D12_FILL_MODE_WIREFRAME;
	m光栅化.m线框渲染.FrontCounterClockwise = false;
	m光栅化.m线框渲染.DepthClipEnable = true;
	m光栅化.m线框渲染.MultisampleEnable = true;
	//显示隐藏面
	m光栅化.m显示隐藏面 = c默认光栅化;
	m光栅化.m显示隐藏面.CullMode = D3D12_CULL_MODE_NONE;
	m光栅化.m显示隐藏面.FillMode = D3D12_FILL_MODE_SOLID;
	//设置逆时针为正面
	m光栅化.m反面渲染 = c默认光栅化;
	m光栅化.m反面渲染.FrontCounterClockwise = true;

	//混合	====================================================================
	//开启透明
	m混合.m开启透明 = c默认混合;
	m混合.m开启透明.RenderTarget[0].BlendEnable = true;
	m混合.m开启透明.RenderTarget[0].SrcBlend = D3D12_BLEND_SRC_ALPHA;
	m混合.m开启透明.RenderTarget[0].DestBlend = D3D12_BLEND_INV_SRC_ALPHA;
	m混合.m开启透明.RenderTarget[0].BlendOp = D3D12_BLEND_OP_ADD;
	m混合.m开启透明.RenderTarget[0].SrcBlendAlpha = D3D12_BLEND_SRC_ALPHA;
	m混合.m开启透明.RenderTarget[0].DestBlendAlpha = D3D12_BLEND_DEST_ALPHA;
	m混合.m开启透明.RenderTarget[0].BlendOpAlpha = D3D12_BLEND_OP_MAX;
	m混合.m开启透明.RenderTarget[0].RenderTargetWriteMask = D3D12_COLOR_WRITE_ENABLE_ALL;
	//颜色叠加
	m混合.m颜色叠加 = m混合.m开启透明;
	m混合.m颜色叠加.RenderTarget[0].DestBlend = D3D12_BLEND_DEST_ALPHA;
	m混合.m颜色叠加.RenderTarget[0].SrcBlendAlpha = D3D12_BLEND_SRC_ALPHA;
	m混合.m颜色叠加.RenderTarget[0].DestBlendAlpha = D3D12_BLEND_DEST_ALPHA;
	//禁止写颜色
	m混合.m禁止写颜色 = c默认混合;
	m混合.m禁止写颜色.RenderTarget[0].BlendEnable = false;
	m混合.m禁止写颜色.RenderTarget[0].RenderTargetWriteMask = 0;

	//深度模板	================================================================
	//正常深度
	m深度模板.m正常深度l = c默认深度模板;
	m深度模板.m正常深度l.DepthEnable = true;
	m深度模板.m正常深度l.DepthWriteMask = D3D12_DEPTH_WRITE_MASK_ALL;
	m深度模板.m正常深度l.DepthFunc = D3D12_COMPARISON_FUNC_LESS_EQUAL;
	m深度模板.m正常深度l.StencilEnable = false;
	m深度模板.m正常深度r = m深度模板.m正常深度l;
	m深度模板.m正常深度r.DepthFunc = D3D12_COMPARISON_FUNC_GREATER_EQUAL;
	m深度模板.m总是覆盖 = m深度模板.m正常深度l;
	m深度模板.m总是覆盖.DepthFunc = D3D12_COMPARISON_FUNC_ALWAYS;
	//模板标记
	m深度模板.m模板标记 = c默认深度模板;
	m深度模板.m模板标记.DepthEnable = false;
	m深度模板.m模板标记.StencilEnable = true;
	m深度模板.m模板标记.FrontFace.StencilFailOp = D3D12_STENCIL_OP_KEEP;
	m深度模板.m模板标记.FrontFace.StencilDepthFailOp = D3D12_STENCIL_OP_KEEP;
	m深度模板.m模板标记.FrontFace.StencilPassOp = D3D12_STENCIL_OP_REPLACE;
	m深度模板.m模板标记.FrontFace.StencilFunc = D3D12_COMPARISON_FUNC_ALWAYS;
	m深度模板.m模板标记.BackFace = m深度模板.m模板标记.FrontFace;
	//模板比较
	m深度模板.m模板比较 = c默认深度模板;
	m深度模板.m模板比较.StencilEnable = true;
	m深度模板.m模板比较.FrontFace.StencilFunc = D3D12_COMPARISON_FUNC_EQUAL;
	m深度模板.m模板比较.BackFace.StencilFunc = D3D12_COMPARISON_FUNC_EQUAL;

	//采样器	================================================================
	//纹理
	m采样器.m纹理.Filter = D3D12_FILTER_MIN_MAG_MIP_LINEAR;
	m采样器.m纹理.AddressU = D3D12_TEXTURE_ADDRESS_MODE_WRAP;
	m采样器.m纹理.AddressV = D3D12_TEXTURE_ADDRESS_MODE_WRAP;
	m采样器.m纹理.AddressW = D3D12_TEXTURE_ADDRESS_MODE_WRAP;
	m采样器.m纹理.ComparisonFunc = D3D12_COMPARISON_FUNC_NEVER;
	m采样器.m纹理.BorderColor[0] = 0;
	m采样器.m纹理.BorderColor[1] = 0;
	m采样器.m纹理.BorderColor[2] = 0;
	m采样器.m纹理.BorderColor[3] = 0;
	m采样器.m纹理.MinLOD = 0;
	m采样器.m纹理.MaxLOD = D3D12_FLOAT32_MAX;
	m采样器.m纹理.MipLODBias = 0;
	m采样器.m纹理.MaxAnisotropy = 16;
	//图案
	m采样器.m图案 = m采样器.m纹理;
	m采样器.m图案.AddressU = D3D12_TEXTURE_ADDRESS_MODE_CLAMP;
	m采样器.m图案.AddressV = D3D12_TEXTURE_ADDRESS_MODE_CLAMP;
	m采样器.m图案.AddressW = D3D12_TEXTURE_ADDRESS_MODE_CLAMP;
	//各向异性过滤
	m采样器.m各向异性过滤 = m采样器.m纹理;
	m采样器.m各向异性过滤.Filter = D3D12_FILTER_ANISOTROPIC;
}
C渲染状态::~C渲染状态() {
}
D3D12_SAMPLER_DESC C渲染状态::ft采样器(const D3D12_STATIC_SAMPLER_DESC &a) {
	return {a.Filter, a.AddressU, a.AddressV, a.AddressW, a.MipLODBias, a.MaxAnisotropy, a.ComparisonFunc, {0, 0, 0, 0}, a.MinLOD, a.MaxLOD};
}
D3D12_STATIC_SAMPLER_DESC C渲染状态::ft静态采样器(const D3D12_SAMPLER_DESC &a, UINT a寄存器, UINT a空间, D3D12_SHADER_VISIBILITY a可视性) {
	return {a.Filter, a.AddressU, a.AddressV, a.AddressW, a.MipLODBias, a.MaxAnisotropy, a.ComparisonFunc, D3D12_STATIC_BORDER_COLOR_TRANSPARENT_BLACK, a.MinLOD, a.MaxLOD, a寄存器, a空间, a可视性};
}
//==============================================================================
// 顶点格式
//==============================================================================
void C顶点格式::f清空() {
	m数组.clear();
	m类型累计.clear();
	m字节累计 = 0;
}
void C顶点格式::f添加(E类型 a类型, int a大小) {
	static const char*const v语义[] = {
		"POSITION",
		"NORMAL",
		"BINORMAL",
		"COLOR",
		"TEXCOORD",
		"PSIZE",
		"TANGENT",
		"ALPHA"
	};
	f添加(v语义[a类型], a大小);
}
void C顶点格式::f添加(const char *a语义, int a大小) {
	static const DXGI_FORMAT v格式[] = {
		DXGI_FORMAT_R32_FLOAT,
		DXGI_FORMAT_R32G32_FLOAT,
		DXGI_FORMAT_R32G32B32_FLOAT,
		DXGI_FORMAT_R32G32B32A32_FLOAT
	};
	D3D12_INPUT_ELEMENT_DESC v;
	v.AlignedByteOffset = m字节累计;
	v.Format = v格式[a大小 - 1];
	m字节累计 += a大小 * 4;
	v.SemanticName = a语义;
	auto &v语义索引 = m类型累计[a语义];
	v.SemanticIndex = v语义索引;
	v语义索引 += 1;
	v.InputSlot = 0;
	v.InputSlotClass = D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA;
	v.InstanceDataStepRate = 0;
	m数组.push_back(v);
}
D3D12_INPUT_LAYOUT_DESC C顶点格式::fg输入层描述() const {
	return {m数组.data(), (UINT)m数组.size()};
}
//==============================================================================
// 根签名
//==============================================================================
void C根签名参数::f清空() {
	ma索引.clear();
	ma参数.clear();
	ma采样器.clear();
	ma描述范围.clear();
	ma描述符表.clear();
	mi连续添加 = false;
}
C根签名参数 &C根签名参数::f添加描述符(E类型 a类型, UINT a寄存器, UINT a空间, E着色器 a可见性) {
	f实现_添加索引(E根参数类型::e描述符);
	D3D12_ROOT_PARAMETER v参数 = {};
	v参数.ParameterType = f计算根参数类型(a类型);
	v参数.Descriptor.ShaderRegister = a寄存器;
	v参数.Descriptor.RegisterSpace = a空间;
	v参数.ShaderVisibility = f计算可见性(a可见性);
	ma参数.push_back(v参数);
	return *this;
}
C根签名参数 &C根签名参数::f添加采样器(const D3D12_SAMPLER_DESC &a采样器, UINT a寄存器, UINT a空间, E着色器 a可见性) {
	ma采样器.push_back(C渲染状态::ft静态采样器(a采样器, a寄存器, a空间, f计算可见性(a可见性)));
	return *this;
}
C根签名参数 &C根签名参数::f添加范围(E类型 a类型, UINT a数量, UINT a开始寄存器, UINT a寄存器空间, UINT a偏移, E着色器 a可见性) {
	assert(mi连续添加 == false);	//连续添加范围时不能添加单个范围
	assert(a数量 > 0);
	f实现_添加索引(E根参数类型::e描述符表);
	S描述符表 v描述表;
	v描述表.m开始位置 = ma描述范围.size();
	v描述表.m数量 = 1;
	v描述表.m可见性 = f计算可见性(a可见性);
	ma描述符表.push_back(v描述表);
	f实现_添加范围(a类型, a数量, a开始寄存器, a寄存器空间, a偏移);
	return *this;
}
C根签名参数 &C根签名参数::f连续添加范围(E类型 a类型, UINT a数量, UINT a开始寄存器, UINT a寄存器空间, UINT a偏移) {
	assert(mi连续添加 == true);
	f实现_添加范围(a类型, a数量, a开始寄存器, a寄存器空间, a偏移);
	++m连续添加.m数量;
	return *this;
}
C根签名参数 &C根签名参数::f连续添加范围开始(E着色器 a可见性) {
	assert(mi连续添加 == false);
	f实现_添加索引(E根参数类型::e描述符表);
	m连续添加.m开始位置 = ma描述范围.size();
	m连续添加.m数量 = 0;
	m连续添加.m可见性 = f计算可见性(a可见性);
	mi连续添加 = true;
	return *this;
}
C根签名参数 &C根签名参数::f连续添加范围结束() {
	assert(mi连续添加 == true);
	ma描述符表.push_back(m连续添加);
	mi连续添加 = false;
	return *this;
}
void C根签名参数::fs标志(E根签名标志 a) {
	fs标志((D3D12_ROOT_SIGNATURE_FLAGS)a);
}
void C根签名参数::fs标志(D3D12_ROOT_SIGNATURE_FLAGS a) {

}
void C根签名参数::f实现_添加范围(E类型 a类型, UINT a数量, UINT a开始寄存器, UINT a寄存器空间, UINT a偏移) {
	D3D12_DESCRIPTOR_RANGE v范围;
	v范围.RangeType = f计算描述范围类型(a类型);
	v范围.NumDescriptors = a数量;
	v范围.BaseShaderRegister = a开始寄存器;
	v范围.RegisterSpace = a寄存器空间;
	v范围.OffsetInDescriptorsFromTableStart = a偏移;
	ma描述范围.push_back(v范围);
}
void C根签名参数::f实现_添加索引(E根参数类型 a类型) {
	S根参数索引 v索引 = {};
	v索引.m类型 = a类型;
	switch (a类型) {
	case E根参数类型::e描述符表:
		v索引.m位置 = ma描述符表.size();
		break;
	case E根参数类型::e常量:
	case E根参数类型::e描述符:
		v索引.m位置 = ma参数.size();
		break;
	default:
		throw;
	}
	ma索引.push_back(v索引);
}
D3D12_SHADER_VISIBILITY C根签名参数::f计算可见性(E着色器 a) {
	switch (a) {
	case E着色器::e顶点着色器:
		return D3D12_SHADER_VISIBILITY_VERTEX;
	case E着色器::e外壳着色器:
		return D3D12_SHADER_VISIBILITY_HULL;
	case E着色器::e域着色器:
		return D3D12_SHADER_VISIBILITY_DOMAIN;
	case E着色器::e几何着色器:
		return D3D12_SHADER_VISIBILITY_GEOMETRY;
	case E着色器::e像素着色器:
		return D3D12_SHADER_VISIBILITY_PIXEL;
	default:
		return D3D12_SHADER_VISIBILITY_ALL;
	}
}
D3D12_ROOT_PARAMETER_TYPE C根签名参数::f计算根参数类型(E类型 a) {
	switch (a) {
	case E类型::e着色器资源视图:
		return D3D12_ROOT_PARAMETER_TYPE_SRV;
	case E类型::e常量缓冲视图:
		return D3D12_ROOT_PARAMETER_TYPE_CBV;
	case E类型::e无序访问视图:
		return D3D12_ROOT_PARAMETER_TYPE_UAV;
	case E类型::e根常量:
		return D3D12_ROOT_PARAMETER_TYPE_32BIT_CONSTANTS;
	default:
		throw;
	}
}
D3D12_DESCRIPTOR_RANGE_TYPE C根签名参数::f计算描述范围类型(E类型 a) {
	switch (a) {
	case E类型::e着色器资源视图:
		return D3D12_DESCRIPTOR_RANGE_TYPE_SRV;
	case E类型::e常量缓冲视图:
		return D3D12_DESCRIPTOR_RANGE_TYPE_CBV;
	case E类型::e无序访问视图:
		return D3D12_DESCRIPTOR_RANGE_TYPE_UAV;
	case E类型::e采样器:
		return D3D12_DESCRIPTOR_RANGE_TYPE_SAMPLER;
	default:
		throw;
	}
}
//==============================================================================
// 修改
//==============================================================================
C自动映射::C自动映射(ID3D12Resource *a):
	m资源(a) {
	HRESULT hr = m资源->Map(0, nullptr, (void**)&m数据);
	if (FAILED(hr)) {
		throw;
	}
}
C自动映射::~C自动映射() {
	m资源->Unmap(0, nullptr);
}
void C自动映射::f映射并复制(ID3D12Resource *a资源, const void *a数据, size_t a大小) {
	void *v数据;
	HRESULT hr = a资源->Map(0, nullptr, &v数据);
	if (FAILED(hr)) {
		throw;
	}
	memcpy(v数据, a数据, a大小);
	a资源->Unmap(0, nullptr);
}
void C自动映射::f复制(const void *a数据, size_t a大小) {
	memcpy(m数据, a数据, a大小);
}
//==============================================================================
// 资源工厂
//==============================================================================
DXGI_FORMAT C缓冲工厂::f计算索引格式(UINT a类型大小) {
	switch (a类型大小) {
	case 2:
		return DXGI_FORMAT_R16_UINT;
	case 4:
		return DXGI_FORMAT_R32_UINT;
	default:
		return DXGI_FORMAT_UNKNOWN;
	}
}
void C缓冲工厂::f初始化(ID3D12Device *a设备) {
	m设备 = a设备;
}
HRESULT C缓冲工厂::f创建上传资源(ComPtr<ID3D12Resource> &a, const void *a数据, UINT a数据大小) {
	const D3D12_HEAP_PROPERTIES v堆属性 = {D3D12_HEAP_TYPE_UPLOAD, D3D12_CPU_PAGE_PROPERTY_UNKNOWN, D3D12_MEMORY_POOL_UNKNOWN, 1, 1};
	const D3D12_RESOURCE_DESC v资源描述 = S资源描述::fc缓存(a数据大小);
	HRESULT hr = m设备->CreateCommittedResource(&v堆属性, D3D12_HEAP_FLAG_NONE, &v资源描述, D3D12_RESOURCE_STATE_GENERIC_READ, nullptr, IID_PPV_ARGS(&a));
	if (FAILED(hr)) {
		return hr;
	}
	a->SetName(L"上传");
	if (a数据) {
		C自动映射::f映射并复制(a.Get(), a数据, a数据大小);
	}
	return S_OK;
}
HRESULT C缓冲工厂::f创建顶点(tp顶点 &a, const void *a数据, UINT a类型大小, UINT a数据大小) {
	tp顶点 v = std::make_shared<C顶点缓冲>();
	HRESULT hr = f创建上传资源(v->m资源, a数据, a数据大小);
	if (FAILED(hr)) {
		return hr;
	}
	v->m资源->SetName(L"顶点");
	//顶点缓存视图
	v->m视图.BufferLocation = v->m资源->GetGPUVirtualAddress();
	v->m视图.StrideInBytes = a类型大小;
	v->m视图.SizeInBytes = a数据大小;
	//结束
	a = std::move(v);
	return S_OK;
}
HRESULT C缓冲工厂::f创建索引(tp索引 &a, const void *a数据, UINT a类型大小, UINT a数据大小) {
	//检查参数
	const DXGI_FORMAT v索引格式 = f计算索引格式(a类型大小);
	if (v索引格式 == DXGI_FORMAT_UNKNOWN) {
		return E_INVALIDARG;
	}
	//资源
	tp索引 v = std::make_shared<C索引缓冲>();
	HRESULT hr = f创建上传资源(v->m资源, a数据, a数据大小);
	if (FAILED(hr)) {
		return hr;
	}
	v->m资源->SetName(L"索引");
	//顶点缓存视图
	v->m视图.BufferLocation = v->m资源->GetGPUVirtualAddress();
	v->m视图.SizeInBytes = a数据大小;
	v->m视图.Format = v索引格式;
	//结束
	a = std::move(v);
	return S_OK;
}
HRESULT C缓冲工厂::f创建常量(tp常量 &a, const void *a数据, UINT a类型大小, UINT a数据大小) {
	//堆描述符
	D3D12_DESCRIPTOR_HEAP_DESC v描述符堆参数 = {};
	v描述符堆参数.NumDescriptors = 1;
	v描述符堆参数.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE;
	v描述符堆参数.Type = D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV;
	tp常量 v = std::make_shared<C常量缓冲>();
	HRESULT hr = m设备->CreateDescriptorHeap(&v描述符堆参数, IID_PPV_ARGS(&v->m描述符堆));
	if (FAILED(hr)) {
		return hr;
	}
	//资源
	const S堆属性 v堆属性 = S堆属性::fc类型(D3D12_HEAP_TYPE_UPLOAD);
	const UINT v数据大小 = (a数据大小 + 255) & ~255;	// 256字节对齐
	const D3D12_RESOURCE_DESC v资源描述 = S资源描述::fc缓存(v数据大小);
	hr = m设备->CreateCommittedResource(&v堆属性, D3D12_HEAP_FLAG_NONE, &v资源描述, D3D12_RESOURCE_STATE_GENERIC_READ, nullptr, IID_PPV_ARGS(&v->m资源));
	if (FAILED(hr)) {
		return hr;
	}
	v->m资源->SetName(L"常量");
	//视图
	D3D12_CONSTANT_BUFFER_VIEW_DESC v常量缓冲视图参数 = {};
	v常量缓冲视图参数.BufferLocation = v->m资源->GetGPUVirtualAddress();
	v常量缓冲视图参数.SizeInBytes = v数据大小;
	m设备->CreateConstantBufferView(&v常量缓冲视图参数, v->m描述符堆->GetCPUDescriptorHandleForHeapStart());
	if (FAILED(hr)) {
		return hr;
	}
	C自动映射::f映射并复制(v->m资源.Get(), a数据, a数据大小);
	//结束
	a = std::move(v);
	return S_OK;
}
//==============================================================================
// 纹理工厂
//==============================================================================
C纹理工厂::~C纹理工厂() {}
HRESULT C纹理工厂::f初始化() {
	m工厂 = std::make_unique<纹理::C图像工厂>();
	return m工厂->f初始化();
}
HRESULT C纹理工厂::f从文件创建纹理(tp纹理 &a输出, const wchar_t *a文件) {
	std::unique_ptr<纹理::C只读纹理> v纹理 = m工厂->f一键读取(a文件);
	if (v纹理 == nullptr) {
		return E_FAIL;
	}
	return f从纹理对象创建纹理(a输出, *v纹理);
}
HRESULT C纹理工厂::f从纹理对象创建纹理(tp纹理 &a输出, const 纹理::I纹理 &a纹理) {
	tp纹理 v = std::make_shared<C纹理资源>();
	HRESULT hr = f从纹理对象创建纹理资源(v->m资源, a纹理);
	if (FAILED(hr)) {
		return hr;
	}
	hr = f从纹理资源创建纹理视图(v->m描述符堆, v->m资源, a纹理.fg格式());
	if (FAILED(hr)) {
		return hr;
	}
	//结束
	a输出 = std::move(v);
	return S_OK;
}
HRESULT C纹理工厂::f从内存创建纹理资源(tp资源 &a输出, const void *a数据, DXGI_FORMAT a格式, UINT a宽, UINT a高, UINT a行距, UINT a大小) {
	//创建资源
	D3D12_RESOURCE_DESC v纹理描述 = {};
	v纹理描述.Dimension = D3D12_RESOURCE_DIMENSION_TEXTURE2D;
	v纹理描述.Width = a宽;
	v纹理描述.Height = a高;
	v纹理描述.DepthOrArraySize = 1;
	v纹理描述.MipLevels = 1;
	v纹理描述.Format = a格式;
	v纹理描述.SampleDesc.Count = 1;
	v纹理描述.SampleDesc.Quality = 0;
	v纹理描述.Layout = D3D12_TEXTURE_LAYOUT_UNKNOWN;
	v纹理描述.Flags = D3D12_RESOURCE_FLAG_NONE;
	const S堆属性 v堆属性 = S堆属性::fc类型(D3D12_HEAP_TYPE_DEFAULT);
	HRESULT hr = m设备->CreateCommittedResource(&v堆属性, D3D12_HEAP_FLAG_NONE, &v纹理描述, D3D12_RESOURCE_STATE_COPY_DEST, nullptr, IID_PPV_ARGS(&a输出));
	if (FAILED(hr)) {
		return hr;
	}
	a输出->SetName(L"纹理");
	//复制数据
	const UINT64 v上传大小 = GetRequiredIntermediateSize(a输出.Get(), 0, 1);
	ComPtr<ID3D12Resource> v上传资源;
	hr = m缓冲工厂->f创建上传资源(v上传资源, nullptr, v上传大小);
	if (FAILED(hr)) {
		return hr;
	}
	D3D12_SUBRESOURCE_DATA v资源描述 = {};
	v资源描述.pData = a数据;
	v资源描述.RowPitch = a行距;
	v资源描述.SlicePitch = a大小;
	m渲染控制->f更新纹理(a输出.Get(), v上传资源.Get(), v资源描述);
	return S_OK;
}
HRESULT C纹理工厂::f从纹理对象创建纹理资源(tp资源 &a输出, const 纹理::I纹理 &a纹理) {
	return f从内存创建纹理资源(a输出, a纹理.fg数据(), a纹理.fg格式(), a纹理.fg宽(), a纹理.fg高(), a纹理.fg行距(), a纹理.fg图像大小());
}
HRESULT C纹理工厂::f从纹理资源创建纹理视图(tp描述符堆 &a输出, const tp资源 &a资源, DXGI_FORMAT a格式) {
	D3D12_DESCRIPTOR_HEAP_DESC v堆描述 = {};
	v堆描述.NumDescriptors = 1;
	v堆描述.Type = D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV;
	v堆描述.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE;
	HRESULT hr = m设备->CreateDescriptorHeap(&v堆描述, IID_PPV_ARGS(&a输出));
	if (FAILED(hr)) {
		return hr;
	}
	D3D12_SHADER_RESOURCE_VIEW_DESC v视图描述 = {};
	v视图描述.Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;
	v视图描述.Format = a格式;
	v视图描述.ViewDimension = D3D12_SRV_DIMENSION_TEXTURE2D;
	v视图描述.Texture2D.MipLevels = 1;
	m设备->CreateShaderResourceView(a资源.Get(), &v视图描述, a输出->GetCPUDescriptorHandleForHeapStart());
	return S_OK;
}
//==============================================================================
// 资源描述
//==============================================================================
S资源描述 S资源描述::fc缓存(UINT64 a宽) {
	S资源描述 v = {};
	v.Dimension = D3D12_RESOURCE_DIMENSION_BUFFER;
	v.Alignment = 0;
	v.Width = a宽;
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
S资源描述 S资源描述::fc纹理2(UINT64 a宽, UINT a高, DXGI_FORMAT a格式, D3D12_RESOURCE_FLAGS a标志) {
	S资源描述 v = {};
	v.Dimension = D3D12_RESOURCE_DIMENSION_TEXTURE2D;
	v.Alignment = 0;
	v.Width = a宽;
	v.Height = a高;
	v.DepthOrArraySize = 1;
	v.MipLevels = 1;
	v.Format = a格式;
	v.SampleDesc.Count = 1;
	v.SampleDesc.Quality = 0;
	v.Layout = D3D12_TEXTURE_LAYOUT_UNKNOWN;
	v.Flags = a标志;
	return v;
}
//==============================================================================
// 图形管线参数
//==============================================================================
S图形管线参数::S图形管线参数():
	D3D12_GRAPHICS_PIPELINE_STATE_DESC() {
	NumRenderTargets = 1;
	RTVFormats[0] = c交换链格式;
	SampleDesc.Count = 1;
	SampleMask = UINT_MAX;
}
void S图形管线参数::fs输入布局(const C顶点格式 &a) {
	InputLayout = a.fg输入层描述();
}
void S图形管线参数::fs根签名(ID3D12RootSignature *a) {
	pRootSignature = a;
}
void S图形管线参数::fs顶点着色器(const std::span<const std::byte> &a) {
	VS.pShaderBytecode = a.data();
	VS.BytecodeLength = a.size();
}
void S图形管线参数::fs像素着色器(const std::span<const std::byte> &a) {
	PS.pShaderBytecode = a.data();
	PS.BytecodeLength = a.size();
}
void S图形管线参数::fs几何着色器(const std::span<const std::byte> &a) {
	GS.pShaderBytecode = a.data();
	GS.BytecodeLength = a.size();
}
void S图形管线参数::fs外壳着色器(const std::span<const std::byte> &a) {
	HS.pShaderBytecode = a.data();
	HS.BytecodeLength = a.size();
}
void S图形管线参数::fs域着色器(const std::span<const std::byte> &a) {
	DS.pShaderBytecode = a.data();
	DS.BytecodeLength = a.size();
}
void S图形管线参数::fs光栅化(const D3D12_RASTERIZER_DESC &a) {
	RasterizerState = a;
}
void S图形管线参数::fs混合(const D3D12_BLEND_DESC &a) {
	BlendState = a;
}
void S图形管线参数::fs深度模板(const D3D12_DEPTH_STENCIL_DESC &a) {
	DSVFormat = c深度模板格式;
	DepthStencilState = a;
}
void S图形管线参数::f关闭深度模板() {
	DepthStencilState.DepthEnable = FALSE;
	DepthStencilState.StencilEnable = FALSE;
}
void S图形管线参数::fs图元拓扑类型(E图元拓扑类型 a) {
	PrimitiveTopologyType = (D3D12_PRIMITIVE_TOPOLOGY_TYPE)a;
}
S资源栅栏 S资源栅栏::fc变换(ID3D12Resource* a资源, D3D12_RESOURCE_STATES a前, D3D12_RESOURCE_STATES a后, UINT a子资源, D3D12_RESOURCE_BARRIER_FLAGS a标志) {
	S资源栅栏 v栅栏{};
	v栅栏.Type = D3D12_RESOURCE_BARRIER_TYPE_TRANSITION;
	v栅栏.Flags = a标志;
	v栅栏.Transition.StateBefore = a前;
	v栅栏.Transition.StateAfter = a后;
	v栅栏.Transition.pResource = a资源;
	v栅栏.Transition.Subresource = a子资源;
	return v栅栏;
}
//==============================================================================
// 计算管线参数
//==============================================================================
S计算管线参数::S计算管线参数():
	D3D12_COMPUTE_PIPELINE_STATE_DESC() {
}
void S计算管线参数::fs根签名(ID3D12RootSignature *a) {
	pRootSignature = a;
}
void S计算管线参数::fs计算着色器(const std::span<const std::byte> &a) {
	CS.pShaderBytecode = a.data();
	CS.BytecodeLength = a.size();
}
//==============================================================================
// 堆属性
//==============================================================================
S堆属性 S堆属性::fc类型(D3D12_HEAP_TYPE a类型, UINT a创建节点掩码, UINT a可见节点掩码) {
	S堆属性 v堆属性 = {};
	v堆属性.Type = a类型;
	v堆属性.CPUPageProperty = D3D12_CPU_PAGE_PROPERTY_UNKNOWN;
	v堆属性.MemoryPoolPreference = D3D12_MEMORY_POOL_UNKNOWN;
	v堆属性.CreationNodeMask = a创建节点掩码;
	v堆属性.VisibleNodeMask = a可见节点掩码;
	return v堆属性;
}
//==============================================================================
// 纹理复制区
//==============================================================================
S纹理复制区 S纹理复制区::fc脚印(ID3D12Resource *a资源, const D3D12_PLACED_SUBRESOURCE_FOOTPRINT &a脚印) {
	S纹理复制区 v = {};
	v.pResource = a资源;
	v.Type = D3D12_TEXTURE_COPY_TYPE_PLACED_FOOTPRINT;
	v.PlacedFootprint = a脚印;
	return v;
}
S纹理复制区 S纹理复制区::fc索引(ID3D12Resource *a资源, UINT a索引) {
	S纹理复制区 v = {};
	v.pResource = a资源;
	v.Type = D3D12_TEXTURE_COPY_TYPE_SUBRESOURCE_INDEX;
	v.SubresourceIndex = a索引;
	return v;
}
//==============================================================================
// 清除值
//==============================================================================
S清除值 S清除值::fc颜色(DXGI_FORMAT a格式, const 数学::S颜色 &a颜色) {
	S清除值 v = {};
	v.Format = a格式;
	v.Color[0] = a颜色.r;
	v.Color[1] = a颜色.g;
	v.Color[2] = a颜色.b;
	v.Color[3] = a颜色.a;
	return v;
}
S清除值 S清除值::fc深度模板(DXGI_FORMAT a格式, float a深度, UINT8 a模板) {
	S清除值 v = {};
	v.Format = a格式;
	v.DepthStencil.Depth = a深度;
	v.DepthStencil.Stencil = a模板;
	return v;
}
//==============================================================================
// 深度模板参数
//==============================================================================
S深度模板参数::S深度模板参数() :
	D3D12_DEPTH_STENCIL_DESC(c默认深度模板) {
}
void S深度模板参数::fs深度部分(const D3D12_DEPTH_STENCIL_DESC &a) {
	DepthEnable = a.DepthEnable;
	DepthWriteMask = a.DepthWriteMask;
	DepthFunc = a.DepthFunc;
}
void S深度模板参数::fs模板部分(const D3D12_DEPTH_STENCIL_DESC &a) {
	StencilEnable = a.StencilEnable;
	StencilReadMask = a.StencilReadMask;
	StencilWriteMask = a.StencilWriteMask;
	FrontFace = a.FrontFace;
	BackFace = a.BackFace;
}

}	//namespace cflw::图形::d3d12