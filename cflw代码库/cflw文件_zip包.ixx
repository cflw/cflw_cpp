module;
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <functional>
#include <cassert>
#include <zlib.h>	//zlib
#include "cflw时间.h"
export module cflw.文件.zip;
export import cflw.文件.二进制;
namespace 二进制 = cflw::文件::二进制;
export namespace cflw::文件::zip {	//参考minizip实现,minizip的zipOpen()不支持宽字符,所以复制一份改一下
//==============================================================================
// deflate/inflate
//==============================================================================
int f压缩流(Bytef *dest, uLongf *destLen, const Bytef *source, uLong sourceLen) {	//compress2()压缩的数据带有zlib头尾信息,重新写一个不带头尾信息的函数
	z_stream stream = {0};
	int err = Z_OK;
	const uInt max = (uInt)-1;
	uLong left = *destLen;

	*destLen = 0;
	stream.zalloc = (alloc_func)0;
	stream.zfree = (free_func)0;
	stream.opaque = (voidpf)0;

	err = deflateInit2_(&stream, Z_BEST_COMPRESSION, Z_DEFLATED, -MAX_WBITS, 8, Z_DEFAULT_STRATEGY, ZLIB_VERSION, (int)sizeof(z_stream));	//差异
	if (err != Z_OK) return err;

	stream.next_out = dest;
	stream.avail_out = 0;
	stream.next_in = (z_const Bytef *)source;
	stream.avail_in = 0;

	do {
		if (stream.avail_out == 0) {
			stream.avail_out = left > (uLong)max ? max : (uInt)left;
			left -= stream.avail_out;
		}
		if (stream.avail_in == 0) {
			stream.avail_in = sourceLen > (uLong)max ? max : (uInt)sourceLen;
			sourceLen -= stream.avail_in;
		}
		err = deflate(&stream, sourceLen ? Z_NO_FLUSH : Z_FINISH);
	} while (err == Z_OK);

	*destLen = stream.total_out;
	deflateEnd(&stream);
	return err == Z_STREAM_END ? Z_OK : err;
}
int f解压流(Bytef *dest, uLongf *destLen, const Bytef *source, uLong *sourceLen) {
	z_stream stream = {0};
	int err = Z_OK;
	const uInt max = (uInt)-1;
	uLong len = *sourceLen;
	uLong left;
	Byte buf[1] = {0};    /* for detection of incomplete stream when *destLen == 0 */

	if (*destLen) {
		left = *destLen;
		*destLen = 0;
	} else {
		left = 1;
		dest = buf;
	}

	stream.next_in = (z_const Bytef *)source;
	stream.avail_in = 0;
	stream.zalloc = (alloc_func)0;
	stream.zfree = (free_func)0;
	stream.opaque = (voidpf)0;

	err = inflateInit2_(&stream, -MAX_WBITS, ZLIB_VERSION, (int)sizeof(z_stream));
	if (err != Z_OK) return err;

	stream.next_out = dest;
	stream.avail_out = 0;

	do {
		if (stream.avail_out == 0) {
			stream.avail_out = left > (uLong)max ? max : (uInt)left;
			left -= stream.avail_out;
		}
		if (stream.avail_in == 0) {
			stream.avail_in = len > (uLong)max ? max : (uInt)len;
			len -= stream.avail_in;
		}
		err = inflate(&stream, Z_NO_FLUSH);
	} while (err == Z_OK);

	*sourceLen -= len + stream.avail_in;
	if (dest != buf)
		*destLen = stream.total_out;
	else if (stream.total_out && err == Z_BUF_ERROR)
		left = 1;

	inflateEnd(&stream);
	return err == Z_STREAM_END ? Z_OK :
		err == Z_NEED_DICT ? Z_DATA_ERROR :
		err == Z_BUF_ERROR && left + stream.avail_out ? Z_DATA_ERROR :
		err;
}
//==============================================================================
// zip头
//==============================================================================
constexpr unsigned long c本地文件头标识 = 0x04034b50;
constexpr unsigned long c本地文件描述标识 = 0x08074b50;
constexpr unsigned long c中央目录记录标识 = 0x02014b50;
constexpr unsigned long c中央目录记录尾标识 = 0x06054b50;
constexpr unsigned long c本地文件头大小 = 30;	//可能存在内存对齐和内存优化,不能用sizeof()计算大小
constexpr unsigned long c中央目录记录大小 = 46;
constexpr unsigned long c中央目录记录尾大小 = 22;
struct S本地文件头 {	//不含扩展部分
	uint32_t m标识;	//0x04034b50
	uint16_t m解压版本;	//20=deflate
	uint16_t m标志;	//2=level9
	uint16_t m压缩方式;	//8=deflate
	uint16_t m修改时间;	//msdos格式
	uint16_t m修改日期;	//msdos格式
	uint32_t m校验码;	//crc32
	uint32_t m压缩后大小;
	uint32_t m压缩前大小;
	uint16_t m文件名长度;
	uint16_t m扩展区长度;
	//byte[n] m文件名;
	//byte[m] m扩展区;
	void fs默认() {
		m标识 = c本地文件头标识;
		m解压版本 = 20;	//deflate
		m标志 = 2;	//压缩级别9
		m压缩方式 = Z_DEFLATED;	//deflate
		const auto v时间点 = 时间::fg本地现在();
		m修改时间 = 时间::f本地时间到微软时间(v时间点);
		m修改日期 = 时间::f本地时间到微软日期(v时间点);
		m扩展区长度 = 0;
	}
};
struct S文件描述 {	//一般用不着
	uint32_t m标识;	//0x08074b50
	uint32_t m校验码;	//crc32
	uint32_t m压缩后大小;
	uint32_t m压缩前大小;
};
struct S中央目录记录 {
	uint32_t m标识;	//0x02014b50
	uint16_t m压缩版本;
	uint16_t m解压版本;
	uint16_t m标志;
	uint16_t m压缩方式;
	uint16_t m修改时间;	//msdos格式
	uint16_t m修改日期;	//msdos格式
	uint32_t m校验码;	//crc32
	uint32_t m压缩后大小;
	uint32_t m压缩前大小;
	uint16_t m文件名长度;
	uint16_t m扩展区长度;
	uint16_t m注释长度;
	uint16_t m文件开始磁盘编号;
	uint16_t m内部文件属性;
	uint32_t m外部文件属性;
	uint32_t m本地文件头偏移;
	//byte[n] m文件名;
	//byte[m] m扩展区;
	//byte[k] m注释;
	void fs从本地文件头(const S本地文件头 &a头) {
		m标识 = c中央目录记录标识;
		m压缩版本 = m解压版本 = a头.m解压版本;
		m标志 = a头.m标志;
		m压缩方式 = a头.m压缩方式;
		m修改时间 = a头.m修改时间;
		m修改日期 = a头.m修改日期;
		m校验码 = a头.m校验码;
		m压缩后大小 = a头.m压缩后大小;
		m压缩前大小 = a头.m压缩前大小;
		m文件名长度 = a头.m文件名长度;
		m扩展区长度 = a头.m扩展区长度;
		m注释长度 = 0;
		m文件开始磁盘编号 = 0;
		m内部文件属性 = 0;
		m外部文件属性 = 0;
	}
};
struct S中央目录记录尾 {
	uint32_t m标识;	//0x06054b50
	uint16_t m当前磁盘编号;
	uint16_t m中央目录开始磁盘编号;
	uint16_t m中央目录数量;
	uint16_t m文件数量;
	uint32_t m中央目录大小;
	uint32_t m中央目录偏移;
	uint16_t m注释长度;
	//byte[n] m注释;
	void fs默认() {
		m标识 = c中央目录记录尾标识;
		m当前磁盘编号 = 0;
		m中央目录开始磁盘编号 = 0;
		m注释长度 = 0;
	}
};
//==============================================================================
// zip文件
//==============================================================================
class C提取: private 二进制::C读 {
public:
	struct S文件信息 {
		uint32_t m索引 = 0;	//第几个文件
		uint32_t m头部位置 = 0;	//文件在整个zip文件中的字节偏移
		uint32_t m数据位置 = 0;	//文件在整个zip文件中的字节偏移
		uint32_t m压缩前大小 = 0;
		uint32_t m压缩后大小 = 0;
	};
	C提取() = default;
	~C提取() {
		m文件.close();
	}
	bool f打开(const std::wstring_view &a文件名) {
		m文件.open(a文件名.data(), std::ios::in | std::ios::binary);
		if (!m文件.is_open()) {
			return false;	//打开失败
		}
		//读取文件头
		S文件信息 v文件信息 = {};
		while (true) {
			const uint32_t v当前位置 = (uint32_t)m文件.tellg();
			S本地文件头 v头;
			std::string v文件名;
			if (!f读本地文件头(v头, &v文件名)) {
				if (v头.m标识 == c中央目录记录标识) {	//遇到中央目录记录区
					return true;	//到达中央目录区,正常结束
				} else if (v头.m标识 == c本地文件描述标识) {	//遇到本地文件描述区
					f跳过(12);	//跳过本地文件描述的剩余部分
					continue;
				} else {
					return false;	//可能读到错误数据
				}
			}
			v文件信息.m数据位置 = v当前位置 + c本地文件头大小 + v头.m文件名长度 + v头.m扩展区长度;
			v文件信息.m压缩前大小 = v头.m压缩前大小;
			v文件信息.m压缩后大小 = v头.m压缩后大小;
			ma文件.emplace(v文件名, v文件信息);
			++v文件信息.m索引;
			f跳过(v文件信息.m压缩后大小);	//跳过压缩数据
		}
		return false;	//异常结束
	}
	template<typename t容器>
	bool f提取到容器(const std::string &a文件名, t容器 &a数据) {
		using t值 = typename t容器::value_type;
		t容器 v数据;
		const auto vf分配 = [&](uint32_t a压缩前大小)->std::byte * {
			if (a压缩前大小 % sizeof(t值)) {
				return nullptr;	//数据大小必需是值大小的整数倍
			}
			v数据.resize(a压缩前大小 / sizeof(t值));
			return (std::byte *)v数据.data();
		};
		if (!f提取到内存0(a文件名, vf分配)) {
			return false;
		}
		a数据 = std::move(v数据);
		return true;
	}
	bool f提取到内存(const std::string &a文件名, std::vector<std::byte> &a数据) {
		std::vector<std::byte> v解压数据;
		const auto vf分配 = [&](uint32_t a压缩前大小)->std::byte * {
			v解压数据.resize(a压缩前大小);
			return v解压数据.data();
		};
		if (!f提取到内存0(a文件名, vf分配)) {
			return false;
		}
		a数据 = std::move(v解压数据);
		return true;
	}
private:
	bool f提取到内存0(const std::string &a文件名, const std::function<std::byte *(uint32_t)> &af分配) {
		m文件.clear();
		if (!m文件) {
			return false;	//状态错误
		}
		const auto vp文件 = ma文件.find(a文件名);
		if (vp文件 == ma文件.end()) {
			return false;	//找不到归档文件
		}
		//读压缩数据
		std::vector<std::byte> v压缩数据;
		const S文件信息 &v文件信息 = vp文件->second;
		v压缩数据.resize(v文件信息.m压缩后大小);
		m文件.seekg(v文件信息.m数据位置, std::ios::beg);
		assert(m文件.tellg() == v文件信息.m数据位置);
		m文件.read((char *)v压缩数据.data(), v文件信息.m压缩后大小);
		if (const size_t v读取大小 = m文件.gcount(); v读取大小 != v文件信息.m压缩后大小) {
			return false;	//读取失败
		}
		//解压
		std::byte *const vp解压数据 = af分配(v文件信息.m压缩前大小);
		if (!vp解压数据) {
			return false;	//空指针
		}
		uLong v压缩大小 = v文件信息.m压缩后大小;
		uLong v解压大小 = v文件信息.m压缩前大小;
		int v结果 = f解压流((Byte *)vp解压数据, &v解压大小, (Byte *)v压缩数据.data(), &v压缩大小);
		if (v结果 != Z_OK) {
			return false;	//解压失败
		}
		return true;
	}
	bool f读本地文件头(S本地文件头 &a, std::string *a文件名 = nullptr) {
		m文件.clear();
		if (!m文件) {
			return false;
		}
		a.m标识 = f读值<uint32_t>();
		if (a.m标识 != c本地文件头标识) {
			return false;
		}
		a.m解压版本 = f读值<uint16_t>();
		a.m标志 = f读值<uint16_t>();
		a.m压缩方式 = f读值<uint16_t>();
		a.m修改时间 = f读值<uint16_t>();
		a.m修改日期 = f读值<uint16_t>();
		a.m校验码 = f读值<uint32_t>();
		a.m压缩后大小 = f读值<uint32_t>();
		a.m压缩前大小 = f读值<uint32_t>();
		a.m文件名长度 = f读值<uint16_t>();
		a.m扩展区长度 = f读值<uint16_t>();
		if (a文件名) {
			*a文件名 = f读容器数据<std::string>(a.m文件名长度);
		} else {
			f跳过(a.m文件名长度);
		}
		return true;
	}
	bool f读中央目录记录(S中央目录记录 &a, std::string *a文件名 = nullptr) {
		m文件.clear();
		if (!m文件) {
			return false;
		}
		a.m标识 = f读值<uint32_t>();
		if (a.m标识 != c中央目录记录标识) {
			return false;
		}
		a.m压缩版本 = f读值<uint16_t>();
		a.m解压版本 = f读值<uint16_t>();
		a.m标志 = f读值<uint16_t>();
		a.m压缩方式 = f读值<uint16_t>();
		a.m修改时间 = f读值<uint16_t>();
		a.m修改日期 = f读值<uint16_t>();
		a.m校验码 = f读值<uint32_t>();
		a.m压缩后大小 = f读值<uint32_t>();
		a.m压缩前大小 = f读值<uint32_t>();
		a.m文件名长度 = f读值<uint16_t>();
		a.m扩展区长度 = f读值<uint16_t>();
		a.m注释长度 = f读值<uint16_t>();
		a.m文件开始磁盘编号 = f读值<uint16_t>();
		a.m内部文件属性 = f读值<uint16_t>();
		a.m外部文件属性 = f读值<uint32_t>();
		a.m本地文件头偏移 = f读值<uint32_t>();
		if (a文件名) {
			*a文件名 = f读容器数据<std::string>(a.m文件名长度);
		} else {
			f跳过(a.m文件名长度);
		}
		return true;
	}
	bool f读中央目录记录尾(S中央目录记录尾 &a) {
		m文件.clear();
		if (!m文件) {
			return false;
		}
		a.m标识 = f读值<uint32_t>();
		if (a.m标识 != c中央目录记录尾标识) {
			return false;
		}
		a.m当前磁盘编号 = f读值<uint16_t>();
		a.m中央目录开始磁盘编号 = f读值<uint16_t>();
		a.m中央目录数量 = f读值<uint16_t>();
		a.m文件数量 = f读值<uint16_t>();
		a.m中央目录大小 = f读值<uint32_t>();
		a.m中央目录偏移 = f读值<uint32_t>();
		a.m注释长度 = f读值<uint16_t>();
		return true;
	}
	std::map<std::string, S文件信息> ma文件;
};
class C归档 : private 二进制::C写 {
public:
	struct S文件信息 {
		size_t m头部位置;
		size_t m数据位置;
		S本地文件头 m头;
		std::string m文件名;
	};
	C归档() = default;
	~C归档() {
		f关闭();
	}
	using 二进制::C写::f打开;
	void f关闭() {	//覆盖 C写::f关闭
		if (!m文件.is_open()) {
			return;
		}
		S中央目录记录尾 v尾 = {0};
		v尾.fs默认();
		v尾.m中央目录数量 = v尾.m文件数量 = (uint16_t)ma文件.size();
		v尾.m中央目录偏移 = (uint32_t)m文件.tellp();
		//写入中央目录记录
		for (const S文件信息 &v文件 : ma文件) {
			S中央目录记录 v中央目录记录;
			v中央目录记录.fs从本地文件头(v文件.m头);
			v中央目录记录.m本地文件头偏移 = (uint32_t)v文件.m头部位置;
			f写中央目录记录(v中央目录记录);
			f写容器数据(v文件.m文件名);
			v尾.m中央目录大小 += c中央目录记录大小 + (uint32_t)v文件.m文件名.size();
		}
		//写入中央目录记录尾
		f写中央目录记录尾(v尾);
		//关闭
		m文件.close();
	}
	bool f归档从文件(const std::string_view &a文件名, const std::wstring_view &a硬盘文件名) {
		return false;	//未实现
	}
	template<typename t容器>	//必需是连续容器
	bool f归档从容器(const std::string_view &a文件名, const t容器 &a容器) {
		using t值 = typename t容器::value_type;
		return f归档从内存(a文件名, (const std::byte *)a容器.data(), sizeof(t值) * a容器.size());
	}
	bool f归档从内存(const std::string_view &a文件名, const std::byte *a数据, size_t a大小) {
		if (!m文件) {
			return false;
		}
		//统计
		S文件信息 v文件 = {0};
		v文件.m头部位置 = (size_t)m文件.tellp();
		S本地文件头 &v头 = v文件.m头;
		v头.fs默认();
		v头.m压缩前大小 = (uint32_t)a大小;
		v头.m压缩后大小 = compressBound(v头.m压缩前大小);
		//压缩数据
		std::vector<std::byte> v压缩数据(v头.m压缩后大小);
		int v结果 = 0;
		v结果 = f压缩流((Byte *)v压缩数据.data(), (uLong*)&v头.m压缩后大小, (const Byte *)a数据, (uLong)a大小);
		if (v结果 != Z_OK) {
			return false;
		}
		//计算校验码
		uLong crc = crc32_z(0, nullptr, 0);
		crc = crc32_z(crc, (const Byte *)a数据, a大小);
		v头.m校验码 = crc;
		//其他
		v头.m文件名长度 = (uint16_t)a文件名.size();
		v文件.m数据位置 = v文件.m头部位置 + c本地文件头大小 + v头.m文件名长度;
		//写入
		f写本地文件头(v头);
		f写容器数据(a文件名);
		f写数据(v压缩数据.data(), v头.m压缩后大小);
		//结束
		v文件.m文件名 = a文件名;
		ma文件.push_back(v文件);
		return true;
	}
private:
	void f写本地文件头(const S本地文件头 &a) {	//可能存在内存对齐和内存优化,不能整个写入,改成逐个写入
		f写值(a.m标识);
		f写值(a.m解压版本);
		f写值(a.m标志);
		f写值(a.m压缩方式);
		f写值(a.m修改时间);
		f写值(a.m修改日期);
		f写值(a.m校验码);
		f写值(a.m压缩后大小);
		f写值(a.m压缩前大小);
		f写值(a.m文件名长度);
		f写值(a.m扩展区长度);
	}
	void f写中央目录记录(const S中央目录记录 &a) {
		f写值(a.m标识);
		f写值(a.m压缩版本);
		f写值(a.m解压版本);
		f写值(a.m标志);
		f写值(a.m压缩方式);
		f写值(a.m修改时间);
		f写值(a.m修改日期);
		f写值(a.m校验码);
		f写值(a.m压缩后大小);
		f写值(a.m压缩前大小);
		f写值(a.m文件名长度);
		f写值(a.m扩展区长度);
		f写值(a.m注释长度);
		f写值(a.m文件开始磁盘编号);
		f写值(a.m内部文件属性);
		f写值(a.m外部文件属性);
		f写值(a.m本地文件头偏移);
	}
	void f写中央目录记录尾(const S中央目录记录尾 &a) {
		f写值(a.m标识);
		f写值(a.m当前磁盘编号);
		f写值(a.m中央目录开始磁盘编号);
		f写值(a.m中央目录数量);
		f写值(a.m文件数量);
		f写值(a.m中央目录大小);
		f写值(a.m中央目录偏移);
		f写值(a.m注释长度);
	}
	std::vector<S文件信息> ma文件;
};
}	//namespace cflw::文件::zip