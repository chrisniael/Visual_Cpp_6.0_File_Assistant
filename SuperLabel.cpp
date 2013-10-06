// SuperLabel.cpp : implementation file
//

#include "stdafx.h"
#include "FileAssistant.h"
#include "SuperLabel.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSuperLabel

CSuperLabel::CSuperLabel()
{
}

CSuperLabel::~CSuperLabel()
{
}


BEGIN_MESSAGE_MAP(CSuperLabel, CStatic)
	//{{AFX_MSG_MAP(CSuperLabel)
	ON_WM_PAINT()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDOWN()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSuperLabel message handlers

void CSuperLabel::PreSubclassWindow() 
{
	// TODO: Add your specialized code here and/or call the base class
	GetWindowText(m_ConnectStr);
	CFont* pFont = GetFont();

	pFont->GetLogFont(&lfont);
	lfont.lfUnderline =TRUE;
	m_Font.CreateFontIndirect(&lfont);
	
	CStatic::PreSubclassWindow();
}

void CSuperLabel::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	CDC* pDC = GetDC();

	CString text;
	GetWindowText(text);
	
	if (m_ConnectStr.IsEmpty())
		m_ConnectStr = text;

	pDC->SetBkMode(TRANSPARENT);
	pDC->SetTextColor(RGB(0,0,255));


	pDC->SelectObject(&m_Font);
	pDC->TextOut(0,0,text);
	// TODO: Add your message handler code here
	
	// Do not call CStatic::OnPaint() for painting messages
}

void CSuperLabel::OnMouseMove(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	::SetCursor(AfxGetApp()->LoadCursor(IDC_CURSOR_HAND));
	CStatic::OnMouseMove(nFlags, point);
}

void CSuperLabel::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	ShellExecute(m_hWnd,NULL,m_ConnectStr,NULL,NULL,SW_SHOW);			
	CStatic::OnLButtonDown(nFlags, point);
}
