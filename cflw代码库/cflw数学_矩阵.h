#pragma once
#include <cassert>
#include "cflw��ѧ.h"
namespace cflw::��ѧ {
//=============================================================================
// ����
//=============================================================================
//�����ļ�
struct S����3;
struct S����4;
struct Sƽ�淽��;
//=============================================================================
// ����
//=============================================================================
template<unsigned int ��, unsigned int ��> struct S���� {
	const static unsigned int c�� = ��;
	const static unsigned int c�� = ��;
	float mֵ[��][��];
	S����();
	S����(std::initializer_list<float>);
	float &operator ()(unsigned int i, unsigned int j) {
		return mֵ[i][j];
	}
};
struct S������Ϣ {
private:
	int m��, m��;
	float *m��;
public:
	float &fȡ(int ��, int ��) {
		return m��[�� * m�� + ��];
	}
};
class C���� {	//�ṩ��������
public:
	static void f�վ���_(float *, int, int);
	static void f�������_(float *, const float *, const float *, int, int, int);
	static void f��λ����_(float *, int);
	static void f�������_(float *, const float *, const float *, int, int);
	static void f����ת��_(float *, const float *, int, int);
	static float f������ʽ_(float *, int);
public:
	template<unsigned int ��, unsigned int ��> static void f�վ���(S����<��, ��> &p);
	template<unsigned int һ, unsigned int ��, unsigned int ��> static void f�������(S����<һ, ��> &p��, const S����<һ, ��> &pһ, const S����<��, ��> &p��);
	template<unsigned int һ> static void f��λ����(S����<һ, һ> &p);
	template<unsigned int i, unsigned int j> static void f�������(S����<i, j> &o, const S����<i, j> &p1, const S����<i, j> &p2);
	template<unsigned int i, unsigned int j> static void f����ת��(S����<i, j> &po, const S����<j, i> &pi);
	template<unsigned int i> static float f������ʽ(S����<i, i> &pi);
};
//���׾���
struct S����2 : public S����<2, 2> {
	typedef S����<2, 2> t����;
	using t����::t����;
	//������
	S����2 &operator +=(const S����2 &);
	S����2 &operator *=(const S����2 &);
	S����2 operator +(const S����2 &) const;
	S����2 operator *(const S����2 &) const;
	//��̬����
	static S����2 fc��λ();
	static S����2 fc��ת(const float &);
	static S����2 fc����(const float &, const float &);
	static S����2 fc�б�(const float &, const float &);
	static S����2 fc��ת(const float &, const float &);
	static S����2 fc����(const t����<float> &);
};
//�Ľ׾���
struct S����4 : public S���� < 4, 4 > {
	typedef S����<4, 4> t����;
	static const S����4 c��λ;
	//���캯��
	S����4();
	//������
	S����4 &operator +=(const S����4 &);
	S����4 &operator *=(const S����4 &);
	S����4 operator +(const S����4 &) const;
	S����4 operator *(const S����4 &) const;
	//��̬����
	static S����4 fc��λ();
	static S����4 fc��x��ת(const float &);
	static S����4 fc��y��ת(const float &);
	static S����4 fc��z��ת(const float &);
	static S����4 fc��ת(const float &x, const float &y, const float &z);
	static S����4 fc��l(const S����3 &λ��, const S����3 &Ŀ��, const S����3 &�Ϸ�);
	static S����4 fc��r(const S����3 &λ��, const S����3 &Ŀ��, const S����3 &�Ϸ�);
	static S����4 fc����l(const S����3 &λ��, const S����3 &����, const S����3 &�Ϸ�);
	static S����4 fc����r(const S����3 &λ��, const S����3 &����, const S����3 &�Ϸ�);
	static S����4 fc͸��ͶӰ�ӽ�l(const float &��Χ, const float &��߱�, const float &���ü���, const float &Զ�ü���);
	static S����4 fc͸��ͶӰ�ӽ�r(const float &��Χ, const float &��߱�, const float &���ü���, const float &Զ�ü���);
	static S����4 fc͸��ͶӰ����l(float ��, float ��, float ���ü���, float Զ�ü���);
	static S����4 fc͸��ͶӰ����r(float ��, float ��, float ���ü���, float Զ�ü���);
	static S����4 fc͸��ͶӰ�Զ���l(float ��, float ��, float ��, float ��, float ���ü���, float Զ�ü���);
	static S����4 fc͸��ͶӰ�Զ���r(float ��, float ��, float ��, float ��, float ���ü���, float Զ�ü���);
	static S����4 fcת��(const S����4 &);
	static S����4 fcƽ��(const float &x, const float &y, const float &z);
	static S����4 fc����(const float &x, const float &y, const float &z);
	static S����4 fc���淴��(const Sƽ�淽�� &);
	static S����4 fc��Ӱ(const Sƽ�淽�� &ƽ��, const S����4 &�ⷽ��);
};


//=============================================================================
// ����
//=============================================================================
template<unsigned int ��, unsigned int ��> S����<��, ��>::S����() :mֵ{0} {}
template<unsigned int ��, unsigned int ��> S����<��, ��>::S����(std::initializer_list<float> p) {
	for (int i = 0; i != ��; ++i) {
		for (int j = 0; j != ��; ++j) {
			const int n = i * �� + j;
			assert(n <= p.size());
			mֵ[i][j] = p[n];
		}
	}
}
template<unsigned int ��, unsigned int ��> void C����::f�վ���(S����<��, ��> &a����) {
	f�վ���_(*a����.mֵ, a����.c��, a����.c��);
}
template<unsigned int һ, unsigned int ��, unsigned int ��> void C����::f�������(S����<һ, ��> &a���, const S����<һ, ��> &a����0, const S����<��, ��> &a����1) {
	f�������_(*a���.mֵ, *a����0.mֵ, *a����1.mֵ, һ, ��, ��);
}
template<unsigned int һ> void C����::f��λ����(S����<һ, һ> &a����) {
	f��λ����_(*a����.mֵ, һ);
}
template<unsigned int i, unsigned int j> void C����::f�������(S����<i, j> &a���, const S����<i, j> &a����0, const S����<i, j> &a����1) {
	f�������_(*a���.mֵ, *a����0.mֵ, *a����1.mֵ, i, j);
}
template<unsigned int i, unsigned int j>  void C����::f����ת��(S����<i, j> &a���, const S����<j, i> &a����) {
	f����ת��_(*a���.mֵ, *a����.mֵ, i, j);
}
template<unsigned int i> float C����::f������ʽ(S����<i, i> &a����) {
	return f������ʽ_(a����.mֵ, i);
}

}	//namespace cflw::��ѧ