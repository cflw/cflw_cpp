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