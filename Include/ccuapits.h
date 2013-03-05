#ifndef CCUAPI_CCUAPITS_H_
#define CCUAPI_CCUAPITS_H_

/***********************************************************************************************/
/**						���ļ�ʵ��CCUӦ�ó���ӿ�											   */
/**						�汾:1.0.1.2														   */
/**						��Ȩ����:2010@ ��������ʱ���Ƽ����޹�˾								   */
/**						��Ȩ�����˱�������Ȩ��												   */
/***********************************************************************************************/

#include "ccuapidef.h"
#include <iostream>
#include <string.h>

struct RegTSInfo
{
	std::string HostName;
	std::string MQName;
	std::string MQHost;
	unsigned int CPUCount;
	double CPUClockSpeed;
	unsigned int MemeorySize;
	unsigned int Status;
	unsigned int Memorytype;
	unsigned int Netcardtype;
	bool IsLocked;
	bool IsLogDBServer;

};

struct RegTSInfoEx
{
	std::string HostName;
	std::string MQName;
	std::string MQHost;
	std::string ID;			//ÿ��TS��ΨһID
	std::string Label;		//TS��ʾ����
	unsigned int CPUCount;
	double CPUClockSpeed;
	unsigned int MemeorySize;
	unsigned int Status;
	unsigned int Memorytype;
	unsigned int Netcardtype;
	bool IsLocked;
	bool IsLogDBServer;
	bool IsStoped;

};

struct RegTSReply
{
	std::string BackupCCU;
	std::string MQName;
	std::string MQHost;
	bool IsNew;
};

struct RegTSReplyEx
{
	std::string BackupCCU;
	std::string MQName;
	std::string MQHost;
	bool IsNew;
	std::string ErrorDes;
	std::string ID;			//CCU ǿ��ָ������ID
	std::string Label;		//CCU ǿ��ָ������ʾ����

};

CCUAPI_API
int RegisterTS(const char *ccuaddr,const struct RegTSInfo &rti,struct RegTSReply &rtr);

//for new taskserver id
CCUAPI_API
int RegisterTSEx(const char *ccuaddr,const struct RegTSInfoEx &rti,struct RegTSReplyEx &rtr);


CCUAPI_API
int DoTSHeartbeat(const char *ccuaddr,unsigned int status);

//for new taskserver id(name)
CCUAPI_API
int DoTSHeartbeatEx(const char *ccuaddr,const char * tsname,unsigned int status);


CCUAPI_API
int DoDSHeartbeat(const char *ccuaddr,unsigned int status);

//for new dbserver id(name)
CCUAPI_API
int DoDSHeartbeatEx(const char *ccuaddr,const char *dbsname,unsigned int status);


struct RegDSInfo
{
	std::string hostname;
	unsigned int type;
	unsigned int status;
	bool isLocked;
};

struct RegDSInfoEx
{
	std::string hostname;
	unsigned int type;
	unsigned int status;
	bool isLocked;
	std::string ID;
	std::string Label;
};


CCUAPI_API
int RegisterDS(const char *ccuaddr,const struct RegDSInfo &ri,std::string &strBackCCU);

CCUAPI_API
int RegisterDSEx(const char *ccuaddr,const struct RegDSInfoEx &ri,std::string &strBackCCU,std::string &strLabel,std::string &strID);






#endif