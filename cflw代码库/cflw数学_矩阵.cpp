#include "cflw��ѧ_����.h"
#include "cflw��ѧ_����.h"
#include "cflw��ѧ_��������.h"
namespace cflw::��ѧ {
//������
void C����::f�վ���_(float *p, int p��, int p��) {
	for (int �� = 0; �� != p��; ++��)
		for (int �� = 0; �� != p��; ++��)
			p[�� * p�� + ��] = 0;
}
void C����::f�������_(float *p��, const float *pһ, const float *p��, int ��, int ��, int ��) {
	float *v = new float[��*��];
	memset(v, 0, sizeof(float)*��*��);
	for (int �� = 0; �� != ��; ++��)
		for (int �� = 0; �� != ��; ++��)
			for (int i = 0; i != ��; ++i)
				v[�� * �� + ��] += pһ[�� * �� + i] * p��[i * �� + ��];
	memcpy(p��, v, 4 * ��*��);
	delete[] v;
}
void C����::f��λ����_(float *p, int p��) {
	for (int �� = 0; �� != p��; ++��)
		for (int �� = 0; �� != p��; ++��)
			p[�� * p�� + ��] = (�� == ��) ? 1.f : 0.f;
}
void C����::f�������_(float *po, const float *p1, const float *p2, int ni, int nj) {
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
void C����::f����ת��_(float *po, const float *pi, int ni, int nj) {
	float *v = new float[ni*nj];
	memset(v, 0, sizeof(float)*ni*nj);
	for (int i = 0; i != ni; ++i)
		for (int j = 0; j != nj; ++j)
			v[i*ni + j] = pi[j*nj + i];
	memcpy(po, v, 4 * ni*nj);
	delete[] v;
}
float C����::f������ʽ_(float *p, int n) {
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
//���׾���
S����2 &S����2::operator +=(const S����2 &p) {
	C����::f�������((t����&)(*this), (const t����&)(*this), (const t����&)p);
	return *this;
}
S����2 &S����2::operator *=(const S����2 &p) {
	C����::f�������((t����&)(*this), (const t����&)(*this), (const t����&)p);
	return *this;
}
S����2 S����2::operator +(const S����2 &p) const {
	S����2 v;
	C����::f�������((t����&)v, (const t����&)(*this), (const t����&)p);
	return v;
}
S����2 S����2::operator *(const S����2 &p) const {
	S����2 v;
	C����::f�������((t����&)v, (const t����&)(*this), (const t����&)p);
	return v;
}
S����2 S����2::fc��λ() {
	S����2 v;
	v.m[0][0] = 1;	v.m[0][1] = 0;
	v.m[1][0] = 0;	v.m[1][1] = 1;
	return v;
}
S����2 S����2::fc��ת(const float &t) {
	S����2 v;
	const float s = sin(t);
	const float c = cos(t);
	v.m[0][0] = c;	v.m[0][1] = -s;
	v.m[1][0] = s;	v.m[1][1] = c;
	return v;
}
S����2 S����2::fc����(const float &x, const float &y) {
	S����2 v;
	v.m[0][0] = x;	v.m[0][1] = 0;
	v.m[1][0] = 0;	v.m[1][1] = y;
	return v;
}
S����2 S����2::fc�б�(const float &x, const float &y) {
	S����2 v;
	v.m[0][0] = 1;	v.m[0][1] = x;
	v.m[1][0] = y;	v.m[1][1] = 1;
	return v;
}
S����2 S����2::fc��ת(const float &x, const float &y) {
	S����2 v;
	v.m[0][0] = sin(y);	v.m[0][1] = 0;
	v.m[1][0] = 0;		v.m[1][1] = sin(x);
	return v;
}
S����2 S����2::fc����(const t���� &cx) {
	const float r = cx.real();
	const float i = cx.imag();
	const float t = atan2(i, r);
	const float s = hypot(r, i);
	return fc��ת(t) * fc����(s, s);
}
//�Ľ׾���
const S����4 S����4::c��λ = S����4::fc��λ();
S����4::S����4() {
	memset(this, 0, sizeof(S����4));
}
S����4 &S����4::operator +=(const S����4 &p) {
	C����::f�������((t����&)(*this), (const t����&)(*this), (const t����&)p);
	return *this;
}
S����4 &S����4::operator *=(const S����4 &p) {
	C����::f�������((t����&)(*this), (const t����&)(*this), (const t����&)p);
	return *this;
}
S����4 S����4::operator +(const S����4 &p) const {
	S����4 v;
	C����::f�������((t����&)v, (const t����&)(*this), (const t����&)p);
	return v;
}
S����4 S����4::operator *(const S����4 &p) const {
	S����4 v;
	C����::f�������((t����&)v, (const t����&)(*this), (const t����&)p);
	return v;
}
S����4 S����4::fc��λ() {
	S����4 v;
	v.m[0][0] = 1;	v.m[0][1] = 0;	v.m[0][2] = 0;	v.m[0][3] = 0;
	v.m[1][0] = 0;	v.m[1][1] = 1;	v.m[1][2] = 0;	v.m[1][3] = 0;
	v.m[2][0] = 0;	v.m[2][1] = 0;	v.m[2][2] = 1;	v.m[2][3] = 0;
	v.m[3][0] = 0;	v.m[3][1] = 0;	v.m[3][2] = 0;	v.m[3][3] = 1;
	return v;
}
S����4 S����4::fc��x��ת(const float &t) {
	S����4 v;
	const float s = sin(t);
	const float c = cos(t);
	v.m[0][0] = 1;	v.m[0][1] = 0;	v.m[0][2] = 0;	v.m[0][3] = 0;
	v.m[1][0] = 0;	v.m[1][1] = c;	v.m[1][2] = -s;	v.m[1][3] = 0;
	v.m[2][0] = 0;	v.m[2][1] = s;	v.m[2][2] = c;	v.m[2][3] = 0;
	v.m[3][0] = 0;	v.m[3][1] = 0;	v.m[3][2] = 0;	v.m[3][3] = 1;
	return v;
}
S����4 S����4::fc��y��ת(const float &t) {
	S����4 v;
	const float s = sin(t);
	const float c = cos(t);
	v.m[0][0] = c;	v.m[0][1] = 0;	v.m[0][2] = s;	v.m[0][3] = 0;
	v.m[1][0] = 0;	v.m[1][1] = 1;	v.m[1][2] = 0;	v.m[1][3] = 0;
	v.m[2][0] = -s;	v.m[2][1] = 0;	v.m[2][2] = c;	v.m[2][3] = 0;
	v.m[3][0] = 0;	v.m[3][1] = 0;	v.m[3][2] = 0;	v.m[3][3] = 1;
	return v;
}
S����4 S����4::fc��z��ת(const float &t) {
	S����4 v;
	const float s = sin(t);
	const float c = cos(t);
	v.m[0][0] = c;	v.m[0][1] = -s;	v.m[0][2] = 0;	v.m[0][3] = 0;
	v.m[1][0] = s;	v.m[1][1] = c;	v.m[1][2] = 0;	v.m[1][3] = 0;
	v.m[2][0] = 0;	v.m[2][1] = 0;	v.m[2][2] = 1;	v.m[2][3] = 0;
	v.m[3][0] = 0;	v.m[3][1] = 0;	v.m[3][2] = 0;	v.m[3][3] = 1;
	return v;
}
S����4 S����4::fc��ת(const float &x, const float &y, const float &z) {
	S����4 v;
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
S����4 S����4::fc��l(const S����3 &e, const S����3 &a, const S����3 &u) {
	S����4 v;
	const S����3 z = (a - e).fg��һ();	//ǰ
	const S����3 x = u.f���(z).fg��һ();	//��
	const S����3 y = z.f���(x);	//��
	v.m[0][0] = x.x;	v.m[0][1] = x.y;	v.m[0][2] = x.z;	v.m[0][3] = -x.f���(e);
	v.m[1][0] = y.x;	v.m[1][1] = y.y;	v.m[1][2] = y.z;	v.m[1][3] = -y.f���(e);
	v.m[2][0] = z.x;	v.m[2][1] = z.y;	v.m[2][2] = z.z;	v.m[2][3] = -z.f���(e);
	v.m[3][0] = 0;		v.m[3][1] = 0;		v.m[3][2] = 0;		v.m[3][3] = 1;
	return v;
}
S����4 S����4::fc��r(const S����3 &e, const S����3 &a, const S����3 &u) {
	S����4 v;
	const S����3 z = (e - a).fg��һ();
	const S����3 x = u.f���(z).fg��һ();
	const S����3 y = z.f���(x);
	v.m[0][0] = x.x;	v.m[0][1] = x.y;	v.m[0][2] = x.z;	v.m[0][3] = -x.f���(e);
	v.m[1][0] = y.x;	v.m[1][1] = y.y;	v.m[1][2] = y.z;	v.m[1][3] = -y.f���(e);
	v.m[2][0] = z.x;	v.m[2][1] = z.y;	v.m[2][2] = z.z;	v.m[2][3] = -z.f���(e);
	v.m[3][0] = 0;		v.m[3][1] = 0;		v.m[3][2] = 0;		v.m[3][3] = 1;
	return v;
}
S����4 S����4::fc����l(const S����3 &e, const S����3 &f, const S����3 &u) {
	S����4 v;
	return v;
}
S����4 S����4::fc����r(const S����3 &e, const S����3 &f, const S����3 &u) {
	S����4 v;
	return v;
}
S����4 S����4::fc͸��ͶӰ�ӽ�l(const float &f, const float &a, const float &zn, const float &zf) {
	S����4 v;
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
S����4 S����4::fc͸��ͶӰ�ӽ�r(const float &f, const float &a, const float &zn, const float &zf) {
	S����4 v;
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
S����4 S����4::fc͸��ͶӰ����l(float w, float h, float zn, float zf) {
	S����4 v;
	const float q1 = zf / (zf - zn);
	const float q2 = -zn * q1;
	v.m[0][0] = 2 * zn / w;	v.m[0][1] = 0;		v.m[0][2] = 0;		v.m[0][3] = 0;
	v.m[1][0] = 0;		v.m[1][1] = 2 * zn / h;	v.m[1][2] = 0;		v.m[1][3] = 0;
	v.m[2][0] = 0;		v.m[2][1] = 0;		v.m[2][2] = q1;		v.m[2][3] = q2;
	v.m[3][0] = 0;		v.m[3][1] = 0;		v.m[3][2] = 1;		v.m[3][3] = 0;
	return v;
}
S����4 S����4::fc͸��ͶӰ����r(float w, float h, float zn, float zf) {
	S����4 v;
	const float q1 = zf / (zn - zf);
	const float q2 = zn * q1;
	v.m[0][0] = 2 * zn / w;	v.m[0][1] = 0;		v.m[0][2] = 0;	v.m[0][3] = 0;
	v.m[1][0] = 0;		v.m[1][1] = 2 * zn / h;	v.m[1][2] = 0;	v.m[1][3] = 0;
	v.m[2][0] = 0;		v.m[2][1] = 0;		v.m[2][2] = q1;	v.m[2][3] = q2;
	v.m[3][0] = 0;		v.m[3][1] = 0;		v.m[3][2] = -1;	v.m[3][3] = 0;
	return v;
}
S����4 S����4::fc͸��ͶӰ�Զ���l(float l, float r, float b, float t, float zn, float zf) {
	S����4 v;
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
S����4 S����4::fc͸��ͶӰ�Զ���r(float l, float r, float b, float t, float zn, float zf) {
	S����4 v;
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
S����4 S����4::fcת��(const S����4 &p) {
	S����4 v;
	v.m[0][0] = p.m[0][0];	v.m[0][1] = p.m[1][0];	v.m[0][2] = p.m[2][0];	v.m[0][3] = p.m[3][0];
	v.m[1][0] = p.m[0][1];	v.m[1][1] = p.m[1][1];	v.m[1][2] = p.m[2][1];	v.m[1][3] = p.m[3][1];
	v.m[2][0] = p.m[0][2];	v.m[2][1] = p.m[1][2];	v.m[2][2] = p.m[2][2];	v.m[2][3] = p.m[3][2];
	v.m[3][0] = p.m[0][3];	v.m[3][1] = p.m[1][3];	v.m[3][2] = p.m[2][3];	v.m[3][3] = p.m[3][3];
	return v;
}
S����4 S����4::fcƽ��(const float &x, const float &y, const float &z) {
	S����4 v;
	v.m[0][0] = 1;	v.m[0][1] = 0;	v.m[0][2] = 0;	v.m[0][3] = x;
	v.m[1][0] = 0;	v.m[1][1] = 1;	v.m[1][2] = 0;	v.m[1][3] = y;
	v.m[2][0] = 0;	v.m[2][1] = 0;	v.m[2][2] = 1;	v.m[2][3] = z;
	v.m[3][0] = 0;	v.m[3][1] = 0;	v.m[3][2] = 0;	v.m[3][3] = 1;
	return v;
}
S����4 S����4::fc����(const float &x, const float &y, const float &z) {
	S����4 v;
	v.m[0][0] = x;	v.m[0][1] = 0;	v.m[0][2] = 0;	v.m[0][3] = 0;
	v.m[1][0] = 0;	v.m[1][1] = y;	v.m[1][2] = 0;	v.m[1][3] = 0;
	v.m[2][0] = 0;	v.m[2][1] = 0;	v.m[2][2] = z;	v.m[2][3] = 0;
	v.m[3][0] = 0;	v.m[3][1] = 0;	v.m[3][2] = 0;	v.m[3][3] = 1;
	return v;
}
S����4 S����4::fc���淴��(const Sƽ�淽�� &p) {
	S����4 v;
	v.m[0][0] = 1-2*p.a*p.a;	v.m[0][1] = -2*p.a*p.b;		v.m[0][2] = -2*p.a*p.c;		v.m[0][3] = 0;
	v.m[1][0] = -2*p.b*p.a;		v.m[1][1] = 1-2*p.b*p.b;	v.m[1][2] = -2*p.b*p.c;		v.m[1][3] = 0;
	v.m[2][0] = -2*p.c*p.a;		v.m[2][1] = -2*p.c*p.b;		v.m[2][2] = 1-2*p.c*p.c;	v.m[2][3] = 0;
	v.m[3][0] = -2*p.d*p.a;		v.m[3][1] = -2*p.d*p.b;		v.m[3][2] = -2*p.d*p.c;		v.m[3][3] = 1;
	return v;
}
S����4 S����4::fc��Ӱ(const Sƽ�淽�� &p, const S����4 &l) {
	S����4 v;
	const float nl = p.fg��().f���(l.ft����3());
	const float nld = nl - p.d;
	v.m[0][0] = nld-p.a*l.x;	v.m[0][1] = -l.y*p.a;		v.m[0][2] = -l.z*p.a;		v.m[0][3] = -p.a;
	v.m[1][0] = -l.x*p.b;		v.m[1][1] = nld-l.y*p.b;	v.m[1][2] = -l.z*p.b;		v.m[1][3] = -p.b;
	v.m[2][0] = -l.x*p.c;		v.m[2][1] = -l.y*p.c;		v.m[2][2] = nld-l.z*p.c;	v.m[2][3] = -p.c;
	v.m[3][0] = -l.x*p.d;		v.m[3][1] = -l.y*p.d;		v.m[3][2] = -l.z*p.d;		v.m[3][3] = nl;
	return v;
}

}