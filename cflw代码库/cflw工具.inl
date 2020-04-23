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
// 数字与文本的转换
//==============================================================================
#define _文本转换模板(t1, t2, f) \
	template<> t2 C文本::f转换<t1, t2>(t1 p);
#define _文本转换模板_到文本(t, f) _文本转换模板(t, C文本::t字符串, f<t>)
#define _文本转换模板_到数字(t, f) _文本转换模板(C文本::t字符串, t, f<t>)
_文本转换模板_到文本(unsigned char, f整数_文本)
_文本转换模板_到文本(unsigned long, f整数_文本)
_文本转换模板_到文本(int, f整数_文本)
_文本转换模板_到文本(long long, f整数_文本)
_文本转换模板_到文本(float, f浮点数_文本)
_文本转换模板_到文本(double, f浮点数_文本)
_文本转换模板_到数字(unsigned char, f文本_整数)
_文本转换模板_到数字(unsigned long, f文本_整数)
_文本转换模板_到数字(int, f文本_整数)
_文本转换模板_到数字(long long, f文本_整数)
_文本转换模板_到数字(float, f文本_浮点数)
_文本转换模板_到数字(double, f文本_浮点数)
#undef _文本转换模板
#undef _文本转换模板_到文本
#undef _文本转换模板_到数字
template<typename t> C文本::t字符串 C文本::f整数_文本(t n) {
	wchar_t v[sizeof(t)*3] = L"";
	int v修改位 = 0;
	if (n < 0) {
		v[v修改位++] = L'-';
		n = n * -1;
	} else if (n == 0) {
		return L"0";
	}
	int v最高位 = (int)log10(n);
	while (v最高位 >= 0) {
		const t v指数 = (t)pow((t)10, v最高位);
		v[v修改位++] = (wchar_t)(L'0' + n / v指数);
		n = (n % v指数);
		v最高位 -= 1;
	}
	return {v};
}
template<typename t> C文本::t字符串 C文本::f浮点数_文本(t n) {
	wchar_t v[sizeof(t)*3] = L"";
	int v有效数字 = sizeof(t) + 2;
	int v修改位 = 0;
	//取负号
	if (n < 0) {
		v[v修改位++] = L'-';
		n = n * -1;
	} else if (n == 0) {
		return L"0";
	}
	int v当前位 = (int)log10(n);
	int v小数位 = 0;
	while (v有效数字) {
		const t v指数 = pow((t)10, v当前位);
		const t v指数2 = v指数 * 10;
		t v数字 = (n - floor(n / v指数2) * v指数2) / v指数;
		//补精度损失
		v数字 += FLT_EPSILON;
		if (v数字 >= 10) {
			v数字 -= 10;
		}
		//写文本
		v[v修改位++] = (wchar_t)(L'0' + v数字);
		if (v当前位 == 0) {//加小数
			v小数位 = v修改位++;
			v[v小数位] = L'.';
		}
		v当前位 -= 1;
		v有效数字 -= 1;
	}
	return {v};
}
template<typename t> t C文本::f文本_整数(const t字符串 &s) {
	t v = 0;
	int v读取位 = 0;
	t v符号 = 1;
	//取负号
	if (!辅助::fi无符号(v)) {
		if (s[v读取位] == L'-') {
			v符号 = (t)(-1);
			++v读取位;
		}
	}
	//计算多少位
	int v位数 = 0;
	while (s[v读取位] >= L'0' && s[v读取位] <= L'9') {
		++v位数;
		++v读取位;
	}
	//溢出判断
	if (sizeof(t) * 8 * log10(2) < v位数) {
		throw;
	}
	//赋值
	int v当前位 = 0;
	while (v当前位 < v位数) {
		v += (t)((s[--v读取位] - L'0') * pow((t)10, v当前位));
		++v当前位;
	}
	return v * v符号;
}
template<typename t> t C文本::f文本_浮点数(const t字符串 &s) {
	t v = 0;
	int v读取位 = 0;
	t v符号 = 1;
	//取负号
	if (!辅助::fi无符号(v)) {
		if (s[v读取位] == L'-') {
			v符号 = -1;
			++v读取位;
		}
	}
	//计算多少位
	int v位数 = 0;
	int v有效数字 = sizeof(t) + 2;
	int v小数位置 = -1;
	while (v位数 <= v有效数字) {
		const wchar_t v读取字符 = s[v读取位];
		if (v读取字符 >= L'0' && v读取字符 <= L'9') {
			++v位数;
		} else if (v读取字符 == L'.') {
			v小数位置 = v位数;
		} else {
			break;
		}
		++v读取位;
	}
	//赋值
	int v当前位 = 0;
	while (v当前位 < v位数) {
		const wchar_t v读取字符 = s[--v读取位];
		if (v读取字符 == L'.') {
			continue;
		}
		v += (v读取字符 - L'0') * (t)pow((t)10, v当前位);
		++v当前位;
	}
	v *= (t)pow((t)10, v小数位置 - v位数);
	return v * v符号;
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