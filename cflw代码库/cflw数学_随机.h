#pragma once
#include <random>
#include "cflw数学.h"
#include "cflw数学_平面几何.h"
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
//分布类
template<typename t>
class C零一分布 {
public:
	C零一分布(double a = 0.5) :
		m伯努利分布(a) {
	}
	template<typename t引擎>
	t operator()(t引擎 &a引擎) const {
		return m伯努利分布(a引擎) ? (t)1 : (t)0;
	}
private:
	std::bernoulli_distribution m伯努利分布;
};
template<>
class C零一分布<bool> {
public:
	C零一分布(double a = 0.5) :
		m伯努利分布(a) {
	}
	template<typename t引擎>
	bool operator()(t引擎 &a引擎) const {
		return m伯努利分布(a引擎);
	}
private:
	std::bernoulli_distribution m伯努利分布;
};
class C圆形分布 {
public:
	C圆形分布(const S圆形 &);
	template<typename t引擎>
	S向量2 operator()(t引擎 &a引擎) const {
		return f生成(a引擎());
	}
	S向量2 f生成(unsigned int) const;
private:
	S圆形 m圆形;
};
class C矩形分布 {
public:
	C矩形分布(const S矩形 &);
	C矩形分布(const S旋转矩形 &);
	template<typename t引擎>
	S向量2 operator()(t引擎 &a引擎) const {
		return f生成(a引擎());
	}
	S向量2 f生成(unsigned int) const;
private:
	S旋转矩形 m矩形;
};
//分布常量
template<typename t = double> 
static const std::uniform_real_distribution<t> c圆周分布r = std::uniform_real_distribution<t>(0, c二π<t>);
template<typename t = double> 
static const std::uniform_real_distribution<t> c圆周分布d = std::uniform_real_distribution<t>(0, (t)360);
template<typename t = double>
static const auto c零一分布 = C零一分布<t>(0.5f);
template<>
static const auto c零一分布<bool> = std::bernoulli_distribution(0.5f);
}	//namespace cflw::数学