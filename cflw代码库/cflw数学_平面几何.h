#pragma once
#include <functional>
#include "cflw��ѧ_����.h"
namespace cflw::��ѧ {
//=============================================================================
// ����
//=============================================================================
//���ļ�
struct SԲ��;
struct S��ת����;
struct S���ھ���;
struct S������;
struct S�߶�2;
struct S����2;
struct S��ת��Բ;
struct SԲ�Ǿ���;
//=============================================================================
// ƽ�漸�νṹ����
//=============================================================================
struct SԲ�� {
	S����2 m����;
	float m�뾶;
	SԲ��();
	SԲ��(const S����2 &, const float &);
	S����2 fȡ��r(const float &����) const;
	S����2 fȡ��d(const float &����) const;
	S����2 f��������(const SԲ�� &) const;
	bool f�����ж�(const S����2 &) const;
	float f�������߼н�r(const S����2 &) const;	//����=��Բ����һ���ֱ��
	float f��ֱ�����ߵ����߾���(const S����2 &) const;	//����=��Բ��һ����Բ��ֱ��
};
struct S���� {
	S����2 m���� = S����2::c��;
	S����2 m��ߴ� = S����2::cһ;	//�ߴ��һ��
	S����() = default;
	S����(const S����2 &, const S����2 &);
	static S���� fc��������(float ��, float ��, float ��, float ��);
	static S���� fc����ߴ�(const S����2 &, const S����2 &);
	static S���� fc�����ߴ�(const S����2 &, const S����2 &);
	static S���� fc������(const S����2 &, float �߳�);
};
struct S��ת���� {
	S����2 m���� = S����2::c��;
	S����2 m��ߴ� = S����2::cһ;	//�ߴ��һ��
	float m���� = 0;
	S��ת����() = default;
	S��ת����(const S����2 &, const S����2 &, float);
	static S��ת���� fc�߶�(const S����2 &, const S����2 &, float ��� = 0);
	static S��ת���� fc��������(float ��, float ��, float ��, float ��, float ���� = 0);
	static S��ת���� fc����ߴ�(const S����2 &, const S����2 &, float ���� = 0);
	static S��ת���� fc�����ߴ�(const S����2 &, const S����2 &, float ���� = 0);
	S����2 fg��(float x, float y) const;
	float fg�ܳ�() const;
	float fg���() const;
	float fg��Խ��߳�() const;
	float fg�����᳤() const;
	float fg�̰��᳤() const;
	S����2 fgȫ�ߴ�() const;
	bool f��������(std::function<bool(const S����2 &)>) const;
	bool f�����ж�(const S����2 &) const;
	S���ھ��� f�����ھ���(float, float);
};
struct S���ھ��� {
	float m��, m��, m��, m��;
	S���ھ���();
	S���ھ���(float, float, float, float);
	S���ھ���(const S����2 &, const S����2 &);
	static S���ھ��� fc�����ߴ�(const S����2 &, const S����2 &);
	float fg��();
	float fg��();
	S����2 fg����();
	S����2 fg��ߴ�();
	S���ھ��� f�������(float);
	S���ھ��� f�����ϱ�(float);
	S���ھ��� f�����ұ�(float);
	S���ھ��� f�����±�(float);
	S���ھ��� f��������(const S����2 &);
	S���ھ��� f�ƶ�(const S����2 &);
	S��ת���� f��ֱ�Ǿ���(float, float);
};
//������
struct S������ {
	S����2 m��[3];
	S������();
	S������(const S����2 &, const S����2 &, const S����2 &);
	//��������
	S����2 fg��(int) const;
	S�߶�2 fg��(int) const;
	float fg�߳�(int) const;
	float fg��r(int) const;
	float fg��d(int) const;
	//����
	S����2 f��׼����(const S����3 &) const;
	S����3 f��������(const S����2 &) const;
	//��
	S����2 fg����() const;
	S����2 fg����() const;
	S����2 fg����() const;
	S����2 fg����() const;
	//Բ
	SԲ�� fg����Բ() const;
	SԲ�� fg���Բ() const;
};
//�߶�2
struct S�߶�2 {
	S����2 m��[2];
	S�߶�2(void);
	S�߶�2(const S����2 &, const S����2 &);
	static S�߶�2 fc����(const S����2 &, const S����2 &);
	S�߶�2 &fs����(const S����2 &, const S����2 &);
	S�߶�2 &fsƽ��(const S����2 &);
	S�߶�2 &fs��תr(const float &);
	S�߶�2 &fs��תd(const float &);
	S�߶�2 fƽ��(const S����2 &) const;
	S�߶�2 f��תr(const float &) const;
	S�߶�2 f��תd(const float &) const;
	S�߶�2 f����Ե�() const;
	float fg����r() const;
	float fg����d() const;
	float fgб��() const;
};
//����
struct S����2 {
	S����2 m����;
	float m����;
	S����2();
	S����2(const S����2 &, float);
	void fs����(const S����2 &, const S����2 &);
	void fs����(const S����2 &, const S����2 &);
	float fͬ�����(const S����2 &) const;
	float f�������(const S����2 &) const;
	S����2 f��Ծ���(const S����2 &) const;
};
//��Բ
struct S��Բ {
	S����2 m���� = S����2::c��;
	S����2 m�뾶 = S����2::cһ;
	S��Բ() = default;
	S��Բ(const S����2 &, const S����2 &);
	static S��Բ fcԲ(const S����2 &, float);
	bool fwԲ() const;
	S����2 fȡ��(float) const;
};
//��ת��Բ
struct S��ת��Բ {
	S����2 m���� = S����2::c��;
	S����2 m�뾶 = S����2::cһ;
	float m���� = 0;
	S��ת��Բ();
	S��ת��Բ(const S����2 &, const S����2 &, float);
	static S��ת��Բ fcԲ(const S����2 &, float);
	bool fwԲ() const;
	S����2 fȡ��(float) const;
};
//Բ�Ǿ���
struct SԲ�Ǿ��� {
	S����2 m����, m��ߴ�, m�ǰ뾶;
	SԲ�Ǿ���();
	SԲ�Ǿ���(const S����2 &, const S����2 &, const S����2 &);
};
//=============================================================================
// ƽ�漸�μ���
//=============================================================================
//����ɢ�����ཻ�ж�����
bool fԲ���ཻ�ж�(const S����2 &, float, const S����2 &, float);
bool fԲ����ת�����ཻ�ж�(const S����2 &, float, const S����2 &, const S����2 &, float);
//��״�ཻ�ж�,˳��:����,Բ��,����,�߶�,����,��Բ,ֱ��,������
bool f�����ص��ж�(float *, float *, int);
bool f�����߶��ཻ�ж�(const S����2 &, const S�߶�2 &);
bool f����Բ���ཻ�ж�(const S����2 &, const SԲ�� &);
bool f������ת�����ཻ�ж�(const S����2 &, const S��ת���� &);
bool fԲ���ཻ�ж�(const SԲ�� &, const SԲ�� &);
bool fԲ����ת�����ཻ�ж�(const SԲ�� &, const S��ת���� &);
bool fԲ���߶��ཻ�ж�(const SԲ�� &, const S�߶�2 &);
bool fԲ�������ཻ�ж�(const SԲ�� &, const S����2 &);
bool fԲ����ת��Բ�ཻ�ж�(const SԲ�� &, const S��ת��Բ &);
bool fԲ��ֱ���ཻ�ж�(const SԲ�� &, const Sֱ�߷��� &);
bool f��ת�����ཻ�ж�(const S��ת���� &, const S��ת���� &);
bool f��ת�����߶��ཻ�ж�(const S��ת���� &, const S�߶�2 &);
bool f��ת���������ཻ�ж�(const S��ת���� &, const S����2 &);
bool f�߶��ཻ�ж�(const S�߶�2 &, const S�߶�2 &);
bool f�߶��������ཻ�ж�(const S�߶�2 &, const S������ &);
bool f��ת��Բ�ཻ�ж�(const S��ת��Բ &, const S��ת��Բ &);
bool f�������ཻ�ж�(const S������ &, const S������ &);
//λ�ù�ϵ
int f��Բλ�ù�ϵ(const S����2 &, const SԲ�� &);
int f����ת��Բλ�ù�ϵ(const S����2 &, const S��ת��Բ &);

}