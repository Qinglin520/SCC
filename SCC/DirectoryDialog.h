#ifndef _DIRECTORYDIALOG_H
#define _DIRECTORYDIALOG_H

enum Flag{SD_DIR=1,SD_DIR_FILE=3};

class  CDirectoryDialog  
{	
public:
	CDirectoryDialog();
	CDirectoryDialog(CString strIniKeyName);
	virtual ~CDirectoryDialog();
	
	//����һ���Ի���,���û�ѡ���ļ���
	CString ShowDirectoryTree(CWnd *pBuddyWnd);//��ڲ�����������Ĵ���
	CString ShowDirectoryTree(CString strIniDir="");//��ڲ����ǳ���ֵ

	//д���ȡע���(��ini)�е�ֵ
	void SetDefaultDirectory(CString strDefaultDirectory);
	CString GetDefaultDirectory();
		
	HWND		m_hwndOwner; //�����ھ��    
    CString		m_strTitle;  //����
    enum Flag	m_ulFlags;   //SD_DIR,ֵΪ1,ֻ��ʾ�ļ���;SD_DIR_FILE,ֵΪ3��ʾ�ļ����ļ���  
    	
	//ע����ini�ļ��������Ϣ,��¼�ϴδ򿪵��ļ���
	CString m_strIniAppName ;
	CString m_strIniKeyName ;
			
private:
	void init();//������Ա����
	static CString GetShortDir(CString strDir,long nMaxLength =45);//����·����ת���ɶ�·����
	UINT GetStyle(enum Flag flag);//�����ת����SHBrowseForFolder�ķ��
	CString GetDefaultTitle();//�õ�Ĭ�ϱ���
	
	//�ص�����,��SHBrowseForFolder����
	static int CALLBACK  BrowseCallbackProc(HWND hwnd, UINT uMsg, LPARAM lParam, LPARAM lpData);
};

#endif _DIRECTORYDIALOG_H
