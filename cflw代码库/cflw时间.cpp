#include <algorithm>
#include "cflw时间.h"
using namespace std::chrono;
namespace cflw::时间 {
//==============================================================================
// 计算时间
//==============================================================================
t时间点 fg现在() {
	return system_clock::now();
}
t时间段 fg零() {
	return t时间段::zero();
}
t时间段 f间隔(const t时间点 &a0, const t时间点 &a1) {
	return duration_cast<t时间段>(a1 - a0);
}
t本地时间 fg本地现在() {
	return current_zone()->to_local(system_clock::now());
}
t本地时间 f本地时间(const t时间点 &a) {
	return current_zone()->to_local(a);
}
t本地秒 f本地秒(const t时间点 &a) {
	return f本地秒(f本地时间(a));
}
t本地秒 f本地秒(const t时间秒 &a) {
	return current_zone()->to_local(a);
}
t本地秒 f本地秒(const t本地时间 &a) {
	return time_point_cast<t秒>(a);
}
time_t f时间戳(const t时间点 &a) {
	return system_clock::to_time_t(a);
}
time_t f时间戳(const t本地时间 &a) {
	const auto v时间点 = current_zone()->to_sys(a);
	return system_clock::to_time_t(v时间点);
}
t时间点 f时间点(time_t a) {
	return system_clock::from_time_t(a);
}
t时间点 f时间点(unsigned short a年, unsigned char a月, unsigned char a日, unsigned char a时, unsigned char a分, unsigned char a秒, unsigned short a毫秒) {
	const auto v年月日 = year_month_day(year(a年), month(a月), day(a日));
	const auto v时分秒 = hh_mm_ss<t时间段>(t时间段(a时 * 3600 + a分 * 60 + a秒 + a毫秒 * 0.001));
	return time_point_cast<t时间点::duration>(static_cast<sys_days>(v年月日)) + duration_cast<t时间点::duration>(v时分秒.to_duration());
}
t本地时间 f本地时间(time_t a) {
	const auto v时间点 = f时间点(a);
	return f本地时间(v时间点);
}
t本地时间 f本地时间(unsigned short a年, unsigned char a月, unsigned char a日, unsigned char a时, unsigned char a分, unsigned char a秒, unsigned short a毫秒) {
	const auto v年月日 = year_month_day(year(a年), month(a月), day(a日));
	const auto v时分秒 = hh_mm_ss<t时间段>(t时间段(a时 * 3600 + a分 * 60 + a秒 + a毫秒 * 0.001));
	return time_point_cast<t本地时间::duration>(static_cast<local_days>(v年月日)) + duration_cast<t本地时间::duration>(v时分秒.to_duration());
}
t日期元组 f拆分年月日(const std::chrono::year_month_day &a) {
	const unsigned short v年 = static_cast<unsigned short>(a.year().operator int());
	const unsigned char v月 = static_cast<unsigned char>(a.month().operator unsigned int());
	const unsigned char v日 = static_cast<unsigned char>(a.day().operator unsigned int());
	return std::make_tuple(v年, v月, v日);
}
uint16_t f本地时间到微软时间(const t本地时间 &a) {
	//0~4:秒除以2(0~29), 5~10:分钟(0~59), 11~15:小时(0~23)
	const auto [v时, v分, v秒] = f时分秒(a);
	return (static_cast<uint16_t>(v时) << 11) + (static_cast<uint16_t>(v分) << 5) + (v秒 / 2);
}
uint16_t f本地时间到微软日期(const t本地时间 &a) {
	//0~4:日(1~31), 5~8:月(1~12), 9~15:年(1980年开始)
	const auto [v年, v月, v日] = f年月日(a);
	return (static_cast<uint16_t>(v年 - 1980) << 9) + (static_cast<uint16_t>(v月) << 5) + v日;
}
std::tuple<unsigned short, unsigned char, unsigned char> f微软日期到年月日(uint16_t a) {
	const unsigned short v年 = (a >> 9) + 1980;
	const unsigned char v月 = (a >> 5) & 0b1111;
	const unsigned char v日 = a & 0b11111;
	return std::make_tuple(v年, v月, v日);
}
std::tuple<unsigned char, unsigned char, unsigned char> f微软时间到时分秒(uint16_t a) {
	const unsigned char v时 = a >> 11;
	const unsigned char v分 = (a >> 5) & 0b111111;
	const unsigned char v秒 = (a & 0b11111) * 2;
	return std::make_tuple(v时, v分, v秒);
}
t本地时间 f微软日期时间到本地时间(uint16_t a日期, uint16_t a时间) {
	const auto [v年, v月, v日] = f微软日期到年月日(a日期);
	const auto [v时, v分, v秒] = f微软时间到时分秒(a时间);
	return f本地时间(v年, v月, v日, v时, v分, v秒);
}
//==============================================================================
// 时间间隔
//==============================================================================
void C时间间隔::f重置() {
	m上次时间 = fg现在();
}
void C时间间隔::f刷新() {
	m上次时间 = m这次时间;
	m这次时间 = fg现在();
}
t时间段 C时间间隔::f计算() {
	f刷新();
	return fg间隔();
}
t时间段 C时间间隔::fg间隔() const {
	return f间隔(m上次时间, m这次时间);
}
//==============================================================================
// 计时器
//==============================================================================
void C计时器::f重置(double t) {
	m持续时间 = fg零();
	m上次时间 = fg现在();
	fs间隔(t);
}
void C计时器::fs间隔(double t) {
	m滴答时间 = t时间段(t);
}
bool C计时器::f滴答() {
	auto v这次时间 = fg现在();
	if (m滴答时间.count() <= 0) {
		m上次时间 = v这次时间;
		return true;
	}
	if (v这次时间 != m上次时间) {
		auto v间隔时间 = f间隔(m上次时间, v这次时间);
		m上次时间 = v这次时间;
		m持续时间 += v间隔时间;
	}
	if (m持续时间 > m滴答时间) {
		if (m滴答时间.count() == 0) {
			m持续时间 = fg零();
		} else {
			m持续时间 -= m滴答时间;
			//丢弃多余的时间
			double v次数 = floor(m持续时间.count() / m滴答时间.count());
			if (v次数 >= 2) {
				m持续时间 -= m滴答时间 * (v次数 - 1);
			}
		}
		return true;
	} else {
		return false;
	}
}
//==============================================================================
// 计帧器
//==============================================================================
C计帧器::C计帧器() {
	m时间.push_back(fg现在());
}
void C计帧器::f重置() {
	m时间.clear();
	m时间.push_back(fg现在());
}
double C计帧器::f计算() {
	const t时间点 v这次时间 = fg现在();
	const double v这次间隔 = f间隔(m时间.back(), v这次时间).count();
	const int v保留数量 = (int)(c取数范围 / v这次间隔);
	const int v删除数量 = (int)m时间.size() - v保留数量 - 1;
	if (v删除数量 <= 0) {
		++m删除计数;
		if (m删除计数 >= 2) {
			m时间.pop_front();
			m删除计数 = 0;
		}
	} else {
		for (int i = 0; i < v删除数量; ++i) {
			m时间.pop_front();
			m删除计数 = 0;
		}
	}
	m时间.push_back(v这次时间);
	const double v总间隔 = f间隔(m时间.front(), v这次时间).count();
	const double v数量 = (double)m时间.size();
	const double v帧速率 = v数量 / (v总间隔 + (1 / m帧数率));
	m帧数率 = (m帧数率 + v帧速率) / 2;
	return m帧数率;
}
double C计帧器::fg帧速率() const {
	return m帧数率;
}
//==============================================================================
// 秒表
//==============================================================================
void C秒表::f重置() {
	m开始时间 = fg现在();
	m上次时间 = fg现在();
}
double C秒表::f开始到现在() {
	auto v这次时间 = fg现在();
	auto v持续时间 = f间隔(m开始时间, v这次时间);
	m上次时间 = v这次时间;
	return v持续时间.count();
}
double C秒表::f上次到现在() {
	auto v这次时间 = fg现在();
	auto v持续时间 = f间隔(m上次时间, v这次时间);
	m上次时间 = v这次时间;
	return v持续时间.count();
}
//==============================================================================
// 自动跳帧
//==============================================================================
void C自动跳帧::f重置(double a正常, double a最小) {
	m单帧间隔 = 1 / a正常;
	m跳帧上限 = a正常 / a最小 - 1;
	m跳帧计数 = 0;
}
bool C自动跳帧::f滴答() {
	//跳帧
	if (m跳帧计数 > 0) {
		m跳帧计数 -= 1;
		return false;
	} 
	//计时
	const t时间点 v这次 = fg现在();
	const t时间段 v间隔 = f间隔(m上次, v这次);
	const double v耗时 = v间隔.count();
	const double v跳帧 = std::min<double>(v耗时 / m单帧间隔 - 1, m跳帧上限);
	m跳帧计数 += v跳帧;
	m上次 = v这次;
	if (m跳帧计数 > 0) {
		m跳帧计数 -= 1;
		return false;
	}
	return true;
}
}	//namespace cflw::时间