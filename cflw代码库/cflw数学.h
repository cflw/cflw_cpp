#pragma once
#include <math.h>
#include <complex>
#include <utility>
#include <functional>
#include <algorithm>
namespace cflw::��ѧ {
//==============================================================================
//��������&����&ǰ������
//==============================================================================
//��׼������
typedef std::complex<float> t����;
//==============================================================================
// ��ѧ����
//==============================================================================
constexpr double c��� = 1.5707963267948966192313216916398;
constexpr double c�� = 3.1415926535897932384626433832795;
constexpr double c���� = 6.283185307179586476925286766559;
constexpr double c����2 = 1.4142135623730950488016887242097;
constexpr double c�ȵ����� = 0.01745329251994329576923690768489;
constexpr double c���ȵ��� = 57.295779513082320876798154814105;
//==============================================================================
// ������ѧ����&ȫ��͵������
//==============================================================================
int fȡ����λ��(const int &);
template<typename t> int fȡ����(const t &x);
template<> int fȡ����<bool>(const bool &x);
template<typename t> const t& f���ֵ(const t &a, const t &b);
template<typename t> const t& f��Сֵ(const t &a, const t &b);
template<typename t> t f����(const t &ֵ, const t &��Сֵ, const t &���ֵ);
template<typename t> t f�ӽ�(const t &Դֵ, const t &Ŀ��ֵ, const t &�ӽ���);
template<typename t> t f��������(const t &Դֵ, const t &Ŀ��ֵ, const float &��ֵ���䱶��, const t &��С����, const t &��󽥱�);
template<typename t> t f���Խ���(const t &Դֵ, const t &Ŀ��ֵ, const float &����ֵ);
template<typename t> t f����(const t &pԴֵ, const t &p����);
template<typename t> bool f����ѭ��(t &pֵ, const t &p���ֵ);
int f10�Ĵη�(const int &x);
template<typename t> t f����ֵ(const t &);
template<typename t> std::tuple<t, t> sincos(t);
template<typename t> t f��ֵ(const t&��ʼֵ, const t&��ֵֹ, float �м�ֵ);
template<typename t> int f��(t &����ֵ, const t &��ֵ);
template<typename t> t f���(const t&��, const t&��);
template<typename t> t f���(const t&��, const t&��);
template<typename t> t f��(const t&��);
template<typename t> bool fͬ����(const t &, const t &);
template<typename t> t fƽ��(const t &);
template<typename t> t f����(const t &);
template<typename t> t f����(const t &, const t &);//��x���뵽y��������
template<typename t> t fѭ��(const t &, const t &��С, const t &���);
template<typename t> t f��(const t &, const t &);
template<typename tk, typename tv> tv f��ֵ2(const std::pair<tk, tv> &, const std::pair<tk, tv> &, const tk &);
template<typename tk, typename tv> tv f��ֵ2(const tk &, const tv &, const tk &, const tv &, const tk &);
template<typename t> t f������(const t &, const t &);	//��֪б�ߺ�һֱ�Ǳ�����һֱ�Ǳ�
template<typename t> t f��������(const t &);	//
template<typename t> t f�������β�ֵ(const t &pС, const t &p��, float pб��, float p�м�ֵ);
template<typename t����, typename...t����> t���� f����ƽ��(t���� &&...);
template<typename t����, typename...t����> t���� f����ƽ��(t���� &&...);
template<typename t����, typename...t����> t���� f����ֵ���ֵ(t���� &&...);	//���������ֵ���ֵ,����ԭֵ
//==============================================================================
// �������κ���
//==============================================================================
//�ر�Ƕ�
float f����(const float &x, const float &y);
float f����(float, float);
float fλ��(float, float);
//����������ֱ������任
float f��������x(float, float);
float f��������y(float, float);
float fֱ������x(float, float);
float fֱ������y(float, float);
//==============================================================================
// ���ּ�����
//==============================================================================
template<typename t> class C�Ƕȼ��� {
public:
	static const C�Ƕȼ��� c��, c����;
	t m�ܽ�;
	t mƽ��;
	C�Ƕȼ���(const t &);
	t fƽ��(const t &��1, const t &��2) const;
	t fȡ��(const t &��) const;	//������[0,�ܽ�)��Χ��
	t f����(const t &��) const;	//������(-ƽ��,ƽ��]��Χ��
	t fȡ��(const t &��) const;	//������[0,ƽ��)��Χ��
	t f��ת����(const t &Դ, const t &Ŀ��, const t &���) const;
	t f�н�(const t &��1, const t &��2) const;
	t f����(const t &x, const t &y) const;	//ԭ�㵽Ŀ���ķ���
	t f��ֵ(const t &��1, const t &��2, const t &��ֵ) const;
};
//==============================================================================
// λ�ù�ϵ
//==============================================================================
enum Eλ�ù�ϵ {
	e�ں� = -2,
	e���� = -1,
	e�ཻ = 0,
	e���� = 1,
	e���� = 2
};
//std::weak_equality operator <=>(Eλ�ù�ϵ, int);
}	//�����ռ����
#include "cflw��ѧ.inl"
