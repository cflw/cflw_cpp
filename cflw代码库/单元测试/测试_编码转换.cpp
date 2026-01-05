#include <boost/test/unit_test.hpp>
#include <string>
import cflw.字符串.编码;
namespace 字符串 = cflw::字符串;
BOOST_AUTO_TEST_SUITE(测试字符串)
BOOST_AUTO_TEST_CASE(测试编码转换) {
	const std::wstring v字符串0 = L"测试1234asdf测试";
	//char和wchar_t互转
	const std::string v字符串1 = 字符串::f编码转换<wchar_t, char>(v字符串0);
	BOOST_CHECK(v字符串1 == "测试1234asdf测试");
	const std::wstring v字符串2 = 字符串::f编码转换<char, wchar_t>(v字符串1);
	BOOST_CHECK(v字符串2 == L"测试1234asdf测试");
	//char8_t和wchar_t互转
	const std::u8string v字符串3 = 字符串::f编码转换<wchar_t, char8_t>(v字符串0);
	BOOST_CHECK(v字符串3 == u8"测试1234asdf测试");
	const std::wstring v字符串4 = 字符串::f编码转换<char8_t, wchar_t>(v字符串3);
	BOOST_CHECK(v字符串4 == L"测试1234asdf测试");
}
BOOST_AUTO_TEST_SUITE_END()