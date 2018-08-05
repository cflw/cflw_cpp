#pragma once
#include <algorithm>
#include "cflw��ѧ_�ӻ�.h"
#include "cflw��ѧ.h"
namespace cflw::��ѧ {
//==============================================================================
// λ�ü���
//==============================================================================
template<typename t> t Cλ�ü���<t>::f����(const t &pλ��, const t &p����) {
	return pλ�� + p���� / 2;
}
template<typename t> t Cλ�ü���<t>::f�е���(const t &pλ��, const t &p����) {
	return pλ�� - p���� / 2;
}
template<typename t> t Cλ�ü���<t>::f�ҵ���(const t &pλ��, const t &p����) {
	return pλ�� - p���� / 2;
}
template<typename t> t Cλ�ü���<t>::f�е���(const t &pλ��, const t &p����) {
	return pλ�� + p���� / 2;
}
template<typename t> t Cλ�ü���<t>::f�ҵ���(const t &pλ��, const t &p����) {
	return pλ�� - p����;
}
template<typename t> t Cλ�ü���<t>::f����(const t &pλ��, const t &p����) {
	return pλ�� + p����;
}
template<typename t> t Cλ�ü���<t>::f�µ���(const t &pλ��, const t &p����) {
	return pλ�� + p���� / 2;
}
template<typename t> t Cλ�ü���<t>::f�µ���(const t &pλ��, const t &p����) {
	return pλ�� + p����;
}
template<typename t> t Cλ�ü���<t>::f�е���(const t &pλ��, const t &p����) {
	return pλ�� - p���� / 2;
}
template<typename t> t Cλ�ü���<t>::f�е���(const t &pλ��, const t &p����) {
	return pλ�� + p���� / 2;
}
template<typename t> t Cλ�ü���<t>::f�ϵ���(const t &pλ��, const t &p����) {
	return pλ�� - p���� / 2;
}
template<typename t> t Cλ�ü���<t>::f�ϵ���(const t &pλ��, const t &p����) {
	return pλ�� - p����;
}
//==============================================================================
// ����ֵ
//==============================================================================
template<typename t> S����ֵ<t>::S����ֵ() :m��ǰ((t)-1), m���((t)-1) {}
template<typename t> S����ֵ<t>::S����ֵ(const t &_) : m��ǰ(_), m���(_) {}
template<typename t> void S����ֵ<t>::f���() {
	if (m��ǰ > m���)
		m��ǰ = m���;
}
template<typename t> void S����ֵ<t>::f����(const t &_) {
	m��ǰ = _;
	m��� = _;
}
template<typename t> void S����ֵ<t>::f��() {
	m��ǰ = m���;
}
template<typename t> typename S����ֵ<t>::tС�� S����ֵ<t>::fg�ٷֱ�() const {
	return (tС��)m��ǰ / (tС��)m���;
}
//==============================================================================
// ��Χ
//==============================================================================
template<typename t> S��Χ<t>::S��Χ() : mС(), m��() {
}
template<typename t> S��Χ<t>::S��Χ(const t &aС, const t &a��) : mС(aС), m��(a��) {
}
template<typename t> S��Χ<t> S��Χ<t>::fc���İ뾶(const t &a����, const t &a�뾶) {
	S��Χ v;
	v.mС = a���� - a�뾶;
	v.m�� = a���� + a�뾶;
	return v;
}
template<typename t> t S��Χ<t>::fgС() const {
	return mС;
}
template<typename t> t S��Χ<t>::fg��() const {
	return m��;
}
template<typename t> t S��Χ<t>::fg����() const {
	return (mС + m��) / 2;
}
template<typename t> t S��Χ<t>::fgֱ��() const {
	return m�� - mС;
}
template<typename t> t S��Χ<t>::fg�뾶() const {
	return fgֱ��() / 2;
}
template<typename t> S��Χ<t> &S��Χ<t>::fs��(const t &a��) {
	m�� = a��;
}
template<typename t> S��Χ<t> &S��Χ<t>::fsС(const t &aС) {
	mС = aС;
}
template<typename t> S��Χ<t> &S��Χ<t>::fs���İ뾶(const t &a����, const t &a�뾶) {
	mС = a���� - a�뾶;
	m�� = a���� + a�뾶;
	return *this;
}
template<typename t> S��Χ<t> &S��Χ<t>::fs����(const t &a����) {
	const t v�뾶 = fg�뾶();
	mС = a���� - v�뾶;
	m�� = a���� + v�뾶;
	return *this;
}
template<typename t> S��Χ<t> &S��Χ<t>::fsֱ��(const t &aֱ��) {
	return fs�뾶(aֱ�� / 2);
}
template<typename t> S��Χ<t> &S��Χ<t>::fs�뾶(const t &a�뾶) {
	const t v���� = fg����();
	mС = v���� - a�뾶;
	m�� = v���� + a�뾶;
	return *this;
}
template<typename t> S��Χ<t> &S��Χ<t>::fs�ƶ�(const t &a�ƶ�) {
	mС += a�ƶ�;
	m�� += a�ƶ�;
	return *this;
}
template<typename t> S��Χ<t> &S��Χ<t>::fs�ϲ�(const S��Χ &a��Χ) {
	mС = std::min<t>(mС, a��Χ.mС);
	m�� = std::max<t>(m��, a��Χ.m��);
	return *this;
}
template<typename t> bool S��Χ<t>::fi��Χ��(const t &a��) const {
	return mС <= a�� && a�� <= m��;
}
template<typename t> bool S��Χ<t>::fi�ཻ(const S��Χ &a��Χ) const {
	const t v���� = a��Χ.fg����() - fg����();
	return v���� <= a��Χ.fg�뾶() + fg�뾶();
}
template<typename t> S��Χ<t> S��Χ<t>::f�ϲ�(const S��Χ &a��Χ) const {
	return{std::min<t>(mС, a��Χ.mС), std::max<t>(m��, a��Χ.m��)};
}
//==============================================================================
// ��Χ�任����
//==============================================================================
template<typename t> C��Χ�任����<t>::C��Χ�任����() :
	mǰ(), m��() {
}
template<typename t> C��Χ�任����<t>::C��Χ�任����(const S��Χ<t> &aǰ, const S��Χ<t> &a��) :
	mǰ(aǰ), m��(a��) {
}
template<typename t>  t C��Χ�任����<t>::f�任����(const S��Χ<t> &aǰ, const S��Χ<t> &a��, const t &aֵ) {
	return (aֵ - aǰ.mС) / aǰ.fgֱ��() * a��.fgֱ��() + a��.mС;
}
template<typename t> t C��Χ�任����<t>::operator ()(const t &a) const {
	return f�任����(mǰ, m��, a);
}
template<typename t> t C��Χ�任����<t>::f����(const t &a) const {
	return f�任����(mǰ, m��, a);
}
template<typename t> t C��Χ�任����<t>::f�����(const t &a) const {
	return f�任����(m��, mǰ, a);
}
//==============================================================================
// ��ά��ż���
//==============================================================================
template<typename t> C��ά��ż���<t>::C��ά��ż���():
	m��() {
}
template<typename t> C��ά��ż���<t>::C��ά��ż���(const t &a��):
	m��(a��) {
}
template<typename t> t C��ά��ż���<t>::operator()(const t &a��, const t &a��) const {
	return f����һ(m��, a��, a��);
}
template<typename t> std::pair<t, t> C��ά��ż���<t>::operator()(const t &aһά) const {
	return fһ����(m��, aһά);
}
template<typename t> t C��ά��ż���<t>::f����һ(const t &aԭ��, const t &aָ����, const t &aָ����) {
	return aԭ�� * aָ���� + aָ����;
}
template<typename t> std::pair<t, t> C��ά��ż���<t>::fһ����(const t &aԭ��, const t &aָ��һά) {
	return std::pair<t, t>{aָ��һά / aԭ��, aָ��һά % aԭ��};
}
//==============================================================================
// ��ά��ż���
//==============================================================================
template<typename t> t S����ֵ<t>::f���Խ���(t aֵ) {
	m��ǰ = ��ѧ::f���Խ���<t>(m��ǰ, mĿ��, aֵ);
	return m��ǰ;
}
template<typename t> t S����ֵ<t>::f��������(float a����, t a��С, t a���) {
	m��ǰ = ��ѧ::f��������<t>(m��ǰ, mĿ��, a����, a��С, a���);
	return m��ǰ;
}
}	//namespace cflw::��ѧ