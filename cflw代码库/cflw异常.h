#pragma once
#include <exception>
#include <stdexcept>
namespace cflw::�쳣 {
//��׼���쳣����
using X���� = std::invalid_argument;
//δʵ��
class Xδʵ�� : public std::runtime_error {
public:
	Xδʵ��();
};
//HRESULT
class X�Ӵ� : public std::runtime_error {
public:
	X�Ӵ�(long);
	long mֵ;
};
}	//namespace cflw::�쳣