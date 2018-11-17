#pragma once
#include <vector>
#include <wrl.h>
#include <d3d11on12.h>
#ifdef _WINDOWS
#pragma comment(lib, "d3d11.lib")
#endif
//12
namespace cflw::ͼ��::d3d12 {
class C��ά;
}
//��
namespace cflw::ͼ��::d3d11��12 {
using Microsoft::WRL::ComPtr;
class C��ά {
public:
	HRESULT f��ʼ��(d3d12::C��ά &);
	HRESULT f������ȾĿ����Դ(ID3D12Resource *);
	void f��ʼ(UINT ֡����);
	void f����();
	//����
	ComPtr<IDXGIDevice> fg�����豸() const;
public:
	ComPtr<ID3D11On12Device> m�豸;
	ComPtr<ID3D11DeviceContext> m������;
	std::vector<ComPtr<ID3D11Resource>> ma��ȾĿ����Դ;
	UINT m֡����;
};
}