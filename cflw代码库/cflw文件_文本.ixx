export module cflw.文件.文本;
export import <fstream>;
export import <string>;
export import <filesystem>;
export import cflw.字符串.编码;
export namespace cflw::文件::文本 {	//解析各种txt文件
template<typename t文件编码, typename t输出编码 = typename t文件编码>
std::basic_string<t输出编码> f读取文件(const std::filesystem::path &a路径) {
	std::ifstream v流;
	v流.open(a路径);
	if (!v流) {
		return {};
	}
	std::string v内容((std::istreambuf_iterator<char>(v流)), std::istreambuf_iterator<char>());
	if constexpr (std::is_same_v<char, t文件编码>) {
		if constexpr (std::is_same_v<char, t输出编码>) {
			return v内容;
		} else {
			return 字符串::f编码转换<t输出编码>(v内容);
		}
	} else {
		if constexpr (std::is_same_v<t文件编码, t输出编码>) {
			return 字符串::f强制转换v<t输出编码>(v内容);
		} else {
			return 字符串::f编码转换<t输出编码>(字符串::f强制转换v<t文件编码>(v内容));
		}
	}
}
}	//namespace cflw::文件::文本