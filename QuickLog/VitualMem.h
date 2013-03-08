#pragma once

class CVitualMem
{
private:
	PVOID	m_Head;
	DWORD	m_dwVirtualMaxSize;
	DWORD	m_dwMaxPhysicalSize;
	DWORD	m_dwPhysicalSize;

	

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
	// Parameter: int nSzie		存储数据大小
	// Parameter: DWORD & dwRealSize		实际占用大小
	//************************************
	PVOID Push(IN char* pData, IN int nSzie, OUT DWORD& dwRealSize);

};
