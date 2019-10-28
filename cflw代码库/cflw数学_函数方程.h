#pragma once
namespace cflw::数学 {
struct S向量2;
struct S向量3;
//==============================================================================
// 函数和方程
//==============================================================================
struct F一次函数 {
	float k, b;	// y = k * x + b
	F一次函数();
	F一次函数(float, float);
	static F一次函数 fc一般(float, float);
	static F一次函数 fc点斜(const S向量2 &, float);
	static F一次函数 fc两点(const S向量2 &, const S向量2 &);
	float operator()(float) const;
};
struct F二次函数 {
	float a, b, c;	// y = a * x^2 + b * x + c
	F二次函数();
	F二次函数(float, float, float);
	static F二次函数 fc一般(float, float, float);
	static F二次函数 fc三点(const S向量2 &, const S向量2 &, const S向量2 &);
	float operator()(float) const;
	F二次函数 &fs三点(const S向量2 &, const S向量2 &, const S向量2 &);
	float f求y(float) const;//y=f(x)
	float f垂直方向(const S向量2 &) const;//参数.y-f(参数.x)
};
struct F指数函数2 {
	float a = 0, b = 0, s = 0;	// y = s * a ^ x + b	(s∈{-1, 1})
	F指数函数2() = default;
	F指数函数2(float, float, float = 1);
	static F指数函数2 fc两点(const S向量2 &, const S向量2 &);
	float operator()(float) const;
};
struct F指数函数 {
	float a, b, c, d;	// y = a * b^(x + c) + d
	F指数函数();
	F指数函数(float, float, float, float);
	static F指数函数 fc一般(float, float, float, float);
	static F指数函数 fc原点(const S向量2 &, const S向量2 &, const S向量2 &);
	float operator()(float) const;
	F指数函数 &fs原点(const S向量2 &, const S向量2 &, const S向量2 &);
	float f求y(const float &) const;
};
struct F反函数 {
	float a, b, c, d;	// y = a / (b * x + c) + d
	F反函数();
	F反函数(float, float, float, float);
	static F反函数 fc三点(const S向量2 &, const S向量2 &, const S向量2 &);
	float operator()(float) const;
};
struct F正幂函数2 {
	float a, b;	// y = x ^ a + b	(x∈R+, a∈R+)
	F正幂函数2();
	F正幂函数2(float, float);
	static F正幂函数2 fc一般(float, float);
	static F正幂函数2 fc三点(const S向量2 &, const S向量2 &, const S向量2 &);

	float operator()(float) const;
};
}	//namespace cflw::数学