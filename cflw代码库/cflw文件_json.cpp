#include <boost/program_options/detail/convert.hpp>
#include <boost/program_options/detail/utf8_codecvt_facet.hpp>
#include "cflw文件_json.h"
import cflw.字符串.编码;
namespace cflw::文件::json {
const std::locale utf8{std::locale(), new boost::program_options::detail::utf8_codecvt_facet()};
//==============================================================================
// 文件
//==============================================================================
C文件::C文件() {
	m流.imbue(utf8);
}
bool C文件::f打开(const wchar_t *a文件名, int a模式) {
	m流.open(a文件名, a模式);
	return fi好();
}
void C文件::f读取(t树 &a树) {
	assert(fi好());
	boost::property_tree::read_json(m流, a树);
}
void C文件::f写入(const t树 &a树) {
	assert(fi好());
	boost::property_tree::write_json(m流, a树);
}
bool C文件::fi好() const {
	return m流.good();
}
//==============================================================================
// 函数
//==============================================================================
bool f打开文件(const wchar_t *a文件名, t树 &a树) {	//打开utf8编码的json文件
	std::wifstream v流;
	v流.imbue(utf8);
	v流.open(a文件名, std::ios::in);
	if (!v流.is_open()) {
		return false;
	}
	boost::property_tree::read_json(v流, a树);
	return true;
}
bool f保存文件(const wchar_t *a文件名, const t树 &a树) {	//保存utf8编码的json文件
	std::wofstream v流;
	v流.imbue(utf8);
	v流.open(a文件名, std::ios::out);
	if (!v流.is_open()) {
		return false;
	}
	boost::property_tree::write_json(v流, a树);
	return true;
}
t树 f解析数据(const std::u8string_view &a数据) {	//解析utf8字符串
	const std::wstring v数据 = 字符串::f编码转换<char8_t, wchar_t>(a数据);
	std::wistringstream v流{v数据};
	t树 v树;
	boost::property_tree::read_json(v流, v树);
	return v树;
}
std::u8string f生成数据(const t树 &a树) {	//生成utf8字符串
	std::wostringstream v流;
	boost::property_tree::write_json(v流, a树);
	const std::u8string v数据 = 字符串::f编码转换<wchar_t, char8_t>(v流.str());
	return v数据;
}
}	//namespace cflw::文件::json
//==============================================================================
// 重写转义函数
//==============================================================================
namespace boost::property_tree::json_parser {
template<> std::wstring create_escapes(const std::wstring &s) {
	using Ch = wchar_t;
	std::wstring result;
	typename std::wstring::const_iterator b = s.begin();
	typename std::wstring::const_iterator e = s.end();
	while (b != e)
	{
		typedef typename std::make_unsigned<wchar_t>::type UCh;
		UCh c(*b);
		if (c == 0x20 || c == 0x21 || (c >= 0x23 && c <= 0x2E) ||
			(c >= 0x30 && c <= 0x5B) || (c >= 0x5D && c <= 0xFFff))
			result += *b;
		else if (*b == Ch('\b')) result += Ch('\\'), result += Ch('b');
		else if (*b == Ch('\f')) result += Ch('\\'), result += Ch('f');
		else if (*b == Ch('\n')) result += Ch('\\'), result += Ch('n');
		else if (*b == Ch('\r')) result += Ch('\\'), result += Ch('r');
		else if (*b == Ch('\t')) result += Ch('\\'), result += Ch('t');
		else if (*b == Ch('/')) result += Ch('\\'), result += Ch('/');
		else if (*b == Ch('"'))  result += Ch('\\'), result += Ch('"');
		else if (*b == Ch('\\')) result += Ch('\\'), result += Ch('\\');
		else
		{
			const char *hexdigits = "0123456789ABCDEF";
			unsigned long u = (std::min)(static_cast<unsigned long>(
				static_cast<UCh>(*b)),
				0xFFFFul);
			unsigned long d1 = u / 4096; u -= d1 * 4096;
			unsigned long d2 = u / 256; u -= d2 * 256;
			unsigned long d3 = u / 16; u -= d3 * 16;
			unsigned long d4 = u;
			result += Ch('\\'); result += Ch('u');
			result += Ch(hexdigits[d1]); result += Ch(hexdigits[d2]);
			result += Ch(hexdigits[d3]); result += Ch(hexdigits[d4]);
		}
		++b;
	}
	return result;
}
}	//namespace boost::property_tree::json_parser