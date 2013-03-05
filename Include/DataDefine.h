
#include <string>
using namespace std;


#if _MSC_VER > 1000
#pragma once
#else
#endif

#define MX_MAX_INDEX		0x0fffffff

#define DATADB				"mxdb"
#define MONITORALERTMQ		"BMP_Alert"
#define ALERTMQ				"alertmq"
#define INIKEY				"MX_INI"
#define ENTITYKEY			"EntityTemplate"
#define MONITORKEY			"PluginData"
#define MXSEKEY				"MXSE"
#define NNMKEY				"NNM"
#define STINGTABLEKEY		"StringTable"
#define SERVERADDR			"127.0.0.1"
#define NNMCMDMQ			"nnm_cmd_mq"

#define MXSESERVER			"Svr"
#define MXSENETWORK			"Net"
#define MXSEAPP				"App"

#define	CLIENTMQ			"BMPClient1_"
#define TOPOBACK			"Topo-Backup"

#define SUBGROUP			".SG"
#define SUBDEVICE			".SD"
#define ROOTID				"1"
#define GISKEY				"GIS"
//Column Label of MXDB
//Event Log
static const char CREATETIME[]=			"CreatTime";
static const char MONITORID[]=			"MonitorId";
static const char DEVICEID[]=			"DeviceId";
static const char SOURCE[]=				"Source";
static const char EVENTLEVEL[]=			"EventLevel";
static const char EVENTCLASS[]=			"EventType";
static const char REMARK[]=				"Remark";
static const char MONITORSTATUS[]=		"MonitorStat";
static const char LASTMONITORSTAT[]=	"LastMonitorStat";

//Alert Report
static const char ALERTID[]=			"AlertId";
static const char SENDTIME[]=			"SendTime";
static const char SENDTYPE[]=			"SendType";

/////////////////////////////////////////////////////////////////////////////////////////////////////////////

// SE Group || SE || Group(Sub Group) || Device || Monitor
enum CriticalLevel {NORMALLEVEL=1,CRITICALLEVEL=7};
enum VERSIONTYPE {TRAILTYPE=0,FULLTRAILTYPE=1};
enum ObjType{SETYPE=4, GROUPTYPE = 3,DEVICETYPE = 2,MONITORTYPE = 1,VGROUP=5,VDEVICE=6,VMONITOR=7 , NETCFGTYPE};
enum FINDTIME{CURDAY=0,THREEDAY=1,ONEWEEK=2,ONEMONTH=3,SELFTIME=4 };
enum INCLUDETYPE{INCLUDEDEVICE=0,INCLUDEVIRSUAL };
enum DEVICEPROPERTYTYPE{DEVICESINGLEPROPERTY=0,DEVICELISTPROPERTY=1,DEVICEFIXPROPERTY=2};

//Time Mode

#define TIMEMODE_ONEDAY		0
#define TIMEMODE_THREEDAYS	1
#define TIMEMODE_ONEWEEK	2
#define TIMEMODE_ONEMONTH	3

//enum RADIOCAL{GOODRADIO=-10,ERRORRADIO=-11};

enum TOPOSTATE{REAL = 1,HISTORY,DIFF};           //Ф��---�����Ҽ���ʾ��·��������״̬���ز�
enum REPROTTYPE{ DAYREPORT=0,WEEKREPORT=1,MONTHREPORT=2};
const int AlAWYSMONITOR = 0x03;
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// monitor state
// ������ || ���� || ����״̬ || ���� || ��ֹ || ���ش����
enum MONITORSTAT{GOODSTAT=1,WARNINGSTAT=2,ERRORSTAT=3,BADSTAT=4,DISABLESTAT=5,NODATASTAT=0  ,ALLSTAT =6 };
enum SHOWSTAT{UNKNOWNSTATUS = 0, GOODSTATUS = 1, WARNINGSTATUS = 2, ERRORSTATUS = 3,  DISABLESTATUS = 5, ALLSTATUS = 6};
enum WMISCRIPT{SENDMSG=0 ,RESTATMACHINE=1,RESTARTSERVICE=2};
//--------------���β˵�----------------------------------------------
enum MenuType{DATATYPE=0, ALERTROOTTYPE=1,ALERTCONFTYPE=2,ALERTREPORTTYPE=3,  
			ALERTTYPE=4  ,REPORTYPE=5 , TOPNTYPE=6, REALTIMETYPE=7,REALTIMETPLTYPE=8,
			STATISTICTYPE=9 ,ANALYSISREPORT=10,ANALYSISTPLREPORT=11,HANDTAILORREPORT,
			CURRENTTRAFFIC,TRAFFICHISTORY,TRAFFICHISTORYTPL ,TOPNTPLTYPE,DEVICEREPORT,
			REALPARAMTYPE,REALMONITORTYPE ,REALMONITORTYPETPL,AVGPARAMREPORT,AVGPARAMREPORTTPL,
			ALLDEVICESTATREPROT,ALLMONITORSTATREPORT,TOOLS,PINGTOOL,TELNETTOOL,REMOTETOOL,FARCONTROL,
			TRACEROUTTOOL,HTTPTOOL,VISIOTOPOLOGY,VISIOTOPOLOGYMAP,MONITORSTATIC,VIRSUALGROUP,
			VIRSUALDEVICE,VIRSUALMONITOR,EVENTLOGTYPE,FAULTCATEGORY,FAULTREPORT,FAULTREPORTTPL
			,URLREPORT,ALLVGROUPSTATREPROT,IISREPORT, TOPOLOGY,SUBNETS,SUBNETGROUP, SUBNET,NETWORKSET,NET3WORK,NET2WORK
			,OTHERNETWORK, TOPOLOGYMAPS,MAINTOPO,TOPOLOGYMAP ,MACHINES,SNMPMACHINES,IPSETS,DEVICEEGISINFO,
			DEVICEEGISMAN,CNPCREPORT,OPERATELOGTYPE,HANDETAILOR,DYNVIEW,ALLGROUPDASHBORAD,TOPGROUPDASHBORAD,GROUPDASHBORAD
			,DAYTRAFFIC,DAYTRAFFICPL,LOGICMAP,LOGICGROUP};

enum SNMPDEVICETYPE {HUB=0,HOST=1,SWITCH2=2,SWITCH3=3,ROUTER=4, FIREWALL=5,OTHERSNMP=9,SUBTOPO=10};
enum TOPODATA {TOPOBOX=0, TOPOLINE=1};

#define TOPOMAIN	"maintopo"
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ����

#define MB_YES             0x0000000AL
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Ȩ�޶���
enum MX_Purview
{
    Add_Group       = 0x2,          // ������
    Add_Device      = 0x3,          // ���ӹ������
    Add_Monitor     = 0x4,          // ���Ӽ���
    Edit_SVSE       = 0x10,         // �༭SE
    Edit_Group      = 0x20,         // �༭��
    Edit_Device     = 0x30,         // �༭�������
    Edit_Monitor    = 0x40,         // �༭����
    Delete_Group    = 0x200,        // ɾ����
    Delete_Device   = 0x300,        // ɾ���������
    Delete_Monitor  = 0x400,        // ɾ������
    Refresh_Device  = 0x3000,       // ˢ�¹������
    Refresh_Monitor = 0x4000,       // ˢ�¼���
    Test_Device     = 0x30000,      // ���Թ������
};
static const char MX_ERRORSTOP[]					= "_monitorcondition";
#define ERRORSTOP			1
#define ERRORSTOPCONFIRM	2
#define MAXTABLENAMELENGTH		200
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// �ű�����
static const char MX_SENDMSG[]=					"������Ϣ";
static const char MX_RESTATMACHINE[]=           "������������";//
static const char MX_RESTARTSERVICE[]=			"������������";//
//����������������������������������������������������������


static const char BM_REFRESH_QUEUE[]            = "BMP_RefreshInfo_%s";  // ˢ�¶���ͷ
//static const char BM_REFRESH_QUEUE[]            = "MXBMP-ConfigTrack_%s";  // ˢ�¶���ͷ

static const char BM_CONFIG_TRACK[]             = "MXBMP-ConfigTrack_%s";  // ���ø��Ķ���ͷ
static const char BM_USER_OPERATE_LOG_TABLE[]   = "UserOperateLog";             // ������־

// ��������





static const char mxHealth[]                      = "mxHealth";   
static const char mxName[]                      = "mxname";                    // ����
static const char mxRetryTimes[]                      = "mxretrytimes";                    // ����




static const char mxIndex[]                 = "mxindex";                   // ��ʾ����
static const char mxDescription[]               = "mxdescription";             // ����


static const char mxDisable[]                   = "mxdisable";                 // �Ƿ��ֹ��true, false, time��

static const char mxConditionCount[]            = "mx_conditioncount";          // ��������ƥ��ʽ����
static const char mxParamValue[]                = "mx_paramvalue%d";            // ����ֵ
static const char mxParamName[]                 = "mx_paramname%d";             // ������
static const char mxOperate[]                   = "mx_operate%d";               // ����
static const char mxRelation[]                  = "mx_relation%d";              // ���ӷ�

static const char mxExpression[]                = "mx_expression";              // 

static const char mxPlan[]                      = "mx_plan";                    // ����ƻ�
static const char mxCheckErr[]                  = "mx_checkerr";                // У�����
static const char mxErrFreqSave[]               = "mx_errfreqsave";             // ����ʱ���Ƶ�ʴ洢
static const char mxErrFreq[]                   = "mx_errfreq";                 // ����ʱ���Ƶ��
static const char mxErrFreqUnit[]               = "mx_errfrequint";             // ������Ƶ�ʵ�λ
static const char mxErrFreqSec[]               = "mx_errfreqsec";             // ����ʱ���Ƶ�ʴ洢
static const char mxDay[]								= "dayctrl" ;            // �����ı���
static const char mxDayTime[]                           = "daytimectrl";
static const char mxTime[]                              = "timectrl";
static const char mxGroupBox[]                           = "groupbox";







/////////////////////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
static const char LeftParenthesis                 = '[';                          // ������
static const char RightParenthesis               = ']';                          // ������



/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
static const int  mxMaxBufferSize                  = 1024 * 50;                    // ��󻺳�����С





//-------------------snmp-------------------------------------------------------------------
static const char mxSysDescr[]                = "sysDescr";              // ��������
static const char mxSysContact[]              = "sysContact";                    // ����ƻ�
static const char mxSysName[]                 = "sysName";                // У�����
static const char mxSysObjectID[]                 = "sysObjectID";                // У�����

static const char mxSysLocation[]             = "sysLocation";              // ��������
static const char mxSysService[]              = "mx_SysService";                // У�����
static const char mxipForwarding[]            = "mx_ipForwarding";              // ��������
static const char mxbRouteTable[]             = "mx_bRouteTable";                    // ����ƻ�
static const char mxbFdbTable[]               = "mx_bFdbTable";                // У�����
static const char mxbSupportBulk[]            = "mx_bSupportBulk";                // У�����
static const char mxVendor[]			      = "mx_Vendor";                // �豸����
static const char mxModel[]					  = "mx_Model";                // У�����
static const char mxSnmpDeviceType[]            = "_snmpdevicetype";                // У�����
static const char mxNetConfig[]            = "mx_NetConfig";                // ���������豸
static const char mxSyslog[]					= "mxsyslog";						//Syslogʶ��
static const char mxMac[]			            = "mx_mac";                // У�����
static const char mxSpeed[]						= "mx_Speed";                // У�����
//static const char mxMSpeed[]						= "mxMSpeed";                // У�����
static const char mxIfType[]					= "mx_iftype";                // У�����
static const char mxOpstat[]		            = "mx_opstat";                // У�����
static const char mxAdstat[]		            = "mx_ifadminstat";                // �ӿڹ���״̬
static const char mxSort[]		            = "mxsort";                // У�����

//-------------------------------------------------------------------------------
static const char mxSortType[]		            = "mxsorttype";                // У�����
static const char mxDelete[]					= "mx_delete";
static const char mxPropName[]					= "mxpropname";
static const char mxTempProp[]					= "mx_istemp";
static const char mxPropType[]					= "mxproptype";
static const char mxBaseProp[]					= "BaseInfo";
static const char mxAutoProp[]					= "Auto";
static const char mxIsInR[]						= "mxisInR";

static const char mxHub[]						= "Hub";
static const char mxSubTopo[]					= "subtopo.";
static const char mxTopo[]						= "Topo.";
static const char mxRelatePanel[]					= "mx_relatepanel";
static const char mxDataUpdateTime[]					= "mx_updatedatatime";
//------------------------------------------------------------------------------------
static const char mxStartTime[]					="mx_starttime";
static const char mxEndTime[]					="mx_endtime";


#define VERTICALSPACE   7
#define WINDOWHEIGHT    24
#define LABELWIDTH      110
#define HORIZONSPACE    20
#define WINDOWWIDTH     400
#define HALFWINDOWWIDTH     200     //Ϊ�� ����,���Լ���


#define ERROR_NONULL  1
#define ERROR_ISNUM   2



//--------------------------ϵͳ����------------------------------------------------------------
#define RANGETYPE 2
#define ABSTYPE   1
#define SMSTPL  1
#define EMAILTPL 2
#define SMSTPLSec "SmsTpl"
#define EMAILTPLSec "EmailTpl"
#define TRAPTPLSec "TrapTpl"

#define WEEKDAY   7
#define DOUBLEHOUR  48

#define SELFID			 5000
#define DEVICEDYNID		10000
#define MONITORDYNID	15000
//----------------------mainfrm----------------------------------------
enum WINDOWOP{CLOSEWIN =0, UPDATETITLE=1  };
enum OBJOP {ADDOP=0,UPDATEOP=1,DELETEOP=2,UPDATESTAT=3};
enum   EventLevel { EVENTNOTICE=0,EVENTWARNING=1,EVENTEMERGENCE=2,EVENTERROR=3};
enum   OtherEventType {IPMACEVENT =0};

#define COLOR_MASK	RGB(0x00,0x80,0x80)
enum   TOPORELEATION{ SELRELEATION =0, IPRELEATION=1 };
enum  TOPODEVICETYPE{ROUTERTYPE=0, SWITCHTYPE =1 ,SERVERTYPE =2 };
 // SELRELEATION  ϵͳ����id����ѡ��
// IPADDRRELEATION ip��ַ����

enum TOPOOPERATOR {TOPOSELECT =0, ADDTOPOLINE =1,ZOOMMAX=2, ZOOMMIN=3,NORMALSIZE=4 };

enum PROPERTYTYPE {PROTOCOL = -1,SINGLEOJB=0,MULITOBJ=1,MONITOREX=2};

#define COLOR_BLACK         RGB(0, 0, 0)
#define COLOR_WHITE         RGB(255, 255, 255)
#define COLOR_BLUE          RGB(0, 0, 255)
#define COLOR_YELLOW        RGB(255, 255, 0)
#define COLOR_RED           RGB(255, 0, 0)
#define COLOR_LIGHTCORAL    RGB(240, 128, 128)
#define COLOR_GREEN         RGB(0, 255,0 )

#define SYSLOG		"SysLog"
#define ALERTREPORT "AlertReport"
#define EVENTTABLE  "EventLog"
#define OPERATETABLE "OperateLog"
#define  ASSERTTRUE(X) if(!X) {  return false;}
#define  NEWASSERTTRUE(X) if(!X) { CloseMXCTHandle(hd); return false;}


//-----------------ALERT DEFINE	---------------------------------------
#define INVALID_NUM          -1

enum AlertAction{EMAILALERT=0, SMSALERT = 1,SOUNDALERT= 2,SCRIPTALERT = 3,SNMPTRAPALERT=4,LEDALERT=5};
enum AlertCondition{  SEQUENCE=0,ONCE=1,JUMP=2,AllStat=3,ELECTT=4};
enum TplCondition {ALERTALL =0,ALERTINCLUD=1,ALERTEXCLUD=2};

enum CellShowType{CELLTEXTTYPE =0,CELLSCALETYPE=1,CELLSTATTYPE=2 ,CELLCOLUMN=3};
enum ValueType{TEXTTYPE =0,INTETYPE=1,FLOATTYPE=2};

enum TOPCALTYPE {CALAVG=1,CALLAST=0};
enum SORTORDER{SORTASC=1,SORTDECS=0 };
enum SORTTYPE{NOSORT=0 ,SORTBYNAME=1,SORTBYTYPE=2,SORTDEFAULT=3,SORTBYSELF=4 };

enum DRAWTYPE{PIE=0,LINE=1,BAR=2,GAUGES=3,AREAR};
enum AVGCALTYPE {SIMPLEAVG=0,MODAVG };

enum AVGUNIT {FIVEMIN=0,TENMIN,HALFHOUR,HOUR,DAY,WEEK,MONTH };
#define HTTPSTPL		"SSL"
#define MASSURLTPL		"MassURL"
#define MASSURLEXTPL	"MassUrlEx"
#define GSMMQ "gsmmq"
#define GSMRETMQ "gsmretmq"

//--------------------------------NNM---------------------------------
enum SNMPTPVERB {IDLEVER=0, //����״̬
				STOPSEARCH=1, //ֹͣ������ ˫���� �����豸��ɻ�ֹͣ��������·����ֹ
				ADDSUBNET=2,  //��������  ��������ͻ�����
				STARTSEACHDEVIE=3, //��ʼ�����豸 �ͻ������������
				STARTSEARCHTP=4,   //��ʼ�������� �ͻ������������
				GETDEVICEPROP=5,   //�õ��豸���� ��ȡ�豸����ʱ����
				ADDSNMPDEVICE=6,   //�����豸   ˫���� 
				DELETESNMPDEVICE=7, //ɾ���豸  �ͻ������������
				EDITSNMPDEVICE=8,   //�༭�豸 �ͻ������������
				GETTPSTAT=9,		//�õ���ǰ�����豸״̬
				DELETEALLSUBNET=10, // ɾ���������� �ͻ������������ ������
				DELETESUBNET=11,	//ɾ������
				GETSTEP=12,			//�õ������豸�Ľ�չ���
				ResetDeviceThreadMax=13,//�������������豸���߳���
				CurrentSearchStat=14,//֪ͨ�ͻ��˵�ǰ�������  ��������ͻ�����
				FINISHTOPOLOGY=15,//�����·����
				GETDEVICEIFSTAT=16,
				SETDEVICEIFCLOSE=17,
				SETDEVICEIFOPEN=18,
				GETAFTDATA=19,
				GETARPDATA=20,
				REFRESHCOMMDATA=21,
				DELETESNMPGROUP=22,
				GETIFDATA=23,
				GETIFTWOSTATDATA=24,
				GETDEVICESPROP=25,
				TESTSOUNDALERT=26,
				GETCDPDATA=27,
				GETARPFTPDATA=28

				};

enum SNMPTPSTAT {SEACHIDLE=0, SEARCHDEVICES=1,SEARCHTOPO=2};
#define PROPERTYGETOK	"OK"
//Add New
//--------------------------ά������Ϣ-----------------------------------------------
static const char mxGroup[]         ="_Group";
static const char mxComm[]          = "_Comm"; 
static const char mxProperty[]          = "Property"; 
static const char mxSelfGetPro[]          = "SelfGetProperty"; 

static const char mxContactInfo[]          = "ContactInfo";           // ��ϵ����Ϣ
static const char mxContactName[]		   = "contactName";		      // ����
static const char mxTelephony[]			   = "telephony";		      // �绰
static const char mxDuty[]				   = "duty";				  // ְ��
static const char mxUnit[]				   = "unit";				  // ��λ

static const char mxMaintenanceInfo[]	   = "MaintenanceInfo";		  // ά����Ϣ
static const char mxTimeLimit[]			   = "timeLimit";			  // ά������
static const char mxBeginDate[]			   = "begin_date";			  // ��ʼ����
static const char mxEndDate[]			   = "end_date";				  // ��������
static const char mxManuFacturer[]		   = "manufacturer";		  // ά������

//Add End
enum MAINVERB 
{
	STATCHANGE=1201,
	UPDATEDIPMAC=1202,
	ALERTSENDMSG=1203,
	CLIENTUPDATE,
	CLIENTSYNCHRONIZATION,

};

enum CLIENTUPDATE_type
{
	CLIENTUPDATE_ADD = 1,
	CLIENTUPDATE_MODIFY,
	CLIENTUPDATE_DELETE,
	CLIENTUPDATE_UNKNOWN,
};

enum TPLTYPE {XMLTEMPLATE=0, ODBCTEMPLATE=1}; //��������ģ��
enum MACEVENTTYPE {MACCHANGED=803 ,MACNEW=804,MACWRONGIP=805};
enum OperateType {				EDITSE=2,							//���ڵ�
					ADDGROUP=11,EDITGROUP=12,DELETEGROUP=13, FORBITGROUP = 14, ALLOWGROUP = 15,		//��
					ADDDEVICE=21,EDITDEVICE=22,DELETEDEVICE=23, FORBITDEVICE= 24, ALLOWDEIVCE = 25,TEMPORARYFORBITDEVICE=26,//�豸
					ADDMONITOR=31,EDITMONITOR=32,DELETEMONITOR=33, FORBITMONITOR = 34, ALLOWMONITOR = 35,TEMPORARYFORBITMONITOR=36,//����
					ADDUSER=41,EDITUSER=42,DELETEUSER=43,			//�û�
					ADDVRGROUP=51,EDITVRGROUP=52,DELETEVRGROUP=53,	//������
					ADDREALREPORT=61,EDITREALREPORT=62,DELETEREALREPORT=63,			//ʵʱ����
					ADDTOPNREPORT=71,EDITTOPNREPORT=72,DELETETOPNREPORT=73,			//TopN����
					ADDAVGREPORT=81,EDITAVGREPORT=82,DELETEAVGREPORT=83,			//ͳ�����ݱ���(ƽ������)
					ADDANYSREPORT=91,EDITANYSREPORT=92,DELETEANYSREPORT=93,			//ͳ��ԭʼ����(��������)
					ADDFAULTKIND=101,EDITFAULTKIND=102,DELETEFAULTKIND=103,			//���Ϸ���
					ADDFAULTREPORT=111,EDITFAULTREPORT=112,DELETEFAULTREPORT=113,	//����ͳ�Ʊ���
					ADDALERT=121,EDITALERT=122,DELETEALERT=123,		//����
					USERLOGIN=131,USEREXIT=132,EDITDAYTRFFICPORT=133,ADDDAYTRAFFICMONITOR=134,
					DELDAYTRIFFICREPORT=135};



//-----------------------------Return----------------------------------
static const  char mxDataType[]	=				"mxdatatype";
static const  char mxDataUnit[]	=				"mxunit";
static const  char mxVar[] =					"mxvar";
static const  char mxDataLabel[]	=			"mxlabel";
static const  char mxRow[]	=					"mxrow";
static const  char mxCol[]	=					"mxcol";
static const  char mxIcon[]	=					"mxIcon";
static const  char mxTplIcon[] =				"mxTplIcon";

//Topo��׼�������
static const  char mxNetworkInterface[]	=			"networkinterface";
static const  char mxRecvTraffic[]	=			"recivetraffic";
static const  char mxSendTraffic[]	=			"sendtraffic";
static const char mxTargetIp[]					= "_target_ip";
static const char mxAgentMonitorType[]					= "_monitor_type";
//-------------------Report--------------------------------------------------
#define		MX_GOOD_RADIO						"���������(%)"
#define		MX_ERROR_RADIO						"��������(%)"
#define GOODRADIO    "GoodRadio"
#define ERRORRADIO    "ErrorRadio"

//----------------------Monitor Device Group--------------------------------------------------------
static const  char mxLabel[]	=					"mxlabel";
static const  char mxControlType[]	=				"mxcontroltype";
static const  char mxIsMust[]		=				 "mxismust";
static const  char mxDefault[]		=				 "mxdefault";
static const  char mxOnlyNum[]		=				 "mxisonlynum";
static const  char mxHelp[]		=					"mxhelp";
static const  char mxRows[]		=					"mxrows";
static const  char mxIsFollow[]		=				 "mxisfollow";
static const  char mxFllowName[]		=				 "mxfollowname";
static const  char mxIsInputDll[]		=				 "mxisinputdll";
static const  char mxIsDyn[]			=				 "mxisdyn";
static const  char mxDllFunc[]			=					"mxdllfun";
static const  char mxDll[]				=					"mxdll";
static const  char mxIsMulti[]			=					"mxismutli";
static const  char mxIsHide[]			=						"mxishide";
static const  char mxIsReadOnly[]			=					"mxisreadonly";
static const  char mxIsSort[]			=						"mxissort";
static const char mxSaveInMain[]	=						"mxsaveinmain";
static const char mxParamdContent[]	=						"mxparam%dcontent";
static const char mxParamdName[]	=						"mxparam%dname";
static const char mxParamdIcon[]	=						"mxparam%dicon";
static const char mxParamdNum[]	=						"mxparamnum";
static const char mxHasParent[]	=						"mxhasparent";
static const char mxDistanceTime[]				= "_distancetime";             // ��������
static const char mxDistanceTimeUnit[]                = "_distancetime_unit";             // ��������
static const char mxPluginName[]=							"mxpluginname";
static const char mxSubPlugin[]=							"mxsubplug";
static const char mxRemark[]						= "mxRemark";
static const char mxKey[]						= "mx_key";						// �ؼ�Key
// controltype
static const char mxTextCtrl[]	=						"textbox";
static const char mxPwdTextCtrl[]	=					"passwordtextbox";
static const char mxComboCtrl[]	=						"combobox";
static const char mxMonitorType[]=						"monitorTypebox";
static const char mxDropCtrl[]	=						"dropbox";
static const char mxCheckCtrl[]	=						"checkbox";
static const char mxRadiotCtrl[]	=						"radio";
static const char mxlistCtrl[]	=						"listbox";
static const char mxTextboxProperty[]					= "textboxproperty" ;            // �����ı���
static const char mxLink[]					=			"mxlink" ;            // ����

//static const char mxDay[]								= "dayctrl" ;            // �����ı���
static const char mxRId[]								= "mxrid";						// ��¼ID
static const char mxThresholdRemark[]							="mxthresholdremark";
static const char mxFaciLevel[]							= "_important_level";
static const char mxDependCondition[]				   = "mxdependscondition";        // ��������
static const char mxDependON[]							 = "mxdependson";               // ������
static const char mxDeviceType[]						= "mxdevicetype";              // �����������
static const char mxType[]								= "mxtype";                    // ��������
static const char mxIden[]								= "mxiden";                    // ��������
static const char mxStyle[]								= "mxstyle";                    // ��������
static const char mxMonitorBox[]								= "monitorbox";                    // ����
static const char mxFixServer[]								= "mx_fixtsserver";                    // ��������
static const char mxLogServer[]								= "mx_logdbserver";                    // ��������
static const char mxCanbeOhterServerMonitor[]					= "mx_canbeloadwhilenofixserver";
static const char mxImportantLevel[]					= "_important_level";			//��Ҫ�̶�

static const char mxIconBase[]							= "mxIcon";						//ICON BASE
static const char mxIsTplDev[]							= "mxIsTplDev";					//�Ƿ����豸ģ��
static const char mxGroup_[]								= "Group";						//������
static const char mxFolder[]							= "FOLDER";						//�ļ���
static const char mxGroupOpen[]							= "GroupOpen";					//��������
static const char mxFolderOpen[]						= "FOLDER_O";					//�򿪵��ļ���
static const char mxMonitor[]							= "Monitor";					//��������
static const char mxDot[]								= "DOT";						//����ͼ��
static const char mxCriticalMonitor[]					= "CriticalMonitor";			//��Ҫ����
static const char mxSun[]								= "SUN";						//��Ҫ����ͼ��
static const char mxPassiveMonitor[]					= "PassiveMonitor";				//����ʽ����
static const char mxRhombus[]							= "RHOMBUS";					//����ʽ������ͼ��
static const char mxSwitch2[]							= "Switch";						//���㽻����
static const char mxSwitch3[]							= "SwtichRouter";				//���㽻����
static const char mxSwitch[]							= "SWITCH";						//���㽻����ͼ��
static const char mxSwitchRouter[]						= "SWITCHROUTER";				//���㽻����ͼ��
static const char mxRouter[]							= "Router";						//·����
static const char mxRouterIcon[]						= "ROUTER";						//·����ͼ��
static const char mxCommon[]							= "COMMON";						//ͨ���豸
static const char mxUnKnown[]							= "COMMON";						//δָ���豸ͼ��

static const char IconBaseKey[]							= "IconBase";				
//------------------------------------------------------------------------------------

enum MONITORWAY{
	MXCOMMONMONITOR = 1,					//��ͨ����
	MXPASSVICEMONITOR,						//����ʽ����
	MXCUSTOMMONITOR,						//�Զ������
};

enum ExportTable {	RESOURCE=0,				//������Դ��
					MONITORTEMPLATE=1,		//����ģ���
					MONITORCONFIG=2,		//������ͱ�
					DEVICETYPETABLE=3,		//�豸���ͱ�
					GROUPTABLE=4,			//���
					DEVICETABLE=5,			//�豸��
					MONITORTABLE=6,			//�����
					DEVICEMINITOR=7,		//�豸�����
					GROUPDEVICE=8,			//����豸��ϵ��
					EVENTTYPE=9,			//�¼������
					CONTROLTABLE=10,		//����Ԫ��
					CONTROLGROUP=11,		//����Ԫ���ϵ��
					CONTROLDEVICE=12,       //����Ԫ�豸��ϵ��
					RESULTTABLE=13,			//�������
					EVENTLOG=14,			//�¼���
					ALERTLOG=15				//������
};		
enum MXVERSION {SINGLEVERSION=1,FENBUVERSION=2};