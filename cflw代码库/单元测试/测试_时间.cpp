#include <boost/test/unit_test.hpp>
#include <cflw时间.h>
import cflw.字符串.编码;
namespace 时间 = cflw::时间;
namespace 字符串 = cflw::字符串;
BOOST_AUTO_TEST_SUITE(测试日期时间)
BOOST_AUTO_TEST_CASE(测试时间转换) {
	const 时间::t时间点 v时间 = 时间::f时间点(2022, 1, 1, 12, 0, 0);
	const std::wstring v字符串0 = std::format(时间::c斜杠分隔格式, std::chrono::time_point_cast<std::chrono::seconds>(v时间));
	BOOST_CHECK(v字符串0 == L"2022/01/01 12:00:00");
	const auto [v年, v月, v日] = 时间::f年月日(v时间);
	BOOST_CHECK(v年 == 2022);
	BOOST_CHECK(v月 == 1);
	BOOST_CHECK(v日 == 1);
	const auto [v时, v分, v秒] = 时间::f时分秒(v时间);
	BOOST_CHECK(v时 == 12);
	BOOST_CHECK(v分 == 0);
	BOOST_CHECK(v秒 == 0);
}
BOOST_AUTO_TEST_CASE(测试本地时间转换) {
	const 时间::t本地时间 v时间 = 时间::f本地时间(2022, 1, 1, 12, 0, 0);
	const std::wstring v字符串0 = std::format(时间::c斜杠分隔格式, std::chrono::time_point_cast<std::chrono::seconds>(v时间));
	BOOST_CHECK(v字符串0 == L"2022/01/01 12:00:00");
	const auto [v年, v月, v日] = 时间::f年月日(v时间);
	BOOST_CHECK(v年 == 2022);
	BOOST_CHECK(v月 == 1);
	BOOST_CHECK(v日 == 1);
	const auto [v时, v分, v秒] = 时间::f时分秒(v时间);
	BOOST_CHECK(v时 == 12);
	BOOST_CHECK(v分 == 0);
	BOOST_CHECK(v秒 == 0);
}
#define c年 2022
#define c月 1
#define c日 1
#define c时 12
#define c分 30
#define c秒 58
BOOST_AUTO_TEST_CASE(测试微软时间) {
	const 时间::t本地时间 v时间0 = 时间::f本地时间(c年, c月, c日, c时, c分, c秒);
	const uint16_t v时分秒0 = 时间::f本地时间到微软时间(v时间0);
	const uint16_t v时分秒1 = (c时 << 11) + (c分 << 5) + (c秒 / 2);
	BOOST_CHECK(v时分秒0 == v时分秒1);
	const uint16_t v年月日0 = 时间::f本地时间到微软日期(v时间0);
	const uint16_t v年月日1 = ((c年 - 1980) << 9) + (c月 << 5) + c日;
	BOOST_CHECK(v年月日0 == v年月日1);
	const 时间::t本地时间 v时间1 = 时间::f微软日期时间到本地时间(v年月日1, v时分秒1);
	BOOST_CHECK(v时间0 == v时间1);
}
BOOST_AUTO_TEST_SUITE_END()