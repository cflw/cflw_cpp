#include <assert.h>
#include "cflw��ѧ.h"
#include "cflw��ѧ_����.h"
#include "cflw��ѧ_��������.h"
#include "cflw��ѧ_ƽ�漸��.h"
#include "cflw��ѧ_����.h"
namespace cflw::��ѧ {
template<> S����2 f����ֵ<S����2>(const S����2 &_) {
	return {abs(_.x), abs(_.y)};
}
template<> S����3 f����ֵ<S����3>(const S����3 &_) {
	return S����3(abs(_.x), abs(_.y), abs(_.z));
}
//=============================================================================
// ����
//=============================================================================
//����
const S����2 S����2::c��{0, 0};
const S����2 S����2::cһ{1, 1};
//���캯��
S����2::S����2(float X, float Y):
	x(X), y(Y) {
}
S����2 S����2::fc����r(const float &a��С, const float &a����) {
	return {cos(a����) * a��С, sin(a����) * a��С};
}
S����2 S����2::fc����d(const float &a��С, const float &a����) {
	const float r = a���� / 180.f * (float)c��;
	return {cos(r) * a��С, sin(r) * a��С};
}
S����2 S����2::fc��ͬ(const float &p) {
	return {p, p};
}
//��ֵ������
S����2& S����2::operator +=(const S����2 &_) {
	x += _.x;
	y += _.y;
	return *this;
}
S����2& S����2::operator -=(const S����2 &_) {
	x -= _.x;
	y -= _.y;
	return *this;
}
S����2& S����2::operator *=(const float &_) {
	x *= _;
	y *= _;
	return *this;
}
S����2& S����2::operator /=(const float &_) {
	x /= _;
	y /= _;
	return *this;
}
S����2 &S����2::operator *= (const t���� &_) {
	const float vx = x, vy = y;
	x = vx * _._Val[0] - vy * _._Val[1];
	y = vy * _._Val[0] + vx * _._Val[1];
	return *this;
}
//�������������
S����2 S����2::operator +(const S����2 &_) const {
	return S����2(x + _.x, y + _.y);
}
S����2 S����2::operator -(const S����2 &_) const {
	return S����2(x - _.x, y - _.y);
}
S����2 S����2::operator *(const float &_) const {
	return S����2(x * _, y * _);
}
S����2 S����2::operator /(const float &_) const {
	return S����2(x / _, y / _);
}
S����2 S����2::operator *(const t���� &_) const {
	S����2 v = *this;
	v.x = x * _.real() - y * _.imag();
	v.y = y * _.real() + x * _.imag();
	return v;
}
//
S����2 S����2::operator -() const {
	S����2 v = *this;
	v.x = -v.x;
	v.y = -v.y;
	return v;
}
bool S����2::operator ==(const S����2 &p) const {
	return (x == p.x) && (y == p.y);
}
bool S����2::operator !=(const S����2 &p) const {
	return (x != p.x) || (y != p.y);
}
//���ӱȽ�
bool S����2::fȫС��(const S����2 &p) const {
	return (x < p.x) && (y < p.y);
}
bool S����2::fȫС�ڵ���(const S����2 &p) const {
	return (x <= p.x) && (y <= p.y);
}
bool S����2::fȫ����(const S����2 &p) const {
	return (x > p.x) && (y > p.y);
}
bool S����2::fȫ���ڵ���(const S����2 &p) const {
	return (x >= p.x) && (y >= p.y);
}
bool S����2::fi��() const {
	return (x == 0) && (y == 0);
}
//��ͨ����
float S����2::fg��С() const {
	return hypotf(x, y);
}
float S����2::fgƽ��() const {
	return x * x + y * y;
}
float S����2::fg����d() const {
	return C�Ƕȼ���<float>::c��.f����(x, y);
}
float S����2::fg����r() const {
	return C�Ƕȼ���<float>::c����.f����(x, y);
}
float S����2::fg�н�r(const S����2 &_) const {
	return C�Ƕȼ���<float>::c����.fȡ��(fg����r() - _.fg����r());
}
S����2 S����2::fg����() const {
	return S����2(-x, -y);
}
S����2 S����2::fg��һ() const {
	float vģ = fg��С();
	return S����2(x / vģ, y / vģ);
}
S����2 &S����2::fs(const float &XY) {
	x = y = XY;
	return *this;
}
S����2 &S����2::fs(const float &X, const float &Y) {
	x = X;
	y = Y;
	return *this;
}
S����2 &S����2::fs��С(const float &p) {
	float vģ = fg��С();
	assert(vģ != 0);
	x = x / vģ * p;
	y = y / vģ * p;
	return *this;
}
S����2 &S����2::fs����(const float &p) {
	const float vģ = fg��С();
	x = cos(p) * vģ;
	y = sin(p) * vģ;
	return *this;
}
S����2 &S����2::fs����d(const float &p) {
	const float vģ = fg��С();
	const float r = p * c�ȵ�����;
	x = cos(r) * vģ;
	y = sin(r) * vģ;
	return *this;
}
S����2 &S����2::fs��תr(const float &p) {
	*this = f��תr(p);
	return *this;
}
S����2 &S����2::fs��תd(const float &p) {
	*this = f��תd(p);
	return *this;
}
S����2 S����2::f��С(const float &p) const {
	return S����2(*this).fs��С(p);
}
S����2 S����2::f����r(const float &p) const {
	return S����2(*this).fs����(p);
}
S����2 S����2::f����d(const float &p) const {
	return S����2(*this).fs����d(p);
}
float S����2::f���㷽��r(const S����2 &_) const {
	const S����2 v = _ - *this;
	return C�Ƕȼ���<float>::c����.f����(v.x, v.y);
}
float S����2::f���㷽��d(const S����2 &_) const {
	const S����2 v = _ - *this;
	return C�Ƕȼ���<float>::c��.f����(v.x, v.y);
}
S����2 S����2::f��תr(const float &p�Ƕ�) const {
	const float s = sin(p�Ƕ�);
	const float c = cos(p�Ƕ�);
	return S����2{x * c - y * s, x * s + y * c};
}
S����2 S����2::f��תd(const float &p�Ƕ�) const {
	return f��תr(p�Ƕ� * (float)c�ȵ�����);
}
S����2 S����2::f�Ƶ���תr(const S����2 &p����, const float &p�Ƕ�) const {
	return (*this - p����).f��תr(p�Ƕ�) += p����;
}
S����2 S����2::f�Ƶ���תd(const S����2 &p����, const float &p�Ƕ�) const {
	return f�Ƶ���תr(p����, p�Ƕ� * (float)c�ȵ�����);
}
float S����2::f�������(const S����2 &p) const {
	const float _x = p.x - x;
	const float _y = p.y - y;
	return sqrt(_x*_x + _y * _y);
}
S����2 S����2::f��������(const S����2 &p) const {
	return S����2{p.x - x, p.y - y};
}
S����2 S����2::f���㷽λr(const S����2 &p��, const float &a����) const {
	const S����2 v�� = f��������(p��);
	return v��.f��תr(-a����);
}
S����2 S����2::f���㷽λd(const S����2 &p��, const float &a����) const {
	return f���㷽λr(p��, a���� * (float)c�ȵ�����);
}
float S����2::f���(const S����2 &p) const {
	return x * p.x + y * p.y;
}
S����2 &S����2::fs���Խ���(const S����2 &p, const float &p����) {
	S����2 v = p - *this;
	if (v.fg��С() <= p����)
		return *this = p;
	v.fs��С(p����);
	return *this += v;
}
S����2 S����2::f���Խ���(const S����2 &p, const float &p����) const {
	S����2 v = p - *this;
	if (v.fg��С() <= p����)
		return p;
	v.fs��С(p����);
	return *this + v;
}
S����2 &S����2::fs��������(const S����2 &p, const float &p����, const float &p��С, const float &p���) {
	S����2 v = (p - *this) * p����;
	const float vģ = v.fg��С();
	if (vģ == 0)
		return *this;
	if (vģ < p��С)
		v.fs��С(p��С);
	else if (vģ > p���)
		v.fs��С(p���);
	return *this += v;
}
S����2 S����2::f��������(const S����2 &p, const float &p����, const float &p��С, const float &p���) const {
	S����2 v = (p - *this) * p����;
	const float vģ = v.fg��С();
	if (vģ == 0)
		return *this;
	if (vģ < p��С)
		v.fs��С(p��С);
	else if (vģ > p���)
		v.fs��С(p���);
	return *this + v;
}
S����2 S����2::f����(const Sֱ�߷��� &p) const {
	assert(p.a != 0 || p.b != 0);
	S����2 v = *this;
	if (p.a == 0) {//ֱ��ƽ����y��
		const float d = -p.c / p.b;
		v.x = ��ѧ::f����(v.x, d);
	} else if (p.b == 0) {//ֱ��ƽ����x��
		const float d = -p.c / p.a;
		v.y = ��ѧ::f����(v.y, d);
	} else {
		const float v2d = p.f�������(*this);
		const float mб = hypotf(p.a, p.b);
		v.x = x - p.a / mб * v2d;
		v.y = y - p.b / mб * v2d;
	}
	return v;
}
S����2 S����2::f����(const float &p) const {
	return S����2::fc����r(fg��С(), ��ѧ::f����(fg����r(), p));
}
S����2 S����2::f����(const SԲ�� &p) const {
	const S����2 m��� = *this - p.m����;
	const float m���� = m���.fg��С();
	const float m���� = m���.fg����r();
	return fc����r(��ѧ::f����(m����, p.m�뾶), m����);
}
S����2 S����2::f����(const float &p) const {
	return{��ѧ::f����(x, p), ��ѧ::f����(y, p)};
}
S����2 S����2::fֱ������(float sx, float sy) const {
	return{fֱ������x(x, sx), fֱ������y(y, sy)};
}
S����2 S����2::f��������(float sx, float sy) const {
	return{f��������x(x, sx), f��������y(y, sy)};
}
S����2 S����2::f������(float a, float b) const {
	return {x * a, y * b};
}
S����2 S����2::f������(const S����2 &p) const {
	return {x * p.x, y * p.y};
}
bool S����2::fi�������() const {
	return x == y;
}
//ת��
S����3 S����2::ft����3(float z)const {
	return S����3(x, y, z);
}
S����4 S����2::ft����4(float z, float w) const {
	return S����4(x, y, z, w);
}
//=============================================================================
// ����3
//=============================================================================
const S����3 S����3::c��{0, 0, 0};
const S����3 S����3::cһ{1, 1, 1};
S����3::S����3() : x(0), y(0), z(0) {}
S����3::S����3(const float &X, const float &Y, const float &Z) : x(X), y(Y), z(Z) {}
//��ֵ������
S����3& S����3::operator +=(const S����3 &_) {
	x += _.x;
	y += _.y;
	z += _.z;
	return *this;
}
S����3& S����3::operator -=(const S����3 &_) {
	x -= _.x;
	y -= _.y;
	z -= _.z;
	return *this;
}
S����3& S����3::operator *=(const float &_) {
	x *= _;
	y *= _;
	z *= _;
	return *this;
}
S����3& S����3::operator /=(const float &_) {
	x /= _;
	y /= _;
	z /= _;
	return *this;
}
//�������������
S����3 S����3::operator +(const S����3 &_) const {
	return S����3(x + _.x, y + _.y, z + _.z);
}
S����3 S����3::operator -(const S����3 &_) const {
	return S����3(x - _.x, y - _.y, z - _.z);
}
S����3 S����3::operator *(const float &_) const {
	return S����3(x * _, y * _, z * _);
}
S����3 S����3::operator /(const float &_) const {
	return S����3(x / _, y / _, z / _);
}
//
float S����3::fg��С() const {
	return sqrt(x * x + y * y + z * z);
}
float S����3::fgƽ��() const {
	return x * x + y * y + z * z;
}
S����3 S����3::fg����() const {
	return S����3(-x, -y, -z);
}
S����3 S����3::fg��һ() const {
	const float vģ = fg��С();
	return S����3(x / vģ, y / vģ, z / vģ);
}
S����3 &S����3::fs��С(const float &p) {
	*this = fg��һ() / p;
	return *this;
}
float S����3::f���(const S����3 &p) const {
	return x * p.x + y * p.y + z * p.z;
}
S����3 S����3::f���(const S����3 &p) const {
	return S����3(
		y * p.z - z * p.y,
		z * p.x - x * p.z,
		x * p.y - y * p.x);
}
S����3 &S����3::fs(const float &p) {
	x = y = z = p;
	return *this;
}
S����3 &S����3::fs(const float &X, const float &Y, const float &Z) {
	x = X;
	y = Y;
	z = Z;
	return *this;
}
//ת��
S����2 S����3::ft����2() const {
	return S����2(x, y);
}
S����4 S����3::ft����4(const float &w) const {
	return S����4(x, y, z, w);
}
//=============================================================================
// ����4
//=============================================================================
S����4::S����4() :x(0), y(0), z(0), w(0) {}
S����4::S����4(const float &X, const float &Y, const float &Z, const float &W) : x(X), y(Y), z(Z), w(W) {}
S����3 S����4::ft����3() const {
	return S����3(x, y, z);
}
S����4 S����4::operator *(const S����4 &p) const {
	S����4 _;
	for (int i = 0; i != 4; ++i)
		for (int j = 0; j != 4; ++j)
			_.m[i] += p.m[i][j] * m[j];
	return _;
}

}