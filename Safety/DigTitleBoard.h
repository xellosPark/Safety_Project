#pragma once

class CIniFile;
// CDigTitleBoard 대화 상자입니다.

class CDigTitleBoard : public CDialog
{
	DECLARE_DYNAMIC(CDigTitleBoard)

public:
	CDigTitleBoard(int nInDex = 0,CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CDigTitleBoard();

// 대화 상자 데이터입니다. 
	enum { IDD = IDD_DLG_TITLE_BOARD };
 
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

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
