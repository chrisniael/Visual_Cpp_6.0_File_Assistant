// SettingDialog.cpp : implementation file
//

#include "stdafx.h"
#include "FileAssistant.h"
#include "SettingDialog.h"

#include "FileAssistantDlg.h"  //加载主对话框的头文件

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSettingDialog dialog


CSettingDialog::CSettingDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CSettingDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSettingDialog)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CSettingDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSettingDialog)
	DDX_Control(pDX, IDC_TAB_CTRL, m_tab_ctrl);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSettingDialog, CDialog)
	//{{AFX_MSG_MAP(CSettingDialog)
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB_CTRL, OnSelchangeTabCtrl)
	ON_WM_SYSCOMMAND()
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSettingDialog message handlers

void CSettingDialog::OnOK() 
{
	//------------获取主窗口对象的指针------------//
	((CFileAssistantDlg *)m_pMyDlg)->m_bSetting = TRUE;

	//CDialog::OnOK();

	//DestroyWindow();
}

void CSettingDialog::OnCancel() 
{
	//------------获取主窗口对象的指针-----------//
	((CFileAssistantDlg *)m_pMyDlg)->m_bSetting = FALSE;

	CDialog::OnCancel();

	DestroyWindow();
}

void CSettingDialog::OnSelchangeTabCtrl(NMHDR* pNMHDR, LRESULT* pResult) 
{
	int index = m_tab_ctrl.GetCurSel();

	m_DlgArray[m_index]->ShowWindow(SW_HIDE);

	m_index = index;
	m_DlgArray[m_index]->ShowWindow(SW_SHOW);
	
	*pResult = 0;
}

BOOL CSettingDialog::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here

	//-------------设置子对话框的图标--------------//
	SetIcon(AfxGetApp()->LoadIcon(IDI_ICON_VC), TRUE);


	m_tab_ctrl.InsertItem(0, "基本设置");
	m_tab_ctrl.InsertItem(1, "高级设置");
	m_tab_ctrl.InsertItem(2, "帮助");

	m_DlgArray[0] = &m_DlgItem0;
	m_DlgArray[1] = &m_DlgItem1;
	m_DlgArray[2] = &m_DlgItem2;

	m_DlgItem0.Create(IDD_DIALOG_ITEM0, &m_tab_ctrl);
	m_DlgItem1.Create(IDD_DIALOG_ITEM1, &m_tab_ctrl);
	m_DlgItem2.Create(IDD_DIALOG_ABOUT, &m_tab_ctrl);

	m_tab_ctrl.GetClientRect(&m_rect);

	m_rect.left += 2;
	m_rect.top += 21;
	m_rect.right -= 2;
	m_rect.bottom -= 2;

	//-------调整子窗口的位置和大小-------//
	m_DlgItem0.MoveWindow(&m_rect);
	m_DlgItem1.MoveWindow(&m_rect);
	m_DlgItem2.MoveWindow(&m_rect);

	//-------初始化显示Item0------//
	m_index = 0;
	m_DlgItem0.ShowWindow(SW_SHOW);



	//------------------读取注册表配置信息---------------//
	HKEY hKey;
	if(RegOpenKey(HKEY_CURRENT_USER, "Software\\VC6.0 FILE ASSISTANT", &hKey) != ERROR_SUCCESS)
	{
		//----------键不存在----------//
		char strValue[MAX_PATH];   

		//----------获取桌面的完整路径----------//
		SHGetSpecialFolderPath(this->GetSafeHwnd(), strValue, CSIDL_DESKTOP, 0); 

		//------------------------------------获取用户文件夹----------------------------------------//
		
		m_DlgItem0.SetDlgItemText(IDC_EDIT_DEF_FILE_POSITION, (const char *)strValue);  //根据注册表数据设置控件

		((CButton *)m_DlgItem0.GetDlgItem(IDC_RADIO_VC))->SetCheck(1);

		((CEdit *)m_DlgItem0.GetDlgItem(IDC_EDIT_DEF_PROGRAM_POSITION))->EnableWindow(FALSE);
		((CButton *)m_DlgItem0.GetDlgItem(IDC_BUTTON_CHOICE_DEF_PROGRAM_POSITION))->EnableWindow(FALSE);

	}
	else
	{
		DWORD type;
		DWORD length;
		BYTE *strValue;

		//--------------------控件IDC_DEF_FILE_POSITION------------------//
		if(RegQueryValueEx(hKey, "FilePosition", 0, &type, NULL, &length) != ERROR_SUCCESS)  //获取数据长度
		{
			MessageBox("RegQueryValueEx1 Fail.");
		}
		else
		{
			strValue = new BYTE[length];
			if(RegQueryValueEx(hKey, "FilePosition", 0, &type, (LPBYTE)strValue, &length) != ERROR_SUCCESS)
			{
				MessageBox("RegQueryValueEx2 Fail.");
			}
			else
			{
				m_DlgItem0.SetDlgItemText(IDC_EDIT_DEF_FILE_POSITION, (const char *)strValue);  //根据注册表数据设置控件
			}

			delete [] strValue;
		}


		//--------------------控件默认程序------------------//
		if(RegQueryValueEx(hKey, "ProgramPosition", 0, &type, NULL, &length) != ERROR_SUCCESS)  //获取数据长度
		{
			MessageBox("RegQueryValueEx1 Fail.");
		}
		else
		{
			strValue = new BYTE[length];
			if(RegQueryValueEx(hKey, "ProgramPosition", 0, &type, (LPBYTE)strValue, &length) != ERROR_SUCCESS)
			{
				MessageBox("RegQueryValueEx2 Fail.");
			}
			else
			{
				if(strcmp((const char*)strValue, "MSDEV.EXE") == 0)
				{
					((CButton *)m_DlgItem0.GetDlgItem(IDC_RADIO_VC))->SetCheck(1);
					((CButton *)m_DlgItem0.GetDlgItem(IDC_RADIO_HAND))->SetCheck(0);

					((CEdit *)m_DlgItem0.GetDlgItem(IDC_EDIT_DEF_PROGRAM_POSITION))->EnableWindow(FALSE);
					((CButton *)m_DlgItem0.GetDlgItem(IDC_BUTTON_CHOICE_DEF_PROGRAM_POSITION))->EnableWindow(FALSE);
				}
				else
				{
					((CButton *)m_DlgItem0.GetDlgItem(IDC_RADIO_VC))->SetCheck(0);
					((CButton *)m_DlgItem0.GetDlgItem(IDC_RADIO_HAND))->SetCheck(1);

					((CEdit *)m_DlgItem0.GetDlgItem(IDC_EDIT_DEF_PROGRAM_POSITION))->SetWindowText((const char *)strValue);
				}
			}

			delete [] strValue;
		}

		RegCloseKey(hKey);
	}

	//--------------从注册表中读取开机自动启动的配置信息------------//
	if(RegOpenKey(HKEY_CURRENT_USER, "Software\\Microsoft\\Windows\\CurrentVersion\\Run", &hKey) != ERROR_SUCCESS)
	{
		//----------键不存在----------//
		//MessageBox("RegOpenKey Fail.");
	}
	else
	{
		DWORD type;
		DWORD length;

		if(RegQueryValueEx(hKey, "VC6.0 File Assistant", 0, &type, NULL, &length) != ERROR_SUCCESS)
		{
			((CButton *)m_DlgItem1.GetDlgItem(IDC_CHECK_AUTORUN))->SetCheck(0);
		}
		else
		{
			((CButton *)m_DlgItem1.GetDlgItem(IDC_CHECK_AUTORUN))->SetCheck(1);  //选上
		}
			
	}

	//-------------设置快捷键按钮的初始状态-------------//
	m_DlgItem1.m_hot_key_ctrl1.SetRules(HKCOMB_A | HKCOMB_C | HKCOMB_S | HKCOMB_CA | HKCOMB_SC | HKCOMB_SA, 0);
	m_DlgItem1.m_hot_key_ctrl2.SetRules(HKCOMB_A | HKCOMB_C | HKCOMB_S | HKCOMB_CA | HKCOMB_SC | HKCOMB_SA, 0);
	m_DlgItem1.m_hot_key_ctrl3.SetRules(HKCOMB_A | HKCOMB_C | HKCOMB_S | HKCOMB_CA | HKCOMB_SC | HKCOMB_SA, 0);


	
	if(RegOpenKey(HKEY_CURRENT_USER, "Software\\VC6.0 File Assistant" ,&hKey) != ERROR_SUCCESS)
	{
		//MessageBox("RegOpenKey Fail.");
		m_DlgItem1.m_hot_key_ctrl1.EnableWindow(FALSE);
		m_DlgItem1.m_hot_key_ctrl2.EnableWindow(FALSE);
		m_DlgItem1.m_hot_key_ctrl3.EnableWindow(FALSE);

	}
	else
	{	DWORD type;
		DWORD length;
		DWORD dwValue_VK_FAST_NEW;
		DWORD dwValue_VK_NEW;
		DWORD dwValue_VK_OPEN;


		//----------------FAST_NEW------------------//
		if(RegQueryValueEx(hKey, "VK_FAST_NEW", 0, &type, NULL, &length) != ERROR_SUCCESS)  //键值不存在
		{
			m_DlgItem1.m_hot_key_ctrl1.EnableWindow(FALSE);
		}
		else
		{
			if(RegQueryValueEx(hKey, "VK_FAST_NEW", 0, &type, (LPBYTE)&dwValue_VK_FAST_NEW, &length) != ERROR_SUCCESS)
			{
				MessageBox("RegQueryValueEx2 Fail.");
			}
			else
			{
				((CButton *)m_DlgItem1.GetDlgItem(IDC_CHECK_USE_FAST_NEW))->SetCheck(1);

				WORD wVK = (WORD)dwValue_VK_FAST_NEW;
				m_DlgItem1.m_hot_key_ctrl1.SetHotKey(wVK, 0);   //设置热键1
			}
		}


		//------------------NEW------------------//
		if(RegQueryValueEx(hKey, "VK_NEW", 0, &type, NULL, &length) != ERROR_SUCCESS)  //键值不存在
		{
			m_DlgItem1.m_hot_key_ctrl2.EnableWindow(FALSE);
		}
		else
		{
			if(RegQueryValueEx(hKey, "VK_NEW", 0, &type, (LPBYTE)&dwValue_VK_NEW, &length) != ERROR_SUCCESS)
			{
				MessageBox("RegQueryValueEx2 Fail.");
			}
			else
			{
				((CButton *)m_DlgItem1.GetDlgItem(IDC_CHECK_USE_NEW))->SetCheck(1);

				WORD wVK = (WORD)dwValue_VK_NEW;
				m_DlgItem1.m_hot_key_ctrl2.SetHotKey(wVK, 0);   //设置热键1
			}
		}

		//------------------OPEN------------------//
		if(RegQueryValueEx(hKey, "VK_OPEN", 0, &type, NULL, &length) != ERROR_SUCCESS)  //键值不存在
		{
			m_DlgItem1.m_hot_key_ctrl3.EnableWindow(FALSE);
		}
		else
		{
			if(RegQueryValueEx(hKey, "VK_OPEN", 0, &type, (LPBYTE)&dwValue_VK_OPEN, &length) != ERROR_SUCCESS)
			{
				MessageBox("RegQueryValueEx2 Fail.");
			}
			else
			{
				((CButton *)m_DlgItem1.GetDlgItem(IDC_CHECK_USE_OPEN))->SetCheck(1);

				WORD wVK = (WORD)dwValue_VK_OPEN;
				m_DlgItem1.m_hot_key_ctrl3.SetHotKey(wVK, 0);   //设置热键1
			}
		}






		RegCloseKey(hKey);
	}




	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CSettingDialog::OnDestroy() 
{
	CDialog::OnDestroy();
	
	delete this;
}
