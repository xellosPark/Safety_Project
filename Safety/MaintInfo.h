#pragma once
#include "afxwin.h"


// MaintInfo ��ȭ �����Դϴ�.

class CMaintInfo : public CDialog
{
	DECLARE_DYNAMIC(CMaintInfo)

public:
	CMaintInfo(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CMaintInfo();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_MAINT_INFOMATION };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonOk();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual BOOL OnInitDialog();

	BOOL INIFilePaser(CStringW Name, CStringW Number, CStringW Time, CStringW Info, CStringW strPassword, CStringW strStartTime);
	BOOL INIFilePaser(CStringW m_strName, CStringW m_strNumber, CStringW m_strPassword,CStringW strStartTime);
	CEdit m_editName;
	CEdit m_editNumber;
	CEdit m_editTime;
	CEdit m_editInfo;
	CEdit m_editPassword;
	CEdit m_editPassword2;

	
	CStringW m_strName;
	CStringW m_strNumber;
	CStringW m_strTime;
	CStringW m_strInfo;
	CStringW m_strPassword;
	CStringW m_strPassword2;

	CFont m_font;
	CFont m_font2;

	CWinApp *pApp;

	afx_msg void OnBnClickedCheckPassword();
	afx_msg void OnBnClickedButtonCancel();
	CButton m_checkPassword;
	BOOL m_bPassword;
};
