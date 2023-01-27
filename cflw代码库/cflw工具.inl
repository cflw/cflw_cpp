#pragma once
#include "cflw工具.h"
#include <math.h>
#include "cflw辅助.h"
namespace cflw::工具 {
//==============================================================================
// 计值器
//==============================================================================
template<typename t> void C计值器<t>::f清零() {
	m值数 = 0;
}
template<typename t> void C计值器<t>::f重置(t a) {
	m值数 = 0;
	m间隔 = a;
}
template<typename t> bool C计值器<t>::f滴答(t a) {
	m值数 += a;
	if (m值数 >= m间隔) {
		m值数 = 0;
		return true;
	} else {
		return false;
	}
}
//==============================================================================
// 空间
//==============================================================================
template<typename t> C空间<t>::~C空间() {
	if (m指针 != nullptr) {
		delete[] m指针;
	}
}
template<typename t> t *C空间<t>::f分配(unsigned int p数量) {
	if (m分配数量 < p数量) {
		if (m指针 != nullptr) {
			delete[] m指针;
		}
		m分配数量 = p数量 * 2;
		m指针 = new t[m分配数量];
	}
	m需要数量 = p数量;
	return m指针;
}
//==============================================================================
// 树
//==============================================================================
template<typename t> C树<t>::C节点::C节点(const t &a值, std::unique_ptr<std::vector<C节点>> &&a叶) :
	m值(a值),
	m叶(std::move(a叶)) {
}
}	//namespace cflw::工具