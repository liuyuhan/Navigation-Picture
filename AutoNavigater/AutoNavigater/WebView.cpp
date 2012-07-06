// WebView.cpp : 实现文件
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


// WebView 诊断

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


// WebView 消息处理程序


bool WebView::paintView(UINT nID, CWnd* pParent)
{
	CStatic wndStatic; //静态控件对象；
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
	CBitmap*  m_pBitmap; 	                                                 // 加入类成员
	CFrameWnd* pMainFrame = (CFrameWnd*)AfxGetMainWnd();                     // 获得截图窗口的指针，默认为主窗口，可以更改为其他的窗口。
   	CPaintDC   dc(pMainFrame); 
	CString filename;
	
	m_pBitmap=new CBitmap;   
	m_pBitmap->CreateCompatibleBitmap(&dc,rect.Width(),rect.Height());   

	CDC   memDC;  
	memDC.CreateCompatibleDC(&dc); 
	CBitmap memBitmap, *oldmemBitmap;                                        // 建立和屏幕兼容的bitmap
	
    memBitmap.CreateCompatibleBitmap(&dc, rect.Width(),rect.Height());
	
    oldmemBitmap = memDC.SelectObject(&memBitmap);//将memBitmap选入内存DC
    memDC.BitBlt(0, 0, rect.Width(),rect.Height(), &dc,rect.left, rect.top, SRCCOPY);  // 调解高度宽度
	BITMAP bmp;
    memBitmap.GetBitmap(&bmp);                                               // 获得位图信息 

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
	
    BITMAPINFOHEADER bih = {0};                                              // 位图信息头
    bih.biBitCount = bmp.bmBitsPixel;                                        // 每个像素字节大小
    bih.biCompression = BI_RGB;
    bih.biHeight = bmp.bmHeight;                                             // 高度
    bih.biPlanes = 1;
    bih.biSize = sizeof(BITMAPINFOHEADER);
    bih.biSizeImage = bmp.bmWidthBytes * bmp.bmHeight;                       // 图像数据大小
    bih.biWidth = bmp.bmWidth;                                               // 宽度
    
    BITMAPFILEHEADER bfh = {0};                                              // 位图文件头
    bfh.bfOffBits = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);     // 到位图数据的偏移量
    bfh.bfSize = bfh.bfOffBits + bmp.bmWidthBytes * bmp.bmHeight;            // 文件总的大小
    bfh.bfType = (WORD)0x4d42;
    
    fwrite(&bfh, 1, sizeof(BITMAPFILEHEADER), fp);                           //写入位图文件头
    
    fwrite(&bih, 1, sizeof(BITMAPINFOHEADER), fp);                           //写入位图信息头
    
    byte * p = new byte[bmp.bmWidthBytes * bmp.bmHeight];                    //申请内存保存位图数据
	
    GetDIBits(memDC.m_hDC, (HBITMAP) memBitmap.m_hObject, 0, rect.Height(), p, 
    (LPBITMAPINFO) &bih, DIB_RGB_COLORS);                                    //获取位图数据
	
    fwrite(p, 1, bmp.bmWidthBytes * bmp.bmHeight, fp);                       //写入位图数据
    delete [] p;	
    fclose(fp);
	memDC.SelectObject(oldmemBitmap);
	memDC.DeleteDC();
}


void WebView::reload(void)
{
	this->Refresh();
}
