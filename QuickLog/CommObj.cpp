// D:\work\test\AllNetWork\Data\CommObj.cpp : 实现文件
//

#include "stdafx.h"

#include "CommObj.h"
#include "MXDBOp.h"
#include "sysop.h"
#include "mxDcry.h"
#include "searchdevicecondition.h"
#include "ccugapi.h"
#include "mstat.h"
#include "shlwapi.h"
#include "MxOp.h"
#include "TDBOP.h"
#include <libchen/Util.h>
#define SYSLOGAPP

static CString s_strText_Cn[] = 
{
	"2层交换机",
	"主机",
	"防火墙",
	"集线器",
	"3层交换机",
	"路由器",
	"其他网络设备",
	"被禁止",
	"管理对象被禁止",
	"监测器ID:",
	"的监测点是 ",
	"备注",
};

static CString s_strText_En[] = 
{
	"Layer 2 switches",
	"Host",
	"Firewall",
	"Hub",
	"Layer 3 switches",
	"Router",
	"Other network devices",
	"Banned",
	"Device is disable",
	"which is depended on:",
	"Monitor:",
	"Note",
};

PairData& PairData::operator=(PairData A)
{
	strLabel =A.strLabel;
	strValue=A.strValue;
	strValueLabel=A.strValueLabel;
	bIsPwd = A.bIsPwd;

	return *this;
}
//CPairDataObj

void CPairDataObj::GetOut(PairData& pd)
{
	pd.strLabel=strLabel ;
	pd.strValue=strValue;
	pd.strValueLabel=strValueLabel;
	pd.bIsPwd=bIsPwd;
}
void CPairDataObj::SaveIn(PairData& pd)
{
	strLabel =pd.strLabel;
	strValue=pd.strValue;
	strValueLabel=pd.strValueLabel;
	bIsPwd = pd.bIsPwd;
}
void CPairDataObj::Serialize( CArchive& ar ) 
{
	CString strTemp;
	if(ar.IsStoring())
	{
		strTemp=strLabel.c_str();
		ar<<strTemp;
		strTemp=strValue.c_str();
		ar<<strTemp;
		strTemp=strValueLabel.c_str();
		ar<<strTemp;
		ar<<bIsPwd;
	}else
	{
		ar>>strTemp;
		strLabel=strTemp.GetBuffer();
		ar>>strTemp;
		strValue=strTemp.GetBuffer();
		ar>>strTemp;
		strValueLabel=strTemp.GetBuffer();

		ar>>bIsPwd;
	}
	//	return TRUE;
}
// CCommObj


MXHANDLE CCommObj::m_hDyn =MX_INVALID_HANDLE;
MXHANDLE CCommObj::m_hSimpleDyn=MX_INVALID_HANDLE;
MXHANDLE CCommObj::m_hTable=MX_INVALID_HANDLE;
MXHANDLE CCommObj::m_hMq=MX_INVALID_HANDLE;
MXHANDLE CCommObj::m_hStatMq=MX_INVALID_HANDLE;
MXHANDLE CCommObj::m_hPlug=MX_INVALID_HANDLE;
MXHANDLE CCommObj::m_hNNM=MX_INVALID_HANDLE;
MXHANDLE CCommObj::m_hAlert=MX_INVALID_HANDLE;
CLogServerHandles CCommObj::m_TaskServerHandles;

CCriticalSection CCommObj::m_critDyn;
CCriticalSection CCommObj::m_mqCrit;
CCriticalSection CCommObj::m_statMqCrit;
CCriticalSection CCommObj::m_plugCrit;
CCriticalSection CCommObj::m_alertCrit;

CObjParam& CObjParam::operator=(CObjParam& A)
{
	this->m_szPage=A.m_szPage;
	for(std::map<std::string,PairData >::iterator it =A.m_propmap.begin();
		it!=A.m_propmap.end();it++)//非固定属性 ，主要属性
	{
		m_propmap[(*it).first]=(*it).second;
	}

	return *this;
}


CCommObj::CCommObj()
: m_nAFTCount(0)
,m_nARPCount(0)
//, m_nIntFaceCount(0)
{

	m_nStat =NODATASTAT;
	m_bChecked =FALSE;
	m_bDisable =FALSE;
	m_bParentDisable =FALSE;
	m_nIndex =-1;
	m_strId=_T("");
	m_strKey=_T("");
	m_pView=NULL;
	m_bDelete =FALSE;
	m_tmLastLook=m_tmHappen=chen::TimeFace(1990,1,1,1,1,1);
	m_nSelf=-1;
	m_bGetDyn =TRUE;
	m_bLoad=FALSE;
	m_strUpdateTime=_T("");
	m_nLoadSize=0;
	m_nMonitorWay = 0;
	m_bNewUpdate =FALSE;
	m_bSort = FALSE;
	m_bNewAdd =FALSE;
	m_bTmpBan = FALSE;
	m_nNetConfig = net_unkown;
}

CCommObj::~CCommObj()
{
}


// CCommObj 成员函数
