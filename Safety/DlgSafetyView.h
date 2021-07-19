#pragma once

#ifdef _WIN32_WCE
#error "Windows CE에서는 CDHtmlDialog가 지원되지 않습니다."
#endif 
// CDlgSafetyView 대화 상자입니다.


class CDlgSafetyView : public CDialogEx
{
	DECLARE_DYNCREATE(CDlgSafetyView)

public:
	CDlgSafetyView(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CDlgSafetyView();

	struct _SAFETY_DATA
	{
		CRect	m_rtPos1;
		CRect	m_rtPos2;
		CRect	m_rtPosBG;
		CRect	m_rtPosSelect;
		CString m_strKRTitle;
		CString m_strCNTitle;
		int		m_state;

		_SAFETY_DATA ()
		{
			m_rtPos1 = 0,0,0,0;
			m_rtPos2 = 0,0,0,0;
			m_rtPosBG = 0,0,0,0;
			m_rtPosSelect = 0,0,0,0;
			m_strKRTitle = "";
			m_strCNTitle = "";
			m_state = 0;
		}
	};

// 대화 상자 데이터입니다.
	enum { IDD = IDD_DLG_SAFETY};

	enum tSelectType
	{
		SELECT_READY	=0,
		SELECT_ON,
		SELECT_OFF
	};

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnPaint();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
			
public:
	BOOL SetMainImageLoad();
	BOOL SetMainImageCBitmapLoad();
	BOOL SetCBitmaptoBitmapLoad();
	BOOL CheckExistItem(int nKey);

	BOOL SetBitmaptoCBitmapLoad();
	BOOL SetBitmaptoCBitmapView();
	void GetItemsStateValue(int order, int& nvalue);
	BOOL SetItemsStateValue(int order, int nState);
	
	BOOL SetItemsValue(int order, int nState, CString strKRText, CString strCNText);
	void GetItemsValue( int order, CDlgSafetyView::_SAFETY_DATA& Data );
	
	void ClearMapDataInfo() { m_mapDataInfo.clear(); }
	void AddMapDataInfo(int nkey,const CDlgSafetyView::_SAFETY_DATA& DataInfo);
	void SetTitleBoardView(int index);
	void addButton(int ikey, CButton* createButton);
	void ClearButton();
public:
	map<int, _SAFETY_DATA> m_mapDataInfo;
	CStatic m_ctrTex[TYPE_TITLE_MAX][TYPE_TITLE_MIN];
	CButton m_ctrBnt[TYPE_TITLE_MAX];
	
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	
	map<int, CButton*> m_mapButton;
	CFont m_font;
protected:
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
public:
	afx_msg void OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct);
};
