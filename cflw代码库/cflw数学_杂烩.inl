#pragma once
#include <algorithm>
#include "cflw数学_杂烩.h"
#include "cflw数学.h"
namespace cflw::数学 {
//==============================================================================
// 位置计算
//==============================================================================
template<typename t> t C位置计算<t>::f左到中(const t &a位置, const t &a长度) {
	return a位置 + a长度 / 2;
}
template<typename t> t C位置计算<t>::f中到左(const t &a位置, const t &a长度) {
	return a位置 - a长度 / 2;
}
template<typename t> t C位置计算<t>::f右到中(const t &a位置, const t &a长度) {
	return a位置 - a长度 / 2;
}
template<typename t> t C位置计算<t>::f中到右(const t &a位置, const t &a长度) {
	return a位置 + a长度 / 2;
}
template<typename t> t C位置计算<t>::f右到左(const t &a位置, const t &a长度) {
	return a位置 - a长度;
}
template<typename t> t C位置计算<t>::f左到右(const t &a位置, const t &a长度) {
	return a位置 + a长度;
}
template<typename t> t C位置计算<t>::f下到中(const t &a位置, const t &a长度) {
	return a位置 + a长度 / 2;
}
template<typename t> t C位置计算<t>::f下到上(const t &a位置, const t &a长度) {
	return a位置 + a长度;
}
template<typename t> t C位置计算<t>::f中到下(const t &a位置, const t &a长度) {
	return a位置 - a长度 / 2;
}
template<typename t> t C位置计算<t>::f中到上(const t &a位置, const t &a长度) {
	return a位置 + a长度 / 2;
}
template<typename t> t C位置计算<t>::f上到中(const t &a位置, const t &a长度) {
	return a位置 - a长度 / 2;
}
template<typename t> t C位置计算<t>::f上到下(const t &a位置, const t &a长度) {
	return a位置 - a长度;
}
//==============================================================================
// 有限值
//==============================================================================
template<typename t> S有限值<t>::S有限值() :m当前((t)-1), m最大((t)-1) {}
template<typename t> S有限值<t>::S有限值(const t &_) : m当前(_), m最大(_) {}
template<typename t> void S有限值<t>::f检查() {
	if (m当前 > m最大)
		m当前 = m最大;
}
template<typename t> void S有限值<t>::f重置(const t &_) {
	m当前 = _;
	m最大 = _;
}
template<typename t> void S有限值<t>::f满() {
	m当前 = m最大;
}
template<typename t> typename S有限值<t>::t小数 S有限值<t>::fg百分比() const {
	return (t小数)m当前 / (t小数)m最大;
}
//==============================================================================
// 范围
//==============================================================================
template<typename t> S范围<t>::S范围() : m小(), m大() {
}
template<typename t> S范围<t>::S范围(const t &a小, const t &a大) : m小(a小), m大(a大) {
}
template<typename t> S范围<t> S范围<t>::fc中心半径(const t &a中心, const t &a半径) {
	S范围 v;
	v.m小 = a中心 - a半径;
	v.m大 = a中心 + a半径;
	return v;
}
template<typename t> t S范围<t>::fg小() const {
	return m小;
}
template<typename t> t S范围<t>::fg大() const {
	return m大;
}
template<typename t> t S范围<t>::fg中心() const {
	return (m小 + m大) / 2;
}
template<typename t> t S范围<t>::fg直径() const {
	return m大 - m小;
}
template<typename t> t S范围<t>::fg半径() const {
	return fg直径() / 2;
}
template<typename t> S范围<t> &S范围<t>::fs大(const t &a大) {
	m大 = a大;
}
template<typename t> S范围<t> &S范围<t>::fs小(const t &a小) {
	m小 = a小;
}
template<typename t> S范围<t> &S范围<t>::fs中心半径(const t &a中心, const t &a半径) {
	m小 = a中心 - a半径;
	m大 = a中心 + a半径;
	return *this;
}
template<typename t> S范围<t> &S范围<t>::fs中心(const t &a中心) {
	const t v半径 = fg半径();
	m小 = a中心 - v半径;
	m大 = a中心 + v半径;
	return *this;
}
template<typename t> S范围<t> &S范围<t>::fs直径(const t &a直径) {
	return fs半径(a直径 / 2);
}
template<typename t> S范围<t> &S范围<t>::fs半径(const t &a半径) {
	const t v中心 = fg中心();
	m小 = v中心 - a半径;
	m大 = v中心 + a半径;
	return *this;
}
template<typename t> S范围<t> &S范围<t>::fs移动(const t &a移动) {
	m小 += a移动;
	m大 += a移动;
	return *this;
}
template<typename t> S范围<t> &S范围<t>::fs合并(const S范围 &a范围) {
	m小 = std::min<t>(m小, a范围.m小);
	m大 = std::max<t>(m大, a范围.m大);
	return *this;
}
template<typename t> bool S范围<t>::fi范围内(const t &a点) const {
	return m小 <= a点 && a点 <= m大;
}
template<typename t> bool S范围<t>::fi相交(const S范围 &a范围) const {
	const t v中心 = a范围.fg中心() - fg中心();
	return v中心 <= a范围.fg半径() + fg半径();
}
template<typename t> S范围<t> S范围<t>::f合并(const S范围 &a范围) const {
	return{std::min<t>(m小, a范围.m小), std::max<t>(m大, a范围.m大)};
}
//==============================================================================
// 范围变换计算
//==============================================================================
template<typename t> C范围变换计算<t>::C范围变换计算() :
	m前(), m后() {
}
template<typename t> C范围变换计算<t>::C范围变换计算(const S范围<t> &a前, const S范围<t> &a后) :
	m前(a前), m后(a后) {
}
template<typename t>  t C范围变换计算<t>::f变换计算(const S范围<t> &a前, const S范围<t> &a后, const t &a值) {
	return (a值 - a前.m小) / a前.fg直径() * a后.fg直径() + a后.m小;
}
template<typename t> t C范围变换计算<t>::operator ()(const t &a) const {
	return f变换计算(m前, m后, a);
}
template<typename t> t C范围变换计算<t>::f计算(const t &a) const {
	return f变换计算(m前, m后, a);
}
template<typename t> t C范围变换计算<t>::f逆计算(const t &a) const {
	return f变换计算(m后, m前, a);
}
//==============================================================================
// 二维序号计算
//==============================================================================
template<typename t> C二维序号计算<t>::C二维序号计算():
	m列() {
}
template<typename t> C二维序号计算<t>::C二维序号计算(const t &a列):
	m列(a列) {
}
template<typename t> t C二维序号计算<t>::operator()(const t &a行, const t &a列) const {
	return f二到一(m列, a行, a列);
}
template<typename t> std::pair<t, t> C二维序号计算<t>::operator()(const t &a一维) const {
	return f一到二(m列, a一维);
}
template<typename t> t C二维序号计算<t>::f二到一(const t &a原列, const t &a指定行, const t &a指定列) {
	return a原列 * a指定行 + a指定列;
}
template<typename t> std::pair<t, t> C二维序号计算<t>::f一到二(const t &a原列, const t &a指定一维) {
	return std::pair<t, t>{a指定一维 / a原列, a指定一维 % a原列};
}
//==============================================================================
// 二维序号计算
//==============================================================================
template<typename t> t S渐变值<t>::f线性渐变(t a值) {
	m当前 = 数学::f线性渐变<t>(m当前, m目标, a值);
	return m当前;
}
template<typename t> t S渐变值<t>::f倍数渐变(float a倍数, t a最小, t a最大) {
	m当前 = 数学::f倍数渐变<t>(m当前, m目标, a倍数, a最小, a最大);
	return m当前;
}
}	//namespace cflw::数学