#include "cflw图形_dx着色器.h"
namespace cflw::图形::dx着色器 {
HRESULT C着色器工厂::f初始化(const wchar_t *a着色模型) {
	HRESULT hr;
	hr = DxcCreateInstance(CLSID_DxcCompiler, IID_PPV_ARGS(&m编译器));
	if (FAILED(hr)) {
		return hr;
	}
	hr = DxcCreateInstance(CLSID_DxcLibrary, IID_PPV_ARGS(&m库));
	if (FAILED(hr)) {
		return hr;
	}
	const auto f着色模型赋值 = [&](std::wstring &a字符串, const wchar_t *a着色器) {
		a字符串 = std::wstring(a着色器) + L"_" + a着色模型;
	};
	f着色模型赋值(m顶点着色模型, L"vs");
	f着色模型赋值(m像素着色模型, L"ps");
	f着色模型赋值(m几何着色模型, L"gs");
	f着色模型赋值(m外壳着色模型, L"hs");
	f着色模型赋值(m域着色模型, L"ds");
	f着色模型赋值(m计算着色模型, L"cs");
	return S_OK;
}
//编译着色器
HRESULT C着色器工厂::f编译顶点着色器(ComPtr<IDxcBlob> &a, const wchar_t *a文件名, const wchar_t *a函数名) {
	return f编译着色器(a, a文件名, a函数名, m顶点着色模型.c_str());
}
HRESULT C着色器工厂::f编译像素着色器(ComPtr<IDxcBlob> &a, const wchar_t *a文件名, const wchar_t *a函数名) {
	return f编译着色器(a, a文件名, a函数名, m像素着色模型.c_str());
}
HRESULT C着色器工厂::f编译几何着色器(ComPtr<IDxcBlob> &a, const wchar_t *a文件名, const wchar_t *a函数名) {
	return f编译着色器(a, a文件名, a函数名, m几何着色模型.c_str());
}
HRESULT C着色器工厂::f编译外壳着色器(ComPtr<IDxcBlob> &a, const wchar_t *a文件名, const wchar_t *a函数名) {
	return f编译着色器(a, a文件名, a函数名, m外壳着色模型.c_str());
}
HRESULT C着色器工厂::f编译域着色器(ComPtr<IDxcBlob> &a, const wchar_t *a文件名, const wchar_t *a函数名) {
	return f编译着色器(a, a文件名, a函数名, m域着色模型.c_str());
}
HRESULT C着色器工厂::f编译计算着色器(ComPtr<IDxcBlob> &a, const wchar_t *a文件名, const wchar_t *a函数名) {
	return f编译着色器(a, a文件名, a函数名, m计算着色模型.c_str());
}
//核心函数
HRESULT C着色器工厂::f编译着色器(ComPtr<IDxcBlob> &a输出, const wchar_t *a文件名, const wchar_t *a入口, const wchar_t *a着色模型) {
	HRESULT hr;
	ComPtr<IDxcBlobEncoding> v源;
	hr = m库->CreateBlobFromFile(a文件名, nullptr, &v源);
	if (FAILED(hr)) {
		return hr;
	}
	ComPtr<IDxcOperationResult> v结果;
	hr = m编译器->Compile(v源.Get(), a文件名, a入口, a着色模型, nullptr, 0, nullptr, 0, nullptr, &v结果);
	if (FAILED(hr)) {
		return hr;
	}
	v结果->GetStatus(&hr);
	if (FAILED(hr)) {
		ComPtr<IDxcBlobEncoding> v错误;
		v结果->GetErrorBuffer(&v错误);
		OutputDebugStringA((char*)v错误->GetBufferPointer());
		return hr;
	}
	v结果->GetResult(&a输出);
	return S_OK;
}
HRESULT C着色器工厂::f读取着色器(ComPtr<IDxcBlob> &a, const wchar_t *a文件名) {
	HRESULT hr;
	ComPtr<IDxcBlobEncoding> v源;
	hr = m库->CreateBlobFromFile(a文件名, nullptr, &v源);
	if (FAILED(hr)) {
		return hr;
	}
	v源.As(&a);
	return S_OK;
}
}