#pragma once
#include <string>
#include <fstream>
#include <vector>
#include "cflw工具_循环.h"
namespace cflw {
namespace 文件 {
namespace csv {
class C读;
class C写;
//=============================================================================
// 读
//=============================================================================
struct S行 {
	S行(std::vector<std::wstring> &);
	const std::wstring &operator[](size_t i) const;
	std::vector<std::wstring> &fe() const;
	std::vector<std::wstring> *m数组;
};
class C行循环 : public 工具::循环::I循环<C行循环> {
public:
	C行循环(std::wifstream &);
	bool f循环控制_i继续();
	S行 f循环控制_解引用();
private:
	std::vector<std::wstring> m数组;
	std::wifstream *m文件;
};
class C读 {
public:
	void f打开(const std::wstring &);
	C行循环 fe行();
	void fs标题行(bool);	//如果有,fe行()不会出现标题行
private:
	bool m标题行 = false;
	size_t m第二行开始位置 = 0;
	std::wifstream m文件;
};
//=============================================================================
// 写
//=============================================================================
class C写 {
public:
	void f打开(const std::wstring &, int 模式 = std::ios::out);
	void fs列数(int);
	template<typename t> C写 &operator <<(const t &);
private:
	void f写(const std::wstring &);
};
template<typename t> C写 &C写::operator <<(const t &p) {
	f写(std::to_wstring(p));
	return *this;
}
}	//namespace csv
}	//namespace 文件
}	//namespace cflw