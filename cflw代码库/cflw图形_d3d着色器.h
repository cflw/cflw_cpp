#pragma once
#include <memory>
#include <string>
#include <span>
#include <wrl.h>
#include <d3dcompiler.h>
#ifdef _WINDOWS
#pragma comment(lib, "d3dcompiler.lib")
#endif
namespace cflw::图形::d3d着色器 {
using Microsoft::WRL::ComPtr;
using tp着色器 = ComPtr<ID3DBlob>;
class C着色器工厂 {
public:
	void f初始化(const char *着色模型 = "5_0");
	//编译着色器
	HRESULT f编译顶点着色器(ComPtr<ID3DBlob> &, const wchar_t *文件名, const char *函数名);
	HRESULT f编译像素着色器(ComPtr<ID3DBlob> &, const wchar_t *文件名, const char *函数名);
	HRESULT f编译几何着色器(ComPtr<ID3DBlob> &, const wchar_t *文件名, const char *函数名);
	HRESULT f编译外壳着色器(ComPtr<ID3DBlob> &, const wchar_t *文件名, const char *函数名);
	HRESULT f编译域着色器(ComPtr<ID3DBlob> &, const wchar_t *文件名, const char *函数名);
	HRESULT f编译计算着色器(ComPtr<ID3DBlob> &, const wchar_t *文件名, const char *函数名);
	//静态函数
	HRESULT f编译着色器(ComPtr<ID3DBlob> &, const wchar_t *文件名, const char *入口, const char *着色模型);
	HRESULT f读取着色器(std::unique_ptr<std::byte[]> &数据, DWORD &大小, const wchar_t *文件名);
	HRESULT f读取着色器(ComPtr<ID3DBlob> &, const wchar_t *文件名);
public:
	std::string m顶点着色模型, m像素着色模型, m几何着色模型, m外壳着色模型, m域着色模型, m计算着色模型;
};
inline std::span<std::byte> fc跨度(const ComPtr<ID3DBlob> &a) {
	return {(std::byte*)a->GetBufferPointer(), (std::span<std::byte>::index_type)a->GetBufferSize()};
}
}	//namespace cflw::图形::d3d着色器
