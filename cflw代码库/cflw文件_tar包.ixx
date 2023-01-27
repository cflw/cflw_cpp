module;
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <functional>
#include <cassert>
#include <ctime>
export module cflw.文件.tar;
export import cflw.文件.二进制;
namespace 二进制 = cflw::文件::二进制;
export namespace cflw::文件::tar {
//==============================================================================
// 结构
//==============================================================================
inline const char CHKBLANKS[] = "        ";
inline const char TMAGIC[] = "ustar  ";
inline const char c空块[512] = {};
size_t f计算校验和(const unsigned char *);
struct posix_tar_header {	//posix_tar_header
	char name[100];
	char mode[8];
	char uid[8];
	char gid[8];
	char size[12];
	char mtime[12];
	char chksum[8];
	char typeflag;
	char linkname[100];
	char magic[8];
	char uname[32];
	char gname[32];
	char devmajor[8];
	char devminor[8];
	char prefix[155];
	char padding[12];
	//get/set
	void fs默认值() {
		fs文件权限(0777);
		fs用户id(1);
		fs组id(1);
		fs修改时间(time(0));
		fs魔数();
		fs用户名称("root");
		fs组名称("root");
	}
	std::string_view fg文件名() {
		return {name};
	}
	void fs文件名(std::string_view a文件名) {
		memcpy(name, a文件名.data(), a文件名.size());
	}
	int fg文件权限() {
		return strtol(mode, nullptr, 8);
	}
	void fs文件权限(int a权限) {
		snprintf(mode, sizeof(mode), "%07o", a权限);
	}
	int fg用户id() {
		return strtol(uid, nullptr, 8);
	}
	void fs用户id(int id) {
		snprintf(uid, sizeof(uid), "%07o", id);
	}
	int fg组id() {
		return strtol(gid, nullptr, 8);
	}
	void fs组id(int id) {
		snprintf(gid, sizeof(gid), "%07o", id);
	}
	size_t fg文件大小() {
		return strtoull(size, nullptr, 8);
	}
	void fs文件大小(size_t a) {
		snprintf(size, sizeof(size), "%011o", (int)a);
	}
	time_t fg修改时间() {
		return strtoull(mtime, nullptr, 8);
	}
	void fs修改时间(time_t t) {
		snprintf(mtime, sizeof(mtime), "%011o", (int)t);
	}
	int fg校验和() {
		return strtol(chksum, nullptr, 8);
	}
	void fs校验和() {	//自动计算校验和
		size_t v和 = f计算校验和((unsigned char *)this);
		snprintf(chksum, sizeof(chksum), "%06o", (int)v和);
		chksum[6] = '\0';
		chksum[7] = ' ';
	}
	bool fi校验和() {
		return fg校验和() == (int)f计算校验和((unsigned char *)this);
	}
	void fs魔数() {
		memcpy(magic, TMAGIC, sizeof(magic));
	}
	bool fi魔数() {
		return (memcmp(magic, TMAGIC, 8) == 0);
	}
	std::string_view fg用户名称() {
		return {uname};
	}
	void fs用户名称(std::string_view a名称) {
		memcpy(uname, a名称.data(), a名称.size());
	}
	std::string_view fg组名称() {
		return {gname};
	}
	void fs组名称(std::string_view a名称) {
		memcpy(gname, a名称.data(), a名称.size());
	}
};
struct S文件信息 {
	size_t m索引;	//这是tar文件中第几个文件
	size_t m头部位置;	//文件在整个tar文件中的字节偏移
	size_t m数据位置;	//文件在整个tar文件中的字节偏移
	size_t m数据大小;	//该文件大小
};
size_t f计算校验和(const unsigned char *a) {	//只计算
	unsigned char v数据[512];
	memcpy(v数据, a, 512);
	memcpy(v数据 + 148, CHKBLANKS, 8);
	const unsigned char *const v开始 = v数据;
	const unsigned char *const v结束 = v开始 + 512;
	size_t v和 = 0;
	for (const unsigned char *p = v开始; p != v结束; ++p) {
		v和 += *p;
	}
	return v和;
}
size_t f填充大小(size_t a大小) {	//给定数据大小,计算需要填充的大小
	return 512 - a大小 % 512;
}
size_t f块大小(size_t a大小) {	//给定数据大小,计算数据+填充的大小
	return ((a大小 - 1) / 512 + 1) * 512;
}
//==============================================================================
// 文件
//==============================================================================
class C提取 {
public:
	C提取() = default;
	~C提取() {
		m文件.close();
	}
	bool f打开(const std::wstring_view &a文件名) {
		m文件.open(a文件名.data(), std::ios::in | std::ios::binary);
		if (!m文件.is_open()) {
			return false;	//打开失败
		}
		size_t v索引 = 0;
		size_t v位置 = 0;
		while (m文件.good()) {
			posix_tar_header v头;
			m文件.read((char *)&v头, 512);
			if (const size_t v读取大小 = m文件.gcount(); v读取大小 == 0) {
				return true;	//什么都没读到,可能结束
			} else if (v读取大小 != 512) {
				return false;	//读取到的头部不完整,可能数据错误
			}
			//验证文件
			if (!v头.fi校验和()) {
				return false;	//校验失败
			}
			//读取头
			S文件信息 v信息;
			v信息.m索引 = ++v索引;
			v信息.m头部位置 = v位置;
			v信息.m数据位置 = (v位置 += 512);
			v信息.m数据大小 = v头.fg文件大小();
			ma文件.emplace(v头.fg文件名(), v信息);
			const size_t v数据块大小 = f块大小(v信息.m数据大小);
			m文件.ignore(v数据块大小);	//跳过数据块
			v位置 += v数据块大小;
		}
		return true;
	}
	bool f提取到文件(const std::string &a文件名, const std::wstring_view &a硬盘文件名) {
		std::vector<std::byte> v数据;
		const auto vf分配 = [&](size_t a大小)->std::byte * {
			v数据.resize(a大小);
			return v数据.data();
		};
		if (!f提取到内存0(a文件名, vf分配)) {
			return false;
		}
		if (!二进制::f写入文件(a硬盘文件名, v数据.data(), v数据.size())) {
			return false;
		}
		return true;
	}
	template<typename t容器>
	bool f提取到容器(const std::string &a文件名, t容器 &a数据) {
		using t值 = typename t容器::value_type;
		t容器 v数据;
		const auto vf分配 = [&](size_t a大小)->std::byte * {
			if (a大小 % sizeof(t值)) {
				return nullptr;	//数据大小必需是值大小的整数倍
			}
			v数据.resize(a大小 / sizeof(t值));
			return (std::byte *)v数据.data();
		};
		if (!f提取到内存0(a文件名, vf分配)) {
			return false;
		}
		a数据 = std::move(v数据);
		return true;
	}
	bool f提取到内存(const std::string &a文件名, std::vector<std::byte> &a数据) {
		std::vector<std::byte> v数据;
		auto vf分配 = [&](size_t a大小)->std::byte * {
			v数据.resize(a大小);
			return v数据.data();
		};
		if (!f提取到内存0(a文件名, vf分配)) {
			return false;
		}
		a数据 = std::move(v数据);
		return true;
	}
private:
	bool f提取到内存0(const std::string &a文件名, const std::function<std::byte *(size_t)> &af分配) {
		m文件.clear();
		if (!m文件) {
			return false;	//状态错误
		}
		const auto vp文件 = ma文件.find(a文件名);
		if (vp文件 == ma文件.end()) {
			return false;	//找不到归档文件
		}
		const S文件信息 &v文件信息 = vp文件->second;
		std::byte *const vp数据 = af分配(v文件信息.m数据大小);
		if (!vp数据) {
			return false;	//空指针
		}
		m文件.seekg(v文件信息.m数据位置, std::ios::beg);
		assert(m文件.tellg() == v文件信息.m数据位置);
		m文件.read((char *)vp数据, v文件信息.m数据大小);
		if (const size_t v读取大小 = m文件.gcount(); v读取大小 != v文件信息.m数据大小) {
			return false;
		}
		return true;
	}
	std::ifstream m文件;
	std::map<std::string, S文件信息> ma文件;
};
class C归档 {
public:
	C归档() = default;
	~C归档() {
		m文件.close();
	}
	bool f打开(const std::wstring_view &a文件名) {
		m文件.open(a文件名.data(), std::ios::out | std::ios::binary);
		return m文件.is_open();
	}
	bool f归档从文件(const std::string_view &a文件名, const std::wstring_view &a硬盘文件名) {
		if (!m文件) {
			return false;	//状态错误
		}
		std::vector<std::byte> v数据;
		if (!二进制::f读取文件(a硬盘文件名, v数据)) {
			return false;
		}
		const size_t v文件大小 = v数据.size();
		//写入
		posix_tar_header v头 = {};
		v头.fs默认值();
		v头.fs文件名(a文件名);
		v头.fs文件大小(v文件大小);
		v头.fs校验和();
		m文件.write((const char *)&v头, 512);
		m文件.write((const char *)v数据.data(), v文件大小);
		if (size_t v填充大小 = f填充大小(v文件大小)) {
			m文件.write(c空块, v填充大小);
		}
		return true;
	}
	template<typename t容器>	//必需是连续容器
	bool f归档从容器(const std::string_view &a文件名, const t容器 &a容器) {
		using t值 = typename t容器::value_type;
		return f归档从内存(a文件名, (const std::byte *)a容器.data(), sizeof(t值) * a容器.size());
	}
	bool f归档从内存(const std::string_view &a文件名, const std::byte *a数据, size_t a大小) {
		if (!m文件) {
			return false;	//状态错误
		}
		posix_tar_header v头 = {};
		v头.fs默认值();
		v头.fs文件名(a文件名);
		v头.fs文件大小(a大小);
		v头.fs校验和();
		m文件.write((const char *)&v头, 512);
		m文件.write((const char *)a数据, a大小);
		if (size_t v填充大小 = f填充大小(a大小)) {
			m文件.write(c空块, v填充大小);
		}
		return true;
	}
private:
	std::ofstream m文件;
};
}	//namespace cflw::文件::tar