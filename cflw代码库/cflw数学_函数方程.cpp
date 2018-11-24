#include <assert.h>
#include "cflw��ѧ.h"
#include "cflw��ѧ_��������.h"
#include "cflw��ѧ_����.h"
namespace cflw::��ѧ {
//==============================================================================
// ���κ���
//==============================================================================
S���κ���::S���κ���() : a(0), b(0), c(0) {}
S���κ���::S���κ���(const S����2 &p1, const S����2 &p2, const S����2 &p3) {
	fs����(p1, p2, p3);
}
S���κ��� &S���κ���::fs����(const S����2 &p1, const S����2 &p2, const S����2 &p3) {
	a = ((p1.y - p2.y) * (p2.x - p3.x) - (p2.y - p3.y) * (p1.x - p2.x)) /
		((p1.x*p1.x - p2.x*p2.x) * (p2.x - p3.x) - (p2.x*p2.x - p3.x*p3.x) * (p1.x - p2.x));
	b = (p1.y - p2.y - a * (p1.x*p1.x - p2.x*p2.x)) / (p1.x - p2.x);
	c = p1.y - a * p1.x * p1.x - b * p1.x;
	assert(abs(f��y(p3.x) - p3.y) < 0.0001f);	//����
	return *this;
}
float S���κ���::f��ֱ����(const S����2 &p) const {
	return p.y - f��y(p.x);
}
float S���κ���::f��y(float x) const {
	return	a * x * x + b * x + c;
}
//==============================================================================
// ֱ�߷���
//==============================================================================
Sֱ�߷���::Sֱ�߷���() :
	a(0), b(0), c(0) {}
Sֱ�߷���::Sֱ�߷���(float A, float B, float C) :
	a{A}, b{B}, c{C} {}
Sֱ�߷��� Sֱ�߷���::fc��б(const S����2 &p, const float &k) {
	const float a = k;
	const float b = -1;
	const float c = k * p.x + p.y;
	return {a, b, c};
}
Sֱ�߷��� Sֱ�߷���::fc����(const S����2 &p1, const S����2 &p2) {
	const float a = p2.y - p1.y;
	const float b = p1.x - p2.x;
	const float c = -p1.x * a - p2.y * b;
	return {a, b, c};
}
Sֱ�߷��� Sֱ�߷���::fcб��(const float &k, const float &y) {
	const float a = k;
	const float b = -1;
	const float c = y;
	return{a, b, c};
}
Sֱ�߷��� Sֱ�߷���::fc�ؾ�(const float &x, const float &y) {
	const float a = x;
	const float b = y;
	const float c = -1;
	return{a, b, c};
}
Sֱ�߷��� Sֱ�߷���::fcһ��(const float &A, const float &B, const float &C) {
	const float a = A;
	const float b = B;
	const float c = C;
	return{a, b, c};
}
Sֱ�߷��� Sֱ�߷���::fc�㷨(const S����2 &p, const S����2 &n) {
	const float a = n.x;
	const float b = n.y;
	const float c = -n.x * p.x - n.y * p.y;
	return{a, b, c};
}
Sֱ�߷��� Sֱ�߷���::fc����(const S����2 &p, const float &d) {
	return fc�㷨(p, S����2::fc����r(1, d + (float)c���));
}
float Sֱ�߷���::fgб��() const {
	return a / b;
}
float Sֱ�߷���::f�������(const S����2 &p) const {
	return abs(a * p.x + b * p.y + c) / sqrt(a*a + b * b);
}
Sֱ�߷��� Sֱ�߷���::fƽ��(const S����2 &a����) const {
	Sֱ�߷��� v = *this;
	v.c -= v.a * a����.x;
	v.c -= v.b * a����.y;
	return v;
}
float Sֱ�߷���::f��x(const float &y) const {
	assert(a != 0);
	return (b * y + c) / -a;
}
float Sֱ�߷���::f��y(const float &x) const {
	assert(b != 0);
	return (a * x + c) / -b;
}
bool Sֱ�߷���::fƽ��(const Sֱ�߷��� &aֱ�߷���) const {
	if (a == 0) return aֱ�߷���.a == 0;
	else return (b / a) == (aֱ�߷���.b / aֱ�߷���.a);
}
float Sֱ�߷���::fg����r() const {
	return C�Ƕȼ���<float>::c����.fȡ��(atan2(b, a) + (float)c���);
}
float Sֱ�߷���::fg����d() const {
	return fg����r() * (float)c���ȵ���;
}
S����2 Sֱ�߷���::f����(const Sֱ�߷��� &aֱ�߷���) const {
	const float y = (aֱ�߷���.a*c - a * aֱ�߷���.c) / (aֱ�߷���.b*a - b * aֱ�߷���.a);
	const float x = f��x(y);
	return S����2(x, y);
}
S����2 Sֱ�߷���::fg������() const {
	const float m = hypotf(a, b);
	return S����2(a / m, b / m);
}
bool Sֱ�߷���::f��x��(int p) const {
	if (a == 0) {
		if (p == 0)
			return true;
		else
			return fȡ����(c) == fȡ����(p);
	} else if (b == 0) {
		return c == 0;
	} else {
		if (p == 0)
			return true;
		else
			return -c / a * fȡ����(p) > 0;
	}
}
bool Sֱ�߷���::f��y��(int p) const {
	if (a == 0) {
		return c == 0;
	} else if (b == 0) {
		if (p == 0)
			return true;
		else
			return fȡ����(c) == fȡ����(p);
	} else {
		if (p == 0)
			return true;
		else
			return -c / b * fȡ����(p) > 0;
	}
}
bool Sֱ�߷���::fiƽ��x��() const {
	return b == 0;
}
bool Sֱ�߷���::fiƽ��y��() const {
	return a == 0;
}
bool Sֱ�߷���::fi��ֱx��() const {
	return a == 0;
}
bool Sֱ�߷���::fi��ֱy��() const {
	return b == 0;
}
//==============================================================================
// ֱ�߷���3d
//==============================================================================
Sֱ�߷���3::Sֱ�߷���3() :x(), y(), z() {}
Sֱ�߷���3 &Sֱ�߷���3::fs����(const S����3 &p1, const S����3 &p2) {
	x[0] = p1.x - p2.x;
	x[1] = p2.x;
	y[0] = p1.y - p2.y;
	y[1] = p2.y;
	z[0] = p1.z - p2.z;
	z[1] = p2.z;
	return *this;
}
Sֱ�߷���3 &Sֱ�߷���3::fs��һ() {
	const float v = fgģ();
	x[0] /= v;
	y[0] /= v;
	z[0] /= v;
	return *this;
}
bool Sֱ�߷���3::f�ཻ�ж�(const Sֱ�߷���3 &aֱ�߷���, S����3 *a���) const {
	const float v[2] = {fgģ(), aֱ�߷���.fgģ()};
	auto f = [](float *p1, float *p2)->float {
		return (p2[1] - p1[1]) / (p1[0] - p2[2]);
	};
	if (x[0] / v[0] == aֱ�߷���.x[0] / v[1]) {
		return true;
	} else if (y[0] / v[0] == aֱ�߷���.y[0] / v[1]) {
		return true;
	} else if (z[0] / v[0] == aֱ�߷���.z[0] / v[1]) {
		return true;
	}
	return false;
}
float Sֱ�߷���3::fgģ() const {
	return sqrt(x[0] * x[0] + y[0] * y[0] + z[0] * z[0]);
}
//==============================================================================
// ƽ�淽��
//==============================================================================
Sƽ�淽��::Sƽ�淽��() :a(0), b(0), c(0), d(0) {}
Sƽ�淽�� &Sƽ�淽��::fs����(const S����3 &p1, const S����3 &p2, const S����3 &p3) {
	return fs�㷨(p1, (p1 - p2).f���(p2 - p3));
}
Sƽ�淽�� &Sƽ�淽��::fs�㷨(const S����3 &p, const S����3 &n) {
	a = n.x;
	b = n.y;
	c = n.z;
	d = -n.x * p.x - n.y * p.y - n.z * p.z;
	return *this;
}
Sƽ�淽�� &Sƽ�淽��::fsһ��(float A, float B, float C, float D) {
	a = A;
	b = B;
	c = C;
	d = D;
	return *this;
}
S����3 Sƽ�淽��::fg��() const {
	return S����3(a, b, c);
}
//==============================================================================
// ָ������
//==============================================================================
Sָ������::Sָ������() :a(0), b(0), c(0), d(0) {}
float Sָ������::f��y(const float &x) const {
	return a * pow(b, x + c) + d;
}
Sָ������ &Sָ������::fsԭ��(const S����2 &o, const S����2 &p1, const S����2 &p2) {
	c = -o.x;
	d = o.y;
	const float v1 = (p1.y - d) / (p2.y - d);
	const float v2 = 1 / (p1.x - p2.x);
	const float v���� = ((p1.y - d > 0) && (p2.y - d > 0)) ? 1.f : -1.f;
	b = pow(v1, v2);
	a = (p1.y - d) / pow(b, p1.x + c) * v����;
	assert(abs(f��y(p2.x) - p2.y) < 0.001f);	//����
	return *this;
}

}