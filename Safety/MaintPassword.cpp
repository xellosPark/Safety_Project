// MaintPassword.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "Safety.h"
#include "MaintPassword.h"


// MaintPassword ��ȭ �����Դϴ�.

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


// CMaintPassword �޽��� ó�����Դϴ�.

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
		AfxMessageBox(L"��й�ȣ�� Ʋ���ϴ�.\n��ا���ҡ�");
	}
}
