#include "cflw数学_矩阵.h"
#include "cflw数学_向量.h"
#include "cflw数学_函数方程.h"
namespace cflw::数学 {
//矩阵类
void C矩阵::f空矩阵_(float *a输出, int a行, int a列) {
	for (int 行 = 0; 行 != a行; ++行) {
		for (int 列 = 0; 列 != a列; ++列) {
			a输出[行 * a列 + 列] = 0;
		}
	}
}
void C矩阵::f矩阵相乘_(float *a输出, const float *a矩阵0, const float *a矩阵1, int ①, int ②, int ③) {
	float *v = new float[①*③];
	memset(v, 0, sizeof(float)*①*③);
	for (int 列 = 0; 列 != ③; ++列) {
		for (int 行 = 0; 行 != ①; ++行) {
			for (int i = 0; i != ②; ++i) {
				v[行 * ② + 列] += a矩阵0[行 * ② + i] * a矩阵1[i * ③ + 列];
			}
		}
	}
	memcpy(a输出, v, 4 * ①*③);
	delete[] v;
}
void C矩阵::f单位矩阵_(float *a参数, int a参数数) {
	for (int 行 = 0; 行 != a参数数; ++行)
		for (int 列 = 0; 列 != a参数数; ++列)
			a参数[行 * a参数数 + 列] = (行 == 列) ? 1.f : 0.f;
}
void C矩阵::f矩阵相加_(float *a输出, const float *a矩阵0, const float *a矩阵1, int ni, int nj) {
	float *v = new float[ni*nj];
	memset(v, 0, sizeof(float)*ni*nj);
	for (int i = 0; i != ni; ++i)
		for (int j = 0; j != nj; ++j) {
			const int n = i * nj + j;
			v[n] = a矩阵0[n] + a矩阵1[n];
		}
	memcpy(a输出, v, 4 * ni*nj);
	delete[] v;
}
void C矩阵::f矩阵转置_(float *a输出, const float *a输入, int ni, int nj) {
	float *v = new float[ni*nj];
	memset(v, 0, sizeof(float)*ni*nj);
	for (int i = 0; i != ni; ++i)
		for (int j = 0; j != nj; ++j)
			v[i*ni + j] = a输入[j*nj + i];
	memcpy(a输出, v, 4 * ni*nj);
	delete[] v;
}
float C矩阵::f算行列式_(float *a参数, int n) {
	float s0 = 0;
	for (int i = 0; i != n; ++i) {
		float s1 = 1;
		for (int j = 0; j != n; ++j) {
			s1 *= a参数[i*n + (i + j) % n];
		}
		s0 += s1;
	}
	for (int i = 0; i != n; ++i) {
		float s1 = 1;
		for (int j = 0; j != n; ++j) {
			s1 *= a参数[i*n + (i - j) % n];
		}
		s0 -= s1;
	}
	return s0;
}
//二阶矩阵
S矩阵2 &S矩阵2::operator +=(const S矩阵2 &a) {
	C矩阵::f矩阵相加((t基类&)(*this), (const t基类&)(*this), (const t基类&)a);
	return *this;
}
S矩阵2 &S矩阵2::operator *=(const S矩阵2 &a) {
	C矩阵::f矩阵相乘((t基类&)(*this), (const t基类&)(*this), (const t基类&)a);
	return *this;
}
S矩阵2 S矩阵2::operator +(const S矩阵2 &a) const {
	S矩阵2 v;
	C矩阵::f矩阵相加((t基类&)v, (const t基类&)(*this), (const t基类&)a);
	return v;
}
S矩阵2 S矩阵2::operator *(const S矩阵2 &a) const {
	S矩阵2 v;
	C矩阵::f矩阵相乘((t基类&)v, (const t基类&)(*this), (const t基类&)a);
	return v;
}
S矩阵2 S矩阵2::fc单位() {
	S矩阵2 v;
	v.m值[0][0] = 1;	v.m值[0][1] = 0;
	v.m值[1][0] = 0;	v.m值[1][1] = 1;
	return v;
}
S矩阵2 S矩阵2::fc旋转(const float &t) {
	S矩阵2 v;
	const float s = sin(t);
	const float c = cos(t);
	v.m值[0][0] = c;	v.m值[0][1] = -s;
	v.m值[1][0] = s;	v.m值[1][1] = c;
	return v;
}
S矩阵2 S矩阵2::fc缩放(const float &x, const float &y) {
	S矩阵2 v;
	v.m值[0][0] = x;	v.m值[0][1] = 0;
	v.m值[1][0] = 0;	v.m值[1][1] = y;
	return v;
}
S矩阵2 S矩阵2::fc切变(const float &x, const float &y) {
	S矩阵2 v;
	v.m值[0][0] = 1;	v.m值[0][1] = x;
	v.m值[1][0] = y;	v.m值[1][1] = 1;
	return v;
}
S矩阵2 S矩阵2::fc翻转(const float &x, const float &y) {
	S矩阵2 v;
	v.m值[0][0] = sin(y);	v.m值[0][1] = 0;
	v.m值[1][0] = 0;		v.m值[1][1] = sin(x);
	return v;
}
S矩阵2 S矩阵2::fc复数(const t复数<float> &cx) {
	const float r = cx.real();
	const float i = cx.imag();
	const float t = atan2(i, r);
	const float s = hypot(r, i);
	return fc旋转(t) * fc缩放(s, s);
}
//四阶矩阵
const S矩阵4 S矩阵4::c单位 = S矩阵4::fc单位();
S矩阵4::S矩阵4() {
	memset(this, 0, sizeof(S矩阵4));
}
S矩阵4 &S矩阵4::operator +=(const S矩阵4 &a) {
	C矩阵::f矩阵相加((t基类&)(*this), (const t基类&)(*this), (const t基类&)a);
	return *this;
}
S矩阵4 &S矩阵4::operator *=(const S矩阵4 &a) {
	C矩阵::f矩阵相乘((t基类&)(*this), (const t基类&)(*this), (const t基类&)a);
	return *this;
}
S矩阵4 S矩阵4::operator +(const S矩阵4 &a) const {
	S矩阵4 v;
	C矩阵::f矩阵相加((t基类&)v, (const t基类&)(*this), (const t基类&)a);
	return v;
}
S矩阵4 S矩阵4::operator *(const S矩阵4 &a) const {
	S矩阵4 v;
	C矩阵::f矩阵相乘((t基类&)v, (const t基类&)(*this), (const t基类&)a);
	return v;
}
S矩阵4 S矩阵4::fc单位() {
	S矩阵4 v;
	v.m值[0][0] = 1;	v.m值[0][1] = 0;	v.m值[0][2] = 0;	v.m值[0][3] = 0;
	v.m值[1][0] = 0;	v.m值[1][1] = 1;	v.m值[1][2] = 0;	v.m值[1][3] = 0;
	v.m值[2][0] = 0;	v.m值[2][1] = 0;	v.m值[2][2] = 1;	v.m值[2][3] = 0;
	v.m值[3][0] = 0;	v.m值[3][1] = 0;	v.m值[3][2] = 0;	v.m值[3][3] = 1;
	return v;
}
S矩阵4 S矩阵4::fc绕x旋转(const float &t) {
	S矩阵4 v;
	const float s = sin(t);
	const float c = cos(t);
	v.m值[0][0] = 1;	v.m值[0][1] = 0;	v.m值[0][2] = 0;	v.m值[0][3] = 0;
	v.m值[1][0] = 0;	v.m值[1][1] = c;	v.m值[1][2] = -s;	v.m值[1][3] = 0;
	v.m值[2][0] = 0;	v.m值[2][1] = s;	v.m值[2][2] = c;	v.m值[2][3] = 0;
	v.m值[3][0] = 0;	v.m值[3][1] = 0;	v.m值[3][2] = 0;	v.m值[3][3] = 1;
	return v;
}
S矩阵4 S矩阵4::fc绕y旋转(const float &t) {
	S矩阵4 v;
	const float s = sin(t);
	const float c = cos(t);
	v.m值[0][0] = c;	v.m值[0][1] = 0;	v.m值[0][2] = s;	v.m值[0][3] = 0;
	v.m值[1][0] = 0;	v.m值[1][1] = 1;	v.m值[1][2] = 0;	v.m值[1][3] = 0;
	v.m值[2][0] = -s;	v.m值[2][1] = 0;	v.m值[2][2] = c;	v.m值[2][3] = 0;
	v.m值[3][0] = 0;	v.m值[3][1] = 0;	v.m值[3][2] = 0;	v.m值[3][3] = 1;
	return v;
}
S矩阵4 S矩阵4::fc绕z旋转(const float &t) {
	S矩阵4 v;
	const float s = sin(t);
	const float c = cos(t);
	v.m值[0][0] = c;	v.m值[0][1] = -s;	v.m值[0][2] = 0;	v.m值[0][3] = 0;
	v.m值[1][0] = s;	v.m值[1][1] = c;	v.m值[1][2] = 0;	v.m值[1][3] = 0;
	v.m值[2][0] = 0;	v.m值[2][1] = 0;	v.m值[2][2] = 1;	v.m值[2][3] = 0;
	v.m值[3][0] = 0;	v.m值[3][1] = 0;	v.m值[3][2] = 0;	v.m值[3][3] = 1;
	return v;
}
S矩阵4 S矩阵4::fc旋转(const float &x, const float &y, const float &z) {
	S矩阵4 v;
	const float sx = sin(x);
	const float cx = cos(x);
	const float sy = sin(y);
	const float cy = cos(y);
	const float sz = sin(z);
	const float cz = cos(z);
	v.m值[0][0] = cy * cz;			v.m值[0][1] = -cy * sz;			v.m值[0][2] = sy;		v.m值[0][3] = 0;
	v.m值[1][0] = cx * sz + cz * sx*sy;	v.m值[1][1] = cx * cz - sx * sy*sz;	v.m值[1][2] = -cy * sx;	v.m值[1][3] = 0;
	v.m值[2][0] = sx * sz - cx * cz*sy;	v.m值[2][1] = cz * sx + cx * sy*sz;	v.m值[2][2] = cx * cy;	v.m值[2][3] = 0;
	v.m值[3][0] = 0;				v.m值[3][1] = 0;				v.m值[3][2] = 0;		v.m值[3][3] = 1;
	return v;
}
S矩阵4 S矩阵4::fc看l(const S向量3 &e, const S向量3 &a, const S向量3 &u) {
	S矩阵4 v;
	const S向量3 z = (a - e).fg归一();	//前
	const S向量3 x = u.f叉乘(z).fg归一();	//右
	const S向量3 y = z.f叉乘(x);	//上
	v.m值[0][0] = x.x;	v.m值[0][1] = x.y;	v.m值[0][2] = x.z;	v.m值[0][3] = -x.f点乘(e);
	v.m值[1][0] = y.x;	v.m值[1][1] = y.y;	v.m值[1][2] = y.z;	v.m值[1][3] = -y.f点乘(e);
	v.m值[2][0] = z.x;	v.m值[2][1] = z.y;	v.m值[2][2] = z.z;	v.m值[2][3] = -z.f点乘(e);
	v.m值[3][0] = 0;	v.m值[3][1] = 0;	v.m值[3][2] = 0;	v.m值[3][3] = 1;
	return v;
}
S矩阵4 S矩阵4::fc看r(const S向量3 &e, const S向量3 &a, const S向量3 &u) {
	S矩阵4 v;
	const S向量3 z = (e - a).fg归一();
	const S向量3 x = u.f叉乘(z).fg归一();
	const S向量3 y = z.f叉乘(x);
	v.m值[0][0] = x.x;	v.m值[0][1] = x.y;	v.m值[0][2] = x.z;	v.m值[0][3] = -x.f点乘(e);
	v.m值[1][0] = y.x;	v.m值[1][1] = y.y;	v.m值[1][2] = y.z;	v.m值[1][3] = -y.f点乘(e);
	v.m值[2][0] = z.x;	v.m值[2][1] = z.y;	v.m值[2][2] = z.z;	v.m值[2][3] = -z.f点乘(e);
	v.m值[3][0] = 0;	v.m值[3][1] = 0;	v.m值[3][2] = 0;	v.m值[3][3] = 1;
	return v;
}
S矩阵4 S矩阵4::fc看向l(const S向量3 &e, const S向量3 &f, const S向量3 &u) {
	S矩阵4 v;
	return v;
}
S矩阵4 S矩阵4::fc看向r(const S向量3 &e, const S向量3 &f, const S向量3 &u) {
	S矩阵4 v;
	return v;
}
S矩阵4 S矩阵4::fc透视投影视角l(const float &f, const float &a, const float &zn, const float &zf) {
	S矩阵4 v;
	const float y = 1.0f / tan(f * 0.5f);
	const float x = y / a;
	const float q1 = zf / (zf - zn);
	const float q2 = -zn * q1;
	v.m值[0][0] = x;	v.m值[0][1] = 0;	v.m值[0][2] = 0;		v.m值[0][3] = 0;
	v.m值[1][0] = 0;	v.m值[1][1] = y;	v.m值[1][2] = 0;		v.m值[1][3] = 0;
	v.m值[2][0] = 0;	v.m值[2][1] = 0;	v.m值[2][2] = q1;		v.m值[2][3] = q2;
	v.m值[3][0] = 0;	v.m值[3][1] = 0;	v.m值[3][2] = 1;		v.m值[3][3] = 0;
	return v;
}
S矩阵4 S矩阵4::fc透视投影视角r(const float &f, const float &a, const float &zn, const float &zf) {
	S矩阵4 v;
	const float y = 1.0f / tan(f * 0.5f);
	const float x = y / a;
	const float q1 = zn / (zf - zn);
	const float q2 = zf * q1;
	v.m值[0][0] = x;	v.m值[0][1] = 0;	v.m值[0][2] = 0;		v.m值[0][3] = 0;
	v.m值[1][0] = 0;	v.m值[1][1] = y;	v.m值[1][2] = 0;		v.m值[1][3] = 0;
	v.m值[2][0] = 0;	v.m值[2][1] = 0;	v.m值[2][2] = q1;		v.m值[2][3] = q2;
	v.m值[3][0] = 0;	v.m值[3][1] = 0;	v.m值[3][2] = -1;		v.m值[3][3] = 0;
	return v;
}
S矩阵4 S矩阵4::fc透视投影中心l(float w, float h, float zn, float zf) {
	S矩阵4 v;
	const float q1 = zf / (zf - zn);
	const float q2 = -zn * q1;
	v.m值[0][0] = 2 * zn / w;	v.m值[0][1] = 0;			v.m值[0][2] = 0;		v.m值[0][3] = 0;
	v.m值[1][0] = 0;			v.m值[1][1] = 2 * zn / h;	v.m值[1][2] = 0;		v.m值[1][3] = 0;
	v.m值[2][0] = 0;			v.m值[2][1] = 0;			v.m值[2][2] = q1;		v.m值[2][3] = q2;
	v.m值[3][0] = 0;			v.m值[3][1] = 0;			v.m值[3][2] = 1;		v.m值[3][3] = 0;
	return v;
}
S矩阵4 S矩阵4::fc透视投影中心r(float w, float h, float zn, float zf) {
	S矩阵4 v;
	const float q1 = zf / (zn - zf);
	const float q2 = zn * q1;
	v.m值[0][0] = 2 * zn / w;	v.m值[0][1] = 0;			v.m值[0][2] = 0;	v.m值[0][3] = 0;
	v.m值[1][0] = 0;			v.m值[1][1] = 2 * zn / h;	v.m值[1][2] = 0;	v.m值[1][3] = 0;
	v.m值[2][0] = 0;			v.m值[2][1] = 0;			v.m值[2][2] = q1;	v.m值[2][3] = q2;
	v.m值[3][0] = 0;			v.m值[3][1] = 0;			v.m值[3][2] = -1;	v.m值[3][3] = 0;
	return v;
}
S矩阵4 S矩阵4::fc透视投影自定义l(float l, float r, float b, float t, float zn, float zf) {
	S矩阵4 v;
	const float w = r - l;
	const float h = t - b;
	const float q1 = zf / (zf - zn);
	const float q2 = -zn * q1;
	v.m值[0][0] = 2 * zn / w;	v.m值[0][1] = 0;			v.m值[0][2] = -(l + r) / w;	v.m值[0][3] = 0;
	v.m值[1][0] = 0;			v.m值[1][1] = 2 * zn / h;	v.m值[1][2] = -(t + b) / h;	v.m值[1][3] = 0;
	v.m值[2][0] = 0;			v.m值[2][1] = 0;			v.m值[2][2] = q1;			v.m值[2][3] = q2;
	v.m值[3][0] = 0;			v.m值[3][1] = 0;			v.m值[3][2] = 1;			v.m值[3][3] = 0;
	return v;
}
S矩阵4 S矩阵4::fc透视投影自定义r(float l, float r, float b, float t, float zn, float zf) {
	S矩阵4 v;
	const float q1 = zf / (zn - zf);
	const float q2 = zn * q1;
	const float w = r - l;
	const float h = t - b;
	v.m值[0][0] = 2 * zn / w;	v.m值[0][1] = 0;			v.m值[0][2] = (l + r) / w;	v.m值[0][3] = 0;
	v.m值[1][0] = 0;			v.m值[1][1] = 2 * zn / h;	v.m值[1][2] = (t + b) / h;	v.m值[1][3] = 0;
	v.m值[2][0] = 0;			v.m值[2][1] = 0;			v.m值[2][2] = q1;			v.m值[2][3] = q2;
	v.m值[3][0] = 0;			v.m值[3][1] = 0;			v.m值[3][2] = -1;			v.m值[3][3] = 0;
	return v;
}
S矩阵4 S矩阵4::fc转置(const S矩阵4 &a) {
	S矩阵4 v;
	v.m值[0][0] = a.m值[0][0];	v.m值[0][1] = a.m值[1][0];	v.m值[0][2] = a.m值[2][0];	v.m值[0][3] = a.m值[3][0];
	v.m值[1][0] = a.m值[0][1];	v.m值[1][1] = a.m值[1][1];	v.m值[1][2] = a.m值[2][1];	v.m值[1][3] = a.m值[3][1];
	v.m值[2][0] = a.m值[0][2];	v.m值[2][1] = a.m值[1][2];	v.m值[2][2] = a.m值[2][2];	v.m值[2][3] = a.m值[3][2];
	v.m值[3][0] = a.m值[0][3];	v.m值[3][1] = a.m值[1][3];	v.m值[3][2] = a.m值[2][3];	v.m值[3][3] = a.m值[3][3];
	return v;
}
S矩阵4 S矩阵4::fc平移(const float &x, const float &y, const float &z) {
	S矩阵4 v;
	v.m值[0][0] = 1;	v.m值[0][1] = 0;	v.m值[0][2] = 0;	v.m值[0][3] = x;
	v.m值[1][0] = 0;	v.m值[1][1] = 1;	v.m值[1][2] = 0;	v.m值[1][3] = y;
	v.m值[2][0] = 0;	v.m值[2][1] = 0;	v.m值[2][2] = 1;	v.m值[2][3] = z;
	v.m值[3][0] = 0;	v.m值[3][1] = 0;	v.m值[3][2] = 0;	v.m值[3][3] = 1;
	return v;
}
S矩阵4 S矩阵4::fc缩放(const float &x, const float &y, const float &z) {
	S矩阵4 v;
	v.m值[0][0] = x;	v.m值[0][1] = 0;	v.m值[0][2] = 0;	v.m值[0][3] = 0;
	v.m值[1][0] = 0;	v.m值[1][1] = y;	v.m值[1][2] = 0;	v.m值[1][3] = 0;
	v.m值[2][0] = 0;	v.m值[2][1] = 0;	v.m值[2][2] = z;	v.m值[2][3] = 0;
	v.m值[3][0] = 0;	v.m值[3][1] = 0;	v.m值[3][2] = 0;	v.m值[3][3] = 1;
	return v;
}
S矩阵4 S矩阵4::fc镜面反射(const S平面方程 &a平面) {
	S矩阵4 v;
	v.m值[0][0] = 1-2*a平面.a*a平面.a;	v.m值[0][1] = -2*a平面.a*a平面.b;	v.m值[0][2] = -2*a平面.a*a平面.c;	v.m值[0][3] = 0;
	v.m值[1][0] = -2*a平面.b*a平面.a;	v.m值[1][1] = 1-2*a平面.b*a平面.b;	v.m值[1][2] = -2*a平面.b*a平面.c;	v.m值[1][3] = 0;
	v.m值[2][0] = -2*a平面.c*a平面.a;	v.m值[2][1] = -2*a平面.c*a平面.b;	v.m值[2][2] = 1-2*a平面.c*a平面.c;	v.m值[2][3] = 0;
	v.m值[3][0] = -2*a平面.d*a平面.a;	v.m值[3][1] = -2*a平面.d*a平面.b;	v.m值[3][2] = -2*a平面.d*a平面.c;	v.m值[3][3] = 1;
	return v;
}
S矩阵4 S矩阵4::fc阴影(const S平面方程 &a平面, const S向量4 &l) {
	S矩阵4 v;
	const float nl = a平面.fg法().f点乘(l.ft向量3());
	const float nld = nl - a平面.d;
	v.m值[0][0] = nld-a平面.a*l.x;	v.m值[0][1] = -l.y*a平面.a;		v.m值[0][2] = -l.z*a平面.a;		v.m值[0][3] = -a平面.a;
	v.m值[1][0] = -l.x*a平面.b;		v.m值[1][1] = nld-l.y*a平面.b;	v.m值[1][2] = -l.z*a平面.b;		v.m值[1][3] = -a平面.b;
	v.m值[2][0] = -l.x*a平面.c;		v.m值[2][1] = -l.y*a平面.c;		v.m值[2][2] = nld-l.z*a平面.c;	v.m值[2][3] = -a平面.c;
	v.m值[3][0] = -l.x*a平面.d;		v.m值[3][1] = -l.y*a平面.d;		v.m值[3][2] = -l.z*a平面.d;		v.m值[3][3] = nl;
	return v;
}

}	//namespace cflw::数学