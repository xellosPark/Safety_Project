// DigTitleBoard.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "Safety.h"
#include "DigTitleBoard.h"
#include <locale>

// CDigTitleBoard 대화 상자입니다.

IMPLEMENT_DYNAMIC(CDigTitleBoard, CDialog)

CDigTitleBoard::CDigTitleBoard(int nIndex/*=0*/,CWnd* pParent /*=NULL*/)
	: CDialog(CDigTitleBoard::IDD, pParent)
{
	m_pIniRecipe = NULL;
	CString strRcpPath = _T("");
	strRcpPath.Format(_T("%s"),RCP_PATH);

	m_pIniRecipe = new CIniFile(strRcpPath);
	m_nIndex = nIndex;


	m_font14;
	m_font14.CreateFont( 14, // nHeight 
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

CDigTitleBoard::~CDigTitleBoard()
{
	delete(m_pIniRecipe);
	DeleteObject(m_font14);
}

void CDigTitleBoard::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDigTitleBoard, CDialog)
	ON_BN_CLICKED(IDOK, &CDigTitleBoard::OnBnClickedOk)
	ON_WM_ERASEBKGND()
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDCANCEL, &CDigTitleBoard::OnBnClickedCancel)
END_MESSAGE_MAP()


// CDigTitleBoard 메시지 처리기입니다.

void CDigTitleBoard::OnBnClickedOk()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	CString strKRBoard = L"",strCNBoard = L"";

	GetDlgItemText(IDC_EDIT_KR_BOARD,strKRBoard);
	GetDlgItemText(IDC_EDIT_CN_BOARD,strCNBoard);

	SafetyDataSave(m_nIndex,strKRBoard,strCNBoard);

	OnOK();
}


BOOL CDigTitleBoard::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	BOOL bOk = SafetyDataLOAD(m_nIndex);

	GetDlgItem(IDC_STATIC_TEXT_KR)->SetFont(&m_font14);
	GetDlgItem(IDC_STATIC_TEXT_CN)->SetFont(&m_font14);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

BOOL CDigTitleBoard::SafetyDataLOAD(int nKey)
{
	CString strKRkey(_T(""));CString strCNkey(_T(""));
	strKRkey.Format(_T("BOARD_KR_%d"),nKey);
	strCNkey.Format(_T("BOARD_CN_%d"),nKey);

	CString strDefKRBoard(_T(""));CString strDefCNBoard(_T(""));
	strDefKRBoard.Format(_T("작업자추가%d"),nKey);
	strDefCNBoard.Format(_T("追加点检者%d"),nKey);
	
//	CString str = L"追加点检者";
//	wstring strUni = L"追加点检者"; 
// 	
// 	int len = WideCharToMultiByte( CP_ACP, 0, &strUni[0], -1, NULL, 0, NULL, NULL );
// 	string strMulti(len,0);
// 	WideCharToMultiByte( CP_ACP, 0, &strUni[0], -1, &strMulti[0], len, NULL, NULL );
// 	strDefCNBoard.Format(_T("%s%d"),strMulti.c_str(),nKey);

// 	CStringW utf16;
// 	len = MultiByteToWideChar(CP_UTF8, 0, str, -1, NULL, 0);
// 	if (len>1)
// 	{
// 		wchar_t *ptr = utf16.GetBuffer(len-1);
// 		if (ptr){
// 			MultiByteToWideChar(CP_UTF8, 0, str, -1, ptr, len);
// 		}
// 		utf16.ReleaseBuffer(); 
// 	}
// 
// 	CStringA utf8;
// 	int len = WideCharToMultiByte(CP_UTF8, 0, str, -1, NULL, 0, 0, 0);
// 	if (len>1)
// 	{
// 		char *ptr = utf8.GetBuffer(len-1);
// 		if (ptr)
// 			WideCharToMultiByte(CP_UTF8, 0, str, -1, ptr, len, 0, 0);
// 		utf8.ReleaseBuffer();
// 	}
// 	

	
//  	CStringW utf16 = L"汉字 / 漢字";
//  	CStringA utf8 = CW2A(utf16, CP_UTF8);
//  	CStringW copy = CA2W(utf8, CP_UTF8);
	
//	str = StringToChar(_T("追加点检者"));
	 

	CString strKRBoard = _T("");
	CString strCNBoard = _T(""); 
	strKRBoard = m_pIniRecipe->read(_T("TITLE"),strKRkey,strDefKRBoard);
	strCNBoard = m_pIniRecipe->read(_T("TITLE"),strCNkey,strDefCNBoard);
 
 	GetDlgItem(IDC_EDIT_KR_BOARD)->SetWindowText(strKRBoard);
 	GetDlgItem(IDC_EDIT_CN_BOARD)->SetWindowText(strCNBoard);

// 	CEdit* pCtrEdit = (CEdit*)this->GetDlgItem(IDC_EDIT_KR_BOARD);
// 	CWnd* editWnd = CWnd::FromHandle(pCtrEdit);
//	SetWindowText(pCtrEdit->GetSafeHwnd(),str);

	
	return TRUE;
}

BOOL CDigTitleBoard::SafetyDataSave(int nKey,CString strKr,CString strCn)
{
	CString strKRkey(_T(""));CString strCNkey(_T(""));
	strKRkey.Format(_T("BOARD_KR_%d"),nKey);
	strCNkey.Format(_T("BOARD_CN_%d"),nKey);

	m_pIniRecipe->write(_T("TITLE"),strKRkey,strKr);
	m_pIniRecipe->write(_T("TITLE"),strCNkey,strCn);

	return TRUE;
}

char* CDigTitleBoard::StringToChar(CString str)
{
	char *szStr = NULL;
#if defined(UNICODE) || defined(_UNICODE)
	int nLen = str.GetLength() + 1;
	TCHAR *tszTemp = NULL;
	tszTemp = new TCHAR[nLen];
	memset(tszTemp, 0x00, nLen * sizeof(TCHAR));
	_tcscpy_s(tszTemp, nLen, str);
	// Get size (실제사용되는바이트사이즈)
	int nSize = WideCharToMultiByte(CP_ACP, 0, tszTemp, -1, NULL, NULL, NULL, NULL);
	szStr = new char[nSize];
	memset(szStr, 0x00, nSize);
	WideCharToMultiByte(CP_ACP, 0, tszTemp, -1, szStr, nSize, NULL, NULL);
	if(tszTemp)
	{
		delete [] tszTemp;
		tszTemp = NULL;
	}
#else
// 	int nLen = str.GetLength() + 1;
// 	szStr = new char[nLen];
// 	memset(szStr, 0x00, nLen);
// 	strcpy(szStr, str);
#endif
	return szStr;
}
BOOL CDigTitleBoard::OnEraseBkgnd(CDC* pDC)
{
	CRect rect;
	GetClientRect(rect);
	pDC->FillSolidRect(rect, RGB(183,240,200));

	/*return CDialog::OnEraseBkgnd(pDC);*/
	return TRUE;
}

HBRUSH CDigTitleBoard::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	if (nCtlColor == CTLCOLOR_STATIC)
	{
		pDC->SetBkMode(TRANSPARENT);
		hbr = (HBRUSH)GetStockObject(NULL_BRUSH);
	}
	return hbr;
}
void CDigTitleBoard::OnBnClickedCancel()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	OnCancel();
}
