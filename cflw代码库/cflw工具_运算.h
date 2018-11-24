#pragma once
#include <algorithm>
namespace cflw::工具 {
//四则运算
template<typename t> using F加 = std::plus<t>;
template<typename t> using F减 = std::minus<t>;
template<typename t> using F乘 = std::multiplies<t>;
//简单比较
template<typename t>
bool f等于(const t &a0, const t &a1) {
	return a0 < a1;
}
template<typename t>
bool f不等于(const t &a0, const t &a1) {
	return a0 < a1;
}
template<typename t>
bool f小于(const t &a0, const t &a1) {
	return a0 < a1;
}
template<typename t>
bool f大于(const t &a0, const t &a1) {
	return a0 > a1;
}
template<typename t>
bool f小于等于(const t &a0, const t &a1) {
	return a0 <= a1;
}
template<typename t>
bool f大于等于(const t &a0, const t &a1) {
	return a0 >= a1;
}
template<typename t>
bool f永不(const t &a0, const t &a1) {
	return false;
}
template<typename t>
bool f总是(const t &a0, const t &a1) {
	return true;
}
template<typename t> using F等于 = std::equal_to<t>;
template<typename t> using F不等于 = std::not_equal_to<t>;
template<typename t> using F小于 = std::less<t>;
template<typename t> using F小于等于 = std::less_equal<t>;
template<typename t> using F大于 = std::greater<t>;
template<typename t> using F大于等于 = std::greater_equal<t>;
//比较枚举
enum E比较 {
	e永不,
	e小于,
	e等于,
	e小于等于,
	e大于,
	e不等于,
	e大于等于,
	e总是,
};
template<typename t> constexpr auto F比较(E比较 a比较)->bool(*)(const t &, const t &) {
	switch (a比较) {
	case e永不:
		return f永不<t>;
	case e小于:
		return f小于<t>;
	case e等于:
		return f等于<t>;
	case e小于等于:
		return f小于等于<t>;
	case e大于:
		return f大于<t>;
	case e不等于:
		return f不等于<t>;
	case e大于等于:
		return f大于等于<t>;
	case e总是:
		return f总是<t>;
	default:
		return f永不<t>;
	}
}
//逻辑运算
inline constexpr bool f且(bool a0, bool a1) {
	return a0 && a1;
}
inline constexpr bool f或(bool a0, bool a1) {
	return a0 || a1;
}
inline constexpr bool f非(bool a) {
	return !a;
}
//复杂比较
template<typename t, typename tF = std::hash<t>>
struct F哈希相等 {
	bool operator()(const t &a, const t &b) const {
		auto vf = tF();
		return vf(a) == vf(b);
	}
};
//自增自减
template<typename t>
t &f自增(t &a) {
	++a;
	return a;
}
template<typename t>
t &f自减(t &a) {
	--a;
	return a;
}
template<typename t>
struct F自增 {
	t &operator()(t &a) const {
		++a;
		return a;
	}
};
template<typename t>
struct F自减 {
	t &operator()(t &a) const {
		--a;
		return a;
	}
};
//循环
template<typename t>
t f循环(const t &a开始, const t &a结束, const t &a当前) {
	if (a当前 < a开始) {
		return a结束 - 1;
	} else if (a当前 >= a结束) {
		return a开始;
	} else {
		return a当前;
	}
}
template<typename t>
struct F循环 {
	F循环(t a开始, t a结束):
		m开始(a开始), m结束(a结束) {
	}
	t operator()(const t &a) const {
		return f循环(m开始, m结束, a);
	}
	t m开始, m结束;
};
//循环自增自减
template<typename t>
t &f循环自增(const t &a开始, const t &a结束, t &a当前) {
	if (a当前 >= a结束 - 1) {
		return a当前 = a开始;
	} else {
		return ++a当前;
	}
}
template<typename t>
t &f循环自减(const t &a开始, const t &a结束, t &a当前) {
	if (a当前 <= a开始) {
		return a当前 = a结束 - 1;
	} else {
		return --a当前;
	}
}
}	//namespace cflw::工具