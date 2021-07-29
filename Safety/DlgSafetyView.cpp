// DlgSafetyView.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "Safety.h"
#include "DlgSafetyView.h"
#include <atlimage.h>
#include "DigTitleBoard.h"

// CDlgSafetyView 대화 상자입니다.

IMPLEMENT_DYNCREATE(CDlgSafetyView, CDialogEx)

CDlgSafetyView::CDlgSafetyView(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgSafetyView::IDD, pParent)
{
	CString strRcpPath = _T("");
	strRcpPath.Format(_T("%s"),RCP_PATH);

	m_pIniRecipe = new CIniFile(strRcpPath);

	m_font;
	m_font.CreateFont( 20, // nHeight 
		0, // nWidth 
		0, // nEscapement 
		0, // nOrientation 
		0, // nWeight 
		0, // bItalic 
		0, // bUnderline 
		0, // cStrikeOut 
		0, // nCharSet 
		OUT_DEFAULT_PRECIS, // nOutPrecision 
		0,                              // nClipPrecision 
		DEFAULT_QUALITY,       // nQuality
		DEFAULT_PITCH | FF_DONTCARE,  // nPitchAndFamily 
		_T("굴림")); // lpszFacename 

}

CDlgSafetyView::~CDlgSafetyView()
{
	ClearButton();
	DeleteObject(m_font);
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
	ON_WM_ERASEBKGND()
	ON_WM_DRAWITEM()
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

	//SetMainImageLoad();
	//SetBitmaptoCBitmapLoad();
	//SetBitmaptoCBitmapView();
	SetMainImageCBitmapLoad();

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
	DataInfo[0].m_rtPosSelect.SetRect(11,100,23,150);
	DataInfo[0].m_state = 0;

	//2
	DataInfo[1].m_rtPos1.SetRect(505,160,538,195);
	DataInfo[1].m_rtPos2.SetRect(547,160,580,195);
	DataInfo[1].m_rtPosBG.SetRect(23,155,490,205);
	DataInfo[1].m_rtPosSelect.SetRect(11,155,23,205);
	DataInfo[1].m_state = 0;

	//3
	DataInfo[2].m_rtPos1.SetRect(505,215,538,252);
	DataInfo[2].m_rtPos2.SetRect(547,215,580,252);
	DataInfo[2].m_rtPosBG.SetRect(23,209,490,259);
	DataInfo[2].m_rtPosSelect.SetRect(11,209,23,259);
	DataInfo[2].m_state = 0;

	//4
	DataInfo[3].m_rtPos1.SetRect(505,270,538,308);
	DataInfo[3].m_rtPos2.SetRect(547,270,580,308);
	DataInfo[3].m_rtPosBG.SetRect(23,264,490,314);
	DataInfo[3].m_rtPosSelect.SetRect(11,264,23,314);
	DataInfo[3].m_state = 0;

	//5
	DataInfo[4].m_rtPos1.SetRect(505,323,538,360);
	DataInfo[4].m_rtPos2.SetRect(547,323,580,360);
	DataInfo[4].m_rtPosBG.SetRect(23,318,490,368);
	DataInfo[4].m_rtPosSelect.SetRect(11,318,23,368);
	DataInfo[4].m_state = 0;

	//6
	DataInfo[5].m_rtPos1.SetRect(505,367,538,412);
	DataInfo[5].m_rtPos2.SetRect(547,367,580,412);
	DataInfo[5].m_rtPosBG.SetRect(23,374,490,429);
	DataInfo[5].m_rtPosSelect.SetRect(11,374,23,429);
	DataInfo[5].m_state = 0;

	//7
	DataInfo[6].m_rtPos1.SetRect(505,434,538,469);
	DataInfo[6].m_rtPos2.SetRect(547,434,580,469);
	DataInfo[6].m_rtPosBG.SetRect(23,428,490,483);
	DataInfo[6].m_rtPosSelect.SetRect(11,428,23,483);
	DataInfo[6].m_state = 0;

	//8
	DataInfo[7].m_rtPos1.SetRect(505,488,538,524);
	DataInfo[7].m_rtPos2.SetRect(547,488,580,524);
	DataInfo[7].m_rtPosBG.SetRect(23,482,490,532);
	DataInfo[7].m_rtPosSelect.SetRect(11,482,23,532);
	DataInfo[7].m_state = 0;

	//9
	DataInfo[8].m_rtPos1.SetRect(505,542,538,580);
	DataInfo[8].m_rtPos2.SetRect(547,542,580,580);
	DataInfo[8].m_rtPosBG.SetRect(23,536,490,586);
	DataInfo[8].m_rtPosSelect.SetRect(11,536,23,586);
	DataInfo[8].m_state = 0;

	//10
	DataInfo[9].m_rtPos1.SetRect(505,598,538,633);
	DataInfo[9].m_rtPos2.SetRect(547,598,580,633);
	DataInfo[9].m_rtPosBG.SetRect(23,591,490,641);
	DataInfo[9].m_rtPosSelect.SetRect(11,591,23,641);
	DataInfo[9].m_state = 0;

	//11
	DataInfo[10].m_rtPos1.SetRect(505,653,538,688);
	DataInfo[10].m_rtPos2.SetRect(547,653,580,688);
	DataInfo[10].m_rtPosBG.SetRect(23,647,490,697);
	DataInfo[10].m_rtPosSelect.SetRect(11,647,23,697);
	DataInfo[10].m_state = 0;

	//12
	DataInfo[11].m_rtPos1.SetRect(505,707,538,742);
	DataInfo[11].m_rtPos2.SetRect(547,707,580,742);
	DataInfo[11].m_rtPosBG.SetRect(23,702,490,754);
	DataInfo[11].m_rtPosSelect.SetRect(11,702,23,754);
	DataInfo[11].m_state = 0;

	//13
	DataInfo[12].m_rtPos1.SetRect(505,761,538,797);
	DataInfo[12].m_rtPos2.SetRect(547,761,580,797);
	DataInfo[12].m_rtPosBG.SetRect(23,756,490,806);
	DataInfo[12].m_rtPosSelect.SetRect(11,756,23,806);
	DataInfo[12].m_state = 0;

	//14
	DataInfo[13].m_rtPos1.SetRect(505,816,538,852);
	DataInfo[13].m_rtPos2.SetRect(547,816,580,852);
	DataInfo[13].m_rtPosBG.SetRect(23,811,490,861);
	DataInfo[13].m_rtPosSelect.SetRect(11,811,23,861);
	DataInfo[13].m_state = 0;

	//15
	DataInfo[14].m_rtPos1.SetRect(505,871,538,907);
	DataInfo[14].m_rtPos2.SetRect(547,871,580,907);
	DataInfo[14].m_rtPosBG.SetRect(23,865,490,915);
	DataInfo[14].m_rtPosSelect.SetRect(11,865,23,915);
	DataInfo[14].m_state = 0;

	//16
	DataInfo[15].m_rtPos1.SetRect(505,925,538,963);
	DataInfo[15].m_rtPos2.SetRect(547,925,580,963);
	DataInfo[15].m_rtPosBG.SetRect(23,920,490,970);
	DataInfo[15].m_rtPosSelect.SetRect(11,920,23,970);
	DataInfo[15].m_state = 0;
	
 	int nCount(0);
	ClearButton();
	for (int i = 0; i <TYPE_TITLE_MAX ; i++)
	{
		AddMapDataInfo(i,DataInfo[i]);	
		for (int j = 0; j < TYPE_TITLE_MIN; j++)
		{
			if ( j == 0 )
			{
				m_ctrTex[i][j].Create(_T("작업자추가"), WS_CHILD | WS_VISIBLE,CRect(10, 10, 20, 20), this,IDC_STATIC_TITLE_1 + nCount);
				
				Sleep(5);
				m_ctrTex[i][j].MoveWindow( DataInfo[i].m_rtPosBG.left + 15, DataInfo[i].m_rtPosBG.top + 5,
					DataInfo[i].m_rtPosBG.right, DataInfo[i].m_rtPosBG.top + 25, TRUE );	
			}
			else
			{

 				CString strCh = _T("追加点检者");
 				m_ctrTex[i][j].Create(strCh, WS_CHILD | WS_VISIBLE,CRect(10, 10, 20, 20), this,IDC_STATIC_TITLE_1 + nCount);
				//m_ctrTex[i][j].CreateWindow("static",strCh, WS_CHILD | WS_VISIBLE,CRect(10, 10, 20, 20), this,IDC_STATIC_TITLE_1 + nCount);
			
				Sleep(5);
 				m_ctrTex[i][j].MoveWindow(DataInfo[i].m_rtPosBG.left + 15,DataInfo[i].m_rtPosBG.top + 25,
 					DataInfo[i].m_rtPosBG.right,DataInfo[i].m_rtPosBG.top + 50,TRUE);
				GetDlgItem(IDC_STATIC_TITLE_1 + nCount)->SetFont(&m_font);
				GetDlgItem(IDC_STATIC_TITLE_1 + nCount)->SetWindowText(strCh);
			}
			nCount++;
		}
		CString str(_T(""));
		str.Format(_T(">"));
		//m_ctrBnt[i].Create(str,WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,CRect(DataInfo[i].m_rtPosSelect.left,DataInfo[i].m_rtPosSelect.top,DataInfo[i].m_rtPosSelect.left + 12, DataInfo[i].m_rtPosSelect.top + 50), this,IDC_BUTTON_TITLE_1 + i);
		Sleep(10);
		CButton* createButton = new CButton;
		createButton->Create(str,WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,CRect(DataInfo[i].m_rtPosSelect.left,DataInfo[i].m_rtPosSelect.top,DataInfo[i].m_rtPosSelect.left + 12, DataInfo[i].m_rtPosSelect.top + 50), this,IDC_BUTTON_TITLE_1 + i);
		addButton(i,createButton);
		
	}

	BOOL bok = TRUE; 
	//bok = SetMainImageLoad();
	//bok = SetBitmaptoCBitmapLoad();
	//bok = SetBitmaptoCBitmapView();
	bok = SetMainImageCBitmapLoad();
	if (bok == FALSE)
	{
		AfxMessageBox(_T("Main Image Load 실패하셨습니다."));
	}

	InitBoard();
	
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
	HRESULT hr = cImageBG.Load(_T("./res/BG_CHECKBOX_ALL_END_WHITE.jpg"));
	
	if(FAILED(hr))
	{
		AfxMessageBox(_T("Error : BG_IMGAE Invalid file"));
		return FALSE;
	}
	cImageBG.Draw( pDC->m_hDC, 0, 0, 1920, 1080, 0, 0, 1920, 1080 );

 	hr = cImageSelect.Load(_T("./res/BG_CHECKBOX_ALL_END_SELECT.jpg"));
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

BOOL CDlgSafetyView::SetMainImageCBitmapLoad()
{
	CDC * pDC = GetDC();	
	CDC MemDC;
	CRect rect;

	GetClientRect(&rect);
	MemDC.CreateCompatibleDC(pDC);

	CImage cImageBG;
	HRESULT hr = cImageBG.Load(_T("./res/BG_CHECKBOX_ALL_END_WHITE.jpg"));
	if(FAILED(hr))
	{
		AfxMessageBox(_T("Error : BG_IMGAE Invalid file"));
		return FALSE;
	}

	CImage cImageSelect;
	hr = cImageSelect.Load(_T("./res/BG_CHECKBOX_ALL_END_SELECT.jpg"));
	if(FAILED(hr))
	{
		AfxMessageBox(_T("Error : SELECT_IMGAE Invalid file"));
		return FALSE;
	}
	CBitmap *cBitmapBG;
	cBitmapBG = CBitmap::FromHandle(cImageBG);

	CBitmap *cBitmapSelect;
	cBitmapSelect = CBitmap::FromHandle(cImageSelect);


	RECT r = {50,70,700,700};
	int pOldMode = MemDC.SetBkMode(TRANSPARENT);
	CFont * pOldFont = (CFont *)MemDC.SelectObject(&m_font);
	//pDC->DrawText(L"굴림",&r,DT_SINGLELINE | DT_CENTER | DT_VCENTER);
	//MemDC.DrawTextW(L"追 加 点 检 者",&r,DT_SINGLELINE | DT_CENTER | DT_VCENTER);



	CBitmap memBitmapBG;	//Bitmap를 받아서 그르게될 CBitmap입니다.
	CBitmap *pOldBmp; 
	memBitmapBG.CreateCompatibleBitmap(pDC, 1920,1080);
	pOldBmp = (CBitmap *)MemDC.SelectObject(cBitmapBG);
	//pDC->PatBlt(0,0,rect.Width(),rect.Height(),WHITENESS );
	pDC->BitBlt(0,0,rect.Width(),rect.Height(),&MemDC,0,0,SRCCOPY);


	CBitmap memBitmapSelect;	//Bitmap를 받아서 그르게될 CBitmap입니다.
	//CBitmap *pOldBmpSelet; 
	memBitmapSelect.CreateCompatibleBitmap(pDC, 1920,1080);
	pOldBmp = (CBitmap *)MemDC.SelectObject(cBitmapSelect);
	
	
	map<int, _SAFETY_DATA>::iterator it;
	for( it = m_mapDataInfo.begin(); it != m_mapDataInfo.end(); ++it)
	{
		_SAFETY_DATA Data;
		Data = it->second;

		if (Data.m_state == SELECT_ON)
		{
 			pDC->BitBlt(Data.m_rtPosBG.left,Data.m_rtPosBG.top,Data.m_rtPosBG.Width(),Data.m_rtPosBG.Height(),&MemDC,Data.m_rtPosBG.left,Data.m_rtPosBG.top,SRCCOPY);
 			pDC->BitBlt(Data.m_rtPos1.left,Data.m_rtPos1.top,Data.m_rtPos1.Width(),Data.m_rtPos1.Height(),&MemDC,Data.m_rtPos1.left,Data.m_rtPos1.top,SRCCOPY);
// 			CString str= "追 加 点 检 者";
// 			MemDC.DrawText(str,&r,DT_SINGLELINE | DT_CENTER | DT_VCENTER);
		}
		else if (Data.m_state == SELECT_OFF)
		{
			pDC->BitBlt(Data.m_rtPos2.left,Data.m_rtPos2.top,Data.m_rtPos2.Width(),Data.m_rtPos2.Height(),&MemDC,Data.m_rtPos2.left,Data.m_rtPos2.top,SRCCOPY);
// 			CString str= "追 加 点 检 者";
// 			MemDC.DrawText(str,&r,DT_SINGLELINE | DT_CENTER | DT_VCENTER);
		}	
	}

	MemDC.SelectObject(pOldFont);
	MemDC.SetBkMode(pOldMode);

	MemDC.SelectObject(pOldBmp);
	//MemDC.SelectObject(pOldBmpSelet);
	MemDC.DeleteDC();
	this->ReleaseDC(pDC);	

	
	
	return TRUE;

}

BOOL CDlgSafetyView::SetCBitmaptoBitmapLoad() //Gdi -> Gdi+ 데이터형 변환
{
	//Bitmap *bitmap = Bitmap::FromHBITMAP((HBITMAP)CBitmap변수.m_hObjct,NULL);
	return TRUE;

}

BOOL CDlgSafetyView::SetBitmaptoCBitmapLoad() //Gdi -> Gdi+ 데이터형 변환
{
	Bitmap *pBitmap;
	pBitmap = (Bitmap*)Image::FromFile(L"./res/BG_CHECKBOX_ALL_END_WHITE.jpg");

	CClientDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.
	CDC MemDC;

	CRect rect;
	GetClientRect(&rect);

	CBitmap memBitmap; //Bitmap를 받아서 그르게될 CBitmap입니다.
	MemDC.CreateCompatibleDC(&dc);
	memBitmap.CreateCompatibleBitmap(&dc, 1920,1080);
	

	/*Graphics graphicsMem(memDC.GetSafeHdc());*/
 	Graphics graphicsMem(dc.GetSafeHdc());
 	graphicsMem.DrawImage(pBitmap,Rect(0,0,1920,1080)); //CBitmap 변수에 Bitmap 이미지를 그려줍니다.

	//CBitmap *pOldBmp; 
	//pOldBmp = (CBitmap *)MemDC.SelectObject(pBitmap);
	/*pOldBmp = (CBitmap *)MemDC.SelectObject(&memBitmap);*/

	//pDC->PatBlt(0,0,rect.Width(),rect.Height(),WHITENESS );
	//dc.BitBlt(0,0,rect.Width(),rect.Height(),&MemDC,0,0,SRCCOPY);

	//MemDC.SelectObject(pOldBmp);
	MemDC.DeleteDC();
	delete pBitmap; // 기존에 pBitmap이 존재할 이유가 없으므로 delete 시킵니다.

	return TRUE;

}

BOOL CDlgSafetyView::SetBitmaptoCBitmapView() //Gdi -> Gdi+ 데이터형 변환
{
	Bitmap *pBitmap;
	pBitmap = (Bitmap*)Image::FromFile(L"./res/BG_CHECKBOX_ALL_END_WHITE.jpg");

	//CClientDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.
	CDC * pDC = GetDC();
	CDC MemDC;
	
	CRect rect;
	GetClientRect(&rect);

	int nWidth = pBitmap->GetWidth();
	int nHeight = pBitmap->GetHeight();


	CBitmap memBitmap; //Bitmap를 받아서 그르게될 CBitmap입니다.
	CBitmap *pOldBmp; 
	MemDC.CreateCompatibleDC(pDC);
	memBitmap.CreateCompatibleBitmap(pDC, 1920,1080);
	pOldBmp = (CBitmap *)MemDC.SelectObject(&memBitmap);
	/*pOldBmp = (CBitmap *)MemDC.SelectObject(&memBitmap);*/

	//pDC->PatBlt(0,0,rect.Width(),rect.Height(),WHITENESS );
	pDC->BitBlt(0,0,rect.Width(),rect.Height(),&MemDC,0,0,SRCCOPY);

	MemDC.SelectObject(pOldBmp);
	MemDC.DeleteDC();

	this->ReleaseDC(pDC);
	delete pBitmap; 
	return TRUE;

}

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
		hbr = (HBRUSH)GetStockObject(NULL_BRUSH);
	}
	return hbr;
}

BOOL CDlgSafetyView::OnEraseBkgnd(CDC* pDC)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	return FALSE;
	//return CDialogEx::OnEraseBkgnd(pDC);
}

void CDlgSafetyView::SetTitleBoardView(int index)
{
	
}

void CDlgSafetyView::addButton(int ikey,CButton* createButton)
{
	m_mapButton[ikey] = createButton;
}

void CDlgSafetyView::ClearButton()
{
	for(int i = 0; i < (int)m_mapButton.size(); i++)
	{
		CButton* deleteButton = m_mapButton[i];
		delete deleteButton;
		deleteButton = NULL;
	}
	m_mapButton.clear();	
	//m_mapButton.FreeExtra(); //사용하지 않는 메모리를 반납
}
#include <algorithm>
BOOL CDlgSafetyView::OnCommand(WPARAM wParam, LPARAM lParam)
{
	if(wParam >= (unsigned int)IDC_BUTTON_TITLE_1 && wParam < (unsigned int)IDC_BUTTON_TITLE_1 + (int)m_mapButton.size())
	{
		for(int i = 0; i < (int)m_mapButton.size(); i++)
		{
			if(IDC_BUTTON_TITLE_1 + i == wParam)
			{
				CDigTitleBoard dlg(i);
				if(dlg.DoModal() == IDOK)
				{
					LoadBoardData(i);
				}
			}
		}
	}

	return CDialogEx::OnCommand(wParam, lParam);
}

void CDlgSafetyView::OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	UINT uStyle = DFCS_BUTTONPUSH;

	ASSERT(lpDrawItemStruct->CtlType == ODT_BUTTON);

	if (lpDrawItemStruct->itemState & ODS_SELECTED)
		uStyle |= DFCS_PUSHED;

	::DrawFrameControl(lpDrawItemStruct->hDC, &lpDrawItemStruct->rcItem, DFC_BUTTON, uStyle);

	CDC dc;
	dc.Attach(lpDrawItemStruct->hDC);

	RECT rect;
	rect = lpDrawItemStruct->rcItem;

	if(nIDCtl >= IDC_BUTTON_TITLE_1 && nIDCtl < nIDCtl + (int)m_mapButton.size())
	{
		for(int i = 0; i < (int)m_mapButton.size(); i++)
		{
			if(nIDCtl == IDC_BUTTON_TITLE_1 + i)
			{
				dc.FillSolidRect(&rect, RGB(static_cast<unsigned int>(rand() % 254), static_cast<unsigned int>(rand() % 254), static_cast<unsigned int>(rand() % 254)));
				break;
			}
		}
	}
}


BOOL CDlgSafetyView::InitBoard()
{
	for (int i = 0; i <TYPE_TITLE_MAX ; i++)
	{
		LoadBoardData(i);
	}
	return TRUE;
}

BOOL CDlgSafetyView::LoadBoardData(int index)
{
	CString strKRkey(_T("")); CString strCNkey(_T(""));
	strKRkey.Format(_T("BOARD_KR_%d"),index);
	strCNkey.Format(_T("BOARD_CN_%d"),index);

	CString strDefKRBoard(_T(""));CString strDefCNBoard(_T(""));
	strDefKRBoard.Format(_T("작업자추가"));
	strDefCNBoard.Format(_T("追加点检者"));

	// UpDatat
	CString strKR=_T(""),strCN=_T("");
	strKR = m_pIniRecipe->read(_T("TITLE"),strKRkey,strDefKRBoard);
	strCN = m_pIniRecipe->read(_T("TITLE"),strCNkey,strDefCNBoard);

	if (strKR == "" || strKR.IsEmpty() == TRUE )
	{
		strKR = strDefKRBoard;
	}

	if (strCN == "" || strCN.IsEmpty() == TRUE )
	{
		strCN = strDefCNBoard;
	}

	GetDlgItem(IDC_STATIC_TITLE_1 + (2 * index))->SetWindowText(strKR);
	GetDlgItem(IDC_STATIC_TITLE_1 + (2 * index +1))->SetWindowText(strCN); 

	this->Invalidate(0);
	return TRUE;
}