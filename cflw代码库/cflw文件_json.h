#pragma once
#include <locale>
#include <fstream>
#include <boost/property_tree/json_parser.hpp>
namespace boost::property_tree::json_parser {
//����ֹ����ת������غ�������Ҫ����������ŵ�boost/property_tree/json_parser/detail/write.hpp�ļ���
std::wstring create_escapes(const std::wstring &);
}	//namespace boost::property_tree::json_parser
namespace cflw::�ļ�::json {
using t�� = boost::property_tree::wptree;
/*
template<typename t> concept T�ַ��� = requires(t a) {
	{a.c_str()}->const wchar_t *
}
*/
class C�ļ� {
public:
	static const std::locale utf8;
	C�ļ�();
	bool f��(const wchar_t *, int ģʽ = std::ios::in);
	template<typename t> bool f��(const t &, int ģʽ = std::ios::in);
	void f��ȡ(t�� &);
	void fд��(const t�� &);
	bool fi��() const;
	std::wfstream m��;
};
template<typename t> bool C�ļ�::f��(const t &a·��, int aģʽ) {
	return f��(a·��.c_str(), aģʽ);
}
}	//namespace cflw::�ļ�::json