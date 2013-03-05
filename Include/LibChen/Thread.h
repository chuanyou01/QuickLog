#ifndef	LIBCHEN_THREAD_H_
#define LIBCHEN_THREAD_H_

#ifdef WIN32
#ifndef _WINSOCKAPI_
#define _WINSOCKAPI_      //фа╠н winsock1.1
#endif
#include "windows.h"
#endif

namespace chen
{
	class Thread
	{
	public:
		Thread(void);
		virtual ~Thread(void);

		void SetThreadName(const char *threadName);
		HANDLE GetThreadHandle(){ return m_hThread; };
		DWORD  GetThreadID(){ return m_ThreadID; };
		const char * GetThreadName(void)
		{
			return m_ThreadName;
		}
		virtual BOOL Start(void);

	protected:

		virtual void BeforeStart(void) { return; };
		virtual void Run(void) = 0;
		virtual void AfertRun(void) { return ;};
		virtual void AfterException(void) { return ; };

		bool m_DeleteAfterRun;
		HANDLE	m_hThread;
		DWORD	m_ThreadID;
		char	*m_ThreadName;
	private:
		static DWORD WINAPI ThreadProc(LPVOID lpParam);

	};
}

#endif
