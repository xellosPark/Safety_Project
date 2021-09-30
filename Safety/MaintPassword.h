#pragma once


// MaintPassword 대화 상자입니다.

class CMaintPassword : public CDialog
{
	DECLARE_DYNAMIC(CMaintPassword)

public:
	CMaintPassword(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CMaintPassword();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_MAINT_PASSWORD };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	CString m_strPassword;
	BOOL m_bPassword;
	afx_msg void OnBnClickedButtonOk();
};
