#pragma once

#ifdef _WIN32_WCE
#error "Windows CE������ CDHtmlDialog�� �������� �ʽ��ϴ�."
#endif 

// CDlgSafetyView ��ȭ �����Դϴ�.

class CDlgSafetyView : public CDialogEx
{
	DECLARE_DYNCREATE(CDlgSafetyView)

public:
	CDlgSafetyView(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CDlgSafetyView();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_DLG_SAFETY};

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.
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
