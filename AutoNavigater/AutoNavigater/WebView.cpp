// WebView.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "AutoNavigater.h"
#include "WebView.h"


// WebView

IMPLEMENT_DYNCREATE(WebView, CHtmlView)

WebView::WebView()
{

}

void WebView::DoDataExchange(CDataExchange* pDX)
{
	CHtmlView::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(WebView, CHtmlView)
END_MESSAGE_MAP()


// WebView ���

#ifdef _DEBUG
void WebView::AssertValid() const
{
	CHtmlView::AssertValid();
}

void WebView::Dump(CDumpContext& dc) const
{
	CHtmlView::Dump(dc);
}
#endif //_DEBUG


// WebView ��Ϣ�������


bool WebView::paintView(UINT nID, CWnd* pParent)
{
	CStatic wndStatic; //��̬�ؼ�����
	if(!wndStatic.SubclassDlgItem(nID, pParent))
		return False;
	CRect rc;
	wndStatic.GetWindowRect(&rc);
	pParent->ScreenToClient(&rc);
	wndStatic.DestroyWindow();
	BOOL status = Create(NULL, NULL, (WS_CHILD | WS_VISIBLE), rc, pParent, nID, NULL);
	ModifyStyle(WS_BORDER, 0);
	LoadFromResource(IDR_HTML1);

	TRACE("\d", status);
	return status;
}


int WebView::OnMouseActivate(CWnd* pDesktopWnd, UINT nHitTest, UINT msg)
{
	return CWnd::OnMouseActivate(pDesktopWnd, nHitTest, msg);
}


void WebView::PostNcDestroy(void)
{
}


HRESULT WebView::OnGetHostInfo(DOCHOSTUIINFO* pInfo)
{
	if(pInfo != NULL)
		pInfo->dwFlags |= DOCHOSTUIFLAG_NO3DBORDER;
	return S_OK;
}


void WebView::mapShot(CRect rect)
{
	TRACE("Output test.\n");
	//RECT rc;
	//GetDlgItem(IDC_HTMLVIEW)->GetClientRect(&rc);
	//CRect rect(10, 10, 10, 10);
	//ScreenToClient(rect);
	CBitmap*  m_pBitmap; 	                                                 // �������Ա
	CFrameWnd* pMainFrame = (CFrameWnd*)AfxGetMainWnd();                     // ��ý�ͼ���ڵ�ָ�룬Ĭ��Ϊ�����ڣ����Ը���Ϊ�����Ĵ��ڡ�
   	CPaintDC   dc(pMainFrame); 
	CString filename;
	
	m_pBitmap=new CBitmap;   
	m_pBitmap->CreateCompatibleBitmap(&dc,rect.Width(),rect.Height());   

	CDC   memDC;  
	memDC.CreateCompatibleDC(&dc); 
	CBitmap memBitmap, *oldmemBitmap;                                        // ��������Ļ���ݵ�bitmap
	
    memBitmap.CreateCompatibleBitmap(&dc, rect.Width(),rect.Height());
	
    oldmemBitmap = memDC.SelectObject(&memBitmap);//��memBitmapѡ���ڴ�DC
    memDC.BitBlt(0, 0, rect.Width(),rect.Height(), &dc,rect.left, rect.top, SRCCOPY);  // ����߶ȿ��
	BITMAP bmp;
    memBitmap.GetBitmap(&bmp);                                               // ���λͼ��Ϣ 

	//CFileDialog fileDlg(TRUE,0,0, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT|OFN_ALLOWMULTISELECT, _T("Bitmap (*.bmp)|*.bmp||"),AfxGetMainWnd());
	CFileDialog fileDlg(FALSE,"txt",NULL,NULL,"Bitmap (*.bmp)|*.bmp||",AfxGetMainWnd());

	if(fileDlg.DoModal() == IDOK)
		filename = fileDlg.GetPathName();
	else
		return;

    FILE *fp;

	char* fullpath = new char[filename.GetLength() + 1];
	//strcpy_s(fullpath, (const char*)filename.GetBuffer());
	strcpy(fullpath, (const char*)filename.GetBuffer());

	fopen_s(&fp, fullpath, "w+b");
	
    BITMAPINFOHEADER bih = {0};                                              // λͼ��Ϣͷ
    bih.biBitCount = bmp.bmBitsPixel;                                        // ÿ�������ֽڴ�С
    bih.biCompression = BI_RGB;
    bih.biHeight = bmp.bmHeight;                                             // �߶�
    bih.biPlanes = 1;
    bih.biSize = sizeof(BITMAPINFOHEADER);
    bih.biSizeImage = bmp.bmWidthBytes * bmp.bmHeight;                       // ͼ�����ݴ�С
    bih.biWidth = bmp.bmWidth;                                               // ���
    
    BITMAPFILEHEADER bfh = {0};                                              // λͼ�ļ�ͷ
    bfh.bfOffBits = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);     // ��λͼ���ݵ�ƫ����
    bfh.bfSize = bfh.bfOffBits + bmp.bmWidthBytes * bmp.bmHeight;            // �ļ��ܵĴ�С
    bfh.bfType = (WORD)0x4d42;
    
    fwrite(&bfh, 1, sizeof(BITMAPFILEHEADER), fp);                           //д��λͼ�ļ�ͷ
    
    fwrite(&bih, 1, sizeof(BITMAPINFOHEADER), fp);                           //д��λͼ��Ϣͷ
    
    byte * p = new byte[bmp.bmWidthBytes * bmp.bmHeight];                    //�����ڴ汣��λͼ����
	
    GetDIBits(memDC.m_hDC, (HBITMAP) memBitmap.m_hObject, 0, rect.Height(), p, 
    (LPBITMAPINFO) &bih, DIB_RGB_COLORS);                                    //��ȡλͼ����
	
    fwrite(p, 1, bmp.bmWidthBytes * bmp.bmHeight, fp);                       //д��λͼ����
    delete [] p;	
    fclose(fp);
	memDC.SelectObject(oldmemBitmap);
	memDC.DeleteDC();
}


void WebView::reload(void)
{
	this->Refresh();
}
