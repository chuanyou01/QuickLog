/************************************************************************/
/*                                                                      */
/************************************************************************/
#ifndef __DS_DEBUG_MACRO_DEF_INC__
#define __DS_DEBUG_MACRO_DEF_INC__

//#include <assert.h>
#include <tchar.h>
#include <stdio.h>

#ifdef _DEBUG	// debug version
#include <winbase.h>

#define _DS_TRACE_BUF_SIZE_		512		// the most chars can be output

// Input unicode string.
#define _DSTRACE0T(tsz)		OutputDebugString(tsz)
#define _DSTRACE1T(tsz, p1)	{ \
								TCHAR t_trace1[_DS_TRACE_BUF_SIZE_]; \
								t_trace1[0] = _T('\0'); \
								_stprintf(t_trace1, tsz, p1); \
								OutputDebugString(t_trace1); \
							}
#define _DSTRACE2T(tsz, p1, p2)	{ \
									TCHAR t_trace2[_DS_TRACE_BUF_SIZE_]; \
									t_trace2[0] = _T('\0'); \
									_stprintf(t_trace2, tsz, p1, p2); \
									OutputDebugString(t_trace2); \
								}
#define _DSTRACE3T(tsz, p1, p2, p3)	{ \
										TCHAR t_trace3[_DS_TRACE_BUF_SIZE_]; \
										t_trace3[0] = _T('\0'); \
										_stprintf(t_trace3, tsz, p1, p2, p3); \
										OutputDebugString(t_trace3); \
									}
// Input multibyte string.
#define _DSTRACE0(sz)		OutputDebugString(_T(sz))
#define _DSTRACE1(sz, p1)	{ \
								TCHAR t_trace1[_DS_TRACE_BUF_SIZE_]; \
								t_trace1[0] = _T('\0'); \
								_stprintf_s(t_trace1, _DS_TRACE_BUF_SIZE_, _T(sz), p1); \
								OutputDebugString(t_trace1); \
							}
#define _DSTRACE2(sz, p1, p2)	{ \
									TCHAR t_trace2[_DS_TRACE_BUF_SIZE_]; \
									t_trace2[0] = _T('\0'); \
									_stprintf(t_trace2, _T(sz), p1, p2); \
									OutputDebugString(t_trace2); \
								}
#define _DSTRACE3(sz, p1, p2, p3)	{ \
										TCHAR t_trace3[_DS_TRACE_BUF_SIZE_]; \
										t_trace3[0] = _T('\0'); \
										_stprintf(t_trace3, _T(sz), p1, p2, p3); \
										OutputDebugString(t_trace3); \
									}

//#define assert(exp)		assert(exp)

#else	// release version

#define _DSTRACE0T(tsz)
#define _DSTRACE1T(tsz, p1)
#define _DSTRACE2T(tsz, p1, p2)
#define _DSTRACE3T(tsz, p1, p2, p3)
#define _DSTRACE0(sz)
#define _DSTRACE1(sz, p1)
#define _DSTRACE2(sz, p1, p2)
#define _DSTRACE3(sz, p1, p2, p3)
//#define assert(exp)

#endif

#endif
//////////////////////////////////////////////////////////////////////////
// End of File.