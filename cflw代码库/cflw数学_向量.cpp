#include <assert.h>
#include "cflw数学.h"
#include "cflw数学_向量.h"
#include "cflw数学_函数方程.h"
#include "cflw数学_平面几何.h"
#include "cflw数学_矩阵.h"
namespace cflw::数学 {
template<> S向量2 f绝对值<S向量2>(const S向量2 &_) {
	return {abs(_.x), abs(_.y)};
}
template<> S向量3 f绝对值<S向量3>(const S向量3 &_) {
	return S向量3(abs(_.x), abs(_.y), abs(_.z));
}
//=============================================================================
// 向量
//=============================================================================
//常量
const S向量2 S向量2::c零{0, 0};
const S向量2 S向量2::c一{1, 1};
//构造函数
S向量2::S向量2(float X, float Y):
	x(X), y(Y) {
}
S向量2 S向量2::fc方向r(const float &a大小, const float &a方向) {
	return {cos(a方向) * a大小, sin(a方向) * a大小};
}
S向量2 S向量2::fc方向d(const float &a大小, const float &a方向) {
	const float r = a方向 / 180.f * (float)cπ;
	return {cos(r) * a大小, sin(r) * a大小};
}
S向量2 S向量2::fc相同(const float &p) {
	return {p, p};
}
//赋值操作符
S向量2& S向量2::operator +=(const S向量2 &_) {
	x += _.x;
	y += _.y;
	return *this;
}
S向量2& S向量2::operator -=(const S向量2 &_) {
	x -= _.x;
	y -= _.y;
	return *this;
}
S向量2& S向量2::operator *=(const float &_) {
	x *= _;
	y *= _;
	return *this;
}
S向量2& S向量2::operator /=(const float &_) {
	x /= _;
	y /= _;
	return *this;
}
S向量2 &S向量2::operator *= (const t复数 &_) {
	const float vx = x, vy = y;
	x = vx * _._Val[0] - vy * _._Val[1];
	y = vy * _._Val[0] + vx * _._Val[1];
	return *this;
}
//四则运算操作符
S向量2 S向量2::operator +(const S向量2 &_) const {
	return S向量2(x + _.x, y + _.y);
}
S向量2 S向量2::operator -(const S向量2 &_) const {
	return S向量2(x - _.x, y - _.y);
}
S向量2 S向量2::operator *(const float &_) const {
	return S向量2(x * _, y * _);
}
S向量2 S向量2::operator /(const float &_) const {
	return S向量2(x / _, y / _);
}
S向量2 S向量2::operator *(const t复数 &_) const {
	S向量2 v = *this;
	v.x = x * _.real() - y * _.imag();
	v.y = y * _.real() + x * _.imag();
	return v;
}
//
S向量2 S向量2::operator -() const {
	S向量2 v = *this;
	v.x = -v.x;
	v.y = -v.y;
	return v;
}
bool S向量2::operator ==(const S向量2 &p) const {
	return (x == p.x) && (y == p.y);
}
bool S向量2::operator !=(const S向量2 &p) const {
	return (x != p.x) || (y != p.y);
}
//复杂比较
bool S向量2::f全小于(const S向量2 &p) const {
	return (x < p.x) && (y < p.y);
}
bool S向量2::f全小于等于(const S向量2 &p) const {
	return (x <= p.x) && (y <= p.y);
}
bool S向量2::f全大于(const S向量2 &p) const {
	return (x > p.x) && (y > p.y);
}
bool S向量2::f全大于等于(const S向量2 &p) const {
	return (x >= p.x) && (y >= p.y);
}
bool S向量2::fi零() const {
	return (x == 0) && (y == 0);
}
//普通函数
float S向量2::fg大小() const {
	return hypotf(x, y);
}
float S向量2::fg平方() const {
	return x * x + y * y;
}
float S向量2::fg方向d() const {
	return C角度计算<float>::c度.f方向(x, y);
}
float S向量2::fg方向r() const {
	return C角度计算<float>::c弧度.f方向(x, y);
}
float S向量2::fg夹角r(const S向量2 &_) const {
	return C角度计算<float>::c弧度.f取正(fg方向r() - _.fg方向r());
}
S向量2 S向量2::fg反向() const {
	return S向量2(-x, -y);
}
S向量2 S向量2::fg归一() const {
	float v模 = fg大小();
	return S向量2(x / v模, y / v模);
}
S向量2 &S向量2::fs(const float &XY) {
	x = y = XY;
	return *this;
}
S向量2 &S向量2::fs(const float &X, const float &Y) {
	x = X;
	y = Y;
	return *this;
}
S向量2 &S向量2::fs大小(const float &p) {
	float v模 = fg大小();
	assert(v模 != 0);
	x = x / v模 * p;
	y = y / v模 * p;
	return *this;
}
S向量2 &S向量2::fs方向(const float &p) {
	const float v模 = fg大小();
	x = cos(p) * v模;
	y = sin(p) * v模;
	return *this;
}
S向量2 &S向量2::fs方向d(const float &p) {
	const float v模 = fg大小();
	const float r = p * c度到弧度;
	x = cos(r) * v模;
	y = sin(r) * v模;
	return *this;
}
S向量2 &S向量2::fs旋转r(const float &p) {
	*this = f旋转r(p);
	return *this;
}
S向量2 &S向量2::fs旋转d(const float &p) {
	*this = f旋转d(p);
	return *this;
}
S向量2 S向量2::f大小(const float &p) const {
	return S向量2(*this).fs大小(p);
}
S向量2 S向量2::f方向r(const float &p) const {
	return S向量2(*this).fs方向(p);
}
S向量2 S向量2::f方向d(const float &p) const {
	return S向量2(*this).fs方向d(p);
}
float S向量2::f到点方向r(const S向量2 &_) const {
	const S向量2 v = _ - *this;
	return C角度计算<float>::c弧度.f方向(v.x, v.y);
}
float S向量2::f到点方向d(const S向量2 &_) const {
	const S向量2 v = _ - *this;
	return C角度计算<float>::c度.f方向(v.x, v.y);
}
S向量2 S向量2::f旋转r(const float &p角度) const {
	const float s = sin(p角度);
	const float c = cos(p角度);
	return S向量2{x * c - y * s, x * s + y * c};
}
S向量2 S向量2::f旋转d(const float &p角度) const {
	return f旋转r(p角度 * (float)c度到弧度);
}
S向量2 S向量2::f绕点旋转r(const S向量2 &p中心, const float &p角度) const {
	return (*this - p中心).f旋转r(p角度) += p中心;
}
S向量2 S向量2::f绕点旋转d(const S向量2 &p中心, const float &p角度) const {
	return f绕点旋转r(p中心, p角度 * (float)c度到弧度);
}
float S向量2::f到点距离(const S向量2 &p) const {
	const float _x = p.x - x;
	const float _y = p.y - y;
	return sqrt(_x*_x + _y * _y);
}
S向量2 S向量2::f到点向量(const S向量2 &p) const {
	return S向量2{p.x - x, p.y - y};
}
S向量2 S向量2::f到点方位r(const S向量2 &p点, const float &a方向) const {
	const S向量2 v点 = f到点向量(p点);
	return v点.f旋转r(-a方向);
}
S向量2 S向量2::f到点方位d(const S向量2 &p点, const float &a方向) const {
	return f到点方位r(p点, a方向 * (float)c度到弧度);
}
float S向量2::f点乘(const S向量2 &p) const {
	return x * p.x + y * p.y;
}
S向量2 &S向量2::fs线性渐变(const S向量2 &p, const float &p渐变) {
	S向量2 v = p - *this;
	if (v.fg大小() <= p渐变)
		return *this = p;
	v.fs大小(p渐变);
	return *this += v;
}
S向量2 S向量2::f线性渐变(const S向量2 &p, const float &p渐变) const {
	S向量2 v = p - *this;
	if (v.fg大小() <= p渐变)
		return p;
	v.fs大小(p渐变);
	return *this + v;
}
S向量2 &S向量2::fs倍数渐变(const S向量2 &p, const float &p渐变, const float &p最小, const float &p最大) {
	S向量2 v = (p - *this) * p渐变;
	const float v模 = v.fg大小();
	if (v模 == 0)
		return *this;
	if (v模 < p最小)
		v.fs大小(p最小);
	else if (v模 > p最大)
		v.fs大小(p最大);
	return *this += v;
}
S向量2 S向量2::f倍数渐变(const S向量2 &p, const float &p渐变, const float &p最小, const float &p最大) const {
	S向量2 v = (p - *this) * p渐变;
	const float v模 = v.fg大小();
	if (v模 == 0)
		return *this;
	if (v模 < p最小)
		v.fs大小(p最小);
	else if (v模 > p最大)
		v.fs大小(p最大);
	return *this + v;
}
S向量2 S向量2::f翻折(const S直线方程 &p) const {
	assert(p.a != 0 || p.b != 0);
	S向量2 v = *this;
	if (p.a == 0) {//直线平行于y轴
		const float d = -p.c / p.b;
		v.x = 数学::f翻折(v.x, d);
	} else if (p.b == 0) {//直线平行于x轴
		const float d = -p.c / p.a;
		v.y = 数学::f翻折(v.y, d);
	} else {
		const float v2d = p.f到点距离(*this);
		const float m斜 = hypotf(p.a, p.b);
		v.x = x - p.a / m斜 * v2d;
		v.y = y - p.b / m斜 * v2d;
	}
	return v;
}
S向量2 S向量2::f翻折(const float &p) const {
	return S向量2::fc方向r(fg大小(), 数学::f翻折(fg方向r(), p));
}
S向量2 S向量2::f翻折(const S圆形 &p) const {
	const S向量2 m相对 = *this - p.m坐标;
	const float m距离 = m相对.fg大小();
	const float m方向 = m相对.fg方向r();
	return fc方向r(数学::f翻折(m距离, p.m半径), m方向);
}
S向量2 S向量2::f对齐(const float &p) const {
	return{数学::f对齐(x, p), 数学::f对齐(y, p)};
}
S向量2 S向量2::f直角坐标(float sx, float sy) const {
	return{f直角坐标x(x, sx), f直角坐标y(y, sy)};
}
S向量2 S向量2::f窗口坐标(float sx, float sy) const {
	return{f窗口坐标x(x, sx), f窗口坐标y(y, sy)};
}
S向量2 S向量2::f分量乘(float a, float b) const {
	return {x * a, y * b};
}
S向量2 S向量2::f分量乘(const S向量2 &p) const {
	return {x * p.x, y * p.y};
}
bool S向量2::fi分量相等() const {
	return x == y;
}
//转换
S向量3 S向量2::ft向量3(float z)const {
	return S向量3(x, y, z);
}
S向量4 S向量2::ft向量4(float z, float w) const {
	return S向量4(x, y, z, w);
}
//=============================================================================
// 向量3
//=============================================================================
const S向量3 S向量3::c零{0, 0, 0};
const S向量3 S向量3::c一{1, 1, 1};
S向量3::S向量3() : x(0), y(0), z(0) {}
S向量3::S向量3(const float &X, const float &Y, const float &Z) : x(X), y(Y), z(Z) {}
//赋值操作符
S向量3& S向量3::operator +=(const S向量3 &_) {
	x += _.x;
	y += _.y;
	z += _.z;
	return *this;
}
S向量3& S向量3::operator -=(const S向量3 &_) {
	x -= _.x;
	y -= _.y;
	z -= _.z;
	return *this;
}
S向量3& S向量3::operator *=(const float &_) {
	x *= _;
	y *= _;
	z *= _;
	return *this;
}
S向量3& S向量3::operator /=(const float &_) {
	x /= _;
	y /= _;
	z /= _;
	return *this;
}
//四则运算操作符
S向量3 S向量3::operator +(const S向量3 &_) const {
	return S向量3(x + _.x, y + _.y, z + _.z);
}
S向量3 S向量3::operator -(const S向量3 &_) const {
	return S向量3(x - _.x, y - _.y, z - _.z);
}
S向量3 S向量3::operator *(const float &_) const {
	return S向量3(x * _, y * _, z * _);
}
S向量3 S向量3::operator /(const float &_) const {
	return S向量3(x / _, y / _, z / _);
}
//
float S向量3::fg大小() const {
	return sqrt(x * x + y * y + z * z);
}
float S向量3::fg平方() const {
	return x * x + y * y + z * z;
}
S向量3 S向量3::fg反向() const {
	return S向量3(-x, -y, -z);
}
S向量3 S向量3::fg归一() const {
	const float v模 = fg大小();
	return S向量3(x / v模, y / v模, z / v模);
}
S向量3 &S向量3::fs大小(const float &p) {
	*this = fg归一() / p;
	return *this;
}
float S向量3::f点乘(const S向量3 &p) const {
	return x * p.x + y * p.y + z * p.z;
}
S向量3 S向量3::f叉乘(const S向量3 &p) const {
	return S向量3(
		y * p.z - z * p.y,
		z * p.x - x * p.z,
		x * p.y - y * p.x);
}
S向量3 &S向量3::fs(const float &p) {
	x = y = z = p;
	return *this;
}
S向量3 &S向量3::fs(const float &X, const float &Y, const float &Z) {
	x = X;
	y = Y;
	z = Z;
	return *this;
}
//转换
S向量2 S向量3::ft向量2() const {
	return S向量2(x, y);
}
S向量4 S向量3::ft向量4(const float &w) const {
	return S向量4(x, y, z, w);
}
//=============================================================================
// 向量4
//=============================================================================
S向量4::S向量4() :x(0), y(0), z(0), w(0) {}
S向量4::S向量4(const float &X, const float &Y, const float &Z, const float &W) : x(X), y(Y), z(Z), w(W) {}
S向量3 S向量4::ft向量3() const {
	return S向量3(x, y, z);
}
S向量4 S向量4::operator *(const S矩阵4 &p) const {
	S向量4 _;
	for (int i = 0; i != 4; ++i)
		for (int j = 0; j != 4; ++j)
			_.m[i] += p.m[i][j] * m[j];
	return _;
}

}