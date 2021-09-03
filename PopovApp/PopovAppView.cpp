
// PopovAppView.cpp : implementation of the CPopovAppView class
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "PopovApp.h"
#endif

#include "PopovAppDoc.h"
#include "PopovAppView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CPopovAppView

IMPLEMENT_DYNCREATE(CPopovAppView, CView)

BEGIN_MESSAGE_MAP(CPopovAppView, CView)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
END_MESSAGE_MAP()

// CPopovAppView construction/destruction

CPopovAppView::CPopovAppView() noexcept
{
	// TODO: add construction code here

}

CPopovAppView::~CPopovAppView()
{
}

BOOL CPopovAppView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CPopovAppView drawing

void CPopovAppView::OnDraw(CDC* pDC)
{
	CPopovAppDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	switch (pDoc->type)
	{
	case 0: {DrawHist(pDC); break; }
	case 1: {DrawPVDist(pDC); break; }
	case 2: {DrawTDep(pDC); break; }
	default:
		break;
	}

}


void CPopovAppView::DrawHist(CDC* pDC) {
	CPopovAppDoc* pDoc = GetDocument();
	CRect rc;
	GetClientRect(&rc);
	CStringW str;
	int ind = 60;
	int n = pDoc->chi->GetFreqsize();
	double dx = (rc.Width() - 2 * ind) / n;
	double x = ind;
	double y = rc.Height() - ind;
	double max = pDoc->chi->GetExpFreqAt((int)pDoc->d0->GetLambda());
	for (size_t i = 0; i < n; ++i)
		if (pDoc->chi->GetObsFreqAt(i)> max) max = pDoc->chi->GetObsFreqAt(i);

	double dy = (rc.Height() - 2 * ind) / max;

	CBrush brush;
	CBrush* pOldBrush;
	brush.CreateSolidBrush(RGB(102, 255, 102));
	pOldBrush = pDC->SelectObject(&brush);

	for (size_t i = 0; i < n; ++i)
	{
		double temp = pDoc->chi->GetObsFreqAt(i);
		pDC->Rectangle(x, rc.Height() - ind, x + dx, y - temp * dy);
		x += dx;
	}
	pDC->SelectObject(pOldBrush);
	brush.DeleteObject();
	brush.CreateSolidBrush(RGB(255, 80, 80));
	pOldBrush = pDC->SelectObject(&brush);
	x = ind;
	for (size_t i = 0; i < n; ++i)
	{
		double temp = pDoc->chi->GetExpFreqAt(i);
		pDC->Rectangle(x + dx * 0.3, rc.Height() - ind, x + 0.7 * dx, y - temp * dy);
		x += dx;
	}

	pDC->MoveTo(ind, rc.Height() - ind);//X
	pDC->LineTo(rc.Width() - ind + 20, rc.Height() - ind);
	pDC->TextOutW(rc.Width() - ind + 20, rc.Height() - ind - 20, L"Value");

	pDC->MoveTo(30, rc.Height() - 30);

	pDC->MoveTo(ind, rc.Height() - ind); //Y
	pDC->LineTo(ind, ind - 20);
	pDC->TextOutW(20, 20, L"Frequency");
	//ZERO
	str.Format(_T("%d"), 0);
	pDC->TextOutW(ind - 10, rc.Height() - ind, str);

	str.Format(_T("%.1f"), max);
	pDC->TextOutW(ind - 40, ind, str);

	str.Format(_T("%d"), 1);
	pDC->TextOutW(ind + dx / 2, rc.Height() - ind + 5, str);

	str.Format(_T("%.1f"), pDoc->chi->GetExpFreqAt(0));
	pDC->TextOutW(ind - 45, y - pDoc->chi->GetExpFreqAt(0) * dy - 10, str);

	str.Format(_T("%d"), n - 1);
	pDC->TextOutW(x - dx / 2, rc.Height() - ind + 5, str);

	pDC->SelectObject(pOldBrush);
	brush.DeleteObject();
}

void CPopovAppView::DrawPVDist(CDC* pDC) {
	CPopovAppDoc* pDoc = GetDocument();
	CRect rc;
	GetClientRect(&rc);
	CStringW str;
	int ind = 60;
	int n = 20;
	double dx = (rc.Width() - 2 * ind) / double(n);
	double x = ind;
	double y = rc.Height() - ind;
	double dy = rc.Height() - 2 * ind;

	CPen pen;
	CPen* pOldPen;
	pen.CreatePen(BS_SOLID, 3, RGB(255, 0, 0));
	pOldPen = pDC->SelectObject(&pen);

	pDC->MoveTo(ind, rc.Height() - ind);
	pDC->LineTo(rc.Width() - ind, ind);

	pDC->SelectObject(pOldPen);
	pen.DeleteObject();
	pen.CreatePen(BS_SOLID, 3, RGB(0, 100, 200));
	pOldPen = pDC->SelectObject(&pen);

	pDC->MoveTo(ind, rc.Height() - ind);

	for (size_t i = 0; i < n; ++i)
	{
		double temp = pDoc->pDist[i];
		pDC->LineTo(x + dx, y - temp * dy);
		x += dx;
	}

	pDC->SelectObject(pOldPen);
	pen.DeleteObject();
	//ZERO
	str.Format(_T("%d"), 0);
	pDC->TextOutW(ind - 10, rc.Height() - ind, str);
	//X
	pDC->MoveTo(ind, rc.Height() - ind);
	pDC->LineTo(rc.Width() - ind + 20, rc.Height() - ind);
	pDC->TextOutW(rc.Width() - ind + 20, rc.Height() - ind - 20, L"Value");
	for (size_t i = 2; i < n + 1; i += 2)
	{
		str.Format(_T("%.2f"), i * 0.05);
		pDC->TextOutW(ind + dx * i - 12, y + 10, str);
		pDC->MoveTo(ind + dx * i, y - 5);
		pDC->LineTo(ind + dx * i, y + 5);
	}

	//Y
	pDC->MoveTo(ind, rc.Height() - ind);
	pDC->LineTo(ind, ind - 20);
	pDC->TextOutW(20, 20, L"Frequency");
	for (size_t i = 1; i < n + 1; ++i)
	{
		str.Format(_T("%.2f"), i * 0.05);
		pDC->TextOutW(30, y - i * 0.05 * dy - 7, str);
		pDC->MoveTo(ind - 5, y - i * 0.05 * dy);
		pDC->LineTo(ind + 5, y - i * 0.05 * dy);
	}

}

void CPopovAppView::DrawTDep(CDC* pDC) {

	CPopovAppDoc* pDoc = GetDocument();
	CRect rc;
	GetClientRect(&rc);
	CStringW str;

	int ind = 60;
	int n = pDoc->steps;
	double dx = (rc.Width() - 2 * ind) / double(n);
	double x = ind + dx;
	double y = rc.Height() - ind;
	double max;
	max = pDoc->sTime2[n - 1];	//approx max
	double dy = (rc.Height() - 2 * ind) / (1.5 * max);

	CPen pen;
	CPen* pOldPen;
	pen.CreatePen(BS_SOLID, 3, RGB(255, 0, 0));
	pOldPen = pDC->SelectObject(&pen);

	pDC->MoveTo(x, y - pDoc->sTime1[0] * dy);
	for (size_t i = 1; i < n; i++)
	{
		pDC->LineTo(x + dx, y - pDoc->sTime1[i] * dy);
		x += dx;
	}

	pDC->SelectObject(pOldPen);
	pen.DeleteObject();
	pen.CreatePen(BS_SOLID, 3, RGB(0, 100, 200));
	pOldPen = pDC->SelectObject(&pen);

	x = ind + dx;
	pDC->MoveTo(x, y - pDoc->sTime2[0] * dy);
	for (size_t i = 1; i < n; i++)
	{
		pDC->LineTo(x + dx, y - pDoc->sTime2[i] * dy);
		x += dx;
	}

	pDC->SelectObject(pOldPen);
	pen.DeleteObject();
	//ZERO
	str.Format(_T("%d"), 0);
	pDC->TextOutW(ind - 10, rc.Height() - ind, str);
	//X
	pDC->MoveTo(ind, rc.Height() - ind);
	pDC->LineTo(rc.Width() - ind + 20, rc.Height() - ind);
	pDC->TextOutW(rc.Width() - ind + 20, rc.Height() - ind - 20, L"Lambda");
	for (size_t i = 1; i < n + 1; i++)
	{
		str.Format(_T("%.1f"), i * pDoc->step);
		pDC->TextOutW(ind + dx * i - 12, y + 10, str);
		pDC->MoveTo(ind + dx * i, y - 5);
		pDC->LineTo(ind + dx * i, y + 5);
	}

	//Y
	pDC->MoveTo(ind, rc.Height() - ind);
	pDC->LineTo(ind, ind - 20);
	pDC->TextOutW(20, 20, L"Time, 1e-3 seconds");
	double temp = max;
	double kr = 1;
	while (temp > 10) { temp /= 10; kr *= 10; }
	for (size_t i = 1; i < temp * 1.5; ++i)
	{
		str.Format(_T("%.1f"), i * kr);
		pDC->TextOutW(20, -10 + y - i * kr * (rc.Height() - 2 * ind) / (1.5 * max), str);
		pDC->MoveTo(ind - 5, y - i * kr * (rc.Height() - 2 * ind) / (1.5 * max));
		pDC->LineTo(ind + 5, y - i * kr * (rc.Height() - 2 * ind) / (1.5 * max));
	}

	CBrush brush;
	CBrush* pOldBrush;
	brush.CreateSolidBrush(RGB(0, 100, 200));
	pOldBrush = pDC->SelectObject(&brush);

	pDC->Rectangle(rc.Width() / 4, 40, rc.Width() / 4 + 20, 60);
	pDC->TextOutW(rc.Width() / 4 + 25, 40, L"Poisson Exponential");

	pDC->SelectObject(pOldBrush);
	brush.DeleteObject();
	brush.CreateSolidBrush(RGB(255, 0, 0));
	pOldBrush = pDC->SelectObject(&brush);

	pDC->Rectangle(rc.Width() / 4, 70, rc.Width() / 4 + 20, 90);
	pDC->TextOutW(rc.Width() / 4 + 25, 70, L"Poisson Inverse Sequential");

	pDC->SelectObject(pOldBrush);
	brush.DeleteObject();
}

void CPopovAppView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CPopovAppView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}

// CPopovAppView diagnostics

#ifdef _DEBUG
void CPopovAppView::AssertValid() const
{
	CView::AssertValid();
}

void CPopovAppView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CPopovAppDoc* CPopovAppView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CPopovAppDoc)));
	return (CPopovAppDoc*)m_pDocument;
}
#endif //_DEBUG

