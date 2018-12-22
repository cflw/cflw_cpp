#pragma once
#include <locale>
#include <fstream>
#include <boost/property_tree/json_parser.hpp>
namespace cflw::文件::json {
using t树 = boost::property_tree::wptree;
/*
template<typename t> concept T字符串 = requires(t a) {
	{a.c_str()}->const wchar_t *
}
*/
class C文件 {
public:
	static const std::locale utf8;
	C文件();
	bool f打开(const wchar_t *, int 模式 = std::ios::in);
	template<typename t> bool f打开(const t &, int 模式 = std::ios::in);
	void f读取(t树 &);
	void f写入(const t树 &);
	bool fi好() const;
	std::wfstream m流;
};
template<typename t> bool C文件::f打开(const t &a路径, int a模式) {
	return f打开(a路径.c_str());
}
}	//namespace cflw::文件::json