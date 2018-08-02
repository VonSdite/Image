
// ImageView.h : CImageView ��Ľӿ�
//

#pragma once


class CImageView : public CScrollView
{
protected: // �������л�����
	CImageView();
	DECLARE_DYNCREATE(CImageView)

// ����
public:
	CImageDoc* GetDocument() const;

// ����
public:

// ��д
public:
	virtual void OnDraw(CDC* pDC);  // ��д�Ի��Ƹ���ͼ
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void OnInitialUpdate(); // ������һ�ε���
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// ʵ��
public:
	virtual ~CImageView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnGray();
	afx_msg void OnUpdateGray(CCmdUI *pCmdUI);
//	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnHistogram();
	afx_msg void OnUpdateHistogram(CCmdUI *pCmdUI);
	afx_msg void OnLinetrans();
	afx_msg void OnUpdateLinetrans(CCmdUI *pCmdUI);
	afx_msg void OnEqualize();
	afx_msg void OnUpdateEqualize(CCmdUI *pCmdUI);
	afx_msg void OnFourier();
	afx_msg void OnUpdateFourier(CCmdUI *pCmdUI);
	afx_msg void OnIfourier();
	afx_msg void OnUpdateIfourier(CCmdUI *pCmdUI);
	afx_msg void OnFft();
	afx_msg void OnUpdateFft(CCmdUI *pCmdUI);
	afx_msg void OnIfft();
	afx_msg void OnUpdateIfft(CCmdUI *pCmdUI);
	afx_msg void OnAverageFilter();
	afx_msg void OnUpdateAverageFilter(CCmdUI *pCmdUI);
	afx_msg void OnMedianFilter();
	afx_msg void OnUpdateMedianFilter(CCmdUI *pCmdUI);
	afx_msg void OnGradSharp();
	afx_msg void OnUpdateGradSharp(CCmdUI *pCmdUI);
	afx_msg void OnRaplasSharp();
	afx_msg void OnUpdateRaplasSharp(CCmdUI *pCmdUI);
	afx_msg void OnIdealfilterfft();
	afx_msg void OnUpdateIdealfilterfft(CCmdUI *pCmdUI);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnButterworthfilter();
	afx_msg void OnUpdateButterworthfilter(CCmdUI *pCmdUI);
	afx_msg void OnGaussfiter();
	afx_msg void OnUpdateGaussfiter(CCmdUI *pCmdUI);
};

#ifndef _DEBUG  // ImageView.cpp �еĵ��԰汾
inline CImageDoc* CImageView::GetDocument() const
   { return reinterpret_cast<CImageDoc*>(m_pDocument); }
#endif

