#include <assert.h>
#include "cflw��ѧ.h"
#include "cflw��ѧ_����.h"
namespace cflw {
namespace ��ѧ {
//==============================================================================
// ������ѧ����
//==============================================================================
int fȡ����λ��(const int &x) {
	int v = x;
	int i = 0;
	while (v != 0) {
		v /= 10;
		++i;
	}
	return i;
}
int f10�Ĵη�(const int &x) {
	return (int)pow(10.0, x);
}
//����
float f����(const float &x, const float &y) {
	return sqrt(x * x + y * y);
}
float f����(float p��, float p����) {
	return 2 * p���� - p��;
}
float fλ��(float x, float y) {
	return y - x;
}
//����������ֱ������任
float f��������x(float x, float s) {
	return x + s / 2;
}
float f��������y(float y, float s) {
	return s / 2 - y;
}
float fֱ������x(float x, float s) {
	return x - s / 2;
}
float fֱ������y(float y, float s) {
	return s / 2 - y;
}
float f��������x(float x, float s, float d) {
	return f��������x(x * f��������(s, d), d);
}
float f��������y(float y, float s, float d) {
	return f��������y(y * f��������(s, d), d);
}
float fֱ������x(float x, float s, float d) {
	return fֱ������x(x * fֱ������(s, d), d);
}
float fֱ������y(float y, float s, float d) {
	return fֱ������y(y * fֱ������(s, d), d);
}
float f��������(float s, float d) {
	return d / s;
}
float fֱ������(float s, float d) {
	return d / s;
}
//ģ��ʵ�л�
template<> int fȡ����<bool>(const bool &x) {
	return x ? 1 : -1;
}
//λ�ù�ϵ
/*
std::weak_equality operator <=>(Eλ�ù�ϵ p, int n) {
	assert(n == 0);
	if (p < Eλ�ù�ϵ::e����) {
		return std::weak_equality::less;
	} else if (p0 > Eλ�ù�ϵ::e����) {
		return std::weak_equality::greater;
	} else {
		return std::weak_equality::equivalent;
	}
}
*/
//==============================================================================
}}	//�����ռ����