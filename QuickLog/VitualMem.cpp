#include "StdAfx.h"
#include "VitualMem.h"

static int s_PageSize = 4096;

CVitualMem::CVitualMem(void)
:m_nMaxMCount(1024)
,m_nCurCount(0)
, m_dwPhysicalSize(0)
{
	InitializeCriticalSection(&m_lockMem);
	m_pMemSave = new int [65536][3];
}

CVitualMem::~CVitualMem(void)
{
	Free();
}

void CVitualMem::Free()
{
	if (!VirtualFree(m_Head, m_dwVirtualMaxSize, MEM_RELEASE))
	{
		DEBUGMSG("Free mem failed", GetLastError());
	}
	DeleteCriticalSection(&m_lockMem);
}

void CVitualMem::Init( DWORD dwMaxSize )
{
	m_dwVirtualMaxSize = dwMaxSize;
	m_Head = VirtualAlloc(NULL, dwMaxSize, MEM_TOP_DOWN | MEM_RESERVE, PAGE_READWRITE);
	if (m_Head==NULL)
	{
		DEBUGMSG("Alloc vir mem failed", GetLastError());
	}
}

PVOID CVitualMem::Push( IN char* pData, IN int nSize, OUT DWORD& dwRealSize, INOUT PVOID pVoid/*=NULL*/ )
{
	__try
	{
		dwRealSize = ((nSize + s_PageSize - 1)/s_PageSize )* s_PageSize;
		if (pVoid==NULL)
		{
			char* pTmp = ((char*)m_Head + m_dwPhysicalSize);
			pVoid = pTmp;
		}
		memcpy_s(pVoid, dwRealSize, pData, nSize);

	}
	__except(EXCEPTION_EXECUTE_HANDLER)
	{
		VirtualAlloc(pVoid, dwRealSize, MEM_COMMIT, PAGE_READWRITE);
		memcpy_s(pVoid, dwRealSize, pData, nSize);
	}

	if (m_nCurCount+1>=m_nMaxMCount)
	{
		DEBUGMSG("Mem count no left", 0);
	}
	EnterCriticalSection(&m_lockMem);
	m_dwPhysicalSize += dwRealSize;
	m_pMemSave[m_nCurCount][0] = (int)pVoid;
	m_pMemSave[m_nCurCount][1] = dwRealSize;
	m_pMemSave[m_nCurCount++][2] = nSize;
	LeaveCriticalSection(&m_lockMem);
	return pVoid;
}

void CVitualMem::SetPMemSize( IN DWORD dwMaxPMSize )
{
	m_dwMaxPhysicalSize = dwMaxPMSize;
}

int CVitualMem::GetPMemSize()
{
	return m_dwMaxPhysicalSize;
}

BOOL CVitualMem::FreeData( char* pVoid )
{
	BOOL bRet = FALSE;


	return bRet;
}

int CVitualMem::GetSize( IN PVOID pVoid, OUT int &nRealSize )
{
	int nSize = 0;
	for (int i = 0; i<m_nCurCount; i++)
	{
		if (int(pVoid)==m_pMemSave[i][0])
		{
			nSize = m_pMemSave[i][2];
			nRealSize = m_pMemSave[i][1];
			break;
		}
	}
	return nSize;
}