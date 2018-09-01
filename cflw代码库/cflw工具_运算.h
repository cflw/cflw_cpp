#pragma once
#include <algorithm>
namespace cflw::���� {
template<typename t, typename tF = std::hash<t>>
struct F��ϣ��� {
	bool operator()(const t &a, const t &b) const {
		auto vf = tF();
		return vf(a) == vf(b);
	}
};
//�����Լ�
template<typename t>
t &f����(t &a) {
	++a;
	return a;
}
template<typename t>
t &f�Լ�(t &a) {
	--a;
	return a;
}
template<typename t>
struct F���� {
	t &operator()(t &a) const {
		++a;
		return a;
	}
};
template<typename t>
struct F�Լ� {
	t &operator()(t &a) const {
		--a;
		return a;
	}
};
//ѭ��
template<typename t>
t fѭ��(const t &a��ʼ, const t &a����, const t &a��ǰ) {
	if (a��ǰ < a��ʼ) {
		return a���� - 1;
	} else if (a��ǰ >= a����) {
		return a��ʼ;
	} else {
		return a��ǰ;
	}
}
template<typename t>
struct Fѭ�� {
	Fѭ��(t a��ʼ, t a����):
		m��ʼ(a��ʼ), m����(a����) {
	}
	t operator()(const t &a) const {
		return fѭ��(m��ʼ, m����, a);
	}
	t m��ʼ, m����;
};
//ѭ�������Լ�
template<typename t>
t &fѭ������(const t &a��ʼ, const t &a����, t &a��ǰ) {
	if (a��ǰ >= a���� - 1) {
		return a��ǰ = a��ʼ;
	} else {
		return ++a��ǰ;
	}
}
template<typename t>
t &fѭ���Լ�(const t &a��ʼ, const t &a����, t &a��ǰ) {
	if (a��ǰ <= a��ʼ) {
		return a��ǰ = a���� - 1;
	} else {
		return --a��ǰ;
	}
}
}	//namespace cflw::����