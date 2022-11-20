module;
#include <fstream>
#include <string>
#include <vector>
#include <span>
#include <cassert>
#include <functional>
export module cflw.文件.二进制;
export namespace cflw::文件::二进制 {
constexpr size_t c安全大小 = 1 << 30;	//不能读写超过1GB的数据
class C读 {
public:
	C读() = default;
	~C读() {
		m文件.close();
	}
	bool f打开(const std::wstring_view &a文件名) {
		m文件.open(a文件名.data(), std::ios::in | std::ios::binary);
		return m文件.is_open();
	}
	void f读入缓存(size_t a大小) {
		assert(a大小 < c安全大小);
		if (a大小 > m缓存.size()) {
			m缓存.resize(a大小);
		}
		m文件.read((char *)m缓存.data(), a大小);
	}
	void f跳过(size_t a大小) {
		m文件.seekg(a大小, std::ios::cur);
	}
	template<typename t值>
	void f跳过值() {
		f跳过(sizeof(t值));
	}
	template<typename t容器, typename t大小 = size_t>
	void f跳过动态数组() {
		using t值 = typename t容器::value_type;
		const t大小 v数量 = f读值<t大小>();
		f跳过(sizeof(t值) * v数量);
	}
	template<typename t值>
	const t值 &f读值() {
		f读入缓存(sizeof(t值));
		return *(t值*)m缓存.data();
	}
	template<typename t值>
	const t值 &f读值(const t值 &a默认) {
		f读入缓存(sizeof(t值));
		if (m文件.good()) {
			return *(t值 *)m缓存.data();
		} else {
			return a默认;
		}
	}
	const std::byte *f读数据(size_t a大小) {
		f读入缓存(a大小);
		return m缓存.data();
	}
	template<typename t大小 = size_t>
	std::span<const std::byte> f读跨度() {	//读一个表示数据大小的值,再读数据
		t大小 v大小;
		m文件.read((char*)&v大小, sizeof(t大小));
		f读入缓存(v大小);
		return std::span<const std::byte>(m缓存.data(), v大小);
	}
	template<typename t容器, typename t大小 = size_t>
	t容器 f读动态数组() {	//读数据并构造一个容器对象,要求容器支持范围构造
		using t值 = typename t容器::value_type;
		const t大小 v数量 = f读值<t大小>();
		f读入缓存(sizeof(t值) * v数量);
		std::span<const t值> v跨度{(const t值*)m缓存.data(), v数量};
		return t容器{v跨度.begin(), v跨度.end()};
	}
	template<typename t容器, typename t大小 = size_t>
	t容器 f读动态数组(const std::function<bool(const t大小 &)> &af断言) {	//带断言,防止数据出错读到的数量过大导致内存满
		using t值 = typename t容器::value_type;
		const t大小 v数量 = f读值<t大小>();
		assert(af断言(v数量));
		f读入缓存(sizeof(t值) * v数量);
		std::span<const t值> v跨度{(const t值 *)m缓存.data(), v数量};
		return t容器{v跨度.begin(), v跨度.end()};
	}
	std::ifstream m文件;
	std::vector<std::byte> m缓存;
};
class C写 {
public:
	C写() = default;
	~C写() {
		m文件.close();
	}
	bool f打开(const std::wstring_view &a文件名) {
		m文件.open(a文件名.data(), std::ios::out | std::ios::binary);
		return m文件.is_open();
	}
	template<typename t值>
	void f写值(const t值 &a值) {
		m文件.write((const char*)&a值, sizeof(t值));
	}
	void f写数据(const std::byte *a数据, size_t a大小) {
		m文件.write((const char*)a数据, a大小);
	}
	template<typename t大小 = size_t>
	void f写跨度(const std::span<const std::byte> &a数据) {	//写入数据大小和数据
		const t大小 v大小 = (t大小)a数据.size();
		f写值(v大小);
		f写数据(a数据.data(), v大小);
	}
	template<typename t容器, typename t大小 = size_t>
	void f写动态数组(const t容器 &a数组) {	//写入数据数量的数据
		using t值 = typename t容器::value_type;
		const t大小 v数量 = (t大小)a数组.size();
		f写值(v数量);
		f写数据((const std::byte*)a数组.data(), sizeof(t值) * v数量);
	}
	std::ofstream m文件;
};
}	//namespace cflw::文件::二进制