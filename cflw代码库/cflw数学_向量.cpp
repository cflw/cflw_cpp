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
	const float r = a���� / 180.f * c��<float>;
	return {cos(r) * a��С, sin(r) * a��С};
}
S����2 S����2::fc��ͬ(const float &a) {
	return {a, a};
}
S����2 S����2::fc��������(float a��, float a��, float a��, float a��) {
	return {(a�� + a��) / 2, (a�� + a��) / 2};
}
S����2 S����2::fc���γߴ�(float a��, float a��, float a��, float a��) {
	return {a�� - a��, a�� - a��};
}
S����2 S����2::fc���ΰ�ߴ�(float a��, float a��, float a��, float a��) {
	return {(a�� - a��) / 2, (a�� - a��) / 2};
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
S����2 &S����2::operator *= (const t����<float> &_) {
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
S����2 S����2::operator *(const t����<float> &_) const {
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
bool S����2::operator ==(const S����2 &a) const {
	return (x == a.x) && (y == a.y);
}
bool S����2::operator !=(const S����2 &a) const {
	return (x != a.x) || (y != a.y);
}
//���ӱȽ�
bool S����2::fȫС��(const S����2 &a) const {
	return (x < a.x) && (y < a.y);
}
bool S����2::fȫС�ڵ���(const S����2 &a) const {
	return (x <= a.x) && (y <= a.y);
}
bool S����2::fȫ����(const S����2 &a) const {
	return (x > a.x) && (y > a.y);
}
bool S����2::fȫ���ڵ���(const S����2 &a) const {
	return (x >= a.x) && (y >= a.y);
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
float S����2::fg���ݱ�() const {
	return x / y;
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
	const float r = p * c�ȵ�����<float>;
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
S����2 S����2::f��תr(const float &a�Ƕ�) const {
	const float s = sin(a�Ƕ�);
	const float c = cos(a�Ƕ�);
	return S����2{x * c - y * s, x * s + y * c};
}
S����2 S����2::f��תd(const float &a�Ƕ�) const {
	return f��תr(a�Ƕ� * c�ȵ�����<float>);
}
S����2 S����2::f�Ƶ���תr(const S����2 &a����, const float &a�Ƕ�) const {
	return (*this - a����).f��תr(a�Ƕ�) += a����;
}
S����2 S����2::f�Ƶ���תd(const S����2 &a����, const float &a�Ƕ�) const {
	return f�Ƶ���תr(a����, a�Ƕ� * c�ȵ�����<float>);
}
float S����2::f�������(const S����2 &a) const {
	const float _x = a.x - x;
	const float _y = a.y - y;
	return sqrt(_x*_x + _y * _y);
}
S����2 S����2::f��������(const S����2 &a) const {
	return S����2{a.x - x, a.y - y};
}
S����2 S����2::f���㷽λr(const S����2 &a��, const float &a����) const {
	const S����2 v�� = f��������(a��);
	return v��.f��תr(-a����);
}
S����2 S����2::f���㷽λd(const S����2 &a��, const float &a����) const {
	return f���㷽λr(a��, a���� * c�ȵ�����<float>);
}
float S����2::f���(const S����2 &a) const {
	return x * a.x + y * a.y;
}
S����2 &S����2::fs���Խ���(const S����2 &a, const float &a����) {
	S����2 v = a - *this;
	if (v.fg��С() <= a����)
		return *this = a;
	v.fs��С(a����);
	return *this += v;
}
S����2 S����2::f���Խ���(const S����2 &a, const float &a����) const {
	S����2 v = a - *this;
	if (v.fg��С() <= a����)
		return a;
	v.fs��С(a����);
	return *this + v;
}
S����2 &S����2::fs��������(const S����2 &a, const float &a����, const float &a��С, const float &a���) {
	S����2 v = (a - *this) * a����;
	const float vģ = v.fg��С();
	if (vģ == 0)
		return *this;
	if (vģ < a��С)
		v.fs��С(a��С);
	else if (vģ > a���)
		v.fs��С(a���);
	return *this += v;
}
S����2 S����2::f��������(const S����2 &a, const float &a����, const float &a��С, const float &a���) const {
	S����2 v = (a - *this) * a����;
	const float vģ = v.fg��С();
	if (vģ == 0)
		return *this;
	if (vģ < a��С)
		v.fs��С(a��С);
	else if (vģ > a���)
		v.fs��С(a���);
	return *this + v;
}
S����2 S����2::f����(const Sֱ�߷��� &aֱ�߷���) const {
	assert(aֱ�߷���.a != 0 || aֱ�߷���.b != 0);
	S����2 v = *this;
	if (aֱ�߷���.a == 0) {//ֱ��ƽ����y��
		const float d = -aֱ�߷���.c / aֱ�߷���.b;
		v.x = ��ѧ::f����(v.x, d);
	} else if (aֱ�߷���.b == 0) {//ֱ��ƽ����x��
		const float d = -aֱ�߷���.c / aֱ�߷���.a;
		v.y = ��ѧ::f����(v.y, d);
	} else {
		const float v2d = aֱ�߷���.f�������(*this);
		const float mб = hypotf(aֱ�߷���.a, aֱ�߷���.b);
		v.x = x - aֱ�߷���.a / mб * v2d;
		v.y = y - aֱ�߷���.b / mб * v2d;
	}
	return v;
}
S����2 S����2::f����(const float &a) const {
	return S����2::fc����r(fg��С(), ��ѧ::f����(fg����r(), a));
}
S����2 S����2::f����(const SԲ�� &a) const {
	const S����2 m��� = *this - a.m����;
	const float m���� = m���.fg��С();
	const float m���� = m���.fg����r();
	return fc����r(��ѧ::f����(m����, a.m�뾶), m����);
}
S����2 S����2::f����(const float &a) const {
	return{��ѧ::f����(x, a), ��ѧ::f����(y, a)};
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
S����2 S����2::f������(const S����2 &a) const {
	return {x * a.x, y * a.y};
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
S����3 &S����3::fs��С(const float &a) {
	*this = fg��һ() / a;
	return *this;
}
float S����3::f���(const S����3 &a) const {
	return x * a.x + y * a.y + z * a.z;
}
S����3 S����3::f���(const S����3 &a) const {
	return S����3(
		y * a.z - z * a.y,
		z * a.x - x * a.z,
		x * a.y - y * a.x);
}
S����3 &S����3::fs(const float &a) {
	x = y = z = a;
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
S����4 S����4::operator *(const S����4 &a) const {
	S����4 v;
	for (int i = 0; i != 4; ++i)
		for (int j = 0; j != 4; ++j)
			v.mֵ[i] += a.mֵ[i][j] * mֵ[j];
	return v;
}

}