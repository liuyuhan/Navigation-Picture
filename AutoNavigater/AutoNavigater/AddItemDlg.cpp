// AddItemDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "AutoNavigater.h"
#include "AddItemDlg.h"
#include "afxdialogex.h"


// AddItemDlg �Ի���

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


// AddItemDlg ��Ϣ�������


void AddItemDlg::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	GetDlgItem(IDC_EDIT1)-> GetWindowText(m_inputName);
	flag = 1;
	CDialogEx::OnOK();
}


void AddItemDlg::OnBnClickedCancel()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	flag = 0;
	CDialogEx::OnCancel();
}
