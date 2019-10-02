#pragma once
#include <cassert>
#include <initializer_list>
#include <type_traits>
namespace cflw::数学 {
class C转换因子表 {
public:
	C转换因子表(const std::initializer_list<double> &p列表) :
		v大小{p列表.size()},
		v数据{new double[v大小 * v大小]} {
		int i = 0;
		for (const double &x : p列表) {
			int j = 0;
			for (const double &y : p列表) {
				v数据[i + j] = y / x;
				++j;
			}
			i += v大小;
		}
	}
	C转换因子表(const C转换因子表 &) = delete;
	C转换因子表(C转换因子表 &&) = delete;
	~C转换因子表() {
		delete[] v数据;
	}
	template<typename t>
	double operator()(const t &x, const t &y) const {
		static_assert(std::is_enum<t>::value, "必需是枚举类型");
		const int vx = static_cast<int>(x);
		assert(vx < v大小);
		const int vy = static_cast<int>(y);
		assert(vy < v大小);
		return v数据[vx * v大小 + vy];
	}
	template<typename t单位, typename t数值 = double>
	t数值 operator()(const t单位 &x, const t单位 &y, const t数值 &p数值) const {
		return static_cast<t数值>(operator()(x, y)) * p数值;
	}
private:
	size_t v大小 = 0;
	double *v数据 = nullptr;
};
extern const C转换因子表 f角度转换;
extern const C转换因子表 f时间转换;
extern const C转换因子表 f长度转换;
extern const C转换因子表 f质量转换;
extern const C转换因子表 f数量转换;
//extern const C转换因子表 f温度转换;
extern const C转换因子表 f货币转换;
enum class E角度 {
	e度,	//周角＝360
	e分,
	e秒,
	e弧度,	//周角＝c二π
};
enum class E时间 {
	e毫秒,
	e秒,
	e分,
	e时,
	e日,
	e月,
	e年,
	e世纪,
};
enum class E长度 {
	e毫米,
	e厘米,
	e分米,
	e米,
	e千米,
};
enum class E质量 {
	e毫克,	//mg
	e克,	//g
	e斤,
	e千克,	//kg
	e吨,	//t
};
enum class E数量 {
	e个,
	e摩尔,	//mol
};
enum class E温度 {
	e摄氏度,	//C
	e华氏度,	//F
	e开氏度,	//K
	e兰氏度,	//Ra
	e列氏度,	//Re
};
enum class E货币 {
	e人民币,
	e美元,
	e欧元,
	e日元
};
}	//namespace cflw::数学