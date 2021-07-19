
// Safety.cpp : ���� ���α׷��� ���� Ŭ���� ������ �����մϴ�.
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
// CSafetyApp ����

CSafetyApp::CSafetyApp()
{
	// TODO: ���⿡ ���� �ڵ带 �߰��մϴ�.
	// InitInstance�� ��� �߿��� �ʱ�ȭ �۾��� ��ġ�մϴ�.
}


// ������ CSafetyApp ��ü�Դϴ�.

CSafetyApp theApp;


// CSafetyApp �ʱ�ȭ

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
		// TODO: ���⿡ [Ȯ��]�� Ŭ���Ͽ� ��ȭ ���ڰ� ������ �� ó����
		//  �ڵ带 ��ġ�մϴ�.
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: ���⿡ [���]�� Ŭ���Ͽ� ��ȭ ���ڰ� ������ �� ó����
		//  �ڵ带 ��ġ�մϴ�.
	}

	// ��ȭ ���ڰ� �������Ƿ� ���� ���α׷��� �޽��� ������ �������� �ʰ�  ���� ���α׷��� ���� �� �ֵ��� FALSE��
	// ��ȯ�մϴ�.
	return FALSE;
}

int CSafetyApp::ExitInstance()
{
	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.
	::GdiplusShutdown(gdiplusToken);
	return CWinAppEx::ExitInstance();
}
