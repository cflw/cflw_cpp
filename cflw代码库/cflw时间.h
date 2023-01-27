#pragma once
#include <chrono>
#include <deque>
#include <tuple>
namespace cflw::时间 {
//==============================================================================
// 类型
//==============================================================================
using t秒 = std::chrono::seconds;
using t时间段 = std::chrono::duration<double>;
using t时间点 = std::chrono::system_clock::time_point;	//标准时区的时间点！
using t时间秒 = std::chrono::sys_seconds;
using t时区秒 = std::chrono::zoned_seconds;	//本地时区的时间点
using t本地时间 = std::chrono::local_time<std::chrono::system_clock::duration>;
using t本地秒 = std::chrono::local_seconds;
using t日期元组 = std::tuple<unsigned short, unsigned char, unsigned char>;	//年月日
using t时间元组 = std::tuple<unsigned char, unsigned char, unsigned char>;	//时分秒
//==============================================================================
// 常量
//==============================================================================
constexpr wchar_t c紧凑格式[] = L"{:%Y%m%d%H%M%S}";	//年月日时分秒
constexpr wchar_t c斜杠分隔格式[] = L"{:%Y/%m/%d %H:%M:%S}";	//年/月/日 时:分:秒
constexpr wchar_t c横杠分隔格式[] = L"{:%Y-%m-%d %H:%M:%S}";	//年-月-日 时:分:秒
//==============================================================================
// 函数
//==============================================================================
t时间点 fg现在();	//标准时区！
t时间段 fg零();
t时间段 f间隔(const t时间点 &, const t时间点 &);
t本地时间 fg本地现在();	//本地时区！
//标准时间与本地时间与unix时间戳转换
t本地时间 f本地时间(const t时间点 &);
t本地秒 f本地秒(const t时间点 &);
t本地秒 f本地秒(const t时间秒 &);
t本地秒 f本地秒(const t本地时间 &);
time_t f时间戳(const t时间点 &);	//时间戳转换成unix时间戳
time_t f时间戳(const t本地时间 &);	//时间戳转换成unix时间戳
t时间点 f时间点(time_t);	//unix时间戳转换成时间点
t时间点 f时间点(unsigned short 年, unsigned char 月, unsigned char 日, unsigned char 时, unsigned char 分, unsigned char 秒, unsigned short 毫秒 = 0);	//从日期时间构造时间点
t本地时间 f本地时间(time_t);
t本地时间 f本地时间(unsigned short 年, unsigned char 月, unsigned char 日, unsigned char 时, unsigned char 分, unsigned char 秒, unsigned short 毫秒 = 0);
//日期时间
template<typename t时钟, typename t时期> std::chrono::year_month_day ft年月日(const std::chrono::time_point<t时钟, t时期> &);
template<typename t时钟, typename t时期> std::chrono::hh_mm_ss<t时期> ft时分秒(const std::chrono::time_point<t时钟, t时期> &);
t日期元组 f拆分年月日(const std::chrono::year_month_day &);
template<typename t时期> t时间元组 f拆分时分秒(const std::chrono::hh_mm_ss<t时期> &);
template<typename t时钟, typename t时期> t日期元组 f年月日(const std::chrono::time_point<t时钟, t时期> &);
template<typename t时钟, typename t时期> t时间元组 f时分秒(const std::chrono::time_point<t时钟, t时期> &);
uint16_t f本地时间到微软时间(const t本地时间 &);	//msdos格式,微软时间不含时区信息,参考其他压缩软件做法,使用本地时间
uint16_t f本地时间到微软日期(const t本地时间 &);	//msdos格式
t日期元组 f微软日期到年月日(uint16_t);
t时间元组 f微软时间到时分秒(uint16_t);
t本地时间 f微软日期时间到本地时间(uint16_t, uint16_t);
//==============================================================================
// 类
//==============================================================================
//时间间隔
class C时间间隔 {
public:
	C时间间隔() = default;
	void f重置();
	void f刷新();
	t时间段 f计算();
	t时间段 fg间隔() const;
private:
	t时间点 m上次时间{fg现在()};
	t时间点 m这次时间{fg现在()};
};
//计时器
class C计时器 {
public:
	C计时器() = default;
	void f重置(double 间隔 = 0);
	void fs间隔(double 间隔);
	bool f滴答();
private:
	t时间段 m持续时间{0};
	t时间段 m滴答时间{0};
	t时间点 m上次时间{fg现在()};
};
//计帧器
class C计帧器 {
public:
	static constexpr double c取数范围 = 2;	//单位:秒
	C计帧器();
	void f重置();
	double f计算();
	double fg帧速率() const;
private:
	std::deque<t时间点> m时间;
	double m帧数率 = 1;	//平滑返回值
	int m删除计数 = 0;	//防止抖动帧长时间存在
};
//秒表
class C秒表 {
public:
	C秒表() = default;
	void f重置();
	double f开始到现在();
	double f上次到现在();
private:
	t时间点 m开始时间{fg现在()};
	t时间点 m上次时间{fg现在()};
};
//自动跳帧
class C自动跳帧 {
public:
	static constexpr double c间隔 = 1.0 / 60.0;
	C自动跳帧() = default;
	void f重置(double 帧速率, double 最小帧速率);
	bool f滴答();
	std::deque<int> m跳帧记录;
	double m单帧间隔 = c间隔;
	double m跳帧上限 = 1;
	double m跳帧计数 = 0;	//跳帧:每n帧跳过n-1帧
	t时间点 m上次{fg现在()};
};
//==============================================================================
// 模板/内联函数
//==============================================================================
template<typename t时钟, typename t时期> std::chrono::year_month_day ft年月日(const std::chrono::time_point<t时钟, t时期> &a) {
	const auto v日0 = std::chrono::time_point_cast<std::chrono::days>(a);
	return std::chrono::year_month_day(v日0);
}
template<typename t时钟, typename t时期> std::chrono::hh_mm_ss<t时期> ft时分秒(const std::chrono::time_point<t时钟, t时期> &a) {
	return std::chrono::hh_mm_ss<t时期>(a.time_since_epoch());
}
template<typename t时期> t时间元组 f拆分时分秒(const std::chrono::hh_mm_ss<t时期> &a) {
	const unsigned char v时 = static_cast<unsigned char>(a.hours().count() % 24);
	const unsigned char v分 = static_cast<unsigned char>(a.minutes().count());
	const unsigned char v秒 = static_cast<unsigned char>(a.seconds().count());
	return std::make_tuple(v时, v分, v秒);
}
template<typename t时钟, typename t时期> t日期元组 f年月日(const std::chrono::time_point<t时钟, t时期> &a) {
	const std::chrono::year_month_day v年月日 = ft年月日(a);
	return f拆分年月日(v年月日);
}
template<typename t时钟, typename t时期> t时间元组 f时分秒(const std::chrono::time_point<t时钟, t时期> &a) {
	const std::chrono::hh_mm_ss<t时期> v时分秒 = ft时分秒(a);
	return f拆分时分秒(v时分秒);
}
}	//namespace cflw::时间