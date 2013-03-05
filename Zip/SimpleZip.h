#pragma once
#include <string>
#include <list>
class CSimpleZip
{
public:
	CSimpleZip(void);
	~CSimpleZip(void);

public:
	bool Add(std::string strZipFile,std::list<std::string>& lstFile,std::string strRootPath,bool bFullPath=FALSE);
	bool Extract(std::string strDest,std::string strZipFile);
};
