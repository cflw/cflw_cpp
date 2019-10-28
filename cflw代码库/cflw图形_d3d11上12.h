#pragma once
#include <vector>
#include <wrl.h>
#include <d3d11on12.h>
#ifdef _WINDOWS
#pragma comment(lib, "d3d11.lib")
#endif
//12
namespace cflw::图形::d3d12 {
class C三维;
}
//上
namespace cflw::图形::d3d11上12 {
using Microsoft::WRL::ComPtr;
class C三维 {
public:
	HRESULT f初始化(d3d12::C三维 &);
	HRESULT f创建渲染目标资源(ID3D12Resource *);
	void f开始(UINT 帧索引);
	void f结束();
	std::vector<ComPtr<ID3D11Resource>> &fe渲染目标资源();
	//对象
	ComPtr<IDXGIDevice> fg基础设备() const;
private:
	ComPtr<ID3D11On12Device> m设备;
	ComPtr<ID3D11DeviceContext> m上下文;
	std::vector<ComPtr<ID3D11Resource>> ma渲染目标资源;
	UINT m帧索引;
};
}