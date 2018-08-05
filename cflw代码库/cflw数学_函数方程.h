#pragma once
namespace cflw::��ѧ {
struct S����2;
struct S����3;
//=============================================================================
// �����ͷ���
//=============================================================================
struct S���κ��� {
	float a, b, c;	// y = a * x^2 + b * x + c
	S���κ���();
	S���κ���(const S����2 &, const S����2 &, const S����2 &);
	S���κ��� &fs(const S����2 &, const S����2 &, const S����2 &);
	float f��y(float) const;//y=f(x)
	float f��ֱ����(const S����2 &) const;//p.y-f(p.x)
};
struct Sֱ�߷��� {
	float a, b, c;	// a*x + b*y + c = 0
	Sֱ�߷���();
	Sֱ�߷���(float, float, float);
	static Sֱ�߷��� fc��б(const S����2 &, const float &);
	static Sֱ�߷��� fc����(const S����2 &, const S����2 &);
	static Sֱ�߷��� fcб��(const float &, const float &);
	static Sֱ�߷��� fc�ؾ�(const float &, const float &);
	static Sֱ�߷��� fcһ��(const float &, const float &, const float &);
	static Sֱ�߷��� fc�㷨(const S����2 &, const S����2 &);
	static Sֱ�߷��� fc����(const S����2 &, const float &);
	float f�������(const S����2 &) const;
	float fgб��() const;
	Sֱ�߷��� fƽ��(const S����2 &) const;
	float f��x(const float &) const;
	float f��y(const float &) const;
	bool fƽ��(const Sֱ�߷��� &) const;
	float fg����r() const;
	float fg����d() const;
	S����2 f����(const Sֱ�߷��� &) const;
	S����2 fg������() const;
	bool f��x��(int) const;
	bool f��y��(int) const;
};
struct Sֱ�߷���3 {
	float x[2], y[2], z[2];//�������̵���ʽ
	Sֱ�߷���3();
	Sֱ�߷���3 &fs����(const S����3 &, const S����3 &);
	Sֱ�߷���3 &fs��һ();
	bool f�ཻ�ж�(const Sֱ�߷���3 &, S����3 * = nullptr) const;
	float fgģ() const;
};
struct Sƽ�淽�� {
	float a, b, c, d;
	Sƽ�淽��();
	Sƽ�淽�� &fs����(const S����3 &, const S����3 &, const S����3 &);
	Sƽ�淽�� &fs�㷨(const S����3 &, const S����3 &);
	Sƽ�淽�� &fsһ��(float, float, float, float);
	S����3 fg��() const;
};
struct Sָ������ {
	float a, b, c, d;	// y = a * b^(x + c) + d
	Sָ������();
	Sָ������ &fsԭ��(const S����2 &, const S����2 &, const S����2 &);
	float f��y(const float &) const;
};

}