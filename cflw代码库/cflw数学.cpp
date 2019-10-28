#include <assert.h>
#include "cflw数学.h"
#include "cflw数学_向量.h"
namespace cflw {
namespace 数学 {
//==============================================================================
// 基本数学函数
//==============================================================================
int f取整数位数(const int &x) {
	int v = x;
	int i = 0;
	while (v != 0) {
		v /= 10;
		++i;
	}
	return i;
}
int f10的次方(const int &x) {
	return (int)pow(10.0, x);
}
//其他
float f求余(const float &x, const float &y) {
	return sqrt(x * x + y * y);
}
float f翻折(float p点, float p翻折) {
	return 2 * p翻折 - p点;
}
float f位置(float x, float y) {
	return y - x;
}
//窗口坐标与直角坐标变换
float f窗口坐标x(float x, float s) {
	return x + s / 2;
}
float f窗口坐标y(float y, float s) {
	return s / 2 - y;
}
float f直角坐标x(float x, float s) {
	return x - s / 2;
}
float f直角坐标y(float y, float s) {
	return s / 2 - y;
}
float f窗口坐标x(float x, float s, float d) {
	return f窗口坐标x(x * f窗口缩放(s, d), d);
}
float f窗口坐标y(float y, float s, float d) {
	return f窗口坐标y(y * f窗口缩放(s, d), d);
}
float f直角坐标x(float x, float s, float d) {
	return f直角坐标x(x * f直角缩放(s, d), d);
}
float f直角坐标y(float y, float s, float d) {
	return f直角坐标y(y * f直角缩放(s, d), d);
}
float f窗口缩放(float s, float d) {
	return d / s;
}
float f直角缩放(float s, float d) {
	return d / s;
}
//模板实列化
template<> int f取符号<bool>(const bool &x) {
	return x ? 1 : -1;
}
//位置关系
/*
std::weak_equality operator <=>(E位置关系 p, int n) {
	assert(n == 0);
	if (p < E位置关系::e内切) {
		return std::weak_equality::less;
	} else if (p0 > E位置关系::e内切) {
		return std::weak_equality::greater;
	} else {
		return std::weak_equality::equivalent;
	}
}
*/
//==============================================================================
}}	//命名空间结束