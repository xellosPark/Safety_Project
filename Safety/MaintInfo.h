#pragma once
#include "afxwin.h"


// MaintInfo 대화 상자입니다.

class CMaintInfo : public CDialog
{
	DECLARE_DYNAMIC(CMaintInfo)

public:
	CMaintInfo(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CMaintInfo();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_MAINT_INFOMATION };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

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
