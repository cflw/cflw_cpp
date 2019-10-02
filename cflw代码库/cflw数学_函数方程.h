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
	S二次函数(float, float, float);
	static S二次函数 fc一般(float, float, float);
	static S二次函数 fc三点(const S向量2 &, const S向量2 &, const S向量2 &);
	float operator()(float) const;
	S二次函数 &fs三点(const S向量2 &, const S向量2 &, const S向量2 &);
	float f求y(float) const;//y=f(x)
	float f垂直方向(const S向量2 &) const;//参数.y-f(参数.x)
};
struct S指数函数 {
	float a, b, c, d;	// y = a * b^(x + c) + d
	S指数函数();
	S指数函数(float, float, float, float);
	static S指数函数 fc一般(float, float, float, float);
	static S指数函数 fc原点(const S向量2 &, const S向量2 &, const S向量2 &);
	float operator()(float) const;
	S指数函数 &fs原点(const S向量2 &, const S向量2 &, const S向量2 &);
	float f求y(const float &) const;
};

}	//namespace cflw::数学