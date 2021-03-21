#include <cassert>
#include <vector>
#include <ranges>
#include "cflw输入_win8.h"
#include "cflw数学_常数.h"
#include "cflw视窗.h"
namespace cflw::输入::win8 {
using tp鼠标 = std::shared_ptr<C鼠标>;
using tp触摸 = std::shared_ptr<C触摸>;
using tp笔 = std::shared_ptr<C笔>;
using tp笔点 = std::shared_ptr<C笔点>;
//==============================================================================
// 函数
//==============================================================================
bool fi进入(const POINTER_INFO &a信息) {
	return a信息.pointerFlags & POINTER_FLAG_INRANGE;
}
bool fi离开(const POINTER_INFO &a信息) {
	return !(a信息.pointerFlags & POINTER_FLAG_INRANGE);
}
//==============================================================================
// 类定义
//==============================================================================
//鼠标
class C鼠标 : public I鼠标 {
	friend class C输入;

};
//触摸
class C触摸 : public I触摸 {
	friend class C输入;

};
//笔
class C笔 : public I笔 {
	friend class C输入;
public:
	C笔(HWND, float 缩放);
	void f更新() override;
	t数量 fg笔点数() const override;
	输入::tp笔点 fg笔点(t索引) const override;
	输入::tp笔点 fg新笔点() override;
	//笔点操作
	tp笔点 f笔点_查找(WORD) const;
	void f笔点_接收(WORD 标识, const POINTER_PEN_INFO &信息);
	tp笔点 f笔点_新建(WORD 标识, const POINTER_PEN_INFO &信息);
	void f笔点_按键(WORD 标识, bool 按键, const POINTER_PEN_INFO &信息);
private:
	std::vector<std::shared_ptr<C笔点>> ma点;
	HWND m窗口;
	float m缩放 = 1;
	t索引 m新点索引 = 0;
	t数量 m新点数 = 0;
};
class C笔点 : public I笔点 {
	friend class C输入;
	friend class C笔;
public:
	C笔点(const C笔 &, const POINTER_PEN_INFO &);
	S按键 fg按键() const override;
	S方向 fg坐标() const override;
	S方向 fg移动() const override;
	bool fi有效() const override;
	float fg压力() const override;
	float fg旋转() const override;
	std::pair<float, float> fg倾斜() const override;
	void f接收信息(const POINTER_PEN_INFO &);
	void f接收按键(bool);
private:
	const C笔 *m笔 = nullptr;
	POINTER_PEN_INFO m信息;
	C缓冲按键 m缓冲;
	S按键 m按键;
	C缓冲方向2 m坐标;
};
//==============================================================================
// 设备
//==============================================================================
C输入::~C输入() {
}
void C输入::f初始化(HWND a窗口, float a缩放) {
	m窗口 = a窗口;
	m缩放 = a缩放;
}
void C输入::f销毁() {
	m鼠标.reset();
	m触摸.reset();
	m笔.reset();
}
bool C输入::f窗口消息(UINT a消息, WPARAM w, LPARAM l) {
	if (a消息 >= WM_NCPOINTERUPDATE && a消息 <= WM_POINTERROUTEDRELEASED) {	//WM_POINT范围,在WinUser.h第2402行
		const WORD v标识 = GET_POINTERID_WPARAM(w);
		POINTER_INPUT_TYPE v类型 = PT_POINTER;
		if (!GetPointerType(v标识, &v类型)) {
			return false;
		}
		switch (v类型) {
		case PT_MOUSE:	//鼠标
			return f鼠标消息(a消息, w, l);
		case PT_TOUCH:	//触摸
			return f触摸消息(a消息, w, l);
		case PT_PEN:	//笔
			return f笔消息(a消息, w, l);
		}
	}
	return false;
}
bool C输入::f鼠标消息(UINT a消息, WPARAM w, LPARAM l) {
	return false;	//未实现
}
bool C输入::f触摸消息(UINT a消息, WPARAM w, LPARAM l) {
	return false;	//未实现
}
bool C输入::f笔消息(UINT a消息, WPARAM w, LPARAM l) {
	if (m笔) {
		const WORD v标识 = GET_POINTERID_WPARAM(w);
		POINTER_PEN_INFO v信息 = {0};
		if (!GetPointerPenInfo(v标识, &v信息)) {
			return false;
		}
		switch (a消息) {
		case WM_POINTERUPDATE:
			m笔->f笔点_接收(v标识, v信息);
			return true;
		case WM_POINTERUP:
			m笔->f笔点_按键(v标识, true, v信息);
			return true;
		case WM_POINTERDOWN:
			m笔->f笔点_按键(v标识, false, v信息);
			return true;
		default:
			m笔->f笔点_接收(v标识, v信息);
			return true;
		}
	}
	return false;
}
void C输入::f更新() {
	if (m笔) {
		m笔->f更新();
	}
}
void C输入::fs缩放(float a缩放) {
	m缩放 = a缩放;
}
输入::tp鼠标 C输入::f创建鼠标() {
	throw;	//未实现
}
输入::tp触摸 C输入::f创建触摸() {
	throw;	//未实现
}
输入::tp笔 C输入::f创建笔() {
	if (m笔 == nullptr) {
		m笔 = std::make_shared<C笔>(m窗口, m缩放);
	}
	return m笔;
}
//==============================================================================
// 鼠标
//==============================================================================

//==============================================================================
// 触摸
//==============================================================================

//==============================================================================
// 笔
//==============================================================================
C笔::C笔(HWND a窗口, float a缩放):
	m窗口(a窗口),
	m缩放(a缩放) {
}
void C笔::f更新() {
	视窗::C屏幕坐标到客户区坐标计算 v计算(m窗口);
	for (const std::shared_ptr<C笔点> &v点 : ma点) {
		//按键
		v点->m按键.f覆盖上次();
		v点->m缓冲.f复制到按键(v点->m按键);
		//坐标
		v点->m坐标.f覆盖上次();
		float *const v这次 = v点->m坐标.m这次;
		v这次[0] = v计算.f直角坐标xf(v点->m信息.pointerInfo.ptPixelLocation.x) / m缩放;
		v这次[1] = v计算.f直角坐标yf(v点->m信息.pointerInfo.ptPixelLocation.y) / m缩放;
	}
	输入::f清除指针(ma点, [](const std::shared_ptr<C笔点> &a)->bool {
		return fi离开(a->m信息.pointerInfo);
	});
	m新点索引 = fg笔点数() - m新点数;
	m新点数 = 0;
}
t数量 C笔::fg笔点数() const {
	return (t数量)ma点.size();
}
输入::tp笔点 C笔::fg笔点(t索引 i) const {
	return ma点[i];
}
输入::tp笔点 C笔::fg新笔点() {
	if (m新点索引 < fg笔点数()) {
		return fg笔点(m新点索引++);
	}
	return nullptr;
}
tp笔点 C笔::f笔点_查找(WORD a标识) const {
	if (auto v点 = std::find_if(ma点.begin(), ma点.end(), [&](const tp笔点 &a点)->bool {return a点->m信息.pointerInfo.pointerId == a标识; }); v点 != ma点.end()) {
		return *v点;
	}
	return nullptr;
}
void C笔::f笔点_接收(WORD a标识, const POINTER_PEN_INFO &a信息) {
	if (auto v点 = f笔点_查找(a标识)) {
		v点->f接收信息(a信息);
	} else {
		f笔点_新建(a标识, a信息);
	}
}
tp笔点 C笔::f笔点_新建(WORD a标识, const POINTER_PEN_INFO &a信息) {
	++m新点数;
	return ma点.emplace_back(std::make_shared<C笔点>(*this, a信息));
}
void C笔::f笔点_按键(WORD a标识, bool a按键, const POINTER_PEN_INFO &a信息) {
	if (auto v点 = f笔点_查找(a标识)) {
		v点->f接收信息(a信息);
		v点->f接收按键(a按键);
	} else {
		auto v新 = f笔点_新建(a标识, a信息);
		v新->f接收按键(a按键);
	}
}
//笔点
C笔点::C笔点(const C笔 &a笔, const POINTER_PEN_INFO &a信息):
	m笔(&a笔),
	m信息(a信息) {
}
S按键 C笔点::fg按键() const {
	return m按键;
}
S方向 C笔点::fg坐标() const {
	return S方向(m坐标.m这次[0], m坐标.m这次[1], 0);
}
S方向 C笔点::fg移动() const {
	return S方向(0, 0, 0);	//未实现
}
bool C笔点::fi有效() const {
	return fi进入(m信息.pointerInfo);
}
float C笔点::fg压力() const {
	return m信息.pressure / 1024.f;
}
float C笔点::fg旋转() const {
	return m信息.rotation * 数学::c度到弧度<float>;
}
std::pair<float, float> C笔点::fg倾斜() const {
	return {m信息.tiltX * 数学::c度到弧度<float>, m信息.tiltY * 数学::c度到弧度<float>};
}
void C笔点::f接收信息(const POINTER_PEN_INFO &a信息) {
	assert(m信息.pointerInfo.pointerId == a信息.pointerInfo.pointerId);
	m信息 = a信息;
}
void C笔点::f接收按键(bool a按键) {
	if (a按键) {
		m缓冲.f按下();
	} else {
		m缓冲.f松开();
	}
}
}	//namespace cflw::输入::win8