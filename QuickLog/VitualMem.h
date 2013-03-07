#pragma once

class CVitualMem
{
private:
	PVOID  m_Head;
	DWORD m_dwMaxSize;
	
public:
	CVitualMem(void);
	~CVitualMem(void);

};
