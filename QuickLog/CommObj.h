
#pragma once

#include <string>
#include <map>


#include "mxdi.h"
#include "taskserverhandles.h"
#include "returnitem.h"
#include <afxmt.h>
#include "deviceprop.h"
#include "MonitorStat.h"
#include "Depends.h"
#include "struct.h"
// CCommObj ����Ŀ��
//ͨ���� ������ʾ se group device monitor

class CReturn;
class CMXDBOp;

class PairData
{
public:
	PairData()
	{
		strLabel ="";
		strValue="";
		strValueLabel="";
		bIsPwd = false;
	};
	PairData& operator=(PairData A);
public:
	string strLabel;		//��ǩ
	string strValue;		//��ʵ value
	string strValueLabel;   //�����õ�value,���� bool 1:�� 0 ����
	bool bIsPwd;				//�Ƿ�������

};


class CPairDataObj  : public CObject
{
public:
	CPairDataObj()
	{
		strLabel ="";
		strValue="";
		strValueLabel="";
		bIsPwd = false;
	};
	
public:
	void  Serialize( CArchive& ar ) ;
	string strLabel;		//��ǩ
	string strValue;		//��ʵ value
	string strValueLabel;   //�����õ�value,���� bool 1:�� 0 ����
	bool bIsPwd;				//�Ƿ�������
	void SaveIn(PairData& pd);
	void GetOut(PairData& pd);
};

typedef std::map<std::string,PairData >  PROPPERTYVALUEMAP;
typedef std::list<PROPPERTYVALUEMAP> LSTPROPPERTYVALUEMAP;
typedef std::map<std::string,LSTPROPPERTYVALUEMAP> PRROPERTMAP;
class CMXDBOp;
class CObjParam :public CObject
{
public:
	std::string  m_szPage;
	std::map<std::string,PairData >  m_propmap; //�ǹ̶����� ���������ԡ�
	std::map<std::string,PairData > m_newpropmap;
	CObjParam& operator=(CObjParam& A);
	void  Serialize( CArchive& ar ) ;	
};
class CCommObj : public CObject
{
public:
	CCommObj();
	virtual ~CCommObj();
private:
	CString m_strLabel;
public:
	BOOL  m_bNewUpdate;//��ʱ����
	static CLogServerHandles m_TaskServerHandles;
	
	BOOL m_bDelete;
	CTime tmUpdate;
	CView *m_pView;
	CString m_strServer;
	CString m_strId;
	CString m_strKey;
	CString m_strDes;//  �顢������󡢼��� ��ʱ������
	CString m_strRemark;//��ע
	BOOL m_bDisable;  //�Ƿ��ֹ
	BOOL m_bParentDisable;  //�����Ƿ��ֹ
	BOOL m_bSort;//�༭�Ƿ�������

	BOOL m_bChecked;   //�û�Ȩ����ʹ��
	int m_nIndex;
	int m_nKeepTimes;
	chen::TimeFace		m_ctmStateChangeTime;
	chen::TimeFace		m_tmHappen;
	chen::TimeFace		m_tmLastLook;
	std::list<chen::VariableData> m_rvlstLast;// z���¼�¼
	
	int m_nStat;
	int m_nShowStat;
	std::map<std::string,PairData >  m_mainpropmap; //�ǹ̶����� ����Ҫ����
	std::map<std::string,PairData >  m_mainNewProMap;
	
	std::map<std::string,PairData >  m_temppropmap; //��ʱ���� ������Ҫ�洢
	CList<CObjParam*> m_lstParam;
	
	CMonitorThreshold        m_cdErrorAlert;
    CMonitorThreshold        m_cdWarnningAlert;
    CMonitorThreshold        m_cdNormalAlert;

	CDepends				m_denpend;
	int m_nType;   //ObjType ��������
	CMap<CString,LPCTSTR, int,int > m_mapField;
	BOOL m_bGetDyn;
	BOOL		m_bTmpBan;// ��ʱ��ֹ

	enum ISNETCONFIG
	{
		net_unkown = -1,
		net_false =0,
		net_true,
	};

	int			m_nNetConfig;
public:
	//-------------------------------------------
	static CCriticalSection m_critDyn;
	CCriticalSection m_critStat;
	list<CDataPro*>		m_lstLastData;
	void ClearLstData();
	BOOL IsNetConfig();
	BOOL IsHide();
public:
	

	CCommObj& operator=(CCommObj& A);
	
	static MXHANDLE m_hDyn;
	static MXHANDLE m_hSimpleDyn;
	static MXHANDLE m_hTable;
	static MXHANDLE m_hMq;
	static MXHANDLE m_hStatMq;
	static MXHANDLE m_hPlug;
	static MXHANDLE m_hNNM;
	static MXHANDLE m_hAlert;
	
	int m_nSelf;

	

	//------------------------------------------------------------
	int m_nAFTCount;
	CString *strAFTIndex;
	CString *strAFTPort;
	CString *strAFTStat;
	CString *strAFTMac;

	void GetARPProperty(CString strServer, CString strId);
	int m_nARPCount;
	CString *strARPIndex;
	CString *strARPIp;
	CString *strARPMac;
	
	void  Serialize( CArchive& ar ) ;
	BOOL  m_bLoad;
	int  m_nLoadSize;
	CString m_strUpdateTime;
	
	int m_nMonitorWay;

	

	BOOL m_bNewAdd;

	
};
typedef CCommObj * PCommObj;


