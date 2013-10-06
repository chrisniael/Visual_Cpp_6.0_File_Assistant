; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CAboutDialog
LastTemplate=CStatic
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "FileAssistant.h"

ClassCount=8
Class1=CFileAssistantApp
Class2=CFileAssistantDlg
Class3=CAboutDlg

ResourceCount=7
Resource1=IDD_ABOUTBOX
Resource2=IDR_MAINFRAME
Resource3=IDD_FILEASSISTANT_DIALOG
Resource4=IDD_DIALOG_ITEM0
Resource5=IDD_MY_DIALOG
Resource6=IDD_DIALOG_ABOUT
Class4=CSettingDialog
Class5=CAboutDialog
Class6=CDialogItem0
Class7=CDialogItem1
Class8=CSuperLabel
Resource7=IDD_DIALOG_ITEM1

[CLS:CFileAssistantApp]
Type=0
HeaderFile=FileAssistant.h
ImplementationFile=FileAssistant.cpp
Filter=N

[CLS:CFileAssistantDlg]
Type=0
HeaderFile=FileAssistantDlg.h
ImplementationFile=FileAssistantDlg.cpp
Filter=D
BaseClass=CDialog
VirtualFilter=dWC
LastObject=CFileAssistantDlg

[CLS:CAboutDlg]
Type=0
HeaderFile=FileAssistantDlg.h
ImplementationFile=FileAssistantDlg.cpp
Filter=D

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[DLG:IDD_FILEASSISTANT_DIALOG]
Type=1
Class=CFileAssistantDlg
ControlCount=3
Control1=IDC_RICHEDIT_NAME,RICHEDIT,1342242949
Control2=IDC_BUTTON_NEW,button,1208025088
Control3=IDC_BUTTON_OPEN,button,1208025088

[DLG:IDD_MY_DIALOG]
Type=1
Class=CSettingDialog
ControlCount=1
Control1=IDC_TAB_CTRL,SysTabControl32,1342177280

[DLG:IDD_DIALOG_ITEM0]
Type=1
Class=CDialogItem0
ControlCount=11
Control1=IDC_STATIC,static,1342308352
Control2=IDC_EDIT_DEF_FILE_POSITION,edit,1350633600
Control3=IDC_BUTTON_CHOICE_DEF_FILE_POSTION,button,1342242816
Control4=IDC_STATIC,static,1342308352
Control5=IDC_RADIO_VC,button,1342177289
Control6=IDC_RADIO_HAND,button,1342177289
Control7=IDC_EDIT_DEF_PROGRAM_POSITION,edit,1350633600
Control8=IDC_BUTTON_CHOICE_DEF_PROGRAM_POSITION,button,1342242816
Control9=IDOK,button,1342242816
Control10=IDCANCEL,button,1342242816
Control11=IDC_BUTTON_APPLY,button,1342242817

[DLG:IDD_DIALOG_ABOUT]
Type=1
Class=CAboutDialog
ControlCount=10
Control1=IDC_STATIC,static,1342308352
Control2=IDC_STATIC,static,1342308352
Control3=IDC_STATIC,static,1342308352
Control4=IDC_STATIC,static,1342308352
Control5=IDC_STATIC,static,1342308352
Control6=IDC_STATIC,static,1342308352
Control7=IDC_STATIC,static,1342177283
Control8=IDC_STATIC,static,1342308480
Control9=IDC_CONNECT,static,1342308608
Control10=IDOK,button,1342242817

[CLS:CSettingDialog]
Type=0
HeaderFile=SettingDialog.h
ImplementationFile=SettingDialog.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=CSettingDialog

[CLS:CAboutDialog]
Type=0
HeaderFile=AboutDialog.h
ImplementationFile=AboutDialog.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=IDC_CONNECT

[CLS:CDialogItem0]
Type=0
HeaderFile=DialogItem0.h
ImplementationFile=DialogItem0.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=IDC_EDIT_DEF_PROGRAM_POSITION

[CLS:CDialogItem1]
Type=0
HeaderFile=DialogItem1.h
ImplementationFile=DialogItem1.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=CDialogItem1

[DLG:IDD_DIALOG_ITEM1]
Type=1
Class=CDialogItem1
ControlCount=13
Control1=IDC_CHECK_AUTORUN,button,1342242819
Control2=IDC_CHECK_USE_FAST_NEW,button,1342242819
Control3=IDC_STATIC,static,1342308352
Control4=IDC_HOTKEY1,msctls_hotkey32,1350631424
Control5=IDC_CHECK_USE_NEW,button,1342242819
Control6=IDC_STATIC,static,1342308352
Control7=IDC_HOTKEY2,msctls_hotkey32,1350631424
Control8=IDC_CHECK_USE_OPEN,button,1342242819
Control9=IDC_STATIC,static,1342308352
Control10=IDC_HOTKEY3,msctls_hotkey32,1350631424
Control11=IDOK,button,1342242816
Control12=IDCANCEL,button,1342242816
Control13=IDC_BUTTON_APPLY,button,1342242817

[CLS:CSuperLabel]
Type=0
HeaderFile=SuperLabel.h
ImplementationFile=SuperLabel.cpp
BaseClass=CStatic
Filter=W
VirtualFilter=WC

