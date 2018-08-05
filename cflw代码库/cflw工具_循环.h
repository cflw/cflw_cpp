#pragma once
#include <vector>
namespace cflw {
namespace 工具 {
namespace 循环 {
//--------------------------------------------------------------------------------
// 循环基类
//--------------------------------------------------------------------------------
template<typename t循环> class I循环 {
public:	//在循环类中继承
	class C迭代器 {
	public:
		C迭代器(t循环 *p) : mp循环{p} {
		}
		C迭代器 &operator ++() {
			mp循环->f循环控制_自增();
			return *this;
		}
		bool operator !=(const C迭代器 &) {
			return mp循环->f循环控制_w继续();
		}
		decltype(std::declval<t循环>().f循环控制_解引用()) operator *() {
			return mp循环->f循环控制_解引用();
		}
		t循环 *mp循环;
	};
	C迭代器 begin() {
		return{(t循环 *)this};
	}
	C迭代器 end() {
		return{(t循环 *)this};
	}
	//可重写
	void f循环控制_自增() {
	}
	bool f循环控制_w继续() {
		return false;
	}
	t循环 &f循环控制_解引用() {
		return *((t循环*)this);
	}
};
//--------------------------------------------------------------------------------
// 计数
//--------------------------------------------------------------------------------
template<typename t循环, typename t = int> class C循环基础_计数 : public I循环<t循环> {
public:
	C循环基础_计数(const t &p) :
		m计数{0}, m总数{p} {
	}
	void f循环控制_自增() {
		++m计数;
	}
	bool f循环控制_w继续() {
		return m计数 != m总数;
	}
	t &f循环控制_解引用() {
		return m计数;
	}
	t m计数, m总数;
};
//--------------------------------------------------------------------------------
// 范围
//--------------------------------------------------------------------------------
template<typename t容器> class C范围 final {
public:
	typedef typename std::conditional<std::is_const<t容器>::value, typename t容器::const_reference, typename t容器::reference>::type t引用;
	class C迭代器 {
	public:
		C迭代器(t容器 *pp, int pi) :
			mp{pp}, mi{pi} {
		}
		C迭代器 &operator ++() {
			++mi;
			return *this;
		}
		bool operator !=(const C迭代器 &p) {
			return mi != p.mi;
		}
		t引用 operator *() {
			return (*mp)[mi];
		}
		int mi;
		t容器 *mp;
	};
	C范围(t容器 &pp, int p0, int p1) :
		m0{std::max<int>(p0, 0)}, m1{std::min<int>(p1, (int)pp.size())}, mp{&pp} {
	}
	C迭代器 begin() {
		return C迭代器{mp, m0};
	}
	C迭代器 end() {
		return C迭代器{mp, m1};
	}
	int m0, m1;
	t容器 *mp;
};
//--------------------------------------------------------------------------------
//零散
//--------------------------------------------------------------------------------
template<typename t容器> class C零散 final : public I循环<C零散<t容器>> {
public:
	typedef decltype(std::declval<t容器>().front()) t引用;
	typedef decltype(std::declval<t容器>().data()) t指针;
	C零散() = default;
	C零散(t容器 &p容器, const std::initializer_list<int> &p表) {
		const t指针 v指针 = p容器.data();
		const int v数量 = (int)p表.size();
		ma指针.reserve(v数量);
		for (const int &v序号 : p表) {
			if (v序号 >= 0 && v序号 < v数量) {
				ma指针.push_back(v指针 + v序号);
			}
		}
		f循环控制_开始();
	}
	C零散(t容器 &p容器, const std::vector<int> &p表) {
		const t指针 v指针 = p容器.data();
		const int v数量 = (int)p容器.size();
		ma指针.reserve(v数量);
		for (const int &v序号 : p表) {
			if (v序号 >= 0 && v序号 < v数量) {
				ma指针.push_back(v指针 + v序号);
			}
		}
		f循环控制_开始();
	}
	void f循环控制_开始() {
		m当前 = ma指针.begin();
		m结束 = ma指针.end();
	}
	void f循环控制_自增() {
		++m当前;
	}
	bool f循环控制_w继续() {
		const bool vw继续 = (m当前 != m结束);
		if (!vw继续) {
			f循环控制_开始();
		}
		return vw继续;
	}
	t引用 f循环控制_解引用() {
		return **m当前;
	}
	std::vector<t指针> ma指针;
	typename std::vector<t指针>::iterator m当前, m结束;
};
//--------------------------------------------------------------------------------
// 前后,引用一个元素的时候还能引用前后
//--------------------------------------------------------------------------------
template<typename t容器> class C前后 final : public I循环<C前后<t容器>> {
public:
	typedef decltype(std::declval<t容器>().data()) t指针;
	typedef decltype(std::declval<t容器>().begin()) t迭代器;
	struct S引用 {
		t指针 m前, m这, m后;
		bool fw前() const {
			return m前 == m这;
		}
		bool fw后() const {
			return m后 == m这;
		}
	};
	C前后(t容器 &p容器) :
		m当前{p容器.begin()}, m结束{p容器.end()} {
		m引用.m前 = m引用.m这 = f这();
	}
	bool f循环控制_w继续() {
		if (m当前 != m结束) {
			m引用.m这 = f这();
			m引用.m后 = f后();
			return true;
		} else {
			return false;
		}
	}
	void f循环控制_自增() {
		m引用.m前 = m引用.m这;
		++m当前;
	}
	S引用 &f循环控制_解引用() {
		return m引用;
	}
	t指针 f这() {
		return &(*m当前);
	}
	t指针 f后() {
		const t迭代器 m后面 = m当前 + 1;
		if (m后面 != m结束) {
			return &(*m后面);
		} else {
			return f这();
		}
	}
	t迭代器 m当前, m结束;
	S引用 m引用;
};
//--------------------------------------------------------------------------------
// 线性
//--------------------------------------------------------------------------------
template<typename t容器, typename t数值 = float> class C线性 final : public I循环<C线性<t容器>> {
public:
	typedef decltype(std::declval<t容器>().data()) t指针;
	typedef decltype(std::declval<t容器>().begin()) t迭代器;
	struct S引用 {
		t指针 m前, m后;
		t数值 m插值;
	};
	C线性(t容器 &p容器, t数值 p数量) :
		m当前{p容器.begin()}, m后面{m当前 + 1}, m结束{p容器.end()}, m递增{(t数值)(p容器.size() - 1) / p数量} {
		m引用.m前 = &(*m当前);
		if (m后面 != m结束) {
			m引用.m后 = &(*m后面);
		}
	}
	void f循环控制_自增() {
		m引用.m插值 += m递增;
		if (m引用.m插值 > 1) {
			m引用.m插值 -= 1;
			++m当前;
			m后面 + 1;
		}
	}
	bool f循环控制_w继续() {
		return m后面 != m结束;
	}
	S引用 &f循环控制_解引用() {
		return m引用;
	}
	t迭代器 m当前, m后面, m结束;
	S引用 m引用;
	t数值 m递增;
};
}	//namespace 循环
}}	//命名空间结束