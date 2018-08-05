#include "cflw数学_矩阵.h"
#include "cflw数学_向量.h"
#include "cflw数学_函数方程.h"
namespace cflw::数学 {
//矩阵类
void C矩阵::f空矩阵_(float *p, int p行, int p列) {
	for (int 行 = 0; 行 != p行; ++行)
		for (int 列 = 0; 列 != p列; ++列)
			p[行 * p列 + 列] = 0;
}
void C矩阵::f矩阵相乘_(float *p出, const float *p一, const float *p二, int ①, int ②, int ③) {
	float *v = new float[①*③];
	memset(v, 0, sizeof(float)*①*③);
	for (int 列 = 0; 列 != ③; ++列)
		for (int 行 = 0; 行 != ①; ++行)
			for (int i = 0; i != ②; ++i)
				v[行 * ② + 列] += p一[行 * ② + i] * p二[i * ③ + 列];
	memcpy(p出, v, 4 * ①*③);
	delete[] v;
}
void C矩阵::f单位矩阵_(float *p, int p数) {
	for (int 行 = 0; 行 != p数; ++行)
		for (int 列 = 0; 列 != p数; ++列)
			p[行 * p数 + 列] = (行 == 列) ? 1.f : 0.f;
}
void C矩阵::f矩阵相加_(float *po, const float *p1, const float *p2, int ni, int nj) {
	float *v = new float[ni*nj];
	memset(v, 0, sizeof(float)*ni*nj);
	for (int i = 0; i != ni; ++i)
		for (int j = 0; j != nj; ++j) {
			const int n = i * nj + j;
			v[n] = p1[n] + p2[n];
		}
	memcpy(po, v, 4 * ni*nj);
	delete[] v;
}
void C矩阵::f矩阵转置_(float *po, const float *pi, int ni, int nj) {
	float *v = new float[ni*nj];
	memset(v, 0, sizeof(float)*ni*nj);
	for (int i = 0; i != ni; ++i)
		for (int j = 0; j != nj; ++j)
			v[i*ni + j] = pi[j*nj + i];
	memcpy(po, v, 4 * ni*nj);
	delete[] v;
}
float C矩阵::f算行列式_(float *p, int n) {
	float s0 = 0;
	for (int i = 0; i != n; ++i) {
		float s1 = 1;
		for (int j = 0; j != n; ++j) {
			s1 *= p[i*n + (i + j) % n];
		}
		s0 += s1;
	}
	for (int i = 0; i != n; ++i) {
		float s1 = 1;
		for (int j = 0; j != n; ++j) {
			s1 *= p[i*n + (i - j) % n];
		}
		s0 -= s1;
	}
	return s0;
}
//二阶矩阵
S矩阵2 &S矩阵2::operator +=(const S矩阵2 &p) {
	C矩阵::f矩阵相加((t基类&)(*this), (const t基类&)(*this), (const t基类&)p);
	return *this;
}
S矩阵2 &S矩阵2::operator *=(const S矩阵2 &p) {
	C矩阵::f矩阵相乘((t基类&)(*this), (const t基类&)(*this), (const t基类&)p);
	return *this;
}
S矩阵2 S矩阵2::operator +(const S矩阵2 &p) const {
	S矩阵2 v;
	C矩阵::f矩阵相加((t基类&)v, (const t基类&)(*this), (const t基类&)p);
	return v;
}
S矩阵2 S矩阵2::operator *(const S矩阵2 &p) const {
	S矩阵2 v;
	C矩阵::f矩阵相乘((t基类&)v, (const t基类&)(*this), (const t基类&)p);
	return v;
}
S矩阵2 S矩阵2::fc单位() {
	S矩阵2 v;
	v.m[0][0] = 1;	v.m[0][1] = 0;
	v.m[1][0] = 0;	v.m[1][1] = 1;
	return v;
}
S矩阵2 S矩阵2::fc旋转(const float &t) {
	S矩阵2 v;
	const float s = sin(t);
	const float c = cos(t);
	v.m[0][0] = c;	v.m[0][1] = -s;
	v.m[1][0] = s;	v.m[1][1] = c;
	return v;
}
S矩阵2 S矩阵2::fc缩放(const float &x, const float &y) {
	S矩阵2 v;
	v.m[0][0] = x;	v.m[0][1] = 0;
	v.m[1][0] = 0;	v.m[1][1] = y;
	return v;
}
S矩阵2 S矩阵2::fc切变(const float &x, const float &y) {
	S矩阵2 v;
	v.m[0][0] = 1;	v.m[0][1] = x;
	v.m[1][0] = y;	v.m[1][1] = 1;
	return v;
}
S矩阵2 S矩阵2::fc翻转(const float &x, const float &y) {
	S矩阵2 v;
	v.m[0][0] = sin(y);	v.m[0][1] = 0;
	v.m[1][0] = 0;		v.m[1][1] = sin(x);
	return v;
}
S矩阵2 S矩阵2::fc复数(const t复数 &cx) {
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
S矩阵4 &S矩阵4::operator +=(const S矩阵4 &p) {
	C矩阵::f矩阵相加((t基类&)(*this), (const t基类&)(*this), (const t基类&)p);
	return *this;
}
S矩阵4 &S矩阵4::operator *=(const S矩阵4 &p) {
	C矩阵::f矩阵相乘((t基类&)(*this), (const t基类&)(*this), (const t基类&)p);
	return *this;
}
S矩阵4 S矩阵4::operator +(const S矩阵4 &p) const {
	S矩阵4 v;
	C矩阵::f矩阵相加((t基类&)v, (const t基类&)(*this), (const t基类&)p);
	return v;
}
S矩阵4 S矩阵4::operator *(const S矩阵4 &p) const {
	S矩阵4 v;
	C矩阵::f矩阵相乘((t基类&)v, (const t基类&)(*this), (const t基类&)p);
	return v;
}
S矩阵4 S矩阵4::fc单位() {
	S矩阵4 v;
	v.m[0][0] = 1;	v.m[0][1] = 0;	v.m[0][2] = 0;	v.m[0][3] = 0;
	v.m[1][0] = 0;	v.m[1][1] = 1;	v.m[1][2] = 0;	v.m[1][3] = 0;
	v.m[2][0] = 0;	v.m[2][1] = 0;	v.m[2][2] = 1;	v.m[2][3] = 0;
	v.m[3][0] = 0;	v.m[3][1] = 0;	v.m[3][2] = 0;	v.m[3][3] = 1;
	return v;
}
S矩阵4 S矩阵4::fc绕x旋转(const float &t) {
	S矩阵4 v;
	const float s = sin(t);
	const float c = cos(t);
	v.m[0][0] = 1;	v.m[0][1] = 0;	v.m[0][2] = 0;	v.m[0][3] = 0;
	v.m[1][0] = 0;	v.m[1][1] = c;	v.m[1][2] = -s;	v.m[1][3] = 0;
	v.m[2][0] = 0;	v.m[2][1] = s;	v.m[2][2] = c;	v.m[2][3] = 0;
	v.m[3][0] = 0;	v.m[3][1] = 0;	v.m[3][2] = 0;	v.m[3][3] = 1;
	return v;
}
S矩阵4 S矩阵4::fc绕y旋转(const float &t) {
	S矩阵4 v;
	const float s = sin(t);
	const float c = cos(t);
	v.m[0][0] = c;	v.m[0][1] = 0;	v.m[0][2] = s;	v.m[0][3] = 0;
	v.m[1][0] = 0;	v.m[1][1] = 1;	v.m[1][2] = 0;	v.m[1][3] = 0;
	v.m[2][0] = -s;	v.m[2][1] = 0;	v.m[2][2] = c;	v.m[2][3] = 0;
	v.m[3][0] = 0;	v.m[3][1] = 0;	v.m[3][2] = 0;	v.m[3][3] = 1;
	return v;
}
S矩阵4 S矩阵4::fc绕z旋转(const float &t) {
	S矩阵4 v;
	const float s = sin(t);
	const float c = cos(t);
	v.m[0][0] = c;	v.m[0][1] = -s;	v.m[0][2] = 0;	v.m[0][3] = 0;
	v.m[1][0] = s;	v.m[1][1] = c;	v.m[1][2] = 0;	v.m[1][3] = 0;
	v.m[2][0] = 0;	v.m[2][1] = 0;	v.m[2][2] = 1;	v.m[2][3] = 0;
	v.m[3][0] = 0;	v.m[3][1] = 0;	v.m[3][2] = 0;	v.m[3][3] = 1;
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
	v.m[0][0] = cy * cz;			v.m[0][1] = -cy * sz;			v.m[0][2] = sy;		v.m[0][3] = 0;
	v.m[1][0] = cx * sz + cz * sx*sy;	v.m[1][1] = cx * cz - sx * sy*sz;	v.m[1][2] = -cy * sx;	v.m[1][3] = 0;
	v.m[2][0] = sx * sz - cx * cz*sy;	v.m[2][1] = cz * sx + cx * sy*sz;	v.m[2][2] = cx * cy;	v.m[2][3] = 0;
	v.m[3][0] = 0;				v.m[3][1] = 0;				v.m[3][2] = 0;		v.m[3][3] = 1;
	return v;
}
S矩阵4 S矩阵4::fc看l(const S向量3 &e, const S向量3 &a, const S向量3 &u) {
	S矩阵4 v;
	const S向量3 z = (a - e).fg归一();	//前
	const S向量3 x = u.f叉乘(z).fg归一();	//右
	const S向量3 y = z.f叉乘(x);	//上
	v.m[0][0] = x.x;	v.m[0][1] = x.y;	v.m[0][2] = x.z;	v.m[0][3] = -x.f点乘(e);
	v.m[1][0] = y.x;	v.m[1][1] = y.y;	v.m[1][2] = y.z;	v.m[1][3] = -y.f点乘(e);
	v.m[2][0] = z.x;	v.m[2][1] = z.y;	v.m[2][2] = z.z;	v.m[2][3] = -z.f点乘(e);
	v.m[3][0] = 0;		v.m[3][1] = 0;		v.m[3][2] = 0;		v.m[3][3] = 1;
	return v;
}
S矩阵4 S矩阵4::fc看r(const S向量3 &e, const S向量3 &a, const S向量3 &u) {
	S矩阵4 v;
	const S向量3 z = (e - a).fg归一();
	const S向量3 x = u.f叉乘(z).fg归一();
	const S向量3 y = z.f叉乘(x);
	v.m[0][0] = x.x;	v.m[0][1] = x.y;	v.m[0][2] = x.z;	v.m[0][3] = -x.f点乘(e);
	v.m[1][0] = y.x;	v.m[1][1] = y.y;	v.m[1][2] = y.z;	v.m[1][3] = -y.f点乘(e);
	v.m[2][0] = z.x;	v.m[2][1] = z.y;	v.m[2][2] = z.z;	v.m[2][3] = -z.f点乘(e);
	v.m[3][0] = 0;		v.m[3][1] = 0;		v.m[3][2] = 0;		v.m[3][3] = 1;
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
	v.m[0][0] = x;	v.m[0][1] = 0;	v.m[0][2] = 0;		v.m[0][3] = 0;
	v.m[1][0] = 0;	v.m[1][1] = y;	v.m[1][2] = 0;		v.m[1][3] = 0;
	v.m[2][0] = 0;	v.m[2][1] = 0;	v.m[2][2] = q1;		v.m[2][3] = q2;
	v.m[3][0] = 0;	v.m[3][1] = 0;	v.m[3][2] = 1;		v.m[3][3] = 0;
	return v;
}
S矩阵4 S矩阵4::fc透视投影视角r(const float &f, const float &a, const float &zn, const float &zf) {
	S矩阵4 v;
	const float y = 1.0f / tan(f * 0.5f);
	const float x = y / a;
	const float q1 = zn / (zf - zn);
	const float q2 = zf * q1;
	v.m[0][0] = x;	v.m[0][1] = 0;	v.m[0][2] = 0;		v.m[0][3] = 0;
	v.m[1][0] = 0;	v.m[1][1] = y;	v.m[1][2] = 0;		v.m[1][3] = 0;
	v.m[2][0] = 0;	v.m[2][1] = 0;	v.m[2][2] = q1;		v.m[2][3] = q2;
	v.m[3][0] = 0;	v.m[3][1] = 0;	v.m[3][2] = -1;		v.m[3][3] = 0;
	return v;
}
S矩阵4 S矩阵4::fc透视投影中心l(float w, float h, float zn, float zf) {
	S矩阵4 v;
	const float q1 = zf / (zf - zn);
	const float q2 = -zn * q1;
	v.m[0][0] = 2 * zn / w;	v.m[0][1] = 0;		v.m[0][2] = 0;		v.m[0][3] = 0;
	v.m[1][0] = 0;		v.m[1][1] = 2 * zn / h;	v.m[1][2] = 0;		v.m[1][3] = 0;
	v.m[2][0] = 0;		v.m[2][1] = 0;		v.m[2][2] = q1;		v.m[2][3] = q2;
	v.m[3][0] = 0;		v.m[3][1] = 0;		v.m[3][2] = 1;		v.m[3][3] = 0;
	return v;
}
S矩阵4 S矩阵4::fc透视投影中心r(float w, float h, float zn, float zf) {
	S矩阵4 v;
	const float q1 = zf / (zn - zf);
	const float q2 = zn * q1;
	v.m[0][0] = 2 * zn / w;	v.m[0][1] = 0;		v.m[0][2] = 0;	v.m[0][3] = 0;
	v.m[1][0] = 0;		v.m[1][1] = 2 * zn / h;	v.m[1][2] = 0;	v.m[1][3] = 0;
	v.m[2][0] = 0;		v.m[2][1] = 0;		v.m[2][2] = q1;	v.m[2][3] = q2;
	v.m[3][0] = 0;		v.m[3][1] = 0;		v.m[3][2] = -1;	v.m[3][3] = 0;
	return v;
}
S矩阵4 S矩阵4::fc透视投影自定义l(float l, float r, float b, float t, float zn, float zf) {
	S矩阵4 v;
	const float w = r - l;
	const float h = t - b;
	const float q1 = zf / (zf - zn);
	const float q2 = -zn * q1;
	v.m[0][0] = 2 * zn / w;	v.m[0][1] = 0;		v.m[0][2] = -(l + r) / w;	v.m[0][3] = 0;
	v.m[1][0] = 0;		v.m[1][1] = 2 * zn / h;	v.m[1][2] = -(t + b) / h;	v.m[1][3] = 0;
	v.m[2][0] = 0;		v.m[2][1] = 0;		v.m[2][2] = q1;			v.m[2][3] = q2;
	v.m[3][0] = 0;		v.m[3][1] = 0;		v.m[3][2] = 1;			v.m[3][3] = 0;
	return v;
}
S矩阵4 S矩阵4::fc透视投影自定义r(float l, float r, float b, float t, float zn, float zf) {
	S矩阵4 v;
	const float q1 = zf / (zn - zf);
	const float q2 = zn * q1;
	const float w = r - l;
	const float h = t - b;
	v.m[0][0] = 2 * zn / w;	v.m[0][1] = 0;		v.m[0][2] = (l + r) / w;	v.m[0][3] = 0;
	v.m[1][0] = 0;		v.m[1][1] = 2 * zn / h;	v.m[1][2] = (t + b) / h;	v.m[1][3] = 0;
	v.m[2][0] = 0;		v.m[2][1] = 0;		v.m[2][2] = q1;			v.m[2][3] = q2;
	v.m[3][0] = 0;		v.m[3][1] = 0;		v.m[3][2] = -1;			v.m[3][3] = 0;
	return v;
}
S矩阵4 S矩阵4::fc转置(const S矩阵4 &p) {
	S矩阵4 v;
	v.m[0][0] = p.m[0][0];	v.m[0][1] = p.m[1][0];	v.m[0][2] = p.m[2][0];	v.m[0][3] = p.m[3][0];
	v.m[1][0] = p.m[0][1];	v.m[1][1] = p.m[1][1];	v.m[1][2] = p.m[2][1];	v.m[1][3] = p.m[3][1];
	v.m[2][0] = p.m[0][2];	v.m[2][1] = p.m[1][2];	v.m[2][2] = p.m[2][2];	v.m[2][3] = p.m[3][2];
	v.m[3][0] = p.m[0][3];	v.m[3][1] = p.m[1][3];	v.m[3][2] = p.m[2][3];	v.m[3][3] = p.m[3][3];
	return v;
}
S矩阵4 S矩阵4::fc平移(const float &x, const float &y, const float &z) {
	S矩阵4 v;
	v.m[0][0] = 1;	v.m[0][1] = 0;	v.m[0][2] = 0;	v.m[0][3] = x;
	v.m[1][0] = 0;	v.m[1][1] = 1;	v.m[1][2] = 0;	v.m[1][3] = y;
	v.m[2][0] = 0;	v.m[2][1] = 0;	v.m[2][2] = 1;	v.m[2][3] = z;
	v.m[3][0] = 0;	v.m[3][1] = 0;	v.m[3][2] = 0;	v.m[3][3] = 1;
	return v;
}
S矩阵4 S矩阵4::fc缩放(const float &x, const float &y, const float &z) {
	S矩阵4 v;
	v.m[0][0] = x;	v.m[0][1] = 0;	v.m[0][2] = 0;	v.m[0][3] = 0;
	v.m[1][0] = 0;	v.m[1][1] = y;	v.m[1][2] = 0;	v.m[1][3] = 0;
	v.m[2][0] = 0;	v.m[2][1] = 0;	v.m[2][2] = z;	v.m[2][3] = 0;
	v.m[3][0] = 0;	v.m[3][1] = 0;	v.m[3][2] = 0;	v.m[3][3] = 1;
	return v;
}
S矩阵4 S矩阵4::fc镜面反射(const S平面方程 &p) {
	S矩阵4 v;
	v.m[0][0] = 1-2*p.a*p.a;	v.m[0][1] = -2*p.a*p.b;		v.m[0][2] = -2*p.a*p.c;		v.m[0][3] = 0;
	v.m[1][0] = -2*p.b*p.a;		v.m[1][1] = 1-2*p.b*p.b;	v.m[1][2] = -2*p.b*p.c;		v.m[1][3] = 0;
	v.m[2][0] = -2*p.c*p.a;		v.m[2][1] = -2*p.c*p.b;		v.m[2][2] = 1-2*p.c*p.c;	v.m[2][3] = 0;
	v.m[3][0] = -2*p.d*p.a;		v.m[3][1] = -2*p.d*p.b;		v.m[3][2] = -2*p.d*p.c;		v.m[3][3] = 1;
	return v;
}
S矩阵4 S矩阵4::fc阴影(const S平面方程 &p, const S向量4 &l) {
	S矩阵4 v;
	const float nl = p.fg法().f点乘(l.ft向量3());
	const float nld = nl - p.d;
	v.m[0][0] = nld-p.a*l.x;	v.m[0][1] = -l.y*p.a;		v.m[0][2] = -l.z*p.a;		v.m[0][3] = -p.a;
	v.m[1][0] = -l.x*p.b;		v.m[1][1] = nld-l.y*p.b;	v.m[1][2] = -l.z*p.b;		v.m[1][3] = -p.b;
	v.m[2][0] = -l.x*p.c;		v.m[2][1] = -l.y*p.c;		v.m[2][2] = nld-l.z*p.c;	v.m[2][3] = -p.c;
	v.m[3][0] = -l.x*p.d;		v.m[3][1] = -l.y*p.d;		v.m[3][2] = -l.z*p.d;		v.m[3][3] = nl;
	return v;
}

}