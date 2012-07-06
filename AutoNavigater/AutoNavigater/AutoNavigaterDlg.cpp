
// AutoNavigaterDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "AutoNavigater.h"
#include "AutoNavigaterDlg.h"
#include "afxdialogex.h"
#include "LyPoint.h"
#include "LyLink.h"
#include "LyPath.h"
#include "AddItemDlg.h"
#include <math.h>
#define TRUE 1
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

const int STARTX = 240,STARTY = 90;
const int WIDTH = 745,HEIGHT = 575;
const int RADIUS = 5;
const int r = 135,g = 6,b = 226;
const int changeR = 8,changeG = 255,changeB = 2;
static int pointID;

// CAutoNavigaterDlg �Ի���

CAutoNavigaterDlg::CAutoNavigaterDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CAutoNavigaterDlg::IDD, pParent)
	, m_mapName(_T(""))
	, m_mapFileName(_T(""))
	, isWeb(false)
	, isMapLoaded(false)
	, m_pathNum(0)
	, flagWithID(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CAutoNavigaterDlg::DoDataExchange(CDataExchange* pDX)
{
	//CDialogEx::DoDataExchange(pDX);
	//DDX_Control(pDX, ID_Map, map);
	DDX_Control(pDX, IDC_LIST1, m_pathList);
	DDX_Control(pDX, IDC_LIST2, m_linkList);
	DDX_Control(pDX, IDC_LIST3, m_pointList);

	DDX_Control(pDX, IDC_STATIC_PIC1, m_background);
	DDX_Control(pDX, IDC_BUTTON1, m_button1);
	DDX_Control(pDX, IDC_BUTTON2, m_button2);
	DDX_Control(pDX, IDC_BUTTON3, m_inButton);
	DDX_Control(pDX, IDC_BUTTON4, m_outButton);
	DDX_Control(pDX, IDC_BUTTON7, m_takePhoto);
	DDX_Control(pDX, IDC_STATIC_PIC2, m_background2);
	DDX_Control(pDX, IDC_BUTTON15, m_googleMap);
}

BEGIN_MESSAGE_MAP(CAutoNavigaterDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CAutoNavigaterDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CAutoNavigaterDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CAutoNavigaterDlg::OnBnClickedButton3)
	ON_EN_CHANGE(IDC_EDIT9, &CAutoNavigaterDlg::OnEnChangeEdit9)
//	ON_WM_LBUTTONDOWN()
	//ON_STN_CLICKED(ID_Map, &CAutoNavigaterDlg::OnStnClickedMap)
	ON_BN_CLICKED(IDC_BUTTON4, &CAutoNavigaterDlg::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON9, &CAutoNavigaterDlg::OnBnClickedButton9)
	ON_BN_CLICKED(IDC_BUTTON13, &CAutoNavigaterDlg::OnBnClickedButton13)
	ON_BN_CLICKED(IDC_BUTTON8, &CAutoNavigaterDlg::OnBnClickedButton8)
	ON_BN_CLICKED(IDC_BUTTON14, &CAutoNavigaterDlg::OnBnClickedButton14)
	ON_BN_CLICKED(IDC_BUTTON12, &CAutoNavigaterDlg::OnBnClickedButton12)
//	ON_WM_LBUTTONUP()
	ON_WM_MOVE()
	ON_WM_SIZE()
	ON_LBN_SELCHANGE(IDC_LIST2, &CAutoNavigaterDlg::OnLbnSelchangeList2)
	ON_BN_CLICKED(IDC_BUTTON11, &CAutoNavigaterDlg::OnBnClickedButton11)
	ON_BN_CLICKED(IDC_BUTTON10, &CAutoNavigaterDlg::OnBnClickedButton10)
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_BN_CLICKED(IDC_BUTTON6, &CAutoNavigaterDlg::OnBnClickedButton6)
	ON_BN_CLICKED(IDC_BUTTON15, &CAutoNavigaterDlg::OnBnClickedButton15)
	ON_BN_CLICKED(IDC_BUTTON7, &CAutoNavigaterDlg::OnBnClickedButton7)
	ON_WM_RBUTTONDOWN()
//	ON_LBN_SETFOCUS(IDC_LIST3, &CAutoNavigaterDlg::OnLbnSetfocusList3)
//ON_LBN_DBLCLK(IDC_LIST3, &CAutoNavigaterDlg::OnLbnDblclkList3)
//ON_LBN_SETFOCUS(IDC_LIST3, &CAutoNavigaterDlg::OnLbnSetfocusList3)
END_MESSAGE_MAP()


// CAutoNavigaterDlg ��Ϣ�������

BOOL CAutoNavigaterDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��


	flagWithID = 0;

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	HBITMAP   bg;   
	bg = (HBITMAP)::LoadImage(   
	NULL,   
	"image\\background.bmp",                           // ͼƬȫ·��  
	IMAGE_BITMAP,                          // ͼƬ��ʽ  
	0,0,   
	LR_LOADFROMFILE|LR_CREATEDIBSECTION);  

	

	HBITMAP   bg2;   
	bg2 = (HBITMAP)::LoadImage(   
	NULL,   
	"image\\background2.bmp",                           // ͼƬȫ·��  
	IMAGE_BITMAP,                          // ͼƬ��ʽ  
	0,0,   
	LR_LOADFROMFILE|LR_CREATEDIBSECTION);  



	HBITMAP   searchPic;   
	searchPic = (HBITMAP)::LoadImage(   
	NULL,   
	"image\\button1.bmp",                           // ͼƬȫ·��  
	IMAGE_BITMAP,                          // ͼƬ��ʽ  
	0,0,   
	LR_LOADFROMFILE|LR_CREATEDIBSECTION);  

	HBITMAP   inPic;   
	inPic = (HBITMAP)::LoadImage(   
	NULL,   
	"image\\in.bmp",                           // ͼƬȫ·��  
	IMAGE_BITMAP,                          // ͼƬ��ʽ  
	0,0,   
	LR_LOADFROMFILE|LR_CREATEDIBSECTION);  

	HBITMAP   outPic;   
	outPic = (HBITMAP)::LoadImage(   
	NULL,   
	"image\\out.bmp",                           // ͼƬȫ·��  
	IMAGE_BITMAP,                          // ͼƬ��ʽ  
	0,0,   
	LR_LOADFROMFILE|LR_CREATEDIBSECTION);  

	HBITMAP   photoPic;   
	photoPic = (HBITMAP)::LoadImage(   
	NULL,   
	"image\\photo.bmp",                           // ͼƬȫ·��  
	IMAGE_BITMAP,                          // ͼƬ��ʽ  
	0,0,   
	LR_LOADFROMFILE|LR_CREATEDIBSECTION);  

	HBITMAP   googleMap;   
	googleMap = (HBITMAP)::LoadImage(   
	NULL,   
	"image\\googleMap.bmp",                           // ͼƬȫ·��  
	IMAGE_BITMAP,                          // ͼƬ��ʽ  
	0,0,   
	LR_LOADFROMFILE|LR_CREATEDIBSECTION); 

	m_background.SetBitmap(bg);
	m_background2.SetBitmap(bg2);
	m_button1.SetBitmap(searchPic);
	m_button2.SetBitmap(searchPic);
	m_inButton.SetBitmap(inPic);
	m_outButton.SetBitmap(outPic);
	m_takePhoto.SetBitmap(photoPic);
	m_googleMap.SetBitmap(googleMap);

	isWeb = false;

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CAutoNavigaterDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CAutoNavigaterDlg::OnMove(int x, int y)
{
	CDialogEx::OnMove(x, y);

	// TODO: �ڴ˴������Ϣ����������

	drawMapWithoutScanFile();
	DrawAllPoint();
	DrawLink();
}


void CAutoNavigaterDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	// TODO: �ڴ˴������Ϣ����������

	drawMapWithoutScanFile();
	DrawAllPoint();
	DrawLink();
}


void CAutoNavigaterDlg::OnEnChangeEdit9()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}


// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CAutoNavigaterDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CRect rect; 
        CPaintDC dc(this); 
        GetClientRect(rect); 
        dc.FillSolidRect(rect,RGB(247,247,247));

		CDC	*pDC = GetDC();
		CRect rc(STARTX, STARTY, STARTX+WIDTH, STARTY+HEIGHT);		//����һ������
		CBrush brush(RGB(50, 50, 50));							//����һ����ɫ�Ļ�ˢ
		pDC->FrameRect(rc, &brush);							//���ƾ��α߿�
		CDialogEx::OnPaint();

		DrawMap();

	


	}
}

void CAutoNavigaterDlg::drawMapWithoutScanFile(){
	m_hBmp=((HBITMAP)LoadImage(NULL, m_mapFileName, IMAGE_BITMAP,0, 0, LR_LOADFROMFILE));
	OnPaint();
}

void CAutoNavigaterDlg::DrawMap(void)
{
	if(m_hBmp != NULL)
		{
			CDC	*pDC = GetDC();
			CBitmap bmp;										//����һ��λͼ����
			bmp.Attach(m_hBmp);								//��λͼ���������λͼ������
			CDC memDC;										//����һ���豸������
			memDC.CreateCompatibleDC(pDC);					//�������ݵ��豸������
			memDC.SelectObject(&bmp);							//ѡ��λͼ����
			BITMAP BitInfo;									//����λͼ�ṹ
			bmp.GetBitmap(&BitInfo);								//��ȡλͼ��Ϣ
			int x = BitInfo.bmWidth;								//��ȡλͼ���
			int y = BitInfo.bmHeight;								//��ȡλͼ�߶�
		
			CRect rc(STARTX, STARTY, STARTX+WIDTH, STARTY+HEIGHT);		//����һ������
			CBrush brush(RGB(0, 0, 0));							//����һ����ɫ�Ļ�ˢ
			pDC->FrameRect(rc, &brush);							//���ƾ��α߿�
			//rc.OffsetRect(240, 0);									//�ƶ�����
			pDC->StretchBlt(rc.left, rc.top, rc.Width(), rc.Height(), &memDC, 0, 0, x, y, SRCCOPY);
			pDC->FrameRect(rc,& brush);		
			brush.DeleteObject();								//�ͷŻ�ˢ����
			memDC.DeleteDC();		
			
			//�ͷ��豸������
			bmp.DeleteObject();									//�ͷ�λͼ����
			CDialogEx::OnPaint();				
		}
}


void CAutoNavigaterDlg::DrawAllPoint(){
	int flag = 0;
	for(int i = 0;i<m_pointNum;i++){
		DrawPoint(i,flag);
	}
	
}


void CAutoNavigaterDlg::DrawPoint(int id,int flag){
	CClientDC dc(this);
	int x = m_pointArray[id].getPointX(),y = m_pointArray[id].getPointY();
	CBrush brush,*oldBrush;
	if(flag == 0){
		brush.CreateSolidBrush(RGB(r,g,b));
	}
	else{
		brush.CreateSolidBrush(RGB(changeR,changeG,changeB));
	}
	oldBrush = dc.SelectObject(&brush);
	dc.Ellipse(STARTX+x-RADIUS,STARTY+y-RADIUS,STARTX+x+RADIUS,STARTY+y+RADIUS);
}

void CAutoNavigaterDlg::DrawLink(){
	for(int i = 0;i<m_linkNum;i++){
		CClientDC dc(this);
		int x1 = m_linkArray[i].getLinkXPoint().getPointX()+STARTX;
		int y1 = m_linkArray[i].getLinkXPoint().getPointY()+STARTY;
		int x2 = m_linkArray[i].getLinkYPoint().getPointX()+STARTX;
		int y2 = m_linkArray[i].getLinkYPoint().getPointY()+STARTY;
		CBrush brush,*oldBrush;
		brush.CreateSolidBrush(RGB(5,244,16));
		oldBrush = dc.SelectObject(&brush);
		dc.MoveTo(x1,y1);
		dc.LineTo(x2,y2);
	}
}


CString CAutoNavigaterDlg::ScanFileRead(int IDNumber,int flag)
{	
	CFileDialog* fileDlg;
	if(flag)
		fileDlg = new CFileDialog(TRUE,0,0, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT|OFN_ALLOWMULTISELECT, _T("Bitmap (*.bmp)|*.bmp||"),AfxGetMainWnd());
	else
		fileDlg = new CFileDialog(TRUE,0,0, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT|OFN_ALLOWMULTISELECT, _T("Route Description Files (*.txt)|*.txt||"),AfxGetMainWnd());
	//CFileDialog fileDlg(TRUE,0,0, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT|OFN_ALLOWMULTISELECT, _T("AllFiles (*.*)|*.*||"),AfxGetMainWnd()); 
	if(fileDlg->DoModal() == IDOK) 
	{ 
		CString fileName; 
		CFile file; 
		file.Open(fileDlg->GetPathName(),CFile::modeReadWrite); 
		//file.Read(strBuffer.GetBuffer(file.GetLength()),(UINT)file.GetLength()); 
		fileName=fileDlg->GetPathName();
		if(flag){

			int index1 = -1,index2 = -1,i = -1;
			m_mapFileName = fileName;
			i = fileName.Find("\\",0);
			while(i!=-1){
				index1 = i;
				i = fileName.Find("\\",i+1);
			}
			index2 = fileName.Find(".",0);
			m_mapName = fileName.Mid(index1+1,index2-index1-1);
			GetDlgItem( IDNumber )->SetWindowText(m_mapName); 
		}
		else{
			GetDlgItem( IDNumber )->SetWindowText(fileName); 
		}
		file.Close(); 
		return fileName;
  
	}
	else 
		return NULL;
}


CString CAutoNavigaterDlg::ScanFileWrite(){
	CFileDialog dlg(FALSE,"txt",NULL,NULL,"txt file(*.txt)|*.txt|",AfxGetMainWnd());

	if (dlg.DoModal()==IDOK)
	{
		return dlg.GetPathName();
	}
	else
		return NULL;
}


void CAutoNavigaterDlg::loadFileData(){
	//pointID = 0;
	CString fileDataName;
	CEdit *edit;
	edit = (CEdit*)GetDlgItem(IDC_EDIT1);
	edit->GetWindowTextA(fileDataName);
	
	CFile mFile;
	CFileException e;

	CString strTemp;

	if(mFile.Open(fileDataName,CFile::modeRead,&e) == 0)
		return;
	CArchive ar(&mFile,CArchive::load);
	ar.ReadString(strTemp);
	if(strTemp != m_mapName){
		MessageBox(_T("��ͼ����ƥ�䣬����������Ч��"));	
	}
	else{
		//Test mapName:
		//MessageBox("mapName:"+m_mapName);
		int i,k = 0,x = 0,y = 0;
		CString roadNameTemp,nodeTemp;
		ar.ReadString(strTemp);
		m_pathNum = (int)_tcstod(strTemp.GetBuffer(0), NULL);

		for(int roadCount=0;roadCount<m_pathNum;roadCount++){
			ar.ReadString(strTemp);									//��n����·���ƺ͵�·���������
			i=strTemp.Find(" ",0);
			roadNameTemp=strTemp.Mid(0,i);					//��·��
			//Test roadNameTemp
			//MessageBox(roadNameTemp);
			strTemp=strTemp.Mid(i,strTemp.GetLength()-i);			//��n����·�Ľ����
			i=_tcstod(strTemp.GetBuffer(0), NULL);					//ת����double��

			m_pathArray[roadCount] = LyPath(roadNameTemp,i);		//��ʼ��LyPath
			/*
			//Test PathName:
			MessageBox("PathName:"+m_pathArray[roadCount].getPathName());     
			 //���Ե�����
			CString testString;
			testString.Format(_T("%d"),m_pathArray[roadCount].getPointNum());
			MessageBox("��������"+testString);
			*/

			for(int j=0;j<i;j++){									//��n����·���н�������
				ar.ReadString(strTemp);
				k=strTemp.Find(" ",0);

				nodeTemp = strTemp.Mid(0,k);
				x=_tcstod(nodeTemp.GetBuffer(0), NULL);

				nodeTemp = strTemp.Mid(k,strTemp.GetLength()-k);
				y =_tcstod(nodeTemp.GetBuffer(0), NULL);
				
				m_pointArray[pointID] = LyPoint(pointID,x,y,roadNameTemp);
				pointID++;

				/*
				//Test point x,y,id,name
				CString testString1,testString2,testString3;
				testString1.Format(_T("%d"),m_pointArray[pointID].getPointX());
				testString2.Format(_T("%d"),m_pointArray[pointID].getPointY());
				testString3.Format(_T("%d"),m_pointArray[pointID].getPointID());
				MessageBox("id:  "+testString3+"x:  "+ testString1+"y:  "+testString2+"name:  "+m_pointArray[pointID].getPointName());
				*/

				/*
				roadNameTemp=strTemp.Mid(0,i);					//��·��
				i=_tcstod(strTemp.GetBuffer(0), NULL);					//ת����double��
				strTemp=strTemp.Mid(i,strTemp.GetLength()-i);			//��n����·�Ľ����
				i=_tcstod(strTemp.GetBuffer(0), NULL);					//ת����double��
				*/
				}
			}
		m_pointNum = pointID;
		ar.ReadString(strTemp);
		m_linkNum = _tcstod(strTemp.GetBuffer(0),NULL);
		CString id1Str,id2Str;
		int m,id1,id2;
		for(int l = 0 ; l < m_linkNum ; l++){
			ar.ReadString(strTemp);
			m=strTemp.Find(" ",0);
			id1Str=strTemp.Mid(0,m);					
			id2Str=strTemp.Mid(m,strTemp.GetLength()-m);			
			id1=_tcstod(id1Str.GetBuffer(0), NULL);		
			id2=_tcstod(id2Str.GetBuffer(0), NULL);	
			m_linkArray[l] = LyLink(l,m_pointArray[id1],m_pointArray[id2]);

			/*
			//Test link id
			strTemp.Format(_T("%d"),m_linkArray[l].getLinkXPoint());
			MessageBox("link:"+strTemp+"  "+"id1Str:"+id1Str+"  "+"id2Str" + id2Str);
			*/
		}

	}
	ar.Close();
	mFile.Close();
	infor();
}


/*
	����Ϣ��ʾ�ڴ�����
*/
void CAutoNavigaterDlg::infor(void)
{
	CString strTemp,xPoint,yPoint;

	m_pathList.ResetContent();
	for(int i=0;i<m_pathNum;i++)
	{
		m_pathList.AddString(m_pathArray[i].getPathName());
	}
	
	m_linkList.ResetContent();
	for(int j=0;j<m_linkNum;j++)
	{
		strTemp.Format(_T("%d"),m_linkArray[j].getLinkID());
		m_linkList.AddString(_T("Link:ID")+strTemp);
	}

	m_pointList.ResetContent();
	for(int k=0;k<m_pointNum;k++)
	{
		xPoint.Format(_T("%d"),m_pointArray[k].getPointX());
		yPoint.Format(_T("%d"),m_pointArray[k].getPointY());
		strTemp.Format(_T("%d"),m_pointArray[k].getPointID());
			m_pointList.AddString(_T("Node:ID")+strTemp+_T(" ("+xPoint+_T(" ")+yPoint+_T(")")));
	}
}


/*
	��������ļ�����
*/
void CAutoNavigaterDlg::OnBnClickedButton1()
{
	// TODO: Add your control notification handler code here
	
	if(isMapLoaded == false)
	{
		MessageBoxA(_T("���ȼ��ص�ͼ"));
		return;
	}
	
	ScanFileRead(IDC_EDIT1,0);
}


/*
	�����ͼ����
*/
void CAutoNavigaterDlg::OnBnClickedButton2()
{
	CString fileName;
	fileName = ScanFileRead(IDC_EDIT9,1);
	
	if(fileName!="")
	{
		drawMapWithoutScanFile();
		this->GetDlgItem(IDC_HTMLVIEW)->ShowWindow(false);
		isWeb = false;
		isMapLoaded = true;
	}
	//this->GetDlgItem(IDC_HTMLVIEW)->ShowWindow(false);
	//isWeb = false;
}


/*
	�������ݰ���
*/
void CAutoNavigaterDlg::OnBnClickedButton3()
{
	pointID = 0;
	loadFileData();
	drawMapWithoutScanFile();
	DrawAllPoint();
	DrawLink();
}


/*
	�������ݰ���
*/
void CAutoNavigaterDlg::OnBnClickedButton4()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	CString outputDataFileName;
	outputDataFileName = ScanFileWrite();

	CFile mFile;
	//mFile.Open(outputDataFileName,CFile::modeCreate|CFile::modeWrite);
	if(mFile.Open(outputDataFileName,CFile::modeCreate|CFile::modeWrite)==0)  //bug
		return;	

	CArchive ar(&mFile,CArchive::store);

	ar.WriteString(m_mapName + "\r\n");		//output mapName
	CString tempString1,tempString2;
	tempString1.Format("%d",m_pathNum);		//output mapNum
	ar.WriteString(tempString1 + "\r\n");

	for(int i = 0;i<m_pathNum;i++)
	{
		tempString1.Format("%d",m_pathArray[i].getPointNum());
		ar.WriteString(m_pathArray[i].getPathName() + " " +tempString1 + "\r\n");  //output pathName and nodeNum
		for(int j = 0;j<m_pointNum;j++)
		{	
			if(m_pointArray[j].getPointName() == m_pathArray[i].getPathName())
			{
				tempString1.Format("%d",m_pointArray[j].getPointX());
				tempString2.Format("%d",m_pointArray[j].getPointY());
				ar.WriteString(tempString1 + " " + tempString2 + "\r\n");
			}
		}
	}

	tempString1.Format("%d",m_linkNum);
	ar.WriteString(tempString1 + "\r\n");

	for(int i = 0;i<m_linkNum;i++)
	{
		tempString1.Format("%d",m_linkArray[i].getLinkXPoint().getPointID());
		tempString2.Format("%d",m_linkArray[i].getLinkYPoint().getPointID());
		ar.WriteString(tempString1 + " " + tempString2 + "\r\n");
	}

	ar.Close();
	mFile.Close();
}


/*
	��ʾ����¼�
*/
void CAutoNavigaterDlg::OnBnClickedButton9()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	int i=m_pathList.GetCurSel();
	CString text,strTemp;

	if(i==-1)      //bug
		return;

    m_pathList.GetText(i, text);

	m_pointList.ResetContent();
	for(int j=0;j<m_pointNum;j++)
	{
		if(m_pointArray[j].getPointName()==text)
		{
			strTemp.Format(_T("%d"),m_pointArray[j].getPointID());
			m_pointList.AddString(_T("Node:ID")+strTemp);
		}

	}
}

/*
	��ʾlink�¼�
*/
void CAutoNavigaterDlg::OnBnClickedButton13()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	int m, n;
	int i=m_pathList.GetCurSel();
	CString text,strTemp;

	if(i==-1)      //bug
		return;

    m_pathList.GetText(i, text);

	m_linkList.ResetContent();
	for(int j=0;j<m_linkNum;j++)
	{
		if(m_linkArray[j].getLinkYPoint().getPointName()==text)
		{
			strTemp.Format(_T("%d"),m_linkArray[j].getLinkID());
			m_linkList.AddString(_T("Link:ID")+strTemp);
		}
	}
}


/*
	ɾ����·����
*/
void CAutoNavigaterDlg::OnBnClickedButton8()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	int m, n;												//ɾ����·
	int sel=m_pathList.GetCurSel();
	CString text,xPoint,yPoint;

	if(sel==-1)
		return;

    m_pathList.GetText(sel, text);
	//MessageBox(text);
	CString strTemp;
	strTemp.Format(_T("%d"),sel);

	if(sel!=m_pathNum-1){
		for(int j=sel;j<m_pathNum-1;j++)
		{
			m_pathArray[j]=m_pathArray[j+1];
		}
	}

	m_pathNum--;
	
	m_pathList.ResetContent();
	for(int i=0;i<m_pathNum;i++)
	{
		m_pathList.AddString(m_pathArray[i].getPathName());
	}
	


	m_linkList.ResetContent();						//ɾ��link
	int x=0;
	if(m_pathNum!=0){
		for(int j=0;j<m_linkNum;j++)
		{
			if(strcmp(m_linkArray[j].getLinkYPoint().getPointName(),text)!=0)
			{
				m_linkArray[x]=m_linkArray[j];
				x++;
			}
		}
		m_linkNum=x;
	}
	else{
		m_linkNum=0;
	}
	
	for(int i=0;i<m_linkNum;i++)
	{
		strTemp.Format(_T("%d"),m_linkArray[i].getLinkID());
		m_linkList.AddString(_T("Link:ID")+strTemp);
	}
		
	int y=0;
	m_pointList.ResetContent();										//ɾ�����
	if(m_pathNum!=0){	
		for(int j=0;j<m_pointNum;j++)
		{
			if(strcmp(m_pointArray[j].getPointName(),text)!=0)
			{
				m_pointArray[y]=m_pointArray[j];
				y++;
			}
		}
		m_pointNum=y;
	}
	else{
		m_pointNum=0;
	}

	for(int i=0;i<m_pointNum;i++)
	{
		xPoint.Format(_T("%d"),m_pointArray[i].getPointX());
		yPoint.Format(_T("%d"),m_pointArray[i].getPointY());
		strTemp.Format(_T("%d"),m_pointArray[i].getPointID());
		m_pointList.AddString(_T("Node:ID")+strTemp+_T(" ("+xPoint+_T(" ")+yPoint+_T(")")));
	}

	drawMapWithoutScanFile();
	DrawAllPoint();
	DrawLink();
}


/*
	ɾ��link����
*/
void CAutoNavigaterDlg::OnBnClickedButton14()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	CString text,strTemp;						//ɾ�����
	int sel=m_linkList.GetCurSel();
	int x=0;

	if(sel==-1)
		return;

	if(sel!=m_linkNum-1)
	{
		for(int j=sel;j<m_linkNum-1;j++)
		{
			m_linkArray[j]=m_linkArray[j+1];
		}
	}

	m_linkNum--;
	m_linkList.ResetContent();				
	for(int i=0;i<m_linkNum;i++)
	{
		strTemp.Format(_T("%d"),m_linkArray[i].getLinkID());
		m_linkList.AddString(_T("Link:ID")+strTemp);
	}
	drawMapWithoutScanFile();
	DrawAllPoint();
	DrawLink();
}



/*
	ɾ����㰴��
*/
void CAutoNavigaterDlg::OnBnClickedButton12()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	CString text,strTemp,xPoint,yPoint;						//ɾ�����
	int sel=m_pointList.GetCurSel();
	int x=0;
	int selID=m_pointArray[sel].getPointID();
   // m_pointList.GetText(sel, text);
	//if(sel==0)
	//	return;

	if(sel!=m_pointNum-1){
		for(int j=sel;j<m_pointNum-1;j++)
		{
			m_pointArray[j]=m_pointArray[j+1];
		}
	}

	m_pointNum--;
	
	m_pointList.ResetContent();
	for(int i=0;i<m_pointNum;i++)
	{
		xPoint.Format(_T("%d"),m_pointArray[i].getPointX());
		yPoint.Format(_T("%d"),m_pointArray[i].getPointY());
		strTemp.Format(_T("%d"),m_pointArray[i].getPointID());
		m_pointList.AddString(_T("Node:ID")+strTemp+_T(" ("+xPoint+_T(" ")+yPoint+_T(")")));
	}

	m_linkList.ResetContent();						//ɾ��link
	
	if(m_pathNum!=0){
		for(int j=0;j<m_linkNum;j++)
		{
			//if(strcmp(m_linkArray[j].getLinkYPoint().getPointName(),text)!=0)
			if(m_linkArray[j].getLinkXPoint().getPointID()!=selID && m_linkArray[j].getLinkYPoint().getPointID()!=selID)
			{
				m_linkArray[x]=m_linkArray[j];
				x++;
			}
		}
		m_linkNum=x;
	}
	else{
		m_linkNum=0;
	}
	
	for(int i=0;i<m_linkNum;i++)
	{
		strTemp.Format(_T("%d"),m_linkArray[i].getLinkID());
		m_linkList.AddString(_T("Link:ID")+strTemp);
	}

	drawMapWithoutScanFile();
	DrawAllPoint();
	DrawLink();
}


/*
	��ȡ�������ֶԻ����е�������ֵ
*/
CString CAutoNavigaterDlg::getDlg1InputName(){
	AddItemDlg addItemDlg;
	addItemDlg.DoModal();
	
	CString inputName;
	inputName = addItemDlg.m_inputName;

	if(addItemDlg.flag == 1){
		return inputName;
	}
	else{
		return "";
	}
}


/*
	��갴���¼�
*/
//void CAutoNavigaterDlg::OnLButtonDown(UINT nFlags, CPoint point)
//{
//	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
//
//	/*
//	CString a,b;
//	a.Format(_T("%d"),point.x);
//	b.Format(_T("%d"),point.y);
//	CDialogEx::OnLButtonDown(nFlags, point);
//	MessageBox(a);
//	MessageBox(b);
//	*/
//	m_mouseMove=true;
//	CDialogEx::OnLButtonDown(nFlags, point);
//}



//void CAutoNavigaterDlg::OnLButtonUp(UINT nFlags, CPoint point)
//{
//	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
//	if(m_mouseMove==true)
//	{
//		drawMapWithoutScanFile();
//	}
//	CDialogEx::OnLButtonUp(nFlags, point);
//}



void CAutoNavigaterDlg::OnLbnSelchangeList2()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}


/*
	�����ӽ�㰴��
*/
void CAutoNavigaterDlg::OnBnClickedButton11()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	CString inputName;
	inputName = getDlg1InputName();
	if(inputName!=""){
			if(coordX>=0&&coordY>=0){
			m_pointArray[m_pointNum] = LyPoint(m_pointNum,coordX,coordY,inputName);
			for(int i = 0;i<m_pathNum;i++){
				if(m_pathArray[i].getPathName() == m_pointArray[m_pointNum].getPointName())
					m_pathArray[i].setPointNum(m_pathArray[i].getPointNum()+1);
			}
			m_pointNum++;
			DrawAllPoint();
			infor();
		}
			else{
				MessageBox("��ѡ�㳬����Χ");
			}
	}
	else{
		MessageBox("������������");
	}
}


/*
	�����ӵ�·����
*/
void CAutoNavigaterDlg::OnBnClickedButton10()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	CString inputName;
	inputName = getDlg1InputName();
	if(inputName!=""){
		m_pathArray[m_pathNum] = LyPath(inputName,0);
		m_pathNum++;
		infor();
	}
}


void CAutoNavigaterDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

	CDialogEx::OnLButtonDown(nFlags, point);
	coordX = point.x - STARTX;
	coordY = point.y - STARTY;
}


void CAutoNavigaterDlg::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

	CDialogEx::OnMouseMove(nFlags, point);

	CString string1,string2;
	int x,y;
	x = point.x - STARTX;
	y = point.y - STARTY;
	string1.Format("%d",x);
	string2.Format("%d",y);
	if(x >= 0 && y >= 0 && x <= WIDTH && y <= HEIGHT)
		GetDlgItem(IDC_EDIT7)->SetWindowTextA(string1 + "," + string2);
	else
		GetDlgItem(IDC_EDIT7)->SetWindowTextA("");
}


void CAutoNavigaterDlg::OnBnClickedButton6()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	
	int nCount = m_pointList.GetSelCount(); 
	int node[2];
	int k;
	int index1 = -1,index2 = -1;
	CString Tempbuffer;
	CString str;
	CArray <int,int>   aryListBoxSel;

	aryListBoxSel.SetSize(nCount); 
	m_pointList.GetSelItems(nCount,aryListBoxSel.GetData());   //������б�ѡ�е����� 
	if(nCount == 2){
		for(int i=0;i <nCount;i++) 
		{  
			m_pointList.GetText(aryListBoxSel[i], Tempbuffer);//���ÿ������� 
		
			index1 = Tempbuffer.Find("D",0);
			index2 = Tempbuffer.GetLength();
			str = Tempbuffer.Mid(index1+1,index2);
			node[i]=_tcstod(str.GetBuffer(0), NULL);  //node[0],node[1]�ֱ𴢴��������ID
		} 
		m_linkArray[m_linkNum] = LyLink(m_linkNum,m_pointArray[node[0]],m_pointArray[node[1]]);
		m_linkNum++;
		DrawLink();
	}
	
}


void CAutoNavigaterDlg::OnBnClickedButton15()
{
	if(isWeb == true)
	{
		m_map_web.ShowWindow(true);
		m_map_web.reload();
		return;
	}
	VERIFY(m_map_web.paintView(IDC_HTMLVIEW, this));
	isWeb = true;
	isMapLoaded = false;
}


void CAutoNavigaterDlg::OnBnClickedButton7()
{
	CRect rect;
	this->GetDlgItem(IDC_HTMLVIEW)->GetClientRect(rect);
	rect.left += 240;
	rect.top += 88;
	rect.right += 242;
	rect.bottom += 90;
	m_map_web.mapShot(rect);
}



void CAutoNavigaterDlg::OnRButtonDown(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

	int x,y;
	x = point.x - STARTX;
	y = point.y - STARTY;

	if(flagWithID == 0){
		DrawAllPoint();
	}

	for(int i = 0;i<m_pointNum;i++){
		if(abs(m_pointArray[i].getPointX()-x)<=RADIUS&&abs(m_pointArray[i].getPointY()-y)<=RADIUS){
			saveID[flagWithID] = i;
			flagWithID++;
			flagWithID = flagWithID%2;
			DrawPoint(i,1);
			break;
		}
	}

	if(flagWithID == 0){
		m_linkArray[m_linkNum] = LyLink(m_linkNum,m_pointArray[saveID[0]],m_pointArray[saveID[1]]);
		m_linkNum++;
		CString str1,str2;
		DrawLink();
	}


	CDialogEx::OnRButtonDown(nFlags, point);
}

