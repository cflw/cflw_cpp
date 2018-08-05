#include "cflw数学.h"
#include "cflw数学_随机.h"
namespace cflw {
namespace 数学 {
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
C圆形分布::C圆形分布(const S圆形 &p圆形):
	m圆形{p圆形} {
}
S向量2 C圆形分布::f生成(unsigned int p) const {
	const auto v分割 = C分布工具::f分割2(p);
	S向量2 v向量 = S向量2::fc方向r(std::get<0>(v分割) * m圆形.m半径, std::get<1>(v分割) * (float)cπ);
	return v向量 + m圆形.m坐标;
}
//矩形分布=========================================================================
C矩形分布::C矩形分布(const S旋转矩形 &p矩形):
	m矩形{p矩形} {
}
S向量2 C矩形分布::f生成(unsigned int p) const {
	const auto v分割 = C分布工具::f分割2(p);
	S向量2 v向量 = S向量2{
		f插值<float>(-m矩形.m半尺寸.x, m矩形.m半尺寸.x, std::get<0>(v分割)),
		f插值<float>(-m矩形.m半尺寸.y, m矩形.m半尺寸.y, std::get<1>(v分割))
	};
	v向量.fs旋转r(m矩形.m方向);
	return v向量 + m矩形.m坐标;
}

}	//namespace 数学
}	//namespace cflw