#pragma once
#include <ratio>
//module cflw.��λ
//export
namespace cflw::��λ {
enum E������ {
	e����,
	e����,
	eʱ��,
	e����,
	e�¶�,
	e���ʵ���,
	e����ǿ��,
	e�Ƕ�
};

template<E������ t������, typename t���� = typename std::ratio<1, 1>::type, typename t�洢���� = double> class C��λ {
public:
	operator t�洢����() const {
		return mֵ * (t�洢����)t����::num / (t�洢����)t����::den;
	}
	t�洢���� mֵ = 0;
};


}