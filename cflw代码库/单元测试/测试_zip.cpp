#include <boost/test/unit_test.hpp>
#include <string>
#include <utility>
import cflw.文件.zip;
import cflw.字符串.编码;
namespace zip = cflw::文件::zip;
namespace 字符串 = cflw::字符串;
BOOST_AUTO_TEST_SUITE(测试文件)
BOOST_AUTO_TEST_CASE(测试zip压缩, *boost::unit_test::disabled()) {
	zip::C归档 v归档;
	v归档.f打开(L"test\\test1.zip");
	const std::string v数据 = "1234567890123456789012345678901234567890";
	v归档.f归档从内存("test.txt", (const std::byte *)v数据.data(), v数据.size());
	v归档.f归档从内存("test2.txt", (const std::byte *)v数据.data(), v数据.size());
}
BOOST_AUTO_TEST_CASE(测试zip解压缩, *boost::unit_test::disabled()) {
	zip::C提取 v提取;
	v提取.f打开(L"test\\test1.zip");
	std::vector<std::byte> v数据;
	v提取.f提取到内存("test.txt", v数据);
	std::cout << 字符串::f强制转换v<std::byte, char>({v数据.data(), v数据.size()}) << "\n";
	v提取.f提取到内存("test2.txt", v数据);
	std::cout << 字符串::f强制转换v<std::byte, char>({v数据.data(), v数据.size()}) << "\n";
}
BOOST_AUTO_TEST_SUITE_END()