#include <assert.h>
#include "cflw数学.h"
#include "cflw数学_函数方程.h"
#include "cflw数学_向量.h"
namespace cflw::数学 {
//==============================================================================
// 二次函数
//==============================================================================
S二次函数::S二次函数() : a(0), b(0), c(0) {}
S二次函数::S二次函数(float A, float B, float C) :
	a(A), b(B), c(C) {
}
S二次函数 S二次函数::fc一般(float A, float B, float C) {
	return S二次函数(A, B, C);
}
S二次函数 S二次函数::fc三点(const S向量2 &p1, const S向量2 &p2, const S向量2 &p3) {
	S二次函数 v;
	v.fs三点(p1, p2, p3);
	return v;
}
float S二次函数::operator()(float x) const {
	return f求y(x);
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
	return a * x * x + b * x + c;
}
//==============================================================================
// 指数函数
//==============================================================================
S指数函数::S指数函数() :a(0), b(0), c(0), d(0) {}
S指数函数::S指数函数(float A, float B, float C, float D):
	a(A), b(B), c(C), d(D) {
}
S指数函数 S指数函数::fc一般(float A, float B, float C, float D) {
	return S指数函数(A, B, C, D);
}
S指数函数 S指数函数::fc原点(const S向量2 &o, const S向量2 &p1, const S向量2 &p2) {
	S指数函数 v;
	v.fs原点(o, p1, p2);
	return v;
}
float S指数函数::operator()(float x) const {
	return f求y(x);
}
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

}	//namespace cflw::数学