#include <assert.h>
#include <vector>
#include <d2d1.h>
#include <wrl.h>
using Microsoft::WRL::ComPtr;
/// <summary>  
/// Refer to : http://www.codeproject.com/KB/graphics/BezierSpline.aspx  
/// Solves a tridiagonal system for one of coordinates (x or y) of first Bezier control points.  
/// </summary>  
/// <param name="rhs">Right hand side vector.</param>  
/// <param name="x">Solution vector.</param>  
void GetFirstControlPoints(
	__in const std::vector<FLOAT>& rhs,
	__out std::vector<FLOAT>& x) {
	assert(rhs.size() == x.size());
	int n = rhs.size();
	std::vector<FLOAT> tmp(n);    // Temp workspace.  

	FLOAT b = 2.0f;
	x[0] = rhs[0] / b;
	for (int i = 1; i < n; i++) // Decomposition and forward substitution.  
	{
		tmp[i] = 1 / b;
		b = (i < n - 1 ? 4.0f : 3.5f) - tmp[i];
		x[i] = (rhs[i] - x[i - 1]) / b;
	}
	for (int i = 1; i < n; i++) {
		x[n - i - 1] -= tmp[n - i] * x[n - i]; // Back substitution.  
	}
}

/// <summary>  
/// Refer to : http://www.codeproject.com/KB/graphics/BezierSpline.aspx  
/// Get open-ended Bezier Spline Control Points.  
/// </summary>  
/// <param name="knots">Input Knot Bezier spline points.</param>  
/// <param name="firstCtrlPt">Output First Control points array of knots.size()-1 length.</param>  
/// <param name="secondCtrlPt">Output Second Control points array of knots.size()-1 length.</param>  
void GetCurveControlPoints(
	__in const std::vector<D2D1_POINT_2F>& knots,
	__out std::vector<D2D1_POINT_2F>& firstCtrlPt,
	__out std::vector<D2D1_POINT_2F>& secondCtrlPt) {
	assert((firstCtrlPt.size() == secondCtrlPt.size())
		&& (knots.size() == firstCtrlPt.size() + 1));

	int n = knots.size() - 1;
	assert(n >= 1);

	if (n == 1) {
		// Special case: Bezier curve should be a straight line.  
		// 3P1 = 2P0 + P3  
		firstCtrlPt[0].x = (2 * knots[0].x + knots[1].x) / 3.0f;
		firstCtrlPt[0].y = (2 * knots[0].y + knots[1].y) / 3.0f;

		// P2 = 2P1 ¨C P0  
		secondCtrlPt[0].x = 2 * firstCtrlPt[0].x - knots[0].x;
		secondCtrlPt[0].y = 2 * firstCtrlPt[0].y - knots[0].y;
		return;
	}

	// Calculate first Bezier control points  
	// Right hand side vector  
	std::vector<FLOAT> rhs(n);

	// Set right hand side X values  
	for (int i = 1; i < (n - 1); ++i) {
		rhs[i] = 4 * knots[i].x + 2 * knots[i + 1].x;
	}
	rhs[0] = knots[0].x + 2 * knots[1].x;
	rhs[n - 1] = (8 * knots[n - 1].x + knots[n].x) / 2.0f;
	// Get first control points X-values  
	std::vector<FLOAT> x(n);
	GetFirstControlPoints(rhs, x);

	// Set right hand side Y values  
	for (int i = 1; i < (n - 1); ++i) {
		rhs[i] = 4 * knots[i].y + 2 * knots[i + 1].y;
	}
	rhs[0] = knots[0].y + 2 * knots[1].y;
	rhs[n - 1] = (8 * knots[n - 1].y + knots[n].y) / 2.0f;
	// Get first control points Y-values  
	std::vector<FLOAT> y(n);
	GetFirstControlPoints(rhs, y);

	// Fill output arrays.  
	for (int i = 0; i < n; ++i) {
		// First control point  
		firstCtrlPt[i] = D2D1::Point2F(x[i], y[i]);
		// Second control point  
		if (i < (n - 1)) {
			secondCtrlPt[i] = D2D1::Point2F(2 * knots[i + 1].x - x[i + 1], 2 * knots[i + 1].y - y[i + 1]);
		} else {
			secondCtrlPt[i] = D2D1::Point2F((knots[n].x + x[n - 1]) / 2, (knots[n].y + y[n - 1]) / 2);
		}
	}
}

HRESULT CreateBezierSpline(
	__in ID2D1Factory* pD2dFactory,
	__in const std::vector<D2D1_POINT_2F>& points,
	__out ID2D1PathGeometry** ppPathGeometry) {
	assert(pD2dFactory);
	assert(ppPathGeometry != nullptr);
	assert(points.size()>1);

	int n = points.size();
	std::vector<D2D1_POINT_2F> firstCtrlPt(n - 1);
	std::vector<D2D1_POINT_2F> secondCtrlPt(n - 1);
	GetCurveControlPoints(points, firstCtrlPt, secondCtrlPt);

	HRESULT hr = pD2dFactory->CreatePathGeometry(ppPathGeometry);
	assert(SUCCEEDED(hr));
	if (FAILED(hr))
		return hr;

	ComPtr<ID2D1GeometrySink> spSink;
	hr = (*ppPathGeometry)->Open(&spSink);
	assert(SUCCEEDED(hr));
	if (SUCCEEDED(hr)) {
		spSink->SetFillMode(D2D1_FILL_MODE_WINDING);
		spSink->BeginFigure(points[0], D2D1_FIGURE_BEGIN_FILLED);
		for (int i = 1; i<n; i++)
			spSink->AddBezier(D2D1::BezierSegment(firstCtrlPt[i - 1], secondCtrlPt[i - 1], points[i]));
		spSink->EndFigure(D2D1_FIGURE_END_OPEN);
		spSink->Close();
	}
	return hr;
}