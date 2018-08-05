#pragma once
#include <memory>
namespace cflw::���� {
using t���� = unsigned short;
using t���� = unsigned short;
//==============================================================================
// �������Ϣ
//==============================================================================
//һ������
struct S���� {
	S����() = default;
	S����(bool, bool);
	operator bool() const;
	bool f�հ���() const;
	bool f���ɿ�() const;
	bool f����() const;
	bool f�ɿ�() const;
	bool f����() const;
	bool f�仯() const;
	void f�����ϴ�() &;
	bool m��� = false, m�ϴ� = false;
};
//һ������
struct S���� {
	S����() = default;
	S����(float, float, float);
	bool f��() const;
	bool f��() const;
	bool f��() const;
	bool f��() const;
	bool fǰ() const;
	bool f��() const;
	float x = 0, y = 0, z = 0;
};
//==============================================================================
// ���������豸����
//==============================================================================
//һ�鰴��
class C������ {
public:
	C������(t����);
	~C������();
	S���� f����(t���� i) const;
	void f�����ϴ�();
	void f����ϴ�();
	void f������();
	t���� m���� = 0;
	bool *m��� = nullptr, *m�ϴ� = nullptr;
};
//���1֡�ڿ��ٰ����ɿ�����ʱ�޷����񰴼�������
class C���尴���� {
public:
	C���尴����(t����);
	~C���尴����();
	void f����(t����);
	void f�ɿ�(t����);
	void f���Ƶ�����(C������ &);//������C����::m���
	void f���();
	t���� m���� = 0;
	bool *m���� = nullptr, *m���� = nullptr;
};
class C���尴�� {
public:
	void f����();
	void f�ɿ�();
	void f���Ƶ�����(S���� &);
	void f���();
	bool m���� = false, m���� = false;
};
class C���巽��2 {
public:
	C���巽��2();
	S���� f��η���() const;
	S���� f�ϴη���() const;
	S���� f�����() const;
	void f�����ϴ�();
	void f������();
	float m���[2], m�ϴ�[2];
};
class C����3 {
public:
	C����3();
	S���� f����() const;
	float m����[3];
};
/*
template<typename t> concept T������ = requires(t a) {
	{a.f����(0)}->S����;
}
*/

//==============================================================================
// �����豸�ӿ�
//==============================================================================
//����
class I�����豸;
class I����;
class I���;
class I�ֱ�;
class I����;
class I���ص�;
using tp�����豸 = std::shared_ptr<I�����豸>;
using tp���� = std::shared_ptr<I����>;
using tp��� = std::shared_ptr<I���>;
using tp�ֱ� = std::shared_ptr<I�ֱ�>;
using tp���� = std::shared_ptr<I����>;
using tp���ص� = std::shared_ptr<I���ص�>;
//����
class I�����豸 {
public:
	virtual void f����() = 0;
};
class I���� : public I�����豸 {
public:
	static constexpr t���� c�������� = 256;
	virtual S���� f����(t���� i) const = 0;
};
class I��� : public I�����豸 {
public:
	static constexpr t���� c�������� = 32;
	virtual S���� f����(t���� i) const = 0;
	virtual S���� f����() const = 0;
	virtual S���� f�ƶ�() const = 0;
	virtual S���� f����() const = 0;
};
class I�ֱ� : public I�����豸 {
public:
	static constexpr t���� c�������� = 32;
	virtual S���� f����(t����) const = 0;
	virtual S���� f����(t����) const = 0;
	virtual float f����(t����) const = 0;
};
class I���� : public I�����豸 {
public:
	virtual t���� f���ص���() const = 0;	//�����԰�����Ļ�ϵĴ��ص�����
	virtual tp���ص� fg���ص�(t����) const = 0;	//����ʵ��Ҫ��֤�³��ֵĴ��ص����������
	virtual tp���ص� fg�´��ص�() = 0;	//û���µ��򷵻�nullptr�������ÿ�θ��º���´��ص�ȡ��
};
class I���ص� {
public:	//I���ص� �ĸ����� I����::f���� ����
	virtual S���� f����() const = 0;
	virtual S���� f����() const = 0;
	virtual S���� f�ƶ�() const = 0;
};
//==============================================================================
// ��������
//==============================================================================
class C����ӳ�� {
public:
	static const t���� cӳ������ = 32;
	t���� mӳ���[cӳ������] = {};
	C������ m����{cӳ������};
	C����ӳ��();
	~C����ӳ��();
	template<typename t������, typename t������> static void f����˳��(C������ &, const t������ &, t������ ��ʼ, t������ ����);	//˳������,����<-
	template<typename t������, typename t������> static void f���¹���l(C������ &, const t������ &, t������ ��ʼ, t������ ����);	//��������,����<-
	template<typename t������, typename t������> static void f���¹���r(C������ &, const t������ &, t������ ��ʼ, t������ ����);	//��������,����->
	S���� f����(t���� i) const;
	void f����(const C������ &);
	void f����(const I���� &);
	void f����(const I��� &);
	void f����(const I�ֱ� &);
	void fsӳ��(t����, t����);
};
class C����� {
public:
	float m���� = 0;
	t���� m����� = 0, m����� = 0;
	C�����() = default;
	C�����(t���� ��, t���� ��);
	static float f����(float, const S���� &, const S���� &);
	void f����(const C������ &);
	void f����(I����&);
	void fs������(t����, t����);
};
//==============================================================================
// ����ӳ��ģ��ʵ��
//==============================================================================
template<typename t������, typename t������> void C����ӳ��::f����˳��(C������ &a���, const t������ &a����, t������ a��ʼ, t������ a����) {
	t������ v���� = a��ʼ;
	for (t���� i = 0; i != a���.m���� && v���� != a����; ++i, ++v����) {
		const S���� &v���� = a����.f����(*v����);
		a���.m���[i] |= v����.m���;
	}
}
template<typename t������, typename t������> void C����ӳ��::f���¹���l(C������ &a���, const t������ &a����, t������ a��ʼ, t������ a����) {
	for (t������ v���� = a��ʼ; v���� != a����; ++v����) {
		const auto &[v�������, v��������] = *v����;
		const S���� &v���� = a����.f����(v��������);
		a���.m���[v�������] |= v����.m���;
	}
}
template<typename t������, typename t������> void C����ӳ��::f���¹���r(C������ &a���, const t������ &a����, t������ a��ʼ, t������ a����) {
	for (t������ v���� = a��ʼ; v���� != a����; ++v����) {
		const auto &[v��������, v�������] = *v����;
		const S���� &v���� = a����.f����(v��������);
		a���.m���[v�������] |= v����.m���;
	}
}
}	//namespace cflw::����