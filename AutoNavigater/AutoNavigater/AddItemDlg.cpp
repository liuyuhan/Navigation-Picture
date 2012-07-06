// AddItemDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "AutoNavigater.h"
#include "AddItemDlg.h"
#include "afxdialogex.h"


// AddItemDlg 对话框

IMPLEMENT_DYNAMIC(AddItemDlg, CDialogEx)

AddItemDlg::AddItemDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(AddItemDlg::IDD, pParent)
{
}

AddItemDlg::~AddItemDlg()
{
}

void AddItemDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATIC1, m_labelName);
	DDX_Control(pDX, IDC_EDIT1, m_edit);
}


BEGIN_MESSAGE_MAP(AddItemDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &AddItemDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &AddItemDlg::OnBnClickedCancel)
END_MESSAGE_MAP()


// AddItemDlg 消息处理程序


void AddItemDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	GetDlgItem(IDC_EDIT1)-> GetWindowText(m_inputName);
	flag = 1;
	CDialogEx::OnOK();
}


void AddItemDlg::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	flag = 0;
	CDialogEx::OnCancel();
}
