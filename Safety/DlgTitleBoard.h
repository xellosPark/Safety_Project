#pragma once



// CDlgTitleBoard �� ���Դϴ�.

class CDlgTitleBoard : public CFormView
{
	DECLARE_DYNCREATE(CDlgTitleBoard)

protected:
	CDlgTitleBoard();           // ���� ����⿡ ���Ǵ� protected �������Դϴ�.
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
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
};


#pragma once


// CDlgTitleBoard ��ȭ �����Դϴ�.

class CDlgTitleBoard : public CDialog
{
	DECLARE_DYNAMIC(CDlgTitleBoard)

public:
	CDlgTitleBoard(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CDlgTitleBoard();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_DIALOG_TEXT_BOARD };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
};
