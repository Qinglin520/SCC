
// SCC.h : SCC Ӧ�ó������ͷ�ļ�
//
#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"       // ������
#include "GLOBAL.H"
#include "MainFrm.h"

// CSCCApp:
// �йش����ʵ�֣������ SCC.cpp
//

class CSCCApp : public CWinAppEx
{
public:
	CSCCApp();

	CRecentFileList* GetFileList(){return m_pRecentFileList;};
	void	RemoveFile(int nIndex){m_pRecentFileList->Remove(nIndex);};

// ��д
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// ʵ��
	BOOL  m_bHiColorIcons;

	virtual void PreLoadState();
	virtual void LoadCustomState();
	virtual void SaveCustomState();

	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CSCCApp theApp;
extern CMainFrame *g_mw;