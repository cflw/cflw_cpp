#pragma once
#include "cflw��ѧ.h"
namespace cflw::��ѧ {
//==============================================================================
//������ѧ����
//==============================================================================
template<typename t> int fȡ����(const t &x) {
	return (x < 0) ? -1 : (x > 0 ? 1 : 0);
}
template<typename t> const t& f���ֵ(const t &a, const t &b) {
	return a > b ? a : b;
}
template<typename t> const t& f��Сֵ(const t &a, const t &b) {
	return a < b ? a : b;
}
template<typename t> t f����(const t &ֵ, const t &��Сֵ, const t &���ֵ) {
	return (ֵ > ���ֵ) ? ���ֵ : ((ֵ < ��Сֵ) ? ��Сֵ : ֵ);
}
template<typename t> t f�ӽ�(const t &Դֵ, const t &Ŀ��ֵ, const t &�ӽ���) {
	return ((f����ֵ(Դֵ - Ŀ��ֵ) <= �ӽ���) ? Ŀ��ֵ : Դֵ);
}
template<typename t> t f��������(const t &Դֵ, const t &Ŀ��ֵ,
		const float &��ֵ���䱶��, const t &��С���� = (t)0, const t &��󽥱� = (t)9999) {
	if (Դֵ == Ŀ��ֵ) {
		return Դֵ;
	} else {
		const t v��ֵ = Ŀ��ֵ - Դֵ;
		const t v����ֵ = (t)(v��ֵ * ��ֵ���䱶��);
		const t v���ƽ���ֵ = f����<t>(f����ֵ<t>(v����ֵ), f����ֵ<t>(��С����), f����ֵ<t>(��󽥱�)) * fȡ����<t>(v��ֵ);
		const t v�ӽ�ֵ = f�ӽ�<t>(Դֵ + v���ƽ���ֵ, Ŀ��ֵ, f����ֵ<t>(��С����));
		return v�ӽ�ֵ;
	}
}
template<typename t> t f���Խ���(const t &Դֵ, const t &Ŀ��ֵ, const float &����ֵ) {
	if (Դֵ == Ŀ��ֵ) {
		return Դֵ;
	} else {
		return f�ӽ�<t>(Դֵ + (t)(����ֵ * fȡ����(Ŀ��ֵ - Դֵ)), Ŀ��ֵ, (t)����ֵ);
	}
}
template<class t> t f����(const t &pԴֵ, const t &p����) {
	const t v���� = floor(pԴֵ / p����);
	return pԴֵ - p���� * v����;
}
template<class t> bool f����ѭ��(t &pֵ, const t &p���ֵ) {
	//�ﵽ���ֵ�����㲢������
	if (pֵ >= p���ֵ) {
		pֵ -= p���ֵ;
		return true;
	} else {
		return false;
	}
}
template<typename t> t f����ֵ(const t &_) {
	return ((_ > 0) ? (_) : (-_));
}
template<typename t> std::tuple<t, t> sincos(t a) {
	return {sin(a), cos(a)};
}
//��ֵ
template<typename t> t f��ֵ(const t &a0, const t &a1, float p) {
	return a0 + (a1 - a0) * p;
}
//��
template<class t> int f��(t &a0, const t &a1) {
	const int r = floor(a0 / a1);
	a0 -= r * a1;
	return r;
}
//
template<class t> bool fͬ����(const t &a1, const t &p2) {
	return (fȡ����<t>(a1) == fȡ����<t>(p2));
}
//ƽ������
template<typename t> t fƽ��(const t &p) {
	return p * p;
}
template<typename t> t f����(const t &p) {
	return p * p * p;
}
//
template<typename t> t f����(const t &x, const t &y) {
	const t a = x / y;
	const t b = floor(a);
	const t c = a - b;
	if (c < 0.5) {
		return y * b;
	} else {
		return y * ceil(a);
	}
}
template<typename t> t fѭ��(const t &p, const t &p��С, const t &p���) {
	const t v�� = p��� - p��С;
	const t v������ = floor(p / v��);
	const t vѭ���� = ceil(p��С / v��);
	return p - v�� * (v������ - vѭ����);
}
template<typename t> t f��(const t &a, const t &b) {
	if (a >= b) {
		return a - b;
	} else {
		return b - a;
	}
}
template<typename tk, typename tv> tv f��ֵ2(const std::pair<tk, tv> &a0, const std::pair<tk, tv> &a1, const tk &a��) {
	const tk k = (a�� - a0.first) / (a1.first - a0.first);
	return f��ֵ<tv>(a0.second, a1.second, k);
}
template<typename tk, typename tv> tv f��ֵ2(const tk &a��0, const tv &aֵ0, const tk &a��1, const tv &aֵ1, const tk &a��) {
	const tk k = (a�� - a��0) / (a��1 - a��0);
	return f��ֵ<tv>(aֵ0, aֵ1, k);
}
template<typename t> t f������(const t &pб��, const t &pֱ�Ǳ�) {
	return sqrt(pб��*pб�� - pֱ�Ǳ�*pֱ�Ǳ�);
}
template<typename t> t f��������(const t &p) {
	const float v�� = floor(p);
	return (p - v�� < (t)0.5) ? v�� : (v�� + 1);
}
template<typename t> t f�������β�ֵ(const t &aС, const t &a��, float aб��, float x) {
	if (x < aб��) {
		return f��ֵ<t>(aС, a��, x / aб��);
	} else if (const float v�ұ� = 1 - aб��; x > v�ұ�) {
		return f��ֵ<t>(a��, aС, (x - v�ұ�) / aб��);
	} else {
		return a��;
	}
}
template<typename t����, typename...t����> t���� f����ƽ��(t���� &&...a����) {
	return (t����)(... + a����) / sizeof...(t����);
}
template<typename t����, typename...t����> t���� f����ƽ��(t���� &&...a����) {
	return sqrt((t����)(... * a����));
}
template<typename t����, typename...t����> t���� f����ֵ���ֵ(t���� &&...a����) {
	t���� v���ֵ = 0;
	t���� vԭֵ = 0;
	auto f = [&](const t���� &a) {
		const t���� v����ֵ = abs(a);
		if (v���ֵ < v����ֵ) {
			v���ֵ = v����ֵ;
			vԭֵ = a;
		}
	};
	(f(a����), ...);
	return vԭֵ;
}
//==============================================================================
// ���ּ�����
//==============================================================================
template<typename t> const C�Ƕȼ���<t> C�Ƕȼ���<t>::c��(360);
template<typename t> const C�Ƕȼ���<t> C�Ƕȼ���<t>::c����((t)c����);
//�Ƕȼ���
template<typename t> C�Ƕȼ���<t>::C�Ƕȼ���(const t &p�ܽ�) :
	m�ܽ�{p�ܽ�}, mƽ��{p�ܽ� / 2} {
}
template<typename t> t C�Ƕȼ���<t>::fƽ��(const t &p��1, const t &p��2) const {
	t v��1 = fȡ��(p��1);
	t v��2 = fȡ��(p��2);
	if (v��1 == v��2) {
		return v��1;
	} else if (v��1 >= v��2) {
		std::swap(v��1, v��2);
	}
	if (abs(v��2 - v��1) >= mƽ��) {
		v��2 -= m�ܽ�;
	}
	return (v��1 + v��2) / 2;
}
template<typename t> t C�Ƕȼ���<t>::fȡ��(const t &p��) const {
	return p�� - floor(p�� / m�ܽ�) * m�ܽ�;
}
template<typename t> t C�Ƕȼ���<t>::f����(const t &p��) const {
	t v�� = p�� + mƽ��;
	v�� -= floor(v�� / m�ܽ�) * m�ܽ�;
	v�� -= mƽ��;
	return v��;
}
template<typename t> t C�Ƕȼ���<t>::fȡ��(const t &p��) const {
	return p�� - floor(p�� / mƽ��) * mƽ��;
}
template<typename t> t C�Ƕȼ���<t>::f��ת����(const t &s, const t &d, const t &max) const {
	const t v�� = fȡ��(d - s);
	if (fȡ��(v��) <= max) {
		return d;
	} else {
		if (v�� > m�ܽ� / 2) {
			return s - max;
		} else {
			return s + max;
		}
	}
}
template<typename t> t C�Ƕȼ���<t>::f�н�(const t &p��1, const t &p��2) const {
	t v = p��1 - p��2;
	v = fȡ��(v);
	if (v >= mƽ��) {
		v = m�ܽ� - v;
	}
	return v;
}
template<typename t> t C�Ƕȼ���<t>::f����(const t &x, const t &y) const {
	return atan2(y, x) / ((t)c���� / m�ܽ�);
}
template<typename t> t C�Ƕȼ���<t>::f��ֵ(const t &p��1, const t &p��2, const t &p��ֵ) const {
	t v = p��2 - p��1;	//��1����2�ļн�
	v = fȡ��(v);
	if (v > mƽ��) {
		v = m�ܽ� - v;	//��üн�
		return p��1 - v * p��ֵ;
	} else {
		return p��1 + v * p��ֵ;
	}
}
}	//namespace cflw::��ѧ 
