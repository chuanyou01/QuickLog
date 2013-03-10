#pragma once

class CMCriticalSectioin;
class CLockCriticalSection
{
public:
	CLockCriticalSection(CMCriticalSectioin* mCriticalSection);
	~CLockCriticalSection(void);
private:
	CMCriticalSectioin*		m_CriticalSection;
};
