#ifndef CCUAPI_CCUAPIDEF_H_
#define CCUAPI_CCUAPIDEF_H_

/***********************************************************************************************/
/**						此文件实现CCU应用程序接口											   */
/**						版本:1.0.0.2														   */
/**						版权所有:2010@ 北京美信时代科技有限公司								   */
/**						版权所有人保留所有权利												   */
/***********************************************************************************************/

#ifdef CCUAPI_EXPORTS
#define CCUAPI_API __declspec(dllexport)
#else
#define CCUAPI_API __declspec(dllimport)
#endif

#define CCUAPI_ERROR_NOERROR			0x0
#define CCUAPI_ERROR_FAILED				0x1
#define CCUAPI_ERROR_TS_FREQREG			0x02
#define CCUAPI_ERROR_TS_RESPERROR		0x03
#define CCUAPI_ERROR_DS_FREQREG			CCUAPI_ERROR_TS_FREQREG

#define CCUAPI_ERROR_PARAMETERERROR		0x00000050
#define CCUAPI_ERROR_CONNECTCCUFAILED	0x00000105
#define CCUAPI_ERROR_SENDFAILED			0x00000100
#define CCUAPI_ERROR_RECVFAILED			0x00000101
#define CCUAPI_ERROR_PROTOCOLERROR		0x00000102
#define CCUAPI_ERROR_ALLOCMEMFAILED		0x00000103
#define CCUAPI_ERROR_UNSERIALIZEFAILED	0x00000104

CCUAPI_API
void SetCCUPortAndTimeout(unsigned short nPort,int timeout=0);






#endif