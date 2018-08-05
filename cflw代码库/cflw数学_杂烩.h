#pragma once
#include <utility>
namespace cflw::��ѧ {
//λ�ü���
template<typename t> class Cλ�ü��� {
public:	//����1"λ��":��ǰλ��	����2"����":	����ֵ:�����λ��
	static t f����(const t &λ��, const t &����);//���뵽[-����/2, ����/2]
	static t f�е���(const t &λ��, const t &����);//[0, ����]
	static t f�ҵ���(const t &λ��, const t &����);
	static t f�е���(const t &λ��, const t &����);
	static t f�ҵ���(const t &λ��, const t &����);
	static t f����(const t &λ��, const t &����);
	static t f�µ���(const t &λ��, const t &����);
	static t f�µ���(const t &λ��, const t &����);
	static t f�е���(const t &λ��, const t &����);
	static t f�е���(const t &λ��, const t &����);
	static t f�ϵ���(const t &λ��, const t &����);
	static t f�ϵ���(const t &λ��, const t &����);
};
template<typename t> class C����λ�ü��� {//����������ϵ����,δ���
public:
	static t f����(const t &λ��, const t &����);
};
//����ֵ
template<class t> struct S����ֵ {
	typedef typename std::conditional<std::is_floating_point<t>::value, t, float>::type tС��;
	t m��ǰ, m���;
	//���캯��
	S����ֵ();
	S����ֵ(const t &);
	//����
	void f���();	//��鵱ǰֵ�Ƿ񳬹����ֵ,�����,�ǰֵ=���ֵ
	void f����(const t &);	//�������õ�ǰֵ�����ֵ
	void f��();	//��ǰֵ=���ֵ
	tС�� fg�ٷֱ�() const;
};
//һ��һά�ķ�Χ
template<typename t> struct S��Χ {
	t mС, m��;
	S��Χ();
	S��Χ(const t &, const t &);
	static S��Χ fc���İ뾶(const t &����, const t &�뾶);
	t fgС() const;
	t fg��() const;
	t fg����() const;
	t fgֱ��() const;
	t fg�뾶() const;
	S��Χ &fs��(const t &);
	S��Χ &fsС(const t &);
	S��Χ &fs���İ뾶(const t &, const t &);
	S��Χ &fs����(const t &);
	S��Χ &fsֱ��(const t &);
	S��Χ &fs�뾶(const t &);
	S��Χ &fs�ƶ�(const t &);
	S��Χ &fs�ϲ�(const S��Χ &);
	bool fi��Χ��(const t &) const;
	bool fi�ཻ(const S��Χ &) const;
	S��Χ f�ϲ�(const S��Χ &) const;
};
//��Χ�任����
template<typename t> class C��Χ�任���� {
public:
	S��Χ<t> mǰ, m��;
	C��Χ�任����();
	C��Χ�任����(const S��Χ<t> &, const S��Χ<t> &);
	static t f�任����(const S��Χ<t> &, const S��Χ<t> &, const t &);
	t operator ()(const t &) const;
	t f����(const t &) const;
	t f�����(const t &) const;
};
//��ά��ż���
template<typename t> class C��ά��ż��� {
public:
	t m��;
	C��ά��ż���();
	C��ά��ż���(const t &��);
	t operator()(const t &��, const t &��) const;
	std::pair<t, t> operator()(const t &һά) const;
	static t f����һ(const t &, const t &, const t &);
	static std::pair<t, t> fһ����(const t &, const t &);
};
//����ֵ
template<typename t> struct S����ֵ {
	t m��ǰ = 0, mĿ�� = 0;
	t f���Խ���(t ֵ);
	t f��������(float ����, t ��С, t ���);
};
}	//namespace cflw::��ѧ
#include "cflw��ѧ_�ӻ�.inl"