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
template<> S向量4 f绝对值<S向量4>(const S向量4 &a) {
	return S向量4(abs(a.x), abs(a.y), abs(a.z), abs(a.w));
}
template<> S向量2 f平均<S向量2>(const S向量2 &a, const S向量2 &b) {
	return {
		f平均<float>(a.x, b.x),
		f平均<float>(a.y, b.y)
	};
}
template<> S向量3 f平均<S向量3>(const S向量3 &a, const S向量3 &b) {
	return {
		f平均<float>(a.x, b.x),
		f平均<float>(a.y, b.y),
		f平均<float>(a.z, b.z)
	};

}
template<> S向量4 f平均<S向量4>(const S向量4 &a, const S向量4 &b) {
	return {
		f平均<float>(a.x, b.x),
		f平均<float>(a.y, b.y),
		f平均<float>(a.z, b.z),
		f平均<float>(a.w, b.w)
	};
}
//==============================================================================
// 向量
//==============================================================================
//常量
const S向量2 S向量2::c零(0, 0);
const S向量2 S向量2::c一(1, 1);
//构造函数
S向量2::S向量2(float X, float Y) :
	x(X), y(Y) {
}
S向量2 S向量2::fc方向r(const float &a大小, const float &a方向) {
	return {cos(a方向) * a大小, sin(a方向) * a大小};
}
S向量2 S向量2::fc方向d(const float &a大小, const float &a方向) {
	const float r = a方向 / 180.f * cπ<float>;
	return {cos(r) * a大小, sin(r) * a大小};
}
S向量2 S向量2::fc相同(const float &a) {
	return {a, a};
}
S向量2 S向量2::fc矩形中心(float a左, float a上, float a右, float a下) {
	return {(a左 + a右) / 2, (a上 + a下) / 2};
}
S向量2 S向量2::fc矩形尺寸(float a左, float a上, float a右, float a下) {
	return {a右 - a左, a上 - a下};
}
S向量2 S向量2::fc矩形半尺寸(float a左, float a上, float a右, float a下) {
	return {(a右 - a左) / 2, (a上 - a下) / 2};
}
//赋值操作符
S向量2 &S向量2::operator +=(const S向量2 &_) {
	x += _.x;
	y += _.y;
	return *this;
}
S向量2 &S向量2::operator -=(const S向量2 &_) {
	x -= _.x;
	y -= _.y;
	return *this;
}
S向量2 &S向量2::operator *=(const float &_) {
	x *= _;
	y *= _;
	return *this;
}
S向量2 &S向量2::operator /=(const float &_) {
	x /= _;
	y /= _;
	return *this;
}
S向量2 &S向量2::operator *= (const t复数<float> &_) {
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
S向量2 S向量2::operator *(const t复数<float> &_) const {
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
bool S向量2::operator ==(const S向量2 &a) const {
	return (x == a.x) && (y == a.y);
}
bool S向量2::operator !=(const S向量2 &a) const {
	return (x != a.x) || (y != a.y);
}
//复杂比较
bool S向量2::f全小于(const S向量2 &a) const {
	return (x < a.x) && (y < a.y);
}
bool S向量2::f全小于等于(const S向量2 &a) const {
	return (x <= a.x) && (y <= a.y);
}
bool S向量2::f全大于(const S向量2 &a) const {
	return (x > a.x) && (y > a.y);
}
bool S向量2::f全大于等于(const S向量2 &a) const {
	return (x >= a.x) && (y >= a.y);
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
float S向量2::fg横纵比() const {
	return x / y;
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
S向量2 &S向量2::fs大小(const float &a大小) {
	float v模 = fg大小();
	assert(v模 != 0);
	x = x / v模 * a大小;
	y = y / v模 * a大小;
	return *this;
}
S向量2 &S向量2::fs方向(const float &a弧度) {
	const float v模 = fg大小();
	x = cos(a弧度) * v模;
	y = sin(a弧度) * v模;
	return *this;
}
S向量2 &S向量2::fs方向d(const float &a度) {
	const float v模 = fg大小();
	const float r = a度 * c度到弧度<float>;
	x = cos(r) * v模;
	y = sin(r) * v模;
	return *this;
}
S向量2 &S向量2::fs旋转r(const float &a弧度) {
	*this = f旋转r(a弧度);
	return *this;
}
S向量2 &S向量2::fs旋转d(const float &a度) {
	*this = f旋转d(a度);
	return *this;
}
S向量2 S向量2::f大小(const float &a大小) const {
	return S向量2(*this).fs大小(a大小);
}
S向量2 S向量2::f方向r(const float &a弧度) const {
	return S向量2(*this).fs方向(a弧度);
}
S向量2 S向量2::f方向d(const float &a度) const {
	return S向量2(*this).fs方向d(a度);
}
float S向量2::f到点方向r(const S向量2 &a向量) const {
	const S向量2 v = a向量 - *this;
	return C角度计算<float>::c弧度.f方向(v.x, v.y);
}
float S向量2::f到点方向d(const S向量2 &a向量) const {
	const S向量2 v = a向量 - *this;
	return C角度计算<float>::c度.f方向(v.x, v.y);
}
S向量2 S向量2::f旋转r(const float &a角度) const {
	const float s = sin(a角度);
	const float c = cos(a角度);
	return S向量2{x * c - y * s, x * s + y * c};
}
S向量2 S向量2::f旋转d(const float &a角度) const {
	return f旋转r(a角度 * c度到弧度<float>);
}
S向量2 S向量2::f绕点旋转r(const S向量2 &a中心, const float &a角度) const {
	return (*this - a中心).f旋转r(a角度) += a中心;
}
S向量2 S向量2::f绕点旋转d(const S向量2 &a中心, const float &a角度) const {
	return f绕点旋转r(a中心, a角度 * c度到弧度<float>);
}
float S向量2::f到点距离(const S向量2 &a) const {
	const float _x = a.x - x;
	const float _y = a.y - y;
	return sqrt(_x * _x + _y * _y);
}
S向量2 S向量2::f到点向量(const S向量2 &a) const {
	return S向量2{a.x - x, a.y - y};
}
S向量2 S向量2::f到点方位r(const S向量2 &a点, const float &a方向) const {
	const S向量2 v点 = f到点向量(a点);
	return v点.f旋转r(-a方向);
}
S向量2 S向量2::f到点方位d(const S向量2 &a点, const float &a方向) const {
	return f到点方位r(a点, a方向 * c度到弧度<float>);
}
float S向量2::f点乘(const S向量2 &a) const {
	return x * a.x + y * a.y;
}
S向量2 &S向量2::fs线性渐变(const S向量2 &a, const float &a渐变) {
	S向量2 v = a - *this;
	if (v.fg大小() <= a渐变)
		return *this = a;
	v.fs大小(a渐变);
	return *this += v;
}
S向量2 S向量2::f线性渐变(const S向量2 &a, const float &a渐变) const {
	S向量2 v = a - *this;
	if (v.fg大小() <= a渐变)
		return a;
	v.fs大小(a渐变);
	return *this + v;
}
S向量2 &S向量2::fs倍数渐变(const S向量2 &a, const float &a渐变, const float &a最小, const float &a最大) {
	S向量2 v = (a - *this) * a渐变;
	const float v模 = v.fg大小();
	if (v模 == 0)
		return *this;
	if (v模 < a最小)
		v.fs大小(a最小);
	else if (v模 > a最大)
		v.fs大小(a最大);
	return *this += v;
}
S向量2 S向量2::f倍数渐变(const S向量2 &a, const float &a渐变, const float &a最小, const float &a最大) const {
	S向量2 v = (a - *this) * a渐变;
	const float v模 = v.fg大小();
	if (v模 == 0)
		return *this;
	if (v模 < a最小)
		v.fs大小(a最小);
	else if (v模 > a最大)
		v.fs大小(a最大);
	return *this + v;
}
S向量2 S向量2::f翻折(const S直线2 &a直线) const {
	return f点关于直线翻折(*this, a直线);
}
S向量2 S向量2::f翻折(const float &a方向) const {
	return f点关于方向翻折(*this, a方向);
}
S向量2 S向量2::f翻折(const S圆形 &a圆形) const {
	return f点关于圆形翻折(*this, a圆形);
}
S向量2 S向量2::f对齐(const float &a) const {
	return{数学::f对齐(x, a), 数学::f对齐(y, a)};
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
S向量2 S向量2::f分量乘(const S向量2 &a) const {
	return {x * a.x, y * a.y};
}
bool S向量2::fi分量相等() const {
	return x == y;
}
float S向量2::f平方() const {
	return x * x + y * y;
}
//转换
S向量3 S向量2::ft向量3(float z)const {
	return S向量3(x, y, z);
}
S向量4 S向量2::ft向量4(float z, float w) const {
	return S向量4(x, y, z, w);
}
//==============================================================================
// 向量3
//==============================================================================
const S向量3 S向量3::c零(0, 0, 0);
const S向量3 S向量3::c一(1, 1, 1);
S向量3::S向量3(const float &X, const float &Y, const float &Z) : 
	x(X), y(Y), z(Z) {
}
S向量3 S向量3::fc相同(float a) {
	return S向量3(a, a, a);
}
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
S向量3 S向量3::operator -() const {
	return fg反向();
}
//
float S向量3::fg大小() const {
	return std::sqrt(fg平方());
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
S向量3 &S向量3::fs大小(const float &a) {
	*this = fg归一() / a;
	return *this;
}
float S向量3::f点乘(const S向量3 &a) const {
	return x * a.x + y * a.y + z * a.z;
}
S向量3 S向量3::f叉乘(const S向量3 &a) const {
	return S向量3(
		y * a.z - z * a.y,
		z * a.x - x * a.z,
		x * a.y - y * a.x);
}
S向量3 &S向量3::fs(const float &a) {
	x = y = z = a;
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
//==============================================================================
// 向量4
//==============================================================================
const S向量4 S向量4::c零(0, 0, 0, 0);
const S向量4 S向量4::c一(1, 1, 1, 1);
S向量4::S向量4() :
	x(0), y(0), z(0), w(0) {
}
S向量4::S向量4(const float &X, const float &Y, const float &Z, const float &W) : 
	x(X), y(Y), z(Z), w(W) {
}
S向量4 S向量4::operator +(const S向量4 &a) const {
	return S向量4(x + a.x, y + a.y, z + a.z, w + a.w);
}
S向量4 S向量4::operator -(const S向量4 &a) const {
	return S向量4(x - a.x, y - a.y, z - a.z, w - a.w);
}
S向量4 S向量4::operator *(const float &a) const {
	return S向量4(x * a, y * a, z * a, w * a);
}
S向量4 S向量4::operator /(const float &a) const {
	return S向量4(x / a, y / a, z / a, w / a);
}
S向量4 S向量4::operator *(const S矩阵4 &a) const {
	S向量4 v;
	for (int i = 0; i != 4; ++i) {
		for (int j = 0; j != 4; ++j) {
			v.m值[i] += a.m值[i][j] * m值[j];
		}
	}
	return v;
}
S向量4 S向量4::operator -() const {
	return fg反向();
}
float S向量4::fg大小() const {
	return std::sqrt(fg平方());
}
float S向量4::fg平方() const {
	return x * x + y * y + z * z + w * w;
}
S向量4 S向量4::fg反向() const {
	return S向量4(-x, -y, -z, -w);
}
S向量4 S向量4::fg归一() const {
	const float v大小 = fg大小();
	return *this / v大小;
}
S向量4 S向量4::fg三维归一() const {
	const float v = fg大小();
	return S向量4(x / v, y / v, z / v, w);
}
S向量4 S向量4::fg三维取反() const {
	return S向量4(-x, -y, -z, w);
}
float S向量4::f点乘(const S向量4 &a) const {
	return x * a.x + y * a.y + z * a.z + w * a.w;
}
S向量3 S向量4::ft向量3() const {
	return S向量3(x, y, z);
}

}