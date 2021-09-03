
// PopovAppView.h : interface of the CPopovAppView class
//

#pragma once


class CPopovAppView : public CView
{
protected: // create from serialization only
	CPopovAppView() noexcept;
	DECLARE_DYNCREATE(CPopovAppView)

// Attributes
public:
	CPopovAppDoc* GetDocument() const;

// Operations
public:

// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	void DrawHist(CDC* pDC);
	void DrawPVDist(CDC* pDC);
	void DrawTDep(CDC* pDC);	
protected:

// Implementation
public:
	virtual ~CPopovAppView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
};

#ifndef _DEBUG  // debug version in PopovAppView.cpp
inline CPopovAppDoc* CPopovAppView::GetDocument() const
   { return reinterpret_cast<CPopovAppDoc*>(m_pDocument); }
#endif

