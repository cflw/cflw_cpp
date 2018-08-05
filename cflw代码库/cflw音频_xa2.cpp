#include <cassert>
#include <algorithm>
#include "cflw��Ƶ_xa2.h"
namespace cflw::��Ƶ::xa2 {
using ��ý��::FindChunk;
using ��ý��::ReadChunkData;
//==============================================================================
// ��������
//==============================================================================
void f��������(IXAudio2Voice *a) {
	a->DestroyVoice();
}
//==============================================================================
// ��Ƶ����
//==============================================================================
C��Ƶ::C��Ƶ() {
};
C��Ƶ::~C��Ƶ() {
	if (m��Ƶ) {
		f����();
	}
};
HRESULT C��Ƶ::f��ʼ��() {
	HRESULT hr;
	hr = CoInitializeEx(nullptr, COINIT_MULTITHREADED);
	if (FAILED(hr)) {
		return hr;
	}
	hr = XAudio2Create(&m��Ƶ, 0, XAUDIO2_DEFAULT_PROCESSOR);
	if (FAILED(hr)) {
		return hr;
	}
	hr = m��Ƶ->CreateMasteringVoice(&m��������);
	if (FAILED(hr)) {
		return hr;
	}
	return S_OK;
};
void C��Ƶ::f����() {
	f��������(m��������);
	m�������� = nullptr;
	m��Ƶ.Reset();
	CoUninitialize();
};
HRESULT C��Ƶ::f��������(tp���� &a����, const wchar_t *a�ļ�) {
	HRESULT hr;
	C�����ļ� v�ļ�;
	hr = v�ļ�.f��(a�ļ�);
	if (FAILED(hr)) {
		return hr;
	}
	if (!v�ļ�.f�������()) {
		return E_FAIL;	//���ǲ��θ�ʽ
	}
	tp���� v���� = std::make_shared<C����>();
	v����->m��ʽ = v�ļ�.f��ȡ��ʽ();
	const auto &[v����, v���ݴ�С] = v�ļ�.f��ȡ����();
	v����->m���� = std::unique_ptr<std::byte>(v����);
	v����->m��С = v���ݴ�С;
	//��仺��
	v����->m����.AudioBytes = v���ݴ�С;
	v����->m����.pAudioData = (BYTE*)v����;
	v����->m����.Flags = XAUDIO2_END_OF_STREAM;
	v����->m����.LoopBegin = XAUDIO2_NO_LOOP_REGION;
	v����->m����.LoopLength = 0;
	v����->m����.LoopCount = 0;
	//����
	a���� = std::move(v����);
	return S_OK;
};
HRESULT C��Ƶ::f����Դ����(tpԴ���� &aԴ����, const C���� &a����, const C��� &a���) {
	IXAudio2SourceVoice *vԴ����;
	HRESULT hr = m��Ƶ->CreateSourceVoice(&vԴ����, (WAVEFORMATEX*)&a����.m��ʽ, 0, 2, nullptr, &a���.m�б�);
	if (FAILED(hr)) {
		return hr;
	}
	aԴ���� = std::shared_ptr<IXAudio2SourceVoice>(vԴ����, &f��������);
	return S_OK;
}
HRESULT C��Ƶ::f�������(tp��� &a���) {
	tp��� v��� = std::make_shared<C���>();
	HRESULT hr = m��Ƶ->CreateSubmixVoice(&v���->m����, 1, 44100);
	if (FAILED(hr)) {
		return hr;
	}
	v���->m����.Flags = 0;
	v���->m����.pOutputVoice = v���->m����;
	v���->m�б�.pSends = &v���->m����;
	v���->m�б�.SendCount = 1;
	a��� = std::move(v���);
	return S_OK;
}
//==============================================================================
// ���ſ���
//==============================================================================
C���ſ���::C���ſ���(C��Ƶ &a):
	m��Ƶ(&a) {
	m��ǰʱ�� = std::chrono::system_clock::now();
}
void C���ſ���::fˢ��() {
	for (auto v���� = ma����.begin(); v���� != ma����.end();) {
		const auto &[v����, vԴ����] = *v����;
		++v����;
		XAUDIO2_VOICE_STATE v״̬;
		vԴ����->GetState(&v״̬);
		if (v״̬.BuffersQueued <= 0) {
			ma����.erase(v����);
		}
	}
	m��ǰʱ�� = std::chrono::system_clock::now();
}
tp���� C���ſ���::f����(const C���� &a����, const C��� &a���) {
	//ȥ��
	if (const auto &v������ = m����ȥ��.find(&a����); v������ != m����ȥ��.end()) {
		if (const float vʱ��� = std::chrono::duration<float>(m��ǰʱ�� - v������->second).count(); vʱ��� <= m�������) {
			return 0;	//�ظ�,������
		}
	}
	//����
	tp���� v���� = (++m���);
	tpԴ���� vԴ����;
	m��Ƶ->f����Դ����(vԴ����, a����, a���);
	vԴ����->SubmitSourceBuffer(&a����.m����);
	vԴ����->Start();
	m����ȥ��[&a����] = m��ǰʱ��;
	ma����[v����] = vԴ����;
	return v����;
}
void C���ſ���::f��ͣ(tp���� a) {
	if (const auto &v�Ҳ��� = ma����.find(a); v�Ҳ��� != ma����.end()) {
		v�Ҳ���->second->Stop();
	}
}
void C���ſ���::f�ָ�(tp���� a) {
	if (const auto &v�Ҳ��� = ma����.find(a); v�Ҳ��� != ma����.end()) {
		v�Ҳ���->second->Start();
	}
}
void C���ſ���::fֹͣ(tp���� a) {
	if (const auto &v�Ҳ��� = ma����.find(a); v�Ҳ��� != ma����.end()) {
		v�Ҳ���->second->Stop();
		ma����.erase(a);
	}
}
void C���ſ���::fֹͣȫ��() {
	for (const auto &[v����, vԴ����] : ma����) {
		vԴ����->Stop();
	}
	ma����.clear();
}
bool C���ſ���::fi����(tp���� a) {
	const auto &v�Ҳ��� = ma����.find(a);
	return v�Ҳ��� != ma����.end();
}
void C���ſ���::fs�ظ����ż��(float a) {
	m������� = a;
}
//==============================================================================
// ����
//==============================================================================
C���::~C���() {
	if (m����) {
		f��������(m����);
	}
}
void C���::f����() {
	f��������(m����);
	m���� = nullptr;
}
void C���::fs����(float a) {
	m����->SetVolume(a);
}
float C���::fg����() const {
	float v;
	m����->GetVolume(&v);
	return v;
}
//==============================================================================
// �����ļ�
//==============================================================================
HRESULT C�����ļ�::f��(const wchar_t *a�ļ���) {
	m�ļ� = CreateFileW(a�ļ���, GENERIC_READ, FILE_SHARE_READ, nullptr, OPEN_EXISTING, 0, nullptr);
	if (INVALID_HANDLE_VALUE == m�ļ�)
		return HRESULT_FROM_WIN32(GetLastError());
	if (INVALID_SET_FILE_POINTER == SetFilePointer(m�ļ�, 0, nullptr, FILE_BEGIN))
		return HRESULT_FROM_WIN32(GetLastError());
	return S_OK;
};
bool C�����ļ�::f�������() const {
	DWORD v���С;
	DWORD v��λ��;
	DWORD v�ļ�����;
	FindChunk(m�ļ�, ��ý��::c��RIFF, v���С, v��λ��);
	ReadChunkData(m�ļ�, &v�ļ�����, sizeof(DWORD), v��λ��);
	return v�ļ����� == ��ý��::c��WAVE;
};
WAVEFORMATEXTENSIBLE C�����ļ�::f��ȡ��ʽ() const {
	DWORD v���С;
	DWORD v��λ��;
	WAVEFORMATEXTENSIBLE v��ʽ;
	FindChunk(m�ļ�, ��ý��::c��fmt, v���С, v��λ��);
	ReadChunkData(m�ļ�, &v��ʽ, v���С, v��λ��);
	return v��ʽ;
};
std::pair<std::byte*, size_t> C�����ļ�::f��ȡ����() const {
	DWORD v���С;
	DWORD v��λ��;
	FindChunk(m�ļ�, ��ý��::c��data, v���С, v��λ��);
	std::byte *v���� = new std::byte[v���С];
	ReadChunkData(m�ļ�, v����, v���С, v��λ��);
	return {v����, v���С};
};
bool C�����ļ�::f�ر�() {
	return CloseHandle(m�ļ�);
}
}	//namespace cflw::��Ƶ::xa2