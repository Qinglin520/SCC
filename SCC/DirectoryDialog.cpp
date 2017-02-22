#include "stdafx.h"
#include "DirectoryDialog.h"
// Download by http://www.codefans.net
CDirectoryDialog::CDirectoryDialog()
{
	init();	
}

CDirectoryDialog::CDirectoryDialog(CString strIniKeyName)
{
	init();
	m_strIniKeyName = strIniKeyName ;
}

CDirectoryDialog::~CDirectoryDialog()
{

}

int CALLBACK CDirectoryDialog::BrowseCallbackProc(HWND hwnd, UINT uMsg, LPARAM lParam, LPARAM lpData)
{
	switch(uMsg)
	{		
	case BFFM_INITIALIZED://����lpDataѡ���ʼ�ļ���		
		::SendMessage(hwnd,BFFM_SETSELECTION,TRUE,lpData);
		return 1 ;
	case BFFM_SELCHANGED:
		{
			char szDir[1000];
			if (SHGetPathFromIDList((LPITEMIDLIST) lParam ,szDir))
			{//��ѡ����ļ�����ʾ�ھ�̬�ı�����,���̫��ֻ��ʾ��ͷ�ͽ�β
				SendMessage(hwnd,BFFM_SETSTATUSTEXT,0,(LPARAM)(LPCTSTR)GetShortDir(szDir));
			}			
		}
		return 1 ;
	}
	return 1 ;
}

/////////////////////////////////////////////////////////////////////////
//  ��������: CDirectoryDialog::ShowDirectoryTree
//  ����˵��: ����ϵͳ�Ի������û�ѡ��һ�����ʵ��ļ��л��ļ�
//  ��ڲ���: ��ʼ·��
//  ����ֵ  : �û�ѡ���·��,ȡ�����ؿմ�
/////////////////////////////////////////////////////////////////////////
CString CDirectoryDialog::ShowDirectoryTree(CString strIniDir)
{
	CString strPath;//��¼�û�ѡ����ļ���
	char pszTemp[1000] = {""};
	char pszTitle[1000] = {""};//����
	
	if(NULL == m_hwndOwner)		m_hwndOwner = AfxGetMainWnd()->GetSafeHwnd();
	if(m_strTitle.IsEmpty())	m_strTitle = GetDefaultTitle();//Ϊ��,�õ�Ĭ�ϵı���
	BROWSEINFOA bi ={0}; 	
	char pszDisplayName[MAX_PATH] = "\0";//�洢�û���ѡ��
	bi.hwndOwner=m_hwndOwner;	
	bi.pszDisplayName = pszDisplayName;	
	bi.ulFlags	 = GetStyle(m_ulFlags);	
	bi.lpszTitle = m_strTitle ;
	bi.lpfn		 = BrowseCallbackProc ;

	if(strIniDir.IsEmpty())
		strcpy_s(pszTemp,(LPCTSTR)(AfxGetApp()->GetProfileString(m_strIniAppName,m_strIniKeyName,"")));
	else	strcpy_s(pszTemp,strIniDir);
	bi.lParam   = (int)pszTemp ;	
	LPITEMIDLIST lpIL = SHBrowseForFolder(&bi);	
	if(lpIL)	SHGetPathFromIDList(lpIL,bi.pszDisplayName);
	else		return "";	
	strPath = bi.pszDisplayName;//���������"\\"��β,����"\\"
	if(strPath.Right(1)!='\\')		strPath += "\\";
	SetDefaultDirectory(strPath);//���ļ��д��ע����ini
	return strPath ;
}

CString CDirectoryDialog::GetDefaultDirectory()
{
	//m_strIniAppName��m_strIniKeyNameΪ��,�����ע���
	if(m_strIniAppName.IsEmpty() || m_strIniKeyName.IsEmpty())
		return "";
	
	return AfxGetApp()->GetProfileString(m_strIniAppName,m_strIniKeyName,"");
}

void CDirectoryDialog::SetDefaultDirectory(CString strDefaultDirectory)
{
	//m_strIniAppName��m_strIniKeyNameΪ��,�����ע���
	if(m_strIniAppName.IsEmpty() || m_strIniKeyName.IsEmpty())
	{
	//	ASSERT(false);
		return ;
	}
	
	AfxGetApp()->WriteProfileString(m_strIniAppName,m_strIniKeyName,strDefaultDirectory);
}

void CDirectoryDialog::init()
{		
	m_hwndOwner = NULL;    
    m_strTitle.Empty(); 
    m_ulFlags  = SD_DIR;     
    	
	m_strIniAppName = "�ļ��г�ʼ·��";
	m_strIniKeyName.Empty();
}

/////////////////////////////////////////////////////////////////////////
//  ��������: CDirectoryDialog::GetShortDir
//  ����˵��: ����·��ת�ɶ�·��;��·��=�̷�+1��6��"." + ���һ���ļ��л��ļ�
//  ��ڲ���: ��·����,�����
/////////////////////////////////////////////////////////////////////////
CString CDirectoryDialog::GetShortDir(CString strDir,long nMaxLength/*=45*/)
{
	ASSERT(nMaxLength > 5);
	if(strDir.GetLength() < nMaxLength)	return strDir ;//û�г�����,���ô���
	CString strShortDir;//������̷�(��c:\)�����̷�
	if(':'==strDir[1] && '\\'==strDir[2])	strShortDir = strDir.Left(3);
	CString strLastDir ;//ȡ���һ���ļ��л��ļ�
	int nPos = strDir.ReverseFind('\\');
	if(nPos != -1)		strLastDir = strDir.Mid(nPos);
	if(strLastDir.GetLength() > nMaxLength - 5 )
	{		  
		strLastDir = strLastDir.Mid(strLastDir.GetLength() - (nMaxLength - 5));
		if('\\' != strLastDir[0])	strLastDir = '\\' + strLastDir ;
	}//�м��������...,�������
	int nSpace = nMaxLength - strShortDir.GetLength() - strLastDir.GetLength() ;
	if(nSpace > 6)		nSpace = 6;
	for(int i = 0 ; i< nSpace ; i++)		strShortDir +=".";
	strShortDir += strLastDir ;
	strLastDir.Empty();
	return strShortDir ;	
}

/////////////////////////////////////////////////////////////////////////
//  ��������: CDirectoryDialog::ShowDirectoryTree
//  ����˵��: ����ϵͳ�Ի������û�ѡ��һ��·��
//  ��ڲ���: ��ڲ�����������
//  ��������Ϊ��,�򸸾��Ϊ�����ؼ��ĸ�����
//	�������ѡ���·��д��ini,���ù����ؼ���ֵΪ��ʼֵ
//	���û�ѡ���ֵ��ʾ�ڹ����ؼ���,���������������
/////////////////////////////////////////////////////////////////////////
CString CDirectoryDialog::ShowDirectoryTree(CWnd *pBuddyWnd)
{
	if(NULL == pBuddyWnd)	return "" ;
	CString strDir ;
	
	if(NULL == m_hwndOwner)//�Թ����ؼ��ĸ�����Ϊ������
	{
		if(NULL != pBuddyWnd->GetParent())
			m_hwndOwner = pBuddyWnd->GetParent()->GetSafeHwnd();
	}		
	if(m_strIniKeyName.IsEmpty())	pBuddyWnd->GetWindowText(strDir);//���û�н��ϴε�·��д��ע���,��ʼֵΪ�����ؼ�������
	strDir = ShowDirectoryTree(strDir);		
	if(!strDir.IsEmpty())
	{//���¹����ؼ�����ʾ������������ֵ
		pBuddyWnd->SetWindowText(strDir);
		if(NULL != pBuddyWnd->GetParent())
			pBuddyWnd->GetParent()->UpdateData(true);
	}		
	return strDir ;
}

CString CDirectoryDialog::GetDefaultTitle()
{
	CString strTitle ;
	if(m_strIniKeyName.IsEmpty())		strTitle = "ѡ�񱣴���ӱ��ĵ�Ŀ¼:";	
	else
	{
		char pszTitle[255];
		sprintf_s(pszTitle,"��Ϊ%sѡ����ʵ�Ŀ¼:",m_strIniKeyName);
		strTitle =  pszTitle ;
	}
	return strTitle ;
}

UINT CDirectoryDialog::GetStyle(enum Flag flag)
{
	switch(flag)
	{
//	case SD_DIR		 :	
//		return BIF_RETURNONLYFSDIRS|BIF_STATUSTEXT ;//ֻ��ʾ�ļ���
	case SD_DIR_FILE :	
		return BIF_RETURNONLYFSDIRS|BIF_STATUSTEXT|BIF_BROWSEINCLUDEFILES;//��ʾ�ļ��к��ļ�
	}
	return BIF_RETURNONLYFSDIRS|BIF_STATUSTEXT ;//ֻ��ʾ�ļ���
}
