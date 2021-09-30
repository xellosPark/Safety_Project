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
		int		m_state;

		_SAFETY_DATA ()
		{
			m_rtPos1 = 0,0,0,0;
			m_rtPos2 = 0,0,0,0;
			m_rtPosBG = 0,0,0,0;
			m_rtPosSelect = 0,0,0,0;
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
	static LRESULT CALLBACK WinKeyHook(int code, WPARAM wparam, LPARAM lparam);			
	//virtual BOOL PreTranslateMessage(MSG* pMsg);
public:
	BOOL SetMainImageCBitmapLoad();
	
	BOOL CheckExistItem(int nKey);

	void GetItemsStateValue(int order, int& nvalue);
	BOOL SetItemsStateValue(int order, int nState);
	
	BOOL SetItemsValue(int order, int nState, CString strKRText, CString strCNText);
	void GetItemsValue( int order, CDlgSafetyView::_SAFETY_DATA& Data );
	
	void ClearMapDataInfo() { m_mapDataInfo.clear(); }
	void AddMapDataInfo(int nkey,const CDlgSafetyView::_SAFETY_DATA& DataInfo);
	void SetTitleBoardView(int index);
	void addButton(int ikey, CButton* createButton);
	void ClearButton();

	HHOOK hook;

	CRect RtCommentButton;
	CRect RtHourButton;
	CRect RtTempButton;
	CRect RtUnlockButton;

	CRect RtDateArea;
	CRect RtCommentArea;
	CRect RtHourArea;
	CRect RtPhoneArea;
	CRect RtContactArea;
	CRect RtWorkerArea;

	CImage m_cImageBG,m_cImageSelect;
	CBitmap *cBitmapBG;
	CBitmap *cBitmapSelect;	
public:
	map<int, _SAFETY_DATA> m_mapDataInfo;
	CStatic m_ctrTex[TYPE_TITLE_MAX][TYPE_TITLE_MIN];
	CStatic m_strText[7];
	CButton m_ctrBnt[TYPE_TITLE_MAX];
	
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct);
	
	map<int, CButton*> m_mapButton;
	CFont m_font,m_font2,m_font3,m_font4,m_font5, m_fontCH;	
	CButton* createCommentButton;
	CButton* createHourButton;
	CButton* createTemporaryButton;
	CButton* createUnlockButton;
protected:
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
public:	

	BOOL InitBoard();
	BOOL LoadBoardData(int index);
	HANDLE GetProcessByName(PCSTR name);
private:
	CIniFile* m_pIniRecipe;
public:
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	void OnPaintInfo();
	afx_msg void OnDestroy();
};
