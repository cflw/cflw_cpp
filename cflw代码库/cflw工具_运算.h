#pragma once
#include <algorithm>
namespace cflw::工具 {
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