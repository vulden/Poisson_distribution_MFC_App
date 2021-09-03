// CSTimeDep.cpp : implementation file
//

#include "pch.h"
#include "PopovApp.h"
#include "CSTimeDep.h"
#include "afxdialogex.h"


// CSTimeDep dialog

IMPLEMENT_DYNAMIC(CSTimeDep, CDialog)

CSTimeDep::CSTimeDep(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_DIALOG3, pParent)
	, m_sampSize(0)
	, m_step(0)
{

}

CSTimeDep::~CSTimeDep()
{
}

void CSTimeDep::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT3, m_sampSize);
	DDX_Text(pDX, IDC_EDIT4, m_step);
}


BEGIN_MESSAGE_MAP(CSTimeDep, CDialog)
	ON_EN_KILLFOCUS(IDC_EDIT4, &CSTimeDep::OnEnKillfocusEdit4)
	ON_EN_KILLFOCUS(IDC_EDIT3, &CSTimeDep::OnEnKillfocusEdit3)
END_MESSAGE_MAP()


// CSTimeDep message handlers


void CSTimeDep::OnEnKillfocusEdit4()
{
	UpdateData(1);
	if (m_step > 500 || m_step <= 0) {
		m_step = 1;
		AfxMessageBox(L"Enter a number from 0 to 500");
		UpdateData(0);
	}
}


void CSTimeDep::OnEnKillfocusEdit3()
{
	UpdateData(1);
	if (m_sampSize > 1e8 || m_sampSize < 1000) {
		m_sampSize = 1000;
		AfxMessageBox(L"Enter a number from 1000 to 1e8");
		UpdateData(0);
	}
}
