#pragma once
namespace cflw::数学 {
struct S向量2;
struct S向量3;
//=============================================================================
// 函数和方程
//=============================================================================
struct S二次函数 {
	float a, b, c;	// y = a * x^2 + b * x + c
	S二次函数();
	S二次函数(const S向量2 &, const S向量2 &, const S向量2 &);
	S二次函数 &fs(const S向量2 &, const S向量2 &, const S向量2 &);
	float f求y(float) const;//y=f(x)
	float f垂直方向(const S向量2 &) const;//p.y-f(p.x)
};
struct S直线方程 {
	float a, b, c;	// a*x + b*y + c = 0
	S直线方程();
	S直线方程(float, float, float);
	static S直线方程 fc点斜(const S向量2 &, const float &);
	static S直线方程 fc两点(const S向量2 &, const S向量2 &);
	static S直线方程 fc斜截(const float &, const float &);
	static S直线方程 fc截距(const float &, const float &);
	static S直线方程 fc一般(const float &, const float &, const float &);
	static S直线方程 fc点法(const S向量2 &, const S向量2 &);
	static S直线方程 fc点向(const S向量2 &, const float &);
	float f到点距离(const S向量2 &) const;
	float fg斜率() const;
	S直线方程 f平移(const S向量2 &) const;
	float f求x(const float &) const;
	float f求y(const float &) const;
	bool f平行(const S直线方程 &) const;
	float fg方向r() const;
	float fg方向d() const;
	S向量2 f交点(const S直线方程 &) const;
	S向量2 fg法向量() const;
	bool f交x轴(int) const;
	bool f交y轴(int) const;
};
struct S直线方程3 {
	float x[2], y[2], z[2];//参数方程的形式
	S直线方程3();
	S直线方程3 &fs两点(const S向量3 &, const S向量3 &);
	S直线方程3 &fs归一();
	bool f相交判定(const S直线方程3 &, S向量3 * = nullptr) const;
	float fg模() const;
};
struct S平面方程 {
	float a, b, c, d;
	S平面方程();
	S平面方程 &fs三点(const S向量3 &, const S向量3 &, const S向量3 &);
	S平面方程 &fs点法(const S向量3 &, const S向量3 &);
	S平面方程 &fs一般(float, float, float, float);
	S向量3 fg法() const;
};
struct S指数函数 {
	float a, b, c, d;	// y = a * b^(x + c) + d
	S指数函数();
	S指数函数 &fs原点(const S向量2 &, const S向量2 &, const S向量2 &);
	float f求y(const float &) const;
};

}