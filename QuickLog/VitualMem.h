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
	// Returns:   PVOID		ָ��洢�ĵ�ַ
	// Qualifier:			������д�������ڴ�
	// Parameter: char * pData	�洢����
	// Parameter: int nSzie		�洢���ݴ�С
	// Parameter: DWORD & dwRealSize		ʵ��ռ�ô�С
	//************************************
	PVOID Push(IN char* pData, IN int nSzie, OUT DWORD& dwRealSize);

};
