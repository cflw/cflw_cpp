#pragma once
#include <random>
#include "cflw数学_平面几何.h"
#define 定义随机数分布计算函数 \
template<typename t>\
auto operator()(t &p) {\
	return f生成(p());\
}
namespace cflw::数学 {
//==============================================================================
// 随机引擎
//==============================================================================
class C线性同余 {
public:
	unsigned long a;		//随机数种子a
	unsigned long b;		//随机数种子b
	unsigned long r;		//上次计算结果
	static constexpr unsigned long c最大值 = 0x00ffffff;	//随机数最大值
	C线性同余();		//构造函数
	void f置种子(const unsigned long &);
	void f计算();	//计算一个随机数
	unsigned long f生成();
	template<class t> t f生成(const t &, const t &);
	bool f生成(const float &);
};
template<class t> t C线性同余::f生成(const t &a小, const t &a大) {
	f计算();
	const t v差 = a大 - a小;
	return (t)(a小 + (t)r / (t)c最大值 * v差);
}
//==============================================================================
// 分布
//==============================================================================
template<typename t = double> std::uniform_real_distribution<t> f圆周分布r() {
	return std::uniform_real_distribution<t>(0, 数学::c二π<t>);
}
template<typename t = double> std::uniform_real_distribution<t> f圆周分布d() {
	return std::uniform_real_distribution<t>(0, (t)360);
}
class C圆形分布 {
public:
	C圆形分布(const S圆形 &);
	定义随机数分布计算函数
	S向量2 f生成(unsigned int) const;
private:
	S圆形 m圆形;
};
class C矩形分布 {
public:
	C矩形分布(const S旋转矩形 &);
	定义随机数分布计算函数
	S向量2 f生成(unsigned int) const;
private:
	S旋转矩形 m矩形;
};
}	//namespace cflw::数学