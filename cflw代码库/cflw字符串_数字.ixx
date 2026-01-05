module;
#include <cstring>
#include <string>
export module cflw.字符串.数字;
export namespace cflw::字符串 {
template<typename t数字, typename t字符>
t数字 f到数字(const std::basic_string_view<t字符> &s) {
	if constexpr (sizeof(t数字) < sizeof(int)) {
		return static_cast<t数字>(f到数字<int>(s));
	}
}
template<> int f到数字<int, wchar_t>(const std::basic_string_view<wchar_t> &);
template<> unsigned long f到数字<unsigned long, wchar_t>(const std::basic_string_view<wchar_t> &);
template<> long f到数字<long, wchar_t>(const std::basic_string_view<wchar_t> &);
template<> long long f到数字<long long, wchar_t>(const std::basic_string_view<wchar_t> &);
template<> unsigned long long f到数字<unsigned long long, wchar_t>(const std::basic_string_view<wchar_t> &);
template<> float f到数字<float, wchar_t>(const std::basic_string_view<wchar_t> &);
template<> double f到数字<double, wchar_t>(const std::basic_string_view<wchar_t> &);
template<> long double f到数字<long double, wchar_t>(const std::basic_string_view<wchar_t> &);
}	//namespace cflw::字符串
module: private;
namespace cflw::字符串 {
template<> int f到数字<int, wchar_t>(const std::basic_string_view<wchar_t> &s) {
	return _wtoi(s.data());
}
template<> unsigned long f到数字<unsigned long, wchar_t>(const std::basic_string_view<wchar_t> &s) {
	return wcstoul(s.data(), nullptr, 10);
}
template<> long f到数字<long, wchar_t>(const std::basic_string_view<wchar_t> &s) {
	return _wtol(s.data());
}
template<> long long f到数字<long long, wchar_t>(const std::basic_string_view<wchar_t> &s) {
	return _wtoll(s.data());
}
template<> unsigned long long f到数字<unsigned long long, wchar_t>(const std::basic_string_view<wchar_t> &s) {
	return wcstoull(s.data(), nullptr, 10);
}
template<> float f到数字<float, wchar_t>(const std::basic_string_view<wchar_t> &s) {
	return wcstof(s.data(), nullptr);
}
template<> double f到数字<double, wchar_t>(const std::basic_string_view<wchar_t> &s) {
	return _wtof(s.data());
}
template<> long double f到数字<long double, wchar_t>(const std::basic_string_view<wchar_t> &s) {
	return wcstold(s.data(), nullptr);
}
}	//namespace cflw::字符串