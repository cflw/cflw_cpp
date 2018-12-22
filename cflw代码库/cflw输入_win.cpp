#include <algorithm>
#include <memory>
#include "cflw����_win.h"
#include "cflw�Ӵ�.h"
namespace cflw::����::win {
//==============================================================================
// �ඨ��
//==============================================================================
//����
class C���� : public I���� {
	friend class C����;
public:
	S���� f����(t���� i) const override;
	void f����() override;
private:
	C������ m����{c��������};
	C���尴���� m����{c��������};
};
//���
class C��� : public I��� {
	friend class C����;
public:
	C���(HWND, float);
	S���� f����(t���� i) const override;
	S���� f����() const override;
	S���� f�ƶ�() const override;
	S���� f����() const override;
	void f����() override;
private:
	HWND m����;
	float m���� = 1;
	C���尴���� m����{c��������};
	C������ m����{c��������};
	C���巽��2 m����, m����;
};
//����
class C���� : public I���� {
	friend class C����;
public:
	C����(HWND, float);
	void f����() override;
	t���� f���ص���() const override;
	tp���ص� fg���ص�(t����) const override;
	tp���ص� fg�´��ص�() override;
	void f��������(const TOUCHINPUT *, size_t);
public:
	std::vector<std::shared_ptr<C���ص�>> ma���ص�;
	HWND m����;
	float m���� = 1;
	t���� m�´��ص����� = 0;
	t���� m�´��ص��� = 0;
};
class C���ص� : public I���ص� {
	friend class C����;
public:
	C���ص�(const C���� &, const TOUCHINPUT &);
	S���� f����() const override;
	S���� f����() const override;
	S���� f�ƶ�() const override;
	void f��������(const TOUCHINPUT &);
public:
	const C���� *m���� = nullptr;
	C���尴�� m����;
	S���� m����;
	C���巽��2 m����;
	LONG m��x = 0, m��y = 0;
	DWORD m��ʶ;
};
//==============================================================================
// ȫ�ֱ���&����
//==============================================================================
const std::tuple<int, int, int> ca��Ӧ���Ҽ�[] = {
	std::tuple<int, int, int>((int)E���̰���::e�ϵ�, (int)E���̰���::e���ϵ�, (int)E���̰���::e���ϵ�),
	std::tuple<int, int, int>((int)E���̰���::e����, (int)E���̰���::e�����, (int)E���̰���::e�ҿ���),
	std::tuple<int, int, int>((int)E���̰���::e����, (int)E���̰���::e����, (int)E���̰���::e�ҽ���),
};
//==============================================================================
// ��������
//==============================================================================
C����::~C����() {
	f����();
}
void C����::f��ʼ��(HWND a����, float a����) {
	m���� = a����;
	if (a���� <= 0) {
		m���� = �Ӵ�::C����::fg����();
	} else {
		m���� = a����;
	}
}
void C����::f����() {
	UnregisterTouchWindow(m����);
	m����.reset();
	m���.reset();
	m����.reset();
	m���� = nullptr;
}
void C����::f������Ϣ(UINT a��Ϣ, WPARAM w, LPARAM l) {
	if (m����) {
		switch (a��Ϣ) {
		case WM_KEYDOWN:
		case WM_SYSKEYDOWN:
			m����->m����.f����(w);
			//�������Ҽ�
			for (const auto &v : ca��Ӧ���Ҽ�) {
				if (std::get<0>(v) == w) {
					const int &v�� = std::get<1>(v);
					const int &v�� = std::get<2>(v);
					if (GetKeyState(v��) & 0x8000) {
						m����->m����.f����(v��);
					} 
					if (GetKeyState(v��) & 0x8000) {
						m����->m����.f����(v��);
					}
				}
			}
			break;
		case WM_KEYUP:
		case WM_SYSKEYUP:
			m����->m����.f�ɿ�(w);
			//�������Ҽ�
			for (const auto &v : ca��Ӧ���Ҽ�) {
				if (std::get<0>(v) == w) {
					const int &v�� = std::get<1>(v);
					const int &v�� = std::get<2>(v);
					if (!(GetKeyState(v��) & 0x8000)) {
						m����->m����.f�ɿ�(v��);
					}
					if (!(GetKeyState(v��) & 0x8000)) {
						m����->m����.f�ɿ�(v��);
					}
				}
			}
			break;
		case WM_ACTIVATE:
			if (w == WA_INACTIVE) {
				m����->m����.f���();
			}
		}
	}
	if (m���) {
		switch (a��Ϣ) {
		case WM_LBUTTONDOWN:
			m���->m����.f����((int)E��갴��::e���);
			break;
		case WM_RBUTTONDOWN:
			m���->m����.f����((int)E��갴��::e�Ҽ�);
			break;
		case WM_MBUTTONDOWN:
			m���->m����.f����((int)E��갴��::e�м�);
			break;
		case WM_LBUTTONUP:
			m���->m����.f�ɿ�((int)E��갴��::e���);
			break;
		case WM_RBUTTONUP:
			m���->m����.f�ɿ�((int)E��갴��::e�Ҽ�);
			break;
		case WM_MBUTTONUP:
			m���->m����.f�ɿ�((int)E��갴��::e�м�);
			break;
		case WM_MOUSEWHEEL:
			m���->m����.m���[0] = GET_WHEEL_DELTA_WPARAM(w) / 120.f;
			break;
		case WM_MOUSEHWHEEL:
			m���->m����.m���[1] = GET_WHEEL_DELTA_WPARAM(w) / 120.f;
			break;
		}
	}
	if (m����) {
		if (a��Ϣ == WM_TOUCH) {
			UINT v���� = LOWORD(w);
			HTOUCHINPUT v���� = (HTOUCHINPUT)l;
			std::unique_ptr<TOUCHINPUT[]> va���� = std::make_unique<TOUCHINPUT[]>(v����);
			if (GetTouchInputInfo(v����, v����, va����.get(), sizeof(TOUCHINPUT))) {
				m����->f��������(va����.get(), v����);
			}
			if (!CloseTouchInputHandle(v����)) {
				__debugbreak();
			}
		}
	}
}
void C����::f����() {
	if (m����) {
		m����->f����();
	}
	if (m���) {
		m���->f����();
	}
	if (m����) {
		m����->f����();
	}
}
void C����::f��������(tp���� &a) {
	if (m���� == nullptr) {
		m���� = std::make_shared<C����>();
	}
	a = m����;
}
void C����::f�������(tp��� &a) {
	if (m��� == nullptr) {
		m��� = std::make_shared<C���>(m����, m����);
	}
	a = m���;
}
void C����::f��������(tp���� &a) {
	if (m���� == nullptr) {
		m���� = std::make_shared<C����>(m����, m����);
		RegisterTouchWindow(m����, 0);
	}
	a = m����;
}
//==============================================================================
// ����
//==============================================================================
S���� C����::f����(t���� i) const {
	return m����.f����(i);
}
void C����::f����() {
	m����.f�����ϴ�();
	m����.f���Ƶ�����(m����);
}
//==============================================================================
// ���
//==============================================================================
C���::C���(HWND a����, float a����):
	m����(a����), m����(a����) {
}
S���� C���::f����(t���� i) const {
	return m����.f����(i);
}
S���� C���::f����() const {
	return m����.f��η���();
}
S���� C���::f�ƶ�() const {
	return m����.f�����();
}
S���� C���::f����() const {
	return m����.f�ϴη���();
}
void C���::f����() {
	//����
	m����.f�����ϴ�();
	m����.f���Ƶ�����(m����);
	//����&�ƶ�
	m����.f�����ϴ�();
	POINT v��;
	GetCursorPos(&v��);
	�Ӵ�::C��Ļ���굽�ͻ���������� v����(m����);
	m����.m���[0] = v����.fֱ������xf(v��.x) / m����;
	m����.m���[1] = v����.fֱ������yf(v��.y) / m����;
	//����
	m����.f�����ϴ�();
	m����.f������();
}
//==============================================================================
// ����
//==============================================================================
C����::C����(HWND a����, float a����):
	m����(a����), m����(a����) {
}
void C����::f����() {
	�Ӵ�::C��Ļ���굽�ͻ���������� v����(m����);
	for (const std::shared_ptr<C���ص�> &v : ma���ص�) {
		//����
		v->m����.f�����ϴ�();
		v->m����.f���Ƶ�����(v->m����);
		//����
		v->m����.f�����ϴ�();
		float *v��� = v->m����.m���;
		v���[0] = v����.fֱ������xf(v->m��x / 100.f) / m����;
		v���[1] = v����.fֱ������yf(v->m��y / 100.f) / m����;
	}
	//����ʧЧ���ص�
	ma���ص�.erase(std::remove_if(ma���ص�.begin(), ma���ص�.end(), [](const std::shared_ptr<C���ص�> &a)->bool {return a->m����.f�ɿ�();}), ma���ص�.end());
	m�´��ص����� = f���ص���() - m�´��ص���;
	m�´��ص��� = 0;
}
t���� C����::f���ص���() const {
	return (t����)ma���ص�.size();
}
tp���ص� C����::fg���ص�(t���� i) const {
	return ma���ص�[i];
}
tp���ص� C����::fg�´��ص�() {
	if (m�´��ص����� < f���ص���()) {
		return fg���ص�(m�´��ص�����++);
	}
	return nullptr;
}
void C����::f��������(const TOUCHINPUT *a����, size_t a����) {
	for (size_t i = 0; i != a����; ++i) {
		const TOUCHINPUT &v���� = a����[i];
		if (auto v�� = std::find_if(ma���ص�.begin(), ma���ص�.end(), [&](const std::shared_ptr<C���ص�> &a)->bool {return a->m��ʶ == v����.dwID; }); v�� != ma���ص�.end()) {
			(*v��)->f��������(v����);
		} else {
			ma���ص�.push_back(std::make_shared<C���ص�>(*this, v����));
			++m�´��ص���;
		}
	}
}
//���ص�
C���ص�::C���ص�(const C���� &a����, const TOUCHINPUT &a����):
	m����(&a����), m��ʶ(a����.dwID) {
	f��������(a����);
}
S���� C���ص�::f����() const {
	return m����;
}
S���� C���ص�::f����() const {
	return m����.f��η���();
}
S���� C���ص�::f�ƶ�() const {
	return m����.f�����();
}
void C���ص�::f��������(const TOUCHINPUT &a����) {
	m��x = a����.x;
	m��y = a����.y;
	if (a����.dwFlags & TOUCHEVENTF_MOVE) {
		m����.f����();
	} else if (a����.dwFlags & TOUCHEVENTF_UP) {
		m����.f�ɿ�();
	} else if (a����.dwFlags & TOUCHEVENTF_DOWN) {
		m����.f����();
	}
}
}	//namespace cflw::����::win