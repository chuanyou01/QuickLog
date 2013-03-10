#pragma once

class CVitualMem
{
private:
	PVOID	m_Head;
	DWORD	m_dwVirtualMaxSize;

	DWORD	m_dwMaxPhysicalSize;
	DWORD	m_dwPhysicalSize;

	int		m_nMaxMCount;
	int		m_nCurCount;

	CRITICAL_SECTION	m_lockMem;
	int (*m_pMemSave)[3];

	int GetSize(IN PVOID pVoid, OUT int &nRealSize);// return - size 

	void Free();
public:
	CVitualMem(void);
	~CVitualMem(void);

	void Init(IN DWORD dwMaxSize);

	void SetPMemSize(IN DWORD dwMaxPMSize);
	int GetPMemSize();

	//************************************
	// Method:    Push
	// FullName:  CVitualMem::Push
	// Access:    public 
	// Returns:   PVOID		ָ��洢�ĵ�ַ
	// Qualifier:			������д�������ڴ�
	// Parameter: char * pData	�洢����
	// Parameter: int nSize		�洢���ݴ�С
	// Parameter: DWORD & dwRealSize		ʵ��ռ�ô�С
	//************************************
	PVOID Push(IN char* pData, IN int nSize, OUT DWORD& dwRealSize, INOUT PVOID pVoid=NULL);

	BOOL FreeData(char* pVoid);//ɾ������ʱʹ�ã� ��m_pMemSave ���һ��ֵ�뵱ǰ��ֵַ������ ����m_nCurcount -1 ���ɾ��

	


};
