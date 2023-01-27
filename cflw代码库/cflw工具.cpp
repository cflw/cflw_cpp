#include <assert.h>
#include "cflw工具.h"
#include "cflw异常.h"
namespace cflw::工具 {
//==============================================================================
// 计次器
//==============================================================================
void C计次器::f重置(int i) {
	m间隔 = i;
	m次数 = 0;
}
bool C计次器::f滴答() {
	++m次数;
	if (m次数 >= m间隔) {
		m次数 = 0;
		return true;
	} else {
		return false;
	}
}
//==============================================================================
// 数据
//==============================================================================
C数据::C数据(unsigned int a大小) : m指针(new unsigned char[a大小]), m大小(a大小) {
}
C数据::C数据(const C数据 &a数据) {
	if (a数据.m指针) {
		f新建(a数据.m大小);
		f复制(a数据.m指针, a数据.m大小);
	}
}
C数据::~C数据() {
	if (m指针) {
		delete[] m指针;
	}
}
bool C数据::f新建(unsigned int a大小) {
	f删除();
	m指针 = new unsigned char[a大小];
	if (m指针 != nullptr) {
		m大小 = a大小;
		return true;
	} else {
		return false;
	}
}
void C数据::f删除() {
	if (m指针) {
		delete[] m指针;
		m指针 = nullptr;
		m大小 = 0;
	}
}
void C数据::f复制(void *a指针, unsigned int a大小) {
	const unsigned int v复制大小 = (m大小 >= a大小) ? a大小 : m大小;
	memcpy(m指针, a指针, v复制大小);
}
void C数据::f复制(const C数据 &a数据) {
	if (a数据.m指针) {
		f复制(a数据.m指针, a数据.m大小);
	}
}
unsigned char *&C数据::fg数据() {
	return m指针;
}
unsigned int C数据::fg大小() {
	return m大小;
}
//==============================================================================
// 位大小,位指针
//==============================================================================
//位大小
S位大小::S位大小(int a字节, int a位):
	v字节(a字节 + a位 / 8),
	v位(a位 % 8)
{}
S位大小 &S位大小::operator +=(const S位大小 &a大小) {
	v字节 += a大小.v字节;
	v位 += a大小.v位;
	while (v位 >= 8) {
		v字节 += 1;
		v位 -= 8;
	}
	return *this;
}
S位大小 S位大小::operator +(const S位大小 &a大小) const {
	return S位大小(v字节 + a大小.v字节, v位 + a大小.v位);
}
S位大小::operator int() const {
	return v字节 * 8 + v位;
}
//位指针
C位指针::C位指针():
	v指针(nullptr),
	v偏移(0, 0)
{}
C位指针::C位指针(void *a指针):
	v指针(a指针),
	v偏移(0, 0)
{}
C位指针::C位指针(void *a指针, int a位):
	v指针(a指针),
	v偏移(0, a位)
{}
C位指针 &C位指针::fs指针(void *a指针, int a位) {
	v指针 = a指针;
	v偏移.v字节 = 0;
	v偏移.v位 = a位;
	return *this;
}
void C位指针::f读(void *a指针, const S位大小 &a大小) {
	assert(v指针);
	f内存复制(*this, C位指针(a指针), a大小);
}
void C位指针::f读(const C位指针 &a指针, const S位大小 &a大小) {
	assert(v指针);
	f内存复制(*this, a指针, a大小);
}
void C位指针::f写(void *a指针, const S位大小 &a大小) {
	assert(v指针);
	f内存复制(C位指针(a指针), *this, a大小);
}
void C位指针::f写(const C位指针 &a指针, const S位大小 &a大小) {
	assert(v指针);
	f内存复制(a指针, *this, a大小);
}
C位指针 &C位指针::f偏移(const S位大小 &a位大小) {
	v偏移 += a位大小;
	return *this;
}
void C位指针::f内存复制(const C位指针 &a左, const C位指针 &a右, const S位大小 &a大小) {
	f内存复制(a左.v指针, a左.v偏移, a右.v指针, a右.v偏移, a大小);
}
void C位指针::f内存复制(void *a指针1, int a偏移1, void *a指针2, int a偏移2, int a大小) {
	while (a大小 > 0) {
		const int v数据大小 = (a大小 >= 8) ? 8 : a大小;
		const unsigned long v数据 = f取数据(a指针2, a偏移2, v数据大小);
		f赋数据(a指针1, a偏移1, v数据);
		++(unsigned char *&)a指针1;
		++(unsigned char *&)a指针2;
		a大小 -= 8;
	}
}
unsigned long C位指针::f取数据(void *a指针, int a偏移, int a大小) {
	assert(a偏移 + a大小 <= 32);
	unsigned long v数据 = *((unsigned long *)a指针);
	v数据 = v数据 >> a偏移;
	v数据 &= 0xffffffff >> (32 - a大小);
	return v数据;
}
void C位指针::f赋数据(void *a指针, int a偏移, unsigned long a数据) {
	unsigned char *v指针 = (unsigned char *)a指针;
	unsigned long v数据 = a数据 << a偏移;
	//第1字节
	*v指针 &= 0xff >> (8 - a偏移);
	*v指针 |= (unsigned char)v数据;
	//第2字节
	*(++v指针) = (unsigned char)(v数据 >> 8);
	//第3字节
	*(++v指针) = (unsigned char)(v数据 >> 16);
	//第4字节
	*(++v指针) = (unsigned char)(v数据 >> (24 - a偏移));
}
}	//namespace cflw::工具