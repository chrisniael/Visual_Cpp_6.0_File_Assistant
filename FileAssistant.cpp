// FileAssistant.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "FileAssistant.h"
#include "FileAssistantDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//---------------快捷键的注册-----------//
#define g_nAtomFirst  1001
#define g_nAtomSecond 1002
#define g_nAtomThird  1003
#define	g_nAtomFouth  1004
#define g_nAtomFifth  1005

/////////////////////////////////////////////////////////////////////////////
// CFileAssistantApp

BEGIN_MESSAGE_MAP(CFileAssistantApp, CWinApp)
	//{{AFX_MSG_MAP(CFileAssistantApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFileAssistantApp construction

CFileAssistantApp::CFileAssistantApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CFileAssistantApp object

CFileAssistantApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CFileAssistantApp initialization

//------------判断操作系统版本-------------//
BOOL g_bIsWin7;

BOOL CFileAssistantApp::InitInstance()
{
	AfxEnableControlContainer();

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif

	//------------保证当前程序只有一个实例运行----------//
	HANDLE hMutex = CreateMutex(NULL, TRUE, "VC++6.0 File Assistant");

	if(hMutex)
	{
		if(GetLastError() == ERROR_ALREADY_EXISTS)
		{
			ReleaseMutex(hMutex);

			HWND hWnd = ::FindWindow(NULL, "VC++6.0 File Assistant");

			if(hWnd == INVALID_HANDLE_VALUE)
			{
				AfxMessageBox("FindWindow Failed.");
				return FALSE;
			}

			::PostMessage(hWnd, WM_HOTKEY, g_nAtomFifth, 0);
			
			//::ShowWindow(hWnd, SW_SHOW);
			//::SetForegroundWindow(hWnd);

			return FALSE;
		}
	}


	OSVERSIONINFOEX osvi;
	BOOL bOsVersionInfoEx;
	
	ZeroMemory(&osvi, sizeof(OSVERSIONINFOEX));
	osvi.dwOSVersionInfoSize = sizeof(OSVERSIONINFOEX);
	bOsVersionInfoEx = GetVersionEx((OSVERSIONINFO*) &osvi);
	if(VER_PLATFORM_WIN32_NT == osvi.dwPlatformId && osvi.dwMajorVersion >= 6)
	{
		//MessageBox("Win7操作系统.");
		g_bIsWin7 = TRUE;
	}
	else
	{
		//MessageBox("不是Win7操作系统.");
		g_bIsWin7 = FALSE;
	}



	//HMODULE hModule = LoadLibrary("RICHED20.DLL");

	AfxInitRichEdit();  //初始化RichEdit控件

	//FreeLibrary(hModule);


	CFileAssistantDlg dlg;
	m_pMainWnd = &dlg;
	int nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{	
		// TODO: Place code here to handle when the dialog is
		//  dismissed with OK
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with Cancel
	}

	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.
	return FALSE;
}
