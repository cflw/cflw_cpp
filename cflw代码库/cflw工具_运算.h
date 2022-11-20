#pragma once
#include <algorithm>
#include <functional>
namespace cflw::工具 {
//四则运算
template<typename t> using F加 = std::plus<t>;
template<typename t> using F减 = std::minus<t>;
template<typename t> using F乘 = std::multiplies<t>;
//简单比较
template<typename t>
bool f等于(const t &a0, const t &a1) {
	return a0 == a1;
}
template<typename t>
bool f不等于(const t &a0, const t &a1) {
	return a0 != a1;
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
template<typename t>
std::function<bool(const t &)> F比较值(auto &&af, const t &b) {
	return std::bind(af, std::placeholders::_1, b);
}
template<typename t>
std::function<bool(const t &)> F等于值(const t &b) {
	return F比较值(f等于<t>, b);
}
template<typename t>
std::function<bool(const t &)> F小于值(const t &b) {
	return F比较值(f小于<t>, b);
}
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
//夹取
template<typename t>
t f夹取(const t &a开始, const t &a结束, const t &a当前) {
	if (a当前 < a开始) {
		return a结束 - 1;
	} else if (a当前 >= a结束) {
		return a开始;
	} else {
		return a当前;
	}
}
template<typename t>
struct F夹取 {
	F夹取(t a开始, t a结束):
		m开始(a开始), m结束(a结束) {
	}
	t operator()(const t &a) const {
		return f夹取(m开始, m结束, a);
	}
	t m开始, m结束;
};
//环绕自增自减
template<typename t>
t &f环绕自增(const t &a开始, const t &a结束, t &a当前) {
	if (a当前 >= a结束 - 1) {
		return a当前 = a开始;
	} else {
		return ++a当前;
	}
}
template<typename t>
t &f环绕自减(const t &a开始, const t &a结束, t &a当前) {
	if (a当前 <= a开始) {
		return a当前 = a结束 - 1;
	} else {
		return --a当前;
	}
}
//哈希
inline size_t f数据哈希(const void *a指针, size_t a大小) {
	constexpr size_t c位数 = sizeof(size_t);
	const size_t *v指针 = (size_t*)a指针;
	size_t v和 = 0;
	for (size_t v偏移 = 0; v偏移 < a大小 / c位数; ++v偏移) {
		v和 += v指针[v偏移];
	}
	return v和 ^ a大小;
}
}	//namespace cflw::工具