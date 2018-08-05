#pragma once
#include "cflw��ѧ.h"
#include "cflw��ѧ_����.h"
namespace cflw::��ѧ {
//=============================================================================
// ����
//=============================================================================
//�����ļ�
struct S��ת����;
struct S����2;
struct S����4;
template<typename t> t f��ֵ(const t&��ʼֵ, const t&��ֵֹ, float �м�ֵ);
//���ļ�
struct S��ɫ;
struct S��ɫyuv;
struct S��Ԫ��;
struct Sŷ����;
template<> S��ɫ f��ֵ<S��ɫ>(const S��ɫ &��ʼֵ, const S��ɫ &��ֵֹ, float �м�ֵ);
template<> S��Ԫ�� f��ֵ<S��Ԫ��>(const S��Ԫ�� &, const S��Ԫ�� &, float);
//=============================================================================
// ��ɫ
//=============================================================================
//rgb��ɫϵͳ
struct S��ɫ {
	enum E��ɫֵ : unsigned int {
		e�� = 0xffffffff,
		e�� = 0x000000ff,
		e�� = 0xff0000ff,
		e�� = 0xff8000ff, 
		e�� = 0xffff00ff, 
		e�� = 0x00ff00ff, 
		e�� = 0x00ffffff, 
		e�� = 0x0000ffff, 
		e�� = 0xff00ffff, 
		e�� = 0xff8080ff
	};
	enum E��ɫֵ��ȡ : unsigned int {
		e��ȡ��,
		e��ȡ��,
		e��ȡ��,
		e��ȡ��
	};
	union {
		struct {
			float r, g, b, a;
		};
		float v[4];
	};
	//����
	static const S��ɫ c��, c��, c��, c��, c��, c��, c��, c��, c��, c��, c��;
	//���캯��
	S��ɫ();
	S��ɫ(E��ɫֵ);
	S��ɫ(float ��, float ��, float ��, float ������ = 1);
	operator unsigned long();
	static S��ɫ fc�ʺ�(float, float A = 1, float ���� = 1, float ���Ͷ� = 1);	//0~6:��Ȼ���������,ѭ��
	static S��ɫ fc����ɫ(float, float A = 1, float ���� = 1, float ���Ͷ� = 1);	//0~2:������,ѭ��
	static S��ɫ fc�ڰ�(float, float A = 1);
	static constexpr float f��ɫֵ��ȡ(E��ɫֵ, E��ɫֵ��ȡ);
	static constexpr float f��ɫֵ��ȡ_��(E��ɫֵ);
	static constexpr float f��ɫֵ��ȡ_��(E��ɫֵ);
	static constexpr float f��ɫֵ��ȡ_��(E��ɫֵ);
	static constexpr float f��ɫֵ��ȡ_��(E��ɫֵ);
	void f��ɫУ��();
	S��ɫ f�Աȶ�(const float &) const;
	S��ɫ f���Ͷ�(const float &) const;
	S��ɫ f��ɫ������(const float &) const;
	S��ɫ f͸���ȳ�(const float &) const;
	S��ɫ fȫ��ֵ(const S��ɫ &, const float &) const;
	S��ɫ f��ɫ������ֵ(const S��ɫ &, const float &) const;
	S��ɫ f���_���(const S��ɫ &) const;
	S��ɫ f���_���(const S��ɫ &) const;
	S��ɫ f���_����(const S��ɫ &) const;
	S��ɫ f���_����(const S��ɫ &) const;
	S��ɫ f���_���(const S��ɫ &) const;
	S��ɫ f���_��С(const S��ɫ &) const;
	S��ɫyuv f��yuv() const;
};
struct S��ɫyuv {
	float y, u, v;
	S��ɫ f��rgb() const;
};
//=============================================================================
// ��
//=============================================================================
struct S�� {
	enum E��Դ���� {
		e���,		//��һ�������ܷ�ɢ�Ĺ�
		e�����,	//ƽ�е���ĳһ���򴫲��Ĺ�
		e�۹��	//���ֵ�Ͳ���ƵĹ�
	}v��Դ����;
	S��ɫ m����ɫ;
	S��ɫ m����ɫ;
	S��ɫ m����ɫ;
	S����3 mλ��;	//�Է������Ч
	S����3 m����;	//�Ե����Ч
	float m��Χ;		//������Զ�ܴﵽ��·��
	float m��Χ˥����;	//�����ھ۹��
	float m����˥����[3];	//�����ڵ��Դ�۹��
	float m��Բ׶��;	//�����ھ۹��
	float m��Բ׶��;	//�����ھ۹��
	//���캯��
	S��();
};
//=============================================================================
// ����
//=============================================================================
struct S���� {
	S��ɫ m����ɫ;
	S��ɫ m����ɫ;
	S��ɫ m����ɫ;
	S��ɫ m����ɫ;
	float m���;
	S����();
};
//=============================================================================
// ���־���
//=============================================================================
struct S�������2 {
	S����2 mƽ�� = S����2::c��;
	float m��ת = 0;
	S����2 m���� = S����2::c��;
	S�������2() = default;
	S�������2(const S����2 &, const float &, const S����2 &);
	S����2 ft����2() const;
};
struct S�������3 {
	S����3 mƽ�� = S����3::c��;
	S����3 m��ת = S����3::c��;
	S����3 m���� = S����3::cһ;
	S�������3() = default;
	S�������3(const S����3 &, const S����3 &, const S����3 &);
	S����4 ft����4() const;
};
struct S��� {
	S����3 m���� = S����3::c��;
	S����3 mĿ�� = S����3::c��;
	S����3 m�Ϸ� = S����3(0, 1, 0);
	S���() = default;
	S���(const S����3 &, const S����3 &, const S����3 &);
	S����4 ft����4l() const;
	S����4 ft����4r() const;
};
struct SͶӰ {
	static constexpr float c�ӽ� = (float)��ѧ::c���;
	float m�ӽ� = c�ӽ�;
	float m�� = 640, m�� = 480;
	float m���ü��� = 1, mԶ�ü��� = 100;
	SͶӰ() = default;
	SͶӰ(float ��, float ��, float �ӽ� = c�ӽ�, float ���ü��� = 0.01f, float Զ�ü��� = 100.f);
	S����4 ft����4l() const;
	S����4 ft����4r() const;
};
struct S�ӿ� {
	S����2 m����;
	S����2 m����;
	float m��С���, m������;
	S�ӿ�();
	S�ӿ�(const S��ת���� &);
};
//=============================================================================
// ŷ����&��Ԫ��
//=============================================================================
struct Sŷ���� {
	float mͷ, m��, m��;
	Sŷ����();
	Sŷ����(float ͷ, float ��, float ��);
	void fs��λ();
	void f����();
	void fs���嵽����(const S��Ԫ�� &);
	void fs���Ե�����(const S��Ԫ�� &);
	void fs���嵽����(const S����4 &);
	void fs���絽����(const S����4 &);
};
struct S��Ԫ�� {
	float w, x, y, z;
	S��Ԫ��();
	S��Ԫ��(const float &, const float &, const float &, const float &);
	//
	S��Ԫ�� &operator *=(const float &);
	S��Ԫ�� &operator *=(const t���� &);
	S��Ԫ�� &operator *=(const S��Ԫ�� &);
	//
	S��Ԫ�� operator *(const float &) const;
	S��Ԫ�� operator *(const t���� &) const;
	S��Ԫ�� operator *(const S��Ԫ�� &) const;
	//ת��
	S��Ԫ�� &fs���嵽����(const Sŷ���� &);
	S��Ԫ�� &fs���Ե�����(const Sŷ���� &);
	static S��Ԫ�� fc���嵽����(const Sŷ���� &);
	static S��Ԫ�� fc���Ե�����(const Sŷ���� &);
	//��ת
	S��Ԫ�� &fs��תx(float);
	S��Ԫ�� &fs��תy(float);
	S��Ԫ�� &fs��תz(float);
	S��Ԫ�� &fs��ת(const S����3 &, float);	//������Ϊ����ת
	static S��Ԫ�� fc��תx(float);
	static S��Ԫ�� fc��תy(float);
	static S��Ԫ�� fc��תz(float);
	static S��Ԫ�� fc��ת(const S����3 &, float);
	//�������
	void fs��λ();	//����Ϊ��λ��Ԫ��
	void fs��һ();	//ģ=1
	float fg��ת��();	//ȡ��ת�Ƕ�
	S����3 fg��ת��();
	S��Ԫ�� fg��() const;
	S��Ԫ�� &fs��();
	S��Ԫ�� fg�η�(const float &) const;
	S��Ԫ�� &fs�η�(const float &);
	S��Ԫ�� f��ֵ(const S��Ԫ�� &, float) const;
	float f���(const S��Ԫ�� &) const;
};
//=============================================================================
// �����������
//=============================================================================
//����λ��
enum class E����λ�� {
	e��,
	e�� = e��,
	e��,
	e��,
	e�� = e��
};
//���귽��
enum class E���귽�� {
	e��,
	e�� = e��,
	e��,
	e�� = e��
};
//������
struct S������ {
	E����λ�� mλ��;
	E���귽�� m����;
	S������();
	S������(E����λ��, E���귽��);
};
extern const S������ cֱ������x;
extern const S������ cֱ������y;
extern const S������ c��������x;
extern const S������ c��������y;
//�����ʽ
struct S�����ʽ {
	S������ x, y;
	S�����ʽ();
	S�����ʽ(const S������ &, const S������ &);
};
extern const S�����ʽ cֱ������;
extern const S�����ʽ c��������;
//�������
class C������� {
public:
	float m�����С[2];
	C�������();
	void fs��С(float, float);
	float f����(float, const S������ &, const S������ &, int);
	S����2 f����(const S����2 &, const S�����ʽ &, const S�����ʽ &);
};

}	//namespace cflw::��ѧ