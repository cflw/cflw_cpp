#pragma once
#include <map>
#include <chrono>
#include <memory>
#include <Windows.h>
#include <wrl.h>
#include <xaudio2.h>
#include "cflw��ý��.h"
//����
#pragma comment(lib, "xaudio2.lib")
//�����ռ�
namespace cflw::��Ƶ::xa2 {
using Microsoft::WRL::ComPtr;
using tʱ��� = std::chrono::time_point<std::chrono::system_clock>;
using tp�ӻ����� = std::shared_ptr<IXAudio2SubmixVoice>;
using tpԴ���� = std::shared_ptr<IXAudio2SourceVoice>;
class C����;
class C���;
using tp���� = std::shared_ptr<C����>;
using tp��� = std::shared_ptr<C���>;
using tp���� = size_t;	//���
//==============================================================================
// ��Ƶ����
//==============================================================================
class C��Ƶ {
public:
	C��Ƶ();
	~C��Ƶ();
	HRESULT f��ʼ��();
	void f����();
	HRESULT f��������(tp���� &, const wchar_t *�ļ���);
	HRESULT f����Դ����(tpԴ���� &, const C���� &, const C��� &);
	HRESULT f�������(tp��� &);
private:
	ComPtr<IXAudio2> m��Ƶ;
	IXAudio2MasteringVoice *m�������� = nullptr;
};
//==============================================================================
// ����
//==============================================================================
class C���ſ��� {
public:
	C���ſ���(C��Ƶ &);
	void fˢ��();
	tp���� f����(const C���� &, const C��� &);
	void f��ͣ(tp����);
	void f�ָ�(tp����);
	void fֹͣ(tp����);
	void fֹͣȫ��();
	bool fi����(tp����);
	void fs�ظ����ż��(float = 0);
private:
	C��Ƶ *m��Ƶ;
	std::map<tp����, tpԴ����> ma����;
	std::map<const C���� *, tʱ���> m����ȥ��;	//��ֹ��һʱ���ڲ��Ŵ���ͬһ������
	float m������� = 0;	//����ʱ�����Բ���ͬһ������
	tʱ��� m��ǰʱ��;
	tp���� m��� = 1;
};
//==============================================================================
// ������
//==============================================================================
class C���� {
public:
	WAVEFORMATEXTENSIBLE m��ʽ;
	XAUDIO2_BUFFER m����;
	std::unique_ptr<std::byte> m����;
	size_t m��С;
};
class C��� {
public:
	~C���();
	void f����();
	void fs����(float);
	float fg����() const;
	IXAudio2SubmixVoice *m���� = nullptr;
	XAUDIO2_SEND_DESCRIPTOR m����;
	XAUDIO2_VOICE_SENDS m�б�;
};
//==============================================================================
// �����ļ�
//==============================================================================
class C�����ļ� {
public:
	HRESULT f��(const wchar_t *);
	bool f�������() const;
	WAVEFORMATEXTENSIBLE f��ȡ��ʽ() const;
	std::pair<std::byte*, size_t> f��ȡ����() const;
	bool f�ر�();
	HANDLE m�ļ�;
};
}	//namespace cflw::��Ƶ::xa2