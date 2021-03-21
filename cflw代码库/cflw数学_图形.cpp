#include <assert.h>
#include "cflw数学_常数.h"
#include "cflw数学_图形.h"
#include "cflw数学_向量.h"
#include "cflw数学_矩阵.h"
#include "cflw工具_运算.h"
namespace cflw::数学 {
//==============================================================================
// 函数
//==============================================================================
template<> S颜色 f插值<S颜色>(const S颜色 &a起始值, const S颜色 &a终止值, float a中间值) {
	return a起始值.f全插值(a终止值, a中间值);
}
template<> S四元数 f插值(const S四元数 &q0, const S四元数 &q1, float a插值) {
	return q0.f插值(q1, a插值);
}
template<> S颜色 f平均<S颜色>(const S颜色 &a, const S颜色 &b) {
	return S颜色(
		f平均<float>(a.r, b.r),
		f平均<float>(a.g, b.g),
		f平均<float>(a.b, b.b),
		f平均<float>(a.a, b.a)
	);
}
template<> S四元数 f平均<S四元数>(const S四元数 &a, const S四元数 &b) {
	return S四元数(
		f平均<float>(a.w, b.w),
		f平均<float>(a.x, b.x),
		f平均<float>(a.y, b.y),
		f平均<float>(a.z, b.z)
	);
}
//==============================================================================
// 颜色rgb
//==============================================================================
S颜色::operator unsigned long() {
	return (unsigned long)(a * 255) * 0x1000000 + (unsigned long)(r * 255) * 0x10000 + (unsigned long)(g * 255) * 0x100 + (unsigned long)(b * 255);
}
S颜色 S颜色::fc彩虹(float R, float A, float l, float s) {
	R = f环绕<float>(R, 0, 7);
	S颜色 c(0, 0, 0, A);
	if (R <= 2) {//红->橙->黄
		c.r = 1;
		c.g = f插值<float>(0, 1, R / 2);
	} else if (R <= 3) {//黄->绿
		c.r = f插值<float>(0, 1, 3 - R);
		c.g = 1;
	} else if (R <= 4) {//绿->青
		c.g = 1;
		c.b = f插值<float>(0, 1, R - 3);
	} else if (R <= 5) {//青->蓝
		c.g = f插值<float>(0, 1, 5 - R);
		c.b = 1;
	} else if (R <= 6) {//蓝->紫
		c.r = f插值<float>(0, 1, R - 5);
		c.b = 1;
	} else if (R <= 7) {//紫->红
		c.r = 1;
		c.b = f插值<float>(0, 1, 7 - R);
	}
	if (s != 1) {
		c.r = f插值<float>(1, c.r, s);
		c.g = f插值<float>(1, c.g, s);
		c.b = f插值<float>(1, c.b, s);
	}
	if (l != 1) {
		c.r *= l;
		c.g *= l;
		c.b *= l;
	}
	return c;
}
S颜色 S颜色::fc三基色(float R, float A, float l, float s) {
	R = f环绕<float>(R, 0, 3);
	S颜色 c(0, 0, 0, A);
	if (R <= 0.5f) {	//[0, 0.5]	红->黄
		const float v插值 = R * 2.f;
		c.r = 1;
		c.g = f插值<float>(0, 1, v插值);
	} else if (R <= 1) {	//(0.5, 1]	黄->绿
		const float v插值 = (R - 0.5f) * 2.f;
		c.r = f插值<float>(1, 0, v插值);
		c.g = 1;
	} else if (R <= 1.5) {	//(1, 1.5]	绿->青
		const float v插值 = (R - 1.f) * 2.f;
		c.g = 1;
		c.b = f插值<float>(0, 1, v插值);
	} else if (R <= 2) {	//(1.5, 2]	青->蓝
		const float v插值 = (R - 1.5f) * 2.f;
		c.g = f插值<float>(1, 0, v插值);
		c.b = 1;
	} else if (R <= 2.5f) {	//(2, 2.5]	蓝->紫
		const float v插值 = (R - 2.f) * 2.f;
		c.b = 1;
		c.r = f插值<float>(0, 1, v插值);
	} else {	//(2.5, 3)	紫->红
		const float v插值 = (R - 2.5f) * 2.f;
		c.b = f插值<float>(1, 0, v插值);
		c.r = 1;
	}
	if (s != 1) {
		c.r = f插值<float>(1, c.r, s);
		c.g = f插值<float>(1, c.g, s);
		c.b = f插值<float>(1, c.b, s);
	}
	if (l != 1) {
		c.r *= l;
		c.g *= l;
		c.b *= l;
	}
	return c;
}
S颜色 S颜色::fc黑白(float W, float A) {
	return S颜色(W, W, W, A);
}
//属性
float *S颜色::fg数据() {
	return &r;
}
const float *S颜色::fg数据() const {
	return &r;
}
//
S颜色 S颜色::f颜色分量变换(const std::function<float(float)> &af变换) const {
	const float R = af变换(r);
	const float G = af变换(g);
	const float B = af变换(b);
	return S颜色(R, G, B, a);
}
S颜色 S颜色::f颜色分量变换2(const S颜色 &a颜色, const std::function<float(float, float)> &af变换) const {
	const float R = af变换(r, a颜色.r);
	const float G = af变换(g, a颜色.b);
	const float B = af变换(b, a颜色.g);
	return S颜色(R, G, B, a);

}
S颜色 S颜色::f全分量变换(const std::function<float(float)> &af变换) const {
	const float R = af变换(r);
	const float G = af变换(g);
	const float B = af变换(b);
	const float A = af变换(a);
	return S颜色(R, G, B, A);
}
S颜色 S颜色::f全分量变换2(const S颜色 &a颜色, const std::function<float(float, float)> &af变换) const {
	const float R = af变换(r, a颜色.r);
	const float G = af变换(g, a颜色.g);
	const float B = af变换(b, a颜色.b);
	const float A = af变换(a, a颜色.a);
	return S颜色(R, G, B, A);
}
S颜色 S颜色::f混合变换2(const S颜色 &a颜色, const std::function<float(float, float)> &af颜色, const std::function<float(float, float)> &af阿尔法) const {
	const float R = af颜色(r, a颜色.r);
	const float G = af颜色(g, a颜色.g);
	const float B = af颜色(b, a颜色.b);
	const float A = af阿尔法(a, a颜色.a);
	return S颜色(R, G, B, A);
}
S颜色 S颜色::f混合变换a固定(const S颜色 &a颜色, const std::function<float(float, float)> &af颜色, float a阿尔法) const {
	const float R = af颜色(r, a颜色.r);
	const float G = af颜色(g, a颜色.g);
	const float B = af颜色(b, a颜色.b);
	return S颜色(R, G, B, a阿尔法);
}
S颜色 S颜色::f颜色校正() const {
	return f全分量变换(f单色校正);
}
S颜色 S颜色::f对比度(const float &a乘) const {
	const auto f = [a乘](float a分量)->float {
		return f单色校正(a分量 * a乘);
	};
	return f全分量变换(f);
}
S颜色 S颜色::f饱和度(const float &) const {
	return *this;
}
S颜色 S颜色::f颜色分量乘(const float &a乘) const {
	const auto f = [a乘](float a分量)->float {
		return a分量 * a乘;
	};
	return f颜色分量变换(f);
}
S颜色 S颜色::f透明度乘(const float &a乘) const {
	S颜色 v = *this;
	v.a *= a乘;
	return v;
}
S颜色 S颜色::f全插值(const S颜色 &a颜色, const float &a插值) const {
	const auto f = [a插值](float a, float b)->float {
		return f插值<float>(a, b, a插值);
	};
	return f全分量变换2(a颜色, f);
}
S颜色 S颜色::f颜色分量插值(const S颜色 &a颜色, const float &a插值) const {
	const auto f = [a插值](float a, float b)->float {
		return f插值<float>(a, b, a插值);
	};
	return f颜色分量变换2(a颜色, f);
}
S颜色 S颜色::f混合_相加(const S颜色 &a颜色) const {
	const auto f = [](float a, float b)->float {
		return f单色校正(a + b);
	};
	return f全分量变换2(a颜色, f);
}
S颜色 S颜色::f混合_相乘(const S颜色 &a颜色) const {
	const auto f = [](float a, float b)->float {
		return f单色校正(a * b);
	};
	return f全分量变换2(a颜色, f);
}
S颜色 S颜色::f混合_叠加(const S颜色 &a颜色) const {
	//正插值
	return f全插值(a颜色, a颜色.a);
}
S颜色 S颜色::f混合_叠底(const S颜色 &a颜色) const {
	//反插值
	const auto f = [v插值 = a颜色.a](float a, float b)->float {
		return f插值<float>(b, a, v插值);
	};
	return f全分量变换2(a颜色, f);
}
S颜色 S颜色::f混合_最大(const S颜色 &a颜色) const {
	//最大值
	const auto f = [](float a, float b)->float {
		return std::max<float>(a, b);
	};
	return f全分量变换2(a颜色, f);
}
S颜色 S颜色::f混合_最小(const S颜色 &a颜色) const {
	//最小值
	const auto f = [](float a, float b)->float {
		return std::min<float>(a, b);
	};
	return f全分量变换2(a颜色, f);
}
S颜色_亮色浓 S颜色::ft亮色浓() const {
	S颜色_亮色浓 v;
	v.y = 0.299f * r + 0.587f * g + 0.114f * b;
	v.u = 0.436f * (b - v.y) / (1 - 0.114f) + 0.5f;
	v.v = 0.615f * (r - v.y) / (1 - 0.299f) + 0.5f;
	return v;
}
//==============================================================================
// 颜色yuv
//==============================================================================
S颜色 S颜色_亮色浓::ft红绿蓝() const {
	S颜色 v返回;
	v返回.r = y + 1.14f * v;
	v返回.g = y - 0.39f * u - 0.58f * v;
	v返回.b = y + 2.03f * u;
	return v返回;
}
//==============================================================================
// 世界矩阵2
//==============================================================================
S世界矩阵2::S世界矩阵2(const S向量2 &a平移, const float &a旋转, const S向量2 &a缩放): 
	m平移(a平移), m旋转(a旋转), m缩放(a缩放) {
}
S矩阵2 S世界矩阵2::ft矩阵2() const {
	//没有平移
	return S矩阵2::fc旋转(m旋转) * S矩阵2::fc缩放(m缩放.x, m缩放.y);
}
//==============================================================================
// 世界矩阵3
//==============================================================================
S世界矩阵3::S世界矩阵3(const S向量3 &a平移, const S向量3 &a旋转, const S向量3 &a缩放): 
	m平移(a平移), m旋转(a旋转), m缩放(a缩放) {
}
S矩阵4 S世界矩阵3::ft矩阵4() const {
	return S矩阵4::fc平移(m平移.x, m平移.y, m平移.z) * S矩阵4::fc旋转(m旋转.x, m旋转.y, m旋转.z) * S矩阵4::fc缩放(m缩放.x, m缩放.y, m缩放.z);
}
//==============================================================================
// 相机
//==============================================================================
S相机::S相机(const S向量3 &a坐标, const S向量3 &a目标, const S向量3 &a上方): 
	m坐标(a坐标), m目标(a目标), m上方(a上方) {
}
S矩阵4 S相机::ft矩阵4l() const {
	return S矩阵4::fc看l(m坐标, m目标, m上方);
}
S矩阵4 S相机::ft矩阵4r() const {
	return S矩阵4::fc看r(m坐标, m目标, m上方);
}
//==============================================================================
// 投影
//==============================================================================
S透视投影::S透视投影(float a宽, float a高, float a视角, float a近裁剪面, float a远裁剪面):
	m视角(a视角), m宽(a宽), m高(a高), m近裁剪面(a近裁剪面), m远裁剪面(a远裁剪面) {
}
S矩阵4 S透视投影::ft矩阵4l() const {
	return S矩阵4::fc透视投影视角l(m视角, m宽 / m高, m近裁剪面, m远裁剪面);
}
S矩阵4 S透视投影::ft矩阵4r() const {
	return S矩阵4::fc透视投影视角r(m视角, m宽 / m高, m近裁剪面, m远裁剪面);
}
//==============================================================================
// 欧拉角
//==============================================================================
void S欧拉角::fs单位() {
	m头 = m侧 = m背 = 0.f;
}
void S欧拉角::f夹取() {
	m侧 = C角度计算<float>::c弧度.f夹取(m侧);
	if (m侧 < -cπ<float> / 2.f) {
		m侧 = -cπ<float> - m侧;
		m头 += cπ<float>;
		m背 += cπ<float>;
	} else if (m侧 >cπ<float> / 2.f) {
		m侧 = cπ<float> - m侧;
		m头 += cπ<float>;
		m背 += cπ<float>;
	}
	if (fabs(m侧) > cπ<float> / 2.f - 1e-4) {
		m头 += m背;
		m背 = 0.0f;
	} else {
		m背 = C角度计算<float>::c弧度.f夹取(m背);
	}
	m头 = C角度计算<float>::c弧度.f夹取(m头);
}
void S欧拉角::fs物体到惯性(const S四元数 &q) {
	float sp = -2.0f * (q.y*q.z - q.w*q.x);
	if (fabs(sp) > 0.9999f) {
		m侧 = cπ<float> / 2 * sp;
		m头 = atan2(-q.x*q.z + q.w*q.y, 0.5f - q.y*q.y - q.z*q.z);
		m背 = 0.0f;
	} else {
		m侧 = asin(sp);
		m头 = atan2(q.x*q.z + q.w*q.y, 0.5f - q.x*q.x - q.y*q.y);
		m背 = atan2(q.x*q.y + q.w*q.z, 0.5f - q.x*q.x - q.z*q.z);
	}
}
void S欧拉角::fs惯性到物体(const S四元数 &q) {
	float sp = -2.0f * (q.y*q.z + q.w*q.x);
	if (fabs(sp) > 0.9999f) {
		m侧 = cπ<float> / 2 * sp;
		m头 = atan2(-q.x*q.z - q.w*q.y, 0.5f - q.y*q.y - q.z*q.z);
		m背 = 0.0f;
	} else {
		m侧 = asin(sp);
		m头 = atan2(q.x*q.z - q.w*q.y, 0.5f - q.x*q.x - q.y*q.y);
		m背 = atan2(q.x*q.y - q.w*q.z, 0.5f - q.x*q.x - q.z*q.z);
	}
}
void S欧拉角::fs物体到世界(const S矩阵4 &m) {
	float	sp = -m.m值[3][2];
	if (fabs(sp) > 9.99999f) {
		m侧 = cπ<float> / 2 * sp;
		m头 = atan2(-m.m值[2][3], m.m值[1][1]);
		m背 = 0.0f;
	} else {
		m头 = atan2(m.m值[3][1], m.m值[3][3]);
		m侧 = asin(sp);
		m背 = atan2(m.m值[1][2], m.m值[2][2]);
	}
}
void S欧拉角::fs世界到物体(const S矩阵4 &m) {
	float	sp = -m.m值[2][3];
	if (fabs(sp) > 9.99999f) {
		m侧 = cπ<float> / 2.f * sp;
		m头 = atan2(-m.m值[3][1], m.m值[1][1]);
		m背 = 0.0f;
	} else {
		m头 = atan2(m.m值[1][3], m.m值[3][3]);
		m侧 = asin(sp);
		m背 = atan2(m.m值[2][1], m.m值[2][2]);
	}
}
//=============================================================================
// 四元数
//=============================================================================
S四元数::S四元数() : w(0), x(0), y(0), z(0) {}
S四元数::S四元数(const float &W, const float &X, const float &Y, const float &Z) : w(W), x(X), y(Y), z(Z) {}
S四元数 &S四元数::operator *=(const float &a) {
	*this = *this * a;
	return *this;
}
S四元数 &S四元数::operator *=(const t复数<float> &a) {
	*this = *this * a;
	return *this;
}
S四元数 &S四元数::operator *=(const S四元数 &a) {
	*this = *this * a;
	return *this;
}
S四元数 S四元数::operator *(const float &a) const {
	S四元数 v;
	v.w = w * a;
	v.x = x * a;
	v.y = y * a;
	v.z = z * a;
	return v;
}
S四元数 S四元数::operator *(const t复数<float>&a) const {
	S四元数 v;
	v.w = -x * a._Val[0] - y * a._Val[1];
	v.x = w * a._Val[0] + z * a._Val[1];
	v.y = w * a._Val[1] - z * a._Val[0];
	v.z = y * a._Val[0] - x * a._Val[1];
	return v;
}
S四元数 S四元数::operator *(const S四元数 &a) const {
	S四元数 v;
	v.w = w * a.w - x * a.x - y * a.y - z * a.z;
	v.x = w * a.x + x * a.w + z * a.y - y * a.z;
	v.y = w * a.y + y * a.w + x * a.z - z * a.x;
	v.z = w * a.z + z * a.w + y * a.x - x * a.y;
	return v;
}
//转换到四元数
S四元数 &S四元数::fs物体到惯性(const S欧拉角 &a) {
	const auto[sp, cp] = sincos(a.m侧 * 0.5f);
	const auto[sb, cb] = sincos(a.m背 * 0.5f);
	const auto[sh, ch] = sincos(a.m头 * 0.5f);
	w = ch * cp*cb + sh * sp*sb;
	x = ch * sp*cb + sh * cp*sb;
	y = -ch * sp*sb + sh * cp*cb;
	z = -sh * sp*cb + ch * cp*sb;
	return *this;
}
S四元数 &S四元数::fs惯性到物体(const S欧拉角 &a) {
	const auto[sp, cp] = sincos(a.m侧 * 0.5f);
	const auto[sb, cb] = sincos(a.m背 * 0.5f);
	const auto[sh, ch] = sincos(a.m头 * 0.5f);
	w = ch * cp*cb + sh * sp*sb;
	x = -ch * sp*cb - sh * cp*sb;
	y = ch * sp*sb - sh * cb*cp;
	z = sh * sp*cb - ch * cp*sb;
	return *this;
}
S四元数 S四元数::fc物体到惯性(const S欧拉角 &a) {
	const auto[sp, cp] = sincos(a.m侧 * 0.5f);
	const auto[sb, cb] = sincos(a.m背 * 0.5f);
	const auto[sh, ch] = sincos(a.m头 * 0.5f);
	S四元数 v;
	v.w = ch * cp*cb + sh * sp*sb;
	v.x = ch * sp*cb + sh * cp*sb;
	v.y = -ch * sp*sb + sh * cp*cb;
	v.z = -sh * sp*cb + ch * cp*sb;
	return v;
}
S四元数 S四元数::fc惯性到物体(const S欧拉角 &a) {
	const auto[sp, cp] = sincos(a.m侧 * 0.5f);
	const auto[sb, cb] = sincos(a.m背 * 0.5f);
	const auto[sh, ch] = sincos(a.m头 * 0.5f);
	S四元数 v;
	v.w = ch * cp*cb + sh * sp*sb;
	v.x = -ch * sp*cb - sh * cp*sb;
	v.y = ch * sp*sb - sh * cb*cp;
	v.z = sh * sp*cb - ch * cp*sb;
	return v;
}
//四元数旋转
S四元数 &S四元数::fs旋转x(float r) {
	*this *= fc旋转x(r);
	return *this;
}
S四元数 &S四元数::fs旋转y(float r) {
	*this *= fc旋转y(r);
	return *this;
}
S四元数 &S四元数::fs旋转z(float r) {
	*this *= fc旋转z(r);
	return *this;
}
S四元数 &S四元数::fs旋转(const S向量3 &v, float r) {
	*this *= fc旋转(v, r);
	return *this;
}
S四元数 S四元数::fc旋转x(float r) {
	const float 半r = r * .5f;
	return S四元数(cos(半r), sin(半r), 0, 0);
}
S四元数 S四元数::fc旋转y(float r) {
	const float 半r = r * .5f;
	return S四元数(cos(半r), 0, sin(半r), 0);
}
S四元数 S四元数::fc旋转z(float r) {
	const float 半r = r * .5f;
	return S四元数(cos(半r), 0, 0, sin(半r));
}
S四元数 S四元数::fc旋转(const S向量3 &v, float r) {
	assert(fabs(v.fg大小() - 1.0f) > .0001f);	//必须是单位向量
	const float 半r = r * .5f;
	const float s半r = sin(半r);
	return S四元数(cos(半r), v.x * s半r, v.y * s半r, v.z * s半r);
}
void S四元数::fs单位() {
	w = 1;
	x = y = z = 0;
}
float S四元数::fg旋转角() {
	return acos(w) * 2;
}
S四元数 S四元数::fg负() const {
	return S四元数(w, -x, -y, -z);
}
S四元数 &S四元数::fs负() {
	x = -x;
	y = -y;
	z = -z;
	return *this;
}
S四元数 &S四元数::fs次方(const float &a) {
	return *this = this->fg次方(a);
}
void S四元数::fs归一() {
	const float v模 = (float)sqrt(w*w + x * x + y * y + z * z);
	if (v模 > 0.0f) {
		const float m倒数 = 1.0f / v模;
		w *= m倒数;
		x *= m倒数;
		y *= m倒数;
		z *= m倒数;
	} else {
		assert(false);	//模为零
		fs单位();
	}
}
S向量3 S四元数::fg旋转轴() {
	float s = 1.0f - w * w;	//(sin(theta/2))^2
	if (s <= 0.0f)	//是否单位向量
		return S向量3(1.0f, 0.0f, 0.0f);
	float d = 1.0f / sqrt(s);	//1/sin(theta/2)
	return S向量3(x*d, y*d, z*d);
}
S四元数 S四元数::fg次方(const float &e) const {
	if (fabs(w) > .9999f)
		return *this;
	float a = acos(w);	//a = 旋转角/2
	float aa = a * e;
	S四元数 v;
	v.w = cos(aa);
	float	mult = sin(aa) / sin(a);
	v.x = x * mult;
	v.y = y * mult;
	v.z = z * mult;
	return v;
}
S四元数 S四元数::f插值(const S四元数 &q, float t) const {
	if (t <= 0.0f) return *this;
	if (t >= 1.0f) return q;
	float co = f点乘(q);
	float q1w = q.w;
	float q1x = q.x;
	float q1y = q.y;
	float q1z = q.z;
	if (co < 0.0f) {
		q1w = -q1w;
		q1x = -q1x;
		q1y = -q1y;
		q1z = -q1z;
		co = -co;
	}
	assert(co < 1.1f);
	float k0, k1;
	if (co > 0.9999f) {
		k0 = 1.0f - t;
		k1 = t;
	} else {
		float so = sqrt(1.0f - co * co);
		float o = atan2(so, co);
		float rso = 1.0f / so;
		k0 = sin((1.0f - t) * o) * rso;
		k1 = sin(t * o) * rso;
	}
	S四元数 v;
	v.x = k0 * q.x + k1 * q1x;
	v.y = k0 * q.y + k1 * q1y;
	v.z = k0 * q.z + k1 * q1z;
	v.w = k0 * q.w + k1 * q1w;
	return v;
}
float S四元数::f点乘(const S四元数 &q) const {
	return w * q.w + x * q.x + y * q.y + z * q.z;
}
//=============================================================================
//坐标计算
//=============================================================================
//坐标轴
S坐标轴::S坐标轴() :m位置(E坐标位置::e中), m方向(E坐标方向::e上) {}
S坐标轴::S坐标轴(E坐标位置 p位置, E坐标方向 p方向) : m位置(p位置), m方向(p方向) {}
const S坐标轴 c直角坐标x{E坐标位置::e中, E坐标方向::e右};
const S坐标轴 c直角坐标y{E坐标位置::e中, E坐标方向::e上};
const S坐标轴 c窗口坐标x{E坐标位置::e上, E坐标方向::e右};
const S坐标轴 c窗口坐标y{E坐标位置::e左, E坐标方向::e下};
//坐标格式
S坐标格式::S坐标格式() :x(c直角坐标x), y(c直角坐标y) {}
S坐标格式::S坐标格式(const S坐标轴 &px, const S坐标轴 &py) : x(px), y(py) {}
const S坐标格式 c直角坐标{c直角坐标x, c直角坐标y};
const S坐标格式 c窗口坐标{c窗口坐标x, c窗口坐标y};
//坐标计算
C坐标计算::C坐标计算() :m区域大小{} {}
void C坐标计算::fs大小(float px, float py) {
	m区域大小[0] = px;
	m区域大小[1] = py;
}
float C坐标计算::f计算(float pi, const S坐标轴 &pif, const S坐标轴 &pof, int i) {
	const float m转换坐标 = (pif.m方向 == pof.m方向) ? pi : -pi;
	const float m位置差 = m区域大小[i] * ((int)pof.m位置 - (int)pif.m位置) * 0.5f;
	return m转换坐标 + m位置差;
}
S向量2 C坐标计算::f计算(const S向量2 &pi, const S坐标格式 &pif, const S坐标格式 &pof) {
	S向量2 m输出;
	m输出.x = f计算(pi.x, pif.x, pof.x, 0);
	m输出.y = f计算(pi.y, pif.y, pof.y, 1);
	return m输出;
}

//命名空间结束
}	//namespace cflw::数学
