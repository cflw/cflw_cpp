#include <string>
#include "cflw异常.h"
#include "cflw工具.h"
namespace cflw::异常 {
X未实现::X未实现():
	std::runtime_error("该函数未实现") {
}
X视窗::X视窗(long a):
	std::runtime_error(std::string("HRESULT:") + std::to_string(a)) {
}
}	//namespace cflw::异常