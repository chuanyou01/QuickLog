#ifndef MXDI_MXDI_H_
#define MXDI_MXDI_H_


#include <iostream>
#include <string>
#include <list>
#include <libchen/VariableData.h>
#include <libchen/TimeFace.h>
#include <map>
#include <hash_map>

using namespace std;

#ifdef _MXDILIB_
#define MXDI_API	
#else
#ifdef MXDI_EXPORTS
#define MXDI_API __declspec(dllexport)
#else
#define MXDI_API __declspec(dllimport)
#endif
#endif

#define MX_MONITORFLAG	"SubMonitor"
#define MX_DEVFLAG		"SD"
#define MX_GROUPFLAG	"SG"


typedef void* MXHANDLE;
#define MX_INVALID_HANDLE	(MXHANDLE)~0

MXDI_API
void SetServerPort(unsigned short port);

MXDI_API
unsigned short GetServerPort();


MXDI_API
void SetTimeout(int timer);

MXDI_API
int GetTimeout();


/////////////////////mq////////////////////////

MXDI_API
void CloseMXHandle(MXHANDLE &hd);

#define OMQF_OPENEXISIT		0x001
#define OMQF_CREATENEW		0x002
#define OMQF_OPENMULTI		0x040

#define OMQT_COMMONMQ	0x00000004
#define OMQT_PRIORITYMQ	0x00000008
#define OMQT_TEMPMQ		0x00000010



MXDI_API
int OpenMQ(std::string addr,std::string mqName,std::string PassWord,MXHANDLE &hd,unsigned int flag=OMQF_OPENEXISIT,int type=OMQT_COMMONMQ);

#define PML_COMMON		0x01
#define PML_HIGHER		0x02
#define PML_LOWER		0x03

//MXDI_API
//int PushMQMessage(MXHANDLE &hd,std::string Message,std::string Label,int level=PML_COMMON);

MXDI_API
int PushMQMessage(MXHANDLE &hd,const chen::VariableData &rv,std::string Label,int level=PML_COMMON);

#define MX_INFINITE		0xFFFFFFFF

MXDI_API
int PopMQMessage(MXHANDLE &hd,std::string &Message,std::string &Label,time_t &createTime,unsigned int timer=0);

MXDI_API
int PopMQMessage(MXHANDLE &hd,chen::VariableData &rv,std::string &Label,time_t &createTime,unsigned int timer=0);

MXDI_API
int PeekMQMessage(MXHANDLE &hd,std::string &Message,std::string &Label,time_t &createTime,unsigned int timer=0);

MXDI_API
int PeekMQMessage(MXHANDLE &hd,chen::VariableData &rv,std::string &Label,time_t &createTime,unsigned int timer=0);

MXDI_API
int DeleteMQ(MXHANDLE &hd);

MXDI_API
int ClearMQ(MXHANDLE &hd);

MXDI_API
int GetMQMessageCount(MXHANDLE &hd,int &nCount);

MXDI_API
int GetMQAllNames(std::string addr,std::list< std::string > &namelist);

///////////////////////////////ct////////////////////////////////////////////

typedef std::pair<std::string ,chen::VariableData > PROPERTY;
typedef std::list<PROPERTY> PROPERTYSET;

#define OTKF_CREATEMAINKEY		0x00000001
#define OTKF_DELETEMAINKEY		0x00000002
#define OTKF_RENAME				0x00000004
#define OTKF_OPENEXIST			0x00000008
#define OTKF_OPENCHILD			0x00000010
#define OTKF_DOTSTLYPATH		0x00000020


MXDI_API
int OpenKey(std::string addr,std::string MainKey,std::string SubKey,MXHANDLE &hd,unsigned int flag=OTKF_OPENEXIST);

MXDI_API
int SelectSubKeys(MXHANDLE &hd,std::list< std::string > &keylist);

 MXDI_API
int GetKeyProperty(MXHANDLE &hd,std::string Name,chen::VariableData &rv);

MXDI_API
int SelectKeyPropertys(MXHANDLE &hd,PROPERTYSET &PropList);

MXDI_API
int ReopenSubKey(MXHANDLE &hd,std::string SubKey,unsigned int flag=OTKF_OPENEXIST);

MXDI_API
int RenameKeys(MXHANDLE &hd,std::string newKeyName);

MXDI_API
int AppendSubKey(MXHANDLE &hd,std::string &subKey);

MXDI_API
int AppendProperty(MXHANDLE &hd,std::string PropertyName,chen::VariableData &rv);

MXDI_API
int DeleteKey(MXHANDLE &hd);

MXDI_API
int DeleteProperty(MXHANDLE &hd,std::string PropertyName);

MXDI_API
int EditProperty(MXHANDLE &hd,std::string PropertyName,chen::VariableData &rv);

MXDI_API
int GetAllMainKeys(std::string addr,std::list< std::string > &namelist);

MXDI_API
int ExportSubTree(MXHANDLE &hd,std::string fileName,bool isOverlay=false);

MXDI_API
int ImportSubTree(std::string addr,std::string fileName);

MXDI_API
void CloseCTHandle(MXHANDLE &hd);

//////////////////////////////////db///////////////////////////////////////////////////

typedef __int64 index_t;

#define ODBF_OPENEXIST		0x00000001
#define ODBF_CREATENEW		0x00000002

MXDI_API
int OpenDB(std::string addr,std::string dbName,std::string user,std::string pwd,MXHANDLE &hd,unsigned int flag=ODBF_OPENEXIST);

typedef std::pair<std::string ,unsigned char >	FIELDPAIR;
typedef std::list< FIELDPAIR > FIELDPAIRLIST;

#define CTF_COMMONTABLE	0x00000002
#define CTF_TEMPTABLE	0x00000004
#define CTF_SYSTEMTABLE 0x00000008
#define CTF_DYN			0x00000010
#define CTF_MCACHE		0x00000020

MXDI_API
int CreateTable(MXHANDLE &hd,std::string tableName,FIELDPAIRLIST &fieldList,unsigned int flag,int mType=0);

MXDI_API
int CreateTableEx(MXHANDLE &hd,std::string tableName,FIELDPAIRLIST &fieldList,unsigned int flag,const char *mType=NULL);

typedef std::list<chen::VariableData > FIELDVALUELIST;

MXDI_API
int AppendRecord(MXHANDLE &hd,std::string tableName,FIELDVALUELIST &vlist);

MXDI_API
int AppendRecord(MXHANDLE &hd,std::string tableName,FIELDVALUELIST &vlist,index_t &rid);

MXDI_API
int AppendRecordAndCtime(MXHANDLE &hd,std::string tableName,FIELDVALUELIST &vlist,time_t ctm);

MXDI_API
int AppendRecord(MXHANDLE &hd,std::string tableName,std::list<std::string > &fieldList,FIELDVALUELIST &vlist);

MXDI_API
int DeleteTable(MXHANDLE &hd,std::string tableName);

MXDI_API
int QuickDeleteTable(MXHANDLE &hd,std::string tableName);

MXDI_API
int RenameTable(MXHANDLE &hd,std::string tableName,std::string newTableName);

typedef std::pair<std::string ,chen::VariableData > FIELDVALUE;
//typedef std::list<FIELDVALUE> RECORD;

typedef std::map<std::string ,chen::VariableData> VALUEMAP;

MXDI_API
int SelectRecordByTimeSpan(MXHANDLE &hd,MXHANDLE &hRS,std::string tableName,chen::TimeSegment recentSpan);

MXDI_API
int SelectRecordByRecentCount(MXHANDLE &hd,MXHANDLE &hRS,std::string tableName,int count);

MXDI_API
int SelectRecordByTime(MXHANDLE &hd,MXHANDLE &hRS,std::string tableName,chen::TimeFace tBegin,chen::TimeFace tEnd);

MXDI_API
int SelectAllRecord(MXHANDLE &hd,MXHANDLE &hRS,std::string tableName);

MXDI_API
int GetRecordCount(MXHANDLE &hRS,int &nCount);

MXDI_API
int GetFields(MXHANDLE &hRS,FIELDPAIRLIST &fields);



MXDI_API
int GetCursor(MXHANDLE &hRS,MXHANDLE &hCR);

MXDI_API
int CursorNext(MXHANDLE &hCR,VALUEMAP &vm,index_t &rid,chen::TimeFace &ctm);

MXDI_API
int CursorPre(MXHANDLE &hCR,VALUEMAP &vm,index_t &rid,chen::TimeFace &ctm);

MXDI_API
int ResetCursor(MXHANDLE &hCR);

MXDI_API
void CloseDBHandle(MXHANDLE &hd);

MXDI_API
void CloseRSHandle(MXHANDLE &hRS);

MXDI_API
void CloseCRHandle(MXHANDLE &hCR);

MXDI_API
int GetAllTables(MXHANDLE &hd,std::list<std::string > &tables);

MXDI_API
int UpdateRecord(MXHANDLE &hd,std::string tableName,index_t id, FIELDVALUELIST &vlist);

#define DDRC_OVER	0x0001
#define DDRC_EQUAL	0x0002
#define DDRC_LESS	0x0003
#define DDRC_OVEREQUAL	0x0004
#define DDRC_LESSEQUAL	0x0005

MXDI_API
int DeleteRecord(MXHANDLE &hd,std::string tableName,index_t id,unsigned char condition=DDRC_EQUAL);

MXDI_API
int DeleteRecord(MXHANDLE &hd,std::string tableName,chen::TimeFace dtm,unsigned char condition);

MXDI_API
int SelectRecordByRID(MXHANDLE &hd,MXHANDLE &hRS,std::string tableName,index_t rid,const char condition=DDRC_EQUAL);

MXDI_API
int SelectRecordByField(MXHANDLE &hd,MXHANDLE &hRS,std::string tableName,const char *field,const char condition,const chen::VariableData &fValue,bool bSingle);


#define IRF_BEFOR	0x001
#define IRF_AFTER	0x002
#define IRF_APPEND	0x003
#define IRF_FIRST	0x004

MXDI_API
int InsertRecord(MXHANDLE &hd,std::string tableName,index_t id,FIELDVALUELIST &vlist,unsigned char flag=IRF_BEFOR);

struct TableDYN
{
	chen::TimeFace m_LastAccessTime;
	int m_State;
	chen::TimeFace m_LastStateChangeTime;
	int m_LastStateKeepTimes;
	int m_MType;
	int m_PreState;
	std::string m_sType;
};

MXDI_API
int GetDYN(MXHANDLE &hd,std::string tableName,struct TableDYN &tdyn,std::list<chen::VariableData> &vlist);

MXDI_API
int GetSimpleDYN(MXHANDLE &hd,std::string tableName,struct TableDYN &tdyn);

MXDI_API
int BToDYN(const char *buf,int dlen,struct TableDYN &tdyn,std::list<chen::VariableData> &vlist);

MXDI_API
int GetAllDYNTableState(MXHANDLE &hd,std::string groupName,stdext::hash_map<unsigned int,unsigned char > &nStateMap,stdext::hash_map<std::string,unsigned char > &sStateMap,bool isQuickMode=true);

////////////////////////////DOG///////////////////


MXDI_API
int ReadDogInfo(std::string addr,bool &isDevLimit,bool &isTimeLimit,chen::TimeFace &limitTime,std::map<std::string ,unsigned short> &DevInfo);


////////////////////////////Other/////////////////

MXDI_API
int ViewReport(std::string addr,bool &isTimeLimit,bool &isDevLimit,chen::TimeFace &limitTime,bool &isTSLimit,bool &isDevCountLimit,unsigned int &nDevCount,unsigned int &nTSCount,std::string &userName);

MXDI_API
int GetServerTime(std::string addr,chen::TimeFace &serverTime);

MXDI_API
int ReadIniFile(std::string addr,std::string strFileName,std::string strSection,std::string strKey,std::string &value);

MXDI_API
int WriteIniFile(std::string addr,std::string strFileName,std::string strSection,std::string strKey,std::string value);

MXDI_API
int GetMxmcState(std::string addr,bool &isRunning);

MXDI_API
int GetFileFromServer(std::string addr,std::string strRFileName,std::string strLFileName, bool isOverWrite=true);

MXDI_API
int GetInfo(std::string addr,unsigned int &issueType,unsigned int &version,unsigned int &objCount,chen::TimeFace &expireDate);

MXDI_API
int GetIssueDescription(std::string addr,unsigned int issueType,std::string &description);

MXDI_API
int RegisterOM(std::string addr,std::string strCompany,std::string strEmail,std::string regString);


///////////////////////////////////////////

MXDI_API
std::string FindParentID(std::string id);

MXDI_API
std::string FindParentGroupID(std::string id);

MXDI_API
std::string FindSEID(std::string id);

MXDI_API
std::string FindEntityID(std::string monitorID);

MXDI_API
bool isMonitorID(std::string id);

MXDI_API
std::string GetMXInstallPath();


MXDI_API
void ParseVersion(unsigned int ver,int &v1,int &v2,int &v3,int &v4);

MXDI_API
std::string ParseVersionToString(unsigned int ver);

MXDI_API
unsigned int SetupVersion(unsigned int v1,unsigned int v2,unsigned int v3,unsigned v4);




#endif

