#ifndef	_OPENMONITOR_OMLICENSE_H_
#define _OPENMONITOR_OMLICENSE_H_

#include <iostream>
#include <string>

struct st_omlic
{
	std::string m_strComany;
	std::string m_strEmail;

#define OM_ISSUE_TYPE_NEVEREXPIRES		0x1
#define OM_ISSUE_TYPE_SERVICE			0x2
#define OM_ISSUE_TYPE_EVALUATION		0x4
#define OM_ISSUE_TYPE_FREE				0x8
	int m_type;
	int m_devCount;
	time_t m_expireDate;
	int m_limitdays;
	int m_tscount;
};

struct st_raw_omlic
{
	std::string m_strComany;
	std::string m_strEmail;
	std::string m_strLicense;
};

#define OMLIC_TYPE_RAW		0x1
#define OMLIC_TYPE_DECRYPT	0x2

int GetLicInfo(std::string addr,struct st_omlic *pOL,struct st_raw_omlic *pROL,int type=OMLIC_TYPE_DECRYPT,unsigned short nPort=8123,int nTimeout=20);



#endif