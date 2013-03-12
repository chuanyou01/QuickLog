#include "StdAfx.h"
#include "VitualMem.h"

static int s_PageSize = 4096;

CVitualMem::CVitualMem(void)
: m_dwPhysicalSize(0)
{
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

BOOL CVitualMem::PushToFree(IN char* pData, IN int nSize, OUT DWORD& dwRealSize, INOUT PVOID pVoid)
{
	for (map<char*, meminfo*>::iterator it = m_mapMemFree.begin();
		it!=m_mapMemFree.end(); it++)
	{
		meminfo* pInfo = it->second;
		if (pInfo->nRealSize>nSize)
		{
			pVoid = it->first;

			dwRealSize = pInfo->nRealSize;
			RemoveFreeMap((char*)pVoid);
			SetSaveMap((char*)pVoid, nSize, dwRealSize);

			memcpy_s(pVoid, dwRealSize, pData, nSize);

			return TRUE;
		}
	}
	return FALSE;
}

PVOID CVitualMem::Push( IN char* pData, IN int nSize, OUT DWORD& dwRealSize, INOUT PVOID pVoid/*=NULL*/ )
{
	BOOL bDone = FALSE;
	__try
	{
		if (!m_mapMemFree.empty())
		{
			bDone = PushToFree(pData, nSize, dwRealSize, pVoid);			
		}
		if (!bDone)
		{
			dwRealSize = ((nSize + s_PageSize - 1)/s_PageSize )* s_PageSize;
			if (pVoid==NULL)
			{
				char* pTmp = ((char*)m_Head + m_dwPhysicalSize);
				pVoid = pTmp;
			}
			memcpy_s(pVoid, dwRealSize, pData, nSize);
		}

	}
	__except(EXCEPTION_EXECUTE_HANDLER)
	{
		VirtualAlloc(pVoid, dwRealSize, MEM_COMMIT, PAGE_READWRITE);
		memcpy_s(pVoid, dwRealSize, pData, nSize);
	}
	if (!bDone)
	{
		SetSaveMap((char*)pVoid, nSize, dwRealSize);
	}
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
	meminfo* pMemInfo = GetMemInfo(m_mapMemSave, pVoid);
	if (pMemInfo!=NULL)
	{
		RemoveSaveMap(pVoid);
		SetFreeMap(pVoid, pMemInfo->nSize, pMemInfo->nRealSize);
		bRet = TRUE;
	}
	return bRet;
}

int CVitualMem::GetSize( IN PVOID pVoid, OUT int &nRealSize )
{
	int nSize = 0;
	CLockCriticalSection mlock(&m_lockMem);
	meminfo* pMemInfo = GetMemInfo(m_mapMemSave, pVoid);
	if (pMemInfo!=NULL)
	{
		nRealSize = pMemInfo->nRealSize;
		nSize = pMemInfo->nSize;
	}
	return nSize;
}

meminfo* CVitualMem::GetMemInfo(IN map<char*, meminfo*>& mapMem, IN PVOID pVoid )
{
	meminfo* pMemInfo = NULL;
	map<char*, meminfo*>::iterator it = mapMem.find((char*)pVoid);
	if (it!=mapMem.end())
	{
		pMemInfo = it->second;
	}
	return pMemInfo;
}

void CVitualMem::SetSaveMap( IN char* pVoid,IN int nSize,IN int nRealSize )
{
	CLockCriticalSection mlock(&m_lockMem);

	meminfo* pMemInfo = NULL;
	if (m_mapMemSave.find(pVoid)!=m_mapMemSave.end())
	{
		pMemInfo = m_mapMemSave[pVoid];
	}
	else
	{
		pMemInfo = new meminfo;
		m_mapMemSave[pVoid] = pMemInfo;
	}

	pMemInfo->nRealSize = nRealSize;
	pMemInfo->nSize = nSize;
}

void CVitualMem::RemoveSaveMap( IN char* pVoid )
{
	CLockCriticalSection mlock(&m_lockMem);
	m_mapMemSave.erase(pVoid);
}

void CVitualMem::SetFreeMap( IN char* pVoid, IN int nSize, IN int nRealSize )
{
	CLockCriticalSection mlock(&m_lockFreeMem);

	meminfo* pMemInfo = NULL;
	if (m_mapMemFree.find(pVoid)!=m_mapMemFree.end())
	{
		pMemInfo = m_mapMemFree[pVoid];
	}
	else
	{
		pMemInfo = new meminfo;
		m_mapMemFree[pVoid] = pMemInfo;
	}

	pMemInfo->nRealSize = nRealSize;
	pMemInfo->nSize = nSize;
}

void CVitualMem::RemoveFreeMap( IN char* pVoid )
{
	CLockCriticalSection mlock(&m_lockFreeMem);
	m_mapMemFree.erase(pVoid);
}
