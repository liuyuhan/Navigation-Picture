#pragma once
#include "afxwin.h"


// AddItemDlg �Ի���

class AddItemDlg : public CDialogEx
{
	DECLARE_DYNAMIC(AddItemDlg)

public:
	AddItemDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~AddItemDlg();

// �Ի�������
	enum { IDD = IDD_DIALOG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CStatic m_labelName;
	CEdit m_edit;
	CString m_inputName;

	int flag;
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
};
