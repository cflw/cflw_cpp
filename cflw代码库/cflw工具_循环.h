#pragma once
#include <vector>
namespace cflw::����::ѭ�� {
//==============================================================================
// ѭ������
//==============================================================================
template<typename tѭ��> class Iѭ�� {
public:	//��ѭ�����м̳�
	class C������ {
	public:
		C������(tѭ�� *a) : mpѭ��{a} {
		}
		C������ &operator ++() {
			mpѭ��->fѭ������_����();
			return *this;
		}
		bool operator !=(const C������ &) {
			return mpѭ��->fѭ������_i����();
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
	bool fѭ������_i����() {
		return false;
	}
	tѭ�� &fѭ������_������() {
		return *((tѭ��*)this);
	}
};
//==============================================================================
// ����
//==============================================================================
template<typename tѭ��, typename t = int> class Cѭ������_���� : public Iѭ��<tѭ��> {
public:
	Cѭ������_����(const t &p) :
		m����{0}, m����{p} {
	}
	void fѭ������_����() {
		++m����;
	}
	bool fѭ������_i����() {
		return m���� != m����;
	}
	t &fѭ������_������() {
		return m����;
	}
	t m����, m����;
};
//==============================================================================
// ��Χ
//==============================================================================
template<typename t����> class C��Χ final {
public:
	typedef typename std::conditional<std::is_const<t����>::value, typename t����::const_reference, typename t����::reference>::type t����;
	class C������ {
	public:
		C������(t���� *ap����, int a����) :
			mp����{ap����}, m����{a����} {
		}
		C������ &operator ++() {
			++m����;
			return *this;
		}
		bool operator !=(const C������ &a) {
			return m���� != a.m����;
		}
		t���� operator *() {
			return (*mp����)[m����];
		}
		int m����;
		t���� *mp����;
	};
	C��Χ(t���� &a����, int a��ʼ, int a����) :
		m��ʼ{std::max<int>(a��ʼ, 0)}, m����{std::min<int>(a����, (int)a����.size())}, mp����{&a����} {
	}
	C������ begin() {
		return C������{mp����, m��ʼ};
	}
	C������ end() {
		return C������{mp����, m����};
	}
	int m��ʼ, m����;
	t���� *mp����;
};
//==============================================================================
// ��ɢ
//==============================================================================
template<typename t����> class C��ɢ final : public Iѭ��<C��ɢ<t����>> {
public:
	typedef decltype(std::declval<t����>().front()) t����;
	typedef decltype(std::declval<t����>().data()) tָ��;
	C��ɢ() = default;
	C��ɢ(t���� &a����, const std::initializer_list<int> &a��) {
		const tָ�� vָ�� = a����.data();
		const int v���� = (int)a��.size();
		maָ��.reserve(v����);
		for (const int &v��� : a��) {
			if (v��� >= 0 && v��� < v����) {
				maָ��.push_back(vָ�� + v���);
			}
		}
		fѭ������_��ʼ();
	}
	C��ɢ(t���� &a����, const std::vector<int> &a��) {
		const tָ�� vָ�� = a����.data();
		const int v���� = (int)a����.size();
		maָ��.reserve(v����);
		for (const int &v��� : a��) {
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
	bool fѭ������_i����() {
		const bool vi���� = (m��ǰ != m����);
		if (!vi����) {
			fѭ������_��ʼ();
		}
		return vi����;
	}
	t���� fѭ������_������() {
		return **m��ǰ;
	}
	std::vector<tָ��> maָ��;
	typename std::vector<tָ��>::iterator m��ǰ, m����;
};
//==============================================================================
// ǰ��,����һ��Ԫ�ص�ʱ��������ǰ��
//==============================================================================
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
	Cǰ��(t���� &a����) :
		m��ǰ{a����.begin()}, m����{a����.end()} {
		m����.mǰ = m����.m�� = f��();
	}
	bool fѭ������_i����() {
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
//==============================================================================
// ����
//==============================================================================
template<typename t����, typename t��ֵ = float> class C���� final : public Iѭ��<C����<t����>> {
public:
	typedef decltype(std::declval<t����>().data()) tָ��;
	typedef decltype(std::declval<t����>().begin()) t������;
	struct S���� {
		tָ�� mǰ, m��;
		t��ֵ m��ֵ;
	};
	C����(t���� &a����, t��ֵ a����) :
		m��ǰ{a����.begin()}, m����{m��ǰ + 1}, m����{a����.end()}, m����{(t��ֵ)(a����.size() - 1) / a����} {
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
	bool fѭ������_i����() {
		return m���� != m����;
	}
	S���� &fѭ������_������() {
		return m����;
	}
	t������ m��ǰ, m����, m����;
	S���� m����;
	t��ֵ m����;
};
}	//namespace cflw::����::ѭ��