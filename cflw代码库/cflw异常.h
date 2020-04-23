#pragma once
#include <exception>
#include <stdexcept>
#include <string>
namespace cflw::异常 {
//标准库异常别名
using X参数 = std::invalid_argument;
//未实现
class X未实现 : public std::runtime_error {
public:
	X未实现(const std::string & = "未实现");
};
//HRESULT
class X视窗 : public std::runtime_error {
public:
	X视窗(long);
	long m值;
};
}	//namespace cflw::异常