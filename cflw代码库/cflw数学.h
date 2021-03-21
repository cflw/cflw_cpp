#pragma once
#include <cmath>
#include <limits>
#include <complex>
#include <utility>
#include <functional>
#include <algorithm>
#undef max
#undef min
namespace cflw::数学 {
//==============================================================================
//数字类型&别名&前置声明
//==============================================================================
//标准库类型
template<typename t = double> using t复数 = std::complex<t>;
//==============================================================================
// 基本数学函数&全局偷懒函数
//==============================================================================
int f取整数位数(const int &);
template<typename t> int f取符号(const t &x);
template <typename t> int f取符号(const t &x, const t &零范围);
template<> int f取符号<bool>(const bool &x);
template<typename t> const t& f最大值(const t &a, const t &b);
template<typename t> const t& f最小值(const t &a, const t &b);
template<typename t> std::pair<const t &, const t &> f小大(const t &, const t &);
template<typename t> t f夹取(const t &值, const t &最小值, const t &最大值);
template<typename t> t f接近(const t &源值, const t &目标值, const t &接近差);
template<typename t> t f倍数渐变(const t &源值, const t &目标值, const float &差值渐变倍数, const t &最小渐变, const t &最大渐变);
template<typename t> t f线性渐变(const t &源值, const t &目标值, const float &渐变值);
template<typename t> t f下整除(const t &, const t &);	//商向下取整
template<typename t> t f上整除(const t &, const t &);	//商向上取整
template<typename t> t f求余(const t &源值, const t &除数);
template<typename t> bool f大于等于环绕(t &值, const t &最大值);
int f10的次方(const int &x);
template<typename t> t f绝对值(const t &);
template<typename t> std::tuple<t, t> sincos(const t &);
template<typename t> t f插值(const t &起始值, const t &终止值, float 中间值);
template<typename t> auto f反插值(const t &起始值, const t &终止值, const t &目标值);
template<typename t> int f环绕取倍数(t &被限值, const t &限值);
template<typename t> t f点乘(const t &, const t& );
template<typename t> t f叉乘(const t &, const t &);
template<typename t> t f负(const t &);
template<typename t> bool f同符号(const t &, const t &);
template<typename t> t f平方(const t &);
template<typename t> t f立方(const t &);
template<typename t> t f对齐(const t &, const t &);//将x对齐到y的整数倍
template<typename t> t f环绕(const t &, const t &最小, const t &最大);
template<typename t> t f差(const t &, const t &);
template<typename t> t f翻折(const t &, const t &);
template<typename tk, typename tv> tv f插值2(const std::pair<tk, tv> &, const std::pair<tk, tv> &, const tk &);
template<typename tk, typename tv> tv f插值2(const tk &, const tv &, const tk &, const tv &, const tk &);
template<typename t> t f反勾股(const t &, const t &);	//已知斜边和一直角边求另一直角边
template<typename t> t f四舍五入(const t &);	//
template<typename t> t f等腰梯形插值(const t &小, const t &大, float 斜宽, float 中间值);
template<typename t> t f平均(const t &, const t &);	//(a+b)/2
template<typename t> t f距离(const t &, const t &);	//b-a
template<typename t> t f半距离(const t &, const t &);	//(b-a)/2
template<typename...t参数> auto f算术平均(t参数 &&...);
template<typename...t参数> auto f几何平均(t参数 &&...);
template<typename...t参数> auto f绝对值最大值(t参数 &&...);	//计算出绝对值最大值,返回原值
//==============================================================================
// 基本几何函数
//==============================================================================
//特别角度
float f求余(const float &x, const float &y);
float f位置(float, float);
//窗口坐标与直角坐标变换
float f窗口坐标x(float, float 原始);
float f窗口坐标y(float, float 原始);
float f直角坐标x(float, float 原始);
float f直角坐标y(float, float 原始);
float f窗口坐标x(float, float 原始, float 目标);
float f窗口坐标y(float, float 原始, float 目标);
float f直角坐标x(float, float 原始, float 目标);
float f直角坐标y(float, float 原始, float 目标);
float f窗口缩放(float 原始, float 目标);
float f直角缩放(float 原始, float 目标);
//==============================================================================
// 各种计算类
//==============================================================================
template<typename t> class C角度计算 {
public:
	static const C角度计算 c度, c弧度;
	t m周角;
	t m平角;
	C角度计算(const t &);
	t f平均(const t &角1, const t &角2) const;
	t f取正(const t &角) const;	//限制在[0,周角)范围内
	t f夹取(const t &角) const;	//限制在(-平角,平角]范围内
	t f取半(const t &角) const;	//限制在[0,平角)范围内
	t f旋转渐变(const t &源, const t &目标, const t &最大) const;
	t f夹角(const t &角1, const t &角2) const;
	t f方向(const t &x, const t &y) const;	//原点到目标点的方向
	t f插值(const t &角1, const t &角2, const t &插值) const;
};
template<typename t> inline const C角度计算<t> &c角度计算 = C角度计算<t>::c角度;
template<typename t> inline const C角度计算<t> &c弧度计算 = C角度计算<t>::c弧度;
//==============================================================================
// 位置关系
//==============================================================================
enum E位置关系 {
	e内含 = -2,
	e内切 = -1,
	e相交 = 0,
	e外切 = 1,
	e外离 = 2
};
//std::weak_equality operator <=>(E位置关系, int);
}	//命名空间结束
#include "cflw数学.inl"
