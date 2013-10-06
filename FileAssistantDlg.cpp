// FileAssistantDlg.cpp : implementation file
//

#include "stdafx.h"
#include "FileAssistant.h"
#include "FileAssistantDlg.h"

//---------�Զ�����Ϣ----------//
#define WM_RESETHOTKEY WM_USER + 1

//---------------��ݼ���ע��-----------//
#define g_nAtomFirst  1001
#define g_nAtomSecond 1002
#define g_nAtomThird  1003
#define	g_nAtomFouth  1004
#define g_nAtomFifth  1005


//----------�жϲ���ϵͳ�İ汾------------//
extern BOOL g_bIsWin7;


int MyOpenFile(CString lpFileName, CString lpDirectory, CString lpDefaultProgram, INT nCmdShow);
int MyNewFile(CString lpFileName, CString lpDirectory, DWORD dwCreationDisposition);


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////

//-----------��дRichEdit���ڹ��̺���-----------//
WNDPROC prevProc;

//-----------�ⲿ����----------//
HWND g_hWnd = NULL;

//BOOL bIfCtrlDown = false;

CString lpRichEditContent = "";

long lContentLength;

CString lpIsExit = "";

CString lpFileName;

CString lpDirectory; // = "C:\\Users\\����\\Desktop\\";

CString lpDefaultProgram; // = "MSDEV.EXE";

INT nCmdShow = SW_MAXIMIZE;


LRESULT CALLBACK NewRichEditProc( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{

	if(uMsg == WM_KEYDOWN)
	{

		switch(wParam)
		{
		case VK_RETURN:
			((CRichEditCtrl *)CWnd::FromHandle(hWnd))->GetWindowText(lpRichEditContent);
			//AfxMessageBox(lpRichEditContent);

			//lpDefaultProgram = "MSDEV.EXE";

			//nCmdShow = SW_SHOWMAXIMIZED;

			//-------------�ж�RichEdit�����Ƿ�Ϊ��------------//
			if(lpRichEditContent.GetLength() == 0)
			{
				ShellExecute(NULL, "open", lpDefaultProgram, NULL, NULL, nCmdShow);
			}
			else
			{
				//---------------�����½��ļ�����-----------------//

				lpFileName = lpRichEditContent;

				//---------------�Զ���׺��-------------//

				int nDotNumber = 0;
				for(int i = 0; i < lpFileName.GetLength(); i++)
				{
					if(lpFileName[i] == '.')
					{
						nDotNumber++;
					}
				}

				if(nDotNumber == 0)
				{
					lpFileName += ".cpp";
				}


				//lpDirectory = "C:\\Users\\����\\Desktop\\";

				
				//-------------�ж��ļ��Ƿ��Ѿ�����-----------//
				lpIsExit = lpDirectory + lpFileName;

				if(_access(lpIsExit, 0) != -1)
				{
					//---------����RichEdit����-----------//
					((CRichEditCtrl *)CWnd::FromHandle(hWnd))->GetParent()->ShowWindow(SW_HIDE);

					CString lpMsg = "�ļ�";
					lpMsg += lpRichEditContent;
					lpMsg += "�Ѵ���!\n\r�Ƿ��滻?";
					if(IDYES == AfxMessageBox(lpMsg, MB_YESNO | MB_ICONWARNING | MB_DEFBUTTON2 | MB_TOPMOST))
					{

						//-------�½��ļ�(����)-------//
						MyNewFile(lpFileName, lpDirectory, CREATE_ALWAYS);

						//----------���ļ�---------//
						MyOpenFile(lpFileName, lpDirectory, lpDefaultProgram, nCmdShow);
					}
					else
					{
						//---------��ʾRichEdit����-----------//
						((CRichEditCtrl *)CWnd::FromHandle(hWnd))->GetParent()->ShowWindow(SW_SHOW);
					}

				}
				else
				{
					//---------����RichEdit����-----------//
					((CRichEditCtrl *)CWnd::FromHandle(hWnd))->GetParent()->ShowWindow(SW_HIDE);

					//------�½��ļ�(�Ǹ���)-------//
					MyNewFile(lpFileName, lpDirectory, CREATE_NEW);
					
					//---------���ļ�----------//
					MyOpenFile(lpFileName, lpDirectory, lpDefaultProgram, nCmdShow);
				}



				//-----------------ɾ��RichEdit�ռ�����---------------//

				((CRichEditCtrl *)CWnd::FromHandle(hWnd))->SetSel(0, -1);
				((CRichEditCtrl *)CWnd::FromHandle(hWnd))->Clear();
			}

			//--------------����RichEdit����--------------//
			
			CHARFORMAT cf;				//����CHARFORMAT����
			memset(&cf, 0, sizeof(CHARFORMAT));	//�����ڴ�
			
			((CRichEditCtrl *)CWnd::FromHandle(hWnd))->GetDefaultCharFormat(cf);	//���ȱʡ���ַ���ʽ������

			cf.dwMask = CFM_FACE | CFM_SIZE | CFM_COLOR;	//���ñ������
			cf.dwEffects = CFE_BOLD;			//���ñ��������Ч
			cf.crTextColor = RGB(255, 0, 0);		//������ɫ
			cf.yHeight  = 655;		//�����ֺ�   //�ֺŴ��� 262 ��ʧ��
			strcpy(cf.szFaceName, "Fixedsys");//�������� Terminal   Fixedsys

			((CRichEditCtrl *)CWnd::FromHandle(hWnd))->SetWordCharFormat(cf);	//���ÿؼ���ʾ����		
	
			break;
		case VK_BACK:
			lContentLength = ((CRichEditCtrl *)CWnd::FromHandle(hWnd))->GetTextLength();
			if(lContentLength != 0)
			{
				prevProc(hWnd, uMsg, wParam, lParam);
			}
			break;

		case VK_UP:
			break;
		case VK_DOWN:
			break;
		case VK_LEFT:
			break;
		case VK_RIGHT:
			break;
		case VK_ESCAPE:
			//((CRichEditCtrl *)CWnd::FromHandle(hWnd))->GetWindowText(lpRichEditContent);
			((CRichEditCtrl *)CWnd::FromHandle(hWnd))->SetSel(0, -1);
			((CRichEditCtrl *)CWnd::FromHandle(hWnd))->Clear();
			
			((CRichEditCtrl *)CWnd::FromHandle(hWnd))->GetParent()->ShowWindow(SW_HIDE);   //���ش���
			break;

		default:
			return prevProc(hWnd, uMsg, wParam, lParam);
		}
		return 1;
	}
	else if(uMsg == WM_LBUTTONDOWN)
	{
		return 1;
	}
	else if(uMsg == WM_LBUTTONDBLCLK)
	{
		return 1;
	}

	else
	{
		LRESULT rtn = prevProc(hWnd, uMsg, wParam, lParam);
		DestroyCaret();   //ɾ�����

		return rtn;
	}
	
}


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFileAssistantDlg dialog

CFileAssistantDlg::CFileAssistantDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CFileAssistantDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CFileAssistantDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDI_ICON_VC);

	m_nNumber = 2;  //Win 7 �������Σ� Win XP һ��

	m_bQuit = FALSE;
	m_bSetting = FALSE;

	szFileNameOpen[0] = '\0';
	szFileNameSave[0] = '\0';

//-------------------�򿪴�������-----------------//
	ofn.hInstance = NULL;
	ofn.hwndOwner = GetSafeHwnd();
	ofn.lStructSize = sizeof(OPENFILENAME);
	ofn.lpstrFilter = "C/C++ Files(*.c; *cpp; *h)\0*.cpp;*.c;*.h\0All Files(*.*)\0*.*\0";
	ofn.lpstrCustomFilter = NULL;
	ofn.nMaxCustFilter = 0;
	ofn.nFilterIndex = 2;
	ofn.lpstrFile = szFileNameOpen;
	ofn.nMaxFile = MAX_PATH;	
	ofn.lpstrFileTitle = NULL;
	ofn.nMaxFileTitle = 0;
	ofn.lpstrInitialDir = lpDirectory;  //"C:\\Users\\����\\Documents\\�������\\C++\\POJ";     //��ʼ·��
	ofn.lpstrTitle = "��";
	ofn.Flags = OFN_HIDEREADONLY | OFN_EXPLORER | OFN_CREATEPROMPT /*| OFN_ALLOWMULTISELECT*/;
	ofn.nFileOffset = 0;
	ofn.nFileExtension = 0;
	ofn.lpstrDefExt = "cpp";
	ofn.lCustData = 0;
	ofn.lpfnHook = NULL;
	ofn.lpTemplateName = NULL;


	//---------------���洰������------------//
	sfn.hInstance = NULL;
	sfn.hwndOwner = GetSafeHwnd();
	sfn.lStructSize = sizeof(OPENFILENAME);
	sfn.lpstrFilter = "C/C++ Files(*.c; *cpp; *h)\0*.cpp;*.c;*.h\0All Files(*.*)\0*.*\0";
	sfn.lpstrCustomFilter = NULL;
	sfn.nMaxCustFilter = 0;
	sfn.nFilterIndex = 2;
	sfn.lpstrFile = szFileNameSave;
	sfn.nMaxFile = MAX_PATH;
	sfn.lpstrFileTitle = NULL;
	sfn.nMaxFileTitle = 0;
	sfn.lpstrInitialDir = lpDirectory;  //"C:\\Users\\����\\Documents\\�������\\C++\\POJ";    //��ʼ·��
	sfn.lpstrTitle = "�½�";
	sfn.Flags = OFN_HIDEREADONLY | OFN_EXPLORER | OFN_OVERWRITEPROMPT;
	sfn.nFileOffset = 0;
	sfn.nFileExtension = 0;
	sfn.lpstrDefExt = "cpp";
	sfn.lCustData = 0;
	sfn.lpfnHook = NULL;
	sfn.lpTemplateName = NULL;



}

void CFileAssistantDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CFileAssistantDlg)
	DDX_Control(pDX, IDC_RICHEDIT_NAME, m_RichEdit);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CFileAssistantDlg, CDialog)
	//{{AFX_MSG_MAP(CFileAssistantDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_NEW, OnButtonNew)
	ON_BN_CLICKED(IDC_BUTTON_OPEN, OnButtonOpen)
	ON_WM_NCHITTEST()
	ON_MESSAGE(WM_HOTKEY, OnHotkey)
	ON_WM_DESTROY()
	ON_WM_ACTIVATE()
	ON_WM_CREATE()
	ON_MESSAGE(WM_RESETHOTKEY, OnResetHotKey)
	ON_WM_NCPAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFileAssistantDlg message handlers

BOOL CFileAssistantDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here


	//--------------ȥ��������ͼ��---------------//
	ModifyStyleEx(WS_EX_APPWINDOW, WS_EX_TOOLWINDOW);

	if(g_bIsWin7 == FALSE)
	{
		//--------------ȥ���Ի���߿�-------------//
		ModifyStyle(WS_BORDER | WS_THICKFRAME , 0, SWP_FRAMECHANGED | SWP_DRAWFRAME);
		ModifyStyleEx(WS_EX_DLGMODALFRAME, 0, SWP_FRAMECHANGED | SWP_DRAWFRAME);

		//--------------�������ڵĴ�С------------//

		int nCxScreen = GetSystemMetrics(SM_CXSCREEN);
		int nCyScreen = GetSystemMetrics(SM_CYSCREEN);

		CRect rect;
		GetClientRect(&rect);  //��ȡ����Ĵ�С

		int nWidth  = nCxScreen;
		int nHeight = rect.Height();
		
		SetWindowPos(NULL, 0, nCyScreen / 2, nWidth, nHeight, SWP_NOZORDER | SWP_SHOWWINDOW);

		GetClientRect(&rect);

		m_RichEdit.MoveWindow(&rect);
	}


	//-------------��ȡע���������Ϣ-----------//

	//------------------��ȡע���������Ϣ---------------//
	HKEY hKey;
	if(RegOpenKey(HKEY_CURRENT_USER, "Software\\VC6.0 File Assistant", &hKey) != ERROR_SUCCESS)
	{
		//----------��������----------//
		//MessageBox("RegOpenKey Fail.");

		char strValue[MAX_PATH];   

		//----------��ȡ���������·��----------//
		SHGetSpecialFolderPath(this->GetSafeHwnd(), strValue, CSIDL_DESKTOP, 0);

		lpDirectory = (char *)strValue;  //����ȫ�ֱ��� Ĭ��Ŀ¼��ֵ
		lpDirectory += '\\';
		lpDefaultProgram = "MSDEV.EXE";

	}
	else
	{
		DWORD type;
		DWORD length;
		BYTE *strValue;

		//--------------------�ؼ�IDC_DEF_FILE_POSITION------------------//
		if(RegQueryValueEx(hKey, "FilePosition", 0, &type, NULL, &length) != ERROR_SUCCESS)  //��ȡ���ݳ���
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
				lpDirectory = (char *)strValue;  //����ȫ�ֱ��� Ĭ��Ŀ¼��ֵ
				lpDirectory += '\\';
			}

			delete [] strValue;
		}


		//--------------------�ؼ�Ĭ�ϳ���------------------//
		if(RegQueryValueEx(hKey, "ProgramPosition", 0, &type, NULL, &length) != ERROR_SUCCESS)  //��ȡ���ݳ���
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
				lpDefaultProgram = (char *)strValue;  //����ȫ�ֱ��� Ĭ�ϳ����ֵ
			}

			delete [] strValue;
		}


		RegCloseKey(hKey);
	}





	//-----------���ô�������----------//
	SetWindowText("VC++6.0 File Assistant");


	//-------------��дCRichEdit���ڹ��̺���--------------//
	prevProc = (WNDPROC)SetWindowLong(GetDlgItem(IDC_RICHEDIT_NAME)->m_hWnd, GWL_WNDPROC, (LONG)NewRichEditProc);


	//------------���RichEdit�ؼ�����---------------//
	m_RichEdit.SetBackgroundColor(FALSE, RGB(0, 255, 255));


	//----------���ô�����չ���------͸������---------//
	SetWindowLong(GetSafeHwnd(), GWL_EXSTYLE, GetWindowLong(GetSafeHwnd(), GWL_EXSTYLE) | 0x80000);

	typedef BOOL (WINAPI *FSetLayeredWindowAttributes)(HWND,COLORREF,BYTE,DWORD);

	FSetLayeredWindowAttributes SetLayeredWindowAttributes ;

	HINSTANCE hInst = LoadLibrary("User32.DLL");

	SetLayeredWindowAttributes = (FSetLayeredWindowAttributes)GetProcAddress(hInst,"SetLayeredWindowAttributes");

	if (SetLayeredWindowAttributes)
	{
		SetLayeredWindowAttributes(GetSafeHwnd(),RGB(0, 255, 255),128,1);
	}
	FreeLibrary(hInst);


	//------------------����RichEdit���������-----------------------//
	m_RichEdit.LimitText(255);


	//--------------����RichEdit����--------------//
	
	CHARFORMAT cf;				//����CHARFORMAT����
	memset(&cf, 0, sizeof(CHARFORMAT));	//�����ڴ�
	
	m_RichEdit.GetDefaultCharFormat(cf);	//���ȱʡ���ַ���ʽ������

	cf.dwMask = CFM_FACE | CFM_SIZE | CFM_COLOR;	//���ñ������
	cf.dwEffects = CFE_BOLD;			//���ñ��������Ч
	cf.crTextColor = RGB(255, 0, 0);		//������ɫ
	cf.yHeight  = 655;		//�����ֺ�   //�ֺŴ��� 262 ��ʧ��
	strcpy(cf.szFaceName, "Fixedsys");//�������� Terminal   Fixedsys

	m_RichEdit.SetWordCharFormat(cf);	//���ÿؼ���ʾ����

	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CFileAssistantDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CFileAssistantDlg::OnPaint() 
{


	if(m_nNumber > 0)
	{
		ShowWindow(SW_HIDE);
		m_nNumber --;
	}

	/*
	if(g_bIsWin7 == FALSE)
	{

		//-------------�״ν����������ش���----------------//

		if(i > 0)
		{
			ShowWindow(SW_HIDE);
			i--;
		}
	}
	*/

	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);

	}
	else
	{
		CDialog::OnPaint();

		//--------���Ի��򱳾���ɫ-------//
		CRect rectClient;
		GetClientRect(&rectClient);

		CPaintDC dc(this);
		dc.FillSolidRect(rectClient, RGB(0, 255, 255));
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CFileAssistantDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CFileAssistantDlg::OnOK() 
{
	// TODO: Add extra validation here
	
	CDialog::OnOK();
}

void CFileAssistantDlg::OnCancel() 
{
	// TODO: Add extra cleanup here
	
	CDialog::OnCancel();
}

void CFileAssistantDlg::OnButtonNew() 
{
	sfn.lpstrFile[0] = '\0';

	if(GetSaveFileName(&sfn) == TRUE)
	{
		//MessageBox(sfn.lpstrFile);

		CString lpFileName = sfn.lpstrFile + sfn.nFileOffset;
		//MessageBox(lpFileName);

		sfn.lpstrFile[strlen(sfn.lpstrFile) - lpFileName.GetLength()] = '\0';
		
		CString lpDirectory = sfn.lpstrFile;
		//MessageBox(sfn.lpstrFile);

		//CString lpDefaultProgram = "MSDEV.EXE";

		int nCmdShow = SW_SHOWMAXIMIZED;


		//-------------�ж��ļ��Ƿ��Ѿ�����-----------//
		CString lpIsExit = lpDirectory + lpFileName;

		if(_access(lpIsExit, 0) != -1)
		{
			//-------�½��ļ�(����)-------//
			MyNewFile(lpFileName, lpDirectory, CREATE_ALWAYS);

			//----------���ļ�---------//
			MyOpenFile(lpFileName, lpDirectory, lpDefaultProgram, nCmdShow);
		}
		else
		{
			//------�½��ļ�(�Ǹ���)-------//
			MyNewFile(lpFileName, lpDirectory, CREATE_NEW);
			
			//---------���ļ�---------//
			MyOpenFile(lpFileName, lpDirectory, lpDefaultProgram, nCmdShow);
		}
	}	
}

void CFileAssistantDlg::OnButtonOpen() 
{
	ofn.lpstrFile[0] = '\0';

	if(GetOpenFileName(&ofn) == TRUE)
	{
		CString lpFileName = ofn.lpstrFile + ofn.nFileOffset;
		//MessageBox(lpFileName);

		ofn.lpstrFile[strlen(ofn.lpstrFile) - lpFileName.GetLength()] = '\0';
		
		CString lpDirectory = ofn.lpstrFile;
		//MessageBox(ofn.lpstrFile);

		//CString lpDefaultProgram = "MSDEV.EXE";

		int nCmdShow = SW_SHOWMAXIMIZED;


		//-------------�ж��ļ��Ƿ��Ѿ�����-----------//
		CString lpIsExit = lpDirectory + lpFileName;

		if(_access(lpIsExit, 0) != -1)   //�ļ��Ѵ���
		{
			//----------���ļ�---------//
			MyOpenFile(lpFileName, lpDirectory, lpDefaultProgram, nCmdShow);
		}
		else
		{
			//------�½��ļ�(�Ǹ���)-------//
			MyNewFile(lpFileName, lpDirectory, CREATE_NEW);
			
			//---------���ļ�----------//
			MyOpenFile(lpFileName, lpDirectory, lpDefaultProgram, nCmdShow);
		}
	
	}	
}

UINT CFileAssistantDlg::OnNcHitTest(CPoint point)
{
	//-------------���÷ǿͻ��������겶׽��Ϣ--------------//
	if(CWnd::OnNcHitTest(point) == HTTOP || CWnd::OnNcHitTest(point) == HTBOTTOM || CWnd::OnNcHitTest(point) == HTLEFT || CWnd::OnNcHitTest(point) == HTRIGHT)
	{
		return HTCLIENT;
	}
	else if(CWnd::OnNcHitTest(point) == HTTOPLEFT || CWnd::OnNcHitTest(point) == HTTOPRIGHT || CWnd::OnNcHitTest(point) == HTBOTTOMLEFT || CWnd::OnNcHitTest(point) == HTBOTTOMRIGHT)
	{
		return HTCLIENT;
	}
	else
	{
		return CWnd::OnNcHitTest(point);
	}
}

void CFileAssistantDlg::OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized)
{
	//-------------����ʧȥ��������ش���-------------//
	switch(nState)
	{
	case WA_INACTIVE:    //ʧȥ����
		ShowWindow(SW_HIDE);
		m_RichEdit.SetWindowText("");

		//--------------����RichEdit����--------------//
		
		CHARFORMAT cf;				//����CHARFORMAT����
		memset(&cf, 0, sizeof(CHARFORMAT));	//�����ڴ�
		
		m_RichEdit.GetDefaultCharFormat(cf);	//���ȱʡ���ַ���ʽ������

		cf.dwMask = CFM_FACE | CFM_SIZE | CFM_COLOR;	//���ñ������
		cf.dwEffects = CFE_BOLD;			//���ñ��������Ч
		cf.crTextColor = RGB(255, 0, 0);		//������ɫ
		cf.yHeight  = 655;		//�����ֺ�   //�ֺŴ��� 262 ��ʧ��
		strcpy(cf.szFaceName, "Fixedsys");//�������� Terminal   Fixedsys

		m_RichEdit.SetWordCharFormat(cf);	//���ÿؼ���ʾ����

		break;
	}
	CWnd::OnActivate(nState, pWndOther, bMinimized);
}


LRESULT CFileAssistantDlg::OnHotkey(WPARAM wParam, LPARAM lParam)
{
	switch(wParam)
	{
	case g_nAtomFirst:

		//-----------���RichEdit�ؼ�����--------//
		m_RichEdit.SetSel(0, -1);
		m_RichEdit.Clear();

		//ShowWindow(SW_SHOW);
		ShowWindow(SW_SHOWNORMAL);
		
		SetForegroundWindow();
		
		m_RichEdit.SetFocus();

		break;
	
	case g_nAtomSecond:
		//-----------���RichEdit�ؼ�����--------//
		m_RichEdit.SetSel(0, -1);
		m_RichEdit.Clear();

		ShowWindow(SW_HIDE);
		
		OnButtonNew();
		break;

	case g_nAtomThird:
		//-----------���RichEdit�ؼ�����--------//
		m_RichEdit.SetSel(0, -1);
		m_RichEdit.Clear();

		ShowWindow(SW_HIDE);
		
		OnButtonOpen();
		break;

	case g_nAtomFouth:
		ShowWindow(SW_SHOW);
		SetForegroundWindow();
		
		
		if(m_bQuit == FALSE)
		{
			m_bQuit = TRUE;

			if(IDYES == MessageBox("ȷ���˳�?", "��ʾ", MB_YESNO | MB_ICONQUESTION))
			{
				DestroyWindow();
			}

			m_bQuit = FALSE;

		}
		break;

	case g_nAtomFifth:
	
		if(m_bSetting == FALSE)
		{
			m_bSetting = TRUE;
		 	m_pSettingDialog= new CSettingDialog;
			m_pSettingDialog->m_pMyDlg = this;   //�������ڶ��ε�ָ�봫�ݸ����ö˵Ĵ���
			m_pSettingDialog->Create(IDD_MY_DIALOG, GetDesktopWindow());
			m_pSettingDialog->ShowWindow(SW_SHOWNORMAL);
			m_pSettingDialog->SetForegroundWindow();
		}
		else if(m_bSetting == TRUE)
		{
			m_pSettingDialog->SetForegroundWindow();
		}

		break;
	}
		

	return 0;
}

void CFileAssistantDlg::OnDestroy() 
{
	CDialog::OnDestroy();
	
	//-----------�����ȼ�ע��----------//
	if(!UnregisterHotKey(m_hWnd, g_nAtomFirst) || !UnregisterHotKey(m_hWnd, g_nAtomSecond) || !UnregisterHotKey(m_hWnd, g_nAtomThird) || !UnregisterHotKey(m_hWnd, g_nAtomFouth) || !UnregisterHotKey(m_hWnd, g_nAtomFifth))
	{
		MessageBox("�����ȼ�ע��ʧ��!");
	}
	
}

int CFileAssistantDlg::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CDialog::OnCreate(lpCreateStruct) == -1)
		return -1;

	//------------��ע����ȡ������Ϣ------------//

	HKEY hKey;

	WORD wFastNew;
	WORD wNew;
	WORD wOpen;

	if(RegOpenKey(HKEY_CURRENT_USER, "Software\\VC6.0 File Assistant" ,&hKey) != ERROR_SUCCESS)
	{
		//MessageBox("RegOpenKey Fail.");
		
		wFastNew = 'M';
		wNew     = 'N';
		wOpen    = 'O';

	}
	else
	{	DWORD type;
		DWORD length;
		DWORD dwValue_VK_FAST_NEW;
		DWORD dwValue_VK_NEW;
		DWORD dwValue_VK_OPEN;


		//----------------FAST_NEW------------------//
		if(RegQueryValueEx(hKey, "VK_FAST_NEW", 0, &type, NULL, &length) != ERROR_SUCCESS)  //��ֵ������
		{
			wFastNew = 'M';
		}
		else
		{
			if(RegQueryValueEx(hKey, "VK_FAST_NEW", 0, &type, (LPBYTE)&dwValue_VK_FAST_NEW, &length) != ERROR_SUCCESS)
			{
				MessageBox("RegQueryValueEx2 Fail.");
			}
			else
			{

				wFastNew = (WORD)dwValue_VK_FAST_NEW;
			}
		}


		//------------------NEW------------------//
		if(RegQueryValueEx(hKey, "VK_NEW", 0, &type, NULL, &length) != ERROR_SUCCESS)  //��ֵ������
		{
			wNew = 'N';
		}
		else
		{
			if(RegQueryValueEx(hKey, "VK_NEW", 0, &type, (LPBYTE)&dwValue_VK_NEW, &length) != ERROR_SUCCESS)
			{
				MessageBox("RegQueryValueEx2 Fail.");
			}
			else
			{

				wNew = (WORD)dwValue_VK_NEW;
			}
		}

		//------------------OPEN------------------//
		if(RegQueryValueEx(hKey, "VK_OPEN", 0, &type, NULL, &length) != ERROR_SUCCESS)  //��ֵ������
		{
			wOpen = 'O';
		}
		else
		{
			if(RegQueryValueEx(hKey, "VK_OPEN", 0, &type, (LPBYTE)&dwValue_VK_OPEN, &length) != ERROR_SUCCESS)
			{
				MessageBox("RegQueryValueEx2 Fail.");
			}
			else
			{

				wOpen = (WORD)dwValue_VK_OPEN;
			}
		}

		RegCloseKey(hKey);
	}	

	//-------------���������ڵľ��---------//
	g_hWnd = GetSafeHwnd();
	

	//-------------ע���ȼ�-------------//
	if(!RegisterHotKey(m_hWnd, g_nAtomFirst, MOD_WIN | MOD_ALT, wFastNew))
	{
		MessageBox("�ȼ�1001ע��ʧ��!");
		return -1;
	}
	if(!RegisterHotKey(m_hWnd, g_nAtomSecond, MOD_WIN | MOD_ALT, wNew))
	{
		MessageBox("�ȼ�1002ע��ʧ��!");
		return -1;
	}
	if(!RegisterHotKey(m_hWnd, g_nAtomThird, MOD_WIN | MOD_ALT, wOpen))
	{
		MessageBox("�ȼ�1003ע��ʧ��!");
		return -1;
	}
	if(!RegisterHotKey(m_hWnd, g_nAtomFouth, MOD_WIN | MOD_ALT, 'Q'))
	{
		MessageBox("�ȼ�1004ע��ʧ��!");
		return -1;
	}
	if(!RegisterHotKey(m_hWnd, g_nAtomFifth, MOD_WIN | MOD_ALT, 'S'))
	{
		MessageBox("�ȼ�1005ע��ʧ��!");
		return -1;
	}	
	return 0;
}

void CFileAssistantDlg::OnResetHotKey(WPARAM wParam, LPARAM lParam)
{
	int nID = (int)wParam;
	WORD wVK = (WORD)lParam;

	if(!UnregisterHotKey(GetSafeHwnd(), nID))
	{
		MessageBox("UnregisterHotKey Failed.");

		return ;
	}

	if(!RegisterHotKey(GetSafeHwnd(), nID, MOD_WIN | MOD_ALT, wVK))
	{
		MessageBox("RegisterHotKey Failed.");

		return ;
	}

}

void CFileAssistantDlg::OnNcPaint()
{
	CDialog::OnNcPaint();
}
