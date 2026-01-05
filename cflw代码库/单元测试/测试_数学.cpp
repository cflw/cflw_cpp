#include <boost/test/unit_test.hpp>
#include <cflw数学_向量.h>
namespace 数学 = cflw::数学;
BOOST_AUTO_TEST_SUITE(测试数学)
BOOST_AUTO_TEST_CASE(测试向量2) {
	const auto c零 = 数学::S向量2{0, 0};
	BOOST_CHECK(数学::S向量2::c零 == c零);
}
BOOST_AUTO_TEST_SUITE_END()