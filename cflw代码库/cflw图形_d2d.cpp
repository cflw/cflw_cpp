#include <wrl.h>
#include "cflw����.h"
#include "cflwͼ��_d2d.h"
#include "cflw�Ӵ�.h"
//����
using Microsoft::WRL::ComPtr;
namespace cflw::ͼ��::d2d {
//==============================================================================
// ��ά
//==============================================================================
C��ά *C��ά::g�� = nullptr;
//����
C��ά::C��ά() {
	assert(g�� == nullptr);	//����
	g�� = this;
}
HRESULT C��ά::f��ʼ��(HWND a����, float a����) {
	const �Ӵ�::S�ͻ����ߴ� v�ߴ� = �Ӵ�::S�ͻ����ߴ�::fc����(a����);
	f��ʼ��_���ڴ�С(v�ߴ�.fg��(), v�ߴ�.fg��(), a����);
	HRESULT hr;
	hr = f��ʼ��_����();
	if (FAILED(hr)) {
		return hr;
	}
	const ��ѧ::S����2 dpi = fgÿӢ�����(a����);
	const D2D1_RENDER_TARGET_PROPERTIES v��ȾĿ������ = D2D1::RenderTargetProperties(
		D2D1_RENDER_TARGET_TYPE_DEFAULT,
		D2D1::PixelFormat(),
		dpi.x, dpi.y
	);
	ComPtr<ID2D1HwndRenderTarget> v������ȾĿ��;
	hr = m��ά����->CreateHwndRenderTarget(
		v��ȾĿ������,
		D2D1::HwndRenderTargetProperties(
			a����, D2D1::SizeU(v�ߴ�.fg��(), v�ߴ�.fg��())
		),
		&v������ȾĿ��);
	if (FAILED(hr)) {
		return hr;
	}
	f��ʼ��_��ȾĿ��(v������ȾĿ��.Get());
	return S_OK;
}
HRESULT C��ά::f��ʼ��(IDXGISwapChain *a������, float a����) {
	// ע�⣺��֧��d3d12�����Ľ�����
	ComPtr<IDXGISurface> v��̨���� = nullptr;
	HRESULT hr = a������->GetBuffer(0, IID_PPV_ARGS(&v��̨����));
	if (FAILED(hr)) {
		return hr;
	}
	hr = f��ʼ��_����();
	if (FAILED(hr)) {
		return hr;
	}
	const ��ѧ::S����2 dpi = fgÿӢ�����(a����);
	const D2D1_RENDER_TARGET_PROPERTIES v��ȾĿ������ = D2D1::RenderTargetProperties(
		D2D1_RENDER_TARGET_TYPE_DEFAULT,
		D2D1::PixelFormat(DXGI_FORMAT_R8G8B8A8_UNORM, D2D1_ALPHA_MODE_PREMULTIPLIED),
		dpi.x, dpi.y);
	ComPtr<ID2D1RenderTarget> v��̨��ȾĿ��;
	hr = m��ά����->CreateDxgiSurfaceRenderTarget(v��̨����.Get(), v��ȾĿ������, &v��̨��ȾĿ��);
	if (FAILED(hr)) {
		return hr;
	}
	const D2D1_SIZE_F v��С = v��̨��ȾĿ��->GetSize();
	f��ʼ��_���ڴ�С(v��С.width, v��С.height, a����);
	f��ʼ��_��ȾĿ��(v��̨��ȾĿ��.Get());
	return S_OK;
}
HRESULT C��ά::f��ʼ��_����() {
	if (m��ά���� == nullptr) {
		HRESULT hr = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, m��ά����.GetAddressOf());
		return hr;
	} else {
		return S_OK;
	}
}
HRESULT C��ά::f��ʼ��_�豸(IDXGIDevice *a�豸) {
	HRESULT hr = f��ʼ��_����();
	if (FAILED(hr)) {
		return hr;
	}
	m��ά����->CreateDevice(a�豸, &m�豸);
	if (FAILED(hr)) {
		return hr;
	}
	hr = m�豸->CreateDeviceContext(D2D1_DEVICE_CONTEXT_OPTIONS_NONE, &m������);
	if (FAILED(hr)) {
		return hr;
	}
	f��ʼ��_��ȾĿ��(m������.Get());
	return S_OK;
}
void C��ά::f��ʼ��_���ڴ�С(float x, float y, float a����) {
	m���ڴ�С.x = x;
	m���ڴ�С.y = y;
	if (m������� == nullptr) {
		m������� = std::make_unique<C����ת��>();
	}
	m�������->fs��С(m���ڴ�С, a����);
}
void C��ά::f��ʼ��_��ȾĿ��(ID2D1RenderTarget *a) {
	m��ȾĿ�� = a;
	m��ȾĿ��->SetAntialiasMode(D2D1_ANTIALIAS_MODE_ALIASED);
}
HRESULT C��ά::f��ʼ��_����λͼ(IDXGISwapChain *a������, float a����) {
	ComPtr<IDXGISurface> v��̨���� = nullptr;
	HRESULT hr = a������->GetBuffer(0, IID_PPV_ARGS(&v��̨����));
	if (FAILED(hr)) {
		return hr;
	}
	const ��ѧ::S����2 dpi = fgÿӢ�����(a����);
	const D2D1_BITMAP_PROPERTIES1 vλͼ���� = D2D1::BitmapProperties1(
		D2D1_BITMAP_OPTIONS_TARGET | D2D1_BITMAP_OPTIONS_CANNOT_DRAW,
		D2D1::PixelFormat(DXGI_FORMAT_UNKNOWN, D2D1_ALPHA_MODE_PREMULTIPLIED),
		dpi.x, dpi.y
	);
	m������->SetDpi(dpi.x, dpi.y);
	ComPtr<ID2D1Bitmap1> vλͼĿ��;
	hr = m������->CreateBitmapFromDxgiSurface(v��̨����.Get(), &vλͼ����, &vλͼĿ��);
	if (FAILED(hr)) {
		return hr;
	}
	m������->SetTarget(vλͼĿ��.Get());
	const D2D1_SIZE_F v��С = vλͼĿ��->GetSize();
	f��ʼ��_���ڴ�С(v��С.width, v��С.height, a����);
	return S_OK;
}
void C��ά::fs����(float a) {
	float v = 96 * a;
	m��ȾĿ��->SetDpi(v, v);
}
//��ͼ
std::shared_ptr<C��ͼ��> C��ά::fc��ͼ��(const ��ѧ::S��ɫ &a��ɫ, float a���) {
	std::shared_ptr<C��ͼ��> v�� = std::make_shared<C��ͼ��>();
	v��->f��ʼ��(m��ȾĿ��.Get(), fg�������());
	v��->f��ʼ��_����(a��ɫ, a���);
	return v��;
}
std::shared_ptr<C���ı�> C��ά::fc���ı�(const ��ѧ::S��ɫ &a��ɫ) {
	std::shared_ptr<C���ı�> v�� = std::make_shared<C���ı�>();
	v��->f��ʼ��(m��ȾĿ��.Get(), fg�������());
	v��->f��ʼ��_����(a��ɫ);
	v��->m��ʽ = fgĬ���ı���ʽ();
	return v��;
}
ComPtr<ID2D1SolidColorBrush> C��ά::fc��ɫ����(const ��ѧ::S��ɫ &a��ɫ) const {
	ComPtr<ID2D1SolidColorBrush> v����;
	m��ȾĿ��->CreateSolidColorBrush(C����ת��::f��ɫ(a��ɫ), &v����);
	return v����;
}
ComPtr<ID2D1GradientStopCollection> C��ά::fc����㼯(const std::vector<S�����> &a) const {
	std::vector<D2D1_GRADIENT_STOP> va����� = C����ת��::f�����(a);
	ComPtr<ID2D1GradientStopCollection> v����㼯;
	m��ȾĿ��->CreateGradientStopCollection(va�����.data(), va�����.size(), &v����㼯);
	return v����㼯;
}
ComPtr<ID2D1LinearGradientBrush> C��ά::fc���Խ��仭��(const std::vector<S�����> &a) const {
	ComPtr<ID2D1GradientStopCollection> v����㼯 = fc����㼯(a);
	ComPtr<ID2D1LinearGradientBrush> v����;
	//δ���
	return v����;
}
ComPtr<ID2D1RadialGradientBrush> C��ά::fc���򽥱仭��(const std::vector<S�����> &a) const {
	ComPtr<ID2D1GradientStopCollection> v����㼯 = fc����㼯(a);
	ComPtr<ID2D1RadialGradientBrush> v����;
	//δ���
	return v����;
}
ComPtr<ID2D1PathGeometry> C��ά::fc·������() const {
	ComPtr<ID2D1PathGeometry> v·������;
	m��ά����->CreatePathGeometry(&v·������);
	return v·������;
}
ComPtr<ID2D1Layer> C��ά::fc��() const {
	ComPtr<ID2D1Layer> v��;
	m��ȾĿ��->CreateLayer(&v��);
	return v��;
}
C�޸�·������ C��ά::f�޸�·������(const ComPtr<ID2D1PathGeometry> &a) const {
	return C�޸�·������(a.Get(), fg�������());
}
ComPtr<C�ı�Ч��> C��ά::fc�ı�Ч��(const ��ѧ::S��ɫ &a���, const ��ѧ::S��ɫ &a���) const {
	C�ı�Ч�� *v0 = new C�ı�Ч��();
	v0->m��ά���� = m��ά����;
	v0->m��ȾĿ�� = fg��ȾĿ��();
	m��ȾĿ��->CreateSolidColorBrush(C����ת��::f��ɫ(a���), &v0->m��仭��);
	m��ȾĿ��->CreateSolidColorBrush(C����ת��::f��ɫ(a���), &v0->m��������);
	ComPtr<C�ı�Ч��> v1;
	*v1.GetAddressOf() = v0;
	return v1;
}
ComPtr<ID2D1Factory3> C��ά::fg��ά����() {
	if (m��ά���� == nullptr) {
		HRESULT hr = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, m��ά����.GetAddressOf());
	}
	return m��ά����;
}
ComPtr<ID2D1RenderTarget> C��ά::fg��ȾĿ��() const {
	return m��ȾĿ��;
}
C����ת�� &C��ά::fg�������() const {
	return *m�������;
}
C�ı����� &C��ά::fg�ı�����() {
	if (m�ı����� == nullptr) {
		m�ı����� = std::make_unique<C�ı�����>();
		m�ı�����->f��ʼ��();
	}
	return *m�ı�����;
}
C��Ⱦ���� &C��ά::fg��Ⱦ����() {
	if (m��Ⱦ���� == nullptr) {
		m��Ⱦ���� = std::make_unique<C��Ⱦ����>();
		m��Ⱦ����->m��ά = this;
	}
	return *m��Ⱦ����;
}
ComPtr<IDWriteTextFormat> C��ά::fgĬ���ı���ʽ() {
	if (mĬ���ı���ʽ == nullptr) {
		C�ı����� &v�ı����� = fg�ı�����();
		mĬ���ı���ʽ = v�ı�����.fc�ı���ʽ(S�ı���ʽ����());
	}
	return mĬ���ı���ʽ;
}
��ѧ::S����2 C��ά::fgÿӢ�����(float a����) const {
	��ѧ::S����2 dpi;
	if (a����) {
		dpi = ��ѧ::S����2::fc��ͬ(96 * a����);
	} else {
		m��ά����->GetDesktopDpi(&dpi.x, &dpi.y);
	}
	return dpi;
}
//==============================================================================
// ��Ⱦ����
//==============================================================================
void C��Ⱦ����::f��ʼ() {
	m��ά->m��ȾĿ��->BeginDraw();
}
void C��Ⱦ����::f��ʼ(UINT a) {
	m��ά->m������->SetTarget(m��ά->maλͼĿ��[a].Get());
	m��ά->m������->BeginDraw();
}
void C��Ⱦ����::f����() {
	m��ά->m��ȾĿ��->Clear(m������ɫ);
}
void C��Ⱦ����::f����() {
	m��ά->m��ȾĿ��->EndDraw();
}
void C��Ⱦ����::fs������ɫ(const ��ѧ::S��ɫ &a��ɫ) {
	m������ɫ = C����ת��::f��ɫ(a��ɫ);
}
//==============================================================================
// ��ͼ��
//==============================================================================
void C��ͼ��::f��ʼ��(ID2D1RenderTarget *a��ȾĿ��, const C����ת�� &a�������) {
	m��ȾĿ�� = a��ȾĿ��;
	m������� = &a�������;
}
void C��ͼ��::f��ʼ��_����(const ��ѧ::S��ɫ &a��ɫ, float a���) {
	const auto &v��ɫ = C����ת��::f��ɫ(a��ɫ);
	m��ȾĿ��->CreateSolidColorBrush(v��ɫ, &m����);
	fs�������(1);
}
void C��ͼ��::fs�������(float a) {
	m������� = a;
}
void C��ͼ��::fs��ɫ(const ��ѧ::S��ɫ &a) {
	const D2D1_COLOR_F v��ɫ = C����ת��::f��ɫ(a);
	m����->SetColor(v��ɫ);
}
void C��ͼ��::fs͸����(float a) {
	m����->SetOpacity(a);
}
//������
void C��ͼ��::f���Ƶ�(const ��ѧ::S����2 &a) {
	m��ȾĿ��->FillRectangle(m�������->f����_���İ뾶(a, {0.5f, 0.5f}), m����.Get());
}
void C��ͼ��::f��������(const ��ѧ::S�߶�2 &a�߶�) {
	m��ȾĿ��->DrawLine(m�������->f��(a�߶�.m��[0]), m�������->f��(a�߶�.m��[1]), m����.Get(), m�������);
}
void C��ͼ��::f���ƾ���(const ��ѧ::S���� &a����) {
	m��ȾĿ��->DrawRectangle(m�������->f����_���İ뾶(a����.m����, a����.m��ߴ�), m����.Get());
}
void C��ͼ��::f������ת����(const ��ѧ::S��ת���� &a����) {
	const auto v���� = m����.Get();
	if (a����.m���� == 0 || a����.m���� == (float)��ѧ::c��) {
		m��ȾĿ��->DrawRectangle(m�������->f����_���İ뾶(a����.m����, a����.m��ߴ�), v����, m�������);
	} else {	// ����Ƕ�
		��ѧ::S����2 v��[4] = {
			a����.m��ߴ�,
			{a����.m��ߴ�.x, -a����.m��ߴ�.y},
			{-a����.m��ߴ�.x, -a����.m��ߴ�.y},
			{-a����.m��ߴ�.x, a����.m��ߴ�.y}
		};
		for (auto &v : v��) {
			v.fs��תr(a����.m����);
			v += a����.m����;
		}
		D2D1_POINT_2F mת����[4] = {
			m�������->f��(v��[0]),
			m�������->f��(v��[1]),
			m�������->f��(v��[2]),
			m�������->f��(v��[3])
		};
		m��ȾĿ��->DrawLine(mת����[0], mת����[1], v����, m�������);
		m��ȾĿ��->DrawLine(mת����[1], mת����[2], v����, m�������);
		m��ȾĿ��->DrawLine(mת����[2], mת����[3], v����, m�������);
		m��ȾĿ��->DrawLine(mת����[3], mת����[0], v����, m�������);
	}
}
void C��ͼ��::f����Բ��(const ��ѧ::SԲ�� &aԲ��) {
	m��ȾĿ��->DrawEllipse(m�������->fԲ��(aԲ��.m����, aԲ��.m�뾶), m����.Get(), m�������);
}
void C��ͼ��::f������Բ(const ��ѧ::S��Բ &a��Բ) {
	m��ȾĿ��->DrawEllipse(m�������->f��Բ(a��Բ.m����, a��Բ.m�뾶), m����.Get(), m�������);
}
void C��ͼ��::f����Բ�Ǿ���(const ��ѧ::SԲ�Ǿ��� &a) {
	m��ȾĿ��->DrawRoundedRectangle(m�������->fԲ�Ǿ���(a.m����, a.m��ߴ�, a.m�ǰ뾶), m����.Get(), m�������);
}
//���
void C��ͼ��::f������(const ��ѧ::S���� &a) {
	m��ȾĿ��->FillRectangle(m�������->f����_���İ뾶(a.m����, a.m��ߴ�), m����.Get());
}
void C��ͼ��::f���Բ��(const ��ѧ::SԲ�� &a) {
	m��ȾĿ��->FillEllipse(m�������->fԲ��(a.m����, a.m�뾶), m����.Get());
}
void C��ͼ��::f�����Բ(const ��ѧ::S��Բ &a) {
	m��ȾĿ��->FillEllipse(m�������->f��Բ(a.m����, a.m�뾶), m����.Get());
}
void C��ͼ��::f���Բ�Ǿ���(const ��ѧ::SԲ�Ǿ��� &a) {
	m��ȾĿ��->FillRoundedRectangle(m�������->fԲ�Ǿ���(a.m����, a.m��ߴ�, a.m�ǰ뾶), m����.Get());
}
//==============================================================================
// ���ı�
//==============================================================================
void C���ı�::f��ʼ��(ID2D1RenderTarget *p��ȾĿ��, const C����ת�� &a�������) {
	m��ȾĿ�� = p��ȾĿ��;
	m������� = &a�������;
	fs����(0, 0);
}
void C���ı�::f��ʼ��_����(const ��ѧ::S��ɫ &a��ɫ) {
	m��ȾĿ��->CreateSolidColorBrush(C����ת��::f��ɫ(a��ɫ), &m����);
}
void C���ı�::fs��ʽ(IDWriteTextFormat *a) {
	m��ʽ = a;
}
void C���ı�::fs��ʽ(C�޸��ı���ʽ &a) {
	fs��ʽ(a.m��ʽ);
}
void C���ı�::fs��ɫ(const ��ѧ::S��ɫ &a) {
	m����->SetColor(C����ת��::f��ɫ(a));
}
void C���ı�::fs͸����(float a) {
	m����->SetOpacity(a);
}
void C���ı�::fs����(const ��ѧ::S����2 &a) {
	m���� = m�������->f����_��(a.x, a.y);
}
void C���ı�::fs����(const ��ѧ::S����2 &a����, const ��ѧ::S����2 &a��ߴ�) {
	m���� = m�������->f����_���İ뾶(a����, a��ߴ�);
}
void C���ı�::fs����(float x, float y) {
	m���� = m�������->f����_��(x, y);
}
void C���ı�::fs����(float l, float t, float r, float b) {
	m���� = m�������->f����_��������(l, t, r, b);
}
void C���ı�::fs����(const ��ѧ::S���� &a) {
	m���� = m�������->f����_���İ뾶(a.m����, a.m��ߴ�);
}
void C���ı�::f�����ı�(const std::wstring_view &a�ı�) const {
	m��ȾĿ��->DrawTextW(a�ı�.data(), a�ı�.size(), m��ʽ.Get(), m����, m����.Get());
}
void C���ı�::f�����ı�����(IDWriteTextLayout *a����) const {
	m��ȾĿ��->DrawTextLayout({m����.left, m����.top}, a����, m����.Get());
}
void C���ı�::f�����ı�����(IDWriteTextLayout *a����, IDWriteTextRenderer *a�ı���Ⱦ) const {
	assert(a�ı���Ⱦ);
	ComPtr<ID2D1Layer> v��;
	m��ȾĿ��->CreateLayer(&v��);
	m��ȾĿ��->PushLayer({D2D1::InfiniteRect(), nullptr, D2D1_ANTIALIAS_MODE_ALIASED, D2D1::IdentityMatrix(), 1, m����.Get(), D2D1_LAYER_OPTIONS_NONE}, v��.Get());
	a����->Draw(nullptr, a�ı���Ⱦ, m����.left, m����.top);
	m��ȾĿ��->PopLayer();
}
void C���ı�::f�����ı�����(C�޸��ı����� &a����) const {
	f�����ı�����(a����.m����);
}
//==============================================================================
// ��ά�ṹ
//==============================================================================
D2D1_POINT_2F C����ת��::f��(const ��ѧ::S����2 &a) {
	return {a.x, a.y};
}
D2D1_COLOR_F C����ת��::f��ɫ(const ��ѧ::S��ɫ &a) {
	return {a.r, a.g, a.b, a.a};
}
std::vector<D2D1_GRADIENT_STOP> C����ת��::f�����(const std::vector<S�����> &a) {
	const int n = a.size();
	std::vector<D2D1_GRADIENT_STOP> v����(n);
	for (int i = 0; i != n; ++i) {
		const S����� &v0 = a[i];
		D2D1_GRADIENT_STOP &v1 = v����[i];
		v1.position = v0.mλ��;
		v1.color = C����ת��::f��ɫ(v0.m��ɫ);
	}
	return v����;
}
//��ά�ṹ����
void C����ת��::fs��С(const ��ѧ::S����2 &a����, float a����) {
	m���ڴ�С = a���� / a����;
}
float C����ת��::x(float X) const {
	return ��ѧ::f��������x(X, m���ڴ�С.x);
}
float C����ת��::y(float Y) const {
	return ��ѧ::f��������y(Y, m���ڴ�С.y);
}
float C����ת��::f�ٷֱ�x(float X) const {
	return (X + 1) / 2 * m���ڴ�С.x;
}
float C����ת��::f�ٷֱ�y(float Y) const {
	return (1 - Y) / -2 * m���ڴ�С.y;
}
D2D1_POINT_2F C����ת��::f��(const ��ѧ::S����2 &a) const {
	return {x(a.x), y(a.y)};
}
D2D_RECT_F C����ת��::f����(const ��ѧ::S���� &a) const {
	return f����_���İ뾶(a.m����, a.m��ߴ�);
}
D2D_RECT_F C����ת��::f����_����() const {
	return {0, 0, m���ڴ�С.x, m���ڴ�С.y};
}
D2D_RECT_F C����ת��::f����_���İ뾶(const ��ѧ::S����2 &a, const ��ѧ::S����2 &r) const {
	return f����_��������(a.x-r.x, a.y+r.y, a.x+r.x, a.y-r.y);
}
D2D_RECT_F C����ת��::f����_��������(const ��ѧ::S����2 &lt, const ��ѧ::S����2 &rb) const {
	return {x(lt.x), y(lt.y), x(rb.x), y(rb.y)};
}
D2D_RECT_F C����ת��::f����_��������(float l, float t, float r, float b) const {
	return {x(l), y(t), x(r), y(b)};
}
D2D_RECT_F C����ת��::f����_��(float X, float Y) const {
	return f����_��������(X, Y, X, Y);
}
D2D1_ELLIPSE C����ת��::fԲ��(const ��ѧ::SԲ�� &a) const {
	return {f��(a.m����), a.m�뾶, a.m�뾶};
}
D2D1_ELLIPSE C����ת��::fԲ��(const ��ѧ::S����2 &a, float r) const {
	return {f��(a), r, r};
}
D2D1_ELLIPSE C����ת��::f��Բ(const ��ѧ::S��Բ &a) const {
	return f��Բ(a.m����, a.m�뾶);
}
D2D1_ELLIPSE C����ת��::f��Բ(const ��ѧ::S����2 &a, const ��ѧ::S����2 &r) const {
	return {f��(a), r.x, r.y};
}
D2D1_ROUNDED_RECT C����ת��::fԲ�Ǿ���(const ��ѧ::SԲ�Ǿ��� &a) const {
	return {f����_���İ뾶(a.m����, a.m��ߴ�), a.m�ǰ뾶.x, a.m�ǰ뾶.y};
}
D2D1_ROUNDED_RECT C����ת��::fԲ�Ǿ���(const ��ѧ::S����2 &a, const ��ѧ::S����2 &r, const ��ѧ::S����2 &rr) const {
	return {f����_���İ뾶(a, r), rr.x, rr.y};
}
//==============================================================================
// ·��
//==============================================================================
C�޸�·������::C�޸�·������(ID2D1PathGeometry *a·������, const C����ת�� &a�������):
	m�������(&a�������) {
	assert(a·������);
	HRESULT hr = a·������->Open(&m���β�);
	assert(SUCCEEDED(hr));
}
C�޸�·������::~C�޸�·������() {
	f����();
}
void C�޸�·������::f����() {
	if (m���β�) {
		if (mw��ʼ) {
			m���β�->EndFigure(D2D1_FIGURE_END_OPEN);
		}
		m���β�->Close();
		m���β� = nullptr;
	}
}
void C�޸�·������::f��(const ��ѧ::S����2 &a) {
	if (!mw��ʼ) {
		m���β�->BeginFigure(m�������->f��(a), D2D1_FIGURE_BEGIN_HOLLOW);
		m��ǰ�� = a;
		mw��ʼ = true;
	}
	if (m��ǰ�� != a) {
		m���β�->AddLine(m�������->f��(a));
		m��ǰ�� = a;
	}
}
void C�޸�·������::fֱ��(const ��ѧ::S����2 &a0, const ��ѧ::S����2 &a1) {
	f��(a0);
	f��(a1);
}
void C�޸�·������::fԲ��(const ��ѧ::S����2 &aԲ��, float a�뾶, float aʼ, float a����, bool a˳ʱ��) {
	assert(a���� <= (float)��ѧ::c����);
	const float v������� = a˳ʱ�� ? -1 : 1;
	const ��ѧ::S����2 v��ʼ�� = aԲ�� + ��ѧ::S����2::fc����r(a�뾶, aʼ);
	const ��ѧ::S����2 v������ = aԲ�� + ��ѧ::S����2::fc����r(a�뾶, aʼ + v������� * a����);
	const D2D1_SWEEP_DIRECTION v˳ʱ�� = a˳ʱ�� ? D2D1_SWEEP_DIRECTION_CLOCKWISE : D2D1_SWEEP_DIRECTION_COUNTER_CLOCKWISE;
	f��(v��ʼ��);
	const D2D1_SIZE_F v�뾶 = D2D1::SizeF(a�뾶, a�뾶);
	if (a���� > (float)��ѧ::c��) {	//���ȴ��ڦ�ʱ�ָ���⻡�Ƚӽ�2�г���ͼ�δ�������
		const ��ѧ::S����2 v�е� = aԲ�� + ��ѧ::S����2::fc����r(a�뾶, aʼ + a���� / 2 * v�������);
		m���β�->AddArc(D2D1::ArcSegment(m�������->f��(v�е�), v�뾶, 0, v˳ʱ��, D2D1_ARC_SIZE_SMALL));
	}
	m���β�->AddArc(D2D1::ArcSegment(m�������->f��(v������), v�뾶, 0, v˳ʱ��, D2D1_ARC_SIZE_SMALL));
	m��ǰ�� = v������;
}
void C�޸�·������::f����ֱ��(const std::vector<��ѧ::S����2> &a) {
	if (!mw��ʼ) {
		m���β�->BeginFigure(m�������->f��(a[0]), D2D1_FIGURE_BEGIN_HOLLOW);
		mw��ʼ = true;
	} else {
		m���β�->AddLine(m�������->f��(a[0]));
	}
	const int n = a.size();
	for (int i = 1; i != n; ++i) {
		m���β�->AddLine(m�������->f��(a[i]));
	}
}
void C�޸�·������::fƽ������(const std::vector<��ѧ::S����2> &a) {
	assert(a.size() > 1);
	std::vector<D2D1_POINT_2F> v��;
	v��.reserve(a.size());
	for (const ��ѧ::S����2 &v : a) {
		v��.push_back(m�������->f��(v));
	}
	const int n = v��.size();
	std::vector<D2D1_POINT_2F> v���Ƶ�1(n - 1);
	std::vector<D2D1_POINT_2F> v���Ƶ�2(n - 1);
	GetCurveControlPoints(v��, v���Ƶ�1, v���Ƶ�2);
	if (!mw��ʼ) {
		m���β�->BeginFigure(v��[0], D2D1_FIGURE_BEGIN_HOLLOW);
		mw��ʼ = true;
	} else {
		m���β�->AddLine(v��[0]);
	}
	for (int i = 1; i != n; ++i) {
		m���β�->AddBezier(D2D1::BezierSegment(v���Ƶ�1[i - 1], v���Ƶ�2[i - 1], v��[i]));
	}
}
void C�޸�·������::f�պ�() {
	assert(mw��ʼ);
	m���β�->EndFigure(D2D1_FIGURE_END_CLOSED);
	mw��ʼ = false;
}
void C�޸�·������::f�Ͽ�() {
	assert(mw��ʼ);
	m���β�->EndFigure(D2D1_FIGURE_END_OPEN);
	mw��ʼ = false;
}

//==============================================================================
// �ı�����
//==============================================================================
C�ı�����::C�ı�����():
	mд�ֹ���(nullptr) {
	f��ʼ��();
}
C�ı�����::~C�ı�����() {
	f����();
}
HRESULT C�ı�����::f��ʼ��() {
	if (mд�ֹ���) {
		return S_OK;
	}
	HRESULT hr = DWriteCreateFactory(DWRITE_FACTORY_TYPE_SHARED, __uuidof(IDWriteFactory), &mд�ֹ���);
	assert(SUCCEEDED(hr));
	return hr;
}
void C�ı�����::f����() {
	mд�ֹ���.Reset();
}
tp�ı���ʽ C�ı�����::fc�ı���ʽ(const S�ı���ʽ���� &a��ʽ) const {
	ComPtr<IDWriteTextFormat> v��ʽ;
	HRESULT hr = mд�ֹ���->CreateTextFormat(a��ʽ.m����.c_str(), nullptr,
		a��ʽ.m����, a��ʽ.mб��, a��ʽ.m����, a��ʽ.m�ֺ�, a��ʽ.m��������.c_str(), &v��ʽ);
	assert(SUCCEEDED(hr));
	v��ʽ->SetTextAlignment(a��ʽ.mˮƽ����);
	v��ʽ->SetParagraphAlignment(a��ʽ.m��ֱ����);
	v��ʽ->SetWordWrapping(a��ʽ.m�Զ�����);
	return v��ʽ;
}
tp�ı����� C�ı�����::fc�ı�����(const std::wstring_view &a�ı�, IDWriteTextFormat *a��ʽ) const {
	if (a��ʽ == nullptr) {
		a��ʽ = C��ά::g��->fgĬ���ı���ʽ().Get();
	}
	ComPtr<IDWriteTextLayout> v����;
	HRESULT hr = mд�ֹ���->CreateTextLayout(a�ı�.data(), a�ı�.size(), a��ʽ, 0, 0, &v����);
	return v����;
}
tp�ı����� C�ı�����::fc�ı�����(const std::wstring_view &a�ı�, const S�ı���ʽ���� &a��ʽ) const {
	tp�ı���ʽ v��ʽ = fc�ı���ʽ(a��ʽ);
	return fc�ı�����(a�ı�, v��ʽ.Get());
}
tp�ı����� C�ı�����::fc�ı�����_С��(double a����, int aС��λ��, IDWriteTextFormat *a��ʽ) {
	const float v�ֺ� = a��ʽ->GetFontSize();
	const float vС���ֺ� = v�ֺ� * 0.6f;
	std::wstring v�ַ��� = std::to_wstring(a����);
	v�ַ��� = ����::C�ı�::fС��λ��(v�ַ���, aС��λ��);
	tp�ı����� v���� = fc�ı�����(v�ַ���, a��ʽ);
	const size_t vС����λ�� = v�ַ���.find(L".");
	v����->SetFontSize(vС���ֺ�, {(UINT32)vС����λ��, (UINT32)(aС��λ�� + 1)});
	return v����;
}
C�޸��ı����� C�ı�����::f�޸��ı�����(const tp�ı����� &a����) {
	return C�޸��ı�����(a����.Get());
}
//==============================================================================
// �ı���ʽ�ṹ
//==============================================================================
void S�ı���ʽ����::fs����(const std::wstring_view &a) {
	m���� = std::wstring(a);
}
void S�ı���ʽ����::fs��������(const std::wstring_view &a) {
	m�������� = std::wstring(a);
}
void S�ı���ʽ����::fs�ֺ�(float a) {
	m�ֺ� = a;
}
void S�ı���ʽ����::fs����(int a) {
	m���� = C�ı���ʽת��::f����(a);
}
void S�ı���ʽ����::fsб��(int a) {
	mб�� = C�ı���ʽת��::fб��(a);
}
void S�ı���ʽ����::fs����(int a) {
	m���� = C�ı���ʽת��::f����(a);
}
void S�ı���ʽ����::fs�Զ�����(bool a) {
	m�Զ����� = C�ı���ʽת��::f�Զ�����(a);
}
void S�ı���ʽ����::fsˮƽ����(E�ı�ˮƽ���� a) {
	mˮƽ���� = C�ı���ʽת��::fˮƽ����(a);
}
void S�ı���ʽ����::fs��ֱ����(E�ı���ֱ���� a) {
	m��ֱ���� = C�ı���ʽת��::f��ֱ����(a);
}

//==============================================================================
// �ı���ʽ
//==============================================================================
DWRITE_FONT_WEIGHT C�ı���ʽת��::f����(int a) {
	static const DWRITE_FONT_WEIGHT ca����[] = {
		DWRITE_FONT_WEIGHT_THIN,
		DWRITE_FONT_WEIGHT_EXTRA_LIGHT,
		DWRITE_FONT_WEIGHT_LIGHT,
		DWRITE_FONT_WEIGHT_NORMAL,
		DWRITE_FONT_WEIGHT_MEDIUM,
		DWRITE_FONT_WEIGHT_DEMI_BOLD,
		DWRITE_FONT_WEIGHT_BOLD,
		DWRITE_FONT_WEIGHT_EXTRA_BOLD,
		DWRITE_FONT_WEIGHT_BLACK,
		DWRITE_FONT_WEIGHT_EXTRA_BLACK
	};
	if (a >= 0 && a <= 9) {
		return ca����[a];
	} else {
		__debugbreak();
		return DWRITE_FONT_WEIGHT_NORMAL;
	}
}
DWRITE_FONT_STYLE C�ı���ʽת��::fб��(int a) {
	static const DWRITE_FONT_STYLE caб��[] = {
		DWRITE_FONT_STYLE_NORMAL,
		DWRITE_FONT_STYLE_OBLIQUE,
		DWRITE_FONT_STYLE_ITALIC
	};
	if (a >= 0 && a <= 2) {
		return caб��[a];
	} else {
		__debugbreak();
		return DWRITE_FONT_STYLE_NORMAL;
	}
}
DWRITE_FONT_STRETCH C�ı���ʽת��::f����(int a) {
	static const DWRITE_FONT_STRETCH ca����[] = {
		DWRITE_FONT_STRETCH_UNDEFINED,
		DWRITE_FONT_STRETCH_ULTRA_CONDENSED,
		DWRITE_FONT_STRETCH_EXTRA_CONDENSED,
		DWRITE_FONT_STRETCH_CONDENSED,
		DWRITE_FONT_STRETCH_SEMI_CONDENSED,
		DWRITE_FONT_STRETCH_NORMAL,
		DWRITE_FONT_STRETCH_MEDIUM,
		DWRITE_FONT_STRETCH_SEMI_EXPANDED,
		DWRITE_FONT_STRETCH_EXPANDED,
		DWRITE_FONT_STRETCH_EXTRA_EXPANDED,
		DWRITE_FONT_STRETCH_ULTRA_EXPANDED 
	};
	if (a >= 0 && a <= 9) {
		return ca����[a];
	} else {
		__debugbreak();
		return DWRITE_FONT_STRETCH_NORMAL;
	}
}
DWRITE_TEXT_ALIGNMENT C�ı���ʽת��::fˮƽ����(E�ı�ˮƽ���� a) {
	switch (a) {
	case E�ı�ˮƽ����::e��:
		return DWRITE_TEXT_ALIGNMENT_LEADING;
	case E�ı�ˮƽ����::e��:
		return DWRITE_TEXT_ALIGNMENT_TRAILING;
	case E�ı�ˮƽ����::e��:
		return DWRITE_TEXT_ALIGNMENT_CENTER;
	default:
		throw;
	}
}
DWRITE_TEXT_ALIGNMENT C�ı���ʽת��::fˮƽ����(int a) {
	if (a < 0) {
		return DWRITE_TEXT_ALIGNMENT_LEADING;
	} else if (a > 0) {
		return DWRITE_TEXT_ALIGNMENT_TRAILING;
	} else {
		return DWRITE_TEXT_ALIGNMENT_CENTER;
	}
}
DWRITE_PARAGRAPH_ALIGNMENT C�ı���ʽת��::f��ֱ����(E�ı���ֱ���� a) {
	switch (a) {
	case E�ı���ֱ����::e��:
		return DWRITE_PARAGRAPH_ALIGNMENT_NEAR;
	case E�ı���ֱ����::e��:
		return DWRITE_PARAGRAPH_ALIGNMENT_FAR;
	case E�ı���ֱ����::e��:
		return DWRITE_PARAGRAPH_ALIGNMENT_CENTER;
	default:
		throw;
	}
}
DWRITE_PARAGRAPH_ALIGNMENT C�ı���ʽת��::f��ֱ����(int a) {
	if (a < 0) {
		return DWRITE_PARAGRAPH_ALIGNMENT_FAR;
	} else if (a > 0) {
		return DWRITE_PARAGRAPH_ALIGNMENT_NEAR;
	} else {
		return DWRITE_PARAGRAPH_ALIGNMENT_CENTER;
	}

}
DWRITE_TRIMMING C�ı���ʽת��::f����(int a) {
	DWRITE_TRIMMING v����ѡ��;
	ZeroMemory(&v����ѡ��, sizeof(v����ѡ��));
	switch (a) {
	case 0:
		v����ѡ��.granularity = DWRITE_TRIMMING_GRANULARITY_NONE;
		break;
	case 1:
		v����ѡ��.granularity = DWRITE_TRIMMING_GRANULARITY_CHARACTER;
		break;
	case 2:
		v����ѡ��.granularity = DWRITE_TRIMMING_GRANULARITY_WORD;
		break;
	}
	return v����ѡ��;
}
DWRITE_WORD_WRAPPING C�ı���ʽת��::f�Զ�����(bool a) {
	if (a) {
		return DWRITE_WORD_WRAPPING_WRAP;
	} else {
		return DWRITE_WORD_WRAPPING_NO_WRAP;
	}
}
//==============================================================================
// �ı���ʽ
//==============================================================================
C�޸��ı���ʽ::C�޸��ı���ʽ(IDWriteTextFormat *a): m��ʽ(a) {}
C�޸��ı���ʽ::~C�޸��ı���ʽ() {
}
C�޸��ı���ʽ &C�޸��ı���ʽ::fsˮƽ����(E�ı�ˮƽ���� a) {
	m��ʽ->SetTextAlignment(C�ı���ʽת��::fˮƽ����(a));
	return *this;
}
C�޸��ı���ʽ &C�޸��ı���ʽ::fs��ֱ����(E�ı���ֱ���� a) {
	m��ʽ->SetParagraphAlignment(C�ı���ʽת��::f��ֱ����(a));
	return *this;
}
C�޸��ı���ʽ &C�޸��ı���ʽ::fs����(E�ı�ˮƽ���� aˮƽ, E�ı���ֱ���� a��ֱ) {
	fsˮƽ����(aˮƽ);
	fs��ֱ����(a��ֱ);
	return *this;
}
C�޸��ı���ʽ &C�޸��ı���ʽ::fs����(int a) {
	auto m����ѡ�� = C�ı���ʽת��::f����(a);
	m��ʽ->SetTrimming(&m����ѡ��, nullptr);
	return *this;
}
//==============================================================================
// �ı���ʽ
//==============================================================================
C�޸��ı�����::C�޸��ı�����(IDWriteTextLayout *a����): 
	m����(a����) {
}
C�޸��ı�����::~C�޸��ı�����() {
}
C�޸��ı����� &C�޸��ı�����::fs����(DWRITE_FONT_WEIGHT a, DWRITE_TEXT_RANGE a��Χ) {
	m����->SetFontWeight(a, a��Χ);
	return *this;
}
C�޸��ı����� &C�޸��ı�����::fsб��(DWRITE_FONT_STYLE a, DWRITE_TEXT_RANGE a��Χ) {
	m����->SetFontStyle(a, a��Χ);
	return *this;
}
C�޸��ı����� &C�޸��ı�����::fs����(DWRITE_FONT_STRETCH a, DWRITE_TEXT_RANGE a��Χ) {
	m����->SetFontStretch(a, a��Χ);
	return *this;
}
F�ı���Χ����::F�ı���Χ����(UINT32 a): m�ı�����(a) {}
DWRITE_TEXT_RANGE F�ı���Χ����::operator()(int a��, int a��) const {
	const int v�ı����� = (int)m�ı�����;
	assert(a�� >= -v�ı�����);
	assert(a�� < v�ı�����);
	assert(a�� > -v�ı�����);
	assert(a�� <= v�ı�����);
	const int v�� = (a�� < 0) ? (v�ı����� + a��) : a��;
	const int v�� = (a�� <= 0) ? (v�ı����� + a��) : a��;
	const int v���� = v�� - v��;
	assert(v���� > 0);
	return {(UINT32)v��, (UINT32)v����};
}
//==============================================================================
// ���ı�
//==============================================================================
unsigned long C�ı�Ч��::AddRef() {
	++m���ü���;
	return m���ü���;
}
unsigned long C�ı�Ч��::Release() {
	--m���ü���;
	if (m���ü��� == 0) {
		delete this;
		return 0;
	} else {
		return m���ü���;
	}
}
HRESULT C�ı�Ч��::QueryInterface(IID const &riid, void **a) {
	if (__uuidof(IDWriteTextRenderer) == riid) {
		*a = this;
	} else if (__uuidof(IDWritePixelSnapping) == riid) {
		*a = this;
	} else if (__uuidof(IUnknown) == riid) {
		*a = this;
	} else {
		*a = nullptr;
		return E_FAIL;
	}
	this->AddRef();
	return S_OK;
}
HRESULT C�ı�Ч��::IsPixelSnappingDisabled(void*, BOOL*a) {
	*a = FALSE;
	return S_OK;
}
HRESULT C�ı�Ч��::GetCurrentTransform(void*, DWRITE_MATRIX *a����) {
	m��ȾĿ��->GetTransform(reinterpret_cast<D2D1_MATRIX_3X2_F*>(a����));
	return S_OK;
}
HRESULT C�ı�Ч��::GetPixelsPerDip(void*, FLOAT *a) {
	float x, y;
	m��ȾĿ��->GetDpi(&x, &y);
	*a = x / 96;
	return S_OK;
}
HRESULT C�ı�Ч��::DrawGlyphRun(void* a������, FLOAT x, FLOAT y, DWRITE_MEASURING_MODE a����, DWRITE_GLYPH_RUN const* a����, DWRITE_GLYPH_RUN_DESCRIPTION const* a��������, IUnknown* aЧ��) {
	HRESULT hr;
	ComPtr<ID2D1PathGeometry> v����;
	hr = m��ά����->CreatePathGeometry(&v����);
	if (FAILED(hr)) {
		return hr;
	}
	ComPtr<ID2D1GeometrySink> v·��;
	v����->Open(&v·��);
	a����->fontFace->GetGlyphRunOutline(a����->fontEmSize, a����->glyphIndices, a����->glyphAdvances, a����->glyphOffsets, a����->glyphCount, a����->isSideways, a����->bidiLevel%2, v·��.Get());
	v·��->Close();
	return f���Ƽ���(v����.Get(), x, y);
}
HRESULT C�ı�Ч��::DrawUnderline(void* a������, FLOAT x, FLOAT y, DWRITE_UNDERLINE const* a�»���, IUnknown* aЧ��) {
	HRESULT hr;
	D2D1_RECT_F v����{0, a�»���->offset, a�»���->width, a�»���->offset + a�»���->thickness};
	ComPtr<ID2D1RectangleGeometry> v���μ���;
	hr = m��ά����->CreateRectangleGeometry(&v����, &v���μ���);
	if (FAILED(hr)) {
		return hr;
	}
	return f���Ƽ���(v���μ���.Get(), x, y);
}
HRESULT C�ı�Ч��::DrawStrikethrough(void* a������, FLOAT x, FLOAT y, DWRITE_STRIKETHROUGH const* aɾ����,  IUnknown* aЧ��) {
	HRESULT hr;
	D2D1_RECT_F v����{0, aɾ����->offset, aɾ����->width, aɾ����->offset + aɾ����->thickness};
	ComPtr<ID2D1RectangleGeometry> v���μ���;
	hr = m��ά����->CreateRectangleGeometry(&v����, &v���μ���);
	if (FAILED(hr)) {
		return hr;
	}
	return f���Ƽ���(v���μ���.Get(), x, y);
}
HRESULT C�ı�Ч��::DrawInlineObject(void* a������, FLOAT x, FLOAT y, IDWriteInlineObject* inlineObject, BOOL ai�Ա�, BOOL ai����, IUnknown* aЧ��) {
	return E_NOTIMPL;
}
HRESULT C�ı�Ч��::f���Ƽ���(ID2D1Geometry *a����, float x, float y) {
	const D2D1_MATRIX_3X2_F v����{1.0f, 0.0f, 0.0f, 1.0f, x, y};
	ComPtr<ID2D1TransformedGeometry> v�任����;
	HRESULT hr = m��ά����->CreateTransformedGeometry(a����, &v����, &v�任����);
	if (FAILED(hr)) {
		return hr;
	}
	m��ȾĿ��->DrawGeometry(v�任����.Get(), m��������.Get(), m�������);
	m��ȾĿ��->FillGeometry(v�任����.Get(), m��仭��.Get());
	return S_OK;
}
void C�ı�Ч��::fs�����ɫ(const ��ѧ::S��ɫ &a) {
	m��仭��->SetColor(C����ת��::f��ɫ(a));
}
void C�ı�Ч��::fs������ɫ(const ��ѧ::S��ɫ &a) {
	m��������->SetColor(C����ת��::f��ɫ(a));
}
void C�ı�Ч��::fs�������(float a) {
	//��Ϊ������λ����������λ�ã����Կ�ȳ�2����������Ҳһ����ʾ��������Ȼ�ᱻ��ס����
	m������� = a * 2;
}
void C�ı�Ч��::fs͸����(float a) {
	m��仭��->SetOpacity(a);
	m��������->SetOpacity(a);
}
}	//namespace cflw::ͼ��::d2d