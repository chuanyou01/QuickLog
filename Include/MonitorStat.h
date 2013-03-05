

#pragma once

//#define MONITORSTAT_API	

#ifdef MONITORSTAT_API
#define MONIS_API __declspec(dllexport)
#else
#define MONIS_API __declspec(dllimport)
#endif
#include "mxdi.h"
MONIS_API int MxGetSimpleDyn( MXHANDLE& hd ,std::string szId,TableDYN& tdyn,
							 std::string szServer,
							 int& nType);
MONIS_API int MxGetDyn( MXHANDLE& hd ,std::string szId,TableDYN& tdyn,
					   std::list<chen::VariableData>& vlist,std::string szServer,
					   int& nType);
MONIS_API int MxSaveDataToShowStat(int nStat);
MONIS_API int MxSrcDataToShowStat(int nStat,int nType);
MONIS_API int MxSaveDataToSrcStat(int nStat);