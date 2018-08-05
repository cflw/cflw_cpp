#include <assert.h>
#include "cflw��ѧ_ͼ��.h"
#include "cflw��ѧ_����.h"
#include "cflw��ѧ_����.h"
namespace cflw::��ѧ {
//=============================================================================
// ����
//=============================================================================
template<> S��ɫ f��ֵ<S��ɫ>(const S��ɫ &p��ʼֵ, const S��ɫ &p��ֵֹ, float p�м�ֵ) {
	return p��ʼֵ.fȫ��ֵ(p��ֵֹ, p�м�ֵ);
}
template<> S��Ԫ�� f��ֵ(const S��Ԫ�� &q0, const S��Ԫ�� &q1, float p) {
	return q0.f��ֵ(q1, p);
}
//=============================================================================
// ��ɫrgb
//=============================================================================
const S��ɫ S��ɫ::c��{1, 1, 1, 1};
const S��ɫ S��ɫ::c��{0, 0, 0, 1};
const S��ɫ S��ɫ::c��{1, 0, 0, 1};
const S��ɫ S��ɫ::c��{1, 0.5f, 0, 1};
const S��ɫ S��ɫ::c��{1, 1, 0, 1};
const S��ɫ S��ɫ::c��{0, 1, 0, 1};
const S��ɫ S��ɫ::c��{0, 1, 1, 1};
const S��ɫ S��ɫ::c��{0, 0, 1, 1};
const S��ɫ S��ɫ::c��{1, 0, 1, 1};
const S��ɫ S��ɫ::c��{1, 0.5f, 0.5f, 1};
const S��ɫ S��ɫ::c��{0.5f, 0.5f, 0.5f, 1};
//���캯��
S��ɫ::S��ɫ() : r(0), g(0), b(0), a(0) {
}
S��ɫ::S��ɫ(E��ɫֵ p): r(f��ɫֵ��ȡ_��(p)), g(f��ɫֵ��ȡ_��(p)), b(f��ɫֵ��ȡ_��(p)), a(f��ɫֵ��ȡ_��(p)) {
}
S��ɫ::S��ɫ(float R, float G, float B, float A) : r(R), g(G), b(B), a(A) {
}
S��ɫ::operator unsigned long() {
	return (unsigned long)(a * 255) * 0x1000000 + (unsigned long)(r * 255) * 0x10000 + (unsigned long)(g * 255) * 0x100 + (unsigned long)(b * 255);
}
S��ɫ S��ɫ::fc�ʺ�(float R, float A, float l, float s) {
	R = fѭ��<float>(R, 0, 7);
	S��ɫ c(0, 0, 0, A);
	if (R <= 2) {//��->��->��
		c.r = 1;
		c.g = f��ֵ<float>(0, 1, R / 2);
	} else if (R <= 3) {//��->��
		c.r = f��ֵ<float>(0, 1, 3 - R);
		c.g = 1;
	} else if (R <= 4) {//��->��
		c.g = 1;
		c.b = f��ֵ<float>(0, 1, R - 3);
	} else if (R <= 5) {//��->��
		c.g = f��ֵ<float>(0, 1, 5 - R);
		c.b = 1;
	} else if (R <= 6) {//��->��
		c.r = f��ֵ<float>(0, 1, R - 5);
		c.b = 1;
	} else if (R <= 7) {//��->��
		c.r = 1;
		c.b = f��ֵ<float>(0, 1, 7 - R);
	}
	if (s != 1) {
		c.r = f��ֵ<float>(c.r, 1, s);
		c.g = f��ֵ<float>(c.g, 1, s);
		c.b = f��ֵ<float>(c.b, 1, s);
	}
	if (l != 1) {
		c.r *= l;
		c.g *= l;
		c.b *= l;
	}
	return c;
}
S��ɫ S��ɫ::fc����ɫ(float R, float A, float l, float s) {
	R = fѭ��<float>(R, 0, 3);
	S��ɫ c(0, 0, 0, A);
	if (R <= 1) {	//[0,1]
		const float v��ֵ = R;
		c.r = f��ֵ<float>(1, 0, v��ֵ);
		c.g = f��ֵ<float>(0, 1, v��ֵ);
	} else if (R <= 2) {	//(1,2]
		const float v��ֵ = R - 1;
		c.g = f��ֵ<float>(1, 0, v��ֵ);
		c.b = f��ֵ<float>(0, 1, v��ֵ);
	} else {	//(2,3)
		const float v��ֵ = R - 2;
		c.b = f��ֵ<float>(1, 0, v��ֵ);
		c.r = f��ֵ<float>(0, 1, v��ֵ);
	}
	if (s != 1) {
		c.r = f��ֵ<float>(c.r, 1, s);
		c.g = f��ֵ<float>(c.g, 1, s);
		c.b = f��ֵ<float>(c.b, 1, s);
	}
	if (l != 1) {
		c.r *= l;
		c.g *= l;
		c.b *= l;
	}
	return c;
}
S��ɫ S��ɫ::fc�ڰ�(float W, float A) {
	return S��ɫ(W, W, W, A);
}
constexpr float S��ɫ::f��ɫֵ��ȡ(E��ɫֵ pֵ, E��ɫֵ��ȡ p��ȡ) {
	return static_cast<float>((static_cast<unsigned int>(pֵ) >> (static_cast<unsigned int>(p��ȡ) * 8)) % 0x100) / 255.f;
}
constexpr float S��ɫ::f��ɫֵ��ȡ_��(E��ɫֵ p) {
	return f��ɫֵ��ȡ(p, e��ȡ��);
}
constexpr float S��ɫ::f��ɫֵ��ȡ_��(E��ɫֵ p) {
	return f��ɫֵ��ȡ(p, e��ȡ��);
}
constexpr float S��ɫ::f��ɫֵ��ȡ_��(E��ɫֵ p) {
	return f��ɫֵ��ȡ(p, e��ȡ��);
}
constexpr float S��ɫ::f��ɫֵ��ȡ_��(E��ɫֵ p) {
	return f��ɫֵ��ȡ(p, e��ȡ��);
}
void S��ɫ::f��ɫУ��() {
	for (int i = 0; i != 4; ++i) {
		if (v[i] > 1) v[i] = 1;
		if (v[i] < 0) v[i] = 0;
	}
}
S��ɫ S��ɫ::f�Աȶ�(const float &_) const {
	S��ɫ v = *this;
	for (int i = 0; i != 4; ++i) {
		v.v[i] *= _;
		if (v.v[i] > 1) v.v[i] = 1;
		if (v.v[i] < 0) v.v[i] = 0;
	}
	return v;
}
S��ɫ S��ɫ::f���Ͷ�(const float &) const {
	return *this;
}
S��ɫ S��ɫ::f��ɫ������(const float &p) const {
	S��ɫ v = *this;
	for (int i = 0; i != 3; ++i) {
		v.v[i] *= p;
	}
	return v;
}
S��ɫ S��ɫ::f͸���ȳ�(const float &p) const {
	S��ɫ v = *this;
	v.a *= p;
	return v;
}
S��ɫ S��ɫ::fȫ��ֵ(const S��ɫ &p��ɫ, const float &p��ֵ) const {
	return S��ɫ{
		f��ֵ<float>(r, p��ɫ.r, p��ֵ),
		f��ֵ<float>(g, p��ɫ.g, p��ֵ),
		f��ֵ<float>(b, p��ɫ.b, p��ֵ),
		f��ֵ<float>(a, p��ɫ.a, p��ֵ)
	};
}
S��ɫ S��ɫ::f��ɫ������ֵ(const S��ɫ &p��ɫ, const float &p��ֵ) const {
	return S��ɫ{
		f��ֵ<float>(r, p��ɫ.r, p��ֵ),
		f��ֵ<float>(g, p��ɫ.g, p��ֵ),
		f��ֵ<float>(b, p��ɫ.b, p��ֵ),
		a
	};
}
S��ɫ S��ɫ::f���_���(const S��ɫ &p) const {
	S��ɫ v = *this;
	for (int i = 0; i != 4; ++i) {
		v.v[i] += p.v[i];
		if (v.v[i] > 1) v.v[i] = 1;
		if (v.v[i] < 0) v.v[i] = 0;
	}
	return v;
}
S��ɫ S��ɫ::f���_���(const S��ɫ &p) const {
	S��ɫ v = *this;
	for (int i = 0; i != 4; ++i) {
		v.v[i] *= p.v[i];
		if (v.v[i] > 1) v.v[i] = 1;
		if (v.v[i] < 0) v.v[i] = 0;
	}
	return v;
}
S��ɫ S��ɫ::f���_����(const S��ɫ &p) const {
	S��ɫ v;
	v.r = this->r * this->a + p.r * (1 - this->a);
	v.g = this->g * this->a + p.g * (1 - this->a);
	v.b = this->b * this->a + p.b * (1 - this->a);
	v.a = this->a;
	return v;
}
S��ɫ S��ɫ::f���_����(const S��ɫ &p) const {
	S��ɫ v;
	v.r = this->r * (1 - p.a) + p.r * p.a;
	v.g = this->g * (1 - p.a) + p.g * p.a;
	v.b = this->b * (1 - p.a) + p.b * p.a;
	v.a = p.a;
	return v;
}
S��ɫ S��ɫ::f���_���(const S��ɫ &p) const {
	S��ɫ v;
	for (int i = 0; i != 4; ++i)
		v.v[i] = std::max<float>(this->v[i], p.v[i]);
	return v;
}
S��ɫ S��ɫ::f���_��С(const S��ɫ &p) const {
	S��ɫ v;
	for (int i = 0; i != 4; ++i)
		v.v[i] = std::min<float>(this->v[i], p.v[i]);
	return v;
}
S��ɫyuv S��ɫ::f��yuv() const {
	S��ɫyuv v;
	v.y = 0.299f * r + 0.587f * g + 0.114f * b;
	v.u = 0.436f * (b - v.y) / (1 - 0.114f) + 0.5f;
	v.v = 0.615f * (r - v.y) / (1 - 0.299f) + 0.5f;
	return v;
}
//=============================================================================
// ��ɫyuv
//=============================================================================
S��ɫ S��ɫyuv::f��rgb() const {
	S��ɫ v;
	v.r = y + 1.14f * v;
	v.g = y - 0.39f * u - 0.58f * v;
	v.b = y + 2.03f * u;
	return v;
}
//=============================================================================
// �������2
//=============================================================================
S�������2::S�������2(const S����2 &pƽ��, const float &p��ת, const S����2 &p����): mƽ��(pƽ��), m��ת(p��ת), m����(p����) {
}
S����2 S�������2::ft����2() const {
	//û��ƽ��
	return S����2::fc��ת(m��ת) * S����2::fc����(m����.x, m����.y);
}
//=============================================================================
// �������3
//=============================================================================
S�������3::S�������3(const S����3 &pƽ��, const S����3 &p��ת, const S����3 &p����): mƽ��(pƽ��), m��ת(p��ת), m����(p����) {
}
S����4 S�������3::ft����4() const {
	return S����4::fcƽ��(mƽ��.x, mƽ��.y, mƽ��.z) * S����4::fc��ת(m��ת.x, m��ת.y, m��ת.z) * S����4::fc����(m����.x, m����.y, m����.z);
}
//=============================================================================
// ���
//=============================================================================
S���::S���(const S����3 &p����, const S����3 &pĿ��, const S����3 &p�Ϸ�): m����(p����), mĿ��(pĿ��), m�Ϸ�(p�Ϸ�) {
}
S����4 S���::ft����4l() const {
	return S����4::fc��l(m����, mĿ��, m�Ϸ�);
}
S����4 S���::ft����4r() const {
	return S����4::fc��r(m����, mĿ��, m�Ϸ�);
}
//=============================================================================
// ͶӰ
//=============================================================================
SͶӰ::SͶӰ(float a��, float a��, float a�ӽ�, float a���ü���, float aԶ�ü���):
	m�ӽ�(a�ӽ�), m��(a��), m��(a��), m���ü���(a���ü���), mԶ�ü���(aԶ�ü���) {
}
S����4 SͶӰ::ft����4l() const {
	return S����4::fc͸��ͶӰ�ӽ�l(m�ӽ�, m�� / m��, m���ü���, mԶ�ü���);
}
S����4 SͶӰ::ft����4r() const {
	return S����4::fc͸��ͶӰ�ӽ�r(m�ӽ�, m�� / m��, m���ü���, mԶ�ü���);
}
//=============================================================================
//ŷ����
//=============================================================================
void Sŷ����::fs��λ() {
	mͷ = m�� = m�� = 0.f;
}
void Sŷ����::f����() {
	m�� = C�Ƕȼ���<float>::c����.f����(m��);
	if (m�� < -(float)c�� / 2.f) {
		m�� = -(float)c�� - m��;
		mͷ += (float)c��;
		m�� += (float)c��;
	} else if (m�� >(float)c�� / 2.f) {
		m�� = (float)c�� - m��;
		mͷ += (float)c��;
		m�� += (float)c��;
	}
	if (fabs(m��) > (float)c�� / 2.f - 1e-4) {
		mͷ += m��;
		m�� = 0.0f;
	} else {
		m�� = C�Ƕȼ���<float>::c����.f����(m��);
	}
	mͷ = C�Ƕȼ���<float>::c����.f����(mͷ);
}
void Sŷ����::fs���嵽����(const S��Ԫ�� &q) {
	float sp = -2.0f * (q.y*q.z - q.w*q.x);
	if (fabs(sp) > 0.9999f) {
		m�� = (float)c�� / 2 * sp;
		mͷ = atan2(-q.x*q.z + q.w*q.y, 0.5f - q.y*q.y - q.z*q.z);
		m�� = 0.0f;
	} else {
		m�� = asin(sp);
		mͷ = atan2(q.x*q.z + q.w*q.y, 0.5f - q.x*q.x - q.y*q.y);
		m�� = atan2(q.x*q.y + q.w*q.z, 0.5f - q.x*q.x - q.z*q.z);
	}
}
void Sŷ����::fs���Ե�����(const S��Ԫ�� &q) {
	float sp = -2.0f * (q.y*q.z + q.w*q.x);
	if (fabs(sp) > 0.9999f) {
		m�� = (float)c�� / 2 * sp;
		mͷ = atan2(-q.x*q.z - q.w*q.y, 0.5f - q.y*q.y - q.z*q.z);
		m�� = 0.0f;
	} else {
		m�� = asin(sp);
		mͷ = atan2(q.x*q.z - q.w*q.y, 0.5f - q.x*q.x - q.y*q.y);
		m�� = atan2(q.x*q.y - q.w*q.z, 0.5f - q.x*q.x - q.z*q.z);
	}
}
void Sŷ����::fs���嵽����(const S����4 &m) {
	float	sp = -m.m[3][2];
	if (fabs(sp) > 9.99999f) {
		m�� = (float)c�� / 2 * sp;
		mͷ = atan2(-m.m[2][3], m.m[1][1]);
		m�� = 0.0f;
	} else {
		mͷ = atan2(m.m[3][1], m.m[3][3]);
		m�� = asin(sp);
		m�� = atan2(m.m[1][2], m.m[2][2]);
	}
}
void Sŷ����::fs���絽����(const S����4 &m) {
	float	sp = -m.m[2][3];
	if (fabs(sp) > 9.99999f) {
		m�� = (float)c�� / 2.f * sp;
		mͷ = atan2(-m.m[3][1], m.m[1][1]);
		m�� = 0.0f;
	} else {
		mͷ = atan2(m.m[1][3], m.m[3][3]);
		m�� = asin(sp);
		m�� = atan2(m.m[2][1], m.m[2][2]);
	}
}
//=============================================================================
// ��Ԫ��
//=============================================================================
S��Ԫ��::S��Ԫ��() : w(0), x(0), y(0), z(0) {}
S��Ԫ��::S��Ԫ��(const float &W, const float &X, const float &Y, const float &Z) : w(W), x(X), y(Y), z(Z) {}
S��Ԫ�� &S��Ԫ��::operator *=(const float &a) {
	*this = *this * a;
	return *this;
}
S��Ԫ�� &S��Ԫ��::operator *=(const t���� &a) {
	*this = *this * a;
	return *this;
}
S��Ԫ�� &S��Ԫ��::operator *=(const S��Ԫ�� &a) {
	*this = *this * a;
	return *this;
}
S��Ԫ�� S��Ԫ��::operator *(const float &a) const {
	S��Ԫ�� v;
	v.w = w * a;
	v.x = x * a;
	v.y = y * a;
	v.z = z * a;
	return v;
}
S��Ԫ�� S��Ԫ��::operator *(const t���� &a) const {
	S��Ԫ�� v;
	v.w = -x * a._Val[0] - y * a._Val[1];
	v.x = w * a._Val[0] + z * a._Val[1];
	v.y = w * a._Val[1] - z * a._Val[0];
	v.z = y * a._Val[0] - x * a._Val[1];
	return v;
}
S��Ԫ�� S��Ԫ��::operator *(const S��Ԫ�� &a) const {
	S��Ԫ�� v;
	v.w = w * a.w - x * a.x - y * a.y - z * a.z;
	v.x = w * a.x + x * a.w + z * a.y - y * a.z;
	v.y = w * a.y + y * a.w + x * a.z - z * a.x;
	v.z = w * a.z + z * a.w + y * a.x - x * a.y;
	return v;
}
//ת������Ԫ��
S��Ԫ�� &S��Ԫ��::fs���嵽����(const Sŷ���� &a) {
	const auto[sp, cp] = sincos(a.m�� * 0.5f);
	const auto[sb, cb] = sincos(a.m�� * 0.5f);
	const auto[sh, ch] = sincos(a.mͷ * 0.5f);
	w = ch * cp*cb + sh * sp*sb;
	x = ch * sp*cb + sh * cp*sb;
	y = -ch * sp*sb + sh * cp*cb;
	z = -sh * sp*cb + ch * cp*sb;
	return *this;
}
S��Ԫ�� &S��Ԫ��::fs���Ե�����(const Sŷ���� &a) {
	const auto[sp, cp] = sincos(a.m�� * 0.5f);
	const auto[sb, cb] = sincos(a.m�� * 0.5f);
	const auto[sh, ch] = sincos(a.mͷ * 0.5f);
	w = ch * cp*cb + sh * sp*sb;
	x = -ch * sp*cb - sh * cp*sb;
	y = ch * sp*sb - sh * cb*cp;
	z = sh * sp*cb - ch * cp*sb;
	return *this;
}
S��Ԫ�� S��Ԫ��::fc���嵽����(const Sŷ���� &a) {
	const auto[sp, cp] = sincos(a.m�� * 0.5f);
	const auto[sb, cb] = sincos(a.m�� * 0.5f);
	const auto[sh, ch] = sincos(a.mͷ * 0.5f);
	S��Ԫ�� v;
	v.w = ch * cp*cb + sh * sp*sb;
	v.x = ch * sp*cb + sh * cp*sb;
	v.y = -ch * sp*sb + sh * cp*cb;
	v.z = -sh * sp*cb + ch * cp*sb;
	return v;
}
S��Ԫ�� S��Ԫ��::fc���Ե�����(const Sŷ���� &a) {
	const auto[sp, cp] = sincos(a.m�� * 0.5f);
	const auto[sb, cb] = sincos(a.m�� * 0.5f);
	const auto[sh, ch] = sincos(a.mͷ * 0.5f);
	S��Ԫ�� v;
	v.w = ch * cp*cb + sh * sp*sb;
	v.x = -ch * sp*cb - sh * cp*sb;
	v.y = ch * sp*sb - sh * cb*cp;
	v.z = sh * sp*cb - ch * cp*sb;
	return v;
}
//��Ԫ����ת
S��Ԫ�� &S��Ԫ��::fs��תx(float r) {
	*this *= fc��תx(r);
	return *this;
}
S��Ԫ�� &S��Ԫ��::fs��תy(float r) {
	*this *= fc��תy(r);
	return *this;
}
S��Ԫ�� &S��Ԫ��::fs��תz(float r) {
	*this *= fc��תz(r);
	return *this;
}
S��Ԫ�� &S��Ԫ��::fs��ת(const S����3 &v, float r) {
	*this *= fc��ת(v, r);
	return *this;
}
S��Ԫ�� S��Ԫ��::fc��תx(float r) {
	const float ��r = r * .5f;
	return S��Ԫ��(cos(��r), sin(��r), 0, 0);
}
S��Ԫ�� S��Ԫ��::fc��תy(float r) {
	const float ��r = r * .5f;
	return S��Ԫ��(cos(��r), 0, sin(��r), 0);
}
S��Ԫ�� S��Ԫ��::fc��תz(float r) {
	const float ��r = r * .5f;
	return S��Ԫ��(cos(��r), 0, 0, sin(��r));
}
S��Ԫ�� S��Ԫ��::fc��ת(const S����3 &v, float r) {
	assert(fabs(v.fg��С() - 1.0f) > .0001f);	//�����ǵ�λ����
	const float ��r = r * .5f;
	const float s��r = sin(��r);
	return S��Ԫ��(cos(��r), v.x * s��r, v.y * s��r, v.z * s��r);
}
void S��Ԫ��::fs��λ() {
	w = 1;
	x = y = z = 0;
}
float S��Ԫ��::fg��ת��() {
	return acos(w) * 2;
}
S��Ԫ�� S��Ԫ��::fg��() const {
	return S��Ԫ��(w, -x, -y, -z);
}
S��Ԫ�� &S��Ԫ��::fs��() {
	x = -x;
	y = -y;
	z = -z;
	return *this;
}
S��Ԫ�� &S��Ԫ��::fs�η�(const float &a) {
	return *this = this->fg�η�(a);
}
void S��Ԫ��::fs��һ() {
	const float vģ = (float)sqrt(w*w + x * x + y * y + z * z);
	if (vģ > 0.0f) {
		const float m���� = 1.0f / vģ;
		w *= m����;
		x *= m����;
		y *= m����;
		z *= m����;
	} else {
		assert(false);	//ģΪ��
		fs��λ();
	}
}
S����3 S��Ԫ��::fg��ת��() {
	float s = 1.0f - w * w;	//(sin(theta/2))^2
	if (s <= 0.0f)	//�Ƿ�λ����
		return S����3(1.0f, 0.0f, 0.0f);
	float d = 1.0f / sqrt(s);	//1/sin(theta/2)
	return S����3(x*d, y*d, z*d);
}
S��Ԫ�� S��Ԫ��::fg�η�(const float &e) const {
	if (fabs(w) > .9999f)
		return *this;
	float a = acos(w);	//a = ��ת��/2
	float aa = a * e;
	S��Ԫ�� v;
	v.w = cos(aa);
	float	mult = sin(aa) / sin(a);
	v.x = x * mult;
	v.y = y * mult;
	v.z = z * mult;
	return v;
}
S��Ԫ�� S��Ԫ��::f��ֵ(const S��Ԫ�� &q, float t) const {
	if (t <= 0.0f) return *this;
	if (t >= 1.0f) return q;
	float co = f���(q);
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
	S��Ԫ�� v;
	v.x = k0 * q.x + k1 * q1x;
	v.y = k0 * q.y + k1 * q1y;
	v.z = k0 * q.z + k1 * q1z;
	v.w = k0 * q.w + k1 * q1w;
	return v;
}
float S��Ԫ��::f���(const S��Ԫ�� &q) const {
	return w * q.w + x * q.x + y * q.y + z * q.z;
}
//=============================================================================
//�������
//=============================================================================
//������
S������::S������() :mλ��(E����λ��::e��), m����(E���귽��::e��) {}
S������::S������(E����λ�� pλ��, E���귽�� p����) : mλ��(pλ��), m����(p����) {}
const S������ cֱ������x{E����λ��::e��, E���귽��::e��};
const S������ cֱ������y{E����λ��::e��, E���귽��::e��};
const S������ c��������x{E����λ��::e��, E���귽��::e��};
const S������ c��������y{E����λ��::e��, E���귽��::e��};
//�����ʽ
S�����ʽ::S�����ʽ() :x(cֱ������x), y(cֱ������y) {}
S�����ʽ::S�����ʽ(const S������ &px, const S������ &py) : x(px), y(py) {}
const S�����ʽ cֱ������{cֱ������x, cֱ������y};
const S�����ʽ c��������{c��������x, c��������y};
//�������
C�������::C�������() :m�����С{} {}
void C�������::fs��С(float px, float py) {
	m�����С[0] = px;
	m�����С[1] = py;
}
float C�������::f����(float pi, const S������ &pif, const S������ &pof, int i) {
	const float mת������ = (pif.m���� == pof.m����) ? pi : -pi;
	const float mλ�ò� = m�����С[i] * ((int)pof.mλ�� - (int)pif.mλ��) * 0.5f;
	return mת������ + mλ�ò�;
}
S����2 C�������::f����(const S����2 &pi, const S�����ʽ &pif, const S�����ʽ &pof) {
	S����2 m���;
	m���.x = f����(pi.x, pif.x, pof.x, 0);
	m���.y = f����(pi.y, pif.y, pof.y, 1);
	return m���;
}

//�����ռ����
}	//namespace cflw::��ѧ
