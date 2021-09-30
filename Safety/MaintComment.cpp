// MaintComment.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "Safety.h"
#include "MaintComment.h"
#include "IniFile.h"
#include "FileOperations.h"


// MaintComment 대화 상자입니다.

IMPLEMENT_DYNAMIC(CMaintComment , CDialog)

CMaintComment ::CMaintComment (CWnd* pParent /*=NULL*/)
	: CDialog(CMaintComment ::IDD, pParent)
{
	m_font.CreateFont( 17, // nHeight 
		0, // nWidth 
		0, // nEscapement 
		0, // nOrientation 
		FW_BOLD, // nWeight 
		0, // bItalic 
		0, // bUnderline 
		0, // cStrikeOut 
		0, // nCharSet 
		OUT_DEFAULT_PRECIS, // nOutPrecision 
		0,                              // nClipPrecision 
		DEFAULT_QUALITY,       // nQuality
		DEFAULT_PITCH | FF_DONTCARE,  // nPitchAndFamily 
		_T("굴림")); // lpszFacename 

	m_font2.CreateFont( 15, // nHeight 
		0, // nWidth 
		0, // nEscapement 
		0, // nOrientation 
		0,//FW_BOLD, // nWeight 
		0, // bItalic 
		0, // bUnderline 
		0, // cStrikeOut 
		0, // nCharSet 
		OUT_DEFAULT_PRECIS, // nOutPrecision 
		0,                              // nClipPrecision 
		DEFAULT_QUALITY,       // nQuality
		DEFAULT_PITCH | FF_DONTCARE,  // nPitchAndFamily 
		_T("굴림")); // lpszFacename 
}

CMaintComment ::~CMaintComment ()
{
}

void CMaintComment ::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_MAINT_COMMENT, m_EditComment);
	DDX_Control(pDX, IDC_EDIT_MAINT_HOUR, m_EditHour);
	DDX_Control(pDX, IDC_EDIT_MAINT_WORKER, m_EditWorker);
	DDX_Control(pDX, IDC_EDIT_MAINT_CHECKER, m_EditChecker);
}


BEGIN_MESSAGE_MAP(CMaintComment , CDialog)
	ON_BN_CLICKED(IDC_BUTTON_OK, &CMaintComment ::OnBnClickedButtonOk)
	ON_BN_CLICKED(IDC_BUTTON_CANCEL, &CMaintComment ::OnBnClickedButtonCancel)
END_MESSAGE_MAP()


// MaintComment 메시지 처리기입니다.
BOOL CMaintComment::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_strComment.Empty();
	m_strHour.Empty();
	m_strWorker.Empty();
	m_strChecker.Empty();

	GetDlgItem(IDC_STATIC_MAINT_COMMENT)->SetFont(&m_font);
	GetDlgItem(IDC_STATIC_MAINT_WORK_HOUR)->SetFont(&m_font);
	GetDlgItem(IDC_STATIC_MAINT_WORKER)->SetFont(&m_font);
	GetDlgItem(IDC_STATIC_MAINT_CHECKER)->SetFont(&m_font);

	char str[200];
	CStringW strComment("");
	TCHAR tzReturn[32767] ={0,}; 
	DWORD dwSize = ::GetPrivateProfileSection( _T( "MaintComment" ), tzReturn, 32767, MAINT_PATH ); 
	if ( dwSize !=0)
	{
		for( int iLoop = 0; iLoop < dwSize - 1; iLoop++ ) 
		{ 
			if( _T( '\0' ) == tzReturn[iLoop] ) 
				tzReturn[iLoop] = _T( '\n' ); 
		} 
		if( 0 != dwSize ) 
		{ 
			CString sRead;
			sRead.Format( _T( "%s" ), tzReturn );
			int iLine = 0; CString sLine;
			while( ::AfxExtractSubString( sLine, sRead, iLine++, _T( '\n' ) ) )
			{
				int iTab = 0; CString sTab; int iIndex = 1;
				while( ::AfxExtractSubString( sTab, sLine, iTab++, _T( '\t' ) ) )
				{ 
					CStringW strTemp;
					strTemp.Format(L"%s\r\n",sTab);
					strComment += strTemp;
				} 
			} 
		}
	}

	strComment.Delete(0,8);
	//GetPrivateProfileString(_T("MaintInfo"), _T("Contact"), _T(""),(LPWSTR)str,200,MAINT_PATH);
	m_EditComment.SetFont(&m_font2);
	m_EditComment.SetWindowText((LPCTSTR)strComment);

	GetPrivateProfileString(_T("MaintInfo"), _T("Hour"), _T(""),(LPWSTR)str,200,MAINT_PATH);
	m_EditHour.SetFont(&m_font2);
	m_EditHour.SetWindowText((LPCTSTR)str);	

	GetPrivateProfileString(_T("MaintInfo"), _T("Worker"), _T(""),(LPWSTR)str,200,MAINT_PATH);
	m_EditWorker.SetFont(&m_font2);
	m_EditWorker.SetWindowText((LPCTSTR)str);

	GetPrivateProfileString(_T("MaintInfo"), _T("Checker"), _T(""),(LPWSTR)str,200,MAINT_PATH);
	m_EditChecker.SetFont(&m_font2);
	m_EditChecker.SetWindowText((LPCTSTR)str);


	return TRUE;

}
void CMaintComment ::OnBnClickedButtonOk()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	m_EditComment.GetWindowText(m_strComment);
	m_EditHour.GetWindowText(m_strHour);
	m_EditChecker.GetWindowText(m_strChecker);
	m_EditWorker.GetWindowText(m_strWorker);

	//	if(INIFilePaser(m_strName, m_strNumber, m_strTime, m_strInfo, m_strPassword, strStartTime) == FALSE)
	if(INIFilePaser(m_strComment, m_strHour, m_strWorker, m_strChecker) == FALSE)
	{
		AfxMessageBox(_T("D:\\Safety\\Maint File Not find."));
		return;
	}


	return OnOK();
}

void CMaintComment ::OnBnClickedButtonCancel()
{
	OnCancel();
}

BOOL CMaintComment ::INIFilePaser(CStringW Comment, CStringW Hour, CStringW Worker, CString Checker)
{
	CFileFind fFinder;
	//CFile File;
	FILE* File=NULL;
	CFileException	e;
	CString strPath("");
	strPath.Format(EQP_PATH);
	//////////////////////////////////////////////////////////////////////////	

	if(!fFinder.FindFile( MAINT_PATH,0))
	{
		//MakeFullDir(sFilePath);			// 20181023 ubslhi - Maint Control
		// 		if(!File.Open(szINIFileName, CFile::modeCreate | CFile::modeWrite , &e))		
		// 			return FALSE;

		if ((File = _wfopen(MAINT_PATH,L"wt+,ccs=UTF-16LE")) == NULL) // C4996
		{
			CFileFind fFinder;
			if (!fFinder.FindFile(strPath,0))
			{
				CFileOperation file;
				file.MakeFullDir(strPath);
			}
			if(!_wfopen(MAINT_PATH,L"wt+,ccs=UTF-16LE"))
			{
				return false;
			}
		}

		//File.Close();
		fclose(File);
	}
	WritePrivateProfileString(_T("MaintComment"),NULL,NULL,MAINT_PATH);
	WritePrivateProfileString(_T("MaintComment"),_T("Comment"),Comment,MAINT_PATH);
	WritePrivateProfileString(_T("MaintInfo"),_T("Hour"),Hour,MAINT_PATH);
	WritePrivateProfileString(_T("MaintInfo"),_T("Worker"),Worker,MAINT_PATH);
	WritePrivateProfileString(_T("MaintInfo"),_T("Checker"),Checker,MAINT_PATH);

	return TRUE;
}

BOOL CMaintComment::PreTranslateMessage(MSG* pMsg)
{
	if(pMsg->message == WM_SYSKEYDOWN || pMsg->message == WM_KEYDOWN || pMsg->message == WM_SYSKEYUP || pMsg->message == WM_KEYUP)
	{
// 		if(pMsg->wParam == VK_RETURN)
// 			return TRUE;
	}
	return CDialog::PreTranslateMessage(pMsg);
}