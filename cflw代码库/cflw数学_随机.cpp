#include "cflw��ѧ.h"
#include "cflw��ѧ_���.h"
namespace cflw {
namespace ��ѧ {
class C�ֲ����� {
public:
	static const unsigned int cλ = sizeof(unsigned int) * 4;
	static const unsigned int c��� = 1 << cλ;
	static std::tuple<float, float> f�ָ�2(unsigned int p) {
		const unsigned int v0 = p >> cλ;	//��λ����
		const unsigned int v1 = p % c���;	//��λ����
		return std::make_tuple<float, float>((float)v0 / c���, (float)v1 / c���);
	}
};
//Բ�ηֲ�=========================================================================
CԲ�ηֲ�::CԲ�ηֲ�(const SԲ�� &pԲ��):
	mԲ��{pԲ��} {
}
S����2 CԲ�ηֲ�::f����(unsigned int p) const {
	const auto v�ָ� = C�ֲ�����::f�ָ�2(p);
	S����2 v���� = S����2::fc����r(std::get<0>(v�ָ�) * mԲ��.m�뾶, std::get<1>(v�ָ�) * (float)c��);
	return v���� + mԲ��.m����;
}
//���ηֲ�=========================================================================
C���ηֲ�::C���ηֲ�(const S��ת���� &p����):
	m����{p����} {
}
S����2 C���ηֲ�::f����(unsigned int p) const {
	const auto v�ָ� = C�ֲ�����::f�ָ�2(p);
	S����2 v���� = S����2{
		f��ֵ<float>(-m����.m��ߴ�.x, m����.m��ߴ�.x, std::get<0>(v�ָ�)),
		f��ֵ<float>(-m����.m��ߴ�.y, m����.m��ߴ�.y, std::get<1>(v�ָ�))
	};
	v����.fs��תr(m����.m����);
	return v���� + m����.m����;
}

}	//namespace ��ѧ
}	//namespace cflw