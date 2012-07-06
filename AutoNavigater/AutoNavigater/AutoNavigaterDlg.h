
// AutoNavigaterDlg.h : 头文件
//

#pragma once
#include "afxwin.h"
#include "LyPoint.h"
#include "LyLink.h"
#include "LyPath.h"
#include "WebView.h"


// CAutoNavigaterDlg 对话框
class CAutoNavigaterDlg : public CDialogEx
{
// 构造
public:
	CAutoNavigaterDlg(CWnd* pParent = NULL);	// 标准构造函数
	WebView m_map_web;

// 对话框数据
	enum { IDD = IDD_AUTONAVIGATER_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton4();
	afx_msg void OnBnClickedButton8();
	afx_msg void OnBnClickedButton9();
	afx_msg void OnBnClickedButton13();
	afx_msg void OnBnClickedButton12();
	afx_msg void OnBnClickedButton14();

	CString getDlg1InputName();

	afx_msg void OnEnChangeEdit9();

//	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	

	HBITMAP m_hBmp;

	BOOL m_mouseMove;
	int m_pathNum;
	int m_linkNum;
	int m_pointNum;

	CString m_mapName;
	CString m_mapFileName;

	CListBox m_pathList;
	CListBox m_linkList;
	CListBox m_pointList;

	LyPath m_pathArray[10];
	LyLink m_linkArray[100];
	LyPoint m_pointArray[100];

	int coordX;
	int coordY;

	int saveID[2];
	int flagWithID;

	CString ScanFileRead(int,int);
	CString ScanFileWrite(void);

	void drawMapWithoutScanFile(void);
	void DrawMap(void);
	void DrawAllPoint();
	void DrawPoint(int,int);
	void DrawLink(void);

	void loadFileData(void);

	void infor(void); //将信息显示在窗体上
//	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMove(int x, int y);
	afx_msg void OnSize(UINT nType, int cx, int cy);

	afx_msg void OnLbnSelchangeList2();
	CStatic m_background;
	CButton m_button1;
	CButton m_button2;
	CButton m_inButton;
	CButton m_outButton;
	CButton m_takePhoto;
	CStatic m_background2;
	CButton m_googleMap;
	afx_msg void OnBnClickedButton11();
	afx_msg void OnBnClickedButton10();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnBnClickedButton6();
	afx_msg void OnBnClickedButton15();
	afx_msg void OnBnClickedButton7();
//	bool isWeb;
private:
	bool isWeb;
public:
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
//	afx_msg void OnLbnSetfocusList3();
//	afx_msg void OnLbnDblclkList3();
//	afx_msg void OnLbnSetfocusList3();
private:
	bool isMapLoaded;
};
