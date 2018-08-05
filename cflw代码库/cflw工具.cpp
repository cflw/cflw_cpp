#include <assert.h>
#include "cflw工具.h"
#include "cflw异常.h"
namespace cflw {
namespace 工具 {
//==============================================================================
// 随机数
//==============================================================================
C随机数::C随机数():a(0),b(0),r(0){};
const unsigned long C随机数::max = 0x00ffffff;
void C随机数::f置种子(const unsigned long &种子) {
	r = 0;
	b = 种子;
	while (b > 0xffff)
		b /= 2;
	a = b;
	while (a > 0xff)
		a /= 2;
}
void C随机数::f计算() {	//计算一个随机数
	r = (a * r + b) % max;
}
unsigned long C随机数::f生成() {
	f计算 ();
	return r;
}
bool C随机数::f生成(const float &p) {
	return f生成<float>(0, 1) <= p;
}
//==============================================================================
// 计次器
//==============================================================================
void C计次器::f重置(int i) {
	v间隔 = i;
	v次数 = 0;
}
bool C计次器::f滴答() {
	++v次数;
	if (v次数 >= v间隔) {
		v次数 = 0;
		return true;
	} else {
		return false;
	}
}
//==============================================================================
// 文本编缉
//==============================================================================
#define _文本转换模板(t1, t2, f) \
	template<> t2 C文本::f转换<t1, t2>(t1 p) { \
		return C文本::f(p); \
	}
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
#undef _文本转换模板_到文本
#undef _文本转换模板_到数字
#undef _文本转换模板
C文本::t字符串 C文本::f数据_十六进制(const void *a数据, size_t a大小) {
	auto f = [](unsigned char a数字)->wchar_t {
		if (a数字 < 10) {
			return L'0' + a数字;
		} else {
			return L'a' + (a数字 - 10);
		}
	};
	std::unique_ptr<wchar_t[]> va缓冲 = std::make_unique<wchar_t[]>(a大小 * 2 + 1);
	unsigned char *v数据 = (unsigned char*)a数据;
	size_t v大小;
	for (v大小 = 0; v大小 != a大小; ++v大小) {
		unsigned char v数 = v数据[v大小];
		va缓冲[2*v大小] = f(v数 / 0x10);
		va缓冲[2*v大小+1] = f(v数 >> 4);
	}
	va缓冲[a大小 * 2] = 0;
	return {va缓冲.get()};
}
std::tuple<std::byte*, size_t> C文本::f十六进制_数据(const t字符串 &a文本) {
	auto f = [](wchar_t a字符)->unsigned char {
		if (a字符 >= L'0' && a字符 <= L'9') {
			return (unsigned char)(a字符 - L'0');
		} else if (a字符 >= L'A' && a字符 <= L'F') {
			return (unsigned char)(a字符 - L'A');
		} else if (a字符 >= L'a' && a字符 <= L'f') {
			return (unsigned char)(a字符 - L'a');
		}
		throw 异常::X参数("无效字符");
	};
	t字符串 v字符串 = (a文本.find(L"0x", 0) != 0) ? a文本 : a文本.substr(2);
	size_t v大小 = v字符串.size() * 2;
	std::byte *v数据 = new std::byte[v大小];
	for (size_t i = 0; i != v大小; ++i) {
		unsigned char &v当前数据 = (unsigned char &)v数据[i];
		v当前数据 = f(v字符串[2*i]) << 0x10;
		v当前数据 |= f(v字符串[2*i+1]);
		//if (2 * i + 2 >= v大小) {
		//	break;
		//}
	}
	return {v数据, v大小};
}
bool C文本::fw数字(const t字符串 &a文本) {
	bool v可负 = true;
	bool v可点 = true;
	bool v可e = true;
	for (int i = 0; i < a文本.size(); ++i) {
		const wchar_t v字 = a文本[i];
		if (v字 == L'-') {//负号
			if (v可负) {
				v可负 = false;
				continue;
			} else {
				return false;
			}
		} else if (v字 == L'.') {
			if (v可点) {
				v可点 = false;
				continue;
			} else {
				return false;
			}
		} else if (v字 == L'e' && v字 == L'E') {
			if (v可e) {
				v可e = false;
				v可点 = false;
				v可负 = true;
				continue;
			} else {
				return false;
			}
		} else if (v字 >= L'0' && v字 <= L'9') {
			v可负 = false;
			continue;
		} else if (v字 == L'\0') {
			return i != 0;
		} else {
			return false;
		}
	}
	return true;
}
int C文本::f查找(const t字符串 &a文本, const t字符串 &a查找, int a开始) {
	for (int i = a开始; i < a文本.size(); ++i) {
		if (i >= a文本.size() - a查找.size()) {
			return -1;
		}
		bool v结果 = true;
		for (int j = 0; j < a查找.size(); ++j) {
			if (a文本[i+j] != a查找[j]) {
				v结果 = false;
				break;
			}
		}
		if (v结果) {
			return i;
		}
	}
	return -1;
}
C文本::t字符串 C文本::f有效数字(const t字符串 &a文本, int a位数) {
	wchar_t v[16] = L"";
	int v修改位 = 0;
	bool v小数位 = false;
	for (; v修改位 < a文本.size(); ++v修改位) {
		const wchar_t v字 = a文本[v修改位];
		if (v字 == L'.') {
			v小数位 = true;
			continue;
		}
		if ((++v修改位) <= a位数) {
			v[v修改位] = v字;
		} else {
			if (v小数位) {
				break;
			}
			v[v修改位] = L'0';
		}
	}
	return {v};
}
C文本::t字符串 C文本::f小数位数(const t字符串 &a文本, int a位数) {
	wchar_t v[16] = L"";
	int v小数 = -999;
	int v修改位 = 0;
	for (; v修改位 < a文本.size(); ++v修改位) {
		const wchar_t v字 = a文本[v修改位];
		v[v修改位] = v字;
		if (v字 == L'.') {
			v小数 = 0;
		}
		if ((++v小数) > a位数) {
			return {v};
		}
	}
	//
	if (v小数 < 0) {
		v[v修改位++] = L'.';
		v小数 = 0;
	}
	while ((++v小数) <= a位数) {
		v[v修改位++] = L'0';
	}
	return {v};
}
//--------------------------------------------------------------------------------
// 数据
//--------------------------------------------------------------------------------
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
//--------------------------------------------------------------------------------
// 位大小,位指针
//--------------------------------------------------------------------------------
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
//命名空间结束
}}