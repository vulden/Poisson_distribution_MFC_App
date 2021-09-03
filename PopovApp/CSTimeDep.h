#pragma once


// CSTimeDep dialog

class CSTimeDep : public CDialog
{
	DECLARE_DYNAMIC(CSTimeDep)

public:
	CSTimeDep(CWnd* pParent = nullptr);   // standard constructor
	virtual ~CSTimeDep();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG3 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	int m_sampSize;
	double m_step;
	afx_msg void OnEnKillfocusEdit4();
	afx_msg void OnEnKillfocusEdit3();
};
