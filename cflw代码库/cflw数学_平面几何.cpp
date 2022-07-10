#include <assert.h>
#include "cflw数学.h"
#include "cflw数学_常数.h"
#include "cflw数学_平面几何.h"
#include "cflw数学_函数方程.h"
namespace cflw::数学 {
//==============================================================================
// 通用函数
//==============================================================================
template<> S圆形 f平均<S圆形>(const S圆形 &a, const S圆形 &b) {
	return S圆形(
		f平均<S向量2>(a.m坐标, b.m坐标),
		f平均<float>(a.m半径, b.m半径)
	);
}
template<> S矩形 f平均<S矩形>(const S矩形 &a, const S矩形 &b) {
	return S矩形(
		f平均<S向量2>(a.m坐标, b.m坐标),
		f平均<S向量2>(a.m半尺寸, b.m半尺寸)
	);
}
template<> S旋转矩形 f平均<S旋转矩形>(const S旋转矩形 &a, const S旋转矩形 &b) {
	return S旋转矩形(
		f平均<S向量2>(a.m坐标, b.m坐标),
		f平均<S向量2>(a.m半尺寸, b.m半尺寸),
		c弧度计算<float>.f平均(a.m方向, b.m方向)
	);
}
template<> S窗口矩形 f平均<S窗口矩形>(const S窗口矩形 &a, const S窗口矩形 &b) {
	return S窗口矩形(
		f平均<float>(a.m左, b.m左),
		f平均<float>(a.m上, b.m上),
		f平均<float>(a.m右, b.m右),
		f平均<float>(a.m下, b.m下)
	);
}
template<> S直线2 f平均<S直线2>(const S直线2 &a, const S直线2 &b) {
	return S直线2(
		f平均<float>(a.a, b.a),
		f平均<float>(a.b, b.b),
		f平均<float>(a.c, b.c)
	);
}
template<> S线段2 f平均<S线段2>(const S线段2 &a, const S线段2 &b) {
	return S线段2(
		f平均<S向量2>(a.m点[0], b.m点[0]),
		f平均<S向量2>(a.m点[1], b.m点[1])
	);
}
template<> S射线2 f平均<S射线2>(const S射线2 &a, const S射线2 &b) {
	return S射线2(
		f平均<S向量2>(a.m坐标, b.m坐标),
		c弧度计算<float>.f平均(a.m方向, b.m方向)
	);
}
template<> S椭圆 f平均<S椭圆>(const S椭圆 &a, const S椭圆 &b) {
	return S椭圆(
		f平均<S向量2>(a.m坐标, b.m坐标),
		f平均<S向量2>(a.m半径, a.m半径)
	);
}
template<> S旋转椭圆 f平均<S旋转椭圆>(const S旋转椭圆 &a, const S旋转椭圆 &b) {
	return S旋转椭圆(
		f平均<S向量2>(a.m坐标, b.m坐标),
		f平均<S向量2>(a.m半径, a.m半径),
		c弧度计算<float>.f平均(a.m方向, b.m方向)
	);
}
template<> S圆角矩形 f平均<S圆角矩形>(const S圆角矩形 &a, const S圆角矩形 &b) {
	return S圆角矩形(
		f平均<S向量2>(a.m坐标, b.m坐标),
		f平均<S向量2>(a.m半尺寸, b.m半尺寸),
		f平均<S向量2>(a.m角半径, b.m角半径)
	);
}
//==============================================================================
// 形状几何
//==============================================================================
//散开的参数
bool f圆形相交判定(const S向量2 &a坐标0, float a半径0, const S向量2 &a坐标1, float a半径1) {
	const float v距离 = a坐标0.f到点距离(a坐标1);
	const float v半径和 = a半径0 + a半径1;
	return v距离 <= v半径和;
}
bool f圆形旋转矩形相交判定(const S向量2 &a圆形坐标, float a圆形半径, const S向量2 &a矩形坐标, const S向量2 &a矩形半尺寸, float a矩形方向) {
	S向量2 v圆形坐标 = a圆形坐标 - a矩形坐标;	//←矩形坐标为原点
	v圆形坐标 = v圆形坐标.f旋转r(-a矩形方向);	//←把矩形旋转角度调整为0度,并旋转圆形坐标
	v圆形坐标 = f绝对值<S向量2>(v圆形坐标);	//←把判定全部扔到第一象限
	//↓开始判断
	const float vx距离和 = a矩形半尺寸.x + a圆形半径;
	const float vy距离和 = a矩形半尺寸.y + a圆形半径;
	if (v圆形坐标.x <= vx距离和 && v圆形坐标.y <= vy距离和) {
		//↑圆形x坐标和y坐标是否在距离内	//↓可能相交
		if (v圆形坐标.x > a矩形半尺寸.x && v圆形坐标.y > a矩形半尺寸.y) {
			//在矩形边长外
			v圆形坐标 -= a矩形半尺寸;
			return v圆形坐标.fg大小() <= a圆形半径;	//在矩形角半径内
		} else {
			return true;	//在边长边缘或里面
		}
	} else {
		return false;	//没有相交
	}
}
bool f线段相交判定(const S向量2 &a点0, const S向量2 &a点1, const S向量2 &a点2, const S向量2 &a点3) {
	//计算范围
	const S向量2 v1最大(std::max<float>(a点0.x, a点1.x), std::max<float>(a点0.y, a点1.y));
	const S向量2 v1最小(std::min<float>(a点0.x, a点1.x), std::min<float>(a点0.y, a点1.y));
	const S向量2 v2最大(std::max<float>(a点2.x, a点3.x), std::max<float>(a点2.y, a点3.y));
	const S向量2 v2最小(std::min<float>(a点2.x, a点3.x), std::min<float>(a点2.y, a点3.y));
	if (v1最大.x < v2最小.x) return false;
	if (v2最大.x < v1最小.x) return false;
	if (v1最大.y < v2最小.y) return false;
	if (v2最大.y < v1最小.y) return false;
	const float v范围左 = std::max<float>(v1最小.x, v2最小.x);
	const float v范围右 = std::min<float>(v1最大.x, v2最大.x);
	//计算直线方程
	const S直线2 v直线0 = S直线2::fc两点(a点0, a点1);
	const S直线2 v直线1 = S直线2::fc两点(a点2, a点3);
	if (v直线0.fi平行(v直线1)) {
		return false;
	}
	auto f线段平行y轴时判断 = [](float x, float y0, float y1, const S向量2 &a正常0, const S向量2 &a正常1)->bool {
		const float vx长 = a正常0.x - a正常1.x;
		const float v位置 = (x - a正常1.x) / vx长;
		const float vy长 = a正常0.y - a正常1.y;
		const float vy = a正常1.y + v位置 * vy长;
		const auto [v下点, v上点] = f小大<float>(y0, y1);
		return vy >= v下点 && vy <= v上点;
	};
	if (v直线0.fi平行y轴()) {
		if (f线段平行y轴时判断(a点0.x, a点0.y, a点1.y, a点2, a点3)) {
			return true;
		}
	}
	if (v直线1.fi平行y轴()) {
		if (f线段平行y轴时判断(a点2.x, a点2.y, a点3.y, a点0, a点1)) {
			return true;
		}
	}
	//计算公共区域相交
	const float v点[2][2] = {
		{v直线0.f求y(v范围左), v直线1.f求y(v范围左)},
		{v直线0.f求y(v范围右), v直线1.f求y(v范围右)}
	};
	if (v点[0][0] == v点[0][1]) return true;
	if (v点[1][0] == v点[1][1]) return true;
	return (v点[0][0] > v点[0][1]) != (v点[1][0] > v点[1][1]);
}
//组合类型
bool f向量重叠判定(float *a1, float *a2, int a参数数量) {
	for (int i = 0; i != a参数数量; ++i) {
		if (a1 != a2) {
			return false;
		}
	}
	return true;
}
//
bool f向量线段相交判定(const S向量2 &a点, const S线段2 &a线) {
	S向量2 v点[2] = {a线.m点[0] - a点, a线.m点[1] - a点};
	if (v点[0].x * v点[1].x > 0) {
		return false;
	}
	return v点[0].x * v点[1].y == v点[0].y * v点[1].x;
}
bool f向量圆形相交判定(const S向量2 &a向量, const S圆形 &a圆形) {
	return (a向量 - a圆形.m坐标).fg大小() <= a圆形.m半径;
}
bool f向量矩形相交判定(const S向量2 &a向量, const S矩形 &a矩形) {
	const S向量2 v相对坐标 = a向量 - a矩形.m坐标;
	const bool x = abs(v相对坐标.x) <= a矩形.m半尺寸.x;
	const bool y = abs(v相对坐标.y) <= a矩形.m半尺寸.y;
	return x && y;
}
bool f向量旋转矩形相交判定(const S向量2 &a向量, const S旋转矩形 &a矩形) {
	const S向量2 v相对坐标 = (a向量 - a矩形.m坐标).f旋转r(-a矩形.m方向);
	const bool x = abs(v相对坐标.x) <= a矩形.m半尺寸.x;
	const bool y = abs(v相对坐标.y) <= a矩形.m半尺寸.y;
	return x && y;
}
bool f圆形相交判定(const S圆形 &a圆形1, const S圆形 &a圆形2) {
	return f圆形相交判定(a圆形1.m坐标, a圆形1.m半径, a圆形2.m坐标, a圆形2.m半径);
}
bool f圆形旋转矩形相交判定(const S圆形 &a圆形, const S旋转矩形 &a矩形) {
	return f圆形旋转矩形相交判定(a圆形.m坐标, a圆形.m半径, a矩形.m坐标, a矩形.m半尺寸, a矩形.m方向);
}
bool f圆形线段相交判定(const S圆形 &a圆形, const S线段2 &a线段) {
	S线段2 v线段 = a线段;
	v线段.fs平移(-a圆形.m坐标);
	if (v线段.m点[0].fg大小() <= a圆形.m半径) {
		return true;
	}
	if (v线段.m点[1].fg大小() <= a圆形.m半径) {
		return true;
	}
	v线段.fs旋转r(-a线段.fg方向r() + c半π<float>);
	if (f同符号(v线段.m点[0].y, v线段.m点[1].y)) {
		return false;
	} else {
		if (f绝对值(v线段.m点[0].x) <= a圆形.m半径) {
			return true;
		}
	}
	return false;
}
bool f圆形射线相交判定(const S圆形 &a圆形, const S射线2 &a射线) {
	const S向量2 v相对距离 = a射线.f相对距离(a圆形.m坐标);
	if (v相对距离.x < 0) {
		return v相对距离.y <= a圆形.m半径;
	} else {
		return a射线.m坐标.f到点距离(a圆形.m坐标) <= a圆形.m半径;
	}
}
bool f圆形旋转椭圆相交判定(const S圆形 &a圆形, const S旋转椭圆 &a椭圆) {
	S向量2 m圆坐标 = a圆形.m坐标.f旋转r(-a椭圆.m方向);
	const float a平方 = a椭圆.m半径.x * a椭圆.m半径.x;
	const float b平方 = a椭圆.m半径.y * a椭圆.m半径.y;
	const float y平方 = (a平方 - a圆形.m半径 * a圆形.m半径) / a平方 * b平方;
	return y平方 >= 0;
}
bool f圆形直线相交判定(const S圆形 &a圆形, const S直线2 &a直线) {
	return a直线.f到点距离(a圆形.m坐标) <= a圆形.m半径;
}
bool f旋转矩形相交判定(const S旋转矩形 &a1, const S旋转矩形 &a2) {
	//计算是否太远或太近
	const float v距离 = (a1.m坐标 - a2.m坐标).fg大小();
	if (v距离 > a1.fg半对角线长() + a2.fg半对角线长()) {
		return false;	//太远
	}
	if (v距离 <= a1.fg短半轴长() + a2.fg短半轴长()) {
		return true;	//太近
	}
	//获得矩形所有顶点
	const S向量2 v顶点[2][4] = {
		{a1.fg点(1, 1), a1.fg点(1, -1), a1.fg点(-1, 1), a1.fg点(-1, -1)},
		{a2.fg点(1, 1), a2.fg点(1, -1), a2.fg点(-1, 1), a2.fg点(-1, -1)}
	};
	//线段两两相交判定
	auto f0 = [&v顶点](const S向量2 &a点1, const S向量2 &a点2)->bool {
		S线段2 v线段1{a点1, a点2};
		auto f1 = [&v线段1](const S向量2 &a点1, const S向量2 &a点2)->bool {
			S线段2 v线段2{a点1, a点2};
			return f线段相交判定(v线段1, v线段2);
		};
		if (f1(v顶点[1][0], v顶点[1][1])) return true;
		if (f1(v顶点[1][1], v顶点[1][2])) return true;
		if (f1(v顶点[1][2], v顶点[1][3])) return true;
		if (f1(v顶点[1][3], v顶点[1][0])) return true;
		return false;
	};
	if (f0(v顶点[1][0], v顶点[1][1])) return true;
	if (f0(v顶点[1][1], v顶点[1][2])) return true;
	if (f0(v顶点[1][2], v顶点[1][3])) return true;
	if (f0(v顶点[1][3], v顶点[1][0])) return true;
	return false;
}
bool f旋转矩形线段相交判定(const S旋转矩形 &a矩形, const S线段2 &a线段) {
	if (f向量旋转矩形相交判定(a线段.m点[0], a矩形)) return true;
	if (f向量旋转矩形相交判定(a线段.m点[1], a矩形)) return true;
	const S向量2 v顶点[4] = {a矩形.fg点(1, 1), a矩形.fg点(1, -1), a矩形.fg点(-1, 1), a矩形.fg点(-1, -1)};
	auto f = [&a线段](const S向量2 &a点1, const S向量2 &a点2)->bool {
		S线段2 m线段{a点1, a点2};
		return f线段相交判定(a线段, m线段);
	};
	if (f(v顶点[0], v顶点[1])) return true;
	if (f(v顶点[1], v顶点[2])) return true;
	if (f(v顶点[2], v顶点[3])) return true;
	if (f(v顶点[3], v顶点[0])) return true;
	return false;
}
bool f旋转矩形射线相交判定(const S旋转矩形 &a矩形, const S射线2 &a射线) {
	const S向量2 v顶点[4] = {a射线.f相对距离(a矩形.fg点(1, 1)), a射线.f相对距离(a矩形.fg点(-1, 1)),
		a射线.f相对距离(a矩形.fg点(-1, -1)), a射线.f相对距离(a矩形.fg点(1, -1))};
	auto f = [](const S向量2 &a1, const S向量2 &a2)->bool {
		if (a1.x < 0 && a2.x < 0)
			return false;	//两点都在后面
		if (f同符号(a1.y, a2.y))
			return false;	//两点同侧
		if (a1.x >= 0 && a2.x >= 0)
			return true;	//连点都在前面
		S直线2 m直线 = S直线2::fc两点(a1, a2);
		return m直线.f求x(0) >= 0;
	};
	if (f(v顶点[0], v顶点[1])) return true;
	if (f(v顶点[1], v顶点[2])) return true;
	if (f(v顶点[2], v顶点[3])) return true;
	if (f(v顶点[3], v顶点[0])) return true;
	return false;
}
bool f线段相交判定(const S线段2 &a0, const S线段2 &a1) {
	return f线段相交判定(a0.m点[0], a0.m点[1], a1.m点[0], a1.m点[1]);
}
bool f线段三角形相交判定(const S线段2 &a线段, const S三角形 &a三角形) {
	for (int i = 0; i != 3; ++i) {
		if (f线段相交判定(a线段, a三角形.fg边(i))) {
			return true;
		}
	}
	return false;
}
bool f旋转椭圆相交判定(const S旋转椭圆 &a1, const S旋转椭圆 &a2) {
	//判断是否有圆
	const S圆形 v圆1(a1.m坐标, a1.m半径.x);
	const S圆形 v圆2(a1.m坐标, a1.m半径.x);
	if (a1.fi圆()) {
		if (a2.fi圆())
			return f圆形相交判定(v圆1, v圆2);
		else
			return f圆形旋转椭圆相交判定(v圆1, a2);
	} else if (a2.fi圆()) {
		return f圆形旋转椭圆相交判定(v圆2, a1);
	} else {

	}
	//↓未做
	return false;
}
bool f三角形相交判定(const S三角形 &a1, const S三角形 &a2) {
	const S线段2 v1[3] = {a1.fg边(0), a1.fg边(1), a1.fg边(2)};
	const S线段2 v2[3] = {a2.fg边(0), a2.fg边(1), a2.fg边(2)};
	for (int i = 0; i != 3; ++i) {
		for (int j = 0; j != 2; ++i) {
			if (f线段相交判定(v1[i], v2[j])) {
				return true;
			}
		}
	}
	return false;
}
//翻折
S向量2 f点关于直线翻折(const S向量2 &a点, const S直线2 &a直线) {
	assert(a直线.fi有效());
	S向量2 v = a点;
	if (a直线.a == 0) {//直线平行于y轴
		const float d = -a直线.c / a直线.b;
		v.x = f翻折(v.x, d);
	} else if (a直线.b == 0) {//直线平行于x轴
		const float d = -a直线.c / a直线.a;
		v.y = f翻折(v.y, d);
	} else {
		const float v距离 = a直线.f到点距离(a点);
		const float v斜 = hypotf(a直线.a, a直线.b);
		v.x = a点.x - a直线.a / v斜 * v距离;
		v.y = a点.y - a直线.b / v斜 * v距离;
	}
	return v;
}
S向量2 f点关于方向翻折(const S向量2 &a点, float a方向) {
	return S向量2::fc方向r(a点.fg大小(), f翻折(a点.fg方向r(), a方向));
}
S向量2 f点关于圆形翻折(const S向量2 &a点, const S圆形 &a圆形) {
	const S向量2 v相对 = a点 - a圆形.m坐标;
	const float v距离 = v相对.fg大小();
	const float v方向 = v相对.fg方向r();
	return S向量2::fc方向r(f翻折(v距离, a圆形.m半径), v方向);
}
//==============================================================================
// 圆形
//==============================================================================
S圆形::S圆形(void) :
	m坐标(),
	m半径(0) {
}
S圆形::S圆形(const S向量2 &a坐标, const float &a半径) :
	m坐标(a坐标),
	m半径(a半径) {
}
S圆形 S圆形::fc坐标半径(const S向量2 &a坐标, float a半径) {
	return S圆形(a坐标, a半径);
}
S圆形 S圆形::fc坐标直径(const S向量2 &a坐标, float a直径) {
	return S圆形(a坐标, a直径 * 0.5f);
}
S向量2 S圆形::fg点r(const float &r) const {
	S向量2 v = S向量2::fc方向r(m半径, r);
	return v + m坐标;
}
S向量2 S圆形::fg点d(const float &d) const {
	return fg点r(d * c度到弧度<float>);
}
float S圆形::fg周长() const {
	return 2 * cπ<float> * m半径;
}
float S圆形::fg半径() const {
	return cπ<float> * m半径 * m半径;
}
S向量2 S圆形::f离边最近点(const S圆形 &a圆) const {
	const float v方向1 = m坐标.f到点方向r(a圆.m坐标);
	const S向量2 v点1 = fg点r(v方向1);
	const float v方向2 = a圆.m坐标.f到点方向r(m坐标);
	const S向量2 v点2 = a圆.fg点r(v方向2);
	return f平均<S向量2>(v点1, v点2);
}
bool S圆形::fi包含点(const S向量2 &p) const {
	return f向量圆形相交判定(p, *this);
}
float S圆形::f中线切线夹角r(const S向量2 &a点) const {
	if (fi包含点(a点)) {
		return 0;	//点不能在圆内
	}
	const float v中线 = m坐标.f到点距离(a点);
	return asin(m半径 / v中线);
}
float S圆形::f垂直于中线到切线距离(const S向量2 &a点) const {
	if (fi包含点(a点)) {
		return m半径;	//点不能在圆内
	}
	const float v中线 = m坐标.f到点距离(a点);
	const float v夹角 = asin(m半径 / v中线);
	return tan(v夹角) * v中线;
}
//==============================================================================
// 矩形
//==============================================================================
S矩形::S矩形(const S向量2 &a坐标, const S向量2 &a半尺寸) :
	m坐标(a坐标), m半尺寸(a半尺寸) {
}
S矩形 S矩形::fc左上右下(float a左, float a上, float a右, float a下) {
	S矩形 v;
	v.m坐标.x = (a左 + a右) / 2;
	v.m坐标.y = (a上 + a下) / 2;
	v.m半尺寸.x = (a右 - a左) / 2;
	v.m半尺寸.y = (a上 - a下) / 2;
	return v;
}
S矩形 S矩形::fc坐标尺寸(const S向量2 &a坐标, const S向量2 &a全尺寸) {
	return {a坐标, a全尺寸 / 2};
}
S矩形 S矩形::fc坐标半尺寸(const S向量2 &a坐标, const S向量2 &a半尺寸) {
	return {a坐标, a半尺寸};
}
S矩形 S矩形::fc正方形(const S向量2 &a坐标, float a边长) {
	const float v半尺寸 = a边长 / 2;
	return {a坐标, {v半尺寸, v半尺寸}};
}
S矩形 S矩形::fc对角点(const S向量2 &a, const S向量2 &b) {
	S矩形 v;
	v.m坐标.x = (a.x + b.x) / 2;
	v.m坐标.y = (a.y + b.y) / 2;
	v.m半尺寸.x = std::abs(a.x - b.x) / 2;
	v.m半尺寸.y = std::abs(a.y - b.y) / 2;
	return v;
}
S矩形 S矩形::fc原点尺寸(float a宽, float a高) {
	S矩形 v;
	v.m半尺寸.x = a宽 * 0.5f;
	v.m半尺寸.y = a高 * 0.5f;
	return v;
}
S矩形 S矩形::fc原点半尺寸(float a宽, float a高) {
	S矩形 v;
	v.m半尺寸.x = a宽;
	v.m半尺寸.y = a高;
	return v;
}
float S矩形::f计算周长(const S向量2 &a半尺寸) {
	return (a半尺寸.x + a半尺寸.y) * 4;
}
float S矩形::f计算面积(const S向量2 &a半尺寸) {
	return a半尺寸.x * a半尺寸.y * 4;
}
S向量2 S矩形::fg点(float X, float Y) const {
	S向量2 v顶点;
	v顶点.x = X * m半尺寸.x;
	v顶点.y = Y * m半尺寸.y;
	return v顶点 + m坐标;
}
S向量2 S矩形::fg中心() const {
	return m坐标;
}
S向量2 S矩形::fg半尺寸() const {
	return m半尺寸;
}
S向量2 S矩形::fg尺寸() const {
	return m半尺寸 * 2;
}
float S矩形::fg周长() const {
	return S矩形::f计算周长(m半尺寸);
}
float S矩形::fg面积() const {
	return S矩形::f计算面积(m半尺寸);
}
float S矩形::fg左() const {
	return m坐标.x - m半尺寸.x;
}
float S矩形::fg右() const {
	return m坐标.x + m半尺寸.x;
}
float S矩形::fg上() const {
	return m坐标.y + m半尺寸.y;
}
float S矩形::fg下() const {
	return m坐标.y - m半尺寸.y;
}
void S矩形::fs左(float a左) {
	fs左右(a左, fg右());
}
void S矩形::fs右(float a右) {
	fs左右(fg左(), a右);
}
void S矩形::fs上(float a上) {
	fs上下(a上, fg下());
}
void S矩形::fs下(float a下) {
	fs上下(fg上(), a下);
}
void S矩形::fs左右(float a左, float a右) {
	m坐标.x = (a左 + a右) * 0.5f;
	m半尺寸.x = (a右 - a左) * 0.5f;
}
void S矩形::fs上下(float a上, float a下) {
	m坐标.y = (a上 + a下) * 0.5f;
	m半尺寸.y = (a上 - a下) * 0.5f;
}
void S矩形::fs下上(float a下, float a上) {
	m坐标.y = (a上 + a下) * 0.5f;
	m半尺寸.y = (a上 - a下) * 0.5f;
}
S矩形 S矩形::f左边移(float x) const {
	const float v坐标x = m坐标.x + x * 0.5f;
	const float v半尺寸x = m半尺寸.x - x * 0.5f;
	return S矩形::fc坐标半尺寸({v坐标x, m坐标.y}, {v半尺寸x, m半尺寸.y});
}
S矩形 S矩形::f右边移(float x) const {
	const float v坐标x = m坐标.x + x * 0.5f;
	const float v半尺寸x = m半尺寸.x + x * 0.5f;
	return S矩形::fc坐标半尺寸({v坐标x, m坐标.y}, {v半尺寸x, m半尺寸.y});
}
S矩形 S矩形::f上边移(float y) const {
	const float v坐标y = m坐标.y + y * 0.5f;
	const float v半尺寸y = m半尺寸.y + y * 0.5f;
	return S矩形::fc坐标半尺寸({m坐标.x, v坐标y}, {m半尺寸.x, v半尺寸y});
}
S矩形 S矩形::f下边移(float y) const {
	const float v坐标y = m坐标.y + y * 0.5f;
	const float v半尺寸y = m半尺寸.y - y * 0.5f;
	return S矩形::fc坐标半尺寸({m坐标.x, v坐标y}, {m半尺寸.x, v半尺寸y});
}
bool S矩形::fi包含点(const S向量2 &a点) const {
	return f向量矩形相交判定(a点, *this);
}
//==============================================================================
// 旋转矩形
//==============================================================================
S旋转矩形::S旋转矩形(const S向量2 &a坐标, const S向量2 &a半尺寸, float a方向):
	m坐标(a坐标), m半尺寸(a半尺寸), m方向(a方向) {
}
S旋转矩形::S旋转矩形(const S矩形 &a矩形, float a方向):
	m坐标(a矩形.m坐标), m半尺寸(a矩形.m半尺寸), m方向(a方向) {
}
S旋转矩形 S旋转矩形::fc线段(const S向量2 &a点0, const S向量2 &a点1, float a宽) {
	S旋转矩形 v;
	v.m坐标 = (a点0 + a点1) / 2;
	v.m半尺寸.x = a点0.f到点距离(a点1) / 2;
	v.m半尺寸.y = a宽 / 2;
	v.m方向 = a点0.f到点方向r(a点1);
	return v;
}
S旋转矩形 S旋转矩形::fc左上右下(float a左, float a上, float a右, float a下, float a方向) {
	S旋转矩形 v;
	v.m坐标.x = (a左 + a右) / 2;
	v.m坐标.y = (a上 + a下) / 2;
	v.m半尺寸.x = (a右 - a左) / 2;
	v.m半尺寸.y = (a上 - a下) / 2;
	v.m方向 = a方向;
	return v;
}
S旋转矩形 S旋转矩形::fc坐标尺寸(const S向量2 &a坐标, const S向量2 &a全尺寸, float a方向) {
	return {a坐标, a全尺寸 / 2, a方向};
}
S旋转矩形 S旋转矩形::fc坐标半尺寸(const S向量2 &a坐标, const S向量2 &a半尺寸, float a方向) {
	return {a坐标, a半尺寸, a方向};
}
float S旋转矩形::fg周长() const {
	return S矩形::f计算周长(m半尺寸);
}
float S旋转矩形::fg面积() const {
	return S矩形::f计算面积(m半尺寸);
}
float S旋转矩形::fg半对角线长() const {
	return hypotf(m半尺寸.x, m半尺寸.y);
}
float S旋转矩形::fg长半轴长() const {
	return std::max<float>(m半尺寸.x, m半尺寸.y);
}
float S旋转矩形::fg短半轴长() const {
	return std::max<float>(m半尺寸.x, m半尺寸.y);
}
S向量2 S旋转矩形::fg全尺寸() const {
	return m半尺寸 * 2;
}
bool S旋转矩形::fi包含点(const S向量2 &p) const {
	return f向量旋转矩形相交判定(p, *this);
}
S向量2 S旋转矩形::fg点(float X, float Y) const {
	S向量2 v顶点;
	v顶点.x = X * m半尺寸.x;
	v顶点.y = Y * m半尺寸.y;
	v顶点 = v顶点.f旋转r(m方向);
	return v顶点 + m坐标;
}
bool S旋转矩形::f遍历顶点(std::function<bool(const S向量2 &)> f) const {
	if (f(fg点(1, 1))) return true;
	if (f(fg点(1, -1))) return true;
	if (f(fg点(-1, 1))) return true;
	if (f(fg点(-1, -1))) return true;
	return false;
}
S窗口矩形 S旋转矩形::f到窗口矩形(float x, float y) {
	S向量2 m中心 = m坐标.f窗口坐标(x, y);
	return S窗口矩形::fc坐标半尺寸(m中心, m半尺寸);
}
//==============================================================================
// 窗口矩形
//==============================================================================
S窗口矩形::S窗口矩形() :S窗口矩形{0, 0, 0, 0} {}
S窗口矩形::S窗口矩形(float a左, float a上, float a右, float a下) :
	m左(a左), m上(a上), m右(a右), m下(a下) {
}
S窗口矩形::S窗口矩形(const S向量2 &a1, const S向量2 &a2) {
	if (a1.x < a2.x) {
		m左 = a1.x;
		m右 = a2.x;
	} else {
		m左 = a2.x;
		m右 = a1.x;
	}
	if (a1.y < a2.y) {
		m上 = a1.x;
		m下 = a2.x;
	} else {
		m上 = a2.x;
		m下 = a1.x;
	}
}
S窗口矩形 S窗口矩形::fc坐标半尺寸(const S向量2 &a坐标, const S向量2 &a半尺寸) {
	return{a坐标.x - a半尺寸.x, a坐标.y - a半尺寸.y, a坐标.x + a半尺寸.x, a坐标.y + a半尺寸.y};
}
float S窗口矩形::fg宽() const {
	return m右 - m左;
}
float S窗口矩形::fg高() const {
	return m下 - m上;
}
S向量2 S窗口矩形::fg中心() const {
	return{(m左 + m右) / 2, (m上 + m下) / 2};
}
S向量2 S窗口矩形::fg半尺寸() const {
	return{fg宽() / 2, fg高() / 2};
}
float S窗口矩形::fg周长() const {
	return S矩形::f计算周长(fg半尺寸());
}
float S窗口矩形::fg面积() const {
	return S矩形::f计算面积(fg半尺寸());
}
S窗口矩形 S窗口矩形::f对齐左边(float a左) {
	return{a左, m上, a左 + fg宽(), m下};
}
S窗口矩形 S窗口矩形::f对齐上边(float a上) {
	return{m左, a上, m右, a上 + fg高()};
}
S窗口矩形 S窗口矩形::f对齐右边(float a右) {
	return{a右 - fg宽(), m上, a右, m下};
}
S窗口矩形 S窗口矩形::f对齐下边(float a下) {
	return{m左, a下 - fg高(), m右, a下};
}
S窗口矩形 S窗口矩形::f对齐中心(const S向量2 &a中心) {
	const float m半宽 = fg宽() / 2;
	const float m半高 = fg高() / 2;
	return{a中心.x - m半宽, a中心.y - m半高, a中心.x + m半宽, a中心.y + m半高};
}
S窗口矩形 S窗口矩形::fg移动(const S向量2 &a移动) {
	return{m左 + a移动.x, m上 + a移动.y, m右 + a移动.x, m下 + a移动.y};
}
S旋转矩形 S窗口矩形::f到直角矩形(float x, float y) {
	S向量2 m中心 = fg中心();
	m中心 = m中心.f直角坐标(x, y);
	S向量2 m半尺寸 = fg半尺寸();
	return{m中心, m半尺寸, 0};
}
//==============================================================================
// 三角形
//==============================================================================
S三角形::S三角形() : m点() {}
S三角形::S三角形(const S向量2 &a1, const S向量2 &a2, const S向量2 &p3) {
	m点[0] = a1;
	m点[1] = a2;
	m点[2] = p3;
}
S向量2 S三角形::fg点(int i) const {
	return m点[i % 3];
}
S线段2 S三角形::fg边(int i) const {
	return{fg点(i), fg点(i + 1)};
}
float S三角形::fg边长(int i) const {
	return fg点(i).f到点距离(fg点(i + 1));
}
float S三角形::fg角r(int i) const {
	const S向量2 m点_ = fg点(i);
	return C角度计算<float>::c弧度.f夹角(m点_.f到点方向r(fg点(i + 1)), m点_.f到点方向r(fg点(i + 2)));
}
float S三角形::fg角d(int i) const {
	return fg角r(i) * c弧度到度<float>;
}
float S三角形::fg周长() const {
	return (m点[0] - m点[1]).fg大小() + (m点[0] - m点[2]).fg大小() + (m点[1] - m点[2]).fg大小();
}
float S三角形::fg面积() const {
	//行列式求面积
	return m点[0].x * m点[1].y + m点[1].x * m点[2].y + m点[2].x + m点[0].y - m点[0].y * m点[1].x - m点[1].y * m点[2].x - m点[2].y * m点[0].x;
}
S向量2 S三角形::f标准坐标(const S向量3 &p) const {
	const S向量2 v重心 = fg重心();
	S向量2 v0 = f插值<S向量2>(v重心, m点[0], p.x);
	S向量2 v1 = f插值<S向量2>(v重心, m点[1], p.y);
	S向量2 v2 = f插值<S向量2>(v重心, m点[2], p.z);
	return v0 + v1 + v2;
}
S向量3 S三角形::f重心坐标(const S向量2 &p) const {
	const S向量2 v重心 = fg重心();
	S向量3 v;
	v.x = v重心.f到点方位r(p, v重心.f到点方向r(m点[0])).x;
	v.y = v重心.f到点方位r(p, v重心.f到点方向r(m点[1])).x;
	v.z = v重心.f到点方位r(p, v重心.f到点方向r(m点[2])).x;
	return v;
}
S向量2 S三角形::fg重心() const {
	return (m点[0] + m点[1] + m点[2]) / 3;
}
S向量2 S三角形::fg垂心() const {
	const float d1 = m点[1].f点乘(m点[2]);
	const float d2 = m点[0].f点乘(m点[2]);
	const float d3 = m点[1].f点乘(m点[0]);
	const float c1 = d2 * d3;
	const float c2 = d1 * d3;
	const float c3 = d2 * d2;
	const float c = c1 + c2 + c3;
	return f标准坐标({c1 / c, c2 / c, c3 / c});
}
S向量2 S三角形::fg内心() const {
	const float l1 = fg边长(0);
	const float l2 = fg边长(1);
	const float l3 = fg边长(2);
	const float d = l1 + l2 + l3;
	return f标准坐标({l1 / d, l2 / d, l3 / d});
}
S向量2 S三角形::fg外心() const {
	const float d1 = m点[1].f点乘(m点[2]);
	const float d2 = m点[0].f点乘(m点[2]);
	const float d3 = m点[1].f点乘(m点[0]);
	const float c1 = d2 * d3;
	const float c2 = d1 * d3;
	const float c3 = d2 * d2;
	const float cc = c1 + c2 + c3;
	return f标准坐标({(c2 + c3)*cc, (c1 + c3)*cc, (c1 + c2)*cc});
}
S圆形 S三角形::fg内切圆() const {
	S圆形 v;
	v.m坐标 = fg内心();
	v.m半径 = v.m坐标.f到点距离(f标准坐标({0.5f, 0.5f, 0}));
	return v;
}
S圆形 S三角形::fg外接圆() const {
	S圆形 v;
	v.m坐标 = fg外心();
	v.m半径 = v.m坐标.f到点距离(m点[0]);
	return v;
}
//==============================================================================
// 直线方程
//==============================================================================
S直线2::S直线2() :
	a(0), b(0), c(0) {
}
S直线2::S直线2(float A, float B, float C) :
	a{A}, b{B}, c{C} {
}
S直线2 S直线2::fc点斜(const S向量2 &p, const float &k) {
	const float a = k;
	const float b = -1;
	const float c = k * p.x + p.y;
	return {a, b, c};
}
S直线2 S直线2::fc两点(const S向量2 &p1, const S向量2 &p2) {
	const float a = p2.y - p1.y;
	const float b = p1.x - p2.x;
	const float c = -p1.x * a - p2.y * b;
	return {a, b, c};
}
S直线2 S直线2::fc斜截(const float &k, const float &y) {
	const float a = k;
	const float b = -1;
	const float c = y;
	return{a, b, c};
}
S直线2 S直线2::fc截距(const float &x, const float &y) {
	const float a = x;
	const float b = y;
	const float c = -1;
	return{a, b, c};
}
S直线2 S直线2::fc一般(const float &A, const float &B, const float &C) {
	const float a = A;
	const float b = B;
	const float c = C;
	return{a, b, c};
}
S直线2 S直线2::fc点法(const S向量2 &p, const S向量2 &n) {
	const float a = n.x;
	const float b = n.y;
	const float c = -n.x * p.x - n.y * p.y;
	return{a, b, c};
}
S直线2 S直线2::fc点向r(const S向量2 &p, const float &d) {
	return fc点法(p, S向量2::fc方向r(1, d + c半π<float>));
}
//点运算
float S直线2::f到点距离(const S向量2 &p) const {
	return abs(a * p.x + b * p.y + c) / hypotf(a, b);
}
S向量2 S直线2::f对称点(const S向量2 &p) const {
	return f点关于直线翻折(p, *this);
}
S直线2 S直线2::f平移(const S向量2 &a向量) const {
	S直线2 v = *this;
	v.c -= v.a * a向量.x;
	v.c -= v.b * a向量.y;
	return v;
}
//直线运算
bool S直线2::fi有效() const {
	return a != 0 || b != 0;
}
float S直线2::fg斜率() const {
	return a / b;
}
float S直线2::f求x(const float &y) const {
	assert(a != 0);
	return (b * y + c) / -a;
}
float S直线2::f求y(const float &x) const {
	assert(b != 0);
	return (a * x + c) / -b;
}
bool S直线2::fi平行(const S直线2 &a直线) const {
	if (a == 0) return a直线.a == 0;
	else return (b / a) == (a直线.b / a直线.a);
}
float S直线2::fg方向r() const {
	return C角度计算<float>::c弧度.f取半(atan2(b, a) + c半π<float>);
}
float S直线2::fg方向d() const {
	return fg方向r() * c弧度到度<float>;
}
S向量2 S直线2::f交点(const S直线2 &a直线) const {
	const float y = (a直线.a * c - a * a直线.c) / (a直线.b * a - b * a直线.a);
	const float x = f求x(y);
	return S向量2(x, y);
}
S向量2 S直线2::fg法向量() const {
	const float m = hypotf(a, b);
	return S向量2(a / m, b / m);
}
bool S直线2::f交x轴(int a符号) const {
	if (a == 0) {
		if (a符号 == 0) {
			return true;
		} else {
			return f取符号(c) == f取符号(a符号);
		}
	} else if (b == 0) {
		return c == 0;
	} else {
		if (a符号 == 0) {
			return true;
		}
		else {
			return -c / a * f取符号(a符号) > 0;
		}
	}
}
bool S直线2::f交y轴(int a符号) const {
	if (a == 0) {
		return c == 0;
	} else if (b == 0) {
		if (a符号 == 0)
			return true;
		else
			return f取符号(c) == f取符号(a符号);
	} else {
		if (a符号 == 0)
			return true;
		else
			return -c / b * f取符号(a符号) > 0;
	}
}
bool S直线2::fi平行x轴() const {
	return b == 0;
}
bool S直线2::fi平行y轴() const {
	return a == 0;
}
bool S直线2::fi垂直x轴() const {
	return a == 0;
}
bool S直线2::fi垂直y轴() const {
	return b == 0;
}
S直线2 S直线2::fg过原点平行线() const {
	return S直线2(a, b, 0);
}
S直线2 S直线2::fg过点平行线(const S向量2 &p) const {
	const float c0 = -a * p.x - b * p.y;
	return S直线2(a, b, c0);
}
S直线2 S直线2::fg过点垂直线(const S向量2 &p) const {
	const float a0 = b;
	const float b0 = -a;
	const float c0 = -a0 * p.x - b0 * p.y;
	return S直线2(a0, b0, c0);
}
//==============================================================================
// 线段2
//==============================================================================
S线段2::S线段2(void):
	m点() {
}
S线段2::S线段2(const S向量2 &p0, const S向量2 &p1):
	m点{p0, p1} {
}
S线段2 S线段2::fc两点(const S向量2 &p0, const S向量2 &p1) {
	return {p0, p1};
}
S线段2 &S线段2::fs两点(const S向量2 &p0, const S向量2 &p1) {
	m点[0] = p0;
	m点[1] = p1;
	return *this;
}
S线段2 &S线段2::fs平移(const S向量2 &p) {
	m点[0] += p;
	m点[1] += p;
	return *this;
}
S线段2 &S线段2::fs旋转r(const float &r) {
	m点[0].fs旋转r(r);
	m点[1].fs旋转r(r);
	return *this;
}
S线段2 &S线段2::fs旋转d(const float &d) {
	m点[0].fs旋转d(d);
	m点[1].fs旋转d(d);
	return *this;
}
S线段2 S线段2::f平移(const S向量2 &p) const {
	S线段2 v = *this;
	v.m点[0] += p;
	v.m点[1] += p;
	return v;
}
S线段2 S线段2::f旋转r(const float &r) const {
	S线段2 v = *this;
	v.m点[0].fs旋转r(r);
	v.m点[1].fs旋转r(r);
	return v;
}
S线段2 S线段2::f旋转d(const float &d) const {
	S线段2 v = *this;
	v.m点[0].fs旋转d(d);
	v.m点[1].fs旋转d(d);
	return v;
}
S线段2 S线段2::f两点对调() const {
	return {m点[1], m点[0]};
}
float S线段2::fg方向r() const {
	return m点[0].f到点方向r(m点[1]);
}
float S线段2::fg方向d() const {
	return m点[0].f到点方向d(m点[1]);
}
float S线段2::fg斜率() const {
	return (m点[0].y - m点[1].y) / (m点[0].x - m点[1].x);
}
float S线段2::fg长度() const {
	return (m点[0] - m点[1]).fg大小();
}
//==============================================================================
// 射线2
//==============================================================================
S射线2::S射线2(): 
	m坐标(), m方向(0) {
}
S射线2::S射线2(const S向量2 &a坐标, float a方向): 
	m坐标(a坐标), m方向(a方向) {
}
void S射线2::fs点向(const S向量2 &a点, const S向量2 &a方向) {
	m坐标 = a点;
	m方向 = a方向.fg方向r();
}
void S射线2::fs两点(const S向量2 &a1, const S向量2 &a2) {
	m坐标 = a1;
	m方向 = a1.f到点方向r(a2);
}
float S射线2::f同向距离(const S向量2 &a点)  const {
	return f相对距离(a点).y;
}
float S射线2::f侧向距离(const S向量2 &a点)  const {
	return f相对距离(a点).x;
}
S向量2 S射线2::f相对距离(const S向量2 &a点)  const {
	return a点.f旋转r(-m方向) - m坐标;
}
S向量2 S射线2::fg点(float t) const {
	return m坐标 + S向量2::fc方向r(t, m方向);
}
//==============================================================================
// 椭圆
//==============================================================================
S椭圆::S椭圆(const S向量2 &a坐标, const S向量2 &a半径):
	m坐标(a坐标), m半径(a半径) {
}
S椭圆 S椭圆::fc圆(const S向量2 &a坐标, float a半径) {
	return {a坐标, S向量2::fc相同(a半径)};
}
float S椭圆::f计算周长(const S向量2 &a半径) {
	//拉玛努金求椭圆近似周长公式
	return cπ<float> * (3 * (a半径.x + a半径.y) - std::sqrt((3 * a半径.x + a半径.y) * (a半径.x + 3 * a半径.y)));
}
float S椭圆::f计算面积(const S向量2 &a半径) {
	return cπ<float> * a半径.x * a半径.y;
}
bool S椭圆::fi圆() const {
	return m半径.x == m半径.y;
}
S向量2 S椭圆::f取点(float t) const {
	S向量2 v;
	v.x = m半径.x * cos(t) + m坐标.x;
	v.y = m半径.y * sin(t) + m坐标.y;
	return v;
}
float S椭圆::fg周长() const {
	return S椭圆::f计算周长(m半径);
}
float S椭圆::fg面积() const {
	return S椭圆::f计算面积(m半径);
}
//==============================================================================
// 椭圆
//==============================================================================
S旋转椭圆::S旋转椭圆(): 
	m坐标(), m半径(), m方向(0) {
}
S旋转椭圆::S旋转椭圆(const S向量2 &a坐标, const S向量2 &a半径, float a方向): 
	m坐标(a坐标), m半径(a半径), m方向(a方向) {
}
S旋转椭圆 S旋转椭圆::fc圆(const S向量2 &a坐标, float a半径) {
	return {a坐标, {a半径, a半径}, 0};
}
bool S旋转椭圆::fi圆() const {
	return m半径.x == m半径.y;
}
S向量2 S旋转椭圆::f取点(float t) const {
	S向量2 v;
	v.x = m半径.x * cos(t - m方向) + m坐标.x;
	v.y = m半径.y * sin(t - m方向) + m坐标.y;
	return v;
}
float S旋转椭圆::fg周长() const {
	return S椭圆::f计算周长(m半径);
}
float S旋转椭圆::fg面积() const {
	return S椭圆::f计算面积(m半径);
}
//==============================================================================
// 圆角矩形
//==============================================================================
S圆角矩形::S圆角矩形(): 
	m坐标(), m半尺寸(), m角半径() {
}
S圆角矩形::S圆角矩形(const S向量2 &a坐标, const S向量2 &a半尺寸, const S向量2 &a角半径): 
	m坐标(a坐标), m半尺寸(a半尺寸), m角半径(a角半径) {
}
S圆角矩形 S圆角矩形::fc左上右下(float a左, float a上, float a右, float a下, S向量2 a角半径) {
	S圆角矩形 v;
	v.m坐标.x = (a左 + a右) / 2;
	v.m坐标.y = (a上 + a下) / 2;
	v.m半尺寸.x = (a右 - a左) / 2;
	v.m半尺寸.y = (a上 - a下) / 2;
	v.m角半径 = a角半径;
	return v;
}
S圆角矩形 S圆角矩形::fc坐标尺寸(const S向量2 &a坐标, const S向量2 &a全尺寸, S向量2 a角半径) {
	return {a坐标, a全尺寸 / 2, a角半径};
}
S圆角矩形 S圆角矩形::fc坐标半尺寸(const S向量2 &a坐标, const S向量2 &a半尺寸, S向量2 a角半径) {
	return {a坐标, a半尺寸, a角半径};
}
float S圆角矩形::fg周长() const {
	return S矩形::f计算周长(m半尺寸) - S矩形::f计算周长(m角半径) + S椭圆::f计算周长(m角半径);
}
float S圆角矩形::fg面积() const {
	return S矩形::f计算面积(m半尺寸) - S矩形::f计算面积(m角半径) + S椭圆::f计算面积(m角半径);
}
}	//namespace cflw::数学