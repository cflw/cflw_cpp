#include "cflw数学.h"
#include "cflw数学_随机.h"
namespace cflw::数学 {
//==============================================================================
// 随机数
//==============================================================================
C线性同余::C线性同余() :a(0), b(0), r(0) {};
void C线性同余::f置种子(const unsigned long &种子) {
	r = 0;
	b = 种子;
	while (b > 0xffff)
		b /= 2;
	a = b;
	while (a > 0xff)
		a /= 2;
}
void C线性同余::f计算() {	//计算一个随机数
	r = (a * r + b) % c最大值;
}
unsigned long C线性同余::f生成() {
	f计算();
	return r;
}
bool C线性同余::f生成(const float &p) {
	return f生成<float>(0, 1) <= p;
}
//==============================================================================
// 分布
//==============================================================================
class C分布工具 {
public:
	static const unsigned int c位 = sizeof(unsigned int) * 4;
	static const unsigned int c最大 = 1 << c位;
	static std::tuple<float, float> f分割2(unsigned int p) {
		const unsigned int v0 = p >> c位;	//高位部分
		const unsigned int v1 = p % c最大;	//低位部分
		return std::make_tuple<float, float>((float)v0 / c最大, (float)v1 / c最大);
	}
};
//圆形分布=========================================================================
C圆形分布::C圆形分布(const S圆形 &a圆形):
	m圆形{a圆形} {
}
S向量2 C圆形分布::f生成(unsigned int a整数) const {
	const auto v分割 = C分布工具::f分割2(a整数);
	S向量2 v向量 = S向量2::fc方向r(std::get<0>(v分割) * m圆形.m半径, std::get<1>(v分割) * cπ<float>);
	return v向量 + m圆形.m坐标;
}
//矩形分布=========================================================================
C矩形分布::C矩形分布(const S矩形 &a矩形):
	m矩形(a矩形, 0) {
}
C矩形分布::C矩形分布(const S旋转矩形 &a矩形):
	m矩形{a矩形} {
}
S向量2 C矩形分布::f生成(unsigned int a整数) const {
	const auto v分割 = C分布工具::f分割2(a整数);
	S向量2 v向量 = S向量2{
		f插值<float>(-m矩形.m半尺寸.x, m矩形.m半尺寸.x, std::get<0>(v分割)),
		f插值<float>(-m矩形.m半尺寸.y, m矩形.m半尺寸.y, std::get<1>(v分割))
	};
	v向量.fs旋转r(m矩形.m方向);
	return v向量 + m矩形.m坐标;
}
}	//namespace cflw::数学