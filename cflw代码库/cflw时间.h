#pragma once
#include <chrono>
#include <deque>
namespace cflw {
namespace ʱ�� {
//����
typedef std::chrono::duration<double> tʱ���;
typedef std::chrono::time_point<std::chrono::system_clock> tʱ���;
class C����ʱ�� {
public:
	static tʱ��� f����();
	static tʱ��� f��();
	static tʱ��� f���(const tʱ��� &, const tʱ��� &);
};
//ʱ����
class Cʱ���� {
public:
	Cʱ����() = default;
	void f����();
	void fˢ��();
	tʱ��� f����();
	tʱ��� fg���() const;
private:
	tʱ��� m�ϴ�ʱ��{C����ʱ��::f����()};
	tʱ��� m���ʱ��{C����ʱ��::f����()};
};
//��ʱ��
class C��ʱ�� {
public:
	C��ʱ��() = default;
	void f����(double ��� = 0);
	void fs���(double ���);
	bool f�δ�();
private:
	tʱ��� m����ʱ��{0};
	tʱ��� m�δ�ʱ��{0};
	tʱ��� m�ϴ�ʱ��{C����ʱ��::f����()};
};
//��֡��
class C��֡�� {
public:
	static constexpr double cȡ����Χ = 2;	//��λ:��
	C��֡��() = default;
	void f����();
	double f����();
private:
	std::deque<tʱ���> mʱ��;
	double m֡���� = 1;	//ƽ������ֵ
	int mɾ������ = 0;	//��ֹ����֡��ʱ�����
};
//���
class C��� {
public:
	C���() = default;
	void f����();
	double f��ʼ������();
	double f�ϴε�����();
private:
	tʱ��� m��ʼʱ��{C����ʱ��::f����()};
	tʱ��� m�ϴ�ʱ��{C����ʱ��::f����()};
};
//=============================================================================
}	//namespace ʱ��
}	//namespace cflw