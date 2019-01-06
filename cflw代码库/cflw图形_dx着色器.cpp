#include "cflwͼ��_dx��ɫ��.h"
namespace cflw::ͼ��::dx��ɫ�� {
HRESULT C��ɫ������::f��ʼ��(const wchar_t *a��ɫģ��) {
	HRESULT hr;
	hr = DxcCreateInstance(CLSID_DxcCompiler, IID_PPV_ARGS(&m������));
	if (FAILED(hr)) {
		return hr;
	}
	hr = DxcCreateInstance(CLSID_DxcLibrary, IID_PPV_ARGS(&m��));
	if (FAILED(hr)) {
		return hr;
	}
	const auto f��ɫģ�͸�ֵ = [&](std::wstring &a�ַ���, const wchar_t *a��ɫ��) {
		a�ַ��� = std::wstring(a��ɫ��) + L"_" + a��ɫģ��;
	};
	f��ɫģ�͸�ֵ(m������ɫģ��, L"vs");
	f��ɫģ�͸�ֵ(m������ɫģ��, L"ps");
	f��ɫģ�͸�ֵ(m������ɫģ��, L"gs");
	f��ɫģ�͸�ֵ(m�����ɫģ��, L"hs");
	f��ɫģ�͸�ֵ(m����ɫģ��, L"ds");
	f��ɫģ�͸�ֵ(m������ɫģ��, L"cs");
	return S_OK;
}
//������ɫ��
HRESULT C��ɫ������::f���붥����ɫ��(ComPtr<IDxcBlob> &a, const wchar_t *a�ļ���, const wchar_t *a������) {
	return f������ɫ��(a, a�ļ���, a������, m������ɫģ��.c_str());
}
HRESULT C��ɫ������::f����������ɫ��(ComPtr<IDxcBlob> &a, const wchar_t *a�ļ���, const wchar_t *a������) {
	return f������ɫ��(a, a�ļ���, a������, m������ɫģ��.c_str());
}
HRESULT C��ɫ������::f���뼸����ɫ��(ComPtr<IDxcBlob> &a, const wchar_t *a�ļ���, const wchar_t *a������) {
	return f������ɫ��(a, a�ļ���, a������, m������ɫģ��.c_str());
}
HRESULT C��ɫ������::f���������ɫ��(ComPtr<IDxcBlob> &a, const wchar_t *a�ļ���, const wchar_t *a������) {
	return f������ɫ��(a, a�ļ���, a������, m�����ɫģ��.c_str());
}
HRESULT C��ɫ������::f��������ɫ��(ComPtr<IDxcBlob> &a, const wchar_t *a�ļ���, const wchar_t *a������) {
	return f������ɫ��(a, a�ļ���, a������, m����ɫģ��.c_str());
}
HRESULT C��ɫ������::f���������ɫ��(ComPtr<IDxcBlob> &a, const wchar_t *a�ļ���, const wchar_t *a������) {
	return f������ɫ��(a, a�ļ���, a������, m������ɫģ��.c_str());
}
//���ĺ���
HRESULT C��ɫ������::f������ɫ��(ComPtr<IDxcBlob> &a���, const wchar_t *a�ļ���, const wchar_t *a���, const wchar_t *a��ɫģ��) {
	HRESULT hr;
	ComPtr<IDxcBlobEncoding> vԴ;
	hr = m��->CreateBlobFromFile(a�ļ���, nullptr, &vԴ);
	if (FAILED(hr)) {
		return hr;
	}
	ComPtr<IDxcOperationResult> v���;
	hr = m������->Compile(vԴ.Get(), a�ļ���, a���, a��ɫģ��, nullptr, 0, nullptr, 0, nullptr, &v���);
	if (FAILED(hr)) {
		return hr;
	}
	v���->GetStatus(&hr);
	if (FAILED(hr)) {
		ComPtr<IDxcBlobEncoding> v����;
		v���->GetErrorBuffer(&v����);
		OutputDebugStringA((char*)v����->GetBufferPointer());
		return hr;
	}
	v���->GetResult(&a���);
	return S_OK;
}
HRESULT C��ɫ������::f��ȡ��ɫ��(ComPtr<IDxcBlob> &a, const wchar_t *a�ļ���) {
	HRESULT hr;
	ComPtr<IDxcBlobEncoding> vԴ;
	hr = m��->CreateBlobFromFile(a�ļ���, nullptr, &vԴ);
	if (FAILED(hr)) {
		return hr;
	}
	vԴ.As(&a);
	return S_OK;
}
}