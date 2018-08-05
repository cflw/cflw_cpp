#pragma once
#include <random>
#include "cflw数学_平面几何.h"
#define 定义随机数分布计算函数 \
template<typename t>\
auto operator()(t &p) {\
	return f生成(p());\
}
namespace cflw {
namespace 数学 {
//分布
template<typename t = double> std::uniform_real_distribution<t> f圆周分布r() {
	return std::uniform_real_distribution<t>(0, (t)数学::c二π);
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
}	//namespace 数学
}	//namespace cflw
