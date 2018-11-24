#include <assert.h>
#include "cflw数学.h"
#include "cflw数学_函数方程.h"
#include "cflw数学_向量.h"
namespace cflw::数学 {
//==============================================================================
// 二次函数
//==============================================================================
S二次函数::S二次函数() : a(0), b(0), c(0) {}
S二次函数::S二次函数(const S向量2 &p1, const S向量2 &p2, const S向量2 &p3) {
	fs三点(p1, p2, p3);
}
S二次函数 &S二次函数::fs三点(const S向量2 &p1, const S向量2 &p2, const S向量2 &p3) {
	a = ((p1.y - p2.y) * (p2.x - p3.x) - (p2.y - p3.y) * (p1.x - p2.x)) /
		((p1.x*p1.x - p2.x*p2.x) * (p2.x - p3.x) - (p2.x*p2.x - p3.x*p3.x) * (p1.x - p2.x));
	b = (p1.y - p2.y - a * (p1.x*p1.x - p2.x*p2.x)) / (p1.x - p2.x);
	c = p1.y - a * p1.x * p1.x - b * p1.x;
	assert(abs(f求y(p3.x) - p3.y) < 0.0001f);	//验算
	return *this;
}
float S二次函数::f垂直方向(const S向量2 &p) const {
	return p.y - f求y(p.x);
}
float S二次函数::f求y(float x) const {
	return	a * x * x + b * x + c;
}
//==============================================================================
// 直线方程
//==============================================================================
S直线方程::S直线方程() :
	a(0), b(0), c(0) {}
S直线方程::S直线方程(float A, float B, float C) :
	a{A}, b{B}, c{C} {}
S直线方程 S直线方程::fc点斜(const S向量2 &p, const float &k) {
	const float a = k;
	const float b = -1;
	const float c = k * p.x + p.y;
	return {a, b, c};
}
S直线方程 S直线方程::fc两点(const S向量2 &p1, const S向量2 &p2) {
	const float a = p2.y - p1.y;
	const float b = p1.x - p2.x;
	const float c = -p1.x * a - p2.y * b;
	return {a, b, c};
}
S直线方程 S直线方程::fc斜截(const float &k, const float &y) {
	const float a = k;
	const float b = -1;
	const float c = y;
	return{a, b, c};
}
S直线方程 S直线方程::fc截距(const float &x, const float &y) {
	const float a = x;
	const float b = y;
	const float c = -1;
	return{a, b, c};
}
S直线方程 S直线方程::fc一般(const float &A, const float &B, const float &C) {
	const float a = A;
	const float b = B;
	const float c = C;
	return{a, b, c};
}
S直线方程 S直线方程::fc点法(const S向量2 &p, const S向量2 &n) {
	const float a = n.x;
	const float b = n.y;
	const float c = -n.x * p.x - n.y * p.y;
	return{a, b, c};
}
S直线方程 S直线方程::fc点向(const S向量2 &p, const float &d) {
	return fc点法(p, S向量2::fc方向r(1, d + (float)c半π));
}
float S直线方程::fg斜率() const {
	return a / b;
}
float S直线方程::f到点距离(const S向量2 &p) const {
	return abs(a * p.x + b * p.y + c) / sqrt(a*a + b * b);
}
S直线方程 S直线方程::f平移(const S向量2 &a向量) const {
	S直线方程 v = *this;
	v.c -= v.a * a向量.x;
	v.c -= v.b * a向量.y;
	return v;
}
float S直线方程::f求x(const float &y) const {
	assert(a != 0);
	return (b * y + c) / -a;
}
float S直线方程::f求y(const float &x) const {
	assert(b != 0);
	return (a * x + c) / -b;
}
bool S直线方程::f平行(const S直线方程 &a直线方程) const {
	if (a == 0) return a直线方程.a == 0;
	else return (b / a) == (a直线方程.b / a直线方程.a);
}
float S直线方程::fg方向r() const {
	return C角度计算<float>::c弧度.f取半(atan2(b, a) + (float)c半π);
}
float S直线方程::fg方向d() const {
	return fg方向r() * (float)c弧度到度;
}
S向量2 S直线方程::f交点(const S直线方程 &a直线方程) const {
	const float y = (a直线方程.a*c - a * a直线方程.c) / (a直线方程.b*a - b * a直线方程.a);
	const float x = f求x(y);
	return S向量2(x, y);
}
S向量2 S直线方程::fg法向量() const {
	const float m = hypotf(a, b);
	return S向量2(a / m, b / m);
}
bool S直线方程::f交x轴(int p) const {
	if (a == 0) {
		if (p == 0)
			return true;
		else
			return f取符号(c) == f取符号(p);
	} else if (b == 0) {
		return c == 0;
	} else {
		if (p == 0)
			return true;
		else
			return -c / a * f取符号(p) > 0;
	}
}
bool S直线方程::f交y轴(int p) const {
	if (a == 0) {
		return c == 0;
	} else if (b == 0) {
		if (p == 0)
			return true;
		else
			return f取符号(c) == f取符号(p);
	} else {
		if (p == 0)
			return true;
		else
			return -c / b * f取符号(p) > 0;
	}
}
bool S直线方程::fi平行x轴() const {
	return b == 0;
}
bool S直线方程::fi平行y轴() const {
	return a == 0;
}
bool S直线方程::fi垂直x轴() const {
	return a == 0;
}
bool S直线方程::fi垂直y轴() const {
	return b == 0;
}
//==============================================================================
// 直线方程3d
//==============================================================================
S直线方程3::S直线方程3() :x(), y(), z() {}
S直线方程3 &S直线方程3::fs两点(const S向量3 &p1, const S向量3 &p2) {
	x[0] = p1.x - p2.x;
	x[1] = p2.x;
	y[0] = p1.y - p2.y;
	y[1] = p2.y;
	z[0] = p1.z - p2.z;
	z[1] = p2.z;
	return *this;
}
S直线方程3 &S直线方程3::fs归一() {
	const float v = fg模();
	x[0] /= v;
	y[0] /= v;
	z[0] /= v;
	return *this;
}
bool S直线方程3::f相交判定(const S直线方程3 &a直线方程, S向量3 *a输出) const {
	const float v[2] = {fg模(), a直线方程.fg模()};
	auto f = [](float *p1, float *p2)->float {
		return (p2[1] - p1[1]) / (p1[0] - p2[2]);
	};
	if (x[0] / v[0] == a直线方程.x[0] / v[1]) {
		return true;
	} else if (y[0] / v[0] == a直线方程.y[0] / v[1]) {
		return true;
	} else if (z[0] / v[0] == a直线方程.z[0] / v[1]) {
		return true;
	}
	return false;
}
float S直线方程3::fg模() const {
	return sqrt(x[0] * x[0] + y[0] * y[0] + z[0] * z[0]);
}
//==============================================================================
// 平面方程
//==============================================================================
S平面方程::S平面方程() :a(0), b(0), c(0), d(0) {}
S平面方程 &S平面方程::fs三点(const S向量3 &p1, const S向量3 &p2, const S向量3 &p3) {
	return fs点法(p1, (p1 - p2).f叉乘(p2 - p3));
}
S平面方程 &S平面方程::fs点法(const S向量3 &p, const S向量3 &n) {
	a = n.x;
	b = n.y;
	c = n.z;
	d = -n.x * p.x - n.y * p.y - n.z * p.z;
	return *this;
}
S平面方程 &S平面方程::fs一般(float A, float B, float C, float D) {
	a = A;
	b = B;
	c = C;
	d = D;
	return *this;
}
S向量3 S平面方程::fg法() const {
	return S向量3(a, b, c);
}
//==============================================================================
// 指数函数
//==============================================================================
S指数函数::S指数函数() :a(0), b(0), c(0), d(0) {}
float S指数函数::f求y(const float &x) const {
	return a * pow(b, x + c) + d;
}
S指数函数 &S指数函数::fs原点(const S向量2 &o, const S向量2 &p1, const S向量2 &p2) {
	c = -o.x;
	d = o.y;
	const float v1 = (p1.y - d) / (p2.y - d);
	const float v2 = 1 / (p1.x - p2.x);
	const float v符号 = ((p1.y - d > 0) && (p2.y - d > 0)) ? 1.f : -1.f;
	b = pow(v1, v2);
	a = (p1.y - d) / pow(b, p1.x + c) * v符号;
	assert(abs(f求y(p2.x) - p2.y) < 0.001f);	//验算
	return *this;
}

}