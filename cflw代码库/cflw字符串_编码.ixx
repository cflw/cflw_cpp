module;
#include <iostream>
#include <locale>
#include <string>
export module cflw.字符串.编码;	//c++20标准库没有好用的编码转换类,手写一些
export namespace cflw::字符串 {
const std::locale &fg本地环境();
template<typename t输入, typename t输出, typename t转换 = std::codecvt<t输入, t输出, std::mbstate_t>>
std::basic_string<t输出> f编码转换o(const std::basic_string_view<t输入> &in) {
	const auto &cvt = std::use_facet<t转换>(fg本地环境());
	std::mbstate_t mb{};
	std::basic_string<t输出> ex(in.size() * (size_t)cvt.max_length(), static_cast<t输出>(0));
	const t输入 *from_next;
	t输出 *to_next;
	cvt.out(mb,
		&in[0], &in[0]+in.size(), from_next,
		&ex[0], &ex[0]+ex.size(), to_next);
	return std::basic_string<t输出>{&ex[0], to_next};
}
template<typename t输入, typename t输出, typename t转换 = std::codecvt<t输入, t输出, std::mbstate_t>>
std::basic_string<t输入> f编码转换i(const std::basic_string_view<t输出> &ex) {
	const auto &cvt = std::use_facet<t转换>(fg本地环境());
	std::mbstate_t mb{};
	std::basic_string<t输入> in(ex.size(), static_cast<t输入>(0));
	const t输出 *from_next;
	t输入 *to_next;
	cvt.in(mb,
		&ex[0], &ex[0]+ex.size(), from_next,
		&in[0], &in[0]+in.size(), to_next);
	return std::basic_string<t输入>{&in[0], to_next};
}
template<typename t输入, typename t输出>
std::basic_string<t输出> f编码转换(const std::basic_string_view<t输入> &a) {
	if constexpr (sizeof(t输入) >= sizeof(t输出)) {
		return f编码转换o<t输入, t输出>(a);
	} else {
		return f编码转换i<t输出, t输入>(a);
	}
}
template<typename t输入, typename t输出>
std::basic_string<t输出> f强制转换s(const std::basic_string_view<t输入> &a) {	//转换字符串,生成副本
	return std::basic_string<t输出>(
		reinterpret_cast<const t输出 *>(a.data()),
		a.size() * sizeof(t输入) / sizeof(t输出) + (sizeof(t输入) % sizeof(t输出) != 0 ? 1 : 0));
}
template<typename t输入, typename t输出>
std::basic_string_view<t输出> f强制转换v(const std::basic_string_view<t输入> &a) {	//转换视图
	return std::basic_string_view<t输出>(
		reinterpret_cast<const t输出*>(a.data()), 
		a.size() * sizeof(t输入) / sizeof(t输出) + (sizeof(t输入) % sizeof(t输出) != 0 ? 1 : 0));
}
//特化
template<> std::string f编码转换(const std::wstring_view &);
template<> std::wstring f编码转换(const std::string_view &);
template<> std::u8string f编码转换(const std::wstring_view &);
template<> std::wstring f编码转换(const std::u8string_view &);
}	//namespace cflw::字符串
module: private;
namespace cflw::字符串 {
const std::locale &fg本地环境() {	//以后再根据系统设置获取语言环境
	static std::locale c本地环境 = std::locale("zh_CN");
	return c本地环境;
}
template<> std::string f编码转换(const std::wstring_view &a) {
	//std::codecvt<wchar_t, char, mbstate_t>需要设置本地环境才能用,local()会返回空串
	return f编码转换o<wchar_t, char>(a);	
}
template<> std::wstring f编码转换(const std::string_view &a) {
	return f编码转换i<wchar_t, char>(a);
}
//template<> std::string f编码转换(const std::wstring &a) {	//codecvt<wchar_t, char, mbstate_t>不能用,会返回空串
//	std::vector<char> v字符串(a.size() * 4);
//	const size_t v长度 = wcstombs(v字符串.data(), a.data(), v字符串.size());
//	return std::string(v字符串.data(), v长度 + 1);	//长度不含'\0'要加1
//}
//template<> std::wstring f编码转换(const std::string &a) {	//codecvt<wchar_t, char, mbstate_t>不能用,会返回空串
//	std::vector<wchar_t> v字符串(a.size() * 4);
//	const size_t v长度 = mbstowcs(v字符串.data(), a.data(), v字符串.size());
//	return std::wstring(v字符串.data(), v长度 + 1);
//}
template<> std::u8string f编码转换(const std::wstring_view &a) {
	//c++标准库没有特化codecvt<wchar_t, char8_t, mbstate_t>,需要换成codecvt<char16_t, char8_t, mbstate_t>.
	//windows操作系统中wchar_t == char16_t, 直接强制转换
	static_assert(sizeof(wchar_t) == sizeof(char16_t));	//windows专用断言
	const std::u16string_view v转换(reinterpret_cast<const char16_t *>(a.data()), a.size());
	return f编码转换o<char16_t, char8_t>(v转换);
}
template<> std::wstring f编码转换(const std::u8string_view &a) {
	static_assert(sizeof(wchar_t) == sizeof(char16_t));	//windows专用断言
	std::u16string v转换 = f编码转换i<char16_t, char8_t>(a);
	return std::wstring(reinterpret_cast<wchar_t *>(v转换.data()), v转换.size());	//存在1次复制,以后优化
}
}	//namespace cflw::字符串