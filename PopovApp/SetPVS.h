#pragma once


// SetPVS dialog

class SetPVS : public CDialog
{
	DECLARE_DYNAMIC(SetPVS)

public:
	SetPVS(CWnd* pParent = nullptr);   // standard constructor
	virtual ~SetPVS();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG2 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	BOOL m_method;
	double m_lambda0;
	double m_lambda1;
	int m_sampSize;
	int m_pvsampSize;
	afx_msg void OnEnKillfocusEdit2();
	afx_msg void OnEnKillfocusEdit3();
	afx_msg void OnEnKillfocusEdit1();
	afx_msg void OnEnKillfocusEdit4();
};
