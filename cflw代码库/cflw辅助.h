#pragma once
#include <assert.h>
#include <memory>
#include <utility>
#ifdef _DEBUG
constexpr bool c调试 = true;
#else
constexpr bool c调试 = false;
#endif
namespace cflw::辅助 {
//删除指针
template<typename t> inline void f删除(t *&p) {
	if (p) {
		delete p;
		p = nullptr;
	}
}
//删除数组
template<typename t> inline void f删除数组(t *&p) {
	if(p) {
		delete[] p;
		p = nullptr;
	}
}
//强制删除
template<typename t> inline void f强制删除(t *&p) {
	delete p;
	p = nullptr;
}
//取数组元素数量
template<typename t> inline size_t f数组数量(const t &) {
	return sizeof(t) / sizeof(**(t*)nullptr);
}
//是否无符号类型
template<typename t> inline bool fi无符号(const t&) {
	return (t)-1 > 0;
}
//位计算
template <typename t> inline t f位赋值(const t &源值, const t &修改位, const unsigned char &值) {
	return (值) ? (源值 | 修改位) : (源值 & (~修改位));
}
template <typename t> inline t f位判断(const t &源值, const t &判断位) {
	return 源值 & 判断位;
}
//内存清空
template<typename t> inline void f清零(t &p) {
	memset((void*)&p, 0, sizeof(p));
}
//比较2个值，如果不相等则把后面赋给前面
template<typename t> inline bool f不等则赋值(t &p0, const t &p1) {
	if (p0 != p1) {
		p0 = p1;
		return true;
	}
	return false;
}
}	//namespace cflw::辅助
