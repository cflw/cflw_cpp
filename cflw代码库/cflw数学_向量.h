#pragma once
#include <complex>
namespace cflw::数学 {
//=============================================================================
// 声明
//=============================================================================
//其它文件
template<typename t = double> using t复数 = std::complex<t>;
struct S直线方程;
struct S矩阵4;
struct S圆形;
//本文件
struct S向量2;
struct S向量3;
struct S向量4;
template<typename t> t f插值(const t&起始值, const t&终止值, float 中间值);
template<typename t> t f绝对值(const t &);
template<> S向量2 f绝对值<S向量2>(const S向量2 &);
template<> S向量3 f绝对值<S向量3>(const S向量3 &);
//=============================================================================
//向量2
struct S向量2 {
	static const S向量2 c零, c一;
	float x = 0, y = 0;
	S向量2() = default;
	S向量2(float, float);
	static S向量2 fc方向r(const float &, const float &);	//大小弧度获得向量
	static S向量2 fc方向d(const float &, const float &);	//大小度获得向量
	static S向量2 fc相同(const float &);	//x,y都等于参数
	static S向量2 fc矩形中心(float, float, float, float);
	static S向量2 fc矩形尺寸(float, float, float, float);
	static S向量2 fc矩形半尺寸(float, float, float, float);
	S向量2 &operator +=(const S向量2 &);
	S向量2 &operator -=(const S向量2 &);
	S向量2 &operator *=(const float &);
	S向量2 &operator /=(const float &);
	S向量2 &operator *=(const t复数<float> &);
	S向量2 operator +(const S向量2 &) const;
	S向量2 operator -(const S向量2 &) const;
	S向量2 operator *(const float &) const;
	S向量2 operator /(const float &) const;
	S向量2 operator *(const t复数<float> &) const;
	S向量2 operator -() const;
	bool operator ==(const S向量2 &) const;
	bool operator !=(const S向量2 &) const;
	bool f全小于(const S向量2 &) const;
	bool f全小于等于(const S向量2 &) const;
	bool f全大于(const S向量2 &) const;
	bool f全大于等于(const S向量2 &) const;
	bool fi零() const;
	float fg大小() const;
	float fg平方() const;
	float fg方向d() const;
	float fg方向r() const;
	float fg夹角r(const S向量2 &) const;
	S向量2 fg反向() const;
	S向量2 fg归一() const;
	S向量2 &fs(const float &);
	S向量2 &fs(const float &, const float &);
	S向量2 &fs大小(const float &);
	S向量2 &fs方向(const float &);
	S向量2 &fs方向d(const float &);
	S向量2 &fs旋转r(const float &);
	S向量2 &fs旋转d(const float &);
	S向量2 f大小(const float &) const;
	S向量2 f方向r(const float &) const;
	S向量2 f方向d(const float &) const;
	float f到点方向r(const S向量2 &) const;
	float f到点方向d(const S向量2 &) const;
	S向量2 f旋转r(const float &) const;
	S向量2 f旋转d(const float &) const;
	S向量2 f绕点旋转r(const S向量2 &, const float &) const;
	S向量2 f绕点旋转d(const S向量2 &, const float &) const;
	float f到点距离(const S向量2 &) const;
	S向量2 f到点向量(const S向量2 &) const;
	S向量2 f到点方位r(const S向量2 &, const float &) const;
	S向量2 f到点方位d(const S向量2 &, const float &) const;
	float f点乘(const S向量2 &) const;
	S向量2 &fs线性渐变(const S向量2 &目标, const float &渐变值);
	S向量2 f线性渐变(const S向量2 &目标, const float &渐变值) const;
	S向量2 &fs倍数渐变(const S向量2 &目标, const float &渐变值, const float &最小渐变 = 0, const float &最大渐变 = 999999999);
	S向量2 f倍数渐变(const S向量2 &目标, const float &渐变值, const float &最小渐变 = 0, const float &最大渐变 = 999999999) const;
	S向量2 f翻折(const S直线方程 &) const;
	S向量2 f翻折(const float &) const;
	S向量2 f翻折(const S圆形 &) const;
	S向量2 f对齐(const float &) const;
	S向量2 f直角坐标(float, float) const;
	S向量2 f窗口坐标(float, float) const;
	S向量2 f分量乘(float, float) const;
	S向量2 f分量乘(const S向量2 &) const;
	bool fi分量相等() const;
	//转换
	S向量3 ft向量3(float = 0) const;
	S向量4 ft向量4(float = 0, float = 0) const;
};
//向量3
struct S向量3 {
	static const S向量3 c零, c一;
	float x, y, z;
	S向量3();
	S向量3(const float &, const float &, const float &);
	S向量3 &operator +=(const S向量3 &);
	S向量3 &operator -=(const S向量3 &);
	S向量3 &operator *=(const float &);
	S向量3 &operator /=(const float &);
	S向量3 operator +(const S向量3 &) const;
	S向量3 operator -(const S向量3 &) const;
	S向量3 operator *(const float &) const;
	S向量3 operator /(const float &) const;
	float fg大小() const;
	float fg平方() const;
	S向量3 fg反向() const;
	S向量3 fg归一() const;
	S向量3 &fs大小(const float &);
	float f点乘(const S向量3 &) const;
	S向量3 f叉乘(const S向量3 &) const;
	S向量3 &fs(const float &);
	S向量3 &fs(const float &, const float &, const float &);
	//转换
	S向量2 ft向量2() const;
	S向量4 ft向量4(const float &) const;
};
//向量4
struct S向量4 {
	union {
		struct {
			float x, y, z, w;
		};
		float m值[4];
	};
	S向量4();
	S向量4(const float &, const float &, const float &, const float &);
	S向量4 operator *(const S矩阵4 &) const;
	S向量3 ft向量3() const;
};

}	//namespace cflw::数学