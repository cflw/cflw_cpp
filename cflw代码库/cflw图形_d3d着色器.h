#pragma once
#include <memory>
#include <string>
#include <span>
#include <wrl.h>
#include <d3dcompiler.h>
#ifdef _WINDOWS
#pragma comment(lib, "d3dcompiler.lib")
#endif
namespace cflw::ͼ��::d3d��ɫ�� {
using Microsoft::WRL::ComPtr;
using tp��ɫ�� = ComPtr<ID3DBlob>;
class C��ɫ������ {
public:
	void f��ʼ��(const char *��ɫģ�� = "5_0");
	//������ɫ��
	HRESULT f���붥����ɫ��(ComPtr<ID3DBlob> &, const wchar_t *�ļ���, const char *������);
	HRESULT f����������ɫ��(ComPtr<ID3DBlob> &, const wchar_t *�ļ���, const char *������);
	HRESULT f���뼸����ɫ��(ComPtr<ID3DBlob> &, const wchar_t *�ļ���, const char *������);
	HRESULT f���������ɫ��(ComPtr<ID3DBlob> &, const wchar_t *�ļ���, const char *������);
	HRESULT f��������ɫ��(ComPtr<ID3DBlob> &, const wchar_t *�ļ���, const char *������);
	HRESULT f���������ɫ��(ComPtr<ID3DBlob> &, const wchar_t *�ļ���, const char *������);
	//��̬����
	HRESULT f������ɫ��(ComPtr<ID3DBlob> &, const wchar_t *�ļ���, const char *���, const char *��ɫģ��);
	HRESULT f��ȡ��ɫ��(std::unique_ptr<std::byte[]> &����, DWORD &��С, const wchar_t *�ļ���);
	HRESULT f��ȡ��ɫ��(ComPtr<ID3DBlob> &, const wchar_t *�ļ���);
public:
	std::string m������ɫģ��, m������ɫģ��, m������ɫģ��, m�����ɫģ��, m����ɫģ��, m������ɫģ��;
};
inline std::span<std::byte> fc���(const ComPtr<ID3DBlob> &a) {
	return {(std::byte*)a->GetBufferPointer(), (std::span<std::byte>::index_type)a->GetBufferSize()};
}
}	//namespace cflw::ͼ��::d3d��ɫ��
