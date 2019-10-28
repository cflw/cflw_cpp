#pragma once
#include <functional>
template<typename t>
class C管线 {
public:
	C管线(const t &a):
		m(a) {
	}
	template<typename t1>
	C管线<t1> operator >>(const std::function<t1(const t &)> &af) {
		return C管线<t1>(af(m));
	}
	const t &m;
};