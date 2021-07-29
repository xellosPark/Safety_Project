#pragma once



// CDlgTitleBoard 폼 뷰입니다.

class CDlgTitleBoard : public CFormView
{
	DECLARE_DYNCREATE(CDlgTitleBoard)

protected:
	CDlgTitleBoard();           // 동적 만들기에 사용되는 protected 생성자입니다.
	virtual ~CDlgTitleBoard();

public:
	enum { IDD = IDD_DLG_TITLE_BOARD };
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
};


#pragma once


// CDlgTitleBoard 대화 상자입니다.

class CDlgTitleBoard : public CDialog
{
	DECLARE_DYNAMIC(CDlgTitleBoard)

public:
	CDlgTitleBoard(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CDlgTitleBoard();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_DIALOG_TEXT_BOARD };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
};
