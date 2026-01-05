module;
#include <string>
export module cflw.字符串;
export import "cflw工具_循环.h";
export namespace cflw::字符串 {
bool fi数字(const std::wstring &a文本) {
	bool v可负 = true;
	bool v可点 = true;
	bool v可e = true;
	for (int i = 0; i < a文本.size(); ++i) {
		const wchar_t v字 = a文本[i];
		if (v字 == L'-') {//负号
			if (v可负) {
				v可负 = false;
				continue;
			} else {
				return false;
			}
		} else if (v字 == L'.') {
			if (v可点) {
				v可点 = false;
				continue;
			} else {
				return false;
			}
		} else if (v字 == L'e' || v字 == L'E') {
			if (v可e) {
				v可e = false;
				v可点 = false;
				v可负 = true;
				continue;
			} else {
				return false;
			}
		} else if (v字 >= L'0' && v字 <= L'9') {
			v可负 = false;
			continue;
		} else if (v字 == L'\0') {
			return i != 0;
		} else {
			return false;
		}
	}
	return true;
}
bool fi整数(const std::wstring &a文本) {
	bool v可负 = true;
	for (int i = 0; i < a文本.size(); ++i) {
		const wchar_t v字 = a文本[i];
		if (v字 == L'-') {//负号
			if (v可负) {
				v可负 = false;
				continue;
			} else {
				return false;
			}
		} else if (v字 >= L'0' && v字 <= L'9') {
			v可负 = false;
			continue;
		} else if (v字 == L'\0') {
			return i != 0;
		} else {
			return false;
		}
	}
	return true;
}
int f查找(const std::wstring &a文本, const std::wstring &a查找, int a开始) {
	for (int i = a开始; i < a文本.size(); ++i) {
		if (i >= a文本.size() - a查找.size()) {
			return -1;
		}
		bool v结果 = true;
		for (int j = 0; j < a查找.size(); ++j) {
			if (a文本[i + j] != a查找[j]) {
				v结果 = false;
				break;
			}
		}
		if (v结果) {
			return i;
		}
	}
	return -1;
}
std::wstring f截取有效数字(const std::wstring &a文本, int a位数) {
	wchar_t v[16] = L"";
	int v修改位 = 0;
	bool v小数位 = false;
	for (; v修改位 < a文本.size(); ++v修改位) {
		const wchar_t v字 = a文本[v修改位];
		if (v字 == L'.') {
			v小数位 = true;
			continue;
		}
		if ((++v修改位) <= a位数) {
			v[v修改位] = v字;
		} else {
			if (v小数位) {
				break;
			}
			v[v修改位] = L'0';
		}
	}
	return {v};
}
std::wstring f截取小数位数(const std::wstring &a文本, int a位数) {
	wchar_t v[16] = L"";
	int v小数 = -999;
	int v修改位 = 0;
	for (; v修改位 < a文本.size(); ++v修改位) {
		const wchar_t v字 = a文本[v修改位];
		v[v修改位] = v字;
		if (v字 == L'.') {
			v小数 = 0;
		}
		if ((++v小数) > a位数) {
			return {v};
		}
	}
	//
	if (v小数 < 0) {
		v[v修改位++] = L'.';
		v小数 = 0;
	}
	while ((++v小数) <= a位数) {
		v[v修改位++] = L'0';
	}
	return {v};
}
class C分离循环 : public 工具::循环::I循环<C分离循环> {
public:
	C分离循环(const std::wstring_view &a文本, const wchar_t a分隔符) :
		m文本(a文本),
		m分隔符(a分隔符),
		m开始(0),
		m结束(a文本.find(a分隔符)),
		m解引用(),
		mi继续(true) {
	}
	void f循环控制_自增() {
		if (m结束 == std::wstring_view::npos) {
			mi继续 = false;
			return;
		}
		m开始 = m结束 + 1;
		m结束 = m文本.find(m分隔符, m开始);
	}
	bool f循环控制_i继续() {
		return mi继续;
	}
	const std::wstring_view &f循环控制_解引用() {
		m解引用 = m文本.substr(m开始, m结束);
		return m解引用;
	}
private:
	const std::wstring_view &m文本;
	std::wstring_view m解引用;
	const wchar_t m分隔符;
	size_t m开始;
	size_t m结束;
	bool mi继续;
};
C分离循环 fe分离(const std::wstring_view &a文本, const wchar_t a分隔符) {
	return C分离循环(a文本, a分隔符);
}
}	//namespace cflw::字符串