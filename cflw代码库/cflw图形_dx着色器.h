#pragma once
#include <string>
#include <span>
#include <wrl.h>
#include <dxcapi.h>
#ifdef _WINDOWS
#pragma comment(lib, "dxcompiler.lib")
#endif
namespace cflw::图形::dx着色器 {
using Microsoft::WRL::ComPtr;
using tp着色器 = ComPtr<IDxcBlob>;
class C着色器工厂 {
public:
	HRESULT f初始化(const wchar_t *着色模型 = L"6_0");
	//编译着色器
	HRESULT f编译顶点着色器(ComPtr<IDxcBlob> &, const wchar_t *文件名, const wchar_t *函数名);
	HRESULT f编译像素着色器(ComPtr<IDxcBlob> &, const wchar_t *文件名, const wchar_t *函数名);
	HRESULT f编译几何着色器(ComPtr<IDxcBlob> &, const wchar_t *文件名, const wchar_t *函数名);
	HRESULT f编译外壳着色器(ComPtr<IDxcBlob> &, const wchar_t *文件名, const wchar_t *函数名);
	HRESULT f编译域着色器(ComPtr<IDxcBlob> &, const wchar_t *文件名, const wchar_t *函数名);
	HRESULT f编译计算着色器(ComPtr<IDxcBlob> &, const wchar_t *文件名, const wchar_t *函数名);
	//其它函数
	HRESULT f编译着色器(ComPtr<IDxcBlob> &, const wchar_t *文件名, const wchar_t *入口, const wchar_t *着色模型);
	HRESULT f读取着色器(ComPtr<IDxcBlob> &, const wchar_t *文件名);
public:
	std::wstring m顶点着色模型, m像素着色模型, m几何着色模型, m外壳着色模型, m域着色模型, m计算着色模型;
	ComPtr<IDxcCompiler> m编译器;
	ComPtr<IDxcLibrary> m库;
};
inline std::span<std::byte> fc跨度(const ComPtr<IDxcBlob> &a) {
	return {(std::byte*)a->GetBufferPointer(), (std::span<std::byte>::index_type)a->GetBufferSize()};
}
}	//namespace cflw::图形::dx着色器