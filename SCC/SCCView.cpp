
// SCCView.cpp : CSCCView ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
#ifndef SHARED_HANDLERS
#include "SCC.h"
#endif

#include "SCCDoc.h"
#include "CntrItem.h"
#include "resource.h"
#include "SCCView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CSCCView

IMPLEMENT_DYNCREATE(CSCCView, CXRichEditView)

BEGIN_MESSAGE_MAP(CSCCView, CXRichEditView)
	ON_WM_DESTROY()
	// ��׼��ӡ����
	ON_COMMAND(ID_FILE_PRINT, &CXRichEditView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CXRichEditView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CSCCView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
END_MESSAGE_MAP()

// CSCCView ����/����

CSCCView::CSCCView()
{
	// TODO: �ڴ˴���ӹ������

}

CSCCView::~CSCCView()
{
}

BOOL CSCCView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return CXRichEditView::PreCreateWindow(cs);
}

void CSCCView::OnInitialUpdate()
{
	CXRichEditView::OnInitialUpdate();


	// ���ô�ӡ�߾�(720 � = 1/2 Ӣ��)
	SetMargins(CRect(720, 720, 720, 720));
}


// CSCCView ��ӡ


void CSCCView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CSCCView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// Ĭ��׼��
	return DoPreparePrinting(pInfo);
}


void CSCCView::OnDestroy()
{
	// ����ʱͣ�ô������
	// ʹ�ò����ͼʱ�ǳ���Ҫ 
   COleClientItem* pActiveItem = GetDocument()->GetInPlaceActiveItem(this);
   if (pActiveItem != NULL && pActiveItem->GetActiveView() == this)
   {
      pActiveItem->Deactivate();
      ASSERT(GetDocument()->GetInPlaceActiveItem(this) == NULL);
   }
   CXRichEditView::OnDestroy();
}


void CSCCView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CSCCView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CSCCView ���

#ifdef _DEBUG
void CSCCView::AssertValid() const
{
	CXRichEditView::AssertValid();
}

void CSCCView::Dump(CDumpContext& dc) const
{
	CXRichEditView::Dump(dc);
}

CSCCDoc* CSCCView::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CSCCDoc)));
	return (CSCCDoc*)m_pDocument;
}
#endif //_DEBUG


// CSCCView ��Ϣ�������
