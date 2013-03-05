//#pragma once
#ifndef	LIBCHEN_BUFFER_H_
#define LIBCHEN_BUFFER_H_
#include "chentype.h"
#include <string.h>

namespace chen{
	class buffer
	{
	public:
		buffer(void);
		~buffer(void);
		enum { maxsize=2147483646 };

		buffer(const buffer &buf);
		buffer(S_UINT size);
		bool checksize(S_UINT length);
		S_UINT size()
		{
			return m_length;
		}

		void clearbuffer();

		bool resetsize(S_UINT length);

		buffer &operator=(const buffer &buf);

		operator char *();
		operator const char *() const;
		operator void *();
        char & operator [](S_UINT index);

		char * getbuffer();
		void zerobuf();
	private:
		S_UINT m_length;
		char *m_pbuf;
	};
}

#endif
