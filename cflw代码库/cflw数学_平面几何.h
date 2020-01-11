#pragma once
#include <functional>
#include "cflw数学_向量.h"
namespace cflw::数学 {
//=============================================================================
// 声明
//=============================================================================
//本文件
struct S圆形;
struct S旋转矩形;
struct S窗口矩形;
struct S三角形;
struct S线段2;
struct S射线2;
struct S旋转椭圆;
struct S圆角矩形;
//=============================================================================
// 平面几何结构定义
//=============================================================================
struct S圆形 {
	S向量2 m坐标;
	float m半径;
	S圆形();
	S圆形(const S向量2 &, const float &);
	static S圆形 fc坐标半径(const S向量2 &, float);
	static S圆形 fc坐标直径(const S向量2 &, float);
	S向量2 fg点r(const float &方向) const;
	S向量2 fg点d(const float &方向) const;
	S向量2 f离边最近点(const S圆形 &) const;
	bool f包含判定(const S向量2 &) const;
	float f中线切线夹角r(const S向量2 &) const;	//中线=过圆心与一点的直线
	float f垂直于中线到切线距离(const S向量2 &) const;	//切线=过圆外一点切圆的直线
};
struct S矩形 {
	S向量2 m坐标 = S向量2::c零;
	S向量2 m半尺寸 = S向量2::c一;	//尺寸的一半
	S矩形() = default;
	S矩形(const S向量2 &, const S向量2 &);
	static S矩形 fc左上右下(float 左, float 上, float 右, float 下);
	static S矩形 fc坐标尺寸(const S向量2 &, const S向量2 &);
	static S矩形 fc坐标半尺寸(const S向量2 &, const S向量2 &);
	static S矩形 fc正方形(const S向量2 &, float 边长);
	static S矩形 fc对角点(const S向量2 &, const S向量2 &);
	S向量2 fg点(float x, float y) const;
	S向量2 fg中心() const;
	S向量2 fg半尺寸() const;
	S向量2 fg尺寸() const;
	float fg周长() const;
	float fg面积() const;
	float fg左() const;
	float fg右() const;
	float fg上() const;
	float fg下() const;
	S矩形 f左边移(float) const;	//调整一条边的位置
	S矩形 f右边移(float) const;
	S矩形 f上边移(float) const;
	S矩形 f下边移(float) const;
};
struct S旋转矩形 {
	S向量2 m坐标 = S向量2::c零;
	S向量2 m半尺寸 = S向量2::c一;	//尺寸的一半
	float m方向 = 0;
	S旋转矩形() = default;
	S旋转矩形(const S向量2 &, const S向量2 &, float);
	S旋转矩形(const S矩形 &, float);
	static S旋转矩形 fc线段(const S向量2 &, const S向量2 &, float 宽度 = 0);
	static S旋转矩形 fc左上右下(float 左, float 上, float 右, float 下, float 方向 = 0);
	static S旋转矩形 fc坐标尺寸(const S向量2 &, const S向量2 &, float 方向 = 0);
	static S旋转矩形 fc坐标半尺寸(const S向量2 &, const S向量2 &, float 方向 = 0);
	S向量2 fg点(float x, float y) const;
	float fg周长() const;
	float fg面积() const;
	float fg半对角线长() const;
	float fg长半轴长() const;
	float fg短半轴长() const;
	S向量2 fg全尺寸() const;
	bool f遍历顶点(std::function<bool(const S向量2 &)>) const;
	bool f包含判定(const S向量2 &) const;
	S窗口矩形 f到窗口矩形(float, float);
};
struct S窗口矩形 {
	float m左, m上, m右, m下;
	S窗口矩形();
	S窗口矩形(float, float, float, float);
	S窗口矩形(const S向量2 &, const S向量2 &);
	static S窗口矩形 fc坐标半尺寸(const S向量2 &, const S向量2 &);
	float fg宽();
	float fg高();
	S向量2 fg中心();
	S向量2 fg半尺寸();
	S窗口矩形 f对齐左边(float);
	S窗口矩形 f对齐上边(float);
	S窗口矩形 f对齐右边(float);
	S窗口矩形 f对齐下边(float);
	S窗口矩形 f对齐中心(const S向量2 &);
	S窗口矩形 f移动(const S向量2 &);
	S旋转矩形 f到直角矩形(float, float);
};
//三角形
struct S三角形 {
	S向量2 m点[3];
	S三角形();
	S三角形(const S向量2 &, const S向量2 &, const S向量2 &);
	//基本属性
	S向量2 fg点(int) const;
	S线段2 fg边(int) const;
	float fg边长(int) const;
	float fg角r(int) const;
	float fg角d(int) const;
	//坐标
	S向量2 f标准坐标(const S向量3 &) const;
	S向量3 f重心坐标(const S向量2 &) const;
	//心
	S向量2 fg重心() const;
	S向量2 fg垂心() const;
	S向量2 fg内心() const;
	S向量2 fg外心() const;
	//圆
	S圆形 fg内切圆() const;
	S圆形 fg外接圆() const;
};
//直线
struct S直线2 {
	float a, b, c;	// a*x + b*y + c = 0
	S直线2();
	S直线2(float, float, float);
	static S直线2 fc点斜(const S向量2 &, const float &);
	static S直线2 fc两点(const S向量2 &, const S向量2 &);
	static S直线2 fc斜截(const float &, const float &);
	static S直线2 fc截距(const float &, const float &);
	static S直线2 fc一般(const float &, const float &, const float &);
	static S直线2 fc点法(const S向量2 &, const S向量2 &);
	static S直线2 fc点向(const S向量2 &, const float &);
	float f到点距离(const S向量2 &) const;
	float fg斜率() const;
	S直线2 f平移(const S向量2 &) const;
	float f求x(const float &) const;
	float f求y(const float &) const;
	bool f平行(const S直线2 &) const;
	float fg方向r() const;
	float fg方向d() const;
	S向量2 f交点(const S直线2 &) const;
	S向量2 fg法向量() const;
	bool f交x轴(int) const;
	bool f交y轴(int) const;
	bool fi平行x轴() const;
	bool fi平行y轴() const;
	bool fi垂直x轴() const;
	bool fi垂直y轴() const;
};
//线段2
struct S线段2 {
	S向量2 m点[2];
	S线段2(void);
	S线段2(const S向量2 &, const S向量2 &);
	static S线段2 fc两点(const S向量2 &, const S向量2 &);
	S线段2 &fs两点(const S向量2 &, const S向量2 &);
	S线段2 &fs平移(const S向量2 &);
	S线段2 &fs旋转r(const float &);
	S线段2 &fs旋转d(const float &);
	S线段2 f平移(const S向量2 &) const;
	S线段2 f旋转r(const float &) const;
	S线段2 f旋转d(const float &) const;
	S线段2 f两点对调() const;
	float fg方向r() const;
	float fg方向d() const;
	float fg斜率() const;
};
//射线
struct S射线2 {
	S向量2 m坐标;
	float m方向;
	S射线2();
	S射线2(const S向量2 &, float);
	void fs点向(const S向量2 &, const S向量2 &);
	void fs两点(const S向量2 &, const S向量2 &);
	float f同向距离(const S向量2 &) const;
	float f侧向距离(const S向量2 &) const;
	S向量2 f相对距离(const S向量2 &) const;
};
//椭圆
struct S椭圆 {
	S向量2 m坐标 = S向量2::c零;
	S向量2 m半径 = S向量2::c一;
	S椭圆() = default;
	S椭圆(const S向量2 &, const S向量2 &);
	static S椭圆 fc圆(const S向量2 &, float);
	bool fw圆() const;
	S向量2 f取点(float) const;
};
//旋转椭圆
struct S旋转椭圆 {
	S向量2 m坐标 = S向量2::c零;
	S向量2 m半径 = S向量2::c一;
	float m方向 = 0;
	S旋转椭圆();
	S旋转椭圆(const S向量2 &, const S向量2 &, float);
	static S旋转椭圆 fc圆(const S向量2 &, float);
	bool fw圆() const;
	S向量2 f取点(float) const;
};
//圆角矩形
struct S圆角矩形 {
	S向量2 m坐标, m半尺寸, m角半径;
	S圆角矩形();
	S圆角矩形(const S向量2 &, const S向量2 &, const S向量2 &);
};
//=============================================================================
// 平面几何计算
//=============================================================================
//参数散开的相交判定函数
bool f圆形相交判定(const S向量2 &, float, const S向量2 &, float);
bool f圆形旋转矩形相交判定(const S向量2 &, float, const S向量2 &, const S向量2 &, float);
//形状相交判定,顺序:向量,圆形,矩形,线段,射线,椭圆,直线,三角形
bool f向量重叠判定(float *, float *, int);
bool f向量线段相交判定(const S向量2 &, const S线段2 &);
bool f向量圆形相交判定(const S向量2 &, const S圆形 &);
bool f向量旋转矩形相交判定(const S向量2 &, const S旋转矩形 &);
bool f圆形相交判定(const S圆形 &, const S圆形 &);
bool f圆形旋转矩形相交判定(const S圆形 &, const S旋转矩形 &);
bool f圆形线段相交判定(const S圆形 &, const S线段2 &);
bool f圆形射线相交判定(const S圆形 &, const S射线2 &);
bool f圆形旋转椭圆相交判定(const S圆形 &, const S旋转椭圆 &);
bool f圆形直线相交判定(const S圆形 &, const S直线2 &);
bool f旋转矩形相交判定(const S旋转矩形 &, const S旋转矩形 &);
bool f旋转矩形线段相交判定(const S旋转矩形 &, const S线段2 &);
bool f旋转矩形射线相交判定(const S旋转矩形 &, const S射线2 &);
bool f线段相交判定(const S线段2 &, const S线段2 &);
bool f线段三角形相交判定(const S线段2 &, const S三角形 &);
bool f旋转椭圆相交判定(const S旋转椭圆 &, const S旋转椭圆 &);
bool f三角形相交判定(const S三角形 &, const S三角形 &);
//位置关系
int f点圆位置关系(const S向量2 &, const S圆形 &);
int f点旋转椭圆位置关系(const S向量2 &, const S旋转椭圆 &);

}