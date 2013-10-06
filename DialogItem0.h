#if !defined(AFX_DIALOGITEM0_H__2B701E5C_AE85_43B0_BEC4_C40904D8D33E__INCLUDED_)
#define AFX_DIALOGITEM0_H__2B701E5C_AE85_43B0_BEC4_C40904D8D33E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DialogItem0.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDialogItem0 dialog

class CDialogItem0 : public CDialog
{
// Construction
public:
	CDialogItem0(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDialogItem0)
	enum { IDD = IDD_DIALOG_ITEM0 };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDialogItem0)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDialogItem0)
	virtual void OnOK();
	virtual void OnCancel();
	afx_msg void OnButtonApply();
	afx_msg void OnButtonChoiceDefFilePostion();
	afx_msg void OnButtonChoiceDefProgramPosition();
	afx_msg void OnRadioVc();
	afx_msg void OnRadioHand();
	afx_msg void OnSetfocusEditDefFilePosition();
	afx_msg void OnSetfocusEditDefProgramPosition();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DIALOGITEM0_H__2B701E5C_AE85_43B0_BEC4_C40904D8D33E__INCLUDED_)
