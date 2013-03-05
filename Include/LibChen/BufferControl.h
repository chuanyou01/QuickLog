#ifndef LIBCHEN_BUFFERCONTROL_H_
#define LIBCHEN_BUFFERCONTROL_H_

#include <list>
#include "buffer.h"
#include "MyMutex.h"
#include "hashmap.h"

namespace chen{


	template < typename MTYPE_ = char >
	class CommonAlloc
	{
	public:
		MTYPE_ * operator () (unsigned int len)
		{
			if(len>0)
			{
				try{

					return new MTYPE_[len];

				}catch(...)
				{
					return NULL;
				}
			}
			return NULL;
		}

		void Free(MTYPE_ *pbuf)
		{
			try{
				delete [] pbuf;
			}catch(...)
			{
				return ;
			}

		}

	};

	template < typename PTYPE_ >
	class MetaData{
	public :
		MetaData()
		{
			m_ref=false;
			m_pdata=NULL;
		}
		~MetaData()
		{
		}

		bool m_ref;
		PTYPE_ *m_pdata;

	};


	template<typename MTYPE_ ,typename AC_=CommonAlloc< MTYPE_ > >
	class BufferControl
	{
		typedef MetaData < MTYPE_ > MetaDataType;
		typedef chen::hashtable< unsigned int,MetaDataType * > BUFFERMAP;
		typedef std::list< MetaDataType * > BUFFERLIST;

	public:
		BufferControl(void)
		{
			m_len=0;
			m_buflen=0;
			m_maxbuf=100000;
			m_maxfreebuf=10000;
			m_buflen=1;
		}
		~BufferControl(void)
		{
			Destory();
		}

		bool Init(unsigned int count,unsigned int buflen,unsigned int maxbuf=100000,unsigned int maxfreebuf=10000)
		{
			if(count<=0||buflen<=0)
				return true;

			chen::Lock lock(m_mutex);

			if(maxbuf>0)
				count=count>maxbuf ? maxbuf : count;
			count=count>maxfreebuf ? maxfreebuf : count;

			m_buflen=buflen;
			m_maxbuf=maxbuf;
			m_maxfreebuf=maxfreebuf;

			m_bufs.resetsize(1777);


			return (AllocFreeBuffer(count)==count);

		}

		MTYPE_ * Alloc()
		{
			chen::Lock lock(m_mutex);
			MetaDataType *p=NULL;
			if(m_freebufs.size()>0)
			{
				p=m_freebufs.front();
				m_freebufs.pop_front();
			}else
			{
				p= AllocBuffer();
			}
			if(p!=NULL)
			{
				p->m_ref=true;
				return p->m_pdata;
			}

			return NULL;
		}

		void Free(MTYPE_ *&p)
		{
			chen::Lock lock(m_mutex);
			if(p==NULL)
				return ;
			unsigned int key=reinterpret_cast<unsigned int>(p);
			MetaDataType **pmd=m_bufs.find(key);
			if(pmd==NULL)
				return ;

			(*pmd)->m_ref=false;

			if(m_freebufs.size()<m_maxfreebuf)
				m_freebufs.push_back(*pmd);
			else
			{
				FreeMetaBuffer((*pmd));
				m_bufs.erase(key);
				m_len--;
			}
			p=NULL;
		}

		void Debug_Printf_Buffer_State()
		{

			int refcount=0;
			BUFFERMAP::iterator it;
			while(m_bufs.findnext(it))
			{
				MetaDataType *p=(*it).getvalue();
				if(p!=NULL)
				{
					if(p->m_ref)
					{
						refcount++;
					}
				}else
					puts("Find empty pointer");

				p=NULL;
			}

			printf("Buffer count:%d,size:%d,Free count:%d,ref count:%d\n",m_len,m_bufs.size(),m_freebufs.size(),refcount);

		}
	protected:

		unsigned int AllocFreeBuffer(unsigned int count)
		{
			chen::Lock lock(m_mutex);

			unsigned int bc=count;
			if(m_maxbuf!=0)		//如果为零则没有限制
				bc=m_len+count<m_maxbuf ? count : m_maxbuf-m_len;

			bc=m_freebufs.size()+bc < m_maxfreebuf ? bc : m_maxfreebuf-m_freebufs.size();
			if(bc<=0)
				return 0;

			unsigned int oldlen=m_len;
			unsigned int key=0;

			for(;bc>0;bc--)
			{
				MetaDataType *pdata=AllocMetaBuffer();
				if(pdata==NULL)
				{
					return m_len-oldlen;
				}
				key=reinterpret_cast<unsigned int>(pdata->m_pdata);
				
				m_bufs.insert(key,pdata);
				m_freebufs.push_back(pdata);
				m_len++;

			}

			return m_len-oldlen;
		}

		MetaDataType *AllocMetaBuffer()
		{
			MetaDataType *pdata=new MetaDataType();
			if(pdata==NULL)
				return NULL;

			MTYPE_ *p=AllocRawBuffer();
			if(p==NULL)
			{
				delete pdata;
				return NULL;
			}
			pdata->m_ref=false;
			pdata->m_pdata=p;

			return pdata;	
		}

		void FreeMetaBuffer(MetaDataType *p)
		{
			if(p!=NULL)
			{
				try{
					FreeRawBuffer(p->m_pdata);
					delete p;
				}catch(...)
				{
					;
				}
			}

		}
		MetaDataType *AllocBuffer()
		{
			if((m_len>=m_maxbuf-1) && (m_maxbuf!=0))
				return NULL;
			MetaDataType *pdata=AllocMetaBuffer();
			if(pdata==NULL)
			{
				return NULL;
			}

			unsigned int key=0;

			key=reinterpret_cast<unsigned int>(pdata->m_pdata);
			m_bufs.insert(key,pdata);

			m_len++;

			return pdata;

		}
		MTYPE_  *AllocRawBuffer()
		{
			return MemAlloc(m_buflen);
		}
		void FreeRawBuffer(MTYPE_ *p)
		{
			if(p!=NULL)
		    	MemAlloc.Free(p);
		}

		void Destory()
		{
			BUFFERMAP::iterator it;
			while(m_bufs.findnext(it))
			{
				MetaDataType *p=(*it).getvalue();
				if(p!=NULL)
				{
					if(p->m_ref)
					{
						printf("Error:destory -- Buffer is used Address:%d\n",(int)p->m_pdata);
						continue;
					}
					FreeMetaBuffer(p);
				}
				p=NULL;
			}

			m_bufs.clear();

		}
	protected:
		AC_ MemAlloc;

		chen::Mutex m_mutex;

		volatile unsigned int m_len;
		unsigned int m_buflen;
		volatile unsigned int m_maxbuf;
		volatile unsigned int m_maxfreebuf;

		BUFFERMAP m_bufs;
		BUFFERLIST m_freebufs;
	};


	template < typename MTYPE_ ,typename AC_=CommonAlloc< MTYPE_ > >
	class BufferPtr
	{
	public:
		BufferPtr( BufferControl<MTYPE_,AC_> *pBC)
		{
			m_pBC=pBC;
			m_pBuf=NULL;
			if(m_pBC!=NULL)
			{
				m_pBuf=m_pBC->Alloc();
			}
		}
		~BufferPtr()
		{
			if(m_pBuf&&m_pBC)
				m_pBC->Free(m_pBuf);
		}

		inline MTYPE_ * operator -> ()
		{
			return m_pBuf;

		}

		inline operator MTYPE_ *() const
		{
			return m_pBuf;
		}
		inline bool operator ==(const MTYPE_ * pv) const
		{
			return (m_pBuf == pv);
		}

		inline MTYPE_ &operator *()
		{
			return *m_pBuf;
		}
	protected:
		BufferControl<MTYPE_,AC_> *m_pBC;
		MTYPE_ *m_pBuf;


	};



}

#endif
