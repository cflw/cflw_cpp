#pragma once
#include <array>
#include <memory>
#include <windef.h>
#include "cflw����.h"
#pragma comment(lib, "xinput.lib")
namespace cflw::����::xi {
using namespace cflw::����;
bool IsXInputDevice(const GUID *pGuidProductFromDirectInput);
//==============================================================================
enum class E�ֱ����� {
	e��,
	e��,
	e��,
	e��,
	e��ʼ,
	e����,
	e��ҡ��,
	e��ҡ��,
	e���,
	e�Ҽ�,
	e����0,
	e����1,
	a,
	b,
	x,
	y,
};
enum class E�ֱ����� {
	e�����,
	e��ҡ��,
	e��ҡ��,
	e�ϲ�
};
enum class E�ֱ����� {
	e��,
	e��
};
//==============================================================================
class C�ֱ�;
class C���� {
public:
	C����();
	~C����();
	void f�����ֱ�(tp�ֱ� &, DWORD = 0);
	void f����();
private:
	std::array<std::shared_ptr<C�ֱ�>, 4> ma�ֱ�;
};
//==============================================================================
}	//namespace cflw::����::xi