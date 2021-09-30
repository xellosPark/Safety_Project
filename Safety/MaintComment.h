#pragma once
#include "afxwin.h"


// MaintComment ��ȭ �����Դϴ�.

class CMaintComment : public CDialog
{
	DECLARE_DYNAMIC(CMaintComment )

public:
	CMaintComment (CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CMaintComment ();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_MAINT_COMMENT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	CStringW m_strComment;
	CStringW m_strHour;
	CStringW m_strWorker;
	CStringW m_strChecker;

	CEdit m_EditComment;
	CEdit m_EditHour;
	CEdit m_EditWorker;
	CEdit m_EditChecker;

	afx_msg void OnBnClickedButtonOk();
	afx_msg void OnBnClickedButtonCancel();
	virtual BOOL OnInitDialog();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	BOOL INIFilePaser(CStringW Comment, CStringW Hour, CStringW Worker, CStringW Checker);
	CFont m_font;
	CFont m_font2;
};
