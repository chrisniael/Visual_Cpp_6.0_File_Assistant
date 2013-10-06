#if !defined(AFX_DIALOGITEM1_H__489F8278_A9AC_4521_AA46_0177255CAB10__INCLUDED_)
#define AFX_DIALOGITEM1_H__489F8278_A9AC_4521_AA46_0177255CAB10__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DialogItem1.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDialogItem1 dialog

class CDialogItem1 : public CDialog
{
// Construction
public:
	CDialogItem1(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDialogItem1)
	enum { IDD = IDD_DIALOG_ITEM1 };
	CHotKeyCtrl	m_hot_key_ctrl3;
	CHotKeyCtrl	m_hot_key_ctrl2;
	CHotKeyCtrl	m_hot_key_ctrl1;
	CButton	m_check_autorun;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDialogItem1)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDialogItem1)
	virtual void OnOK();
	virtual void OnCancel();
	afx_msg void OnButtonApply();
	afx_msg void OnCheckUseFastNew();
	afx_msg void OnCheckUseNew();
	afx_msg void OnCheckUseOpen();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DIALOGITEM1_H__489F8278_A9AC_4521_AA46_0177255CAB10__INCLUDED_)
