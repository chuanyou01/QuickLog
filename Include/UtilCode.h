#ifndef _MXCRECLOUD_UTILCODE_H_
#define _MXCRECLOUD_UTILCODE_H_

#ifdef UTILCODE_EXPORTS
#define UTILCODE_API __declspec(dllexport)
#else
#define UTILCODE_API __declspec(dllimport)
#endif

UTILCODE_API
unsigned int GetTaskIDCode(const char *tid);

#endif