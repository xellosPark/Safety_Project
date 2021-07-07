#pragma once

#ifdef _WIN32_WCE
#error "Windows CE������ CDHtmlDialog�� �������� �ʽ��ϴ�."
#endif 
// CDlgSafetyView ��ȭ �����Դϴ�.

#define TYPE_TITLE_MAX 16


class CDlgSafetyView : public CDialogEx
{
	DECLARE_DYNCREATE(CDlgSafetyView)

public:
	CDlgSafetyView(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CDlgSafetyView();

	struct _SAFETY_DATA
	{
		CRect	m_rtPos1;
		CRect	m_rtPos2;
		CRect	m_rtPosBG;
		CString m_strKRTitle;
		CString m_strCNTitle;
		int		m_state;

		_SAFETY_DATA ()
		{
			m_strKRTitle = "";
			m_strCNTitle = "";
			m_state = 0;
		}
	};

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_DLG_SAFETY};

	enum tSelectType
	{
		SELECT_READY	=0,
		SELECT_ON,
		SELECT_OFF
	};

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.
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
	BOOL CheckExistItem(int nKey);

	void GetItemsStateValue(int order, int& nvalue);
	BOOL SetItemsStateValue(int order, int nState);
	
	BOOL SetItemsValue(int order, int nState, CString strKRText, CString strCNText);
	void GetItemsValue( int order, CDlgSafetyView::_SAFETY_DATA& Data );
	
	void ClearMapDataInfo() { m_mapDataInfo.clear(); }
	void AddMapDataInfo(int nkey,const CDlgSafetyView::_SAFETY_DATA& DataInfo);

public:
	map<int, _SAFETY_DATA> m_mapDataInfo;
	CStatic m_ctrTex[TYPE_TITLE_MAX][2];
	
};
