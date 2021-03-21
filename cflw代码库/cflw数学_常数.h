#pragma once
namespace cflw::数学 {
template<typename t = double> constexpr t c圆周率 = t(3.14159265358979323846264338327950288);	//π
template<typename t = double> constexpr t c半π = c圆周率<t> * t(0.5);
template<typename t = double> constexpr t cπ = c圆周率<t>;	//π
template<typename t = double> constexpr t c二π = c圆周率<t> * 2;
template<typename t = double> constexpr t c根号2 = t(1.4142135623730950488016887242097);
template<typename t = double> constexpr t c根号3 = t(1.7320508075688772935274463415059);
template<typename t = double> constexpr t c根号5 = t(2.2360679774997896964091736687313);
template<typename t = double> constexpr t c度到弧度 = t(0.01745329251994329576923690768489);
template<typename t = double> constexpr t c弧度到度 = t(57.295779513082320876798154814105);
template<typename t = double> constexpr t c自然对数 = t(2.71828182845904523536028747135266249);	//e
template<typename t = double> constexpr t c欧拉常数 = t(0.57721566490153286060651209008240243);	//γ
template<typename t = double> constexpr t c黄金比例 = t(0.61803398874989484820458683436563811);	//φ
template<typename t = double> constexpr t c钱珀瑙恩数 = t(0.1234567891011121314151617181920);	//C10
template<typename t = double> constexpr t c第一费根鲍姆常数 = t(4.66920160910299067185320382046620161);	//δ
template<typename t = double> constexpr t c第二费根鲍姆常数 = t(2.50290787509589282228390287321821578);	//α
}	//namespace cflw::数学