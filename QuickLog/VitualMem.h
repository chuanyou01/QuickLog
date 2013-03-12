#pragma once

struct meminfo 
{
	int nSize;
	int nRealSize;
};

class CVitualMem
{
private:
	PVOID	m_Head;
	DWORD	m_dwVirtualMaxSize;

	DWORD	m_dwMaxPhysicalSize;
	DWORD	m_dwPhysicalSize;

	CMCriticalSectioin	m_lockMem;
	CMCriticalSectioin	m_lockFreeMem;
	int (*m_pMemSave)[3];

	map<char*, meminfo*> m_mapMemSave;
	map<char*, meminfo*> m_mapMemFree;

	int GetSize( IN PVOID pVoid, OUT int &nRealSize );// return - size 
	meminfo* GetMemInfo(IN map<char*, meminfo*>& mapMem, IN PVOID pVoid);

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

	BOOL FreeData(IN char* pVoid);//ɾ������ʱʹ�ã� 
private:
	void SetSaveMap(IN char* pVoid,IN int nSize,IN int nRealSize);
	void RemoveSaveMap(IN char* pVoid);

	void SetFreeMap(IN char* pVoid, IN int nSize, IN int nRealSize);
	void RemoveFreeMap(IN char* pVoid);
	BOOL PushToFree(IN char* pData, IN int nSize, OUT DWORD& dwRealSize, INOUT PVOID pVoid);



};
