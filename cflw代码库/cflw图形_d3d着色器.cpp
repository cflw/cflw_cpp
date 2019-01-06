#include "cflwͼ��_d3d��ɫ��.h"
namespace cflw::ͼ��::d3d��ɫ�� {
void C��ɫ������::f��ʼ��(const char *a��ɫģ��) {
	const auto f��ɫģ�͸�ֵ = [&](std::string &a�ַ���, const char *a��ɫ��) {
		a�ַ��� = std::string(a��ɫ��) + "_" + a��ɫģ��;
	};
	f��ɫģ�͸�ֵ(m������ɫģ��, "vs");
	f��ɫģ�͸�ֵ(m������ɫģ��, "ps");
	f��ɫģ�͸�ֵ(m������ɫģ��, "gs");
	f��ɫģ�͸�ֵ(m�����ɫģ��, "hs");
	f��ɫģ�͸�ֵ(m����ɫģ��, "ds");
	f��ɫģ�͸�ֵ(m������ɫģ��, "cs");
}
HRESULT C��ɫ������::f���붥����ɫ��(ComPtr<ID3DBlob> &a, const wchar_t *a�ļ���, const char *a������) {
	return f������ɫ��(a, a�ļ���, a������, m������ɫģ��.c_str());
}
HRESULT C��ɫ������::f����������ɫ��(ComPtr<ID3DBlob> &a, const wchar_t *a�ļ���, const char *a������) {
	return f������ɫ��(a, a�ļ���, a������, m������ɫģ��.c_str());
}
HRESULT C��ɫ������::f���뼸����ɫ��(ComPtr<ID3DBlob> &a, const wchar_t *a�ļ���, const char *a������) {
	return f������ɫ��(a, a�ļ���, a������, m������ɫģ��.c_str());
}
HRESULT C��ɫ������::f���������ɫ��(ComPtr<ID3DBlob> &a, const wchar_t *a�ļ���, const char *a������) {
	return f������ɫ��(a, a�ļ���, a������, m�����ɫģ��.c_str());
}
HRESULT C��ɫ������::f��������ɫ��(ComPtr<ID3DBlob> &a, const wchar_t *a�ļ���, const char *a������) {
	return f������ɫ��(a, a�ļ���, a������, m����ɫģ��.c_str());
}
HRESULT C��ɫ������::f���������ɫ��(ComPtr<ID3DBlob> &a, const wchar_t *a�ļ���, const char *a������) {
	return f������ɫ��(a, a�ļ���, a������, m������ɫģ��.c_str());
}
HRESULT C��ɫ������::f������ɫ��(ComPtr<ID3DBlob> &a, const wchar_t *a�ļ���, const char *a���, const char *a��ɫģ��) {
	HRESULT hr = S_OK;
	DWORD v��ɫ��־ = D3DCOMPILE_ENABLE_STRICTNESS;
#if defined( DEBUG ) || defined( _DEBUG )
	v��ɫ��־ |= D3DCOMPILE_DEBUG;
#endif
	ComPtr<ID3DBlob> v����;
	hr = D3DCompileFromFile(a�ļ���, nullptr, nullptr, a���, a��ɫģ��, v��ɫ��־, 0, &a, &v����);
	if (FAILED(hr)) {
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
}