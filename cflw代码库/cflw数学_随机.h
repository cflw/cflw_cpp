#pragma once
#include <random>
#include "cflw��ѧ_ƽ�漸��.h"
#define ����������ֲ����㺯�� \
template<typename t>\
auto operator()(t &p) {\
	return f����(p());\
}
namespace cflw::��ѧ {
//==============================================================================
// �������
//==============================================================================
class C����ͬ�� {
public:
	unsigned long a;		//���������a
	unsigned long b;		//���������b
	unsigned long r;		//�ϴμ�����
	static constexpr unsigned long c���ֵ = 0x00ffffff;	//��������ֵ
	C����ͬ��();		//���캯��
	void f������(const unsigned long &);
	void f����();	//����һ�������
	unsigned long f����();
	template<class t> t f����(const t &, const t &);
	bool f����(const float &);
};
template<class t> t C����ͬ��::f����(const t &aС, const t &a��) {
	f����();
	const t v�� = a�� - aС;
	return (t)(aС + (t)r / (t)c���ֵ * v��);
}
//==============================================================================
// �ֲ�
//==============================================================================
template<typename t = double> std::uniform_real_distribution<t> fԲ�ֲܷ�r() {
	return std::uniform_real_distribution<t>(0, ��ѧ::c����<t>);
}
template<typename t = double> std::uniform_real_distribution<t> fԲ�ֲܷ�d() {
	return std::uniform_real_distribution<t>(0, (t)360);
}
class CԲ�ηֲ� {
public:
	CԲ�ηֲ�(const SԲ�� &);
	����������ֲ����㺯��
	S����2 f����(unsigned int) const;
private:
	SԲ�� mԲ��;
};
class C���ηֲ� {
public:
	C���ηֲ�(const S��ת���� &);
	����������ֲ����㺯��
	S����2 f����(unsigned int) const;
private:
	S��ת���� m����;
};
}	//namespace cflw::��ѧ