#pragma once
namespace cflw::���� {
//==============================================================================
// ����
//==============================================================================
template<typename tԭ, typename t����, typename tfԭg = typename t����(tԭ::*)() const, typename tfԭs = typename tԭ&(tԭ::*)(const t���� &)>
class C���� {
public:
	C����(tԭ &aԭ, tfԭg afԭg, tfԭs afԭs):
		mԭ(&aԭ), mfԭg(afԭg), mfԭs(afԭs) {
	}
	t���� fg() const {
		return (mԭ->*mfԭg)();
	}
	C���� &fs(const t���� &) const {
		(mԭ->*mfԭs)(a);
		return *this;
	}
	operator t����() const {
		return fg();
	}
	C���� &operator =(const t���� &a) const {
		return fs(a);
	}
	t���� operator ->() const {
		return fg();
	}
	template<typename...t����> auto operator ()(t���� &&...a����) const {
		return (mԭ->*mfԭg)()(a����...);
	}
	template<typename t> auto operator +(const t &a) const {
		return fg() + a;
	}
	template<typename t> auto operator -(const t &a) const {
		return fg() - a;
	}
	template<typename t> auto operator *(const t &a) const {
		return fg() * a;
	}
	template<typename t> auto operator /(const t &a) const {
		return fg() / a;
	}
	template<typename t> auto operator %(const t &a) const {
		return fg() % a;
	}
	template<typename t> C���� &operator +=(const t &a) const {
		return fs(fg() + a);
	}
	template<typename t> C���� &operator -=(const t &a) const {
		return fs(fg() - a);
	}
	template<typename t> C���� &operator *=(const t &a) const {
		return fs(fg() * a);
	}
	template<typename t> C���� &operator /=(const t &a) const {
		return fs(fg() / a);
	}
	template<typename t> C���� &operator %=(const t &a) const {
		return fs(fg() % a);
	}
	tԭ *mԭ = nullptr;
	tfԭg mfԭg = nullptr;
	tfԭs mfԭs = nullptr;
};
}	//namespace cflw::����