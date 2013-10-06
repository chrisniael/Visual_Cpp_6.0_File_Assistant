#include "StdAfx.h"

//----------------打开文件----------------//

int MyOpenFile(CString lpFileName, CString lpDirectory, CString lpDefaultProgram, INT nCmdShow)
{

	//--------------判断目录是否有效--------------//

	if(_access(lpDirectory, 0) == -1)
	{
		return -1;
	}


	//------------判断 文件名 是否有效------------//
	
	CString lpIsExist;
	lpIsExist = lpDirectory + lpFileName;

	if(_access(lpIsExist, 0) == -1)
	{
		return -1;
	}


	//-------------打开文件--------------//

	HINSTANCE rtn = ShellExecute(NULL, "open", lpDefaultProgram, lpFileName, lpDirectory, nCmdShow);


	if((int)rtn <= 32)
	{
		if((int)rtn == ERROR_FILE_NOT_FOUND)
		{
			return -1;
		}
	}

	return 0;
}

int MyNewFile(CString lpFileName, CString lpDirectory, DWORD dwCreationDisposition)
{

	CString lpPath = lpDirectory + lpFileName;

	//DWORD dwCreationDisposition = CREATE_ALWAYS;

	HANDLE rtn = CreateFile(lpPath, GENERIC_READ | GENERIC_WRITE, 0, NULL, dwCreationDisposition, FILE_ATTRIBUTE_NORMAL, NULL);

	if(dwCreationDisposition == CREATE_NEW)
	{
		if(rtn == INVALID_HANDLE_VALUE)
		{
			CloseHandle(rtn);
			return -1;
		}
		else
		{
			CloseHandle(rtn);
			return 0;
		}
		
	}
	else
	{
		if(rtn == INVALID_HANDLE_VALUE)
		{
			CloseHandle(rtn);
			return -1;
		}
		else
		{
			CloseHandle(rtn);
			return 0;
		}
	}
}

/*
int main()
{

	char szFileName[255];
	cin >> szFileName;

	CString lpFileName = szFileName;

	char szDirectory[255] = "C:\\Users\\沈煜\\Desktop\\";
	CString lpDirectory = szDirectory;

	char szDefaultProgram[255] = "MSDEV.EXE";
	CString lpDefaultProgram = szDefaultProgram;

	INT nCmdShow = SW_SHOWMAXIMIZED;


	//-------------判断文件是否已经存在-----------//
	CString lpIsExit = lpDirectory + lpFileName;
	if(_access(lpIsExit, 0) != -1)
	{
		cout << "文件已存在!" << endl;

		cout << lpFileName << "已存在。" << endl;
		cout << "是否替换它(Y/N)? " << endl;

		char szChoice[20];

		cin >> szChoice;

		if(strcmp(szChoice, "Y") == 0)
		{
			//-------新建文件(覆盖)-------//
			CreateFile(lpFileName, lpDirectory, CREATE_ALWAYS);

			//----------打开文件---------//
			OpenFile(lpFileName, lpDirectory, lpDefaultProgram, nCmdShow);
		}
		else
		{
			cout << "请重新选择文件!" << endl;
		}

	}
	else
	{
		//------新建文件(非覆盖)-------//
		CreateFile(lpFileName, lpDirectory, CREATE_NEW);
		
		//---------打开文件----------//
		OpenFile(lpFileName, lpDirectory, lpDefaultProgram, nCmdShow);
	}


	return 0;
}
*/