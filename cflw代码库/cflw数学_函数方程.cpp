#include <assert.h>
#include "cflw数学.h"
#include "cflw数学_函数方程.h"
#include "cflw数学_向量.h"
namespace cflw::数学 {
//==============================================================================
// 一次函数
//==============================================================================
F一次函数::F一次函数() :
	k(1), b(0) {
}
F一次函数::F一次函数(float K, float B) :
	k(K), b(B) {
}
F一次函数 F一次函数::fc一般(float K, float B) {
	return F一次函数(K, B);
}
F一次函数 F一次函数::fc点斜(const S向量2 &p, float k) {
	return F一次函数(k, p.y - k * p.x);
}
F一次函数 F一次函数::fc两点(const S向量2 &p1, const S向量2 &p2) {
	assert(p1.x != p2.x);
	const float k = (p2.y - p1.y) / (p2.x - p1.x);
	const float b = p1.y - k * p1.x;
	return F一次函数(k, b);
}
float F一次函数::operator()(float x) const {
	return k * x + b;
}
//==============================================================================
// 二次函数
//==============================================================================
F二次函数::F二次函数() :
	a(1), b(0), c(0) {
}
F二次函数::F二次函数(float A, float B, float C) :
	a(A), b(B), c(C) {
}
F二次函数 F二次函数::fc一般(float A, float B, float C) {
	return F二次函数(A, B, C);
}
F二次函数 F二次函数::fc三点(const S向量2 &p1, const S向量2 &p2, const S向量2 &p3) {
	F二次函数 v;
	v.fs三点(p1, p2, p3);
	return v;
}
float F二次函数::operator()(float x) const {
	return f求y(x);
}
F二次函数 &F二次函数::fs三点(const S向量2 &p1, const S向量2 &p2, const S向量2 &p3) {
	a = ((p1.y - p2.y) * (p2.x - p3.x) - (p2.y - p3.y) * (p1.x - p2.x)) /
		((p1.x * p1.x - p2.x * p2.x) * (p2.x - p3.x) - (p2.x * p2.x - p3.x * p3.x) * (p1.x - p2.x));
	b = (p1.y - p2.y - a * (p1.x * p1.x - p2.x * p2.x)) / (p1.x - p2.x);
	c = p1.y - a * p1.x * p1.x - b * p1.x;
	//assert(abs(f求y(p3.x) - p3.y) < 0.0001f);	//验算
	return *this;
}
float F二次函数::f垂直方向(const S向量2 &p) const {
	return p.y - f求y(p.x);
}
float F二次函数::f求y(float x) const {
	return a * x * x + b * x + c;
}
//==============================================================================
// 指数函数2
//==============================================================================
F指数函数2::F指数函数2(float A, float B, float S) :
	a(A), b(B), s(S) {
}
F指数函数2 F指数函数2::fc两点(const S向量2 &, const S向量2 &) {
	//未实现
	return F指数函数2();
}
float F指数函数2::operator()(float x) const {
	return s * std::pow(a, x) + b;
}
//==============================================================================
// 指数函数
//==============================================================================
F指数函数::F指数函数() :a(0), b(0), c(0), d(0) {}
F指数函数::F指数函数(float A, float B, float C, float D) :
	a(A), b(B), c(C), d(D) {
}
F指数函数 F指数函数::fc一般(float A, float B, float C, float D) {
	return F指数函数(A, B, C, D);
}
F指数函数 F指数函数::fc原点(const S向量2 &o, const S向量2 &p1, const S向量2 &p2) {
	F指数函数 v;
	v.fs原点(o, p1, p2);
	return v;
}
float F指数函数::operator()(float x) const {
	return f求y(x);
}
float F指数函数::f求y(const float &x) const {
	return a * pow(b, x + c) + d;
}
F指数函数 &F指数函数::fs原点(const S向量2 &o, const S向量2 &p1, const S向量2 &p2) {
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
//==============================================================================
// 反函数
//==============================================================================
F反函数::F反函数() :
	a(0), b(0), c(0), d(0) {
}
F反函数::F反函数(float A, float B, float C, float D) :
	a(A), b(B), c(C), d(D) {
}
F反函数 F反函数::fc三点(const S向量2 &p1, const S向量2 &p2, const S向量2 &p3) {
	//未实现
	return F反函数();
}
float F反函数::operator()(float x) const {
	return a / (b * x + c) + d;
}

//==============================================================================
// 正幂函数
//==============================================================================
F正幂函数2::F正幂函数2() :
	a(0), b(0) {
}
F正幂函数2::F正幂函数2(float A, float B) :
	a(A), b(B) {
}
F正幂函数2 F正幂函数2::fc一般(float a, float b) {
	return F正幂函数2(a, b);
}
F正幂函数2 F正幂函数2::fc三点(const S向量2 &p1, const S向量2 &p2, const S向量2 &p3) {
	//未实现
	return F正幂函数2();
}
float F正幂函数2::operator()(float x) const {
	return std::pow(x, a) + b;
}

}	//namespace cflw::数学