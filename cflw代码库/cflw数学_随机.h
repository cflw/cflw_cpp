#pragma once
#include <random>
#include "cflw��ѧ_ƽ�漸��.h"
#define ����������ֲ����㺯�� \
template<typename t>\
auto operator()(t &p) {\
	return f����(p());\
}
namespace cflw {
namespace ��ѧ {
//�ֲ�
template<typename t = double> std::uniform_real_distribution<t> fԲ�ֲܷ�r() {
	return std::uniform_real_distribution<t>(0, (t)��ѧ::c����);
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
}	//namespace ��ѧ
}	//namespace cflw
