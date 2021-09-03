
// PopovAppDoc.cpp : implementation of the CPopovAppDoc class
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "PopovApp.h"
#endif

#include "PopovAppDoc.h"

#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CPopovAppDoc

IMPLEMENT_DYNCREATE(CPopovAppDoc, CDocument)

BEGIN_MESSAGE_MAP(CPopovAppDoc, CDocument)
	ON_COMMAND(ID_HISTOGRAM, &CPopovAppDoc::OnHistogram)
	ON_COMMAND(ID_REFRESHHIST, &CPopovAppDoc::OnRefreshhist)
	ON_COMMAND(ID_P, &CPopovAppDoc::OnP)
	ON_COMMAND(ID_TIMEDEPENDANCE, &CPopovAppDoc::OnTimedependance)
	ON_COMMAND(ID_REFRESHP, &CPopovAppDoc::OnRefreshp)
END_MESSAGE_MAP()


// CPopovAppDoc construction/destruction

CPopovAppDoc::CPopovAppDoc() noexcept
{
	// TODO: add one-time construction code here

}

CPopovAppDoc::~CPopovAppDoc()
{
	delete s;
	delete chi;
	delete d0;
	delete d1;
	delete[] pDist;
	delete[] sTime1; 
	delete[] sTime2; 
}

BOOL CPopovAppDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}




// CPopovAppDoc serialization

void CPopovAppDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

#ifdef SHARED_HANDLERS

// Support for thumbnails
void CPopovAppDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// Modify this code to draw the document's data
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT)GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// Support for Search Handlers
void CPopovAppDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// Set search contents from document's data.
	// The content parts should be separated by ";"

	// For example:  strSearchContent = _T("point;rectangle;circle;ole object;");
	SetSearchContent(strSearchContent);
}

void CPopovAppDoc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl* pChunk = nullptr;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != nullptr)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// CPopovAppDoc diagnostics

#ifdef _DEBUG
void CPopovAppDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CPopovAppDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG



void CPopovAppDoc::OnHistogram()
{
	CSampSetDlg dial;
	dial.m_sampSize = sampSize;
	dial.m_lambda = d0->GetLambda();
	dial.m_method = method;
	if (dial.DoModal() != IDOK) return;
	type = 0;
	delete s;
	delete chi;
	delete d0;
	if (dial.m_method) s = new Sample_2(dial.m_sampSize);
	else s = new Sample_1(dial.m_sampSize);
	s->Simulate(dial.m_lambda);
	d0 = new Distribution(dial.m_lambda);
	chi = new ChiSq(d0, s);
	sampSize = dial.m_sampSize;
	d0->SetLambda(dial.m_lambda);
	method = dial.m_method;
	UpdateAllViews(0);
}


void CPopovAppDoc::OnRefreshhist()
{
	if (type) return;
	if (s)
	{
		s->Simulate(d0->GetLambda());
		chi->Update(s);
	}
	else AfxMessageBox(L"Сначала установите параметры!");
	UpdateAllViews(0);
}


void CPopovAppDoc::OnP()
{
	SetPVS dial;
	dial.m_sampSize = sampSize;
	dial.m_pvsampSize = pvsampSize;
	dial.m_lambda0 = d0->GetLambda();
	dial.m_lambda1 = d1->GetLambda();
	dial.m_method = method;
	if (dial.DoModal() != IDOK) return;
	type = 1;
	delete s;
	delete chi;
	delete pDist;
	if (dial.m_method) s = new Sample_2(dial.m_sampSize);
	else s = new Sample_1(dial.m_sampSize);
	s->Simulate(dial.m_lambda0);
	d1 = new Distribution(dial.m_lambda1);
	chi = new ChiSq(d1, s);
	pDist = new double[21]{ 0 };
	for (int i = 0; i < dial.m_pvsampSize; ++i) {
		s->Simulate(dial.m_lambda0);
		chi->Update(s);
		chi->calculatePvalue();
		++pDist[int(chi->GetPvalue() * 20)];
	}
	for (int i = 0; i < 21; ++i)
		pDist[i] /= dial.m_pvsampSize;
	for (int i = 1; i < 21; ++i)
		pDist[i] += pDist[i - 1];

	d0->SetLambda(dial.m_lambda0);
	d1->SetLambda(dial.m_lambda1);
	method = dial.m_method;
	pvsampSize = dial.m_pvsampSize;
	sampSize = dial.m_sampSize;
	UpdateAllViews(0);
}


void CPopovAppDoc::OnTimedependance()
{
	CSTimeDep dial;
	dial.m_sampSize = numGens;
	dial.m_step = step;
	if (dial.DoModal() != IDOK) return;
	delete sTime1;
	delete sTime2;
	delete s;
	type = 2;
	sTime1 = new double[steps];
	sTime2 = new double[steps];
	s = new Sample_1(dial.m_sampSize);
	for (size_t i = 0; i < steps; i++)
	{
		unsigned int start_time = clock();
		s->Simulate(step * (i + 1));
		unsigned int end_time = clock();
		sTime1[i] = end_time - start_time;
	}
	delete s;
	s = new Sample_2(dial.m_sampSize);
	for (size_t i = 0; i < steps; i++)
	{
		unsigned int start_time = clock();
		s->Simulate(step * (i + 1));
		unsigned int end_time = clock();
		sTime2[i] = end_time - start_time;
	}
	numGens = dial.m_sampSize;
	step = dial.m_step;
	UpdateAllViews(0);
}


void CPopovAppDoc::OnRefreshp()
{
	if (type != 1) return;
	if (pDist)
	{
		memset(pDist, 0, sizeof(double) * 21);

		for (int i = 0; i < pvsampSize; ++i) {
			s->Simulate(d0->GetLambda());
			chi->Update(s);
			chi->calculatePvalue();
			++pDist[int(chi->GetPvalue() * 20)];
		}
		for (int i = 0; i < 21; ++i)
			pDist[i] /= pvsampSize;
		for (int i = 1; i < 21; ++i)
			pDist[i] += pDist[i - 1];
	}
	else AfxMessageBox(L"Сначала установите параметры!");
	UpdateAllViews(0);
}
