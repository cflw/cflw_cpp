#pragma once
#include <vector>
#include <string_view>
#include <optional>
namespace cflw::文件::obj {
struct S顶点坐标 {
	float x = 0, y = 0, z = 0, w = 0;
};
struct S纹理坐标 {
	float u = 0, v = 0, w = 0;
};
struct S法线坐标 {
	float x = 0, y = 0, z = 0;
};
struct S索引 {
	//注意：obj的索引从1开始
	int m顶点 = 0, m纹理 = 0, m法线 = 0;
};
struct S面 {
	size_t m开始位置 = 0, m数量 = 0;	//索引
	size_t fg结束位置() const;
};
class C对象模型 {
public:
	static const S顶点坐标 c顶点坐标;
	static const S纹理坐标 c纹理坐标;
	static const S法线坐标 c法线坐标;
	bool f打开(const std::wstring_view &);
	bool f保存(const std::wstring_view &);
	void f读取_顶点(std::wistringstream &);
	void f读取_纹理(std::wistringstream &);
	void f读取_法线(std::wistringstream &);
	void f读取_面(std::wistringstream &);
	static void f读取_索引(S索引 &, const std::wstring &);
	const S顶点坐标 &fg顶点(const S索引 &) const;
	const S纹理坐标 &fg纹理(const S索引 &) const;
	const S法线坐标 &fg法线(const S索引 &) const;
	static size_t ft索引0(int 索引, size_t 数量);
	std::vector<S顶点坐标> ma顶点;
	std::vector<S纹理坐标> ma纹理;
	std::vector<S法线坐标> ma法线;
	std::vector<S索引> ma索引;
	std::vector<S面> ma面;
};
}	//namespace cflw::文件::obj
namespace std {
template<>
struct hash<cflw::文件::obj::S索引> {
	size_t operator()(const cflw::文件::obj::S索引 &) const noexcept;
};
}