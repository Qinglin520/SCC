
// CntrItem.h : CSCCCntrItem ��Ľӿ�
//

#pragma once

class CSCCDoc;
class CSCCView;

class CSCCCntrItem : public CRichEditCntrItem
{
	DECLARE_SERIAL(CSCCCntrItem)

// ���캯��
public:
	CSCCCntrItem(REOBJECT* preo = NULL, CSCCDoc* pContainer = NULL);
		// ע��: ���� pContainer Ϊ NULL ������ IMPLEMENT_SERIALIZE
		//  IMPLEMENT_SERIALIZE Ҫ������д���
		//  �����Ĺ��캯����OLE ��ͨ������
		//  �� NULL �ĵ�ָ�빹���

// ����
public:
	CSCCDoc* GetDocument()
		{ return reinterpret_cast<CSCCDoc*>(CRichEditCntrItem::GetDocument()); }
	CSCCView* GetActiveView()
		{ return reinterpret_cast<CSCCView*>(CRichEditCntrItem::GetActiveView()); }

// ʵ��
public:
	~CSCCCntrItem();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
};

