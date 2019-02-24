#pragma once
#include <complex>
namespace cflw::��ѧ {
//=============================================================================
// ����
//=============================================================================
//�����ļ�
template<typename t = double> using t���� = std::complex<t>;
struct Sֱ�߷���;
struct S����4;
struct SԲ��;
//���ļ�
struct S����2;
struct S����3;
struct S����4;
template<typename t> t f��ֵ(const t&��ʼֵ, const t&��ֵֹ, float �м�ֵ);
template<typename t> t f����ֵ(const t &);
template<> S����2 f����ֵ<S����2>(const S����2 &);
template<> S����3 f����ֵ<S����3>(const S����3 &);
//=============================================================================
//����2
struct S����2 {
	static const S����2 c��, cһ;
	float x = 0, y = 0;
	S����2() = default;
	S����2(float, float);
	static S����2 fc����r(const float &, const float &);	//��С���Ȼ������
	static S����2 fc����d(const float &, const float &);	//��С�Ȼ������
	static S����2 fc��ͬ(const float &);	//x,y�����ڲ���
	static S����2 fc��������(float, float, float, float);
	static S����2 fc���γߴ�(float, float, float, float);
	static S����2 fc���ΰ�ߴ�(float, float, float, float);
	S����2 &operator +=(const S����2 &);
	S����2 &operator -=(const S����2 &);
	S����2 &operator *=(const float &);
	S����2 &operator /=(const float &);
	S����2 &operator *=(const t����<float> &);
	S����2 operator +(const S����2 &) const;
	S����2 operator -(const S����2 &) const;
	S����2 operator *(const float &) const;
	S����2 operator /(const float &) const;
	S����2 operator *(const t����<float> &) const;
	S����2 operator -() const;
	bool operator ==(const S����2 &) const;
	bool operator !=(const S����2 &) const;
	bool fȫС��(const S����2 &) const;
	bool fȫС�ڵ���(const S����2 &) const;
	bool fȫ����(const S����2 &) const;
	bool fȫ���ڵ���(const S����2 &) const;
	bool fi��() const;
	float fg��С() const;
	float fgƽ��() const;
	float fg����d() const;
	float fg����r() const;
	float fg�н�r(const S����2 &) const;
	S����2 fg����() const;
	S����2 fg��һ() const;
	S����2 &fs(const float &);
	S����2 &fs(const float &, const float &);
	S����2 &fs��С(const float &);
	S����2 &fs����(const float &);
	S����2 &fs����d(const float &);
	S����2 &fs��תr(const float &);
	S����2 &fs��תd(const float &);
	S����2 f��С(const float &) const;
	S����2 f����r(const float &) const;
	S����2 f����d(const float &) const;
	float f���㷽��r(const S����2 &) const;
	float f���㷽��d(const S����2 &) const;
	S����2 f��תr(const float &) const;
	S����2 f��תd(const float &) const;
	S����2 f�Ƶ���תr(const S����2 &, const float &) const;
	S����2 f�Ƶ���תd(const S����2 &, const float &) const;
	float f�������(const S����2 &) const;
	S����2 f��������(const S����2 &) const;
	S����2 f���㷽λr(const S����2 &, const float &) const;
	S����2 f���㷽λd(const S����2 &, const float &) const;
	float f���(const S����2 &) const;
	S����2 &fs���Խ���(const S����2 &Ŀ��, const float &����ֵ);
	S����2 f���Խ���(const S����2 &Ŀ��, const float &����ֵ) const;
	S����2 &fs��������(const S����2 &Ŀ��, const float &����ֵ, const float &��С���� = 0, const float &��󽥱� = 999999999);
	S����2 f��������(const S����2 &Ŀ��, const float &����ֵ, const float &��С���� = 0, const float &��󽥱� = 999999999) const;
	S����2 f����(const Sֱ�߷��� &) const;
	S����2 f����(const float &) const;
	S����2 f����(const SԲ�� &) const;
	S����2 f����(const float &) const;
	S����2 fֱ������(float, float) const;
	S����2 f��������(float, float) const;
	S����2 f������(float, float) const;
	S����2 f������(const S����2 &) const;
	bool fi�������() const;
	//ת��
	S����3 ft����3(float = 0) const;
	S����4 ft����4(float = 0, float = 0) const;
};
//����3
struct S����3 {
	static const S����3 c��, cһ;
	float x, y, z;
	S����3();
	S����3(const float &, const float &, const float &);
	S����3 &operator +=(const S����3 &);
	S����3 &operator -=(const S����3 &);
	S����3 &operator *=(const float &);
	S����3 &operator /=(const float &);
	S����3 operator +(const S����3 &) const;
	S����3 operator -(const S����3 &) const;
	S����3 operator *(const float &) const;
	S����3 operator /(const float &) const;
	float fg��С() const;
	float fgƽ��() const;
	S����3 fg����() const;
	S����3 fg��һ() const;
	S����3 &fs��С(const float &);
	float f���(const S����3 &) const;
	S����3 f���(const S����3 &) const;
	S����3 &fs(const float &);
	S����3 &fs(const float &, const float &, const float &);
	//ת��
	S����2 ft����2() const;
	S����4 ft����4(const float &) const;
};
//����4
struct S����4 {
	union {
		struct {
			float x, y, z, w;
		};
		float mֵ[4];
	};
	S����4();
	S����4(const float &, const float &, const float &, const float &);
	S����4 operator *(const S����4 &) const;
	S����3 ft����3() const;
};

}	//namespace cflw::��ѧ