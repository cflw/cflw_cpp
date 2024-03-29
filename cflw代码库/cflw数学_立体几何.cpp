﻿#include "cflw数学.h"
#include "cflw数学_常数.h"
#include "cflw数学_立体几何.h"
#include "cflw数学_向量.h"
namespace cflw::数学 {
//==============================================================================
// 形状几何
//==============================================================================
float f直线与直线最近距离(const S直线3 &l1, const S直线3 &l2) {
	const S向量3 n = l1.fg方向().f叉乘(l2.fg方向());
	return std::abs(n.f点乘(l2.fg坐标() - l1.fg坐标())) / n.fg大小();
}
float f直线与直线最近位置(const S直线3 &l1, const S直线3 &l2) {
	const S向量3 d1 = l1.fg方向();
	const S向量3 d2 = l2.fg方向();
	const S向量3 n = d1.f叉乘(d2);
	const S平面3 p = S平面3::fc线向(l2, n);
	return f直线与平面相交位置(l1, p);
}
float f直线与平面相交位置(const S直线3 &l, const S平面3 &p) {
	return -(p.a * l.x + p.b * l.y + p.c * l.z + p.d) / (p.a * l.m + p.b * l.n + p.c * l.p);
}
S向量3 f直线与平面交点(const S直线3 &l, const S平面3 &p) {
	const float t = f直线与平面相交位置(l, p);
	return l.fg点(t);
}
bool f球体射线相交判定(const S球体 &a球体, const S直线3 &a射线) {
	const S向量3 v射线坐标 = a射线.fg坐标();
	const S向量3 v射线方向 = a射线.fg方向();
	const S向量3 v相对位置 = a球体.m坐标 - v射线坐标;
	const float a = v射线方向.f点乘(v射线方向);
	const float b = 2 * v相对位置.f点乘(v射线方向);
	const float c = v相对位置.f点乘(v相对位置) - a球体.m半径 * a球体.m半径;
	const float d = b * b - 4 * a * c;
	return d >= 0;
}
//==============================================================================
// 球体
//==============================================================================
S球体::S球体(const S向量3 &a坐标, float a半径):
	m坐标(a坐标), m半径(a半径) {
}
S球体 S球体::fc坐标半径(const S向量3 &a坐标, float a半径) {
	return S球体(a坐标, a半径);
}
S球体 S球体::fc坐标直径(const S向量3 &a坐标, float a直径) {
	return S球体(a坐标, a直径 * 0.5f);
}
float S球体::fg表面积() const {
	return 4.f * cπ<float> * m半径 * m半径;
}
float S球体::fg体积() const {
	return 4.f / 3.f * cπ<float> * m半径 * m半径 * m半径;
}
float S球体::fg半径() const {
	return m半径;
}
float S球体::fg直径() const {
	return m半径 * 2;
}
//==============================================================================
// 长方体
//==============================================================================
S长方体::S长方体(const S向量3 &a坐标, const S向量3 &a半尺寸):
	m坐标(a坐标), m半尺寸(a半尺寸) {
}
S长方体 S长方体::fc坐标尺寸(const S向量3 &a坐标, const S向量3 &a尺寸) {
	return S长方体(a坐标, a尺寸 * 0.5f);
}
S长方体 S长方体::fc坐标半尺寸(const S向量3 &a坐标, const S向量3 &a半尺寸) {
	return S长方体(a坐标, a半尺寸);
}
S长方体 S长方体::fc正方体(const S向量3 &a坐标, float a边长) {
	return S长方体(a坐标, S向量3::fc相同(a边长));
}
S长方体 S长方体::fc对角点(const S向量3 &a, const S向量3 &b) {
	S长方体 v;
	v.m坐标.x = (a.x + b.x) / 2;
	v.m坐标.y = (a.y + b.y) / 2;
	v.m坐标.z = (a.z + b.z) / 2;
	v.m半尺寸.x = std::abs(a.x - b.x) / 2;
	v.m半尺寸.y = std::abs(a.y - b.y) / 2;
	v.m半尺寸.z = std::abs(a.z - b.z) / 2;
	return v;
}
float S长方体::fg表面积() const {
	return m半尺寸.x * m半尺寸.y * 8 + m半尺寸.y * m半尺寸.z * 8 + m半尺寸.z * m半尺寸.x * 8;
}
float S长方体::fg体积() const {
	return m半尺寸.x * m半尺寸.y * m半尺寸.z * 8;
}
//==============================================================================
// 直线方程3d
//==============================================================================
S直线3::S直线3():
	x(), y(), z(), m(), n(), p() {
}
S直线3::S直线3(float X, float Y, float Z, float M, float N, float P):
	x(X), y(Y), z(Z), m(M), n(N), p(P) {
}
S直线3 S直线3::fc参数(float x, float m, float y, float n, float z, float p) {
	return S直线3(x, y, z, m, n, p);
}
S直线3 S直线3::fc两点(const S向量3 &p1, const S向量3 &p2) {
	S直线3 v;
	v.x = p1.x;
	v.m = p2.x - p1.x;
	v.y = p1.y;
	v.n = p2.y - p1.y;
	v.z = p1.z;
	v.p = p2.z - p1.z;
	return v;
}
S直线3 S直线3::fc点向(const S向量3 &a点, const S向量3 &a方向) {
	S直线3 v;
	v.x = a点.x;
	v.y = a点.y;
	v.z = a点.z;
	v.m = a方向.x;
	v.n = a方向.y;
	v.p = a方向.z;
	return v;
}
S直线3 &S直线3::fs两点(const S向量3 &p1, const S向量3 &p2) {
	x = p1.x;
	m = p2.x - p1.x;
	y = p1.y;
	n = p2.y - p1.y;
	z = p1.z;
	p = p2.z - p1.z;
	return *this;
}
S向量3 S直线3::fg坐标() const {
	return {x, y, z};
}
S向量3 S直线3::fg方向() const {
	return {m, n, p};
}
S直线3 S直线3::fg归一() const {
	const float v = fg模();
	return S直线3(x, y, z, m/v, n/v, p/v);
}
S直线3 &S直线3::fs归一() {
	const float v = fg模();
	m /= v;
	n /= v;
	p /= v;
	return *this;
}
bool S直线3::f相交判定(const S直线3 &a直线) const {
	const float v[2] = {fg模(), a直线.fg模()};
	if (m / v[0] == a直线.m / v[1]) {
		return true;
	} else if (n / v[0] == a直线.n / v[1]) {
		return true;
	} else if (p / v[0] == a直线.p / v[1]) {
		return true;
	}
	return false;
}
float S直线3::fg模() const {
	return sqrt(m * m + n * n + p * p);
}
S向量3 S直线3::fg点(float t) const {
	return S向量3(x + m * t, y + n * t, z + p * t);
}
//==============================================================================
// 平面方程
//==============================================================================
S平面3::S平面3(float A, float B, float C, float D) :
	a(A), b(B), c(C), d(D) {
}
S平面3 S平面3::fc三点(const S向量3 &p1, const S向量3 &p2, const S向量3 &p3) {
	return fc点法(p1, (p1 - p2).f叉乘(p2 - p3));
}
S平面3 S平面3::fc点法(const S向量3 &p, const S向量3 &n) {
	return S平面3(
		n.x,
		n.y,
		n.z,
		-n.x * p.x - n.y * p.y - n.z * p.z
	);
}
S平面3 S平面3::fc点向(const S向量3 &p, const S向量3 &d1, const S向量3 &d2) {
	const S向量3 n = d1.f叉乘(d2);
	return fc点法(p, n);
}
S平面3 S平面3::fc线向(const S直线3 &l, const S向量3 &d) {
	const S向量3 n = l.fg方向().f叉乘(d);
	return fc点法(l.fg坐标(), n);
}
S平面3 S平面3::fc一般(float A, float B, float C, float D) {
	return S平面3(A, B, C, D);
}
S平面3 S平面3::fc截距(float X, float Y, float Z) {
	return S平面3(1 / X, 1 / Y, 1 / Z, -1);
}
S平面3 &S平面3::fs三点(const S向量3 &p1, const S向量3 &p2, const S向量3 &p3) {
	return fs点法(p1, (p1 - p2).f叉乘(p2 - p3));
}
S平面3 &S平面3::fs点法(const S向量3 &p, const S向量3 &n) {
	a = n.x;
	b = n.y;
	c = n.z;
	d = -n.x * p.x - n.y * p.y - n.z * p.z;
	return *this;
}
S平面3 &S平面3::fs一般(float A, float B, float C, float D) {
	a = A;
	b = B;
	c = C;
	d = D;
	return *this;
}
S向量3 S平面3::fg法线() const {
	return S向量3(a, b, c).fg归一();
}
S平面3 S平面3::fg归一() const {
	const float v = std::sqrt(a * a + b * b + c * c);
	return S平面3(a / v, b / v, c / v, d / v);
}
}	//namespace cflw::数学