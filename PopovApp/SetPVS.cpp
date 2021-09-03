// SetPVS.cpp : implementation file
//

#include "pch.h"
#include "PopovApp.h"
#include "SetPVS.h"
#include "afxdialogex.h"


// SetPVS dialog

IMPLEMENT_DYNAMIC(SetPVS, CDialog)

SetPVS::SetPVS(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_DIALOG2, pParent)
	, m_method(FALSE)
	, m_lambda0(0)
	, m_lambda1(0)
	, m_sampSize(0)
	, m_pvsampSize(0)
{

}

SetPVS::~SetPVS()
{
}

void SetPVS::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Radio(pDX, IDC_RADIO1, m_method);
	DDX_Text(pDX, IDC_EDIT2, m_lambda0);
	DDX_Text(pDX, IDC_EDIT3, m_lambda1);
	DDX_Text(pDX, IDC_EDIT1, m_sampSize);
	DDX_Text(pDX, IDC_EDIT4, m_pvsampSize);
}


BEGIN_MESSAGE_MAP(SetPVS, CDialog)
	ON_EN_KILLFOCUS(IDC_EDIT2, &SetPVS::OnEnKillfocusEdit2)
	ON_EN_KILLFOCUS(IDC_EDIT3, &SetPVS::OnEnKillfocusEdit3)
	ON_EN_KILLFOCUS(IDC_EDIT1, &SetPVS::OnEnKillfocusEdit1)
	ON_EN_KILLFOCUS(IDC_EDIT4, &SetPVS::OnEnKillfocusEdit4)
END_MESSAGE_MAP()


// SetPVS message handlers


void SetPVS::OnEnKillfocusEdit2()
{
	UpdateData(1);
	if (m_lambda0 > 1000 || m_lambda0 < 0) {
		m_lambda0 = 1;
		AfxMessageBox(L"Enter a number from 1 to 1000");
		UpdateData(0);
	}
}


void SetPVS::OnEnKillfocusEdit3()
{
	UpdateData(1);
	if (m_lambda1 > 1000 || m_lambda1 < 0) {
		m_lambda1 = 1;
		AfxMessageBox(L"Enter a number from 1 to 1000");
		UpdateData(0);
	}
}


void SetPVS::OnEnKillfocusEdit1()
{
	UpdateData(1);
	if (m_sampSize > 1e7 || m_sampSize < 0) {
		m_sampSize = 1000;
		AfxMessageBox(L"Enter a number from 1 to 1e7");
		UpdateData(0);
	}
}


void SetPVS::OnEnKillfocusEdit4()
{
	UpdateData(1);
	if (m_pvsampSize > 1e7 || m_pvsampSize < 0) {
		m_pvsampSize = 1000;
		AfxMessageBox(L"Enter a number from 1 to 1e7");
		UpdateData(0);
	}
	// TODO: Add your control notification handler code here
}
