// DlgHistogram.cpp : 实现文件
//

#include "stdafx.h"
#include "Image.h"
#include "DlgHistogram.h"
#include "afxdialogex.h"


// CDlgHistogram 对话框

IMPLEMENT_DYNAMIC(CDlgHistogram, CDialog)

CDlgHistogram::CDlgHistogram(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_HISTOGRAM, pParent)
{

}

CDlgHistogram::~CDlgHistogram()
{
}

void CDlgHistogram::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDlgHistogram, CDialog)
	ON_WM_PAINT()
END_MESSAGE_MAP()


// CDlgHistogram 消息处理程序


extern DWORD H[256];
void Histogram();

BOOL CDlgHistogram::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  在此添加额外的初始化
	Histogram();
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void CDlgHistogram::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: 在此处添加消息处理程序代码
					   // 不为绘图消息调用 CDialog::OnPaint()
	int i;
	DWORD max;
	//绘制方框
	dc.Rectangle(20, 20, 277, 221);
	//求出H数组中的最大值
	max = 0;
	for (i = 0; i < 256; i++)
	{
		if (H[i] > max)
			max = H[i];
	}
	for (i = 0; i < 256; i++)
	{
		dc.MoveTo(i + 20, 220);
		dc.LineTo(i + 20, 220 - (int)(H[i] * 200 / max));
	}

}
