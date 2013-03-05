#ifndef LIBCHEN_TYPE_H_
#define LIBCHEN_TYPE_H_

#undef NULL
#define NULL	0

//#define S_UINT	unsigned int
typedef unsigned int	S_UINT;

#undef	S_STRDUP
#ifdef WIN32
#define S_STRDUP	_strdup
#else
#define S_STRDUP	strdup
#endif




#endif