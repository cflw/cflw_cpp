#pragma once
#include <algorithm>
namespace cflw::Ëã·¨ {
template<typename t, typename tF = std::hash<t>>
struct F¹şÏ£ÏàµÈ {
	bool operator()(const t &a, const t &b) {
		auto vf = tF();
		return vf(a) == vf(b);
	}
};
}