#pragma once


// MaintPassword ��ȭ �����Դϴ�.

class CMaintPassword : public CDialog
{
	DECLARE_DYNAMIC(CMaintPassword)

public:
	CMaintPassword(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CMaintPassword();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_MAINT_PASSWORD };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	CString m_strPassword;
	BOOL m_bPassword;
	afx_msg void OnBnClickedButtonOk();
};
