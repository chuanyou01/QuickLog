#ifndef CCUAPI_CCUGAPI_H_
#define CCUAPI_CCUGAPI_H_

/***********************************************************************************************/
/**						���ļ�ʵ��CCUӦ�ó���ӿ�											   */
/**						�汾:1.0.1.2														   */
/**						��Ȩ����:2010@ ��������ʱ���Ƽ����޹�˾								   */
/**						��Ȩ�����˱�������Ȩ��												   */
/***********************************************************************************************/


#include "ccuapidef.h"
#include <iostream>
#include <string.h>
#include <list>

CCUAPI_API
int GetTaskServerList(const char *ccuaddr,std::list<std::string > &namelist);


struct TSInfoList
{
	std::string ID;
	std::string Label;
	std::string Address;

	struct TSInfoList * Next;

};
CCUAPI_API
int GetTaskServerListEx(const char *ccuaddr,struct TSInfoList **pTSList);

CCUAPI_API
void FreeTSInfoList(struct TSInfoList *pTSList);

struct DBSInfoList
{
	std::string ID;
	std::string Label;
	std::string Address;

	struct DBSInfoList * Next;

};
CCUAPI_API
int GetDBServerListEx(const char *ccuaddr,struct DBSInfoList **pDBSList);

CCUAPI_API
void FreeDBSInfoList(struct DBSInfoList *pDBSList);







#define CCU_GTT_ALL			1
#define CCU_GTT_LIVE		2
#define CCU_GTT_DEAD		3
#define CCU_GTT_LOCKED		4
#define CCU_GTT_NOLOCKED	5
#define CCU_GTT_STOPED		6

CCUAPI_API
int GetTaskServerListByType(const char *ccuaddr,std::list<std::string > &namelist,unsigned int type);


CCUAPI_API
int QueryWhereDev(const char *ccuaddr,const char *name,std::string &serverIP);

CCUAPI_API
int GetDBServerList(const char *ccuaddr,std::list<std::string > &namelist);


CCUAPI_API
int StopTaskServer(const char *ccuaddr,const char *taskservername);

CCUAPI_API
int StartTaskServer(const char *ccuaddr,const char *taskservername);

CCUAPI_API
int BalanceDBS(const char *ccuaddr);


struct CCUOverall
{
	time_t		starttime;
	unsigned int initusedtime;		//seconds
	unsigned int devcount;
	unsigned int taskcount;
	unsigned int tscount;
	unsigned int livetscount;
	unsigned int dbscount;
	unsigned int livedbscount;
	unsigned int taskplancount;
	unsigned int concurrentcount;
	unsigned int currentTSRegisterCount;

	////////////////////////////

	unsigned int perdbserverload;
	double currentpertsunitload;
	double allfreeload;

	double totalweight;
	double freeweight;
	double allfixweight;
	double skipweight;
	double fixnolockedweight;
	double skipandnofixweight;

};

CCUAPI_API
int QueryOverall(const char *ccuaddr,struct CCUOverall &cov);


struct TSInfo
{
	std::string name;
	std::string commqname;
	std::string commqhost;

	unsigned int taskcount;
	unsigned int devcount;
	unsigned int virtualTaskCount;
	double currentLoad;
	double capability;
	time_t lastHeartBeat;
	bool isstoped;
	bool islocked;
	bool isdbserver;
	bool islive;
	unsigned int CPUCount;
	double CPUClockSpeed;
	unsigned int memorySize;

};
CCUAPI_API
int QueryTSInfo(const char *ccuaddr,const char *tsname,struct TSInfo &tsinfo);

CCUAPI_API
int QueryTSAddressByName(const char *ccuaddr,const char *tsname,std::string &addr);

CCUAPI_API
int QueryDBSAddressByName(const char *ccuaddr,const char *dbsname,std::string &addr);


struct DBSInfo
{
	std::string name;
	bool islive;
	bool islocked;
	bool isTS;
	bool isstoped;
	unsigned int devcount;
	unsigned int taskcount;
	time_t lastHeartBeat;
};

CCUAPI_API
int QueryDBSInfo(const char *ccuaddr,const char *dbsname,struct DBSInfo &tsinfo);

CCUAPI_API
int QueryWhereDevInTS(const char *ccuaddr,const char *devname,std::string &tsname);

CCUAPI_API
int QueryWhereTaskInTS(const char *ccuaddr, const char *taskname,std::string &tsname);

CCUAPI_API
int QueryAllDevInTS(const char *ccuaddr,const char *tsname,std::list<std::string > &devlist);

//����ָ����TS����ʾ��(Label)
CCUAPI_API
int RenameTS(const char *ccuaddr,const char *tsname,const char *newlabel);

//ɾ��ָ����TS(ͬʱ��CCU�˵������ļ���ɾ��)
CCUAPI_API
int RemoveTS(const char *ccuaddr,const char *tsname);

//ɾ��ָ����DBServer(LogServer)(ͬʱ��CCU�˵������ļ���ɾ��)
CCUAPI_API
int RemoveDBS(const char *ccuaddr,const char *dsname);

//ɾ������״̬Ϊ����Ծ��TS�Լ�����Ծ��DBServer(LogServer)(ͬʱ��CCU�˵������ļ���ɾ��)
CCUAPI_API
int RemoveDeadTS(const char *ccuaddr,const char *tsname=NULL);








#endif