
// CntrItem.cpp : CSCCCntrItem ���ʵ��
//

#include "stdafx.h"
#include "SCC.h"

#include "SCCDoc.h"
#include "SCCView.h"
#include "CntrItem.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CSCCCntrItem ��ʵ��

IMPLEMENT_SERIAL(CSCCCntrItem, CRichEditCntrItem, 0)

CSCCCntrItem::CSCCCntrItem(REOBJECT* preo, CSCCDoc* pContainer)
	: CRichEditCntrItem(preo, pContainer)
{
	// TODO: �ڴ����һ���Թ������
}

CSCCCntrItem::~CSCCCntrItem()
{
	// TODO: �ڴ˴�����������
}


// CSCCCntrItem ���

#ifdef _DEBUG
void CSCCCntrItem::AssertValid() const
{
	CRichEditCntrItem::AssertValid();
}

void CSCCCntrItem::Dump(CDumpContext& dc) const
{
	CRichEditCntrItem::Dump(dc);
}
#endif

