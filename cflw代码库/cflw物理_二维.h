#pragma once
#include <tuple>
#include "cflw数学_向量.h"
#include "cflw数学_平面几何.h"
namespace cflw::物理 {
using t向量2 = 数学::S向量2;
using t直线2 = 数学::S直线2;
using t圆形 = 数学::S圆形;
using t运动 = std::tuple<t向量2, t向量2>;
t运动 f反弹运动x(const t向量2 &坐标, const t向量2 &速度, float);
t运动 f反弹运动y(const t向量2 &坐标, const t向量2 &速度, float);
t运动 f反弹运动_直线(const t向量2 &坐标, const t向量2 &速度, const t直线2 &);
t运动 f反弹运动_圆形(const t向量2 &坐标, const t向量2 &速度, const t圆形 &);
}	//namespace cflw::物理