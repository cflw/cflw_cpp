#pragma once
#include <string>
#include <fstream>
#include <vector>
#include "cflw����_ѭ��.h"
namespace cflw {
namespace �ļ� {
namespace csv {
class C��;
class Cд;
//=============================================================================
// ��
//=============================================================================
struct S�� {
	S��(std::vector<std::wstring> &);
	const std::wstring &operator[](size_t i) const;
	std::vector<std::wstring> &fe() const;
	std::vector<std::wstring> *m����;
};
class C��ѭ�� : public ����::ѭ��::Iѭ��<C��ѭ��> {
public:
	C��ѭ��(std::wifstream &);
	bool fѭ������_w����();
	S�� fѭ������_������();
private:
	std::vector<std::wstring> m����;
	std::wifstream *m�ļ�;
};
class C�� {
public:
	void f��(const std::wstring &);
	C��ѭ�� fe��();
	void fs������(bool);	//�����,fe��()������ֱ�����
private:
	bool m������ = false;
	int m�ڶ��п�ʼλ�� = 0;
	std::wifstream m�ļ�;
};
//=============================================================================
// д
//=============================================================================
class Cд {
public:
	void f��(const std::wstring &, int pģʽ = std::ios::out);
	void fs����(int);
	template<typename t> Cд &operator <<(const t &);
private:
	void fд(const std::wstring &);
};
template<typename t> Cд &Cд::operator <<(const t &p) {
	fд(std::to_wstring(p));
	return *this;
}
}	//namespace csv
}	//namespace �ļ�
}	//namespace cflw