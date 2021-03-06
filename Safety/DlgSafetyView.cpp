// DlgSafetyView.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "Safety.h"
#include "DlgSafetyView.h"
#include <atlimage.h>
#include "DigTitleBoard.h"
#include <windows.h>
#include <tlhelp32.h>
#include "MaintInfo.h"
#include "MaintPassword.h"
#include "MaintComment.h"

// CDlgSafetyView 대화 상자입니다.

IMPLEMENT_DYNCREATE(CDlgSafetyView, CDialogEx)

CDlgSafetyView::CDlgSafetyView(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgSafetyView::IDD, pParent)
{
	CString strRcpPath = _T("");
	strRcpPath.Format(_T("%s"),RCP_PATH);

	m_pIniRecipe = new CIniFile(strRcpPath);

	m_font.CreateFont( 19, // nHeight 
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
		_T("NSimSun")); // lpszFacename 

	m_fontCH.CreateFont( 18, // nHeight 
		6, // nWidth 
		0, // nEscapement 
		0, // nOrientation 
		FW_MEDIUM, // nWeight 
		0, // bItalic 
		0, // bUnderline 
		0, // cStrikeOut 
		0, // nCharSet 
		OUT_DEFAULT_PRECIS, // nOutPrecision 
		0,                              // nClipPrecision 
		DEFAULT_QUALITY,       // nQuality
		DEFAULT_PITCH | FF_DONTCARE,  // nPitchAndFamily 
		_T("NSimSun")); // lpszFacename 



	RtCommentButton = CRect(611, 1012, 690, 1074);
	RtHourButton = CRect(1445, 1012, 1552, 1074);
	RtTempButton = CRect(1712, 1012, 1826, 1074);
	RtUnlockButton = CRect(1827, 1012, 1917, 1074);
	
	RtCommentArea = CRect(700,1015,1400,1070);
	RtPhoneArea = CRect(1050,651,1400,671);	
	RtContactArea = CRect(1500,651,1850,671);
	RtWorkerArea = CRect(500,1047,596,1063);
	RtHourArea = CRect(1609,1032,1646,1051);
	RtDateArea = CRect(55,1045,200,1064);
}

CDlgSafetyView::~CDlgSafetyView()
{
	
	ClearButton();
	delete(cBitmapBG);
	delete(cBitmapSelect);
	delete(m_cImageBG);
	delete(m_cImageSelect);

	delete(m_pIniRecipe);
	DeleteObject(m_font);
	DeleteObject(m_font2);
	DeleteObject(m_font3);
	DeleteObject(m_font4);
	DeleteObject(m_font5);
	DeleteObject(m_fontCH);
	UnhookWindowsHookEx(hook);


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
	ON_WM_TIMER()
	ON_WM_DESTROY()
END_MESSAGE_MAP()

void CDlgSafetyView::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	SetMainImageCBitmapLoad();
	//OnPaintInfo();

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
	


	
	CString strFileName("");
	strFileName.Format(_T("%sBG_CHECKBOX_ALL_END_WHITE.jpg"),EQP_PATH);
	//	HRESULT hr = cImageBG.Load(_T("..\\Safety\\res\\BG_CHECKBOX_ALL_END_WHITE.jpg"));
	HRESULT hr = m_cImageBG.Load(strFileName);
	if(FAILED(hr))
	{
		AfxMessageBox(_T("Error : BG_IMAGE Invalid file"));
		return FALSE;
	}


	strFileName.Format(_T("%sBG_CHECKBOX_ALL_END_SELECT.jpg"),EQP_PATH);
	//	hr = cImageSelect.Load(_T("..\\Safety\\res\\BG_CHECKBOX_ALL_END_SELECT.jpg"));
	hr = m_cImageSelect.Load(strFileName);
	if(FAILED(hr))
	{
		AfxMessageBox(_T("Error : SELECT_IMAGE Invalid file"));
		return FALSE;
	}

	cBitmapBG = CBitmap::FromHandle(m_cImageBG);

	cBitmapSelect = CBitmap::FromHandle(m_cImageSelect);

	

 	int nCount(0);
	ClearButton();
	for (int i = 0; i <TYPE_TITLE_MAX ; i++)
	{
		AddMapDataInfo(i,DataInfo[i]);	
		for (int j = 0; j < TYPE_TITLE_MIN; j++)
		{
			if ( j == 0 )
			{
//				m_ctrTex[i][j].Create(_T("작업자추가"), WS_CHILD | WS_VISIBLE,CRect(10, 10, 20, 20), this,IDC_STATIC_TITLE_1 + nCount);
				m_ctrTex[i][j].Create(_T(""), WS_CHILD | WS_VISIBLE,CRect(10, 10, 20, 20), this,IDC_STATIC_TITLE_1 + nCount);
				
				Sleep(5);
				m_ctrTex[i][j].MoveWindow( DataInfo[i].m_rtPosBG.left + 15, DataInfo[i].m_rtPosBG.top + 5,
					DataInfo[i].m_rtPosBG.right, DataInfo[i].m_rtPosBG.top + 25, TRUE );	
			}
			else
			{

 				CString strCh = _T("追加点检者");
// 				m_ctrTex[i][j].Create(strCh, WS_CHILD | WS_VISIBLE,CRect(10, 10, 20, 20), this,IDC_STATIC_TITLE_1 + nCount);
				m_ctrTex[i][j].Create(_T(""), WS_CHILD | WS_VISIBLE,CRect(10, 10, 20, 20), this,IDC_STATIC_TITLE_1 + nCount);
				//m_ctrTex[i][j].CreateWindow("static",strCh, WS_CHILD | WS_VISIBLE,CRect(10, 10, 20, 20), this,IDC_STATIC_TITLE_1 + nCount);
			
				Sleep(5);
 				m_ctrTex[i][j].MoveWindow(DataInfo[i].m_rtPosBG.left + 15,DataInfo[i].m_rtPosBG.top + 25,
 					DataInfo[i].m_rtPosBG.right,DataInfo[i].m_rtPosBG.top + 50,TRUE);
				//GetDlgItem(IDC_STATIC_TITLE_1 + nCount)->SetFont(&m_font);
				//GetDlgItem(IDC_STATIC_TITLE_1 + nCount)->SetWindowText(strCh);
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
	bok = SetMainImageCBitmapLoad();
	if (bok == FALSE)
	{
		AfxMessageBox(_T("Main Image Load failed."));
	}
	
	createCommentButton = new CButton;
	createHourButton = new CButton;
	createTemporaryButton = new CButton;
	createUnlockButton = new CButton;
	
//	createCommentButton->Create(L"Comment",WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | BS_OWNERDRAW|BS_BITMAP,CRect(611, 1012, 690, 1074), this,IDC_BUTTON_COMMENT);		
	createCommentButton->Create(L"Comment",WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | BS_OWNERDRAW | BS_MULTILINE,RtCommentButton, this,IDC_BUTTON_COMMENT);		

//	createHourButton->Create(L"Working\r\nHour",WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON |BS_BITMAP | BS_OWNERDRAW,CRect(1465, 1012, 1552, 1074), this,IDC_BUTTON_HOUR);	
	createHourButton->Create(L"Working\r\nHour",WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | BS_OWNERDRAW | BS_MULTILINE,RtHourButton, this,IDC_BUTTON_HOUR);	

//	createTemporaryButton->Create(L"Temporary\r\nUse",WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON |BS_BITMAP | BS_OWNERDRAW,CRect(1732, 1012, 1826, 1074), this,IDC_BUTTON_TEMPORARY);	
	createTemporaryButton->Create(L"Temporary\r\nUse",WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | BS_OWNERDRAW | BS_MULTILINE,RtTempButton, this,IDC_BUTTON_TEMPORARY);

//	createUnlockButton->Create(L"Unlock",WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | BS_OWNERDRAW |BS_BITMAP,CRect(1827, 1012, 1917, 1074), this,IDC_BUTTON_UNLOCK);
	createUnlockButton->Create(L"Unlock",WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | BS_OWNERDRAW | BS_MULTILINE,RtUnlockButton, this,IDC_BUTTON_UNLOCK);

		


	//m_font2.CreatePointFont(200,_T("굴림"));
	m_font2.CreateFont( 30, 0, 0, 0, FW_BOLD, FALSE, FALSE, 0, 
		DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, 
		TMPF_TRUETYPE,_T("Tahoma") );
	m_font3.CreatePointFont(100,_T("Tahoma"));
	m_font4.CreatePointFont(150,_T("Tahoma"));
	m_font5.CreatePointFont(120,_T("Tahoma"));

	m_strText[0].Create(L"",WS_CHILD | WS_VISIBLE,CRect(10,10,20,20),this,IDC_STATIC_PHONE);
	m_strText[0].MoveWindow(1050,651,1400,671);	
	m_strText[0].SetFont(&m_font2,TRUE);
	m_strText[1].Create(L"",WS_CHILD | WS_VISIBLE,CRect(10,10,20,20),this,IDC_STATIC_CONTACT);
	m_strText[1].MoveWindow(1500,651,1850,671);
	m_strText[1].SetFont(&m_font2,TRUE);
	m_strText[2].Create(L"",WS_CHILD | WS_VISIBLE,CRect(10,10,20,20),this,IDC_STATIC_CHECKER);
	m_strText[2].MoveWindow(500,1020,596,1036);
	//m_strText[2].MoveWindow(500,1020,700,1036);
	m_strText[2].SetFont(&m_font3,TRUE);
	
	m_strText[3].Create(L"",WS_CHILD | WS_VISIBLE,CRect(10,10,20,20),this,IDC_STATIC_WORKER);
	m_strText[3].MoveWindow(500,1047,596,1063);
	//m_strText[3].MoveWindow(500,1047,700,1063);
	m_strText[3].SetFont(&m_font3,TRUE);

	m_strText[4].Create(L"",WS_CHILD | WS_VISIBLE,CRect(10,10,20,20),this,IDC_STATIC_HOUR);
	m_strText[4].MoveWindow(1609,1032,1646,1051);
	m_strText[4].SetFont(&m_font4,TRUE);

	m_strText[5].Create(L"",WS_CHILD | WS_VISIBLE,CRect(10,10,20,20),this,IDC_STATIC_DATE);
	m_strText[5].MoveWindow(55,1045,200,1064);
	m_strText[5].SetFont(&m_font5,TRUE);
	
	m_strText[6].Create(L"",WS_CHILD | WS_VISIBLE | BS_MULTILINE ,CRect(10,10,20,20),this,IDC_STATIC_COMMENT);
	m_strText[6].MoveWindow(700,1015,1400,1070);
	m_strText[6].SetFont(&m_font3,TRUE);



	InitBoard();
	
	SetTimer(1, 1000, NULL);	

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

BOOL CDlgSafetyView::SetMainImageCBitmapLoad()
{
	CDC * pDC = GetDC();	
	CDC MemDC;
	CRect rect;

	GetClientRect(&rect);
	MemDC.CreateCompatibleDC(pDC);

	RECT r = {50,70,700,700};
	int pOldMode = MemDC.SetBkMode(TRANSPARENT);
	//CFont * pOldFont = (CFont *)MemDC.SelectObject(&m_font);
	CFont * pOldFont = (CFont *)MemDC.SelectObject(&m_font);
//	CFont * pCHFont = (CFont *)MemDC.SelectObject(&m_fontCH);
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
	

	int index(0);
	map<int, _SAFETY_DATA>::iterator it;
	for( it = m_mapDataInfo.begin(); it != m_mapDataInfo.end(); ++it)
	{
		_SAFETY_DATA Data;
		Data = it->second;

		if (Data.m_state == SELECT_ON)
		{
 			pDC->BitBlt(Data.m_rtPosBG.left,Data.m_rtPosBG.top,Data.m_rtPosBG.Width(),Data.m_rtPosBG.Height(),&MemDC,Data.m_rtPosBG.left,Data.m_rtPosBG.top,SRCCOPY);
 			pDC->BitBlt(Data.m_rtPos1.left,Data.m_rtPos1.top,Data.m_rtPos1.Width(),Data.m_rtPos1.Height(),&MemDC,Data.m_rtPos1.left,Data.m_rtPos1.top,SRCCOPY);
		}
		else if (Data.m_state == SELECT_OFF)
		{
			pDC->BitBlt(Data.m_rtPos2.left,Data.m_rtPos2.top,Data.m_rtPos2.Width(),Data.m_rtPos2.Height(),&MemDC,Data.m_rtPos2.left,Data.m_rtPos2.top,SRCCOPY);

		}	
		CStringW strKRkey(_T("")); CStringW strCNkey(_T(""));
		strKRkey.Format(_T("BOARD_KR_%d"),index);
		strCNkey.Format(_T("BOARD_CN_%d"),index);

		CString strDefKRBoard(_T(""));CString strDefCNBoard(_T(""));
		strDefKRBoard.Format(_T("작업자추가"));
		strDefCNBoard.Format(_T("追加点检者"));

		// UpDatat

		CString strKR=_T(""),strCN=_T("");
		strKR = m_pIniRecipe->read(_T("TITLE"),strKRkey,strDefKRBoard);
		strCN = m_pIniRecipe->read(_T("TITLE"),strCNkey,strDefCNBoard);

		if (strKR == _T("") || strKR.IsEmpty() == TRUE )
		{
			strKR = strDefKRBoard;
		}

		if (strCN == _T("") || strCN.IsEmpty() == TRUE )
		{
			strCN = strDefCNBoard;
		}

		CStringW str = L"";
		pDC->SetBkMode(TRANSPARENT);
		
		pDC->SelectObject(&m_fontCH);
		str.Format(_T(" %s\r\n %s"),strKR,strCN);
//		str.Format(_T("%s"),strCN);
		CRect tempRect = Data.m_rtPosBG;
		tempRect.top = tempRect.top+5;
		tempRect.bottom = tempRect.bottom+5;
		//tempRect.SetRect(Data.m_rtPosBG.left,Data.m_rtPosBG.top+5,Data.m_rtPosBG.right,Data.m_rtPosBG.bottom+5);
//		pDC->DrawText(str,Data.m_rtPosBG,BS_MULTILINE);
		pDC->DrawText(str,tempRect,BS_MULTILINE);
		
		// 			CString str= "追 加 点 检 者";
		// 			MemDC.DrawText(str,&r,DT_SINGLELINE | DT_CENTER | DT_VCENTER);
		index++;
	}

	MemDC.SelectObject(&m_fontCH);
	MemDC.SetBkMode(pOldMode);

	MemDC.SelectObject(pOldBmp);
	//MemDC.SelectObject(pOldBmpSelet);
	MemDC.DeleteDC();
	this->ReleaseDC(pDC);	




//[2021/9/10] ubsWgt - ScreenSaver 화면에서 System Key 입력 불가, 개발중에는 주석, 이후 해제
// 	HINSTANCE inst = AfxGetInstanceHandle();
// 	hook = SetWindowsHookEx(WH_KEYBOARD_LL, WinKeyHook, inst, 0);

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
// 	CString satrtp = _T("");
// 	satrtp.Format(_T("%d %d"),point.x,point.y);
//this->Invalidate(0);
//SetDlgItemText(IDC_STATIC_MOUSE_POS,satrtp);
	
	map<int, _SAFETY_DATA>::iterator it;

	int nCount = m_mapDataInfo.size();
	int i=0;
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
			this->Invalidate(FALSE);
//			ValidateRect(CRect(2,75,35,970));
// 			ValidateRect(RtContactArea);
// 			ValidateRect(RtPhoneArea);

			//this->InvalidateRect(Data.m_rtPos1,FALSE);
// 			this->InvalidateRect(CRect(2,75,35,970),FALSE);
// 			
// 
// 			this->InvalidateRect(RtCommentButton,FALSE);
// 			this->InvalidateRect(RtHourButton,FALSE);
// 			this->InvalidateRect(RtTempButton,FALSE);
// 			this->InvalidateRect(RtUnlockButton,FALSE);
// 
// 			this->InvalidateRect(RtPhoneArea,FALSE);
// 			this->InvalidateRect(RtContactArea,FALSE);
// 			this->InvalidateRect(RtWorkerArea,FALSE);
// 			this->InvalidateRect(RtHourArea,FALSE);
// 			this->InvalidateRect(RtDateArea,FALSE);


			// from left, top, right, and bottom			
			//OnPaintInfo();

			break;
		}
		else if (Data.m_rtPos2.PtInRect(point))
		{
			SetItemsStateValue(it->first,SELECT_OFF);
			this->Invalidate(FALSE);
//			ValidateRect(CRect(2,75,35,970));
// 			ValidateRect(RtContactArea);
// 			ValidateRect(RtPhoneArea);
			//this->InvalidateRect(Data.m_rtPos2,FALSE);
// 			this->InvalidateRect(CRect(2,75,35,970),FALSE);
//  
//  			this->InvalidateRect(RtCommentButton,FALSE);
//  			this->InvalidateRect(RtHourButton,FALSE);
//  			this->InvalidateRect(RtTempButton,FALSE);
//  			this->InvalidateRect(RtUnlockButton,FALSE);

// 			this->InvalidateRect(RtPhoneArea,FALSE);
// 			this->InvalidateRect(RtContactArea,FALSE);
// 			this->InvalidateRect(RtWorkerArea,FALSE);
// 			this->InvalidateRect(RtHourArea,FALSE);
// 			this->InvalidateRect(RtDateArea,FALSE);
			//OnPaintInfo();

			break;
		}
		i++;
	}
	
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
	ShowWindow(SW_HIDE);

	PCSTR str = "MacMic.exe";

	HANDLE hMain = GetProcessByName(str);

//	HWND HWMain = :: FindWindow(NULL, _T("chrome.exe"));

	if(hMain == NULL) 
	{
	}
	else
	{
		CWnd *cwnd = CWnd::FromHandle((HWND)hMain);	
		cwnd->ShowWindow(SW_SHOW);
	}

	CDialogEx::OnOK();
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
	else if(wParam == (unsigned int)IDC_BUTTON_TEMPORARY)
	{
// 		for(int i=0; i<m_mapDataInfo.size(); i++)
// 		{
// 			if(m_mapDataInfo[i].m_state == 0)
// 			{
// 				AfxMessageBox(_T("점검하지 않은 항목이 있습니다."));
// 				return FALSE;
// 			}
// 		}
		OnBnClickedOk();		
	}
	else if(wParam == (unsigned int)IDC_BUTTON_UNLOCK)
 	{
// 		for(int i=0; i<m_mapDataInfo.size(); i++)
// 		{
// 			if(m_mapDataInfo[i].m_state == 0)
// 			{
// 				AfxMessageBox(_T("점검하지 않은 항목이 있습니다."));
// 				return FALSE;
// 			}
// 		}

		CMaintPassword maintpassword;
		maintpassword.DoModal();

		if(maintpassword.m_bPassword == TRUE)
		{
			CRegKey RegKey;
			RegKey.Create(HKEY_CURRENT_USER,_T("SOFTWARE\\REPAIR\\MacMic\\REPAIR")); 
			RegKey.SetValue(_T("0"), _T("SCREEN_SAVER_INFO"));
			RegKey.Close();
			OnBnClickedOk();
		}

	}
	else if(wParam == (unsigned)IDC_BUTTON_COMMENT || wParam == (unsigned)IDC_STATIC_COMMENT || wParam == (unsigned)IDC_BUTTON_HOUR || wParam == (unsigned)IDC_STATIC_MAINT_WORK_HOUR)
	{
		CMaintComment MaintComment;
		MaintComment.DoModal();

		OnPaintInfo();
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

	if(nIDCtl >= IDC_BUTTON_TITLE_1 && nIDCtl < IDC_BUTTON_TITLE_1 + (int)m_mapButton.size())
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
	else if(nIDCtl == IDC_BUTTON_UNLOCK)
	{
		CImage bmpImage;
		CDC dc;
		CRect crect;
		dc.Attach(lpDrawItemStruct -> hDC);                //버튼의 dc구하기
		crect = lpDrawItemStruct->rcItem;                   //버튼영역 구하기

// 		CDC* pMDC = new CDC;
// 
// 		bmpImage.Load(_T("D:\\Safety\\Lock_Icon.bmp"));
		
//		pMDC->CreateCompatibleDC(&dc);
// 		CBitmap* pb = new CBitmap;
// 		pb->CreateCompatibleBitmap(&dc,crect.Width(),crect.Height());
// 		CBitmap* pob = pMDC->SelectObject(pb);
// 		pMDC->SetStretchBltMode(HALFTONE);
// 
// 		bmpImage.StretchBlt(pMDC->m_hDC,-1,-1,crect.Width(),crect.Height(),0,0,bmpImage.GetWidth(),bmpImage.GetHeight(),SRCCOPY);
// 
// 		pMDC->SelectObject(pob);
// 		CImage new_image;
// 		
// 		new_image.Attach((HBITMAP)(*pb));
// 		new_image.BitBlt(dc,crect.left,crect.top,SRCCOPY);
		
		dc.Draw3dRect(&rect,RGB(0,0,0),RGB(0,0,0));  //버튼의 외각선 그리기

		
		
 		dc.FillSolidRect(&rect,RGB(222,223,222));             //버튼색상
//		dc.FillSolidRect(&rect,RGB(255,255,255));             //버튼색상
// 		UINT state = lpDrawItemStruct-> itemState;         //버튼상태구하기
// 		if((state &ODS_SELECTED))
// 		{
// 			dc.DrawEdge(&rect,EDGE_SUNKEN,BF_RECT);
// 		}
// 		else
// 		{
// 			dc.DrawEdge(&rect,EDGE_RAISED,BF_RECT);
// 		}
//		dc.SetBkColor(RGB(51,51,51));                       //text의 백그라운드 색상
		dc.SetTextColor(RGB(0,0,0));                     //texttort
		TCHAR buffer[MAX_PATH];                            //버튼의 text를 얻기위한 임시버퍼
		ZeroMemory(buffer,MAX_PATH);                       //버퍼초기화
		::GetWindowTextA(lpDrawItemStruct->hwndItem,(LPSTR)buffer,MAX_PATH); //버튼의 text얻기
		dc.DrawText(L"UnLock",&rect,DT_VCENTER|DT_SINGLELINE|DT_CENTER); //버튼의 text넣기
		dc.Detach();                                                  //버튼의 dc 풀어주기
		
	}
	else if(nIDCtl == IDC_BUTTON_TEMPORARY)
	{
		CImage bmpImage;
		CDC dc;
		CRect crect;
		dc.Attach(lpDrawItemStruct -> hDC);                //버튼의 dc구하기
		crect = lpDrawItemStruct->rcItem;                   //버튼영역 구하기

		dc.Draw3dRect(&rect,RGB(0,0,0),RGB(0,0,0));  //버튼의 외각선 그리기
		dc.FillSolidRect(&rect,RGB(222,223,222));             //버튼색상
	
		dc.SetTextColor(RGB(0,0,0));                     //texttort
		TCHAR buffer[MAX_PATH];                            //버튼의 text를 얻기위한 임시버퍼
		ZeroMemory(buffer,MAX_PATH);                       //버퍼초기화
		::GetWindowTextA(lpDrawItemStruct->hwndItem,(LPSTR)buffer,MAX_PATH); //버튼의 text얻기
		//dc.DrawText(strW,&rect,DT_VCENTER|DT_SINGLELINE| DT_CENTER | DT_WORDBREAK); //버튼의 text넣기
		dc.DrawText(L"Temporary Use",&rect,DT_SINGLELINE | DT_VCENTER | DT_CENTER | DT_WORDBREAK); //버튼의 text넣기
		dc.Detach();                                                  //버튼의 dc 풀어주기
	}
	else if(nIDCtl == IDC_BUTTON_HOUR)
	{
		CImage bmpImage;
		CDC dc;
		CRect crect;
		dc.Attach(lpDrawItemStruct -> hDC);                //버튼의 dc구하기
		crect = lpDrawItemStruct->rcItem;                   //버튼영역 구하기

		dc.Draw3dRect(&rect,RGB(0,0,0),RGB(0,0,0));  //버튼의 외각선 그리기
		dc.FillSolidRect(&rect,RGB(198,195,198));             //버튼색상

		dc.SetTextColor(RGB(0,0,0));                     //texttort
		TCHAR buffer[MAX_PATH];                            //버튼의 text를 얻기위한 임시버퍼
		ZeroMemory(buffer,MAX_PATH);                       //버퍼초기화
		::GetWindowTextA(lpDrawItemStruct->hwndItem,(LPSTR)buffer,MAX_PATH); //버튼의 text얻기
		dc.DrawText(L"Working Hour",&rect,DT_VCENTER|DT_SINGLELINE|DT_CENTER | DT_WORDBREAK); //버튼의 text넣기
		dc.Detach();                                                  //버튼의 dc 풀어주기
	}
	else if(nIDCtl == IDC_BUTTON_COMMENT)
	{
		CImage bmpImage;
		CDC dc;
		CRect crect;
		dc.Attach(lpDrawItemStruct -> hDC);                //버튼의 dc구하기
		crect = lpDrawItemStruct->rcItem;                   //버튼영역 구하기

		dc.Draw3dRect(&rect,RGB(0,0,0),RGB(0,0,0));  //버튼의 외각선 그리기
		dc.FillSolidRect(&rect,RGB(198,195,198));             //버튼색상

		dc.SetTextColor(RGB(0,0,0));                     //texttort
		TCHAR buffer[MAX_PATH];                            //버튼의 text를 얻기위한 임시버퍼
		ZeroMemory(buffer,MAX_PATH);                       //버퍼초기화
		::GetWindowTextA(lpDrawItemStruct->hwndItem,(LPSTR)buffer,MAX_PATH); //버튼의 text얻기
		dc.DrawText(L"Comment",&rect,DT_VCENTER|DT_SINGLELINE|DT_CENTER); //버튼의 text넣기
		dc.SelectObject(&m_font);
		dc.Detach();                                                  //버튼의 dc 풀어주기
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

// 	GetDlgItem(IDC_STATIC_TITLE_1 + (2 * index))->SetWindowText(strKR);
// 	GetDlgItem(IDC_STATIC_TITLE_1 + (2 * index +1))->SetWindowText(strCN); 

	this->Invalidate(FALSE);
	return TRUE;
}

HANDLE CDlgSafetyView::GetProcessByName(PCSTR name)
{
	DWORD pid = 0;
	
// 	std::string convert;
// 
// 	convert.assign(name.begin(),name.end());

	// Create toolhelp snapshot.
	HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	PROCESSENTRY32 process;
	ZeroMemory(&process, sizeof(process));
	process.dwSize = sizeof(process);

	// Walkthrough all processes.
	if (Process32First(snapshot, &process))
	{
		do
		{
			// Compare process.szExeFile based on format of name, i.e., trim file path
			// trim .exe if necessary, etc.
			 CString str = process.szExeFile;
//			if (string(process.szExeFile) == "Macmic.exe")
			 if (str == "chrome.exe")
			{
				pid = process.th32ProcessID;
				break;
			}
		} while (Process32Next(snapshot, &process));
	}

	CloseHandle(snapshot);

	if (pid != 0)
	{
		return OpenProcess(PROCESS_ALL_ACCESS, FALSE, pid);
	}

	// Not found


	return NULL;
}


void CDlgSafetyView::OnTimer(UINT_PTR nIDEvent)
{
	CWinApp *pApp = AfxGetApp();
	int iScreenSaverInfo = 0;
	
	CRegKey regKey;
	CString strValue;
	DWORD dwSize = 1024;
	if (regKey.Open(HKEY_CURRENT_USER, _T("SOFTWARE\\REPAIR\\MacMic\\REPAIR")) == ERROR_SUCCESS)
	{
		if (regKey.QueryStringValue(_T("SCREEN_SAVER_INFO"), strValue.GetBuffer(dwSize), &dwSize) == ERROR_SUCCESS)
		{
			strValue.ReleaseBuffer();
		}
		regKey.Close();
	}
	
	iScreenSaverInfo = _ttoi(strValue);
	switch(nIDEvent)
	{
	case 1:
		KillTimer(1);
		//iScreenSaverInfo = pApp->GetProfileInt(_T("REPAIR"),_T("SCREEN_SAVER_INFO"),0);

		if(iScreenSaverInfo == 0)
		{
			CMaintInfo MainInfo;
			MainInfo.DoModal();
			if(iScreenSaverInfo == 0)
			{
				SetTimer(1,1000,NULL);
			}
			else
				OnPaintInfo();
		}
		else if(iScreenSaverInfo == 1)
		{
			OnPaintInfo();						
		}

		break;
	}
	CDialogEx::OnTimer(nIDEvent);
}

void CDlgSafetyView::OnPaintInfo()
{	
	Invalidate(FALSE);

// 	GetDlgItem(IDC_STATIC_PHONE)->SetWindowText(_T(""));
// 	GetDlgItem(IDC_STATIC_CONTACT)->SetWindowText(_T(""));
// 	GetDlgItem(IDC_STATIC_CHECKER)->SetWindowText(_T(""));
// 	GetDlgItem(IDC_STATIC_WORKER)->SetWindowText(_T(""));
// 	GetDlgItem(IDC_STATIC_HOUR)->SetWindowText(_T(""));
// 	GetDlgItem(IDC_STATIC_DATE)->SetWindowText(_T(""));
	// 20180709 변경 구문

	CStringW strPhone =L"", strContact =L"", strWorker =L"", strChecker=L"", strHour =L"", strStartTime = L"", strComment = L"";

	char str[200];
	GetPrivateProfileString(_T("MaintInfo"), _T("Worker"), _T(""),(LPWSTR)str,200, MAINT_PATH);
	strWorker.Format(L"%s",str);// = str;
	GetPrivateProfileString(_T("MaintInfo"), _T("Checker"), _T(""),(LPWSTR)str,200, MAINT_PATH);
	strChecker.Format(L"%s",str);// = str;
	GetPrivateProfileString(_T("MaintInfo"), _T("Phone"), _T(""),(LPWSTR)str,200,MAINT_PATH);
	strPhone.Format(L"Phone : %s",str);// = str;
	GetPrivateProfileString(_T("MaintInfo"), _T("Hour"), _T(""),(LPWSTR)str,200,MAINT_PATH);
	strHour.Format(L"%s",str);// = str;
	GetPrivateProfileString(_T("MaintInfo"), _T("Contact"), _T(""),(LPWSTR)str,200,MAINT_PATH);
	strContact.Format(L"Contact : %s",str);// = str;
	GetPrivateProfileString(_T("MaintInfo"), _T("StartTime"), _T(""),(LPWSTR)str,200,MAINT_PATH);
	strStartTime.Format(L"%s",str);
	

	TCHAR tzReturn[32767] ={0,}; 
	DWORD dwSize = ::GetPrivateProfileSection( _T( "MaintComment" ), tzReturn, 32767, MAINT_PATH ); 
	if ( dwSize !=0)
	{
		for( int iLoop = 0; iLoop < dwSize - 1; iLoop++ ) 
		{ 
			if( _T( '\0' ) == tzReturn[iLoop] ) 
				tzReturn[iLoop] = _T( '\n' ); 
		} 
		if( 0 != dwSize ) 
		{ 
			CString sRead;
			sRead.Format( _T( "%s" ), tzReturn );
			int iLine = 0; CString sLine;
			while( ::AfxExtractSubString( sLine, sRead, iLine++, _T( '\n' ) ) )
			{
				int iTab = 0; CString sTab; int iIndex = 1;
				while( ::AfxExtractSubString( sTab, sLine, iTab++, _T( '\t' ) ) )
				{ 
					CStringW strTemp;
					strTemp.Format(L"%s\r\n",sTab);
					strComment += strTemp;
				} 
			} 
		}
	}

	strComment.Delete(0,8);

	GetDlgItem(IDC_STATIC_PHONE)->SetWindowText(strPhone);
	GetDlgItem(IDC_STATIC_CONTACT)->SetWindowText(strContact);
	GetDlgItem(IDC_STATIC_CHECKER)->SetWindowText(strChecker);
	GetDlgItem(IDC_STATIC_WORKER)->SetWindowText(strWorker);
	GetDlgItem(IDC_STATIC_HOUR)->SetWindowText(strHour);
	GetDlgItem(IDC_STATIC_DATE)->SetWindowText(strStartTime);
	GetDlgItem(IDC_STATIC_COMMENT)->SetWindowText(strComment);
	
}

LRESULT CALLBACK CDlgSafetyView::WinKeyHook(int code, WPARAM wparam, LPARAM lparam)
{
	auto PKBDLLHOOKSTRUCT key = (PKBDLLHOOKSTRUCT)lparam;

	CWnd *pWnd = AfxGetMainWnd();
	HWND hWnd = pWnd->m_hWnd;

	switch(wparam)
	{
	case(WM_KEYDOWN):
	case(WM_SYSKEYDOWN):
		if((key->vkCode==VK_LWIN) || (key->vkCode==VK_RWIN) || (key->vkCode == VK_LCONTROL) || (key->vkCode == VK_MENU) || (key->vkCode == VK_RCONTROL) || (key->vkCode == VK_F4) 
			|| (key->vkCode == VK_ESCAPE) || (key->vkCode == VK_RETURN) || (key->vkCode == VK_SPACE) || (key->vkCode == VK_CANCEL) || (key->vkCode == VK_TAB))
			return TRUE;

	case(WM_KEYUP):
	case(WM_SYSKEYUP):
		if((key->vkCode==VK_LWIN) || (key->vkCode==VK_RWIN) || (key->vkCode == VK_LCONTROL) || (key->vkCode == VK_MENU) || (key->vkCode == VK_RCONTROL) || (key->vkCode == VK_F4) 
			|| (key->vkCode == VK_ESCAPE) || (key->vkCode == VK_RETURN) || (key->vkCode == VK_SPACE) || (key->vkCode == VK_CANCEL) || (key->vkCode == VK_TAB))
			return TRUE;
	}

	return CallNextHookEx(0, code, wparam, lparam);
}
/*
BOOL CDlgSafetyView::PreTranslateMessage(MSG* pMsg)
{
	if(pMsg->message == WM_SYSKEYDOWN || pMsg->message == WM_KEYDOWN || pMsg->message == WM_SYSKEYUP || pMsg->message == WM_KEYUP)
	{
		if(pMsg->wParam == VK_LWIN || pMsg->wParam == VK_RWIN || pMsg->wParam == VK_LCONTROL || pMsg->wParam == VK_RCONTROL || pMsg->wParam == VK_CONTROL || pMsg->wParam == VK_MENU || pMsg->wParam == VK_F4 || pMsg->wParam == VK_RETURN || pMsg->wParam == VK_ESCAPE || pMsg->wParam == VK_SPACE || pMsg->wParam == VK_CANCEL)
			return TRUE;
	}
	return CDialog::PreTranslateMessage(pMsg);
}
*/
void CDlgSafetyView::OnDestroy()
{
	CDialogEx::OnDestroy();

	ClearButton();
	delete createCommentButton;
	delete createHourButton;
	delete createTemporaryButton;
	delete createUnlockButton;

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
}
