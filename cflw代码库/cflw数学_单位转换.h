#pragma once
#ifndef ͷ�ļ�_cflw��ѧ_��λת��
#define ͷ�ļ�_cflw��ѧ_��λת��
#include <initializer_list>
namespace cflw {
namespace ��ѧ {
class Cת�����ӱ� {
public:
	Cת�����ӱ�(const std::initializer_list<double> &p�б�) :
		v��С{p�б�.size()},
		v����{new double[v��С * v��С]} {
		int i = 0;
		for (const double &x : p�б�) {
			int j = 0;
			for (const double &y : p�б�) {
				v����[i + j] = y / x;
				++j;
			}
			i += v��С;
		}
	}
	Cת�����ӱ�(const Cת�����ӱ� &) = delete;
	Cת�����ӱ�(Cת�����ӱ� &&) = delete;
	~Cת�����ӱ�() {
		delete[] v����;
	}
	template<typename t>
	double operator()(const t &x, const t &y) const {
		static_assert(std::is_enum<t>::value, "������ö������");
		const int vx = static_cast<int>(x);
		assert(vx < v��С);
		const int vy = static_cast<int>(y);
		assert(vy < v��С);
		return v����[vx * v��С + vy];
	}
	template<typename t��λ, typename t��ֵ = double>
	t��ֵ operator()(const t��λ &x, const t��λ &y, const t��ֵ &p��ֵ) const {
		return static_cast<t��ֵ>(operator()(x, y)) * p��ֵ;
	}
private:
	size_t v��С = 0;
	double *v���� = nullptr;
};
extern const Cת�����ӱ� f�Ƕ�ת��;
extern const Cת�����ӱ� fʱ��ת��;
extern const Cת�����ӱ� f����ת��;
extern const Cת�����ӱ� f����ת��;
extern const Cת�����ӱ� f����ת��;
//extern const Cת�����ӱ� f�¶�ת��;
extern const Cת�����ӱ� f����ת��;
enum class E�Ƕ� {
	e��,	//�ܽǣ�360
	e��,
	e��,
	e����,	//�ܽǣ�c����
};
enum class Eʱ�� {
	e����,
	e��,
	e��,
	eʱ,
	e��,
	e��,
	e��,
	e����,
};
enum class E���� {
	e����,
	e����,
	e����,
	e��,
	eǧ��,
};
enum class E���� {
	e����,	//mg
	e��,	//g
	e��,
	eǧ��,	//kg
	e��,	//t
};
enum class E���� {
	e��,
	eĦ��,	//mol
};
enum class E�¶� {
	e���϶�,	//C
	e���϶�,	//F
	e���϶�,	//K
	e���϶�,	//Ra
	e���϶�,	//Re
};
enum class E���� {
	e�����,
	e��Ԫ,
	eŷԪ,
	e��Ԫ
};
}}	//�����ռ����
#endif