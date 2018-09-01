#include <fstream>
#include <sstream>
#include <map>
#include "cflw文件_obj模型.h"
namespace cflw::文件::obj {
const std::map<std::wstring, void (C对象模型::*)(std::wistringstream &)> ca读取调用 = {
	{L"v", &C对象模型::f读取_顶点},
	{L"vt", &C对象模型::f读取_纹理},
	{L"vn", &C对象模型::f读取_法线},
	{L"f", &C对象模型::f读取_面},
};
size_t S面::fg结束位置() const {
	return m开始位置 + m分配数量;
}
//==============================================================================
// 对象模型
//==============================================================================
const S顶点坐标 C对象模型::c顶点坐标;
const S纹理坐标 C对象模型::c纹理坐标;
const S法线坐标 C对象模型::c法线坐标;
bool C对象模型::f打开(const std::wstring_view &a文件名) {
	std::wifstream v读文件;
	v读文件.open(a文件名.data());
	if (v读文件.fail()) {
		return false;
	}
	while (v读文件.good()) {
		std::wstring v行;
		std::getline(v读文件, v行);
		std::wistringstream v流(v行, std::ios::in);
		std::wstring v关键字;
		v流 >> v关键字;
		if (const auto &v找 = ca读取调用.find(v关键字); v找 != ca读取调用.end()) {
			(this->*(v找->second))(v流);
		}
	}
	return v读文件.eof();
}
bool C对象模型::f保存(const std::wstring_view &) {
	return false;
}
void C对象模型::f读取_顶点(std::wistringstream &a流) {
	S顶点坐标 v顶点;
	(a流 >> v顶点.x) && (a流 >> v顶点.y) && (a流 >> v顶点.z) && (a流 >> v顶点.w);
	ma顶点.push_back(v顶点);
}
void C对象模型::f读取_纹理(std::wistringstream &a流) {
	S纹理坐标 v纹理;
	(a流 >> v纹理.u) && (a流 >> v纹理.v) && (a流 >> v纹理.w);
	ma纹理.push_back(v纹理);
}
void C对象模型::f读取_法线(std::wistringstream &a流) {
	S法线坐标 v法线;
	(a流 >> v法线.x) && (a流 >> v法线.y) && (a流 >> v法线.z);
	ma法线.push_back(v法线);
}
void C对象模型::f读取_面(std::wistringstream &a流) {
	S面 v面;
	const auto f提取 = [&](S索引 &a输出)->bool {
		std::wstring v串;
		if (a流 >> v串) {
			f读取_索引(a输出, v串);
			return true;
		}
		return false;
	};
	v面.m开始位置 = ma索引.size();
	while (true) {
		S索引 v索引;
		const bool v结果 = f提取(v索引);
		if (v结果) {
			++v面.m分配数量;
			ma索引.push_back(v索引);
		} else {
			break;
		}
	}
	ma面.push_back(v面);
}
void C对象模型::f读取_索引(S索引 &a索引, const std::wstring &a串) {
	size_t v位置 = 0;
	const auto f提取 = [&](int &a输出)->bool {
		size_t v找到位置 = a串.find(L"/", v位置);
		if (v找到位置 != std::wstring::npos) {
			a输出 = std::stoi(a串.substr(v位置, v位置 - v找到位置));
			v位置 = v找到位置 + 1;
			return true;
		} else {
			a输出 = std::stoi(a串);
			return false;
		}
	};
	f提取(a索引.m顶点) && f提取(a索引.m纹理) && f提取(a索引.m法线);
}
const S顶点坐标 &C对象模型::fg顶点(const S索引 &a) const {
	if (a.m顶点 == 0) {
		return c顶点坐标;
	} else {
		return ma顶点[ft索引0(a.m顶点, ma顶点.size())];
	}
}
const S纹理坐标 &C对象模型::fg纹理(const S索引 &a) const {
	if (a.m纹理 == 0) {
		return c纹理坐标;
	} else {
		return ma纹理[ft索引0(a.m纹理, ma纹理.size())];
	}
}
const S法线坐标 &C对象模型::fg法线(const S索引 &a) const {
	if (a.m法线 == 0) {
		return c法线坐标;
	} else {
		return ma法线[ft索引0(a.m法线, ma法线.size())];
	}
}
size_t C对象模型::ft索引0(int i, size_t a数量) {
	if (i < 0) {
		return a数量 - abs(i);
	} else {
		return i - 1;
	}
}
}	//namespace cflw::文件::obj
namespace std {
size_t hash<cflw::文件::obj::S索引>::operator()(const cflw::文件::obj::S索引 &a) const noexcept {
	const auto f哈希 = std::hash<int>();
	const size_t v0 = f哈希(a.m顶点);
	const size_t v1 = f哈希(a.m纹理);
	const size_t v2 = f哈希(a.m法线);
	return v0 ^ (v1 << 1) ^ (v2 << 2);
}
}	//namespace std