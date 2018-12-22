#include <boost/program_options/detail/convert.hpp>
#include <boost/program_options/detail/utf8_codecvt_facet.hpp>
#include "cflw文件_json.h"
namespace cflw::文件::json {
const std::locale C文件::utf8{std::locale(), new boost::program_options::detail::utf8_codecvt_facet()};
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

}	//namespace cflw::文件::json