#include "StdAfx.h"
#include "MCriticalSectioin.h"

CMCriticalSectioin::CMCriticalSectioin(void)
{
	InitializeCriticalSection(&m_citiaclSection);
}

CMCriticalSectioin::~CMCriticalSectioin(void)
{
	DeleteCriticalSection(&m_citiaclSection);
}
