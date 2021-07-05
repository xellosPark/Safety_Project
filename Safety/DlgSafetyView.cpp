// DlgSafetyView.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "Safety.h"
#include "DlgSafetyView.h"
#include <atlimage.h>


// CDlgSafetyView ��ȭ �����Դϴ�.

IMPLEMENT_DYNCREATE(CDlgSafetyView, CDialogEx)

CDlgSafetyView::CDlgSafetyView(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgSafetyView::IDD, pParent)
{

}

CDlgSafetyView::~CDlgSafetyView()
{
}

void CDlgSafetyView::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BOOL CDlgSafetyView::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	MoveWindow(0,0,1920,1080);

	BOOL bok = TRUE; 
	bok = SetMainImageLoad();
	if (bok == FALSE)
	{
		AfxMessageBox("Main Image Load �����ϼ̽��ϴ�.");
	}


	return TRUE;  // ��Ŀ���� ��Ʈ�ѿ� �������� ������ TRUE�� ��ȯ�մϴ�.
}

BEGIN_MESSAGE_MAP(CDlgSafetyView, CDialogEx)
	ON_BN_CLICKED(IDOK, &CDlgSafetyView::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CDlgSafetyView::OnBnClickedCancel)
	ON_WM_PAINT()
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()

void CDlgSafetyView::OnBnClickedOk()
{
	CDialogEx::OnOK();
}

void CDlgSafetyView::OnBnClickedCancel()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
}

void CDlgSafetyView::OnPaint()
{
	CPaintDC dc(this); // device context for painting
// 	CDC MemDC;
// 	CBitmap * pOldBmp;
// 	CBitmap Bitmap;
// 	CBitmap bg;
// 
// 	bg.LoadBitmap(IDB_LOGIN);
// 
// 	CRect rect;
// 	GetClientRect(&rect);
// 
// 	MemDC.CreateCompatibleDC(pDC);
// 
// 	Bitmap.CreateCompatibleBitmap(pDC,rect.Width(),rect.Height());
// 	pOldBmp = (CBitmap *)MemDC.SelectObject(&bg);
// 	pDC->BitBlt(0,0,rect.Width(),rect.Height(),&MemDC,0,0,SRCCOPY);
// 
// 	MemDC.SelectObject(pOldBmp);
// 	MemDC.DeleteDC();
// 
// 	this->ReleaseDC(pDC);

// 	int nWidth = GetSystemMetrics(SM_CXSCREEN);
// 	int nHeight = GetSystemMetrics(SM_CYSCREEN);
// 	
// 	HDC hDC = GetDC()->m_hDC; // �������� HDC�� ���� ��������� �ػ󵵵� ������ �� ���� 
// 	int nWidth2 = GetDeviceCaps(hDC, HORZRES); 
// 	int nHeight2 = GetDeviceCaps(hDC, VERTRES);


	CImage cImage;
	HRESULT hr = cImage.Load("./res/BG_CHECKBOX_ALL_END_WITE.jpg");
	if(FAILED(hr))
	{
		AfxMessageBox(_T("Error : Invalid file"));
		return ;	
	}

	cImage.Draw( dc.m_hDC, 0, 0, 1920, 1080, 0, 0, 1920, 1080 );
	//this->Invalidate(0);
	//cImage.Draw( dc.m_hDC, 0, 0, 1920, 1080, 0, 0, 1920, 1080 );
	
}

BOOL CDlgSafetyView::SetMainImageLoad()
{
	CClientDC dc(this); // �׸��⸦ ���� ����̽� ���ؽ�Ʈ�Դϴ�.

	CImage cImage;
	HRESULT hr = cImage.Load("./res/BG_CHECKBOX_ALL_END_WITE.jpg");
	if(FAILED(hr))
	{
		AfxMessageBox(_T("Error : Invalid file"));
		return FALSE;
	}

	cImage.Draw( dc.m_hDC, 0, 0, 1920, 1080, 0, 0, 1920, 1080 );
	return TRUE;

}

void CDlgSafetyView::OnLButtonDown(UINT nFlags, CPoint point)
{
	////////////////////////////////////////////////////
	////////////// ���� ��ġ �Ѱ��ֱ� tset///////////
	//	CString satrtp = _T("");
	//	satrtp.Format(_T("%d %d"),point.x,point.y);
	//	AfxMessageBox(_T(satrtp),MB_TOPMOST);
	
	
	

	CDialogEx::OnLButtonDown(nFlags, point);
}
