module;
#include <boost/test/unit_test.hpp>;
export module cflw.测试.xml;
import <iostream>;
import cflw.文件.xml;
import cflw.字符串.编码;
namespace xml = cflw::文件::xml;
namespace 字符串 = cflw::字符串;
BOOST_AUTO_TEST_SUITE(测试文件)
BOOST_AUTO_TEST_CASE(测试读xml, *boost::unit_test::enabled()) {
	xml::t文档 v文档;
	xml::f打开(v文档, L"test\\read.xml");
	std::wostringstream v流;
	v文档.save(v流);
	std::cout << 字符串::f编码转换<char>(v流.str()) << "\n";
}
BOOST_AUTO_TEST_CASE(测试写xml, *boost::unit_test::enabled()) {
	xml::t文档 v文档;
	xml::t节点 v根节点 = v文档.append_child(L"根");
	xml::t节点 v头部节点 = v根节点.append_child(L"头部");
	xml::t节点 v标识节点 = v头部节点.append_child(L"标识");
	v标识节点.text() = L"1234";
	xml::t节点 v数据节点 = v根节点.append_child(L"数据");
	xml::t节点 v测试节点 = v数据节点.append_child(L"测试");
	v测试节点.text() = L"4321";
	xml::f保存(v文档, L"test\\write.xml");
	std::cout << "保存到: test\\write.xml";
}
BOOST_AUTO_TEST_SUITE_END()