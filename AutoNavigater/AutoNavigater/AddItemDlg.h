#pragma once
#include "afxwin.h"


// AddItemDlg 对话框

class AddItemDlg : public CDialogEx
{
	DECLARE_DYNAMIC(AddItemDlg)

public:
	AddItemDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~AddItemDlg();

// 对话框数据
	enum { IDD = IDD_DIALOG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CStatic m_labelName;
	CEdit m_edit;
	CString m_inputName;

	int flag;
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
};
