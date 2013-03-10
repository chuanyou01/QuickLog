#pragma once

class CMCriticalSectioin
{
public:
	CMCriticalSectioin(void);
	~CMCriticalSectioin(void);

	CRITICAL_SECTION	m_citiaclSection;
};
