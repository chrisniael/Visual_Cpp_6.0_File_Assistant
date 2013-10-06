#include "StdAfx.h"

//----------------���ļ�----------------//

int MyOpenFile(CString lpFileName, CString lpDirectory, CString lpDefaultProgram, INT nCmdShow)
{

	//--------------�ж�Ŀ¼�Ƿ���Ч--------------//

	if(_access(lpDirectory, 0) == -1)
	{
		return -1;
	}


	//------------�ж� �ļ��� �Ƿ���Ч------------//
	
	CString lpIsExist;
	lpIsExist = lpDirectory + lpFileName;

	if(_access(lpIsExist, 0) == -1)
	{
		return -1;
	}


	//-------------���ļ�--------------//

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

	char szDirectory[255] = "C:\\Users\\����\\Desktop\\";
	CString lpDirectory = szDirectory;

	char szDefaultProgram[255] = "MSDEV.EXE";
	CString lpDefaultProgram = szDefaultProgram;

	INT nCmdShow = SW_SHOWMAXIMIZED;


	//-------------�ж��ļ��Ƿ��Ѿ�����-----------//
	CString lpIsExit = lpDirectory + lpFileName;
	if(_access(lpIsExit, 0) != -1)
	{
		cout << "�ļ��Ѵ���!" << endl;

		cout << lpFileName << "�Ѵ��ڡ�" << endl;
		cout << "�Ƿ��滻��(Y/N)? " << endl;

		char szChoice[20];

		cin >> szChoice;

		if(strcmp(szChoice, "Y") == 0)
		{
			//-------�½��ļ�(����)-------//
			CreateFile(lpFileName, lpDirectory, CREATE_ALWAYS);

			//----------���ļ�---------//
			OpenFile(lpFileName, lpDirectory, lpDefaultProgram, nCmdShow);
		}
		else
		{
			cout << "������ѡ���ļ�!" << endl;
		}

	}
	else
	{
		//------�½��ļ�(�Ǹ���)-------//
		CreateFile(lpFileName, lpDirectory, CREATE_NEW);
		
		//---------���ļ�----------//
		OpenFile(lpFileName, lpDirectory, lpDefaultProgram, nCmdShow);
	}


	return 0;
}
*/