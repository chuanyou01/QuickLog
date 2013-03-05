#ifndef MXCRECLOUD_LICENCEINFO_H_
#define MXCRECLOUD_LICENCEINFO_H_
#include <time.h>

#define MX_CRECLOUD_CF_SYSTEMMAINKEY		"MXDM_SYSTEMNKEY"
#define MX_CRECLOUD_CF_SYSTEMKEY			"SYSTEM"
#define MX_CRECLOUD_CF_LINAME				"LicenInfo"
#define MX_CRECLOUD_CF_MF_DESNAME			"MiniFreeDes"
#define MX_CRECLOUD_CF_DE_DESNAME			"DemoEditionDes"
#define MX_CRECLOUD_CF_EE_DESNAME			"EvaluationEditionDes"
#define MX_CRECLOUD_CF_LD_DESNAME			"LicencedEditionDes"


union mx_time_type
{
	time_t ttm;
	char span[8];
};

struct LicenceInfo
{
	unsigned int	nlen;
	unsigned int	licence_version;
	unsigned int	product_version;
	unsigned int	internal_version;
	unsigned int	obj_count;
#define MX_CRECLOUD_IT_NULL				0x0
#define MX_CRECLOUD_IT_MINIFREE			0x1
#define MX_CRECLOUD_IT_DEMOEDITION		0x2
#define MX_CRECLOUD_IT_EVALUATION		0x4
#define MX_CRECLOUD_IT_BASICEVALUATION	0x8
#define MX_CRECLOUD_IT_BASIC			0x20
#define MX_CRECLOUD_IT_PROFESSIONAL		0x40
#define MX_CRECLOUD_IT_CLUSTER			0x80
#define MX_CRECLOUD_IT_LICENCED			0x100
#define MX_CRECLOUD_IT_OP_ENGLISH		0x800
	unsigned int	issue_type;
	mx_time_type	expire_date;

};

#endif