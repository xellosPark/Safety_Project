#pragma once

class CIniFile;
// CDigTitleBoard ��ȭ �����Դϴ�.

class CDigTitleBoard : public CDialog
{
	DECLARE_DYNAMIC(CDigTitleBoard)

public:
	CDigTitleBoard(int nInDex = 0,CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CDigTitleBoard();

// ��ȭ ���� �������Դϴ�. 
	enum { IDD = IDD_DLG_TITLE_BOARD };
 
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	BOOL SafetyDataLOAD(int nKey);
	BOOL SafetyDataSave(int nKey,CString strKr,CString strCn);
	char* StringToChar(CString str);
	virtual BOOL OnInitDialog();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);

public:
	CIniFile* m_pIniRecipe;
	int m_nIndex;

	CFont m_font14;

	
	afx_msg void OnBnClickedCancel();
};
