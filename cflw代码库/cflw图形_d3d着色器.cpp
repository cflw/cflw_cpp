#include "cflw图形_d3d着色器.h"
namespace cflw::图形::d3d着色器 {
void C着色器工厂::f初始化(const char *a着色模型) {
	const auto f着色模型赋值 = [&](std::string &a字符串, const char *a着色器) {
		a字符串 = std::string(a着色器) + "_" + a着色模型;
	};
	f着色模型赋值(m顶点着色模型, "vs");
	f着色模型赋值(m像素着色模型, "ps");
	f着色模型赋值(m几何着色模型, "gs");
	f着色模型赋值(m外壳着色模型, "hs");
	f着色模型赋值(m域着色模型, "ds");
	f着色模型赋值(m计算着色模型, "cs");
}
HRESULT C着色器工厂::f编译顶点着色器(ComPtr<ID3DBlob> &a, const wchar_t *a文件名, const char *a函数名) {
	return f编译着色器(a, a文件名, a函数名, m顶点着色模型.c_str());
}
HRESULT C着色器工厂::f编译像素着色器(ComPtr<ID3DBlob> &a, const wchar_t *a文件名, const char *a函数名) {
	return f编译着色器(a, a文件名, a函数名, m像素着色模型.c_str());
}
HRESULT C着色器工厂::f编译几何着色器(ComPtr<ID3DBlob> &a, const wchar_t *a文件名, const char *a函数名) {
	return f编译着色器(a, a文件名, a函数名, m几何着色模型.c_str());
}
HRESULT C着色器工厂::f编译外壳着色器(ComPtr<ID3DBlob> &a, const wchar_t *a文件名, const char *a函数名) {
	return f编译着色器(a, a文件名, a函数名, m外壳着色模型.c_str());
}
HRESULT C着色器工厂::f编译域着色器(ComPtr<ID3DBlob> &a, const wchar_t *a文件名, const char *a函数名) {
	return f编译着色器(a, a文件名, a函数名, m域着色模型.c_str());
}
HRESULT C着色器工厂::f编译计算着色器(ComPtr<ID3DBlob> &a, const wchar_t *a文件名, const char *a函数名) {
	return f编译着色器(a, a文件名, a函数名, m计算着色模型.c_str());
}
HRESULT C着色器工厂::f编译着色器(ComPtr<ID3DBlob> &a, const wchar_t *a文件名, const char *a入口, const char *a着色模型) {
	HRESULT hr = S_OK;
	DWORD v着色标志 = D3DCOMPILE_ENABLE_STRICTNESS;
#if defined( DEBUG ) || defined( _DEBUG )
	v着色标志 |= D3DCOMPILE_DEBUG;
#endif
	ComPtr<ID3DBlob> v错误;
	hr = D3DCompileFromFile(a文件名, nullptr, nullptr, a入口, a着色模型, v着色标志, 0, &a, &v错误);
	if (FAILED(hr)) {
		if (v错误 != nullptr) {
			OutputDebugStringA((char*)v错误->GetBufferPointer());
		}
		return hr;
	}
	return S_OK;
}
HRESULT C着色器工厂::f读取着色器(std::unique_ptr<std::byte[]> &a数据, DWORD &a大小, const wchar_t *a文件名) {
	HANDLE v文件 = CreateFileW(a文件名, GENERIC_READ, FILE_SHARE_READ, nullptr, OPEN_ALWAYS, 0, nullptr);
	if (v文件 == INVALID_HANDLE_VALUE) {
		return ERROR_FILE_NOT_FOUND;
	}
	a大小 = GetFileSize(v文件, nullptr);
	a数据 = std::make_unique<std::byte[]>(a大小);
	DWORD v读大小;
	ReadFile(v文件, a数据.get(), a大小, &v读大小, nullptr);
	CloseHandle(v文件);
	return S_OK;
}
HRESULT C着色器工厂::f读取着色器(ComPtr<ID3DBlob> &a, const wchar_t *a文件名) {
	ComPtr<ID3DBlob> v;
	HANDLE v文件 = CreateFileW(a文件名, GENERIC_READ, FILE_SHARE_READ, nullptr, OPEN_ALWAYS, 0, nullptr);
	if (v文件 == INVALID_HANDLE_VALUE) {
		return ERROR_FILE_NOT_FOUND;
	}
	const DWORD v大小 = GetFileSize(v文件, nullptr);
	D3DCreateBlob(v大小, &v);
	ReadFile(v文件, v->GetBufferPointer(), v大小, nullptr, nullptr);
	CloseHandle(v文件);
	a = std::move(v);
	return S_OK;
}
}