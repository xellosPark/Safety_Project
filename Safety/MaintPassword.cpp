// MaintPassword.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "Safety.h"
#include "MaintPassword.h"


// MaintPassword 대화 상자입니다.

IMPLEMENT_DYNAMIC(CMaintPassword, CDialog)

CMaintPassword::CMaintPassword(CWnd* pParent /*=NULL*/)
	: CDialog(CMaintPassword::IDD, pParent)
	, m_strPassword(_T(""))
	, m_bPassword(FALSE)
{

}

CMaintPassword::~CMaintPassword()
{
}

void CMaintPassword::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_MAINT_INFO_PASSWORD, m_strPassword);
}


BEGIN_MESSAGE_MAP(CMaintPassword, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_OK, &CMaintPassword::OnBnClickedButtonOk)
END_MESSAGE_MAP()


// CMaintPassword 메시지 처리기입니다.

void CMaintPassword::OnBnClickedButtonOk()
{

	CString strPassword(_T(""));

	char str[200];
	GetPrivateProfileString(_T("MaintInfo"), _T("Password"), _T(""),(LPWSTR)str,200,MAINT_PATH);
	strPassword.Format(_T("%s"),str);

	GetDlgItemText(IDC_EDIT_MAINT_INFO_PASSWORD,m_strPassword);

	if(m_strPassword == strPassword)
	{
		//return TRUE;
		m_bPassword = TRUE;
		CDialog::OnOK();
	}
	else
	{
		AfxMessageBox(L"비밀번호가 틀립니다.\n密碼不同。");
	}
}
