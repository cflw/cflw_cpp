#pragma once
#include <algorithm>
namespace cflw::�㷨 {
template<typename t, typename tF = std::hash<t>>
struct F��ϣ��� {
	bool operator()(const t &a, const t &b) {
		auto vf = tF();
		return vf(a) == vf(b);
	}
};
}