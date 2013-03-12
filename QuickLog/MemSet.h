#pragma once

class CMemSet
{
	list<string> m_lstData;
	int nMaxSize;

	map<string, char*> m_mapBuffer;

public:
	CMemSet(void);
	~CMemSet(void);

	void Push(const string& strId, char* pBuffer, int nSize);
	void Pull(const string& strId, char* pBuffer, int nSize);
};
