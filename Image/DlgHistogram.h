#pragma once


// CDlgHistogram �Ի���

class CDlgHistogram : public CDialog
{
	DECLARE_DYNAMIC(CDlgHistogram)

public:
	CDlgHistogram(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgHistogram();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_HISTOGRAM};
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
};
