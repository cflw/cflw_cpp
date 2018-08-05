#pragma once
#include <vector>
#include <chrono>
#include <string>
#include <tuple>
namespace cflw::���� {
//==============================================================================
// �����
//==============================================================================
class C����� {
public:
	unsigned long a;		//���������a
	unsigned long b;		//���������b
	unsigned long r;		//�ϴμ�����
	static const unsigned long max;	//��������ֵ
	C�����();		//���캯��
	void f������(const unsigned long &);
	void f����();	//����һ�������
	unsigned long f����();
	template<class t> t f����(const t &, const t &);
	bool f����(const float &);
};
//==============================================================================
// �ƴ���,�������
//==============================================================================
class C�ƴ��� {
public:
	int v��� = 0;
	int v���� = 0;
	C�ƴ���() = default;
	void f����(int);
	bool f�δ�();
};
//==============================================================================
// �ı��༩
//==============================================================================
class C�ı� {
public:
	typedef std::wstring t�ַ���;
	template<typename t1, typename t2> static inline t2 fת��(t1);
	template<typename t> static t�ַ��� f����_�ı�(t);
	template<typename t> static t�ַ��� f������_�ı�(t);
	template<typename t> static t f�ı�_����(const t�ַ��� &);
	template<typename t> static t f�ı�_������(const t�ַ��� &);
	static t�ַ��� f����_ʮ������(const void *, size_t);
	static std::tuple<std::byte*, size_t> fʮ������_����(const t�ַ��� &);	//�ǵ�ɾ��ָ��,����������ָ��
	static bool fw����(const t�ַ��� &);
	static int f����(const t�ַ��� &, const t�ַ��� &, int);
	static t�ַ��� f��Ч����(const t�ַ��� &, int);
	static t�ַ��� fС��λ��(const t�ַ��� &, int);
};
//==============================================================================
// ���һ�����ݵ��ֽ�����
//==============================================================================
//��������
class C���� {
public:
	unsigned char *mָ�� = nullptr;
	unsigned int m��С = 0;
	C����() = default;
	C����(const C���� &);
	C����(unsigned int a��С);
	~C����();
	bool f�½�(unsigned int a��С);
	void fɾ��();
	void f����(void *pָ��, unsigned int a��С);
	void f����(const C���� &a����);
	unsigned char *&fg����();
	unsigned int fg��С();
};
//��ʱ�ռ�,���ڴ�õ��Ŀռ����ǡ���Ҫ�ռ�
template<typename t> class C�ռ� {
public:
	t *mָ�� = nullptr;
	unsigned int m�������� = 0;
	unsigned int m��Ҫ���� = 0;
	C�ռ�() = default;
	~C�ռ�();
	t *f����(unsigned int);
	//����
	C�ռ�(const C�ռ� &) = delete;
	C�ռ�(C�ռ� &&) = delete;
	C�ռ� &operator =(const C�ռ� &) = delete;
	C�ռ� &operator =(C�ռ� &&) = delete;
};
//==============================================================================
// λ��С,λָ�� ��ȷ��λ�����ݲ���
//==============================================================================
struct Sλ��С {
	int v�ֽ�;
	int vλ;
	Sλ��С(int, int = 0);
	Sλ��С &operator +=(const Sλ��С &);
	Sλ��С operator +(const Sλ��С &) const;
	operator int() const;
};
class Cλָ�� {
private:
	void *vָ��;
	Sλ��С vƫ��;
public:
	Cλָ��();
	Cλָ��(void *);
	Cλָ��(void *, int);
	Cλָ�� &fsָ��(void *, int);
	void f��(void *, const Sλ��С &);
	void f��(const Cλָ�� &, const Sλ��С &);
	void fд(void *, const Sλ��С &);
	void fд(const Cλָ�� &, const Sλ��С &);
	Cλָ�� &fƫ��(const Sλ��С &);
	static void f�ڴ渴��(const Cλָ�� &, const Cλָ�� &, const Sλ��С &);
	static void f�ڴ渴��(void *, int, void *, int, int);
	static unsigned long fȡ����(void *, int, int);
	static void f������(void *, int, unsigned long);
};
//==============================================================================
// ��
//==============================================================================
template<typename t>
class C�� {
public:
	class C�ڵ� {
	public:
		t mֵ = {};
		std::unique_ptr<std::vector<C�ڵ�>> mҶ;
		C�ڵ�() = default;
		C�ڵ�(const t &, std::unique_ptr<std::vector<C�ڵ�>> && = nullptr);
	};
	typedef std::vector<C�ڵ�> tҶ;
	std::vector<C�ڵ�> mҶ;
	C��() = default;
};
}	//namespace cflw::����
#include "cflw����.inl"