// DialogItem1.cpp : implementation file
//

#include "stdafx.h"
#include "FileAssistant.h"
#include "DialogItem1.h"

#include "FileAssistantDlg.h"

#define WM_RESETHOTKEY WM_USER + 1

//---------------��ݼ���ע��-----------//
#define g_nAtomFirst  1001
#define g_nAtomSecond 1002
#define g_nAtomThird  1003
#define	g_nAtomFouth  1004
#define g_nAtomFifth  1005

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDialogItem1 dialog

//-------�����ڵľ��-------//
extern HWND g_hWnd;



CDialogItem1::CDialogItem1(CWnd* pParent /*=NULL*/)
	: CDialog(CDialogItem1::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDialogItem1)
	//}}AFX_DATA_INIT
}


void CDialogItem1::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDialogItem1)
	DDX_Control(pDX, IDC_HOTKEY3, m_hot_key_ctrl3);
	DDX_Control(pDX, IDC_HOTKEY2, m_hot_key_ctrl2);
	DDX_Control(pDX, IDC_HOTKEY1, m_hot_key_ctrl1);
	DDX_Control(pDX, IDC_CHECK_AUTORUN, m_check_autorun);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDialogItem1, CDialog)
	//{{AFX_MSG_MAP(CDialogItem1)
	ON_BN_CLICKED(IDC_BUTTON_APPLY, OnButtonApply)
	ON_BN_CLICKED(IDC_CHECK_USE_FAST_NEW, OnCheckUseFastNew)
	ON_BN_CLICKED(IDC_CHECK_USE_NEW, OnCheckUseNew)
	ON_BN_CLICKED(IDC_CHECK_USE_OPEN, OnCheckUseOpen)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDialogItem1 message handlers

void CDialogItem1::OnOK() 
{
	OnButtonApply();

	//-------------�˳�����------------//
	GetParent()->GetParent()->PostMessage(WM_CLOSE);

	CDialog::OnOK();
}

void CDialogItem1::OnCancel() 
{
	//-------------�˳�����------------//
	GetParent()->GetParent()->PostMessage(WM_CLOSE);

	CDialog::OnCancel();
}

void CDialogItem1::OnButtonApply() 
{
	int stateAutoRun = m_check_autorun.GetCheck();

	int statusFastNew = ((CButton *)GetDlgItem(IDC_CHECK_USE_FAST_NEW))->GetCheck();
	int statusNew     = ((CButton *)GetDlgItem(IDC_CHECK_USE_NEW))->GetCheck();
	int statusOpen    = ((CButton *)GetDlgItem(IDC_CHECK_USE_OPEN))->GetCheck();


	WORD wFastNewTest, wNewTest, wOpenTest;
	WORD wComb;
		
	m_hot_key_ctrl1.GetHotKey(wFastNewTest, wComb);
	m_hot_key_ctrl2.GetHotKey(wNewTest, wComb);
	m_hot_key_ctrl3.GetHotKey(wOpenTest, wComb);


	BOOL bIsRight = TRUE;
	//---------------�ж��ȼ��Ƿ��趨--------------//
	if(statusFastNew == 1)
	{

		if(wFastNewTest == 229 || wFastNewTest == 0)
		{
			bIsRight = FALSE;
			/*
			MessageBox("�붨���ݼ�!");
			m_hot_key_ctrl1.SetFocus();
			return ;
			*/
		}
		else if(wFastNewTest == 'S' || wFastNewTest == 'Q')
		{
			bIsRight = FALSE;
			//MessageBox("�ȼ���ͻ, �����¶���!");
			m_hot_key_ctrl1.SetHotKey(0, 0);
			//m_hot_key_ctrl1.SetFocus();
			//return;
		}
		else
		{
			if(statusNew == 1 && wFastNewTest == wNewTest)
			{
				bIsRight = FALSE;
				//MessageBox("�ȼ���ͻ, �����¶���!");
				m_hot_key_ctrl1.SetHotKey(0, 0);
				m_hot_key_ctrl2.SetHotKey(0, 0);
				//m_hot_key_ctrl1.SetFocus();
				//return ;
			}

			if(statusOpen == 1 && wFastNewTest == wOpenTest)
			{
				bIsRight = FALSE;
				//MessageBox("�ȼ���ͻ, �����¶���!");
				m_hot_key_ctrl1.SetHotKey(0, 0);
				m_hot_key_ctrl3.SetHotKey(0, 0);
				//m_hot_key_ctrl1.SetFocus();
				//return ;
			}

		}
	}

	if(statusNew == 1)
	{
		if(wNewTest == 229 || wNewTest == 0)
		{
			bIsRight = FALSE;
			/*
			MessageBox("�붨���ݼ�!");
			m_hot_key_ctrl2.SetFocus();
			return ;
			*/
		}
		else if(wNewTest == 'S' || wNewTest == 'Q')
		{
			bIsRight = FALSE;
			//MessageBox("�ȼ���ͻ, �����¶���!");
			m_hot_key_ctrl2.SetHotKey(0, 0);
			//m_hot_key_ctrl2.SetFocus();
			//return;
		}
		else
		{

			if(statusOpen == 1 && wNewTest == wOpenTest)
			{
				bIsRight = FALSE;
				//MessageBox("�ȼ���ͻ, �����¶���!");
				m_hot_key_ctrl2.SetHotKey(0, 0);
				m_hot_key_ctrl3.SetHotKey(0, 0);
				//m_hot_key_ctrl3.SetFocus();

				//return;
			}
		}
	}

	if(statusOpen == 1)
	{
		if(wOpenTest == 229 || wOpenTest == 0)
			{
				bIsRight = FALSE;
			}
			else if(wOpenTest == 'S' || wOpenTest == 'Q')
			{
				bIsRight = FALSE;

				m_hot_key_ctrl3.SetHotKey(0, 0);
			}
	}

	if(bIsRight == FALSE)
	{
		MessageBox("�ȼ���������, ����������!");
		return ;
	}


	HKEY hKey;

	//-----------���������ñ�����ע���--------//
	if(stateAutoRun == 1)
	{
		//���ó��򿪻��Զ�����

		//----------��ȡ���������·��----------//
		 

		CString strProgramDir;
		GetModuleFileName(NULL, strProgramDir.GetBuffer(255), 255);
		strProgramDir.ReleaseBuffer();

		//MessageBox(strProgramDir);


		if(RegOpenKey(HKEY_CURRENT_USER, "Software\\Microsoft\\Windows\\CurrentVersion\\Run" ,&hKey) != ERROR_SUCCESS)
		{
			MessageBox("RegOpenKey Failed.");
		}
		else
		{
			if(RegSetValueEx(hKey, "VC6.0 File Assistant", 0, REG_SZ, (CONST BYTE *)strProgramDir.GetBuffer(strProgramDir.GetLength()), (DWORD)strProgramDir.GetLength()) != ERROR_SUCCESS)
			{
				MessageBox("RegSetValueEx Failed.");
			}

			RegCloseKey(hKey);
		}  

	}
	else
	{
		//---------ȡ�������Զ�����------------//
		
		if(RegOpenKey(HKEY_CURRENT_USER, "Software\\Microsoft\\Windows\\CurrentVersion\\Run" ,&hKey) != ERROR_SUCCESS)
		{
			MessageBox("RegOpenKey Fail.");
		}
		else
		{
	
			if(RegDeleteValue(hKey, "VC6.0 File Assistant") != ERROR_SUCCESS)
			{
				//MessageBox("RegDeleteValue Failed.");
			}
		
			RegCloseKey(hKey);
		}  

	}

	//----------------����ݼ�����д��ע���------------����ע��������Ŀ�ݼ�-----------//

	if(statusFastNew == 1)
	{
		WORD wVK, wVKComb;
		m_hot_key_ctrl1.GetHotKey(wVK, wVKComb);


		DWORD dwValue = (DWORD)wVK;
		if(RegCreateKey(HKEY_CURRENT_USER, "Software\\VC6.0 File Assistant", &hKey) != ERROR_SUCCESS)
		{
			MessageBox("RegCreateKey FAST_NEW Failed.");
		}
		else
		{
			if(RegSetValueEx(hKey, "VK_FAST_NEW", 0, REG_DWORD, (CONST BYTE *)&dwValue, (DWORD)sizeof(dwValue)) != ERROR_SUCCESS)
			{
				MessageBox("RegSetValue FAST_NEW Failed.");
			}
			
			RegCloseKey(hKey);
		}

		//----------------����ע���ȼ�FAST_NEW--------------//

		::PostMessage(g_hWnd, WM_RESETHOTKEY, g_nAtomFirst, (LPARAM)wVK);

	}
	else
	{

		if(RegOpenKey(HKEY_CURRENT_USER, "Software\\VC6.0 File Assistant" ,&hKey) != ERROR_SUCCESS)
		{
			MessageBox("RegOpenKey FAST_NEW Failed.");
		}
		else
		{
	
			if(RegDeleteValue(hKey, "VK_FAST_NEW") != ERROR_SUCCESS)
			{
				//MessageBox("RegDeleteValue FAST_NEW Failed.");
			}
		
			RegCloseKey(hKey);
			
		} 

		//-----------��ԭĬ�Ͽ�ݼ� FAST_NEW-----------//
		::PostMessage(g_hWnd, WM_RESETHOTKEY, g_nAtomFirst, (LPARAM)'M');


	}

	if(statusNew == 1)
	{
		WORD wVK, wVKComb;
		m_hot_key_ctrl2.GetHotKey(wVK, wVKComb);


		DWORD dwValue = (DWORD)wVK;
		if(RegCreateKey(HKEY_CURRENT_USER, "Software\\VC6.0 File Assistant", &hKey) != ERROR_SUCCESS)
		{
			MessageBox("RegCreateKey Fail.");
		}
		else
		{
			if(RegSetValueEx(hKey, "VK_NEW", 0, REG_DWORD, (CONST BYTE *)&dwValue, (DWORD)sizeof(dwValue)) != ERROR_SUCCESS)
			{
				MessageBox("RegSetValue1 Fail.");
			}
			
			RegCloseKey(hKey);
		}

		//----------------����ע���ȼ�FAST_NEW--------------//

		::PostMessage(g_hWnd, WM_RESETHOTKEY, g_nAtomSecond, (LPARAM)wVK);
	}
	else
	{
		if(RegOpenKey(HKEY_CURRENT_USER, "Software\\VC6.0 File Assistant" ,&hKey) != ERROR_SUCCESS)
		{
			MessageBox("RegOpenKey Fail.");
		}
		else
		{
	
			if(RegDeleteValue(hKey, "VK_NEW") != ERROR_SUCCESS)
			{
				//MessageBox("RegDeleteValue Failed.");
			}
		
			RegCloseKey(hKey);
		}

		//-----------��ԭĬ�Ͽ�ݼ� FAST_NEW-----------//
		::PostMessage(g_hWnd, WM_RESETHOTKEY, g_nAtomSecond, (LPARAM)'N');

	}


	if(statusOpen == 1)
	{
		WORD wVK, wVKComb;
		m_hot_key_ctrl3.GetHotKey(wVK, wVKComb);


		DWORD dwValue = (DWORD)wVK;
		if(RegCreateKey(HKEY_CURRENT_USER, "Software\\VC6.0 File Assistant", &hKey) != ERROR_SUCCESS)
		{
			MessageBox("RegCreateKey Fail.");
		}
		else
		{
			if(RegSetValueEx(hKey, "VK_OPEN", 0, REG_DWORD, (CONST BYTE *)&dwValue, (DWORD)sizeof(dwValue)) != ERROR_SUCCESS)
			{
				MessageBox("RegSetValue1 Fail.");
			}
			
			RegCloseKey(hKey);
		}

		//----------------����ע���ȼ�OPEN--------------//

		::PostMessage(g_hWnd, WM_RESETHOTKEY, g_nAtomThird, (LPARAM)wVK);

	}
	else
	{
		if(RegOpenKey(HKEY_CURRENT_USER, "Software\\VC6.0 File Assistant" ,&hKey) != ERROR_SUCCESS)
		{
			MessageBox("RegOpenKey Fail.");
		}
		else
		{
	
			if(RegDeleteValue(hKey, "VK_OPEN") != ERROR_SUCCESS)
			{
				//MessageBox("RegDeleteValue Failed.");
			}
		
			RegCloseKey(hKey);
		}

		//-----------��ԭĬ�Ͽ�ݼ� OPEN-----------//
		::PostMessage(g_hWnd, WM_RESETHOTKEY, g_nAtomThird, (LPARAM)'O');

	}

	


}


void CDialogItem1::OnCheckUseFastNew() 
{
	int statusFastNew = ((CButton *)GetDlgItem(IDC_CHECK_USE_FAST_NEW))->GetCheck();

	if(statusFastNew == 0)
	{
		m_hot_key_ctrl1.EnableWindow(FALSE);
	}
	else if(statusFastNew == 1)
	{
		m_hot_key_ctrl1.EnableWindow(TRUE);
	}

	
}

void CDialogItem1::OnCheckUseNew() 
{
	int statusNew     = ((CButton *)GetDlgItem(IDC_CHECK_USE_NEW))->GetCheck();

	if(statusNew == 0)
	{
		m_hot_key_ctrl2.EnableWindow(FALSE);
	}
	else
	{
		m_hot_key_ctrl2.EnableWindow(TRUE);
	}
	
}

void CDialogItem1::OnCheckUseOpen() 
{
	int statusOpen    = ((CButton *)GetDlgItem(IDC_CHECK_USE_OPEN))->GetCheck();

	if(statusOpen == 0)
	{
		m_hot_key_ctrl3.EnableWindow(FALSE);
	}
	else
	{
		m_hot_key_ctrl3.EnableWindow(TRUE);
	}
}
