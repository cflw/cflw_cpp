#pragma once
#include <algorithm>
namespace cflw::���� {
//��������
template<typename t> using F�� = std::plus<t>;
template<typename t> using F�� = std::minus<t>;
template<typename t> using F�� = std::multiplies<t>;
//�򵥱Ƚ�
template<typename t>
bool f����(const t &a0, const t &a1) {
	return a0 < a1;
}
template<typename t>
bool f������(const t &a0, const t &a1) {
	return a0 < a1;
}
template<typename t>
bool fС��(const t &a0, const t &a1) {
	return a0 < a1;
}
template<typename t>
bool f����(const t &a0, const t &a1) {
	return a0 > a1;
}
template<typename t>
bool fС�ڵ���(const t &a0, const t &a1) {
	return a0 <= a1;
}
template<typename t>
bool f���ڵ���(const t &a0, const t &a1) {
	return a0 >= a1;
}
template<typename t> using F���� = std::equal_to<t>;
template<typename t> using F������ = std::not_equal_to<t>;
template<typename t> using FС�� = std::less<t>;
template<typename t> using FС�ڵ��� = std::less_equal<t>;
template<typename t> using F���� = std::greater<t>;
template<typename t> using F���ڵ��� = std::greater_equal<t>;
//�߼�����
inline constexpr bool f��(bool a0, bool a1) {
	return a0 && a1;
}
inline constexpr bool f��(bool a0, bool a1) {
	return a0 || a1;
}
inline constexpr bool f��(bool a) {
	return !a;
}
//���ӱȽ�
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