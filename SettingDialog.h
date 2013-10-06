#if !defined(AFX_SETTINGDIALOG_H__3830D7E5_AC25_4E1F_96CD_BC89334A87D2__INCLUDED_)
#define AFX_SETTINGDIALOG_H__3830D7E5_AC25_4E1F_96CD_BC89334A87D2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SettingDialog.h : header file
//

#include "DialogItem0.h"
#include "DialogItem1.h"
#include "AboutDialog.h"

/////////////////////////////////////////////////////////////////////////////
// CSettingDialog dialog

class CSettingDialog : public CDialog
{
// Construction
public:
	CSettingDialog(CWnd* pParent = NULL);   // standard constructor

	CDialog *m_pMyDlg;  //保存主窗口的指针
	
	CDialog * m_DlgArray[3];  //子窗口指针

// Dialog Data
	//{{AFX_DATA(CSettingDialog)
	enum { IDD = IDD_MY_DIALOG };
	CTabCtrl	m_tab_ctrl;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSettingDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void OnOK();
	virtual void OnCancel();
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CSettingDialog)
	afx_msg void OnSelchangeTabCtrl(NMHDR* pNMHDR, LRESULT* pResult);
	virtual BOOL OnInitDialog();
	afx_msg void OnDestroy();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	CDialogItem0 m_DlgItem0;
	CDialogItem1 m_DlgItem1;
	CAboutDialog m_DlgItem2;

	CRect m_rect;

	int m_index;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SETTINGDIALOG_H__3830D7E5_AC25_4E1F_96CD_BC89334A87D2__INCLUDED_)
