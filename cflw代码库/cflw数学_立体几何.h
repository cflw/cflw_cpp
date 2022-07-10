﻿#pragma once
#include "cflw数学_向量.h"
namespace cflw::数学 {
//球
struct S球体 {
	S向量3 m坐标 = S向量3::c零;
	float m半径 = 0;
	S球体() = default;
	S球体(const S向量3 &, float);
	static S球体 fc坐标半径(const S向量3 &, float);
	static S球体 fc坐标直径(const S向量3 &, float);
	float fg表面积() const;
	float fg体积() const;
	float fg半径() const;
	float fg直径() const;
};
//长方体
struct S长方体 {
	S向量3 m坐标 = S向量3::c零;
	S向量3 m半尺寸 = S向量3::c零;
	S长方体() = default;
	S长方体(const S向量3 &, const S向量3 &);
	static S长方体 fc坐标尺寸(const S向量3 &, const S向量3 &);
	static S长方体 fc坐标半尺寸(const S向量3 &, const S向量3 &);
	static S长方体 fc正方体(const S向量3 &坐标, float 边长);
	static S长方体 fc对角点(const S向量3 &, const S向量3 &);
	float fg表面积() const;
	float fg体积() const;
};
//三维空间中的直线
struct S直线3 {
	float x, y, z, m, n, p;	//参数方程的形式
	S直线3();
	S直线3(float x, float y, float z, float m, float n, float p);
	static S直线3 fc参数(float x, float m, float y, float n, float z, float p);	//和构造函数顺序不一样
	static S直线3 fc两点(const S向量3 &, const S向量3 &);
	static S直线3 fc点向(const S向量3 &点, const S向量3 &方向);
	S直线3 &fs两点(const S向量3 &, const S向量3 &);
	S直线3 fg归一() const;
	S直线3 &fs归一();
	bool f相交判定(const S直线3 &) const;
	float fg模() const;
	S向量3 f在(float t) const;
};
//三维空间中的射线
struct S射线3 {
	S向量3 m坐标;
	S向量3 m方向;
	S射线3() = default;
	S射线3(const S向量3 &, const S向量3 &);
	static S射线3 fc方向(const S向量3 &, const S向量3 &);
	static S射线3 fc目标(const S向量3 &, const S向量3 &);
	S向量3 fg点(float t) const;
};
//三维空间中的平面
struct S平面3 {
	float a = 0, b = 0, c = 1, d = 0;	//ax + by + cz + d = 0
	S平面3() = default;
	S平面3(float, float, float, float);
	static S平面3 fc三点(const S向量3 &, const S向量3 &, const S向量3 &);
	static S平面3 fc点法(const S向量3 &, const S向量3 &);
	static S平面3 fc一般(float, float, float, float);
	static S平面3 fc截距(float, float, float);
	S平面3 &fs三点(const S向量3 &, const S向量3 &, const S向量3 &);
	S平面3 &fs点法(const S向量3 &, const S向量3 &);
	S平面3 &fs一般(float, float, float, float);
	S向量3 fg法线() const;
	S平面3 fg归一() const;	//a,b,c归一
};
//==============================================================================
// 立体几何计算
//==============================================================================
float f直线与平面相交位置(const S直线3 &, const S平面3 &);	//返回t
S向量3 f直线与平面交点(const S直线3 &, const S平面3 &);	//返回交点
bool f球体射线相交判定(const S球体 &, const S射线3 &);
}	//namespace cflw::数学