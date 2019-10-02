#pragma once
#include <numeric>
#include <utility>
#include <algorithm>
namespace cflw::数学::分辨率 {
//==============================================================================
// 分辨率函数
//==============================================================================
//组合整数
constexpr int f组合(int a宽, int a高) {
	return a宽 * 0x10000 + a高;
}
constexpr int f组合(std::pair<int, int> a) {
	return f组合(a.first, a.second);
}
//分解整数
constexpr int f分解宽(int a) {
	return a / 0x10000;
}
constexpr int f分解高(int a) {
	return a % 0x10000;
}
constexpr std::pair<int, int> f分解(int a) {
	return std::make_pair(f分解宽(a), f分解高(a));
}
//比例约分
constexpr std::pair<int, int> f比例(std::pair<int, int> a) {
	const int v = std::gcd(a.first, a.second);
	return std::make_pair(a.first / v, a.second / v);
}
constexpr std::pair<int, int> f比例(int a) {
	const std::pair<int, int> v分解 = f分解(a);
	return f比例(v分解);
}
//计算比例,原分辨率中比例较小边与目标相同,较大边比目标大
constexpr std::pair<float, float> f小边相同(std::pair<int, int> a原, std::pair<int, int> a目标) {
	const float v原比例 = (float)a原.first / (float)a原.second;
	const float v目标比例 = (float)a目标.first / (float)a目标.second;
	if (v原比例 > v目标比例) {
		return {v原比例 * a目标.second, a目标.second};
	} else if (v原比例 < v目标比例) {
		return {a目标.first, a目标.first / v原比例};
	} else {
		return {a目标.first, a目标.second};
	}
}
//==============================================================================
// 分辨率结构
//==============================================================================
struct S分辨率 {
	int m宽 = 0;
	int m高 = 0;
	constexpr S分辨率() = default;
	constexpr S分辨率(int a组合):
		m宽(f分解宽(a组合)), m高(f分解高(a组合)) {
	}
	constexpr S分辨率(int a宽, int a高):
		m宽(a宽), m高(a高) {
	}
	constexpr S分辨率 operator *(int a倍数) const {
		return S分辨率(m宽 * a倍数, m高 * a倍数);
	}
	constexpr S分辨率 operator /(int a除数) const {
		return S分辨率(m宽 / a除数, m高 / a除数);
	}
	constexpr S分辨率 f比例() const {
		const int v最大公约数 = std::gcd(m宽, m高);
		return *this / v最大公约数;
	}
	constexpr float fg缩放(const S分辨率 &a原始) const {
		return std::min((float)m宽 / (float)a原始.m宽, (float)m高 / (float)a原始.m高);
	}
};
//==============================================================================
// 分辨率枚举
//==============================================================================
#define 分辨率(a宽, a高) e##a宽##x##a高 = f组合(a宽, a高)
enum E分辨率 {
	//4:3
	分辨率(800, 600),
	分辨率(960, 720),
	分辨率(1024, 768),
	分辨率(1280, 960),
	//16:9
	分辨率(1280, 720),
	分辨率(1366, 768),
	分辨率(1440, 900),
	分辨率(1920, 1080),	//1080p
	分辨率(2560, 1440),	//2k
	分辨率(3840, 2160),	//4k
	分辨率(7680, 4320),	//8k
	//3:2
	分辨率(1800, 1200),	//surface go
	分辨率(2160, 1440),	//surface pro3
	分辨率(2736, 1824),	//surface pro4
	分辨率(3000, 2000),	//surface book 13.5英寸
	分辨率(3240, 2160),	//surface book 15英寸
};
#undef 分辨率
}	//namespace cflw::数学::分辨率