#pragma once


// CFilterParaDlg �Ի���

class CFilterParaDlg : public CDialog
{
	DECLARE_DYNAMIC(CFilterParaDlg)

public:
	CFilterParaDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CFilterParaDlg();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	int m_nDis;
};
