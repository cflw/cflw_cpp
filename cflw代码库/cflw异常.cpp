#include <string>
#include "cflw�쳣.h"
#include "cflw����.h"
namespace cflw::�쳣 {
Xδʵ��::Xδʵ��():
	std::runtime_error("�ú���δʵ��") {
}
X�Ӵ�::X�Ӵ�(long a):
	std::runtime_error(std::string("HRESULT:") + std::to_string(a)) {
}
}	//namespace cflw::�쳣