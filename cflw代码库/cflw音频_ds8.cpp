#include "cflw��Ƶ_ds8.h"
#include "cflw����.h"
#include "cflw����_win.h"
namespace cflw::��Ƶ::ds8 {
//--------------------------------------------------------------------------------
// ��Ƶ����
//--------------------------------------------------------------------------------
//���캯��
C��Ƶ����::C��Ƶ����() {
	����::f����(*this);
};
//��������
C��Ƶ����::~C��Ƶ����() {
	if (v�豸)
		f�ͷ�();
};
//��ʼ��
HRESULT C��Ƶ����::f��ʼ�� (HWND p����) {
	if (v�豸)
		return S_FALSE;
	v��Ҫ = nullptr;
	HRESULT hr;
	LPDIRECTSOUNDBUFFER v������ = nullptr;
	hr = DirectSoundCreate8(nullptr, &v�豸, nullptr);
	if(FAILED(hr))
		return hr;
	hr = v�豸->SetCooperativeLevel(p����, DSSCL_PRIORITY);
	DSBUFFERDESC v��������;
	v��������.dwFlags = DSBCAPS_PRIMARYBUFFER;
	v��������.dwBufferBytes = 0;
	v��������.lpwfxFormat = nullptr;
	hr = v�豸->CreateSoundBuffer(&v��������, &v������, nullptr);
	WAVEFORMATEX v���θ�ʽ;
	����::f����(v���θ�ʽ); 
	v���θ�ʽ.wFormatTag = WAVE_FORMAT_PCM; 
	v���θ�ʽ.nChannels = 2; 
	v���θ�ʽ.nSamplesPerSec = 22050; 
	v���θ�ʽ.wBitsPerSample = 16; 
	v���θ�ʽ.nBlockAlign = v���θ�ʽ.wBitsPerSample / 8 * v���θ�ʽ.nChannels;
	v���θ�ʽ.nAvgBytesPerSec = v���θ�ʽ.nSamplesPerSec * v���θ�ʽ.nBlockAlign;
	hr = v������->SetFormat(&v���θ�ʽ);
	if(FAILED(hr))
	   return hr;
	����::f�ͷ�(v������);
	return S_OK;
}
//�ͷ�
void C��Ƶ����::f�ͷ� () {
	����::f�ͷ�(v��Ҫ);
	����::f�ͷ�(v�豸);
}
//��������
HRESULT C��Ƶ����::f�������� (S���� &p����, WCHAR *p�ļ���, WCHAR *p�ļ���2) {
	if (p����.v����)
		p����.f�ͷ�();
	C�����ļ� v�ļ�[2];
	v�ļ�[0].f��(p�ļ���);
	v�ļ�[1].f��(p�ļ���2);
	return S_OK;
}
//������Ч
HRESULT C��Ƶ����::f������Ч (S���� &p����, WCHAR *p�ļ���) {
	if (p����.v����)
		p����.f�ͷ�();
	C�����ļ� v�ļ�;
	HRESULT hr;
	hr = v�ļ�.f��(p�ļ���);
	if (FAILED(hr))
		return hr;	//�޷����ļ�
	fע�Ỻ��(p����, v�ļ�);
	return S_OK;
}
void C��Ƶ����::f�������� () {

}
void C��Ƶ����::f������Ч () {

}
HRESULT C��Ƶ����::fע�Ỻ�� (S���� &p����, C�����ļ� &p�ļ�) {
	DSBUFFERDESC v��������;
	v��������.dwFlags = DSBCAPS_STATIC;
	v��������.dwBufferBytes = p�ļ�.v����Ϣ.cksize;
	v��������.lpwfxFormat = p�ļ�.v��ʽ;
	LPDIRECTSOUNDBUFFER v��ʱ = nullptr;
	HRESULT hr;
	hr = v�豸->CreateSoundBuffer(&v��������, &v��ʱ, nullptr);
	if (FAILED(hr))
		return hr;
	v��ʱ->QueryInterface(IID_IDirectSoundBuffer8, (void**)&p����.v����);
	if (FAILED(hr))
		return hr;
	v��ʱ->Release();
	p����.v��С = v��������.dwBufferBytes;
	return S_OK;
}
HRESULT C��Ƶ����::f������� (S���� &p����, C�����ļ� &p�ļ�) {
	HRESULT hr;
	BYTE* v��������;
	UINT v���δ�С;
	void* v����[2] = {nullptr, nullptr};
	ULONG v����[2];
	const UINT v�ļ���С = p�ļ�.v����Ϣ.cksize;
	v�������� = new BYTE[v�ļ���С];
	if (v�������� == nullptr) {
		delete[] v��������;
		return S_FALSE;	//�ڴ治��
	}
	hr = p�ļ�.f��ȡ(v�ļ���С, v��������, &v���δ�С);
	if (FAILED(hr)) {
		delete[] v��������;
		return hr;	//��ȡʧ��
	}
	p�ļ�.f����();
	hr = p����.v����->Lock(0, p����.v��С, &v����[0], &v����[0], &v����[1], &v����[1], 0);
	if (FAILED(hr)) {
		delete[] v��������;
		return hr;	//����ʧ��
	}
	memcpy(v����[0], v��������, p����.v��С);
	p����.v����->Unlock(v����[0], p����.v��С, nullptr, 0);
	delete[] v��������;
	return S_OK;
}
//==============================================================================
// ����
//==============================================================================
S����::S���� () {
	����::f����(*this);
}
S����::~S���� () {
	f�ͷ�();
}
void S����::f�ͷ� () {
	����::f�ͷ�(v����);
};
//==============================================================================
// �����ļ�
//==============================================================================
C�����ļ�::C�����ļ�() {
	m��ʽ = nullptr;
}
C�����ļ�::~C�����ļ�() {
	f�ر�();
	����::fɾ��(m��ʽ);
};
HRESULT C�����ļ�::f��(WCHAR *a�ļ���) {
	����::fɾ��(m��ʽ);
	HRESULT  hr;
	hr = WaveOpenFile(a�ļ���, &m��ý��io, &m��ʽ, &m����Ϣriff);
	if(FAILED(hr))
		return hr;
	hr = f����();
	if(FAILED(hr))
		return hr;
	return hr;
}
HRESULT C�����ļ�::f����() {
	return WaveStartDataRead(&m��ý��io, &m����Ϣ, &m����Ϣriff);
}
HRESULT C�����ļ�::f��ȡ(UINT pҪ��ȡ��С, BYTE* a����, UINT* p��ȡ��С) {
	return WaveReadFile(m��ý��io, pҪ��ȡ��С, a����, &m����Ϣ, p��ȡ��С);
}
HRESULT C�����ļ�::f�ر�() {
	mmioClose(m��ý��io, 0);
	return S_OK;
}

}	//�����ռ����