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
	// Returns:   PVOID		指向存储的地址
	// Qualifier:			将数据写入虚拟内存
	// Parameter: char * pData	存储数据
	// Parameter: int nSize		存储数据大小
	// Parameter: DWORD & dwRealSize		实际占用大小
	//************************************
	PVOID Push(IN char* pData, IN int nSize, OUT DWORD& dwRealSize, INOUT PVOID pVoid=NULL);

	BOOL FreeData(IN char* pVoid);//删除数据时使用， 
private:
	void SetSaveMap(IN char* pVoid,IN int nSize,IN int nRealSize);
	void RemoveSaveMap(IN char* pVoid);

	void SetFreeMap(IN char* pVoid, IN int nSize, IN int nRealSize);
	void RemoveFreeMap(IN char* pVoid);
	BOOL PushToFree(IN char* pData, IN int nSize, OUT DWORD& dwRealSize, INOUT PVOID pVoid);



};
