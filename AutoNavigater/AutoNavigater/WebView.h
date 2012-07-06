#pragma once

#ifdef _WIN32_WCE
#error "Windows CE ��֧�� CHtmlView��"
#endif 

// WebView Html ��ͼ

class WebView : public CHtmlView
{
	DECLARE_DYNCREATE(WebView)

protected:

public:
	WebView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	bool paintView(UINT nID, CWnd* pParent);
	int OnMouseActivate(CWnd* pDesktopWnd, UINT nHitTest, UINT msg);
	void PostNcDestroy(void);
	HRESULT OnGetHostInfo(DOCHOSTUIINFO* pInfo);
	void mapShot(CRect rect);
	void reload(void);
};


