#ifndef LIBCHEN_MUTEX_H_
#define LIBCHEN_MUTEX_H_

#include "exception.h"

#ifdef WIN32
#ifndef _WINSOCKAPI_
#define _WINSOCKAPI_      //фа╠н winsock1.1
#endif
#include <windows.h>
#endif


namespace chen{

#ifdef WIN32

	class Event {
	public :
		Event()
		{
			m_event=::CreateEvent(NULL,TRUE,FALSE,"");
			if(m_event==NULL)
				throw this;
		}
		~Event()
		{
			if(m_event!=NULL)
				::CloseHandle(m_event);
		}
		bool Wait()
		{
			return (WaitForSingleObject(m_event,INFINITE)==WAIT_OBJECT_0);
		}
		bool Wait(DWORD timer)
		{
			return (WaitForSingleObject(m_event,timer)==WAIT_OBJECT_0);
		}

		BOOL Reset()
		{
			return ::ResetEvent(m_event);
		}
		BOOL Signal()
		{
			return ::SetEvent(m_event);
		}

	protected:
		HANDLE m_event;
	};

	class Mutex {
	public:
		Mutex() {
			InitializeCriticalSection(&crit);
		}
		~Mutex() {
			DeleteCriticalSection(&crit);
		}
	protected:

		void enter() {EnterCriticalSection(&crit);}
		void exit() {LeaveCriticalSection(&crit);}
		BOOL tryEnter() { return ::TryEnterCriticalSection(&crit);}
		CRITICAL_SECTION crit;
		friend class Lock;
		friend class tryLock;
	};

	class NameMutex{
	public:
		NameMutex(){
			m_handle=::CreateMutex(NULL,FALSE,NULL);
			m_isExist=FALSE;

		}
		NameMutex(const char *Name){
			m_handle=::CreateMutex(NULL,FALSE,Name);
			m_isExist=(GetLastError()==ERROR_ALREADY_EXISTS);
		}
		~NameMutex() {
			if(m_handle!=NULL)
			{
				::CloseHandle(m_handle);
				//puts("Close NameMutex");
			}
		}

		BOOL isExist(){return m_isExist;}
		BOOL isCreateOk(){ return (m_handle!=NULL); }

	protected:

		BOOL enter() { return (::WaitForSingleObject(m_handle,INFINITE)==WAIT_OBJECT_0);}
		BOOL exit() { return ::ReleaseMutex(m_handle); }
#define CHEN_NAMEMUTEX_TYROK		WAIT_OBJECT_0
#define CHEN_NAMEMUTEX_TYRTIMEOUT		WAIT_TIMEOUT
#define CHEN_NAMEMUTEX_TYRABANDONED		WAIT_ABANDONED
#define CHEN_NAMEMUTEX_TYRFAILED		 WAIT_FAILED
		DWORD tryEnter(DWORD timer) { 
			return ::WaitForSingleObject(m_handle,timer);
		}

		BOOL m_isExist;
		HANDLE m_handle;

		friend class NameLock;
		friend class tryNameLock;


	};


#endif

	class Lock {
	public:
		Lock(Mutex& m) : mutex(m) {m.enter();}
		~Lock() {mutex.exit();}
	protected:
		Mutex& mutex;
	};
	
	class tryLock {
	public:
		tryLock(Mutex& m) : mutex(m) {
			isEn=m.tryEnter();
		}
		~tryLock() { if(isEn) mutex.exit();}
		BOOL tryAgain(){
			if(!isEn)
				isEn=mutex.tryEnter(); 
			return isEn; 
		}
		BOOL isEnter(){ return isEn; }
	protected:
		BOOL isEn;
		Mutex& mutex;
	};

	class NameLock
	{
	public:
		NameLock(NameMutex &m) : m_mutex(m) { 
			if(!m.enter()) throw exception("Name lock enter failed"); 
		}
		~NameLock() { m_mutex.exit(); }

	protected:
		NameMutex& m_mutex;
	};

	class tryNameLock {
	public:
		tryNameLock(NameMutex& m,unsigned int timer) : m_mutex(m) {
			m_state=m.tryEnter(timer);
		}
		~tryNameLock() { if(m_state==CHEN_NAMEMUTEX_TYROK) m_mutex.exit();}
		BOOL tryAgain(unsigned int timer){
			if(m_state!=CHEN_NAMEMUTEX_TYROK)
				m_state=m_mutex.tryEnter(timer); 
			return (m_state==CHEN_NAMEMUTEX_TYROK); 
		}
		BOOL isEnter(){ return (m_state==CHEN_NAMEMUTEX_TYROK); }
	protected:
		unsigned int m_state;
		NameMutex& m_mutex;
	};


}


#endif // !defined(AFX_MYLOCK_H__292AF879_1C60_4130_9902_3A064D3724A5__INCLUDED_)
