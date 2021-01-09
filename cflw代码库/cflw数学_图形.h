#pragma once
#include <functional>
#include "cflw数学.h"
#include "cflw数学_向量.h"
namespace cflw::数学 {
//=============================================================================
// 声明
//=============================================================================
//其它文件
struct S旋转矩形;
struct S矩阵2;
struct S矩阵4;
template<typename t> t f插值(const t&起始值, const t&终止值, float 中间值);
//本文件
struct S颜色;
struct S颜色_亮色浓;
struct S四元数;
struct S欧拉角;
template<> S颜色 f插值<S颜色>(const S颜色 &起始值, const S颜色 &终止值, float 中间值);
template<> S四元数 f插值<S四元数>(const S四元数 &, const S四元数 &, float);
template<> S颜色 f平均<S颜色>(const S颜色 &, const S颜色 &);
template<> S四元数 f平均<S四元数>(const S四元数 &, const S四元数 &);
constexpr float f单色校正(float a值) {
	if (a值 >= 1) {
		return 1;
	} else if (a值 <= 0) {
		return 0;
	} else {
		return a值;
	}
}
//=============================================================================
// 颜色
//=============================================================================
//红绿蓝颜色系统(rgb)
struct S颜色 {
	enum E颜色值 : unsigned int {
		e白 = 0xffffffff,
		e黑 = 0x000000ff,
		e红 = 0xff0000ff,
		e橙 = 0xff8000ff, 
		e黄 = 0xffff00ff, 
		e绿 = 0x00ff00ff, 
		e青 = 0x00ffffff, 
		e蓝 = 0x0000ffff, 
		e紫 = 0xff00ffff, 
		e粉 = 0xff8080ff
	};
	enum E颜色值提取 : unsigned int {
		e提取阿,
		e提取蓝,
		e提取绿,
		e提取红
	};
	//分量
	float r = 0, g = 0, b = 0, a = 0;
	//常量
	static const S颜色 c白, c黑, c灰, c红, c橙, c黄, c绿, c青, c蓝, c紫, c粉;
	//构造函数
	constexpr S颜色() = default;
	constexpr S颜色(E颜色值 a颜色) : 
		r(f颜色值提取_红(a颜色)), g(f颜色值提取_绿(a颜色)), b(f颜色值提取_蓝(a颜色)), a(f颜色值提取_阿(a颜色)) {
	}
	constexpr S颜色(float R, float G, float B, float A = 1): 
		r(R), g(G), b(B), a(A) {
	}
	operator unsigned long();
	static S颜色 fc彩虹(float, float A = 1, float 亮度 = 1, float 饱和度 = 1);	//0~6:红橙黄绿青蓝紫,循环
	static S颜色 fc三基色(float, float A = 1, float 亮度 = 1, float 饱和度 = 1);	//0~2:红绿蓝,循环
	static S颜色 fc黑白(float, float A = 1);
	static constexpr float f颜色值提取(E颜色值 a值, E颜色值提取 a提取) {
		return static_cast<float>((static_cast<unsigned int>(a值) >> (static_cast<unsigned int>(a提取) * 8)) % 0x100) / 255.f;
	}
	static constexpr float f颜色值提取_红(E颜色值 a颜色) {
		return f颜色值提取(a颜色, e提取红);
	}
	static constexpr float f颜色值提取_绿(E颜色值 a颜色) {
		return f颜色值提取(a颜色, e提取绿);
	}
	static constexpr float f颜色值提取_蓝(E颜色值 a颜色) {
		return f颜色值提取(a颜色, e提取蓝);
	}
	static constexpr float f颜色值提取_阿(E颜色值 a颜色) {
		return f颜色值提取(a颜色, e提取阿);
	}
	//属性
	float *fg数据();
	const float *fg数据() const;
	//通用计算
	S颜色 f颜色分量变换(const std::function<float(float)> &) const;
	S颜色 f颜色分量变换2(const S颜色 &, const std::function<float(float, float)> &) const;
	S颜色 f全分量变换(const std::function<float(float)> &) const;
	S颜色 f全分量变换2(const S颜色 &, const std::function<float(float, float)> &) const;
	S颜色 f混合变换2(const S颜色 &, const std::function<float(float, float)> &, const std::function<float(float, float)> &) const;
	S颜色 f混合变换a固定(const S颜色 &, const std::function<float(float, float)> &, float) const;
	//具体计算
	S颜色 f颜色校正() const;
	S颜色 f对比度(const float &) const;
	S颜色 f饱和度(const float &) const;
	S颜色 f颜色分量乘(const float &) const;
	S颜色 f透明度乘(const float &) const;
	S颜色 f全插值(const S颜色 &, const float &) const;
	S颜色 f颜色分量插值(const S颜色 &, const float &) const;
	S颜色 f混合_相加(const S颜色 &) const;
	S颜色 f混合_相乘(const S颜色 &) const;
	S颜色 f混合_叠加(const S颜色 &) const;
	S颜色 f混合_叠底(const S颜色 &) const;
	S颜色 f混合_最大(const S颜色 &) const;
	S颜色 f混合_最小(const S颜色 &) const;
	S颜色_亮色浓 ft亮色浓() const;
};
constexpr inline S颜色 S颜色::c白{ 1, 1, 1, 1 };
constexpr inline S颜色 S颜色::c黑{ 0, 0, 0, 1 };
constexpr inline S颜色 S颜色::c红{ 1, 0, 0, 1 };
constexpr inline S颜色 S颜色::c橙{ 1, 0.5f, 0, 1 };
constexpr inline S颜色 S颜色::c黄{ 1, 1, 0, 1 };
constexpr inline S颜色 S颜色::c绿{ 0, 1, 0, 1 };
constexpr inline S颜色 S颜色::c青{ 0, 1, 1, 1 };
constexpr inline S颜色 S颜色::c蓝{ 0, 0, 1, 1 };
constexpr inline S颜色 S颜色::c紫{ 1, 0, 1, 1 };
constexpr inline S颜色 S颜色::c粉{ 1, 0.5f, 0.5f, 1 };
constexpr inline S颜色 S颜色::c灰{ 0.5f, 0.5f, 0.5f, 1 };
//亮度,色度,浓度(yuv)
struct S颜色_亮色浓 {
	float y, u, v;
	S颜色 ft红绿蓝() const;
};
//=============================================================================
// 光
//=============================================================================
struct S光 {
	enum E光源类型 {
		e点光,		//从一点向四周发散的光
		e方向光,	//平行地沿某一方向传播的光
		e聚光灯	//与手电筒类似的光
	}v光源类型;
	S颜色 m漫射色;
	S颜色 m镜面色;
	S颜色 m环境色;
	S向量3 m位置;	//对方向光无效
	S向量3 m方向;	//对点光无效
	float m范围;		//光线最远能达到的路程
	float m范围衰减度;	//仅用于聚光灯
	float m距离衰减度[3];	//仅用于点光源聚光灯
	float m内圆锥角;	//仅用于聚光灯
	float m外圆锥角;	//仅用于聚光灯
	//构造函数
	S光();
};
//=============================================================================
// 材质
//=============================================================================
struct S材质 {
	S颜色 m漫射色;
	S颜色 m反射色;
	S颜色 m镜面色;
	S颜色 m发光色;
	float m锐度;
	S材质();
};
//=============================================================================
// 各种矩阵
//=============================================================================
struct S世界矩阵2 {
	S向量2 m平移 = S向量2::c零;
	float m旋转 = 0;
	S向量2 m缩放 = S向量2::c一;
	S世界矩阵2() = default;
	S世界矩阵2(const S向量2 &, const float &, const S向量2 &);
	S矩阵2 ft矩阵2() const;
};
struct S世界矩阵3 {
	S向量3 m平移 = S向量3::c零;
	S向量3 m旋转 = S向量3::c零;
	S向量3 m缩放 = S向量3::c一;
	S世界矩阵3() = default;
	S世界矩阵3(const S向量3 &, const S向量3 &, const S向量3 &);
	S矩阵4 ft矩阵4() const;
};
struct S相机 {
	S向量3 m坐标 = S向量3::c零;
	S向量3 m目标 = S向量3::c零;
	S向量3 m上方 = S向量3(0, 1, 0);
	S相机() = default;
	S相机(const S向量3 &, const S向量3 &, const S向量3 &);
	S矩阵4 ft矩阵4l() const;
	S矩阵4 ft矩阵4r() const;
};
struct S透视投影 {
	static constexpr float c视角 = 数学::c半π<float>;
	float m视角 = c视角;
	float m宽 = 640, m高 = 480;
	float m近裁剪面 = 1, m远裁剪面 = 100;
	S透视投影() = default;
	S透视投影(float 宽, float 高, float 视角 = c视角, float 近裁剪面 = 0.01f, float 远裁剪面 = 100.f);
	S矩阵4 ft矩阵4l() const;
	S矩阵4 ft矩阵4r() const;
};
struct S视口 {
	S向量2 m左上;
	S向量2 m右下;
	float m最小深度, m最大深度;
	S视口();
	S视口(const S旋转矩形 &);
};
//=============================================================================
// 欧拉角&四元数
//=============================================================================
struct S欧拉角 {
	float m头, m侧, m背;
	S欧拉角();
	S欧拉角(float 头, float 侧, float 背);
	void fs单位();
	void f夹取();
	void fs物体到惯性(const S四元数 &);
	void fs惯性到物体(const S四元数 &);
	void fs物体到世界(const S矩阵4 &);
	void fs世界到物体(const S矩阵4 &);
};
struct S四元数 {
	float w, x, y, z;
	S四元数();
	S四元数(const float &, const float &, const float &, const float &);
	//
	S四元数 &operator *=(const float &);
	S四元数 &operator *=(const t复数<float>&);
	S四元数 &operator *=(const S四元数 &);
	//
	S四元数 operator *(const float &) const;
	S四元数 operator *(const t复数<float>&) const;
	S四元数 operator *(const S四元数 &) const;
	//转换
	S四元数 &fs物体到惯性(const S欧拉角 &);
	S四元数 &fs惯性到物体(const S欧拉角 &);
	static S四元数 fc物体到惯性(const S欧拉角 &);
	static S四元数 fc惯性到物体(const S欧拉角 &);
	//旋转
	S四元数 &fs旋转x(float);
	S四元数 &fs旋转y(float);
	S四元数 &fs旋转z(float);
	S四元数 &fs旋转(const S向量3 &, float);	//以向量为轴旋转
	static S四元数 fc旋转x(float);
	static S四元数 fc旋转y(float);
	static S四元数 fc旋转z(float);
	static S四元数 fc旋转(const S向量3 &, float);
	//杂项操作
	void fs单位();	//设置为单位四元数
	void fs归一();	//模=1
	float fg旋转角();	//取旋转角度
	S向量3 fg旋转轴();
	S四元数 fg负() const;
	S四元数 &fs负();
	S四元数 fg次方(const float &) const;
	S四元数 &fs次方(const float &);
	S四元数 f插值(const S四元数 &, float) const;
	float f点乘(const S四元数 &) const;
};
//=============================================================================
// 万能坐标计算
//=============================================================================
//坐标位置
enum class E坐标位置 {
	e左,
	e上 = e左,
	e中,
	e右,
	e下 = e右
};
//坐标方向
enum class E坐标方向 {
	e右,
	e上 = e右,
	e左,
	e下 = e左
};
//坐标轴
struct S坐标轴 {
	E坐标位置 m位置;
	E坐标方向 m方向;
	S坐标轴();
	S坐标轴(E坐标位置, E坐标方向);
};
extern const S坐标轴 c直角坐标x;
extern const S坐标轴 c直角坐标y;
extern const S坐标轴 c窗口坐标x;
extern const S坐标轴 c窗口坐标y;
//坐标格式
struct S坐标格式 {
	S坐标轴 x, y;
	S坐标格式();
	S坐标格式(const S坐标轴 &, const S坐标轴 &);
};
extern const S坐标格式 c直角坐标;
extern const S坐标格式 c窗口坐标;
//坐标计算
class C坐标计算 {
public:
	float m区域大小[2];
	C坐标计算();
	void fs大小(float, float);
	float f计算(float, const S坐标轴 &, const S坐标轴 &, int);
	S向量2 f计算(const S向量2 &, const S坐标格式 &, const S坐标格式 &);
};
}	//namespace cflw::数学