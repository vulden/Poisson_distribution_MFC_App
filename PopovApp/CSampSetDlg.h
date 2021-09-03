#pragma once


// CSampSetDlg dialog

class CSampSetDlg : public CDialog
{
	DECLARE_DYNAMIC(CSampSetDlg)

public:
	CSampSetDlg(CWnd* pParent = nullptr);   // standard constructor
	virtual ~CSampSetDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	double m_lambda;
	int m_sampSize;
	int m_method;
	afx_msg void OnEnKillfocusEdit1();
	afx_msg void OnEnKillfocusEdit3();
	afx_msg void OnBnClickedRadio2();
};
