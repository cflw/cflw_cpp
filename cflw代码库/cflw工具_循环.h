#pragma once
#include <vector>
namespace cflw {
namespace ���� {
namespace ѭ�� {
//--------------------------------------------------------------------------------
// ѭ������
//--------------------------------------------------------------------------------
template<typename tѭ��> class Iѭ�� {
public:	//��ѭ�����м̳�
	class C������ {
	public:
		C������(tѭ�� *p) : mpѭ��{p} {
		}
		C������ &operator ++() {
			mpѭ��->fѭ������_����();
			return *this;
		}
		bool operator !=(const C������ &) {
			return mpѭ��->fѭ������_w����();
		}
		decltype(std::declval<tѭ��>().fѭ������_������()) operator *() {
			return mpѭ��->fѭ������_������();
		}
		tѭ�� *mpѭ��;
	};
	C������ begin() {
		return{(tѭ�� *)this};
	}
	C������ end() {
		return{(tѭ�� *)this};
	}
	//����д
	void fѭ������_����() {
	}
	bool fѭ������_w����() {
		return false;
	}
	tѭ�� &fѭ������_������() {
		return *((tѭ��*)this);
	}
};
//--------------------------------------------------------------------------------
// ����
//--------------------------------------------------------------------------------
template<typename tѭ��, typename t = int> class Cѭ������_���� : public Iѭ��<tѭ��> {
public:
	Cѭ������_����(const t &p) :
		m����{0}, m����{p} {
	}
	void fѭ������_����() {
		++m����;
	}
	bool fѭ������_w����() {
		return m���� != m����;
	}
	t &fѭ������_������() {
		return m����;
	}
	t m����, m����;
};
//--------------------------------------------------------------------------------
// ��Χ
//--------------------------------------------------------------------------------
template<typename t����> class C��Χ final {
public:
	typedef typename std::conditional<std::is_const<t����>::value, typename t����::const_reference, typename t����::reference>::type t����;
	class C������ {
	public:
		C������(t���� *pp, int pi) :
			mp{pp}, mi{pi} {
		}
		C������ &operator ++() {
			++mi;
			return *this;
		}
		bool operator !=(const C������ &p) {
			return mi != p.mi;
		}
		t���� operator *() {
			return (*mp)[mi];
		}
		int mi;
		t���� *mp;
	};
	C��Χ(t���� &pp, int p0, int p1) :
		m0{std::max<int>(p0, 0)}, m1{std::min<int>(p1, (int)pp.size())}, mp{&pp} {
	}
	C������ begin() {
		return C������{mp, m0};
	}
	C������ end() {
		return C������{mp, m1};
	}
	int m0, m1;
	t���� *mp;
};
//--------------------------------------------------------------------------------
//��ɢ
//--------------------------------------------------------------------------------
template<typename t����> class C��ɢ final : public Iѭ��<C��ɢ<t����>> {
public:
	typedef decltype(std::declval<t����>().front()) t����;
	typedef decltype(std::declval<t����>().data()) tָ��;
	C��ɢ() = default;
	C��ɢ(t���� &p����, const std::initializer_list<int> &p��) {
		const tָ�� vָ�� = p����.data();
		const int v���� = (int)p��.size();
		maָ��.reserve(v����);
		for (const int &v��� : p��) {
			if (v��� >= 0 && v��� < v����) {
				maָ��.push_back(vָ�� + v���);
			}
		}
		fѭ������_��ʼ();
	}
	C��ɢ(t���� &p����, const std::vector<int> &p��) {
		const tָ�� vָ�� = p����.data();
		const int v���� = (int)p����.size();
		maָ��.reserve(v����);
		for (const int &v��� : p��) {
			if (v��� >= 0 && v��� < v����) {
				maָ��.push_back(vָ�� + v���);
			}
		}
		fѭ������_��ʼ();
	}
	void fѭ������_��ʼ() {
		m��ǰ = maָ��.begin();
		m���� = maָ��.end();
	}
	void fѭ������_����() {
		++m��ǰ;
	}
	bool fѭ������_w����() {
		const bool vw���� = (m��ǰ != m����);
		if (!vw����) {
			fѭ������_��ʼ();
		}
		return vw����;
	}
	t���� fѭ������_������() {
		return **m��ǰ;
	}
	std::vector<tָ��> maָ��;
	typename std::vector<tָ��>::iterator m��ǰ, m����;
};
//--------------------------------------------------------------------------------
// ǰ��,����һ��Ԫ�ص�ʱ��������ǰ��
//--------------------------------------------------------------------------------
template<typename t����> class Cǰ�� final : public Iѭ��<Cǰ��<t����>> {
public:
	typedef decltype(std::declval<t����>().data()) tָ��;
	typedef decltype(std::declval<t����>().begin()) t������;
	struct S���� {
		tָ�� mǰ, m��, m��;
		bool fwǰ() const {
			return mǰ == m��;
		}
		bool fw��() const {
			return m�� == m��;
		}
	};
	Cǰ��(t���� &p����) :
		m��ǰ{p����.begin()}, m����{p����.end()} {
		m����.mǰ = m����.m�� = f��();
	}
	bool fѭ������_w����() {
		if (m��ǰ != m����) {
			m����.m�� = f��();
			m����.m�� = f��();
			return true;
		} else {
			return false;
		}
	}
	void fѭ������_����() {
		m����.mǰ = m����.m��;
		++m��ǰ;
	}
	S���� &fѭ������_������() {
		return m����;
	}
	tָ�� f��() {
		return &(*m��ǰ);
	}
	tָ�� f��() {
		const t������ m���� = m��ǰ + 1;
		if (m���� != m����) {
			return &(*m����);
		} else {
			return f��();
		}
	}
	t������ m��ǰ, m����;
	S���� m����;
};
//--------------------------------------------------------------------------------
// ����
//--------------------------------------------------------------------------------
template<typename t����, typename t��ֵ = float> class C���� final : public Iѭ��<C����<t����>> {
public:
	typedef decltype(std::declval<t����>().data()) tָ��;
	typedef decltype(std::declval<t����>().begin()) t������;
	struct S���� {
		tָ�� mǰ, m��;
		t��ֵ m��ֵ;
	};
	C����(t���� &p����, t��ֵ p����) :
		m��ǰ{p����.begin()}, m����{m��ǰ + 1}, m����{p����.end()}, m����{(t��ֵ)(p����.size() - 1) / p����} {
		m����.mǰ = &(*m��ǰ);
		if (m���� != m����) {
			m����.m�� = &(*m����);
		}
	}
	void fѭ������_����() {
		m����.m��ֵ += m����;
		if (m����.m��ֵ > 1) {
			m����.m��ֵ -= 1;
			++m��ǰ;
			m���� + 1;
		}
	}
	bool fѭ������_w����() {
		return m���� != m����;
	}
	S���� &fѭ������_������() {
		return m����;
	}
	t������ m��ǰ, m����, m����;
	S���� m����;
	t��ֵ m����;
};
}	//namespace ѭ��
}}	//�����ռ����