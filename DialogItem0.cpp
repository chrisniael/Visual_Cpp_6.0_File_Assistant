// DialogItem0.cpp : implementation file
//

#include "stdafx.h"
#include "FileAssistant.h"
#include "DialogItem0.h"


#include "DialogItem1.h"  //�����ֵܴ���
#include "SettingDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDialogItem0 dialog


CDialogItem0::CDialogItem0(CWnd* pParent /*=NULL*/)
	: CDialog(CDialogItem0::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDialogItem0)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CDialogItem0::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDialogItem0)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDialogItem0, CDialog)
	//{{AFX_MSG_MAP(CDialogItem0)
	ON_BN_CLICKED(IDC_BUTTON_APPLY, OnButtonApply)
	ON_BN_CLICKED(IDC_BUTTON_CHOICE_DEF_FILE_POSTION, OnButtonChoiceDefFilePostion)
	ON_BN_CLICKED(IDC_BUTTON_CHOICE_DEF_PROGRAM_POSITION, OnButtonChoiceDefProgramPosition)
	ON_BN_CLICKED(IDC_RADIO_VC, OnRadioVc)
	ON_BN_CLICKED(IDC_RADIO_HAND, OnRadioHand)
	ON_EN_SETFOCUS(IDC_EDIT_DEF_FILE_POSITION, OnSetfocusEditDefFilePosition)
	ON_EN_SETFOCUS(IDC_EDIT_DEF_PROGRAM_POSITION, OnSetfocusEditDefProgramPosition)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDialogItem0 message handlers

//------------ȫ���ⲿ����----------//
extern CString lpDirectory;
extern CString lpDefaultProgram;

void CDialogItem0::OnOK() 
{
	OnButtonApply();

	//-------------�˳�����------------//
	GetParent()->GetParent()->SendMessage(WM_CLOSE);
	
	CDialog::OnOK();
}

void CDialogItem0::OnCancel() 
{
	//-------------�˳�����------------//
	GetParent()->GetParent()->SendMessage(WM_CLOSE);
	
	CDialog::OnCancel();
}

void CDialogItem0::OnButtonApply() 
{

	//---------------���ݿؼ���״̬���������ļ�---------------//
	CString strFilePosition, strProgramPosition;
	(CEdit *)GetDlgItemText(IDC_EDIT_DEF_FILE_POSITION, strFilePosition);

	int VCState   = ((CButton *)GetDlgItem(IDC_RADIO_VC))->GetCheck();
	int HandState = ((CButton *)GetDlgItem(IDC_RADIO_HAND))->GetCheck();

	if(VCState == 1 && HandState == 0)
	{
		strProgramPosition = "MSDEV.EXE";
	}
	else
	{
		(CEdit *)GetDlgItemText(IDC_EDIT_DEF_PROGRAM_POSITION, strProgramPosition);
	}
	
	//---------------��������Ϣ������������-------------//
	lpDirectory = strFilePosition;    //Ĭ��·��
	lpDirectory += "\\";
	
	lpDefaultProgram = strProgramPosition;    //Ĭ�ϳ���	


	//-----------------��������Ϣд��ע���------------//
	HKEY hKey;
	if(RegCreateKey(HKEY_CURRENT_USER, "Software\\VC6.0 File Assistant", &hKey) != ERROR_SUCCESS)
	{
		MessageBox("RegCreateKey Fail.");
	}
	else
	{
		if(RegSetValueEx(hKey, "FilePosition", 0, REG_SZ, (CONST BYTE *)strFilePosition.GetBuffer(strFilePosition.GetLength()), (DWORD)strFilePosition.GetLength()) != ERROR_SUCCESS)
		{
			MessageBox("RegSetValue1 Fail.");
		}
		
		if(RegSetValueEx(hKey, "ProgramPosition", 0, REG_SZ, (CONST BYTE *)strProgramPosition.GetBuffer(strProgramPosition.GetLength()), (DWORD)strProgramPosition.GetLength()) != ERROR_SUCCESS)
		{
			MessageBox("RegSetValue2 Fial.");
		}

		RegCloseKey(hKey);
	}

	
}

void CDialogItem0::OnButtonChoiceDefFilePostion() 
{

	char strPath[MAX_PATH] = "";

	BROWSEINFO bi;

	bi.hwndOwner = GetSafeHwnd();
	bi.iImage = NULL;
	bi.lParam = NULL;
	bi.lpfn = NULL;
	bi.lpszTitle = "��ѡ��ѡ��Ĭ���ļ�·��:";
	bi.pidlRoot = NULL;
	bi.pszDisplayName = strPath;
	bi.ulFlags = BIF_RETURNONLYFSDIRS;
	
	//----------VC6.0�汾����---------//
	//bi.ulFlags = BIF_EDITBOX | BIF_NEWDIALOGSTYLE | BIF_USENEWUI;

	ITEMIDLIST *pIIL = SHBrowseForFolder(&bi);

	

	if(pIIL != NULL)
	{
		char chPath[MAX_PATH] = "";
		SHGetPathFromIDList(pIIL, chPath);
		//MessageBox(chPath);

		SetDlgItemText(IDC_EDIT_DEF_FILE_POSITION, chPath);
	}

}

void CDialogItem0::OnButtonChoiceDefProgramPosition() 
{

	CFileDialog OpenFileDialog(TRUE);

	OpenFileDialog.m_ofn.lpstrFilter = "Ӧ�ó���(*.exe)\0*.exe\0\0";

	if(IDOK == OpenFileDialog.DoModal())
	{
		CString strPathName = OpenFileDialog.GetPathName();

		SetDlgItemText(IDC_EDIT_DEF_PROGRAM_POSITION, strPathName);
	}

}

void CDialogItem0::OnRadioVc() 
{
	((CEdit *)GetDlgItem(IDC_EDIT_DEF_PROGRAM_POSITION))->EnableWindow(FALSE);
	((CButton *)GetDlgItem(IDC_BUTTON_CHOICE_DEF_PROGRAM_POSITION))->EnableWindow(FALSE);
}

void CDialogItem0::OnRadioHand() 
{
	((CEdit *)GetDlgItem(IDC_EDIT_DEF_PROGRAM_POSITION))->EnableWindow(TRUE);
	((CButton *)GetDlgItem(IDC_BUTTON_CHOICE_DEF_PROGRAM_POSITION))->EnableWindow(TRUE);
}

void CDialogItem0::OnSetfocusEditDefFilePosition() 
{
	DestroyCaret();
}

void CDialogItem0::OnSetfocusEditDefProgramPosition() 
{
	DestroyCaret();
}
