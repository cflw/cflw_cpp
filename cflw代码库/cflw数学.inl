#pragma once
#include "cflw数学.h"
namespace cflw::数学 {
//==============================================================================
// 基本数学函数
//==============================================================================
template<typename t> int f取符号(const t &x) {
	return (x < 0) ? -1 : (x > 0 ? 1 : 0);
}
template<typename t> int f取符号(const t &x, const t &a零) {
	return (x < -a零) ? -1 : (x > a零 ? 1 : 0);
}
template<typename t> const t& f最大值(const t &a, const t &b) {
	return a > b ? a : b;
}
template<typename t> const t& f最小值(const t &a, const t &b) {
	return a < b ? a : b;
}
template<typename t> std::pair<const t &, const t &> f小大(const t &a, const t &b) {
	using r = std::pair<const t &, const t &>;
	return a < b ? r{a, b} : r{b, a};
}
template<typename t> t f限制(const t &值, const t &最小值, const t &最大值) {
	return (值 > 最大值) ? 最大值 : ((值 < 最小值) ? 最小值 : 值);
}
template<typename t> t f接近(const t &源值, const t &目标值, const t &接近差) {
	return ((f绝对值(源值 - 目标值) <= 接近差) ? 目标值 : 源值);
}
template<typename t> t f倍数渐变(const t &a源值, const t &a目标值, const float &a差值渐变倍数, const t &a最小渐变 = (t)0, const t &a最大渐变 = std::numeric_limits<t>::max()) {
	if (a源值 == a目标值) {
		return a源值;
	} else {
		const t v差值 = a目标值 - a源值;
		const t v渐变值 = (t)(v差值 * a差值渐变倍数);
		const t v限制渐变值 = f限制<t>(f绝对值<t>(v渐变值), f绝对值<t>(a最小渐变), f绝对值<t>(a最大渐变)) * f取符号<t>(v差值);
		const t v接近值 = f接近<t>(a源值 + v限制渐变值, a目标值, f绝对值<t>(a最小渐变));
		return v接近值;
	}
}
template<typename t> t f线性渐变(const t &a源值, const t &a目标值, const float &a渐变值) {
	if (a源值 == a目标值) {
		return a源值;
	} else {
		return f接近<t>(a源值 + (t)(a渐变值 * f取符号(a目标值 - a源值)), a目标值, (t)a渐变值);
	}
}
template<typename t> t f下整除(const t &a被除数, const t &a除数) {
	if constexpr (std::is_integral_v<t>) {
		return (a被除数 < 0) ?
			(a被除数 / a除数 + ((a被除数 % a除数 == 0) ? 0 : -1)) :
			(a被除数 / a除数);
	} else {
		return floor(a被除数 / a除数);
	}
}
template<typename t> t f上整除(const t &a被除数, const t &a除数) {
	if constexpr (std::is_integral_v<t>) {
		return (a被除数 <= 0) ?
			(int)(a被除数 / a除数) :
			(int)(a被除数 / a除数 + ((a被除数 % a除数 == 0) ? 0 : 1));
	} else {
		return ceil(a被除数 / a除数);
	}
}
template<typename t> t f求余(const t &a源值, const t &a除数) {
	return a源值 - a除数 * f下整除<t>(a源值, a除数);
}
template<typename t> bool f限制循环(t &a值, const t &a最大值) {
	//达到最大值则清零并返回真
	if (a值 >= a最大值) {
		a值 -= a最大值;
		return true;
	} else {
		return false;
	}
}
template<typename t> t f绝对值(const t &a) {
	return ((a > 0) ? (a) : (-a));
}
template<typename t> std::tuple<t, t> sincos(const t &a) {
	return {sin(a), cos(a)};
}
//插值
template<typename t> t f插值(const t &a0, const t &a1, float p) {
	return a0 + (a1 - a0) * p;
}
//限
template<typename t> int f限(t &a0, const t &a1) {
	const int v倍数 = f下整除<int>(a0, a1);
	a0 -= v倍数 * a1;
	return v倍数;
}
//
template<typename t> bool f同符号(const t &a1, const t &p2) {
	return (f取符号<t>(a1) == f取符号<t>(p2));
}
//平方立方
template<typename t> t f平方(const t &a) {
	return a * a;
}
template<typename t> t f立方(const t &a) {
	return a * a * a;
}
//
template<typename t> t f对齐(const t &x, const t &y) {
	const t a = x / y;
	const t b = floor(a);
	const t c = a - b;
	if (c < 0.5) {
		return y * b;
	} else {
		return y * ceil(a);
	}
}
template<typename t> t f循环(const t &a, const t &a最小, const t &a最大) {
	const t v差 = a最大 - a最小;
	const t v基本倍 = f下整除<t>(a, v差);
	const t v循环倍 = f上整除<t>(a最小, v差);
	return a - v差 * (v基本倍 - v循环倍);
}
template<typename t> t f差(const t &a, const t &b) {
	if (a >= b) {
		return a - b;
	} else {
		return b - a;
	}
}
template<typename tk, typename tv> tv f插值2(const std::pair<tk, tv> &a0, const std::pair<tk, tv> &a1, const tk &a键) {
	const tk k = (a键 - a0.first) / (a1.first - a0.first);
	return f插值<tv>(a0.second, a1.second, k);
}
template<typename tk, typename tv> tv f插值2(const tk &a键0, const tv &a值0, const tk &a键1, const tv &a值1, const tk &a键) {
	const tk k = (a键 - a键0) / (a键1 - a键0);
	return f插值<tv>(a值0, a值1, k);
}
template<typename t> t f反勾股(const t &a斜边, const t &a直角边) {
	return sqrt(a斜边*a斜边 - a直角边*a直角边);
}
template<typename t> t f四舍五入(const t &a数字) {
	const float v舍 = floor(a数字);
	return (a数字 - v舍 < (t)0.5) ? v舍 : (v舍 + 1);
}
template<typename t> t f等腰梯形插值(const t &a小, const t &a大, float a斜宽, float x) {
	if (x < a斜宽) {
		return f插值<t>(a小, a大, x / a斜宽);
	} else if (const float v右边 = 1 - a斜宽; x > v右边) {
		return f插值<t>(a大, a小, (x - v右边) / a斜宽);
	} else {
		return a大;
	}
}
template<typename...t参数> auto f算术平均(t参数 &&...a参数) {
	return (... + a参数) / sizeof...(t参数);
}
template<typename...t参数> auto f几何平均(t参数 &&...a参数) {
	return sqrt(... * a参数);
}
template<typename...t参数> auto f绝对值最大值(t参数 &&...a参数) {
	using t返回 = decltype((... + a参数));
	t返回 v最大值 = 0;
	t返回 v原值 = 0;
	auto f = [&](const t返回 &a) {
		const t返回 v绝对值 = abs(a);
		if (v最大值 < v绝对值) {
			v最大值 = v绝对值;
			v原值 = a;
		}
	};
	(f(a参数), ...);
	return v原值;
}
//==============================================================================
// 各种计算类
//==============================================================================
template<typename t> const C角度计算<t> C角度计算<t>::c度(360);
template<typename t> const C角度计算<t> C角度计算<t>::c弧度(c二π<t>);
//角度计算
template<typename t> C角度计算<t>::C角度计算(const t &a周角) :
	m周角{a周角}, m平角{a周角 / 2} {
}
template<typename t> t C角度计算<t>::f平均(const t &a角1, const t &a角2) const {
	t v角1 = f取正(a角1);
	t v角2 = f取正(a角2);
	if (v角1 == v角2) {
		return v角1;
	} else if (v角1 >= v角2) {
		std::swap(v角1, v角2);
	}
	if (abs(v角2 - v角1) >= m平角) {
		v角2 -= m周角;
	}
	return (v角1 + v角2) / 2;
}
template<typename t> t C角度计算<t>::f取正(const t &a角) const {
	return a角 - floor(a角 / m周角) * m周角;
}
template<typename t> t C角度计算<t>::f限制(const t &a角) const {
	t v角 = a角 + m平角;
	v角 -= floor(v角 / m周角) * m周角;
	v角 -= m平角;
	return v角;
}
template<typename t> t C角度计算<t>::f取半(const t &a角) const {
	return a角 - floor(a角 / m平角) * m平角;
}
template<typename t> t C角度计算<t>::f旋转渐变(const t &s, const t &d, const t &max) const {
	const t v差 = f取正(d - s);
	if (f取半(v差) <= max) {
		return d;
	} else {
		if (v差 > m周角 / 2) {
			return s - max;
		} else {
			return s + max;
		}
	}
}
template<typename t> t C角度计算<t>::f夹角(const t &a角1, const t &a角2) const {
	t v = a角1 - a角2;
	v = f取正(v);
	if (v >= m平角) {
		v = m周角 - v;
	}
	return v;
}
template<typename t> t C角度计算<t>::f方向(const t &x, const t &y) const {
	return atan2(y, x) / (c二π<t> / m周角);
}
template<typename t> t C角度计算<t>::f插值(const t &a角1, const t &a角2, const t &a插值) const {
	t v = a角2 - a角1;	//角1到角2的夹角
	v = f取正(v);
	if (v > m平角) {
		v = m周角 - v;	//获得夹角
		return a角1 - v * a插值;
	} else {
		return a角1 + v * a插值;
	}
}
//==============================================================================
// 未实现
//==============================================================================
template<typename t> t f点乘(const t&, const t&) {
	static_assert(false, "未实现");
}
template<typename t> t f叉乘(const t&, const t&) {
	static_assert(false, "未实现");
}
template<typename t> t f负(const t&) {
	static_assert(false, "未实现");
}
}	//namespace cflw::数学 
