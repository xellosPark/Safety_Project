// DlgTitleBoard.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "Safety.h"
#include "DlgTitleBoard.h"


// CDlgTitleBoard

IMPLEMENT_DYNCREATE(CDlgTitleBoard, CFormView)

CDlgTitleBoard::CDlgTitleBoard()
	: CFormView(CDlgTitleBoard::IDD)
{

}

CDlgTitleBoard::~CDlgTitleBoard()
{
}

void CDlgTitleBoard::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CDlgTitleBoard, CFormView)
END_MESSAGE_MAP()


// CDlgTitleBoard �����Դϴ�.

#ifdef _DEBUG
void CDlgTitleBoard::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CDlgTitleBoard::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CDlgTitleBoard �޽��� ó�����Դϴ�.
// DlgTitleBoard.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "Safety.h"
#include "DlgTitleBoard.h"


// CDlgTitleBoard ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(CDlgTitleBoard, CDialog)

CDlgTitleBoard::CDlgTitleBoard(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgTitleBoard::IDD, pParent)
{

}

CDlgTitleBoard::~CDlgTitleBoard()
{
}

void CDlgTitleBoard::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDlgTitleBoard, CDialog)
END_MESSAGE_MAP()


// CDlgTitleBoard �޽��� ó�����Դϴ�.
