
// SCCView.h : CSCCView ��Ľӿ�
//

#pragma once

class CSCCCntrItem;
#include "XRichEditView.h"
class CSCCDoc;
class CSCCView : public CXRichEditView
{
protected: // �������л�����
	CSCCView();
	DECLARE_DYNCREATE(CSCCView)

// ����
public:
	CSCCDoc* GetDocument() const;

// ����
public:

// ��д
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void OnInitialUpdate(); // ������һ�ε���
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);

// ʵ��
public:
	virtual ~CSCCView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	afx_msg void OnDestroy();
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // SCCView.cpp �еĵ��԰汾
inline CSCCDoc* CSCCView::GetDocument() const
   { return reinterpret_cast<CSCCDoc*>(m_pDocument); }
#endif

