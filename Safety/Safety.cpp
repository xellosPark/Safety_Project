
// Safety.cpp : 응용 프로그램에 대한 클래스 동작을 정의합니다.
//

#include "stdafx.h"
#include "Safety.h"
#include "SafetyDlg.h"

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


	CSafetyDlg dlg;
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: 여기에 [확인]을 클릭하여 대화 상자가 없어질 때 처리할
		//  코드를 배치합니다.
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: 여기에 [취소]를 클릭하여 대화 상자가 없어질 때 처리할
		//  코드를 배치합니다.
	}

	// 대화 상자가 닫혔으므로 응용 프로그램의 메시지 펌프를 시작하지 않고  응용 프로그램을 끝낼 수 있도록 FALSE를
	// 반환합니다.
	return FALSE;
}

int CSafetyApp::ExitInstance()
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	::GdiplusShutdown(gdiplusToken);
	return CWinAppEx::ExitInstance();
}
