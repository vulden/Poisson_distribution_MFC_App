
// PopovAppDoc.h : interface of the CPopovAppDoc class
//
#include "CSampSetDlg.h"
#include "CSTimeDep.h"
#include "SetPVS.h"
#include "Classes.h"
#include <ctime>

#pragma once


class CPopovAppDoc : public CDocument
{
protected: // create from serialization only
	CPopovAppDoc() noexcept;
	DECLARE_DYNCREATE(CPopovAppDoc)

	// Attributes
public:

	// Operations
public:

	// Overrides
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

	// Implementation
public:
	const int steps = 20;
	int type = -1;
	double step = 1;
	int sampSize = 100;
	int numGens = 10000;
	int pvsampSize = 100;
	int method = 0;
	Sample* s = nullptr;
	Distribution* d0 = new Distribution(1);
	Distribution* d1 = new Distribution(1);
	ChiSq* chi = nullptr;
	double* pDist = nullptr;
	double* sTime1 = nullptr;
	double* sTime2 = nullptr;
	virtual ~CPopovAppDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

	// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// Helper function that sets search content for a Search Handler
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
public:
	afx_msg void OnHistogram();
	afx_msg void OnRefreshhist();
	afx_msg void OnP();
	afx_msg void OnTimedependance();
	afx_msg void OnRefreshp();
};
