// CodesPasteDlg.h : header file
//

#if !defined(AFX_CODESPASTEDLG_H__8D566C99_8705_4080_8C4B_61A33A132269__INCLUDED_)
#define AFX_CODESPASTEDLG_H__8D566C99_8705_4080_8C4B_61A33A132269__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CCodesPasteDlg dialog

class CCodesPasteDlg : public CDialog
{
// Construction
public:
	CCodesPasteDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CCodesPasteDlg)
	enum { IDD = IDD_CODESPASTE_DIALOG };
	CComboBox	m_type_select;
	CEdit	m_password_ctl;
	CString	m_username;
	CString	m_password;
	CString	m_codes;
	CString	m_info;
	CString	m_Status;
	CString	m_pass_title;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCodesPasteDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CCodesPasteDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnPaste_click();
	afx_msg void OnSTATIChelp_click();
	afx_msg void OnPrivate_click();
	afx_msg void OnPublic_click();
	afx_msg void CodeType_OnChange();
	afx_msg void OnSetfocusInfo();
	afx_msg void OnSetfocusCodes();
	afx_msg void OnKillfocusCodes();
	afx_msg void OnSetfocusName();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CODESPASTEDLG_H__8D566C99_8705_4080_8C4B_61A33A132269__INCLUDED_)
