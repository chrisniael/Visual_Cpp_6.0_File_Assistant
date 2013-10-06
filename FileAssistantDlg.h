// FileAssistantDlg.h : header file
//

#if !defined(AFX_FILEASSISTANTDLG_H__0DC7CDCF_03AF_4C7D_ADE5_FE3BFB6358EB__INCLUDED_)
#define AFX_FILEASSISTANTDLG_H__0DC7CDCF_03AF_4C7D_ADE5_FE3BFB6358EB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "SettingDialog.h"   //加载CSettingDialog类的头文件


/////////////////////////////////////////////////////////////////////////////
// CFileAssistantDlg dialog

class CFileAssistantDlg : public CDialog
{
// Construction
public:
	CFileAssistantDlg(CWnd* pParent = NULL);	// standard constructor

	BOOL m_bSetting;  //是否打开设置窗口

	OPENFILENAME ofn;
	OPENFILENAME sfn;

	TCHAR szFileNameOpen[MAX_PATH];
	TCHAR szFileNameSave[MAX_PATH];

// Dialog Data
	//{{AFX_DATA(CFileAssistantDlg)
	enum { IDD = IDD_FILEASSISTANT_DIALOG };
	CRichEditCtrl	m_RichEdit;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFileAssistantDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CFileAssistantDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	virtual void OnOK();
	virtual void OnCancel();
	afx_msg void OnButtonNew();
	afx_msg void OnButtonOpen();
	afx_msg UINT OnNcHitTest(CPoint point);
	afx_msg void OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized);
	afx_msg LRESULT OnHotkey(WPARAM wParam, LPARAM lParam);
	afx_msg void OnDestroy();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnResetHotKey(WPARAM wParam, LPARAM lParam);
	afx_msg void OnNcPaint();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	BOOL m_bQuit;
	CSettingDialog *m_pSettingDialog;
	int m_nNumber;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FILEASSISTANTDLG_H__0DC7CDCF_03AF_4C7D_ADE5_FE3BFB6358EB__INCLUDED_)
