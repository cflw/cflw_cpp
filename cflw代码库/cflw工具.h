#pragma once
#include <vector>
#include <chrono>
#include <string>
#include <tuple>
#include <memory>
namespace cflw::工具 {
//==============================================================================
// 计次器,计算次数
//==============================================================================
class C计次器 {
public:
	C计次器() = default;
	void f重置(int);
	bool f滴答();
private:
	int m间隔 = 0;
	int m次数 = 0;
};
template<typename t>
class C计值器 {
public:
	void f清零();
	void f重置(t 间隔);
	bool f滴答(t);
private:
	t m值数 = 0;
	t m间隔 = 0;
};
//==============================================================================
// 文本编缉
//==============================================================================
class C文本 {
public:
	typedef std::wstring t字符串;
	template<typename t1, typename t2> static inline t2 f转换(t1);
	template<typename t> static t字符串 f整数_文本(t);
	template<typename t> static t字符串 f浮点数_文本(t);
	template<typename t> static t f文本_整数(const t字符串 &);
	template<typename t> static t f文本_浮点数(const t字符串 &);
	static t字符串 f数据_十六进制(const void *, size_t);
	static std::tuple<std::byte*, size_t> f十六进制_数据(const t字符串 &);	//记得删除指针,或者用智能指针
	static bool fw数字(const t字符串 &);
	static int f查找(const t字符串 &, const t字符串 &, int);
	static t字符串 f有效数字(const t字符串 &, int);
	static t字符串 f小数位数(const t字符串 &, int);
};
//==============================================================================
// 存放一堆数据的字节数组
//==============================================================================
//任意数量
class C数据 {
public:
	unsigned char *m指针 = nullptr;
	unsigned int m大小 = 0;
	C数据() = default;
	C数据(const C数据 &);
	C数据(unsigned int a大小);
	~C数据();
	bool f新建(unsigned int a大小);
	void f删除();
	void f复制(void *p指针, unsigned int a大小);
	void f复制(const C数据 &a数据);
	unsigned char *&fg数据();
	unsigned int fg大小();
};
//临时空间,从内存得到的空间总是≥需要空间
template<typename t> class C空间 {
public:
	t *m指针 = nullptr;
	unsigned int m分配数量 = 0;
	unsigned int m需要数量 = 0;
	C空间() = default;
	~C空间();
	t *f分配(unsigned int);
	//禁用
	C空间(const C空间 &) = delete;
	C空间(C空间 &&) = delete;
	C空间 &operator =(const C空间 &) = delete;
	C空间 &operator =(C空间 &&) = delete;
};
//==============================================================================
// 位大小,位指针 精确到位的数据操作
//==============================================================================
struct S位大小 {
	int v字节;
	int v位;
	S位大小(int, int = 0);
	S位大小 &operator +=(const S位大小 &);
	S位大小 operator +(const S位大小 &) const;
	operator int() const;
};
class C位指针 {
private:
	void *v指针;
	S位大小 v偏移;
public:
	C位指针();
	C位指针(void *);
	C位指针(void *, int);
	C位指针 &fs指针(void *, int);
	void f读(void *, const S位大小 &);
	void f读(const C位指针 &, const S位大小 &);
	void f写(void *, const S位大小 &);
	void f写(const C位指针 &, const S位大小 &);
	C位指针 &f偏移(const S位大小 &);
	static void f内存复制(const C位指针 &, const C位指针 &, const S位大小 &);
	static void f内存复制(void *, int, void *, int, int);
	static unsigned long f取数据(void *, int, int);
	static void f赋数据(void *, int, unsigned long);
};
//==============================================================================
// 树
//==============================================================================
template<typename t>
class C树 {
public:
	class C节点 {
	public:
		t m值 = {};
		std::unique_ptr<std::vector<C节点>> m叶;
		C节点() = default;
		C节点(const t &, std::unique_ptr<std::vector<C节点>> && = nullptr);
	};
	typedef std::vector<C节点> t叶;
	std::vector<C节点> m叶;
	C树() = default;
};
}	//namespace cflw::工具
#include "cflw工具.inl"