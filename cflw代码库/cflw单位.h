#pragma once
#include <ratio>
//module cflw.单位
//export
namespace cflw::单位 {
enum E物理量 {
	e长度,
	e质量,
	e时间,
	e电流,
	e温度,
	e物质的量,
	e发光强度,
	e角度
};

template<E物理量 t物理量, typename t比率 = typename std::ratio<1, 1>::type, typename t存储类型 = double> class C单位 {
public:
	operator t存储类型() const {
		return m值 * (t存储类型)t比率::num / (t存储类型)t比率::den;
	}
	t存储类型 m值 = 0;
};


}