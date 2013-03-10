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
	// Returns:   PVOID		指向存储的地址
	// Qualifier:			将数据写入虚拟内存
	// Parameter: char * pData	存储数据
	// Parameter: int nSize		存储数据大小
	// Parameter: DWORD & dwRealSize		实际占用大小
	//************************************
	PVOID Push(IN char* pData, IN int nSize, OUT DWORD& dwRealSize, INOUT PVOID pVoid=NULL);

	BOOL FreeData(char* pVoid);//删除数据时使用， 将m_pMemSave 最后一个值与当前地址值交换， 并将m_nCurcount -1 完成删除

	


};
