// DlgSafetyView.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "Safety.h"
#include "DlgSafetyView.h"
#include <atlimage.h>


// CDlgSafetyView 대화 상자입니다.

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

BEGIN_MESSAGE_MAP(CDlgSafetyView, CDialogEx)
	ON_BN_CLICKED(IDOK, &CDlgSafetyView::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CDlgSafetyView::OnBnClickedCancel)
	ON_WM_PAINT()
	ON_WM_LBUTTONDOWN()
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()

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
	// 	HDC hDC = GetDC()->m_hDC; // 가져오는 HDC에 따라 듀얼모니터의 해상도도 가져올 수 있음 
	// 	int nWidth2 = GetDeviceCaps(hDC, HORZRES); 
	// 	int nHeight2 = GetDeviceCaps(hDC, VERTRES);


	// 	CImage cImage;
	// 	HRESULT hr = cImage.Load("./res/BG_CHECKBOX_ALL_END_WITE.jpg");
	// 	if(FAILED(hr))
	// 	{
	// 		AfxMessageBox(_T("Error : Invalid file"));
	// 		return ;	
	// 	}
	// 
	// 	cImage.Draw( dc.m_hDC, 0, 0, 1920, 1080, 0, 0, 1920, 1080 );
	//this->Invalidate(0);
	//cImage.Draw( dc.m_hDC, 0, 0, 1920, 1080, 0, 0, 1920, 1080 );

	SetMainImageLoad();

}

BOOL CDlgSafetyView::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	MoveWindow(0,0,1920,1080);
	m_mapDataInfo.clear();


 	_SAFETY_DATA DataInfo[TYPE_TITLE_MAX]; //16
	//1
 	DataInfo[0].m_rtPos1.SetRect(505,105,538,142);
	DataInfo[0].m_rtPos2.SetRect(547,105,580,142);
	DataInfo[0].m_rtPosBG.SetRect(23,100,490,150);
	DataInfo[0].m_state = 0;
	DataInfo[0].m_strKRTitle = "한국어1";
	DataInfo[0].m_strCNTitle = "test1";
	//2
	DataInfo[1].m_rtPos1.SetRect(505,160,538,195);
	DataInfo[1].m_rtPos2.SetRect(547,160,580,195);
	DataInfo[1].m_rtPosBG.SetRect(23,155,490,205);
	DataInfo[1].m_state = 0;
	DataInfo[1].m_strKRTitle = "한국어2";
	DataInfo[1].m_strCNTitle = "test1";
	//3
	DataInfo[2].m_rtPos1.SetRect(505,215,538,252);
	DataInfo[2].m_rtPos2.SetRect(547,215,580,252);
	DataInfo[2].m_rtPosBG.SetRect(23,209,490,259);
	DataInfo[2].m_state = 0;
	DataInfo[2].m_strKRTitle = "한국어3";
	DataInfo[2].m_strCNTitle = "test3";
	//4
	DataInfo[3].m_rtPos1.SetRect(505,270,538,308);
	DataInfo[3].m_rtPos2.SetRect(547,270,580,308);
	DataInfo[3].m_rtPosBG.SetRect(23,264,490,314);
	DataInfo[3].m_state = 0;
	DataInfo[3].m_strKRTitle = "한국어4";
	DataInfo[3].m_strCNTitle = "test4";
	//5
	DataInfo[4].m_rtPos1.SetRect(505,323,538,360);
	DataInfo[4].m_rtPos2.SetRect(547,323,580,360);
	DataInfo[4].m_rtPosBG.SetRect(23,318,490,368);
	DataInfo[4].m_state = 0;
	DataInfo[4].m_strKRTitle = "한국어5";
	DataInfo[4].m_strCNTitle = "test5";
	//6
	DataInfo[5].m_rtPos1.SetRect(505,367,538,412);
	DataInfo[5].m_rtPos2.SetRect(547,367,580,412);
	DataInfo[5].m_rtPosBG.SetRect(23,374,490,429);
	DataInfo[5].m_state = 0;
	DataInfo[5].m_strKRTitle = "한국어6";
	DataInfo[5].m_strCNTitle = "test6";
	//7
	DataInfo[6].m_rtPos1.SetRect(505,434,538,469);
	DataInfo[6].m_rtPos2.SetRect(547,434,580,469);
	DataInfo[6].m_rtPosBG.SetRect(23,428,490,483);
	DataInfo[6].m_state = 0;
	DataInfo[6].m_strKRTitle = "한국어7";
	DataInfo[6].m_strCNTitle = "test7";
	//8
	DataInfo[7].m_rtPos1.SetRect(505,488,538,524);
	DataInfo[7].m_rtPos2.SetRect(547,488,580,524);
	DataInfo[7].m_rtPosBG.SetRect(23,482,490,532);
	DataInfo[7].m_state = 0;
	DataInfo[7].m_strKRTitle = "한국어8";
	DataInfo[7].m_strCNTitle = "test8";
	//9
	DataInfo[8].m_rtPos1.SetRect(505,542,538,580);
	DataInfo[8].m_rtPos2.SetRect(547,542,580,580);
	DataInfo[8].m_rtPosBG.SetRect(23,536,490,586);
	DataInfo[8].m_state = 0;
	DataInfo[8].m_strKRTitle = "한국어9";
	DataInfo[8].m_strCNTitle = "test9";
	//10
	DataInfo[9].m_rtPos1.SetRect(505,598,538,633);
	DataInfo[9].m_rtPos2.SetRect(547,598,580,633);
	DataInfo[9].m_rtPosBG.SetRect(23,591,490,641);
	DataInfo[9].m_state = 0;
	DataInfo[9].m_strKRTitle = "한국어10";
	DataInfo[9].m_strCNTitle = "test10";
	//11
	DataInfo[10].m_rtPos1.SetRect(505,653,538,688);
	DataInfo[10].m_rtPos2.SetRect(547,653,580,688);
	DataInfo[10].m_rtPosBG.SetRect(23,647,490,697);
	DataInfo[10].m_state = 0;
	DataInfo[10].m_strKRTitle = "한국어11";
	DataInfo[10].m_strCNTitle = "test11";
	//12
	DataInfo[11].m_rtPos1.SetRect(505,707,538,742);
	DataInfo[11].m_rtPos2.SetRect(547,707,580,742);
	DataInfo[11].m_rtPosBG.SetRect(23,702,490,754);
	DataInfo[11].m_state = 0;
	DataInfo[11].m_strKRTitle = "한국어12";
	DataInfo[11].m_strCNTitle = "test12";
	//13
	DataInfo[12].m_rtPos1.SetRect(505,761,538,797);
	DataInfo[12].m_rtPos2.SetRect(547,761,580,797);
	DataInfo[12].m_rtPosBG.SetRect(23,756,490,806);
	DataInfo[12].m_state = 0;
	DataInfo[12].m_strKRTitle = "한국어13";
	DataInfo[12].m_strCNTitle = "test13";
	//14
	DataInfo[13].m_rtPos1.SetRect(505,816,538,852);
	DataInfo[13].m_rtPos2.SetRect(547,816,580,852);
	DataInfo[13].m_rtPosBG.SetRect(23,811,490,861);
	DataInfo[13].m_state = 0;
	DataInfo[13].m_strKRTitle = "한국어14";
	DataInfo[13].m_strCNTitle = "test14";
	//15
	DataInfo[14].m_rtPos1.SetRect(505,871,538,907);
	DataInfo[14].m_rtPos2.SetRect(547,871,580,907);
	DataInfo[14].m_rtPosBG.SetRect(23,865,490,915);
	DataInfo[14].m_state = 0;
	DataInfo[14].m_strKRTitle = "한국어15";
	DataInfo[14].m_strCNTitle = "test15";
	//16
	DataInfo[15].m_rtPos1.SetRect(505,925,538,963);
	DataInfo[15].m_rtPos2.SetRect(547,925,580,963);
	DataInfo[15].m_rtPosBG.SetRect(23,920,490,970);
	DataInfo[15].m_state = 0;
	DataInfo[15].m_strKRTitle = "한국어16";
	DataInfo[15].m_strCNTitle = "test16";

 	int nCount(0);
	for (int i = 0; i <TYPE_TITLE_MAX ; i++)
	{
		AddMapDataInfo(i,DataInfo[i]);	
		for (int j = 0; j < 2; j++)
		{
			
			if ( j == 0 )
			{
				m_ctrTex[i][j].Create(_T("(작업자추가)"), WS_CHILD | WS_VISIBLE,CRect(10, 10, 20, 20), this,IDC_STATIC_TITLE_1 + nCount);
				Sleep(5);
				m_ctrTex[i][j].MoveWindow( DataInfo[i].m_rtPosBG.left + 15, DataInfo[i].m_rtPosBG.top + 5,
					DataInfo[i].m_rtPosBG.right, DataInfo[i].m_rtPosBG.top + 25, TRUE );	
			}
			else
			{
				m_ctrTex[i][j].Create(_T("追加点检者"), WS_CHILD | WS_VISIBLE,CRect(10, 10, 20, 20), this,IDC_STATIC_TITLE_1 + nCount);
				Sleep(5);
				m_ctrTex[i][j].MoveWindow(DataInfo[i].m_rtPosBG.left + 15,DataInfo[i].m_rtPosBG.top + 25,
					DataInfo[i].m_rtPosBG.right,DataInfo[i].m_rtPosBG.top + 50,TRUE);
			}
		}

		nCount++;
	}

	BOOL bok = TRUE; 
	bok = SetMainImageLoad();
	if (bok == FALSE)
	{
		AfxMessageBox("Main Image Load 실패하셨습니다.");
	}
	

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}




BOOL CDlgSafetyView::SetMainImageLoad()
{
	CClientDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

	
	CDC * pDC = GetDC();	
	CDC MemDC;
	CRect rect;

	GetClientRect(&rect);
	MemDC.CreateCompatibleDC(pDC);

	CImage cImageSelect;
	CImage cImageBG;
	HRESULT hr = cImageBG.Load("./res/BG_CHECKBOX_ALL_END_WHITE.jpg");
	if(FAILED(hr))
	{
		AfxMessageBox(_T("Error : BG_IMGAE Invalid file"));
		return FALSE;
	}
	cImageBG.Draw( pDC->m_hDC, 0, 0, 1920, 1080, 0, 0, 1920, 1080 );

 	hr = cImageSelect.Load("./res/BG_CHECKBOX_ALL_END_SELECT.jpg");
 	if(FAILED(hr))
 	{
 		AfxMessageBox(_T("Error :SELECT_IMAGE Invalid file"));
 		return FALSE;
 	}
	
	map<int, _SAFETY_DATA>::iterator it;
	for( it = m_mapDataInfo.begin(); it != m_mapDataInfo.end(); ++it)
	{
		_SAFETY_DATA Data;
		Data = it->second;

		if (Data.m_state == SELECT_ON)
		{
			cImageSelect.Draw( pDC->m_hDC, Data.m_rtPosBG.left, Data.m_rtPosBG.top, Data.m_rtPosBG.right-Data.m_rtPosBG.left,Data.m_rtPosBG.bottom-Data.m_rtPosBG.top,
				Data.m_rtPosBG.left, Data.m_rtPosBG.top, Data.m_rtPosBG.right-Data.m_rtPosBG.left,Data.m_rtPosBG.bottom-Data.m_rtPosBG.top);

			cImageSelect.Draw( pDC->m_hDC, Data.m_rtPos1.left, Data.m_rtPos1.top, Data.m_rtPos1.right-Data.m_rtPos1.left,Data.m_rtPos1.bottom-Data.m_rtPos1.top,
				Data.m_rtPos1.left, Data.m_rtPos1.top, Data.m_rtPos1.right-Data.m_rtPos1.left,Data.m_rtPos1.bottom-Data.m_rtPos1.top);
		}
		else if (Data.m_state == SELECT_OFF)
		{
			cImageSelect.Draw( pDC->m_hDC, Data.m_rtPos2.left, Data.m_rtPos2.top, Data.m_rtPos2.right-Data.m_rtPos2.left,Data.m_rtPos2.bottom-Data.m_rtPos2.top,
				Data.m_rtPos2.left, Data.m_rtPos2.top, Data.m_rtPos2.right-Data.m_rtPos2.left,Data.m_rtPos2.bottom-Data.m_rtPos2.top);
		}	
	}

	
 	


	MemDC.DeleteDC();
	this->ReleaseDC(pDC);	//2014/27/10 PDJ- 메모리 해제
	return TRUE;

}

// BOOL CDlgSafetyView::SetMainTextLoad()
// {
// 	
// 	return TRUE;
// 
// }

void CDlgSafetyView::AddMapDataInfo(int nKey,const CDlgSafetyView::_SAFETY_DATA& DataInfo)
{
	m_mapDataInfo[nKey] = DataInfo;
}

void CDlgSafetyView::OnLButtonDown(UINT nFlags, CPoint point)
{
	////////////////////////////////////////////////////
	////////////// 현재 위치 넘겨주기 tset///////////
	CString satrtp = _T("");
	satrtp.Format(_T("%d %d"),point.x,point.y);
	SetDlgItemText(IDC_STATIC_MOUSE_POS,satrtp);
	
	map<int, _SAFETY_DATA>::iterator it;

	int nCount = m_mapDataInfo.size();
	for( it = m_mapDataInfo.begin(); it != m_mapDataInfo.end(); ++it)
	{
		if (CheckExistItem(it->first) == FALSE)
		{
			break;
		}

		_SAFETY_DATA Data;
		Data = it->second;
		if (Data.m_rtPos1.PtInRect(point))
		{
			SetItemsStateValue(it->first,SELECT_ON);
			this->Invalidate(0);
			break;
		}
		else if (Data.m_rtPos2.PtInRect(point))
		{
			SetItemsStateValue(it->first,SELECT_OFF);
			this->Invalidate(0);
			break;
		}

	}
	//this->Invalidate(0);
	
	CDialogEx::OnLButtonDown(nFlags, point);
}

void CDlgSafetyView::GetItemsValue( int order, CDlgSafetyView::_SAFETY_DATA& Data )
{
	map<int, _SAFETY_DATA>::iterator  it = m_mapDataInfo.find(order);
	if ( it != m_mapDataInfo.end())
	{
		Data = it->second;
	}
}

void CDlgSafetyView::GetItemsStateValue(int order, int& nvalue)
{
	map<int, _SAFETY_DATA>::iterator  it = m_mapDataInfo.find(order);
	if ( it != m_mapDataInfo.end())
	{
		nvalue = it->second.m_state;
	}
}

BOOL CDlgSafetyView::SetItemsValue(int order, int nState, CString strKRText, CString strCNText)
{
	if (CheckExistItem(order) == FALSE)
	{
		return FALSE;
	}
	if (nState != -1)
	{
		m_mapDataInfo[order].m_state = nState;
	}

	if (strKRText != "" || strKRText.IsEmpty() == FALSE )
	{
		m_mapDataInfo[order].m_strKRTitle = strKRText;
	}

	if (strCNText != "" || strCNText.IsEmpty() == FALSE )
	{
		m_mapDataInfo[order].m_strCNTitle = strCNText;
	}


	return TRUE;
}

BOOL CDlgSafetyView::SetItemsStateValue(int order, int nState)
{
	if (CheckExistItem(order) == FALSE)
	{
		return FALSE;
	}
	if (nState != -1)
	{
		m_mapDataInfo[order].m_state = nState;
	}
	return TRUE;
}

BOOL CDlgSafetyView::CheckExistItem(int nKey)
{
	if ((int)m_mapDataInfo.count(nKey) <= 0)
	{
		return FALSE;
	}

	return TRUE;
}

void CDlgSafetyView::OnBnClickedOk()
{
	CDialogEx::OnOK();
}

void CDlgSafetyView::OnBnClickedCancel()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}

HBRUSH CDlgSafetyView::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	if (nCtlColor == CTLCOLOR_STATIC)
	{
		pDC->SetBkMode(TRANSPARENT);
		hbr = (HBRUSH)GetStockObject(NULL_BRUSH);;
	}
	return hbr;
}
