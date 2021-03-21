#include "cflw数学.h"
#include "cflw数学_常数.h"
#include "cflw数学_立体几何.h"
#include "cflw数学_向量.h"
namespace cflw::数学 {
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
S直线3::S直线3() :
	x(), y(), z() {
}
S直线3 S直线3::fc两点(const S向量3 &p1, const S向量3 &p2) {
	S直线3 v;
	v.x[0] = p1.x - p2.x;
	v.x[1] = p2.x;
	v.y[0] = p1.y - p2.y;
	v.y[1] = p2.y;
	v.z[0] = p1.z - p2.z;
	v.z[1] = p2.z;
	return v;
}
S直线3 &S直线3::fs两点(const S向量3 &p1, const S向量3 &p2) {
	x[0] = p1.x - p2.x;
	x[1] = p2.x;
	y[0] = p1.y - p2.y;
	y[1] = p2.y;
	z[0] = p1.z - p2.z;
	z[1] = p2.z;
	return *this;
}
S直线3 S直线3::fg归一() const {
	const float v = fg模();
	//未实现
	return *this;
}
S直线3 &S直线3::fs归一() {
	const float v = fg模();
	x[0] /= v;
	y[0] /= v;
	z[0] /= v;
	return *this;
}
bool S直线3::f相交判定(const S直线3 &a直线方程) const {
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
float S直线3::fg模() const {
	return sqrt(x[0] * x[0] + y[0] * y[0] + z[0] * z[0]);
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