export module cflw.文件.xml;
export import <filesystem>;
export import <pugixml.hpp>;	//pugixml
export namespace cflw::文件::xml {
using t路径 = std::filesystem::path;
using t文档 = pugi::xml_document;
using t结果 = pugi::xml_parse_result;
using t节点 = pugi::xml_node;
using t属性 = pugi::xml_attribute;
bool f打开(t文档 &, const t路径 &);
bool f保存(const t文档 &, const t路径 &);
}	//namespace cflw::文件::xml
namespace cflw::文件::xml {
bool f打开(t文档 &a文档, const t路径 &a路径) {
	const t结果 v结果 = a文档.load_file(a路径.c_str());
	if (!v结果) {
		return false;
	}
	return true;
}
bool f保存(const t文档 &a文档, const t路径 &a路径) {
	const bool v结果 = a文档.save_file(a路径.c_str(), L"\t", pugi::format_default, pugi::encoding_utf8);
	return v结果;
}
}	//namespace cflw::文件::xml