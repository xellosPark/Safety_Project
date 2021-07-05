#pragma once

#ifdef _WIN32_WCE
#error "Windows CE에서는 CDHtmlDialog가 지원되지 않습니다."
#endif 

// CDlgSafetyView 대화 상자입니다.

class CDlgSafetyView : public CDialogEx
{
	DECLARE_DYNCREATE(CDlgSafetyView)

public:
	CDlgSafetyView(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CDlgSafetyView();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_DLG_SAFETY};

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnPaint();
	BOOL SetMainImageLoad();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);

public:
	CRect rcCheckLoad[10];
};
