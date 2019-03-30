#pragma once
#include <cassert>
#include "cflw数学.h"
namespace cflw::数学 {
//=============================================================================
// 声明
//=============================================================================
//其它文件
struct S向量3;
struct S向量4;
struct S平面方程;
//=============================================================================
// 矩阵
//=============================================================================
template<unsigned int 行, unsigned int 列> struct S矩阵 {
	const static unsigned int c行 = 行;
	const static unsigned int c列 = 列;
	float m值[行][列];
	S矩阵();
	S矩阵(std::initializer_list<float>);
	float &operator ()(unsigned int i, unsigned int j) {
		return m值[i][j];
	}
};
struct S矩阵信息 {
private:
	int m行, m列;
	float *m数;
public:
	float &f取(int 行, int 列) {
		return m数[行 * m列 + 列];
	}
};
class C矩阵 {	//提供矩阵运算
public:
	static void f空矩阵_(float *, int, int);
	static void f矩阵相乘_(float *, const float *, const float *, int, int, int);
	static void f单位矩阵_(float *, int);
	static void f矩阵相加_(float *, const float *, const float *, int, int);
	static void f矩阵转置_(float *, const float *, int, int);
	static float f算行列式_(float *, int);
public:
	template<unsigned int 行, unsigned int 列> static void f空矩阵(S矩阵<行, 列> &p);
	template<unsigned int 一, unsigned int 二, unsigned int 三> static void f矩阵相乘(S矩阵<一, 三> &p出, const S矩阵<一, 二> &p一, const S矩阵<二, 三> &p二);
	template<unsigned int 一> static void f单位矩阵(S矩阵<一, 一> &p);
	template<unsigned int i, unsigned int j> static void f矩阵相加(S矩阵<i, j> &o, const S矩阵<i, j> &p1, const S矩阵<i, j> &p2);
	template<unsigned int i, unsigned int j> static void f矩阵转置(S矩阵<i, j> &po, const S矩阵<j, i> &pi);
	template<unsigned int i> static float f算行列式(S矩阵<i, i> &pi);
};
//二阶矩阵
struct S矩阵2 : public S矩阵<2, 2> {
	typedef S矩阵<2, 2> t基类;
	using t基类::t基类;
	//操作符
	S矩阵2 &operator +=(const S矩阵2 &);
	S矩阵2 &operator *=(const S矩阵2 &);
	S矩阵2 operator +(const S矩阵2 &) const;
	S矩阵2 operator *(const S矩阵2 &) const;
	//静态函数
	static S矩阵2 fc单位();
	static S矩阵2 fc旋转(const float &);
	static S矩阵2 fc缩放(const float &, const float &);
	static S矩阵2 fc切变(const float &, const float &);
	static S矩阵2 fc翻转(const float &, const float &);
	static S矩阵2 fc复数(const t复数<float> &);
};
//四阶矩阵
struct S矩阵4 : public S矩阵 < 4, 4 > {
	typedef S矩阵<4, 4> t基类;
	static const S矩阵4 c单位;
	//构造函数
	S矩阵4();
	//操作符
	S矩阵4 &operator +=(const S矩阵4 &);
	S矩阵4 &operator *=(const S矩阵4 &);
	S矩阵4 operator +(const S矩阵4 &) const;
	S矩阵4 operator *(const S矩阵4 &) const;
	//静态函数
	static S矩阵4 fc单位();
	static S矩阵4 fc绕x旋转(const float &);
	static S矩阵4 fc绕y旋转(const float &);
	static S矩阵4 fc绕z旋转(const float &);
	static S矩阵4 fc旋转(const float &x, const float &y, const float &z);
	static S矩阵4 fc看l(const S向量3 &位置, const S向量3 &目标, const S向量3 &上方);
	static S矩阵4 fc看r(const S向量3 &位置, const S向量3 &目标, const S向量3 &上方);
	static S矩阵4 fc看向l(const S向量3 &位置, const S向量3 &视线, const S向量3 &上方);
	static S矩阵4 fc看向r(const S向量3 &位置, const S向量3 &视线, const S向量3 &上方);
	static S矩阵4 fc透视投影视角l(const float &范围, const float &宽高比, const float &近裁剪面, const float &远裁剪面);
	static S矩阵4 fc透视投影视角r(const float &范围, const float &宽高比, const float &近裁剪面, const float &远裁剪面);
	static S矩阵4 fc透视投影中心l(float 宽, float 高, float 近裁剪面, float 远裁剪面);
	static S矩阵4 fc透视投影中心r(float 宽, float 高, float 近裁剪面, float 远裁剪面);
	static S矩阵4 fc透视投影自定义l(float 左, float 右, float 下, float 上, float 近裁剪面, float 远裁剪面);
	static S矩阵4 fc透视投影自定义r(float 左, float 右, float 下, float 上, float 近裁剪面, float 远裁剪面);
	static S矩阵4 fc转置(const S矩阵4 &);
	static S矩阵4 fc平移(const float &x, const float &y, const float &z);
	static S矩阵4 fc缩放(const float &x, const float &y, const float &z);
	static S矩阵4 fc镜面反射(const S平面方程 &);
	static S矩阵4 fc阴影(const S平面方程 &平面, const S向量4 &光方向);
};


//=============================================================================
// 矩阵
//=============================================================================
template<unsigned int 行, unsigned int 列> S矩阵<行, 列>::S矩阵() :m值{0} {}
template<unsigned int 行, unsigned int 列> S矩阵<行, 列>::S矩阵(std::initializer_list<float> p) {
	for (int i = 0; i != 行; ++i) {
		for (int j = 0; j != 列; ++j) {
			const int n = i * 行 + j;
			assert(n <= p.size());
			m值[i][j] = p[n];
		}
	}
}
template<unsigned int 行, unsigned int 列> void C矩阵::f空矩阵(S矩阵<行, 列> &a矩阵) {
	f空矩阵_(*a矩阵.m值, a矩阵.c行, a矩阵.c列);
}
template<unsigned int 一, unsigned int 二, unsigned int 三> void C矩阵::f矩阵相乘(S矩阵<一, 三> &a输出, const S矩阵<一, 二> &a矩阵0, const S矩阵<二, 三> &a矩阵1) {
	f矩阵相乘_(*a输出.m值, *a矩阵0.m值, *a矩阵1.m值, 一, 二, 三);
}
template<unsigned int 一> void C矩阵::f单位矩阵(S矩阵<一, 一> &a矩阵) {
	f单位矩阵_(*a矩阵.m值, 一);
}
template<unsigned int i, unsigned int j> void C矩阵::f矩阵相加(S矩阵<i, j> &a输出, const S矩阵<i, j> &a矩阵0, const S矩阵<i, j> &a矩阵1) {
	f矩阵相加_(*a输出.m值, *a矩阵0.m值, *a矩阵1.m值, i, j);
}
template<unsigned int i, unsigned int j>  void C矩阵::f矩阵转置(S矩阵<i, j> &a输出, const S矩阵<j, i> &a输入) {
	f矩阵转置_(*a输出.m值, *a输入.m值, i, j);
}
template<unsigned int i> float C矩阵::f算行列式(S矩阵<i, i> &a矩阵) {
	return f算行列式_(a矩阵.m值, i);
}

}	//namespace cflw::数学