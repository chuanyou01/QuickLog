#pragma once

class CDbgHelp
{
public:
	CDbgHelp(void);
	~CDbgHelp(void);
};

#ifdef _DEBUG
#define DEBUGMSG(x, y)// 1. debug msg, 2. log msg, 3 . throw exception
#else
#define DEBUGMSG(x, y)
#endif