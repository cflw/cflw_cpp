#include <boost/program_options/detail/convert.hpp>
#include <boost/program_options/detail/utf8_codecvt_facet.hpp>
#include "cflw�ļ�_json.h"
namespace cflw::�ļ�::json {
const std::locale C�ļ�::utf8{std::locale(), new boost::program_options::detail::utf8_codecvt_facet()};
C�ļ�::C�ļ�() {
	m��.imbue(utf8);
}
bool C�ļ�::f��(const wchar_t *a�ļ���, int aģʽ) {
	m��.open(a�ļ���, aģʽ);
	return fi��();
}
void C�ļ�::f��ȡ(t�� &a��) {
	assert(fi��());
	boost::property_tree::read_json(m��, a��);
}
void C�ļ�::fд��(const t�� &a��) {
	assert(fi��());
	boost::property_tree::write_json(m��, a��);
}
bool C�ļ�::fi��() const {
	return m��.good();
}
}	//namespace cflw::�ļ�::json
namespace boost::property_tree::json_parser {
std::wstring create_escapes(const std::wstring &s) {
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