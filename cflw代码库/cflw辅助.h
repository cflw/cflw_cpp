#pragma once
#include <assert.h>
#include <memory>
#include <utility>
#ifdef _DEBUG
constexpr bool c���� = true;
#else
constexpr bool c���� = false;
#endif
namespace cflw::���� {
//ɾ��ָ��
template<typename t> inline void fɾ��(t *&p) {
	if (p) {
		delete p;
		p = nullptr;
	}
}
//ɾ������
template<typename t> inline void fɾ������(t *&p) {
	if(p) {
		delete[] p;
		p = nullptr;
	}
}
//ǿ��ɾ��
template<typename t> inline void fǿ��ɾ��(t *&p) {
	delete p;
	p = nullptr;
}
//ȡ����Ԫ������
template<typename t> inline size_t f��������(const t &) {
	return sizeof(t) / sizeof(**(t*)nullptr);
}
//�Ƿ��޷�������
template<typename t> inline bool fi�޷���(const t&) {
	return (t)-1 > 0;
}
//λ����
template <typename t> inline t fλ��ֵ(const t &Դֵ, const t &�޸�λ, const unsigned char &ֵ) {
	return (ֵ) ? (Դֵ | �޸�λ) : (Դֵ & (~�޸�λ));
}
template <typename t> inline t fλ�ж�(const t &Դֵ, const t &�ж�λ) {
	return Դֵ & �ж�λ;
}
//�ڴ����
template<typename t> inline void f����(t &p) {
	memset((void*)&p, 0, sizeof(p));
}
//�Ƚ�2��ֵ������������Ѻ��渳��ǰ��
template<typename t> inline bool f������ֵ(t &p0, const t &p1) {
	if (p0 != p1) {
		p0 = p1;
		return true;
	}
	return false;
}
}	//namespace cflw::����
