#pragma once
#include <vector>
#include <string_view>
#include <optional>
namespace cflw::�ļ�::obj {
struct S�������� {
	float x = 0, y = 0, z = 0, w = 0;
};
struct S�������� {
	float u = 0, v = 0, w = 0;
};
struct S�������� {
	float x = 0, y = 0, z = 0;
};
struct S���� {
	//ע�⣺obj��������1��ʼ
	int m���� = 0, m���� = 0, m���� = 0;
};
struct S�� {
	size_t m��ʼλ�� = 0, m���� = 0;	//����
	size_t fg����λ��() const;
};
class C����ģ�� {
public:
	static const S�������� c��������;
	static const S�������� c��������;
	static const S�������� c��������;
	bool f��(const std::wstring_view &);
	bool f����(const std::wstring_view &);
	void f��ȡ_����(std::wistringstream &);
	void f��ȡ_����(std::wistringstream &);
	void f��ȡ_����(std::wistringstream &);
	void f��ȡ_��(std::wistringstream &);
	static void f��ȡ_����(S���� &, const std::wstring &);
	const S�������� &fg����(const S���� &) const;
	const S�������� &fg����(const S���� &) const;
	const S�������� &fg����(const S���� &) const;
	static size_t ft����0(int ����, size_t ����);
	std::vector<S��������> ma����;
	std::vector<S��������> ma����;
	std::vector<S��������> ma����;
	std::vector<S����> ma����;
	std::vector<S��> ma��;
};
}	//namespace cflw::�ļ�::obj
namespace std {
template<>
struct hash<cflw::�ļ�::obj::S����> {
	size_t operator()(const cflw::�ļ�::obj::S���� &) const noexcept;
};
}