#pragma once
#include <locale>
#include <fstream>
#include <boost/property_tree/json_parser.hpp>
namespace boost::property_tree::json_parser {
//↓防止中文转义的重载函数，需要把这个声明放到boost/property_tree/json_parser/detail/write.hpp文件中
template<> std::wstring create_escapes(const std::wstring &);
}	//namespace boost::property_tree::json_parser
namespace cflw::文件::json {
using t树 = boost::property_tree::wptree;
extern const std::locale utf8;
//==============================================================================
// 文件类(废弃)
//==============================================================================
class C文件 {	//废弃
public:
	C文件();
	bool f打开(const wchar_t *, int 模式 = std::ios::in);
	template<typename t> bool f打开(const t &, int 模式 = std::ios::in);
	void f读取(t树 &);
	void f写入(const t树 &);
	bool fi好() const;
	std::wfstream m流;
};
template<typename t> bool C文件::f打开(const t &a路径, int a模式) {
	return f打开(a路径.c_str(), a模式);
}
//==============================================================================
// 函数
//==============================================================================
bool f打开文件(const wchar_t *, t树 &);	//打开utf8编码的json文件
bool f保存文件(const wchar_t *, const t树 &);	//保存utf8编码的json文件
t树 f解析数据(const std::u8string_view &);	//解析utf8字符串
std::u8string f生成数据(const t树 &);	//生成utf8字符串
template<typename t> t树 f序列化(const t &) {	//数据结构转成json树,需要手动特化
	return t树{};
}
template<typename t> t f解析(const t树 &) {	//json树转成数据结构,需要手动特化
	return t{};
}
}	//namespace cflw::文件::json