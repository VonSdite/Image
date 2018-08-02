
// ImageView.cpp : CImageView 类的实现
//
#include "stdafx.h"
#include "DlgHistogram.h"
#include "MainFrm.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "Image.h"
#endif

#include "ImageDoc.h"
#include "ImageView.h"
#include "FilterParaDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CImageView

IMPLEMENT_DYNCREATE(CImageView, CScrollView)

BEGIN_MESSAGE_MAP(CImageView, CScrollView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CScrollView::OnFilePrintPreview)
	ON_COMMAND(ID_GRAY, &CImageView::OnGray)
	ON_UPDATE_COMMAND_UI(ID_GRAY, &CImageView::OnUpdateGray)
	ON_COMMAND(ID_HISTOGRAM, &CImageView::OnHistogram)
	ON_UPDATE_COMMAND_UI(ID_HISTOGRAM, &CImageView::OnUpdateHistogram)
	ON_COMMAND(ID_LINETRANS, &CImageView::OnLinetrans)
	ON_UPDATE_COMMAND_UI(ID_LINETRANS, &CImageView::OnUpdateLinetrans)
	ON_COMMAND(ID_EQUALIZE, &CImageView::OnEqualize)
	ON_UPDATE_COMMAND_UI(ID_EQUALIZE, &CImageView::OnUpdateEqualize)
	ON_COMMAND(ID_FOURIER, &CImageView::OnFourier)
	ON_UPDATE_COMMAND_UI(ID_FOURIER, &CImageView::OnUpdateFourier)
	ON_COMMAND(ID_IFOURIER, &CImageView::OnIfourier)
	ON_UPDATE_COMMAND_UI(ID_IFOURIER, &CImageView::OnUpdateIfourier)
	ON_COMMAND(ID_FFT, &CImageView::OnFft)
	ON_UPDATE_COMMAND_UI(ID_FFT, &CImageView::OnUpdateFft)
	ON_COMMAND(ID_IFFT, &CImageView::OnIfft)
	ON_UPDATE_COMMAND_UI(ID_IFFT, &CImageView::OnUpdateIfft)
	ON_COMMAND(ID_AVERAGE_FILTER, &CImageView::OnAverageFilter)
	ON_UPDATE_COMMAND_UI(ID_AVERAGE_FILTER, &CImageView::OnUpdateAverageFilter)
	ON_COMMAND(ID_MEDIAN_FILTER, &CImageView::OnMedianFilter)
	ON_UPDATE_COMMAND_UI(ID_MEDIAN_FILTER, &CImageView::OnUpdateMedianFilter)
	ON_COMMAND(ID_GRAD_SHARP, &CImageView::OnGradSharp)
	ON_UPDATE_COMMAND_UI(ID_GRAD_SHARP, &CImageView::OnUpdateGradSharp)
	ON_COMMAND(ID_RAPLAS_SHARP, &CImageView::OnRaplasSharp)
	ON_UPDATE_COMMAND_UI(ID_RAPLAS_SHARP, &CImageView::OnUpdateRaplasSharp)
	ON_COMMAND(ID_IDEALFILTERFFT, &CImageView::OnIdealfilterfft)
	ON_UPDATE_COMMAND_UI(ID_IDEALFILTERFFT, &CImageView::OnUpdateIdealfilterfft)
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDOWN()
	ON_COMMAND(ID_BUTTERWORTHFILTER, &CImageView::OnButterworthfilter)
	ON_UPDATE_COMMAND_UI(ID_BUTTERWORTHFILTER, &CImageView::OnUpdateButterworthfilter)
	ON_COMMAND(ID_GAUSSFITER, &CImageView::OnGaussfiter)
	ON_UPDATE_COMMAND_UI(ID_GAUSSFITER, &CImageView::OnUpdateGaussfiter)
END_MESSAGE_MAP()

// CImageView 构造/析构

CImageView::CImageView()
{
	// TODO: 在此处添加构造代码

}

CImageView::~CImageView()
{
}

BOOL CImageView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CScrollView::PreCreateWindow(cs);
}

// CImageView 绘制
extern LPBITMAPINFO lpBitsInfo;
extern BITMAPINFO *lpDIB_FFT;
extern BITMAPINFO *lpDIB_IFFT;
void CImageView::OnDraw(CDC* pDC)
{
	CImageDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 在此处为本机数据添加绘制代码
	if (NULL == lpBitsInfo)
		return;

	/****************更改调色板*****************
	// 改变调色板前两个颜色值
	RGBQUAD pal[2];
	pal[0].rgbRed      = 255;
	pal[0].rgbGreen    = 0;
	pal[0].rgbBlue     = 0;
	pal[0].rgbReserved = 0;
	pal[1].rgbRed      = 255;
	pal[1].rgbGreen    = 255;
	pal[1].rgbBlue     = 255;
	pal[1].rgbReserved = 0;
	memcpy(lpBitsInfo->bmiColors,pal,8); // 内存复制函数
	// void *memcpy(void *dest, const void *src, size_t n); // 函数原型
	// 从源src所指的内存地址的起始位置开始拷贝n个字节到目标dest所指的内存地址的起始位置中
	********************************************/
	LPVOID lpBits = (LPVOID)&lpBitsInfo->bmiColors[lpBitsInfo->bmiHeader.biClrUsed];
	StretchDIBits(
		//::GetDC(NULL),		// 在桌面显示
		pDC->GetSafeHdc(),		// 在视图中显示
		0, 0,
		lpBitsInfo->bmiHeader.biWidth,
		lpBitsInfo->bmiHeader.biHeight,
		0, 0,
		lpBitsInfo->bmiHeader.biWidth,
		lpBitsInfo->bmiHeader.biHeight,
		lpBits,
		lpBitsInfo, // bitmap data 
		DIB_RGB_COLORS,
		SRCCOPY);

	if (lpDIB_FFT)
	{
		lpBits = (LPVOID)&lpDIB_FFT->bmiColors[lpDIB_FFT->bmiHeader.biClrUsed];
		StretchDIBits(
			pDC->GetSafeHdc(),
			600, 0,
			lpDIB_FFT->bmiHeader.biWidth,
			lpDIB_FFT->bmiHeader.biHeight,
			0, 0,
			lpDIB_FFT->bmiHeader.biWidth,
			lpDIB_FFT->bmiHeader.biHeight,
			lpBits,
			lpDIB_FFT, // bitmap data 
			DIB_RGB_COLORS,
			SRCCOPY);
	}

	if (lpDIB_IFFT)
	{
		lpBits = (LPVOID)&lpDIB_IFFT->bmiColors[lpDIB_IFFT->bmiHeader.biClrUsed];
		StretchDIBits(
			pDC->GetSafeHdc(),
			0, 600,
			lpDIB_IFFT->bmiHeader.biWidth,
			lpDIB_IFFT->bmiHeader.biHeight,
			0, 0,
			lpDIB_IFFT->bmiHeader.biWidth,
			lpDIB_IFFT->bmiHeader.biHeight,
			lpBits,
			lpDIB_IFFT, // bitmap data 
			DIB_RGB_COLORS,
			SRCCOPY);
	}


}

void CImageView::OnInitialUpdate()
{
	CScrollView::OnInitialUpdate();

	CSize sizeTotal;
	// TODO: 计算此视图的合计大小
	sizeTotal.cx = 800;
	sizeTotal.cy = 2000;
	SetScrollSizes(MM_TEXT, sizeTotal);
}


// CImageView 打印

BOOL CImageView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CImageView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void CImageView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
}


// CImageView 诊断

#ifdef _DEBUG
void CImageView::AssertValid() const
{
	CScrollView::AssertValid();
}

void CImageView::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}

CImageDoc* CImageView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CImageDoc)));
	return (CImageDoc*)m_pDocument;
}
#endif //_DEBUG


// CImageView 消息处理程序

void gray();
void CImageView::OnGray()
{
	// TODO: 在此添加命令处理程序代码
	gray();
	Invalidate(); // 无效化使得窗口重绘
}


void CImageView::OnUpdateGray(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	pCmdUI->Enable(lpBitsInfo != NULL && lpBitsInfo->bmiHeader.biBitCount == 24);
}

void pixel(int, int);
void CImageView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	pixel(point.x, point.y);
	CScrollView::OnLButtonDown(nFlags, point);
}

void pixel(int, int, char *);
void CImageView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	char str[255];
	memset(str, 0, sizeof(str));
	pixel(point.x, point.y, str);

	((CMainFrame *)GetParent())->m_wndStatusBar.SetWindowText(str);

	CScrollView::OnMouseMove(nFlags, point);
}


void CImageView::OnHistogram()
{
	// TODO: 在此添加命令处理程序代码
	CDlgHistogram dlg;
	dlg.DoModal();
}


void CImageView::OnUpdateHistogram(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	pCmdUI->Enable(lpBitsInfo != NULL && lpBitsInfo->bmiHeader.biBitCount == 8);
}

void LinerTrans(float, float);
void CImageView::OnLinetrans()
{
	// TODO: 在此添加命令处理程序代码
	LinerTrans(2, -100);
	Invalidate();
}


void CImageView::OnUpdateLinetrans(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	pCmdUI->Enable(lpBitsInfo != NULL && lpBitsInfo->bmiHeader.biBitCount == 8);
}


void Equalize();
void CImageView::OnEqualize()
{
	// TODO: 在此添加命令处理程序代码
	Equalize();
	Invalidate();
}


void CImageView::OnUpdateEqualize(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	pCmdUI->Enable(lpBitsInfo != NULL && lpBitsInfo->bmiHeader.biBitCount == 8);
}

void Fourier();
void CImageView::OnFourier()
{
	// TODO: 在此添加命令处理程序代码
	Fourier();
	Invalidate();

}


void CImageView::OnUpdateFourier(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	pCmdUI->Enable(lpBitsInfo != NULL && lpBitsInfo->bmiHeader.biBitCount == 8);
}

void IFourier();
void CImageView::OnIfourier()
{
	// TODO: 在此添加命令处理程序代码
	IFourier();
	Invalidate();
}


void CImageView::OnUpdateIfourier(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	pCmdUI->Enable(lpBitsInfo != NULL && lpBitsInfo->bmiHeader.biBitCount == 8);
}

void FFourier1();
void CImageView::OnFft()
{
	// TODO: 在此添加命令处理程序代码
	if (lpDIB_FFT)
		free(lpDIB_FFT);

	FFourier1();
	Invalidate();

}


void CImageView::OnUpdateFft(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	pCmdUI->Enable(lpBitsInfo != NULL && lpBitsInfo->bmiHeader.biBitCount == 8);
}

void IFFourier();
static BOOL bFlag = TRUE;
void CImageView::OnIfft()
{
	// TODO: 在此添加命令处理程序代码
	if (lpDIB_IFFT)
		free(lpDIB_IFFT);

	IFFourier();
	bFlag = FALSE;
	Invalidate();

}


void CImageView::OnUpdateIfft(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	pCmdUI->Enable(lpDIB_FFT != NULL);
}


void AverageFilter();
void MedianFilter();
void GradSharp();
void RaplasSharp();

void CImageView::OnAverageFilter()
{
	// TODO: 在此添加命令处理程序代码
	AverageFilter();
	Invalidate();
}


void CImageView::OnUpdateAverageFilter(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	pCmdUI->Enable(lpBitsInfo != NULL);
}


void CImageView::OnMedianFilter()
{
	// TODO: 在此添加命令处理程序代码
	MedianFilter();
	Invalidate();
}


void CImageView::OnUpdateMedianFilter(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	pCmdUI->Enable(lpBitsInfo != NULL);
}


void CImageView::OnGradSharp()
{
	// TODO: 在此添加命令处理程序代码
	GradSharp();
	Invalidate();
}


void CImageView::OnUpdateGradSharp(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	pCmdUI->Enable(lpBitsInfo != NULL);
}


void CImageView::OnRaplasSharp()
{
	// TODO: 在此添加命令处理程序代码
	RaplasSharp();
	Invalidate();
}


void CImageView::OnUpdateRaplasSharp(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	pCmdUI->Enable(lpBitsInfo != NULL);
}

void Ideal_Filter_FFT(int D);
void CImageView::OnIdealfilterfft()
{
	// TODO: 在此添加命令处理程序代码
	CFilterParaDlg dlg;
	if (IDOK == dlg.DoModal())
		Ideal_Filter_FFT(dlg.m_nDis);
	Invalidate();
}


void CImageView::OnUpdateIdealfilterfft(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	pCmdUI->Enable(lpBitsInfo != NULL);
}

void Butterworth_Filter_FFT(int D);
void CImageView::OnButterworthfilter()
{
	// TODO: 在此添加命令处理程序代码
	CFilterParaDlg dlg;
	if (IDOK == dlg.DoModal())
		Butterworth_Filter_FFT(dlg.m_nDis);
	Invalidate();
}


void CImageView::OnUpdateButterworthfilter(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	pCmdUI->Enable(lpDIB_FFT != NULL && !bFlag);
}

void Gauss_Filter_FFT(int D);
void CImageView::OnGaussfiter()
{
	// TODO: 在此添加命令处理程序代码
	CFilterParaDlg dlg;
	if (IDOK == dlg.DoModal())
		Gauss_Filter_FFT(dlg.m_nDis);
	Invalidate();

}


void CImageView::OnUpdateGaussfiter(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	pCmdUI->Enable(lpDIB_FFT != NULL && !bFlag);
}
