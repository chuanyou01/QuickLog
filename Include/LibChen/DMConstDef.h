#ifndef MXDM_DMCONSTDEF_H_
#define MXDM_DMCONSTDEF_H_

#include <mpoolheader/CommonConstDef.h>

#define MD_MAXTABLE	400000
#define MD_MAXTABLENAME		100
#define MD_MAXDBNAME		60
#define MD_MAXUSERNAME		60
#define MD_MAXPASSWORD		50
#define MD_MAXFIELDNAME		50
#define MD_MAXMQNAME		100
#define	MD_MAXMQPASSWORD	50
#define MD_MAXKEYNAME		256
#define MD_MAXPROPERTYNAME	256

#define MD_MAXINIFILENAME	100
#define MD_MAXINISECTION	100
#define MD_MAXINIKEY		100
#define MD_MAXRPATHNAME		256

#define MD_MAXMONITORTYPE	50

#define MD_MAXDATA			2097152

#define MD_MAXEXPORTDATA	209715200		//200M
//#define MD_MAXEXPORTDATA	10485760		//10M


#define MD_PERINCREASE	1048576

#define MD_MONITORSEPARATOR	"."
#define MD_NODESEPARATOR	"\\"
#define MD_NODESEPARATOR2	"/"

#define	MSTATUS_OK			1
#define	MSTATUS_WARNING		2
#define	MSTATUS_ERROR		3
#define	MSTATUS_BAD			4
#define	MSTATUS_DISABLE		5
#define	MSTATUS_NULL		0

//////////////////////////////
#define MD_INIFILEPATH			"bin/conf"

#define MD_CT_EXPORTSHARMEMORY		"Mxdm_ExportSubTree"


///////////////DOG///////////////
#define MXDOG_FILELEN		450
#define MXDOG_LIMITTIMELEN	10
#define MXDOG_FILEID		1

#define MX_FLAG_TIMELIMIT	0x01
#define MX_FLAG_DEVLIMIT	0x02

#define GET_RECORD_PT(p,m,x,r) {	\
	p=m->GetPage(x.pageindex);	\
	ASSERT_PAGE_BUFFER(p);		\
	r=(LPRECORDHEAD)PAGE_DATA_PT(p,x.pos);	\
}

#define GET_TABLE_PT(p,m,t,i) {	\
	p=m->GetPage(i);	\
	ASSERT_PAGE_BUFFER(p);	\
	if(PAGEHEAD_PT(p)->m_type!=PAGE_TYPE_TABLEINFO)	throw MDException("Get table type error -- GET_TABLE_PT");	\
	t=(Table *)PAGE_DATA_PT(p,0);	\
	if(t->m_cbSize!=sizeof(Table) || t->m_PagePos!=i)	throw MDException("Get table data format error -- GET_TABLE_PT");	\
}

#define GET_TABLERECORD_PT(p,m,r,i) {	\
	p=m->GetPage(i.pageindex);	\
	ASSERT_PAGE_BUFFER(p);	\
	r=(TableRecord *)PAGE_DATA_PT(p,i.pos);	\
	if(!F_ISSET(r->m_Flag,TRF_RECORD)) throw MDException("Get table record data format error -- GET_TABLERECORD_PT");	\
}

#define GET_QUEUEMETA_PT(p,m,q,i) { \
	p=m->GetPage(i);	\
	ASSERT_PAGE_BUFFER(p);	\
    if(PAGEHEAD_PT(p)->m_type!=PAGE_TYPE_QUEUEMETA) throw MDException("Get queuemeta page type error -- GET_QUEUEMETA_PT");	\
	q=(QueueMeta *)PAGE_DATA_PT(p,0);	\
	if(q->m_cblen!=sizeof(QueueMeta)) throw MDException("Get queuemeta data format error -- GET_QUEUEMETA_PT");	\
}

#define GET_QUEUERECORD_PT(p,m,r,i)	{	\
	p=m->GetPage(i.pageindex);	\
	ASSERT_PAGE_BUFFER(p);	\
	r=(MQRecord *)PAGE_DATA_PT(p,i.pos);	\
	if(r->m_cblen!=sizeof(MQRecord)) throw MDException("Get queue record data format error -- GET_QUEUERECORD_PT");	\
}

#define MD_DBTABLELOCK_STR		"mxdm_db_tablelock_string_%s"

#define MD_MAKELOCKSTRING(b,n) {	\
	md_int8 buf64[50];	\
	sprintf(b,MD_DBTABLELOCK_STR,_i64toa(n,buf64,10));	\
}

#endif