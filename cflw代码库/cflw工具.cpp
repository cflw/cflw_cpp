#include <assert.h>
#include "cflw����.h"
#include "cflw�쳣.h"
namespace cflw {
namespace ���� {
//==============================================================================
// �����
//==============================================================================
C�����::C�����():a(0),b(0),r(0){};
const unsigned long C�����::max = 0x00ffffff;
void C�����::f������(const unsigned long &����) {
	r = 0;
	b = ����;
	while (b > 0xffff)
		b /= 2;
	a = b;
	while (a > 0xff)
		a /= 2;
}
void C�����::f����() {	//����һ�������
	r = (a * r + b) % max;
}
unsigned long C�����::f����() {
	f���� ();
	return r;
}
bool C�����::f����(const float &p) {
	return f����<float>(0, 1) <= p;
}
//==============================================================================
// �ƴ���
//==============================================================================
void C�ƴ���::f����(int i) {
	v��� = i;
	v���� = 0;
}
bool C�ƴ���::f�δ�() {
	++v����;
	if (v���� >= v���) {
		v���� = 0;
		return true;
	} else {
		return false;
	}
}
//==============================================================================
// �ı��༩
//==============================================================================
#define _�ı�ת��ģ��(t1, t2, f) \
	template<> t2 C�ı�::fת��<t1, t2>(t1 p) { \
		return C�ı�::f(p); \
	}
#define _�ı�ת��ģ��_���ı�(t, f) _�ı�ת��ģ��(t, C�ı�::t�ַ���, f<t>)
#define _�ı�ת��ģ��_������(t, f) _�ı�ת��ģ��(C�ı�::t�ַ���, t, f<t>)
_�ı�ת��ģ��_���ı�(unsigned char, f����_�ı�)
_�ı�ת��ģ��_���ı�(unsigned long, f����_�ı�)
_�ı�ת��ģ��_���ı�(int, f����_�ı�)
_�ı�ת��ģ��_���ı�(long long, f����_�ı�)
_�ı�ת��ģ��_���ı�(float, f������_�ı�)
_�ı�ת��ģ��_���ı�(double, f������_�ı�)
_�ı�ת��ģ��_������(unsigned char, f�ı�_����)
_�ı�ת��ģ��_������(unsigned long, f�ı�_����)
_�ı�ת��ģ��_������(int, f�ı�_����)
_�ı�ת��ģ��_������(long long, f�ı�_����)
_�ı�ת��ģ��_������(float, f�ı�_������)
_�ı�ת��ģ��_������(double, f�ı�_������)
#undef _�ı�ת��ģ��_���ı�
#undef _�ı�ת��ģ��_������
#undef _�ı�ת��ģ��
C�ı�::t�ַ��� C�ı�::f����_ʮ������(const void *a����, size_t a��С) {
	auto f = [](unsigned char a����)->wchar_t {
		if (a���� < 10) {
			return L'0' + a����;
		} else {
			return L'a' + (a���� - 10);
		}
	};
	std::unique_ptr<wchar_t[]> va���� = std::make_unique<wchar_t[]>(a��С * 2 + 1);
	unsigned char *v���� = (unsigned char*)a����;
	size_t v��С;
	for (v��С = 0; v��С != a��С; ++v��С) {
		unsigned char v�� = v����[v��С];
		va����[2*v��С] = f(v�� / 0x10);
		va����[2*v��С+1] = f(v�� >> 4);
	}
	va����[a��С * 2] = 0;
	return {va����.get()};
}
std::tuple<std::byte*, size_t> C�ı�::fʮ������_����(const t�ַ��� &a�ı�) {
	auto f = [](wchar_t a�ַ�)->unsigned char {
		if (a�ַ� >= L'0' && a�ַ� <= L'9') {
			return (unsigned char)(a�ַ� - L'0');
		} else if (a�ַ� >= L'A' && a�ַ� <= L'F') {
			return (unsigned char)(a�ַ� - L'A');
		} else if (a�ַ� >= L'a' && a�ַ� <= L'f') {
			return (unsigned char)(a�ַ� - L'a');
		}
		throw �쳣::X����("��Ч�ַ�");
	};
	t�ַ��� v�ַ��� = (a�ı�.find(L"0x", 0) != 0) ? a�ı� : a�ı�.substr(2);
	size_t v��С = v�ַ���.size() * 2;
	std::byte *v���� = new std::byte[v��С];
	for (size_t i = 0; i != v��С; ++i) {
		unsigned char &v��ǰ���� = (unsigned char &)v����[i];
		v��ǰ���� = f(v�ַ���[2*i]) << 0x10;
		v��ǰ���� |= f(v�ַ���[2*i+1]);
		//if (2 * i + 2 >= v��С) {
		//	break;
		//}
	}
	return {v����, v��С};
}
bool C�ı�::fw����(const t�ַ��� &a�ı�) {
	bool v�ɸ� = true;
	bool v�ɵ� = true;
	bool v��e = true;
	for (int i = 0; i < a�ı�.size(); ++i) {
		const wchar_t v�� = a�ı�[i];
		if (v�� == L'-') {//����
			if (v�ɸ�) {
				v�ɸ� = false;
				continue;
			} else {
				return false;
			}
		} else if (v�� == L'.') {
			if (v�ɵ�) {
				v�ɵ� = false;
				continue;
			} else {
				return false;
			}
		} else if (v�� == L'e' && v�� == L'E') {
			if (v��e) {
				v��e = false;
				v�ɵ� = false;
				v�ɸ� = true;
				continue;
			} else {
				return false;
			}
		} else if (v�� >= L'0' && v�� <= L'9') {
			v�ɸ� = false;
			continue;
		} else if (v�� == L'\0') {
			return i != 0;
		} else {
			return false;
		}
	}
	return true;
}
int C�ı�::f����(const t�ַ��� &a�ı�, const t�ַ��� &a����, int a��ʼ) {
	for (int i = a��ʼ; i < a�ı�.size(); ++i) {
		if (i >= a�ı�.size() - a����.size()) {
			return -1;
		}
		bool v��� = true;
		for (int j = 0; j < a����.size(); ++j) {
			if (a�ı�[i+j] != a����[j]) {
				v��� = false;
				break;
			}
		}
		if (v���) {
			return i;
		}
	}
	return -1;
}
C�ı�::t�ַ��� C�ı�::f��Ч����(const t�ַ��� &a�ı�, int aλ��) {
	wchar_t v[16] = L"";
	int v�޸�λ = 0;
	bool vС��λ = false;
	for (; v�޸�λ < a�ı�.size(); ++v�޸�λ) {
		const wchar_t v�� = a�ı�[v�޸�λ];
		if (v�� == L'.') {
			vС��λ = true;
			continue;
		}
		if ((++v�޸�λ) <= aλ��) {
			v[v�޸�λ] = v��;
		} else {
			if (vС��λ) {
				break;
			}
			v[v�޸�λ] = L'0';
		}
	}
	return {v};
}
C�ı�::t�ַ��� C�ı�::fС��λ��(const t�ַ��� &a�ı�, int aλ��) {
	wchar_t v[16] = L"";
	int vС�� = -999;
	int v�޸�λ = 0;
	for (; v�޸�λ < a�ı�.size(); ++v�޸�λ) {
		const wchar_t v�� = a�ı�[v�޸�λ];
		v[v�޸�λ] = v��;
		if (v�� == L'.') {
			vС�� = 0;
		}
		if ((++vС��) > aλ��) {
			return {v};
		}
	}
	//
	if (vС�� < 0) {
		v[v�޸�λ++] = L'.';
		vС�� = 0;
	}
	while ((++vС��) <= aλ��) {
		v[v�޸�λ++] = L'0';
	}
	return {v};
}
//--------------------------------------------------------------------------------
// ����
//--------------------------------------------------------------------------------
C����::C����(unsigned int a��С) : mָ��(new unsigned char[a��С]), m��С(a��С) {
}
C����::C����(const C���� &a����) {
	if (a����.mָ��) {
		f�½�(a����.m��С);
		f����(a����.mָ��, a����.m��С);
	}
}
C����::~C����() {
	if (mָ��) {
		delete[] mָ��;
	}
}
bool C����::f�½�(unsigned int a��С) {
	fɾ��();
	mָ�� = new unsigned char[a��С];
	if (mָ�� != nullptr) {
		m��С = a��С;
		return true;
	} else {
		return false;
	}
}
void C����::fɾ��() {
	if (mָ��) {
		delete[] mָ��;
		mָ�� = nullptr;
		m��С = 0;
	}
}
void C����::f����(void *aָ��, unsigned int a��С) {
	const unsigned int v���ƴ�С = (m��С >= a��С) ? a��С : m��С;
	memcpy(mָ��, aָ��, v���ƴ�С);
}
void C����::f����(const C���� &a����) {
	if (a����.mָ��) {
		f����(a����.mָ��, a����.m��С);
	}
}
unsigned char *&C����::fg����() {
	return mָ��;
}
unsigned int C����::fg��С() {
	return m��С;
}
//--------------------------------------------------------------------------------
// λ��С,λָ��
//--------------------------------------------------------------------------------
//λ��С
Sλ��С::Sλ��С(int a�ֽ�, int aλ):
	v�ֽ�(a�ֽ� + aλ / 8),
	vλ(aλ % 8)
{}
Sλ��С &Sλ��С::operator +=(const Sλ��С &a��С) {
	v�ֽ� += a��С.v�ֽ�;
	vλ += a��С.vλ;
	while (vλ >= 8) {
		v�ֽ� += 1;
		vλ -= 8;
	}
	return *this;
}
Sλ��С Sλ��С::operator +(const Sλ��С &a��С) const {
	return Sλ��С(v�ֽ� + a��С.v�ֽ�, vλ + a��С.vλ);
}
Sλ��С::operator int() const {
	return v�ֽ� * 8 + vλ;
}
//λָ��
Cλָ��::Cλָ��():
	vָ��(nullptr),
	vƫ��(0, 0)
{}
Cλָ��::Cλָ��(void *aָ��):
	vָ��(aָ��),
	vƫ��(0, 0)
{}
Cλָ��::Cλָ��(void *aָ��, int aλ):
	vָ��(aָ��),
	vƫ��(0, aλ)
{}
Cλָ�� &Cλָ��::fsָ��(void *aָ��, int aλ) {
	vָ�� = aָ��;
	vƫ��.v�ֽ� = 0;
	vƫ��.vλ = aλ;
	return *this;
}
void Cλָ��::f��(void *aָ��, const Sλ��С &a��С) {
	assert(vָ��);
	f�ڴ渴��(*this, Cλָ��(aָ��), a��С);
}
void Cλָ��::f��(const Cλָ�� &aָ��, const Sλ��С &a��С) {
	assert(vָ��);
	f�ڴ渴��(*this, aָ��, a��С);
}
void Cλָ��::fд(void *aָ��, const Sλ��С &a��С) {
	assert(vָ��);
	f�ڴ渴��(Cλָ��(aָ��), *this, a��С);
}
void Cλָ��::fд(const Cλָ�� &aָ��, const Sλ��С &a��С) {
	assert(vָ��);
	f�ڴ渴��(aָ��, *this, a��С);
}
Cλָ�� &Cλָ��::fƫ��(const Sλ��С &aλ��С) {
	vƫ�� += aλ��С;
	return *this;
}
void Cλָ��::f�ڴ渴��(const Cλָ�� &a��, const Cλָ�� &a��, const Sλ��С &a��С) {
	f�ڴ渴��(a��.vָ��, a��.vƫ��, a��.vָ��, a��.vƫ��, a��С);
}
void Cλָ��::f�ڴ渴��(void *aָ��1, int aƫ��1, void *aָ��2, int aƫ��2, int a��С) {
	while (a��С > 0) {
		const int v���ݴ�С = (a��С >= 8) ? 8 : a��С;
		const unsigned long v���� = fȡ����(aָ��2, aƫ��2, v���ݴ�С);
		f������(aָ��1, aƫ��1, v����);
		++(unsigned char *&)aָ��1;
		++(unsigned char *&)aָ��2;
		a��С -= 8;
	}
}
unsigned long Cλָ��::fȡ����(void *aָ��, int aƫ��, int a��С) {
	assert(aƫ�� + a��С <= 32);
	unsigned long v���� = *((unsigned long *)aָ��);
	v���� = v���� >> aƫ��;
	v���� &= 0xffffffff >> (32 - a��С);
	return v����;
}
void Cλָ��::f������(void *aָ��, int aƫ��, unsigned long a����) {
	unsigned char *vָ�� = (unsigned char *)aָ��;
	unsigned long v���� = a���� << aƫ��;
	//��1�ֽ�
	*vָ�� &= 0xff >> (8 - aƫ��);
	*vָ�� |= (unsigned char)v����;
	//��2�ֽ�
	*(++vָ��) = (unsigned char)(v���� >> 8);
	//��3�ֽ�
	*(++vָ��) = (unsigned char)(v���� >> 16);
	//��4�ֽ�
	*(++vָ��) = (unsigned char)(v���� >> (24 - aƫ��));
}
//�����ռ����
}}