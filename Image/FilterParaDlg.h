#pragma once


// CFilterParaDlg 对话框

class CFilterParaDlg : public CDialog
{
	DECLARE_DYNAMIC(CFilterParaDlg)

public:
	CFilterParaDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CFilterParaDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	int m_nDis;
};
