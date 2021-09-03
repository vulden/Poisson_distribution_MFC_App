// CSampSetDlg.cpp : implementation file
//

#include "pch.h"
#include "PopovApp.h"
#include "CSampSetDlg.h"
#include "afxdialogex.h"


// CSampSetDlg dialog

IMPLEMENT_DYNAMIC(CSampSetDlg, CDialog)

CSampSetDlg::CSampSetDlg(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_DIALOG1, pParent)
	, m_lambda()
	, m_sampSize()
	, m_method(0)
{

}

CSampSetDlg::~CSampSetDlg()
{
}

void CSampSetDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_lambda);
	DDX_Text(pDX, IDC_EDIT3, m_sampSize);
	DDX_Radio(pDX, IDC_RADIO1, m_method);
}


BEGIN_MESSAGE_MAP(CSampSetDlg, CDialog)
	ON_EN_KILLFOCUS(IDC_EDIT1, &CSampSetDlg::OnEnKillfocusEdit1)
	ON_EN_KILLFOCUS(IDC_EDIT3, &CSampSetDlg::OnEnKillfocusEdit3)
	ON_BN_CLICKED(IDC_RADIO2, &CSampSetDlg::OnBnClickedRadio2)
END_MESSAGE_MAP()


// CSampSetDlg message handlers


void CSampSetDlg::OnEnKillfocusEdit1()
{
	UpdateData(1);
	if (m_lambda > 1000 || m_lambda <= 0 ) {
		m_lambda = 1;
		AfxMessageBox(L"Enter a number from 0 to 1000");
		UpdateData(0);
	}
}

void CSampSetDlg::OnEnKillfocusEdit3()
{
	UpdateData(1);
	if (m_sampSize > 1e7 || m_sampSize < 1) {
		m_sampSize = 1000;
		AfxMessageBox(L"Enter a number from 1 to 1e7");
		UpdateData(0);
	}
	// TODO: Add your control notification handler code here
}


void CSampSetDlg::OnBnClickedRadio2()
{
	// TODO: Add your control notification handler code here
}
