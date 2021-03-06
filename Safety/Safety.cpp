
// Safety.cpp : 응용 프로그램에 대한 클래스 동작을 정의합니다.
//

#include "stdafx.h"
#include "Safety.h"
#include "DlgSafetyView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CSafetyApp

BEGIN_MESSAGE_MAP(CSafetyApp, CWinAppEx)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()

ULONG_PTR gdiplusToken;
// CSafetyApp 생성

CSafetyApp::CSafetyApp()
{
	// TODO: 여기에 생성 코드를 추가합니다.
	// InitInstance에 모든 중요한 초기화 작업을 배치합니다.
}


// 유일한 CSafetyApp 개체입니다.

CSafetyApp theApp;


// CSafetyApp 초기화

BOOL CSafetyApp::InitInstance()
{

	CWinAppEx::InitInstance();

	GdiplusStartupInput gdiplusStartupInput;
	if(::GdiplusStartup(&gdiplusToken,&gdiplusStartupInput,NULL) != Ok)
	{
		AfxMessageBox(_T("ERROR: Failed to initialize GDI+ library!"), MB_TOPMOST);
		return FALSE;
	}

	CDlgSafetyView dlg;
	m_pMainWnd = &dlg;
	dlg.DoModal();
	
	return FALSE;
}

int CSafetyApp::ExitInstance()
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	::GdiplusShutdown(gdiplusToken);
	return CWinAppEx::ExitInstance();
}
