#pragma once
#include <string>
#include <span>
#include <wrl.h>
#include <dxcapi.h>
#ifdef _WINDOWS
#pragma comment(lib, "dxcompiler.lib")
#endif
namespace cflw::ͼ��::dx��ɫ�� {
using Microsoft::WRL::ComPtr;
using tp��ɫ�� = ComPtr<IDxcBlob>;
class C��ɫ������ {
public:
	HRESULT f��ʼ��(const wchar_t *��ɫģ�� = L"6_0");
	//������ɫ��
	HRESULT f���붥����ɫ��(ComPtr<IDxcBlob> &, const wchar_t *�ļ���, const wchar_t *������);
	HRESULT f����������ɫ��(ComPtr<IDxcBlob> &, const wchar_t *�ļ���, const wchar_t *������);
	HRESULT f���뼸����ɫ��(ComPtr<IDxcBlob> &, const wchar_t *�ļ���, const wchar_t *������);
	HRESULT f���������ɫ��(ComPtr<IDxcBlob> &, const wchar_t *�ļ���, const wchar_t *������);
	HRESULT f��������ɫ��(ComPtr<IDxcBlob> &, const wchar_t *�ļ���, const wchar_t *������);
	HRESULT f���������ɫ��(ComPtr<IDxcBlob> &, const wchar_t *�ļ���, const wchar_t *������);
	//��������
	HRESULT f������ɫ��(ComPtr<IDxcBlob> &, const wchar_t *�ļ���, const wchar_t *���, const wchar_t *��ɫģ��);
	HRESULT f��ȡ��ɫ��(ComPtr<IDxcBlob> &, const wchar_t *�ļ���);
public:
	std::wstring m������ɫģ��, m������ɫģ��, m������ɫģ��, m�����ɫģ��, m����ɫģ��, m������ɫģ��;
	ComPtr<IDxcCompiler> m������;
	ComPtr<IDxcLibrary> m��;
};
inline std::span<std::byte> fc���(const ComPtr<IDxcBlob> &a) {
	return {(std::byte*)a->GetBufferPointer(), (std::span<std::byte>::index_type)a->GetBufferSize()};
}
}	//namespace cflw::ͼ��::dx��ɫ��