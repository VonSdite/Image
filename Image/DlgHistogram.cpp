// DlgHistogram.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Image.h"
#include "DlgHistogram.h"
#include "afxdialogex.h"


// CDlgHistogram �Ի���

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


// CDlgHistogram ��Ϣ�������


extern DWORD H[256];
void Histogram();

BOOL CDlgHistogram::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	Histogram();
	return TRUE;  // return TRUE unless you set the focus to a control
				  // �쳣: OCX ����ҳӦ���� FALSE
}


void CDlgHistogram::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: �ڴ˴������Ϣ����������
					   // ��Ϊ��ͼ��Ϣ���� CDialog::OnPaint()
	int i;
	DWORD max;
	//���Ʒ���
	dc.Rectangle(20, 20, 277, 221);
	//���H�����е����ֵ
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
