#pragma once
namespace cflw::工具 {
//==============================================================================
// 属性
//==============================================================================
template<typename t原, typename t属性, typename tf原g = typename t属性(t原::*)() const, typename tf原s = typename t原&(t原::*)(const t属性 &)>
class C属性 {
public:
	C属性(t原 &a原, tf原g af原g, tf原s af原s):
		m原(&a原), mf原g(af原g), mf原s(af原s) {
	}
	t属性 fg() const {
		return (m原->*mf原g)();
	}
	C属性 &fs(const t属性 &) const {
		(m原->*mf原s)(a);
		return *this;
	}
	operator t属性() const {
		return fg();
	}
	C属性 &operator =(const t属性 &a) const {
		return fs(a);
	}
	t属性 operator ->() const {
		return fg();
	}
	template<typename...t参数> auto operator ()(t参数 &&...a参数) const {
		return (m原->*mf原g)()(a参数...);
	}
	template<typename t> auto operator +(const t &a) const {
		return fg() + a;
	}
	template<typename t> auto operator -(const t &a) const {
		return fg() - a;
	}
	template<typename t> auto operator *(const t &a) const {
		return fg() * a;
	}
	template<typename t> auto operator /(const t &a) const {
		return fg() / a;
	}
	template<typename t> auto operator %(const t &a) const {
		return fg() % a;
	}
	template<typename t> C属性 &operator +=(const t &a) const {
		return fs(fg() + a);
	}
	template<typename t> C属性 &operator -=(const t &a) const {
		return fs(fg() - a);
	}
	template<typename t> C属性 &operator *=(const t &a) const {
		return fs(fg() * a);
	}
	template<typename t> C属性 &operator /=(const t &a) const {
		return fs(fg() / a);
	}
	template<typename t> C属性 &operator %=(const t &a) const {
		return fs(fg() % a);
	}
	t原 *m原 = nullptr;
	tf原g mf原g = nullptr;
	tf原s mf原s = nullptr;
};
}	//namespace cflw::工具