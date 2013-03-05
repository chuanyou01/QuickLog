#ifndef TREEDB_TREEDB_H_
#define TREEDB_TREEDB_H_

#include <iostream>
#include <string>
#include <list>
#include <LibChen/VariableData.h>
#include <LibChen/TimeFace.h>
#include <map>
#include <hash_map>

using namespace std;


#ifdef _TREEDBLIB_
#define MXDI_API	
#else
#ifdef TREEDB_EXPORTS
#define TREEDB_API __declspec(dllexport)
#else
#define TREEDB_API __declspec(dllimport)
#endif
#endif

typedef void* TREEDBFILEHANDLE;
typedef void* TREEHANDLE;
#define MX_INVALID_TREEHANDLE	(TREEHANDLE)~0

#define OTDB_OPENEXIST			0x00000001
#define OTDB_CREATENEW			0x00000002
#define OTDB_ALWAYSCREATENEW	0x00000004

TREEDB_API
int TDB_OpenFile(const char *filePath,TREEDBFILEHANDLE &hd,unsigned int flag=OTDB_OPENEXIST);

#define OTDBKF_CREATEMAINKEY		0x00000001
#define OTDBKF_DELETEMAINKEY		0x00000002
#define OTDBKF_RENAME				0x00000004
#define OTDBKF_OPENEXIST			0x00000008
#define OTDBKF_OPENCHILD			0x00000010
#define OTDBKF_DOTSTLYPATH			0x00000020

TREEDB_API
int TDB_OpenKey(TREEDBFILEHANDLE &tfhd,TREEHANDLE &hd,std::string mainKey,std::string subKey,unsigned int flag=OTDBKF_OPENEXIST);

TREEDB_API
int TDB_SelectSubKeys(TREEHANDLE &hd,std::list< std::string > &keylist);

TREEDB_API
int TDB_GetKeyProperty(TREEHANDLE &hd,std::string Name,chen::VariableData &rv);

typedef std::pair<std::string ,chen::VariableData > TDBPROPERTY;
typedef std::list<TDBPROPERTY> TDBPROPERTYSET;

TREEDB_API
int TDB_SelectKeyPropertys(TREEHANDLE &hd,TDBPROPERTYSET &PropList);

TREEDB_API
int TDB_ReopenSubKey(TREEHANDLE &hd,std::string SubKey,unsigned int flag=OTDBKF_OPENEXIST);

TREEDB_API
int TDB_RenameKeys(TREEHANDLE &hd,std::string newKeyName);

TREEDB_API
int TDB_AppendSubKey(TREEHANDLE &hd,std::string &subKey);

TREEDB_API
int TDB_AppendProperty(TREEHANDLE &hd,std::string PropertyName,chen::VariableData &rv);

TREEDB_API
int TDB_DeleteKey(TREEHANDLE &hd);

TREEDB_API
int TDB_DeleteProperty(TREEHANDLE &hd,std::string PropertyName);

TREEDB_API
int TDB_EditProperty(TREEHANDLE &hd,std::string PropertyName,chen::VariableData &rv);

TREEDB_API
int TDB_GetAllMainKeys(TREEHANDLE &hd,std::list< std::string > &namelist);

TREEDB_API
int TDB_ExportSubTree(TREEHANDLE &hd,std::string fileName,bool isOverlay=false);

TREEDB_API
int TDB_ImportSubTree(TREEDBFILEHANDLE &hd,std::string fileName,bool isCreateNew=false);

TREEDB_API
void TDB_CloseTDBHandle(TREEHANDLE &hd);

TREEDB_API
void TDB_CloseTDBFHandle(TREEDBFILEHANDLE &tfhd);





#endif
