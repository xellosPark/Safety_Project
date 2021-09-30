#pragma once
#include "afxwin.h"


// MaintComment 대화 상자입니다.

class CMaintComment : public CDialog
{
	DECLARE_DYNAMIC(CMaintComment )

public:
	CMaintComment (CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CMaintComment ();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_MAINT_COMMENT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

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
