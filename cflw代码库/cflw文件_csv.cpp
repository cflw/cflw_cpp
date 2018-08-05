#include <boost\algorithm\string.hpp>
#include "cflw文件_csv.h"
namespace cflw {
namespace 文件 {
namespace csv {
//=============================================================================
// 行
//=============================================================================
S行::S行(std::vector<std::wstring> &p数组) :
	m数组{&p数组} {
}
const std::wstring &S行::operator[](size_t i) const {
	return m数组->at(i);
}
std::vector<std::wstring> &S行::fe() const {
	return *m数组;
}
//=============================================================================
// 循环
//=============================================================================
C行循环::C行循环(std::wifstream &p文件) :
	m文件{&p文件} {
}
bool C行循环::f循环控制_w继续() {
	return !m文件->eof();
}
S行 C行循环::f循环控制_解引用() {
	std::wstring v行;
	std::getline(*m文件, v行);
	boost::split(m数组, v行, boost::is_any_of(L","));
	return S行(m数组);
}
//=============================================================================
// 读
//=============================================================================
void C读::f打开(const std::wstring &a文件名) {
	m文件.open(a文件名);
	if (!m文件) {	//失败
		throw;
	}
	//读第一行
	std::wstring v行;
	std::getline(m文件, v行);
	m第二行开始位置 = v行.size() + 1;
}
C行循环 C读::fe行() {
	if (m标题行) {
		m文件.seekg(m第二行开始位置, std::ios::beg);
	} else {
		m文件.seekg(0, std::ios::beg);
	}
	return C行循环{m文件};
}
void C读::fs标题行(bool p) {
	m标题行 = p;
}
//=============================================================================
// 写
//=============================================================================
void C写::f打开(const std::wstring &, int p模式) {

}
void C写::fs列数(int) {

}
void C写::f写(const std::wstring &) {

}
//=============================================================================
}	//namespace csv
}	//namespace 文件
}	//namespace cflw