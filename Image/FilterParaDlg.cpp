// FilterParaDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Image.h"
#include "FilterParaDlg.h"
#include "afxdialogex.h"


// CFilterParaDlg �Ի���

IMPLEMENT_DYNAMIC(CFilterParaDlg, CDialog)

CFilterParaDlg::CFilterParaDlg(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_DIALOG1, pParent)
	, m_nDis(0)
{

}

CFilterParaDlg::~CFilterParaDlg()
{
}

void CFilterParaDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_nDis);
}


BEGIN_MESSAGE_MAP(CFilterParaDlg, CDialog)
END_MESSAGE_MAP()


// CFilterParaDlg ��Ϣ�������
