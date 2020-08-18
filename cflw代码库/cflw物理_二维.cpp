#include "cflw物理_二维.h"
#include "cflw数学.h"
namespace cflw::物理 {
t运动 f反弹运动x(const t向量2 &a坐标, const t向量2 &a速度, float x) {
	const t向量2 v坐标 = {数学::f翻折<float>(a坐标.x, x), a坐标.y};
	const t向量2 v速度 = {-a速度.x, a速度.y};
	return {v坐标, v速度};
}
t运动 f反弹运动y(const t向量2 &a坐标, const t向量2 &a速度, float y) {
	const t向量2 v坐标 = {a坐标.x, 数学::f翻折<float>(a坐标.y, y)};
	const t向量2 v速度 = {a速度.x, -a速度.y};
	return {v坐标, v速度};
}
t运动 f反弹运动_直线(const t向量2 &a坐标, const t向量2 &a速度, const t直线2 &a直线) {
	if (a直线.fi平行x轴()) {
		return f反弹运动x(a坐标, a速度, -a直线.c);
	}
	if (a直线.fi平行y轴()) {
		return f反弹运动y(a坐标, a速度, -a直线.c);
	}
	const t向量2 v坐标 = 数学::f点关于直线翻折(a坐标, a直线);
	const t向量2 v速度 = 数学::f点关于方向翻折(a速度, a直线.fg方向r());
	return {v坐标, v速度};
}
t运动 f反弹运动_圆形(const t向量2 &a坐标, const t向量2 &a速度, const t圆形 &a圆形) {
	const t向量2 v相对坐标 = a坐标 - a圆形.m坐标;
	const float v相对方向 = v相对坐标.fg方向r();
	const t向量2 v坐标 = 数学::f翻折<t向量2>(a坐标, a圆形.fg点r(v相对方向));
	const t向量2 v速度 = 数学::f点关于方向翻折(a速度, v相对方向 + 数学::c半π<float>);
	return {v坐标, v速度};
}
}	//namespace cflw::物理