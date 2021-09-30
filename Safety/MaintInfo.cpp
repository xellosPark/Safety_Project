// MaintInfo.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "Safety.h"
#include "MaintInfo.h"
#include "IniFile.h"
#include "FileOperations.h"


// MaintInfo 대화 상자입니다.

IMPLEMENT_DYNAMIC(CMaintInfo, CDialog)



CMaintInfo::CMaintInfo(CWnd* pParent /*=NULL*/)
	: CDialog(CMaintInfo::IDD, pParent)
	, m_bPassword(false)
{

	m_font.CreateFont( 19, // nHeight 
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

	m_font2.CreateFont( 19, // nHeight 
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

// 	 pApp = AfxGetApp();	
// 
// 	 HKEY hKey;
// 	 const char* pszPath = "Software\\REPAIR\\MacMic";
// 	 if(ERROR_SUCCESS == ::RegOpenKeyEx(HKEY_CURRENT_USER,(LPCWSTR)pszPath,0,
// 		 KEY_QUERY_VALUE,&hKey))
// 	 {
// 		 ::RegCloseKey(hKey);
// 	 }

}

CMaintInfo::~CMaintInfo()
{
}

void CMaintInfo::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_NAME, m_editName);
	DDX_Control(pDX, IDC_EDIT_NUMBER, m_editNumber);
	DDX_Control(pDX, IDC_EDIT_TIME, m_editTime);
	DDX_Control(pDX, IDC_EDIT_INFO, m_editInfo);
	DDX_Control(pDX, IDC_EDIT_INFO_PASSWORD, m_editPassword);
	DDX_Control(pDX, IDC_EDIT_INFO_PASSWORD2, m_editPassword2);
	DDX_Control(pDX, IDC_CHECK_PASSWORD, m_checkPassword);
}


BEGIN_MESSAGE_MAP(CMaintInfo, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_OK, &CMaintInfo::OnBnClickedButtonOk)
	ON_BN_CLICKED(IDC_CHECK_PASSWORD, &CMaintInfo::OnBnClickedCheckPassword)
	ON_BN_CLICKED(IDC_BUTTON_CANCEL, &CMaintInfo::OnBnClickedButtonCancel)
END_MESSAGE_MAP()


// MaintInfo 메시지 처리기입니다.
void CMaintInfo::OnBnClickedButtonOk()
{

	m_editName.GetWindowText(m_strName);
	m_editNumber.GetWindowText(m_strNumber);
	m_editTime.GetWindowText(m_strTime);
	m_editInfo.GetWindowText(m_strInfo);
	m_editPassword.GetWindowText(m_strPassword);
	m_editPassword2.GetWindowText(m_strPassword2);
	m_strPassword.MakeLower();

	if(m_strPassword.IsEmpty())
	{
		AfxMessageBox(L"비밀번호가 비어있습니다.\n請輸入密碼");
		return;
	}

	if(m_strPassword.GetLength() < 6)
	{
		AfxMessageBox(L"비밀번호는 6자리 이상 입력해야 합니다.\n請輸入6位以上密碼");
		return;
	}

	if(m_strPassword != m_strPassword2)
	{
		AfxMessageBox(L"비밀번호가 틀립니다.\n密碼不同。");
		return;
	}

	if(m_strName.IsEmpty())
	{
		AfxMessageBox(L"이름이 비어있습니다.\n請輸入名字。");
		return;
	}
	if(m_strNumber.IsEmpty())
	{
		AfxMessageBox(L"전화번호가 비어있습니다.\n請輸入電話號碼");
		return;
	}

	SYSTEMTIME localTime;
	::GetLocalTime(&localTime);

	CString strCurDate,strCurTime, strStartTime;
	strCurDate.Format(_T("%04d-%02d-%02d"),localTime.wYear,localTime.wMonth,localTime.wDay);
	strCurTime.Format(_T("%02d:%02d:%02d"), localTime.wHour, localTime.wMinute, localTime.wSecond);
	strStartTime.Format(_T("%s %s"),strCurDate,strCurTime);

//	if(INIFilePaser(m_strName, m_strNumber, m_strTime, m_strInfo, m_strPassword, strStartTime) == FALSE)
	if(INIFilePaser(m_strName, m_strNumber, m_strPassword, strStartTime) == FALSE)
	{
		AfxMessageBox(_T("D:\\Safety\\Maint File을 찾을 수 없습니다."));
		return;
	}


	CRegKey RegKey;
	RegKey.Create(HKEY_CURRENT_USER,_T("SOFTWARE\\REPAIR\\MacMic\\REPAIR")); 
	RegKey.SetValue(_T("1"), _T("SCREEN_SAVER_INFO"));

// 	RegKey.Create(HKEY_CURRENT_USER,_T("SOFTWARE\\REPAIR\\MacMic\\REPAIR")); 
// 	RegKey.SetValue(strTemp, _T("SCREEN_SAVER_START_TIME"));

	RegKey.Close();
	//pApp->WriteProfileInt(_T("REPAIR"),_T("SCREEN_SAVER_INFO"),1);



	return OnOK();
}

BOOL CMaintInfo::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_strName.Empty();
	m_strNumber.Empty();
	m_strTime.Empty();
	m_strInfo.Empty();
	

	GetDlgItem(IDC_STATIC_PHONENO)->SetFont(&m_font);
	GetDlgItem(IDC_STATIC_CONTACT_NAME)->SetFont(&m_font);
	GetDlgItem(IDC_CHECK_PASSWORD)->SetFont(&m_font);
	GetDlgItem(IDC_STATIC_REPASSWORD)->SetFont(&m_font);
	char str[200];
	GetPrivateProfileString(_T("MaintInfo"), _T("Contact"), _T(""),(LPWSTR)str,200,MAINT_PATH);
	m_editName.SetFont(&m_font);
	m_editName.SetWindowText((LPCTSTR)str);
	GetPrivateProfileString(_T("MaintInfo"), _T("Phone"), _T(""),(LPWSTR)str,200,MAINT_PATH);
	m_editNumber.SetFont(&m_font);
	m_editNumber.SetWindowText((LPCTSTR)str);
	m_editPassword.SetFont(&m_font);
	m_editPassword2.SetFont(&m_font);


	//pApp->SetRegistryKey(_T("MacMic"));

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}
//BOOL CMaintInfo::INIFilePaser(CStringW Name, CStringW Number, CStringW Time, CStringW Info, CStringW strPassword, CStringW strStartTime)
BOOL CMaintInfo::INIFilePaser(CStringW Name, CStringW Number, CStringW strPassword, CStringW strStartTime)
{
	CFileFind fFinder;
	//CFile File;
	FILE* File=NULL;
	CFileException	e;
	CString strPath("");
	strPath.Format(EQP_PATH);


	//////////////////////////////////////////////////////////////////////////	

	if(!fFinder.FindFile(MAINT_PATH,0))
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

	WritePrivateProfileString(_T("MaintInfo"),_T("Contact"),Name,MAINT_PATH);
	WritePrivateProfileString(_T("MaintInfo"),_T("Phone"),Number,MAINT_PATH);
	WritePrivateProfileString(_T("MaintInfo"),_T("Maint_MODE"),_T("1"),MAINT_PATH);
	WritePrivateProfileString(_T("MaintInfo"),_T("Password"),strPassword,MAINT_PATH);	
	WritePrivateProfileString(_T("MaintInfo"),_T("StartTime"),strStartTime,MAINT_PATH);

	return TRUE;

	// 
	// 	CINIRecipe INI(sFilePath);
	// 
	// 	INI.GetValue("MaintInfo", "Name", Name);
	// 	INI.GetValue("MaintInfo", "Number", Number);
	// 	INI.GetValue("MaintInfo", "작업시간", Time);
	// 	INI.GetValue("MaintInfo", "작업내용", Info);
}

BOOL CMaintInfo::PreTranslateMessage(MSG* pMsg)
{
	if(pMsg->wParam == VK_RETURN || pMsg->wParam == VK_ESCAPE) 
		OnBnClickedButtonOk();

	if(WM_SYSKEYDOWN == pMsg->message && pMsg->wParam == VK_F4)
		return TRUE;

	return CDialog::PreTranslateMessage(pMsg);
}


void CMaintInfo::OnBnClickedCheckPassword()
{
	const static TCHAR cPasswordChar = m_editPassword.GetPasswordChar();
	const static TCHAR cPasswordChar2 = m_editPassword2.GetPasswordChar();
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	m_bPassword = m_checkPassword.GetCheck();

	if(m_bPassword)
	{
		m_editPassword.SetPasswordChar(NULL);
		m_editPassword2.SetPasswordChar(NULL);
	}
	else
	{
		m_editPassword.SetPasswordChar(cPasswordChar);
		m_editPassword2.SetPasswordChar(cPasswordChar2);
	}
	Invalidate();
}

void CMaintInfo::OnBnClickedButtonCancel()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	OnCancel();
}
