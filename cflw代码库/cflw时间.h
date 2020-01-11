#pragma once
#include <chrono>
#include <deque>
namespace cflw::时间 {
//类型
using t时间段 = std::chrono::duration<double>;
using t时间点 = std::chrono::time_point<std::chrono::system_clock>;
t时间点 fg现在();
t时间段 fg零();
t时间段 f间隔(const t时间点 &, const t时间点 &);
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
}	//namespace cflw::时间