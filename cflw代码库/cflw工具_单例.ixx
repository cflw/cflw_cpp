module;
#include <cassert>
#include <concepts>
export module cflw.工具.单例;
export namespace cflw::工具 {
//概念
template<typename t> concept T单例 = requires(t a) {
	t::g这;
	t::fg实例();
	requires !std::copyable<t>;
};
//类
template<typename t>
class C单例 {
public:
	static t *g这;
	C单例() {
		assert(!g这);
		g这 = static_cast<t *>(this);
	}
	C单例(const C单例<t> &) = delete;	//阻止派生类默认复制&移动
	C单例(C单例<t> &&) = delete;
	C单例<t> &operator=(const C单例<t> &) = delete;
	C单例<t> &operator=(C单例<t> &&) = delete;
	static t &fg实例() {
		static t v;
		return v;
	}
};
template<typename t>
class C弱单例 {	//类本身只有一个静态指针,不维护对象生命周期
public:
	static t *g这;
	C弱单例() {
		assert(!g这);
		g这 = static_cast<t*>(this);
	}
	C弱单例(const C弱单例<t> &) = delete;	//阻止派生类默认复制&移动
	C弱单例(C弱单例<t> &&) = delete;
	C弱单例<t> &operator=(const C弱单例<t> &) = delete;
	C弱单例<t> &operator=(C弱单例<t> &&) = delete;
	static t &fg实例() {
		return *g这;
	}
};
template<typename t> inline t *C单例<t>::g这 = nullptr;
template<typename t> inline t *C弱单例<t>::g这 = nullptr;
}	//namespace cflw::工具