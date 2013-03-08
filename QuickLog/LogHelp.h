#pragma once

class CLogHelp
{
public:
	CLogHelp(void);
	~CLogHelp(void);
};


#ifdef _DEBUG
#define LOGMSG(x, y)
#else
#define LOGMSG(x, y)
#endif