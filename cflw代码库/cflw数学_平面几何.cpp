#include <assert.h>
#include "cflw��ѧ.h"
#include "cflw��ѧ_ƽ�漸��.h"
#include "cflw��ѧ_��������.h"
namespace cflw::��ѧ {
//=============================================================================
//��״����
//=============================================================================
//ɢ���Ĳ���
bool fԲ���ཻ�ж�(const S����2 &a����, float a�뾶, const S����2 &b����, float b�뾶) {
	const float m���� = a����.f�������(b����);
	const float m�뾶�� = a�뾶 + b�뾶;
	return m���� <= m�뾶��;
}
bool fԲ����ת�����ཻ�ж�(const S����2 &a����, float a�뾶, const S����2 &b����, const S����2 &b��ߴ�, float b����) {
	S����2 vԲ������ = a���� - b����;	//����������Ϊԭ��
	vԲ������ = vԲ������.f��תr(-b����);	//���Ѿ�����ת�Ƕȵ���Ϊ0��,����תԲ������
	vԲ������ = f����ֵ<S����2>(vԲ������);	//�����ж�ȫ���ӵ���һ����
	//����ʼ�ж�	//��һ�ѱ���,���ڽ�ʡ����ʱ��
	const float vx����� = b��ߴ�.x + a�뾶;
	const float vy����� = b��ߴ�.y + a�뾶;
	if (vԲ������.x <= vx����� && vԲ������.y <= vy�����) {
		//��Բ��x�����y�����Ƿ��ھ�����	//�������ཻ
		if (vԲ������.x > b��ߴ�.x && vԲ������.y > b��ߴ�.y) {
			//�ھ��α߳���
			vԲ������ -= b��ߴ�;
			return vԲ������.fg��С() <= a�뾶;	//�ھ��νǰ뾶��
		} else {
			return true;	//�ڱ߳���Ե������
		}
	} else {
		return false;	//û���ཻ
	}
}
//�������
bool f�����ص��ж�(float *a1, float *a2, int pv) {
	for (int i = 0; i != pv; ++i) {
		if (a1 != a2) {
			return false;
		}
	}
	return true;
}
//
bool f�����߶��ཻ�ж�(const S����2 &a��, const S�߶�2 &p��) {
	S����2 v��[2] = {p��.m��[0] - a��, p��.m��[1] - a��};
	if (v��[0].x * v��[1].x > 0) {
		return false;
	}
	return v��[0].x * v��[1].y == v��[0].y * v��[1].x;
}
bool f����Բ���ཻ�ж�(const S����2 &a����, const SԲ�� &aԲ��) {
	return (a���� - aԲ��.m����).fg��С() <= aԲ��.m�뾶;
}
bool f������ת�����ཻ�ж�(const S����2 &a����, const S��ת���� &a����) {
	const S����2 v = (a���� - a����.m����).f��תr(-a����.m����);
	return (abs(v.x) <= a����.m��ߴ�.x && abs(v.y) <= a����.m��ߴ�.y);
}
bool fԲ���ཻ�ж�(const SԲ�� &aԲ��1, const SԲ�� &aԲ��2) {
	return fԲ���ཻ�ж�(aԲ��1.m����, aԲ��1.m�뾶, aԲ��2.m����, aԲ��2.m�뾶);
}
bool fԲ����ת�����ཻ�ж�(const SԲ�� &aԲ��, const S��ת���� &a����) {
	return fԲ����ת�����ཻ�ж�(aԲ��.m����, aԲ��.m�뾶, a����.m����, a����.m��ߴ�, a����.m����);
}
bool fԲ���߶��ཻ�ж�(const SԲ�� &aԲ��, const S�߶�2 &p�߶�) {
	S�߶�2 v�߶� = p�߶�;
	v�߶�.fsƽ��(-aԲ��.m����);
	if (v�߶�.m��[0].fg��С() <= aԲ��.m�뾶) {
		return true;
	}
	if (v�߶�.m��[1].fg��С() <= aԲ��.m�뾶) {
		return true;
	}
	v�߶�.fs��תr(-p�߶�.fg����r() + (float)c���);
	if (fͬ����(v�߶�.m��[0].y, v�߶�.m��[1].y)) {
		return false;
	} else {
		if (f����ֵ(v�߶�.m��[0].x) <= aԲ��.m�뾶) {
			return true;
		}
	}
	return false;
}
bool fԲ�������ཻ�ж�(const SԲ�� &aԲ��, const S����2 &a����) {
	const S����2 m��Ծ��� = a����.f��Ծ���(aԲ��.m����);
	if (m��Ծ���.x < 0) {
		return m��Ծ���.y <= aԲ��.m�뾶;
	} else {
		return a����.m����.f�������(aԲ��.m����) <= aԲ��.m�뾶;
	}
}
bool fԲ����ת��Բ�ཻ�ж�(const SԲ�� &aԲ��, const S��ת��Բ &a��Բ) {
	S����2 mԲ���� = aԲ��.m����.f��תr(-a��Բ.m����);
	const float aƽ�� = a��Բ.m�뾶.x * a��Բ.m�뾶.x;
	const float bƽ�� = a��Բ.m�뾶.y * a��Բ.m�뾶.y;
	const float yƽ�� = (aƽ�� - aԲ��.m�뾶*aԲ��.m�뾶) / aƽ�� * bƽ��;
	return yƽ�� >= 0;
}
bool fԲ��ֱ���ཻ�ж�(const SԲ�� &aԲ��, const Sֱ�߷��� &aֱ��) {
	return aֱ��.f�������(aԲ��.m����) <= aԲ��.m�뾶;
}
bool f��ת�����ཻ�ж�(const S��ת���� &a1, const S��ת���� &a2) {
	//�����Ƿ�̫Զ��̫��
	const float v���� = (a1.m���� - a2.m����).fg��С();
	if (v���� > a1.fg��Խ��߳�() + a2.fg��Խ��߳�())
		return false;	//̫Զ
	if (v���� <= a1.fg�̰��᳤() + a2.fg�̰��᳤())
		return true;	//̫��
	//��þ������ж���
	const S����2 v����[2][4] = {
		{a1.fg��(1, 1), a1.fg��(1, -1), a1.fg��(-1, 1), a1.fg��(-1, -1)},
		{a2.fg��(1, 1), a2.fg��(1, -1), a2.fg��(-1, 1), a2.fg��(-1, -1)}
	};
	auto f0 = [&v����](const S����2 &a��1, const S����2 &a��2)->bool {
		S�߶�2 v�߶�1{a��1, a��2};
		auto f1 = [&v�߶�1](const S����2 &a��1, const S����2 &a��2)->bool {
			S�߶�2 v�߶�2{a��1, a��2};
			return f�߶��ཻ�ж�(v�߶�1, v�߶�2);
		};
		if (f1(v����[1][0], v����[1][1])) return true;
		if (f1(v����[1][1], v����[1][2])) return true;
		if (f1(v����[1][2], v����[1][3])) return true;
		if (f1(v����[1][3], v����[1][0])) return true;
		return false;
	};
	if (f0(v����[1][0], v����[1][1])) return true;
	if (f0(v����[1][1], v����[1][2])) return true;
	if (f0(v����[1][2], v����[1][3])) return true;
	if (f0(v����[1][3], v����[1][0])) return true;
	return false;
}
bool f��ת�����߶��ཻ�ж�(const S��ת���� &a����, const S�߶�2 &p�߶�) {
	if (f������ת�����ཻ�ж�(p�߶�.m��[0], a����)) return true;
	if (f������ת�����ཻ�ж�(p�߶�.m��[1], a����)) return true;
	const S����2 v����[4] = {a����.fg��(1, 1), a����.fg��(1, -1), a����.fg��(-1, 1), a����.fg��(-1, -1)};
	auto f = [&p�߶�](const S����2 &a��1, const S����2 &a��2)->bool {
		S�߶�2 m�߶�{a��1, a��2};
		return f�߶��ཻ�ж�(p�߶�, m�߶�);
	};
	if (f(v����[0], v����[1])) return true;
	if (f(v����[1], v����[2])) return true;
	if (f(v����[2], v����[3])) return true;
	if (f(v����[3], v����[0])) return true;
	return false;
}
bool f��ת���������ཻ�ж�(const S��ת���� &a����, const S����2 &a����) {
	const S����2 v����[4] = {a����.f��Ծ���(a����.fg��(1, 1)), a����.f��Ծ���(a����.fg��(-1, 1)),
		a����.f��Ծ���(a����.fg��(-1, -1)), a����.f��Ծ���(a����.fg��(1, -1))};
	auto f = [](const S����2 &a1, const S����2 &a2)->bool {
		if (a1.x < 0 && a2.x < 0)
			return false;	//���㶼�ں���
		if (fͬ����(a1.y, a2.y))
			return false;	//����ͬ��
		if (a1.x >= 0 && a2.x >= 0)
			return true;	//���㶼��ǰ��
		Sֱ�߷��� mֱ�� = Sֱ�߷���::fc����(a1, a2);
		return mֱ��.f��x(0) >= 0;
	};
	if (f(v����[0], v����[1])) return true;
	if (f(v����[1], v����[2])) return true;
	if (f(v����[2], v����[3])) return true;
	if (f(v����[3], v����[0])) return true;
	return false;
}
bool f�߶��ཻ�ж�(const S�߶�2 &a1, const S�߶�2 &a2) {
	//���㷶Χ
	const S����2 v1���(std::max<float>(a1.m��[0].x, a1.m��[1].x), std::max<float>(a1.m��[0].y, a1.m��[1].y));
	const S����2 v1��С(std::min<float>(a1.m��[0].x, a1.m��[1].x), std::min<float>(a1.m��[0].y, a1.m��[1].y));
	const S����2 v2���(std::max<float>(a2.m��[0].x, a2.m��[1].x), std::max<float>(a2.m��[0].y, a2.m��[1].y));
	const S����2 v2��С(std::min<float>(a2.m��[0].x, a2.m��[1].x), std::min<float>(a2.m��[0].y, a2.m��[1].y));
	if (v1���.x < v2��С.x) return false;
	if (v2���.x < v1��С.x) return false;
	if (v1���.y < v2��С.y) return false;
	if (v2���.y < v1��С.y) return false;
	float m��Χ[2];	//[0]��ʾ��,[1]��ʾ��
	m��Χ[0] = std::max<float>(v1��С.x, v2��С.x);
	m��Χ[1] = std::min<float>(v1���.x, v2���.x);
	//����ֱ�߷���
	Sֱ�߷��� vֱ��[2] = {
		Sֱ�߷���::fc����(a1.m��[0], a1.m��[1]),
		Sֱ�߷���::fc����(a2.m��[0], a2.m��[1])
	};
	if (vֱ��[0].fƽ��(vֱ��[1]))
		return false;
	auto f�߶�ƽ��y��ʱ�ж� = [](const S�߶�2 &aƽ��y��, const S�߶�2 &a����)->bool {
		assert(aƽ��y��.m��[0].x == aƽ��y��.m��[1].x);
		const float vx�� = a����.m��[0].x - a����.m��[1].x;
		const float mλ�� = (aƽ��y��.m��[0].x - a����.m��[1].x) / vx��;
		const float vy�� = a����.m��[0].y - a����.m��[1].y;
		const float vy = a����.m��[1].y + mλ�� * vy��;
		const float m�ϵ� = std::max<float>(aƽ��y��.m��[0].y, aƽ��y��.m��[1].y);
		const float m�µ� = std::min<float>(aƽ��y��.m��[0].y, aƽ��y��.m��[1].y);
		return vy >= m�µ� && vy <= m�ϵ�;
	};
	if (vֱ��[0].a == 0)
		if (f�߶�ƽ��y��ʱ�ж�(a1, a2))
			return true;
	if (vֱ��[1].a == 0)
		if (f�߶�ƽ��y��ʱ�ж�(a2, a1))
			return true;
	//���㹫�������ཻ
	const float m��[2][2] = {{vֱ��[0].f��y(m��Χ[0]), vֱ��[1].f��y(m��Χ[0])},
	{vֱ��[0].f��y(m��Χ[1]), vֱ��[1].f��y(m��Χ[1])}};
	if (m��[0][0] == m��[0][1]) return true;
	if (m��[1][0] == m��[1][1]) return true;
	return (m��[0][0] > m��[0][1]) != (m��[1][0] > m��[1][1]);
}
bool f�߶��������ཻ�ж�(const S�߶�2 &p�߶�, const S������ &p������) {
	for (int i = 0; i != 3; ++i) {
		if (f�߶��ཻ�ж�(p�߶�, p������.fg��(i)))
			return true;
	}
	return false;
}
bool f��ת��Բ�ཻ�ж�(const S��ת��Բ &a1, const S��ת��Բ &a2) {
	//�ж��Ƿ���Բ
	const SԲ�� vԲ1(a1.m����, a1.m�뾶.x);
	const SԲ�� vԲ2(a1.m����, a1.m�뾶.x);
	if (a1.fwԲ()) {
		if (a2.fwԲ())
			return fԲ���ཻ�ж�(vԲ1, vԲ2);
		else
			return fԲ����ת��Բ�ཻ�ж�(vԲ1, a2);
	} else if (a2.fwԲ()) {
		return fԲ����ת��Բ�ཻ�ж�(vԲ2, a1);
	} else {

	}
	//��δ��
	return false;
}
bool f�������ཻ�ж�(const S������ &a1, const S������ &a2) {
	const S�߶�2 v1[3] = {a1.fg��(0), a1.fg��(1), a1.fg��(2)};
	const S�߶�2 v2[3] = {a2.fg��(0), a2.fg��(1), a2.fg��(2)};
	for (int i = 0; i != 3; ++i) {
		for (int j = 0; j != 2; ++i) {
			if (f�߶��ཻ�ж�(v1[i], v2[j]))
				return true;
		}
	}
	return false;
}
//=============================================================================
// Բ��
//=============================================================================
SԲ��::SԲ��(void) :
	m����(),
	m�뾶(0) {
}
SԲ��::SԲ��(const S����2 &p����, const float &p�뾶) :
	m����(p����),
	m�뾶(p�뾶) {
}
S����2 SԲ��::fȡ��r(const float &r) const {
	S����2 v = S����2::fc����r(m�뾶, r);
	v += m����;
	return v;
}
S����2 SԲ��::fȡ��d(const float &d) const {
	return fȡ��r(d * (float)c�ȵ�����);
}
S����2 SԲ��::f��������(const SԲ�� &pԲ) const {
	const float m����1 = m����.f���㷽��r(pԲ.m����);
	const S����2 m��1 = fȡ��r(m����1);
	const float m����2 = pԲ.m����.f���㷽��r(m����);
	const S����2 m��2 = pԲ.fȡ��r(m����2);
	return S����2((m��1.x + m��2.x) / 2, (m��1.y + m��2.y) / 2);
}
bool SԲ��::f�����ж�(const S����2 &p) const {
	return f����Բ���ཻ�ж�(p, *this);
}
float SԲ��::f�������߼н�r(const S����2 &a��) const {
	if (f�����ж�(a��)) {
		return 0;	//�㲻����Բ��
	}
	const float m���� = m����.f�������(a��);
	return asin(m�뾶 / m����);
}
float SԲ��::f��ֱ�����ߵ����߾���(const S����2 &a��) const {
	if (f�����ж�(a��)) {
		return m�뾶;	//�㲻����Բ��
	}
	const float m���� = m����.f�������(a��);
	const float m�н� = asin(m�뾶 / m����);
	return tan(m�н�) * m����;
}
//==============================================================================
// ����
//==============================================================================
S����::S����(const S����2 &a����, const S����2 &a��ߴ�):
	m����(a����), m��ߴ�(a��ߴ�) {
}
S���� S����::fc��������(float a��, float a��, float a��, float a��) {
	S���� v;
	v.m����.x = (a�� + a��) / 2;
	v.m����.y = (a�� + a��) / 2;
	v.m��ߴ�.x = (a�� - a��) / 2;
	v.m��ߴ�.y = (a�� - a��) / 2;
	return v;
}
S���� S����::fc����ߴ�(const S����2 &a����, const S����2 &aȫ�ߴ�) {
	return {a����, aȫ�ߴ� / 2};
}
S���� S����::fc�����ߴ�(const S����2 &a����, const S����2 &a��ߴ�) {
	return {a����, a��ߴ�};
}
//==============================================================================
// ��ת����
//==============================================================================
S��ת����::S��ת����(const S����2 &a����, const S����2 &a��ߴ�, float a����):
	m����(a����), m��ߴ�(a��ߴ�), m����(a����) {
}
S��ת���� S��ת����::fc�߶�(const S����2 &a��0, const S����2 &a��1, float a��) {
	S��ת���� v;
	v.m���� = (a��0 + a��1) / 2;
	v.m��ߴ�.x = a��0.f�������(a��1) / 2;
	v.m��ߴ�.y = a�� / 2;
	v.m���� = a��0.f���㷽��r(a��1);
	return v;
}
S��ת���� S��ת����::fc��������(float a��, float a��, float a��, float a��, float a����) {
	S��ת���� v;
	v.m����.x = (a�� + a��) / 2;
	v.m����.y = (a�� + a��) / 2;
	v.m��ߴ�.x = (a�� - a��) / 2;
	v.m��ߴ�.y = (a�� - a��) / 2;
	v.m���� = a����;
	return v;
}
S��ת���� S��ת����::fc����ߴ�(const S����2 &a����, const S����2 &aȫ�ߴ�, float a����) {
	return {a����, aȫ�ߴ� / 2, a����};
}
S��ת���� S��ת����::fc�����ߴ�(const S����2 &a����, const S����2 &a��ߴ�, float a����) {
	return {a����, a��ߴ�, a����};
}
float S��ת����::fg�ܳ�() const {
	return 4 * (m��ߴ�.x + m��ߴ�.y);
}
float S��ת����::fg���() const {
	return 4 * m��ߴ�.x * m��ߴ�.y;
}
float S��ת����::fg��Խ��߳�() const {
	return hypotf(m��ߴ�.x, m��ߴ�.y);
}
float S��ת����::fg�����᳤() const {
	return std::max<float>(m��ߴ�.x, m��ߴ�.y);
}
float S��ת����::fg�̰��᳤() const {
	return std::max<float>(m��ߴ�.x, m��ߴ�.y);
}
S����2 S��ת����::fgȫ�ߴ�() const {
	return m��ߴ� * 2;
}
bool S��ת����::f�����ж�(const S����2 &p) const {
	return f������ת�����ཻ�ж�(p, *this);
}
S����2 S��ת����::fg��(float X, float Y) const {
	S����2 v����;
	v����.x = X * m��ߴ�.x;
	v����.y = Y * m��ߴ�.y;
	v���� = v����.f��תr(m����);
	return v���� + m����;
}
bool S��ת����::f��������(std::function<bool(const S����2 &)> f) const {
	if (f(fg��(1, 1))) return true;
	if (f(fg��(1, -1))) return true;
	if (f(fg��(-1, 1))) return true;
	if (f(fg��(-1, -1))) return true;
	return false;
}
S���ھ��� S��ת����::f�����ھ���(float x, float y) {
	S����2 m���� = m����.f��������(x, y);
	return S���ھ���::fc�����ߴ�(m����, m��ߴ�);
}
//=============================================================================
// ���ھ���
//=============================================================================
S���ھ���::S���ھ���() :S���ھ���{0, 0, 0, 0} {}
S���ھ���::S���ھ���(float p��, float p��, float p��, float p��) :
	m��(p��),
	m��(p��),
	m��(p��),
	m��(p��) {}
S���ھ���::S���ھ���(const S����2 &a1, const S����2 &a2) {
	if (a1.x < a2.x) {
		m�� = a1.x;
		m�� = a2.x;
	} else {
		m�� = a2.x;
		m�� = a1.x;
	}
	if (a1.y < a2.y) {
		m�� = a1.x;
		m�� = a2.x;
	} else {
		m�� = a2.x;
		m�� = a1.x;
	}
}
S���ھ��� S���ھ���::fc�����ߴ�(const S����2 &p����, const S����2 &p��ߴ�) {
	return{p����.x - p��ߴ�.x, p����.y - p��ߴ�.y, p����.x + p��ߴ�.x, p����.y + p��ߴ�.y};
}
float S���ھ���::fg��() {
	return m�� - m��;
}
float S���ھ���::fg��() {
	return m�� - m��;
}
S����2 S���ھ���::fg����() {
	return{(m�� + m��) / 2, (m�� + m��) / 2};
}
S����2 S���ھ���::fg��ߴ�() {
	return{fg��() / 2, fg��() / 2};
}
S���ھ��� S���ھ���::f�������(float p) {
	return{p, m��, p + fg��(), m��};
}
S���ھ��� S���ھ���::f�����ϱ�(float p) {
	return{m��, p, m��, p + fg��()};
}
S���ھ��� S���ھ���::f�����ұ�(float p) {
	return{p - fg��(), m��, p, m��};
}
S���ھ��� S���ھ���::f�����±�(float p) {
	return{m��, p - fg��(), m��, p};
}
S���ھ��� S���ھ���::f��������(const S����2 &p) {
	const float m��� = fg��() / 2;
	const float m��� = fg��() / 2;
	return{p.x - m���, p.y - m���, p.x + m���, p.y + m���};
}
S���ھ��� S���ھ���::f�ƶ�(const S����2 &p) {
	return{m�� + p.x, m�� + p.y, m�� + p.x, m�� + p.y};
}
S��ת���� S���ھ���::f��ֱ�Ǿ���(float x, float y) {
	S����2 m���� = fg����();
	m���� = m����.fֱ������(x, y);
	S����2 m��ߴ� = fg��ߴ�();
	return{m����, m��ߴ�, 0};
}
//=============================================================================
// ������
//=============================================================================
S������::S������() : m��() {}
S������::S������(const S����2 &a1, const S����2 &a2, const S����2 &p3) {
	m��[0] = a1;
	m��[1] = a2;
	m��[2] = p3;
}
S����2 S������::fg��(int i) const {
	return m��[i % 3];
}
S�߶�2 S������::fg��(int i) const {
	return{fg��(i), fg��(i + 1)};
}
float S������::fg�߳�(int i) const {
	return fg��(i).f�������(fg��(i + 1));
}
float S������::fg��r(int i) const {
	const S����2 m��_ = fg��(i);
	return C�Ƕȼ���<float>::c����.f�н�(m��_.f���㷽��r(fg��(i + 1)), m��_.f���㷽��r(fg��(i + 2)));
}
float S������::fg��d(int i) const {
	return fg��r(i) * (float)c���ȵ���;
}
S����2 S������::f��׼����(const S����3 &p) const {
	const S����2 v���� = fg����();
	S����2 v0 = f��ֵ<S����2>(v����, m��[0], p.x);
	S����2 v1 = f��ֵ<S����2>(v����, m��[1], p.y);
	S����2 v2 = f��ֵ<S����2>(v����, m��[2], p.z);
	return v0 + v1 + v2;
}
S����3 S������::f��������(const S����2 &p) const {
	const S����2 v���� = fg����();
	S����3 v;
	v.x = v����.f���㷽λr(p, v����.f���㷽��r(m��[0])).x;
	v.y = v����.f���㷽λr(p, v����.f���㷽��r(m��[1])).x;
	v.z = v����.f���㷽λr(p, v����.f���㷽��r(m��[2])).x;
	return v;
}
S����2 S������::fg����() const {
	return (m��[0] + m��[1] + m��[2]) / 3;
}
S����2 S������::fg����() const {
	const float d1 = m��[1].f���(m��[2]);
	const float d2 = m��[0].f���(m��[2]);
	const float d3 = m��[1].f���(m��[0]);
	const float c1 = d2 * d3;
	const float c2 = d1 * d3;
	const float c3 = d2 * d2;
	const float c = c1 + c2 + c3;
	return f��׼����({c1 / c, c2 / c, c3 / c});
}
S����2 S������::fg����() const {
	const float l1 = fg�߳�(0);
	const float l2 = fg�߳�(1);
	const float l3 = fg�߳�(2);
	const float d = l1 + l2 + l3;
	return f��׼����({l1 / d, l2 / d, l3 / d});
}
S����2 S������::fg����() const {
	const float d1 = m��[1].f���(m��[2]);
	const float d2 = m��[0].f���(m��[2]);
	const float d3 = m��[1].f���(m��[0]);
	const float c1 = d2 * d3;
	const float c2 = d1 * d3;
	const float c3 = d2 * d2;
	const float cc = c1 + c2 + c3;
	return f��׼����({(c2 + c3)*cc, (c1 + c3)*cc, (c1 + c2)*cc});
}
SԲ�� S������::fg����Բ() const {
	SԲ�� v;
	v.m���� = fg����();
	v.m�뾶 = v.m����.f�������(f��׼����({0.5f, 0.5f, 0}));
	return v;
}
SԲ�� S������::fg���Բ() const {
	SԲ�� v;
	v.m���� = fg����();
	v.m�뾶 = v.m����.f�������(m��[0]);
	return v;
}
//=============================================================================
// �߶�2
//=============================================================================
S�߶�2::S�߶�2(void) :m��() {}
S�߶�2::S�߶�2(const S����2 &a1, const S����2 &a2) {
	m��[0] = a1;
	m��[1] = a2;
}
S�߶�2 S�߶�2::fc����(const S����2 &p0, const S����2 &a1) {
	return {p0, a1};
}
S�߶�2 &S�߶�2::fs����(const S����2 &a, const S����2 &b) {
	m��[0] = a;
	m��[1] = b;
	return *this;
}
S�߶�2 &S�߶�2::fsƽ��(const S����2 &p) {
	m��[0] += p;
	m��[1] += p;
	return *this;
}
S�߶�2 &S�߶�2::fs��תr(const float &r) {
	m��[0].fs��תr(r);
	m��[1].fs��תr(r);
	return *this;
}
S�߶�2 &S�߶�2::fs��תd(const float &d) {
	m��[0].fs��תd(d);
	m��[1].fs��תd(d);
	return *this;
}
S�߶�2 S�߶�2::fƽ��(const S����2 &p) const {
	S�߶�2 v = *this;
	v.m��[0] += p;
	v.m��[1] += p;
	return v;
}
S�߶�2 S�߶�2::f��תr(const float &r) const {
	S�߶�2 v = *this;
	v.m��[0].fs��תr(r);
	v.m��[1].fs��תr(r);
	return v;
}
S�߶�2 S�߶�2::f��תd(const float &d) const {
	S�߶�2 v = *this;
	v.m��[0].fs��תd(d);
	v.m��[1].fs��תd(d);
	return v;
}
S�߶�2 S�߶�2::f����Ե�() const {
	return {m��[1], m��[0]};
}
float S�߶�2::fg����r() const {
	return m��[0].f���㷽��r(m��[1]);
}
float S�߶�2::fg����d() const {
	return m��[0].f���㷽��d(m��[1]);
}
float S�߶�2::fgб��() const {
	return (m��[0].y - m��[1].y) / (m��[0].x - m��[1].x);
}
//=============================================================================
// ����2
//=============================================================================
S����2::S����2() : m����(), m����(0) {}
S����2::S����2(const S����2 &p����, float p����) : m����(p����), m����(p����) {}
void S����2::fs����(const S����2 &a��, const S����2 &p����) {
	m���� = a��;
	m���� = p����.fg����r();
}
void S����2::fs����(const S����2 &a1, const S����2 &a2) {
	m���� = a1;
	m���� = a1.f���㷽��r(a2);
}
float S����2::fͬ�����(const S����2 &a��)  const {
	return f��Ծ���(a��).y;
}
float S����2::f�������(const S����2 &a��)  const {
	return f��Ծ���(a��).x;
}
S����2 S����2::f��Ծ���(const S����2 &a��)  const {
	return a��.f��תr(-m����) - m����;
}
//=============================================================================
// ��Բ
//=============================================================================
S��Բ::S��Բ(const S����2 &a����, const S����2 &a�뾶):
	m����(a����), m�뾶(a�뾶) {
}
S��Բ S��Բ::fcԲ(const S����2 &a����, float a�뾶) {
	return {a����, S����2::fc��ͬ(a�뾶)};
}
bool S��Բ::fwԲ() const {
	return m�뾶.x == m�뾶.y;
}
S����2 S��Բ::fȡ��(float t) const {
	S����2 v;
	v.x = m�뾶.x * cos(t) + m����.x;
	v.y = m�뾶.y * sin(t) + m����.y;
	return v;
}
//=============================================================================
// ��Բ
//=============================================================================
S��ת��Բ::S��ת��Բ() : m����(), m�뾶(), m����(0) {}
S��ת��Բ::S��ת��Բ(const S����2 &p����, const S����2 &p�뾶, float p����) : m����(p����), m�뾶(p�뾶), m����(p����) {}
S��ת��Բ S��ת��Բ::fcԲ(const S����2 &p����, float p�뾶) {
	return {p����, {p�뾶, p�뾶}, 0};
}
bool S��ת��Բ::fwԲ() const {
	return m�뾶.x == m�뾶.y;
}
S����2 S��ת��Բ::fȡ��(float t) const {
	S����2 v;
	v.x = m�뾶.x * cos(t - m����) + m����.x;
	v.y = m�뾶.y * sin(t - m����) + m����.y;
	return v;
}
//=============================================================================
// Բ�Ǿ���
//=============================================================================
SԲ�Ǿ���::SԲ�Ǿ���() : m����(), m��ߴ�(), m�ǰ뾶() {}
SԲ�Ǿ���::SԲ�Ǿ���(const S����2 &p����, const S����2 &p��ߴ�, const S����2 &p�ǰ뾶) : m����(p����), m��ߴ�(p��ߴ�), m�ǰ뾶(p�ǰ뾶) {}


}