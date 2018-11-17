#pragma once
//����
#include <vector>
#include <string>
#include <string_view>
#include <d2d1_3.h>
#include <DWrite.h>
#include <dxgi1_4.h>
#include <wrl.h>
#include "cflw����.h"
#include "cflw��ѧ.h"
#include "cflw��ѧ_ͼ��.h"
#include "cflw��ѧ_ƽ�漸��.h"
//����
#ifdef _WINDOWS
#pragma comment(lib, "d2d1.lib")
#pragma comment(lib, "dwrite.lib")
#endif
//
void GetCurveControlPoints(
	__in const std::vector<D2D1_POINT_2F>& knots,
	__out std::vector<D2D1_POINT_2F>& firstCtrlPt,
	__out std::vector<D2D1_POINT_2F>& secondCtrlPt);
HRESULT CreateBezierSpline(
	__in ID2D1Factory* pD2dFactory,
	__in const std::vector<D2D1_POINT_2F>& points,
	__out ID2D1PathGeometry** ppPathGeometry);
//�����ռ�
namespace cflw::ͼ��::d2d {
//�ⲿ
using Microsoft::WRL::ComPtr;
typedef ComPtr<ID2D1RenderTarget> tp��ȾĿ��;
typedef ComPtr<ID2D1SolidColorBrush> tp��ɫ����;
typedef ComPtr<ID2D1GradientStopCollection> tp����㼯;
typedef ComPtr<ID2D1LinearGradientBrush> tp���Խ��仭��;
typedef ComPtr<ID2D1RadialGradientBrush> tp���򽥱仭��;
typedef ComPtr<IDWriteTextFormat> tp�ı���ʽ;
typedef ComPtr<IDWriteTextLayout> tp�ı�����;
typedef ComPtr<ID2D1PathGeometry> tp·������;
typedef ComPtr<ID2D1GeometrySink> tp���β�;
typedef ComPtr<ID2D1Layer> tp��;
typedef D2D1_POINT_2F t��2f;
typedef D2D_RECT_F t����f;
typedef D2D1_ELLIPSE t��Բ;
typedef D2D1_COLOR_F t��ɫf;
typedef D2D1_ROUNDED_RECT tԲ�Ǿ���;
typedef DWRITE_TEXT_RANGE t�ı���Χ;
typedef std::vector<D2D1_GRADIENT_STOP> ta�����;
//���ļ�
class C��ͼ��;
class C���ı�;
class C����ת��;
class C�޸��ı���ʽ;
class C�޸��ı�����;
class C�����ֺŸ�ʽ;
class C����ת��;
class C�޸�·������;
class C�ı�����;
class C�ı�Ч��;
typedef std::shared_ptr<C��ͼ��> tp��ͼ��;
typedef std::shared_ptr<C���ı�> tp���ı�;
typedef std::shared_ptr<C����ת��> tp����ת��;
typedef ComPtr<C�ı�Ч��> tp�ı�Ч��;
//ö��
enum class E�ı�ˮƽ���� {
	e��,
	e��,
	e��,
};
enum class E�ı���ֱ���� {
	e��,
	e��,
	e��,
};
//==============================================================================
// �ṹ
//==============================================================================
struct S����� {
	float mλ��;	//mλ�á�[0,1]
	��ѧ::S��ɫ m��ɫ;
};

//==============================================================================
// ��ά����
//==============================================================================
class C��ά {
public:
	static C��ά *g��;
	static const D2D1_COLOR_F c������ɫ;
//����
	C��ά();
	HRESULT f��ʼ��(HWND, float ���� = 0);
	HRESULT f��ʼ��(IDXGISwapChain*, float ���� = 0);	//����
	HRESULT f��ʼ��_����();
	HRESULT f��ʼ��_�豸(IDXGIDevice *);
	void f��ʼ��_���ڴ�С(float, float);
	void f��ʼ��_��ȾĿ��(ID2D1RenderTarget*);
	HRESULT f��ʼ��_����λͼ(IDXGISwapChain *, float ���� = 0);
	//template<std::ranges::Range t��Χ> HRESULT f��ʼ��_���λͼ(const t��Χ &, float ���� = 0);
	template<typename t��Χ> HRESULT f��ʼ��_���λͼ(const t��Χ &, float ���� = 0);
	void fs����(float = 1);
	//���ƿ���
	void f��ʼ();
	void f��ʼ(UINT);	//ʹ��λͼĿ��
	void f����();
	void f����();
	//��ͼ����
	std::shared_ptr<C��ͼ��> fc��ͼ��(const ��ѧ::S��ɫ &��ɫ = ��ѧ::S��ɫ::c��, float ��� = 1);
	std::shared_ptr<C���ı�> fc���ı�(const ��ѧ::S��ɫ &��ɫ = ��ѧ::S��ɫ::c��);
	ComPtr<ID2D1SolidColorBrush> fc��ɫ����(const ��ѧ::S��ɫ &) const;
	ComPtr<ID2D1GradientStopCollection> fc����㼯(const std::vector<S�����> &) const;
	ComPtr<ID2D1LinearGradientBrush> fc���Խ��仭��(const std::vector<S�����> &) const;
	ComPtr<ID2D1RadialGradientBrush> fc���򽥱仭��(const std::vector<S�����> &) const;
	ComPtr<ID2D1PathGeometry> fc·������() const;
	ComPtr<ID2D1Layer> fc��() const;
	C�޸�·������ f�޸�·������(const ComPtr<ID2D1PathGeometry> &) const;
	ComPtr<C�ı�Ч��> fc�ı�Ч��(const ��ѧ::S��ɫ &��� = ��ѧ::S��ɫ::c��, const ��ѧ::S��ɫ &��� = ��ѧ::S��ɫ::c��) const;
	//��������
	ComPtr<ID2D1Factory3> fg��ά����();
	ComPtr<ID2D1RenderTarget> fg��ȾĿ��() const;
	C����ת�� &fg�������() const;
	C�ı����� &fg�ı�����();
	ComPtr<IDWriteTextFormat> fgĬ���ı���ʽ();
private:
	��ѧ::S����2 fgÿӢ�����(float ���� = 0) const;
	��ѧ::S����2 m���ڴ�С;
	ComPtr<ID2D1Factory3> m��ά����;
	ComPtr<ID2D1Device1> m�豸;
	ComPtr<ID2D1DeviceContext> m������;
	std::vector<ComPtr<ID2D1Bitmap1>> maλͼĿ��;
	ComPtr<ID2D1RenderTarget> m��ȾĿ��;	//��ҪĿ��
	std::unique_ptr<C����ת��> m�������;
	std::unique_ptr<C�ı�����> m�ı�����;
	ComPtr<IDWriteTextFormat> mĬ���ı���ʽ;
};
//���ֻ�
class C��ͼ�� {
public:
	void f��ʼ��(ID2D1RenderTarget *, const C����ת�� &);
	void f��ʼ��_����(const ��ѧ::S��ɫ &p��ɫ, float a���);
	//����
	void fs�������(float);
	void fs��ɫ(const ��ѧ::S��ɫ &);
	void fs͸����(float);
	//����
	void f���Ƶ�(const ��ѧ::S����2 &);
	void f��������(const ��ѧ::S�߶�2 &);
	void f���ƾ���(const ��ѧ::S���� &);
	void f������ת����(const ��ѧ::S��ת���� &);
	void f����Բ��(const ��ѧ::SԲ�� &);
	void f������Բ(const ��ѧ::S��Բ &);
	void f����Բ�Ǿ���(const ��ѧ::SԲ�Ǿ��� &);
	//���
	void f������(const ��ѧ::S���� &);
	void f���Բ��(const ��ѧ::SԲ�� &);
	void f�����Բ(const ��ѧ::S��Բ &);
	void f���Բ�Ǿ���(const ��ѧ::SԲ�Ǿ��� &);
public:
	ComPtr<ID2D1RenderTarget> m��ȾĿ��;
	ComPtr<ID2D1SolidColorBrush> m����;
	const C����ת�� *m�������;
	float m�������;
};
class C���ı� {
public:
	void f��ʼ��(ID2D1RenderTarget *, const C����ת�� &);
	void f��ʼ��_����(const ��ѧ::S��ɫ &);
	//����
	void fs��ʽ(IDWriteTextFormat *);
	void fs��ʽ(C�޸��ı���ʽ &);
	void fs��ɫ(const ��ѧ::S��ɫ &);
	void fs͸����(float);
	void fs����(const ��ѧ::S����2 &);
	void fs����(const ��ѧ::S����2 &, const ��ѧ::S����2 &);
	void fs����(float, float);
	void fs����(float, float, float, float);
	void fs����(const ��ѧ::S���� &);
	//��
	void f�����ı�(const std::wstring_view &) const;
	void f�����ı�����(IDWriteTextLayout *) const;
	void f�����ı�����(IDWriteTextLayout *, IDWriteTextRenderer *) const;
	void f�����ı�����(C�޸��ı����� &) const;
public:
	ComPtr<ID2D1RenderTarget> m��ȾĿ��;
	ComPtr<ID2D1SolidColorBrush> m����;
	ComPtr<IDWriteTextFormat> m��ʽ;
	const C����ת�� *m�������;
	D2D1_RECT_F m����;
};
//==============================================================================
// ��ά�ṹ����&ת��
//==============================================================================
class C����ת�� {
public:
	static D2D1_COLOR_F f��ɫ(const ��ѧ::S��ɫ &);
	static D2D1_POINT_2F f��(const ��ѧ::S����2 &);
	static std::vector<D2D1_GRADIENT_STOP> f�����(const std::vector<S�����> &);
};
class C����ת�� {
public:	//����ֱ������Ȼ��ת���ɴ�������
	void fs��С(const ��ѧ::S����2 &);
	float x(float) const;
	float y(float) const;
	float f�ٷֱ�x(float) const;
	float f�ٷֱ�y(float) const;
	D2D1_POINT_2F f��(const ��ѧ::S����2 &) const;
	D2D_RECT_F f����(const ��ѧ::S���� &) const;
	D2D_RECT_F f����_����() const;
	D2D_RECT_F f����_���İ뾶(const ��ѧ::S����2 &, const ��ѧ::S����2 &) const;
	D2D_RECT_F f����_��������(const ��ѧ::S����2 &, const ��ѧ::S����2 &) const;
	D2D_RECT_F f����_��������(float, float, float, float) const;
	D2D_RECT_F f����_��(float, float) const;
	D2D1_ELLIPSE fԲ��(const ��ѧ::S����2 &, float) const;
	D2D1_ELLIPSE fԲ��(const ��ѧ::SԲ�� &) const;
	D2D1_ELLIPSE f��Բ(const ��ѧ::S����2 &, const ��ѧ::S����2 &) const;
	D2D1_ELLIPSE f��Բ(const ��ѧ::S��Բ &) const;
	D2D1_ROUNDED_RECT fԲ�Ǿ���(const ��ѧ::SԲ�Ǿ��� &) const;
	D2D1_ROUNDED_RECT fԲ�Ǿ���(const ��ѧ::S����2 &, const ��ѧ::S����2 &, const ��ѧ::S����2 &) const;
private:
	��ѧ::S����2 m���ڴ�С;
};
//==============================================================================
// ·��
//==============================================================================
class C�޸�·������ {
public:
	C�޸�·������(ID2D1PathGeometry *, const C����ת�� &);
	~C�޸�·������();
	void f��(const ��ѧ::S����2 &p);
	void fֱ��(const ��ѧ::S����2 &p0, const ��ѧ::S����2 &p1);
	void fԲ��(const ��ѧ::S����2 &pԲ��, float p�뾶, float p��ʼ, float p����, bool ˳ʱ�� = true);
	void f����ֱ��(const std::vector<��ѧ::S����2> &);
	void fƽ������(const std::vector<��ѧ::S����2> &);
	void f�պ�();
	void f�Ͽ�();
	void f����();
private:
	ComPtr<ID2D1GeometrySink> m���β�;
	const C����ת�� *m�������;
	��ѧ::S����2 m��ǰ��;
	bool mw��ʼ = false;
};
//==============================================================================
// �ı�����
//==============================================================================
struct S�ı���ʽ���� {
	std::wstring m���� = L"΢���ź�";
	std::wstring m�������� = L"zh-cn";
	float m�ֺ� = 36;
	DWRITE_FONT_WEIGHT m���� = DWRITE_FONT_WEIGHT_REGULAR;
	DWRITE_FONT_STYLE mб�� = DWRITE_FONT_STYLE_NORMAL;
	DWRITE_FONT_STRETCH m���� = DWRITE_FONT_STRETCH_NORMAL;
	DWRITE_TEXT_ALIGNMENT mˮƽ���� = DWRITE_TEXT_ALIGNMENT_LEADING;//Ĭ�������
	DWRITE_PARAGRAPH_ALIGNMENT m��ֱ���� = DWRITE_PARAGRAPH_ALIGNMENT_CENTER;
	DWRITE_WORD_WRAPPING m�Զ����� = DWRITE_WORD_WRAPPING_NO_WRAP;
	void fs����(const std::wstring_view &);
	void fs��������(const std::wstring_view &);
	void fs�ֺ�(float);
	void fs����(int);
	void fsб��(int);
	void fs����(int);
	void fs�Զ�����(bool);
	void fsˮƽ����(E�ı�ˮƽ����);
	void fs��ֱ����(E�ı���ֱ����);
};
class C�ı����� {
public:
//���캯��
	C�ı�����();
	~C�ı�����();
//����
	HRESULT f��ʼ��();
	void f����();
	tp�ı���ʽ fc�ı���ʽ(const S�ı���ʽ���� &) const;
	tp�ı����� fc�ı�����(const std::wstring_view &�ı�, IDWriteTextFormat *��ʽ = nullptr) const;
	tp�ı����� fc�ı�����(const std::wstring_view &�ı�, const S�ı���ʽ���� &��ʽ) const;
	tp�ı����� fc�ı�����_С��(double, int С��λ��, IDWriteTextFormat *��ʽ);
	C�޸��ı����� f�޸��ı�����(const tp�ı����� &);
public:
	ComPtr<IDWriteFactory> mд�ֹ���;
};
class C�ı���ʽת�� {
public:
	static DWRITE_FONT_WEIGHT f����(int);	//0~9
	static DWRITE_FONT_STYLE fб��(int);	//0~2
	static DWRITE_FONT_STRETCH f����(int);	//0~9
	static DWRITE_TEXT_ALIGNMENT fˮƽ����(E�ı�ˮƽ����);
	static DWRITE_TEXT_ALIGNMENT fˮƽ����(int);
	static DWRITE_PARAGRAPH_ALIGNMENT f��ֱ����(E�ı���ֱ����);
	static DWRITE_PARAGRAPH_ALIGNMENT f��ֱ����(int);
	static DWRITE_TRIMMING f����(int);	//0~2
	static DWRITE_WORD_WRAPPING f�Զ�����(bool);
};
//==============================================================================
// �����ֺ�
//==============================================================================
enum E�����ֺ� {
	e���غ�,e�غ�,
	e����,	eС����,
	e��һ��,eһ��,	eСһ��,
	e����,	eС����,
	e����,	eС����,
	e�ĺ�,	eС�ĺ�,
	e���,	eС���,
	e����,	eС����,
	e�ߺ�,	eС�ߺ�,
	e�˺�,
};
constexpr float ca�����ֺ�[] = {
	63, 54,	//�غ�
	42, 36,	//����
	31.5, 26, 24,	//һ��
	22, 18,	//����
	16, 15,	//����
	14, 12,	//�ĺ�
	10.5, 9,	//���
	7.5, 6.5,	//����
	5.5, 5.25,	//�ߺ�
	5	//�˺�
};
//==============================================================================
// �ı���ʽ&�ı�����
//==============================================================================
class C�޸��ı���ʽ {
public:
	IDWriteTextFormat *m��ʽ;
	C�޸��ı���ʽ(IDWriteTextFormat *);
	~C�޸��ı���ʽ();
	C�޸��ı���ʽ &fsˮƽ����(E�ı�ˮƽ���� = E�ı�ˮƽ����::e��);
	C�޸��ı���ʽ &fs��ֱ����(E�ı���ֱ���� = E�ı���ֱ����::e��);
	C�޸��ı���ʽ &fs����(E�ı�ˮƽ���� = E�ı�ˮƽ����::e��, E�ı���ֱ���� = E�ı���ֱ����::e��);
	C�޸��ı���ʽ &fs����(int = 0);
};
class C�޸��ı����� {
public:
	IDWriteTextLayout *m����;
	C�޸��ı�����(IDWriteTextLayout *);
	~C�޸��ı�����();
	C�޸��ı����� &fs����(DWRITE_FONT_WEIGHT, DWRITE_TEXT_RANGE = {0, 0});
	C�޸��ı����� &fsб��(DWRITE_FONT_STYLE, DWRITE_TEXT_RANGE = {0, 0});
	C�޸��ı����� &fs����(DWRITE_FONT_STRETCH, DWRITE_TEXT_RANGE = {0, 0});
};
class F�ı���Χ���� {
public:
	UINT32 m�ı�����;
	F�ı���Χ����(UINT32);
	DWRITE_TEXT_RANGE operator()(int = 0, int = 0) const;
};
//==============================================================================
// ���ı�
//==============================================================================
class C�ı�Ч�� : public IDWriteTextRenderer {
	friend C��ά;
	C�ı�Ч��() = default;
public:
	//��д�ķ���
	unsigned long __stdcall AddRef() override;
	unsigned long __stdcall Release() override;
	HRESULT __stdcall QueryInterface(IID const&,void**) override;
	HRESULT __stdcall IsPixelSnappingDisabled(void*, BOOL*) override;
	HRESULT __stdcall GetCurrentTransform(void*, DWRITE_MATRIX*) override;
	HRESULT __stdcall GetPixelsPerDip(void*, FLOAT*) override;
	HRESULT __stdcall DrawGlyphRun(void*, FLOAT, FLOAT, DWRITE_MEASURING_MODE, DWRITE_GLYPH_RUN const*, DWRITE_GLYPH_RUN_DESCRIPTION const*, IUnknown*) override;
	HRESULT __stdcall DrawUnderline(void*, FLOAT, FLOAT, DWRITE_UNDERLINE const*, IUnknown*) override;
	HRESULT __stdcall DrawStrikethrough(void*, FLOAT, FLOAT, DWRITE_STRIKETHROUGH const*,  IUnknown*) override;
	HRESULT __stdcall DrawInlineObject(void*, FLOAT, FLOAT, IDWriteInlineObject*, BOOL, BOOL, IUnknown*) override;
	//���ı�
	void fs�����ɫ(const ��ѧ::S��ɫ &);
	void fs������ɫ(const ��ѧ::S��ɫ &);
	void fs�������(float);
	void fs͸����(float);
private:
	HRESULT f���Ƽ���(ID2D1Geometry *, float x, float y);
	ComPtr<ID2D1Factory> m��ά����;
	ComPtr<ID2D1RenderTarget> m��ȾĿ��;
	ComPtr<ID2D1SolidColorBrush> m��仭��;
	ComPtr<ID2D1SolidColorBrush> m��������;
	float m������� = 2;
	unsigned long m���ü��� = 1;
};
}	//namespace cflw::ͼ��::d2d
#include "cflwͼ��_d2d.inl"