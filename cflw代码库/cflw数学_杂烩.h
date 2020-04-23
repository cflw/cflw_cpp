#pragma once
#include <utility>
namespace cflw::数学 {
//位置计算
template<typename t> class C位置计算 {
public:	//参数1"位置":当前位置	参数2"长度":	返回值:计算后位置
	static t f左到中(const t &位置, const t &长度);//对齐到[-长度/2, 长度/2]
	static t f中到左(const t &位置, const t &长度);//[0, 长度]
	static t f右到中(const t &位置, const t &长度);
	static t f中到右(const t &位置, const t &长度);
	static t f右到左(const t &位置, const t &长度);
	static t f左到右(const t &位置, const t &长度);
	static t f下到中(const t &位置, const t &长度);
	static t f下到上(const t &位置, const t &长度);
	static t f中到下(const t &位置, const t &长度);
	static t f中到上(const t &位置, const t &长度);
	static t f上到中(const t &位置, const t &长度);
	static t f上到下(const t &位置, const t &长度);
};
template<typename t> class C窗口位置计算 {//按窗口坐标系计算,未完成
public:
	static t f左到中(const t &位置, const t &长度);
};
//有限值
template<class t> struct S有限值 {
	typedef typename std::conditional<std::is_floating_point<t>::value, t, float>::type t小数;
	t m当前, m最大;
	//构造函数
	S有限值();
	S有限值(const t &);
	//函数
	void f检查();	//检查当前值是否超过最大值,如果是,令当前值=最大值
	void f重置(const t &);	//重新设置当前值和最大值
	void f满();	//当前值=最大值
	t小数 fg百分比() const;
};
//一个一维的范围
template<typename t> struct S范围 {
	t m小, m大;
	S范围();
	S范围(const t &, const t &);
	static S范围 fc中心半径(const t &中心, const t &半径);
	t fg小() const;
	t fg大() const;
	t fg中心() const;
	t fg直径() const;
	t fg半径() const;
	S范围 &fs大(const t &);
	S范围 &fs小(const t &);
	S范围 &fs中心半径(const t &, const t &);
	S范围 &fs中心(const t &);
	S范围 &fs直径(const t &);
	S范围 &fs半径(const t &);
	S范围 &fs移动(const t &);
	S范围 &fs合并(const S范围 &);
	bool fi范围内(const t &) const;
	bool fi相交(const S范围 &) const;
	bool fi零() const;	//小==大,范围为0
	S范围 f合并(const S范围 &) const;
};
//范围变换计算
template<typename t> class C范围变换计算 {
public:
	S范围<t> m前, m后;
	C范围变换计算();
	C范围变换计算(const S范围<t> &, const S范围<t> &);
	static t f变换计算(const S范围<t> &, const S范围<t> &, const t &);
	t operator ()(const t &) const;
	t f计算(const t &) const;
	t f逆计算(const t &) const;
};
//二维序号计算
template<typename t> class C二维序号计算 {
public:
	t m列;
	C二维序号计算();
	C二维序号计算(const t &列);
	t operator()(const t &行, const t &列) const;
	std::pair<t, t> operator()(const t &一维) const;
	static t f二到一(const t &, const t &, const t &);
	static std::pair<t, t> f一到二(const t &, const t &);
};
//渐变值
template<typename t> struct S渐变值 {
	t m当前 = 0, m目标 = 0;
	t f线性渐变(t 值);
	t f倍数渐变(float 倍数, t 最小, t 最大);
};
}	//namespace cflw::数学
#include "cflw数学_杂烩.inl"