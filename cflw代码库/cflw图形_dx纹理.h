#pragma once
#include <memory>
#include <wincodec.h>
#include <wrl.h>
#include <dxgi.h>
#include "cflw��ѧ_ͼ��.h"
namespace cflw::ͼ��::dx���� {
//��ʽ
namespace ��ʽ {
bool f���srgb(IWICBitmapFrameDecode *);
DXGI_FORMAT f��dxgi(const GUID &);
GUID f��ͨ�ø�ʽ(const GUID &);
DXGI_FORMAT f��srgb(DXGI_FORMAT);
bool fiͨ�ø�ʽ(const GUID &);
}
//����
using Microsoft::WRL::ComPtr;
class Cֻ������;
//==============================================================================
// ����
//==============================================================================
class Cͼ�񹤳� {
public:
	~Cͼ�񹤳�();
	HRESULT f��ʼ��();
	HRESULT f��ȡͼ��(const wchar_t *, IWICBitmapFrameDecode **);
	std::unique_ptr<std::byte[]> f������������(IWICBitmapSource *, size_t *���ش�С = nullptr, size_t *�о� = nullptr, size_t *ͼ���С = nullptr);
	size_t f���ش�С(const GUID &);
	WICBitmapPlaneDescription fȡͼ������(IWICBitmapSource *);
	HRESULT fͼ��ߴ�任(IWICBitmapSource *, size_t, size_t, IWICBitmapScaler **);
	HRESULT fͼ���ʽ�任(IWICBitmapSource *, const GUID &, IWICFormatConverter **);
	std::unique_ptr<Cֻ������> fһ����ȡ(const wchar_t *);
	//��ʽת��&����
public:
	ComPtr<IWICImagingFactory> m����;
};
//==============================================================================
// �ṹ
//==============================================================================
struct S�������� {
	size_t fg��() const { return m��; }
	size_t fg��() const { return m��; }
	size_t fg���() const { return m�� * m��; }
	size_t fg���ش�С() const { return m���ش�С; }
	size_t fg�о�() const { return m�� * m���ش�С; }
	size_t fgͼ���С() const { return m�� * m�� * m���ش�С; }
	size_t fg��ʽ() const { return m��ʽ; }
	size_t m��;
	size_t m��;
	size_t m���ش�С;
	DXGI_FORMAT m��ʽ;
};
//==============================================================================
// ��������
//==============================================================================
class I���� {
public:
	virtual size_t fg��() const = 0;
	virtual size_t fg��() const = 0;
	virtual size_t fg���ش�С() const = 0;
	virtual size_t fg���() const;
	virtual size_t fg�о�() const;
	virtual size_t fgͼ���С() const;
	virtual DXGI_FORMAT fg��ʽ() const = 0;
	virtual const std::byte *fg����() const = 0;
	virtual S�������� fg����() const;
};
class Cֻ������ : public I���� {
	friend class Cͼ�񹤳�;
public:
	size_t fg��() const override;
	size_t fg��() const override;
	size_t fg���ش�С() const override;
	size_t fg���() const override;
	size_t fg�о�() const override;
	size_t fgͼ���С() const override;
	DXGI_FORMAT fg��ʽ() const override;
	const std::byte *fg����() const override;
private:
	std::unique_ptr<std::byte[]> mp����;
	DXGI_FORMAT m��ʽ = DXGI_FORMAT_UNKNOWN;
	size_t m�� = 0, m�� = 0, m�о� = 0, m��С = 0, m���ش�С = 0;
};
//�Զ�������
class C�Զ������� : public I���� {
public:
	static constexpr DXGI_FORMAT c��ʽ = DXGI_FORMAT_R32G32B32A32_FLOAT;
	static constexpr size_t c���ش�С = sizeof(��ѧ::S��ɫ);
	void f��ʼ��(size_t, size_t);
	size_t fg��() const override;
	size_t fg��() const override;
	size_t fg���ش�С() const override;
	size_t fg���() const override;
	size_t fg�о�() const override;
	size_t fgͼ���С() const override;
	DXGI_FORMAT fg��ʽ() const override;
	const std::byte *fg����() const override;
	const ��ѧ::S��ɫ *fg��ɫ����() const;
	��ѧ::S��ɫ &fg����(size_t, size_t);
	const ��ѧ::S��ɫ &fg����(size_t, size_t) const;
	��ѧ::S��ɫ f���Բ���(float, float) const;
private:
	std::unique_ptr<��ѧ::S��ɫ[]> mp����;
	size_t m�� = 0, m�� = 0;
};
}