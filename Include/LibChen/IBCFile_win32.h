#ifndef CHEN_IBCFILE_WIN32_H_
#define CHEN_IBCFILE_WIN32_H_

#include <iostream>
#include <string>

#include <windows.h>
#include "TimeFace.h"

namespace chen{
	class IBCFileFind_win32
	{
	public:
		IBCFileFind_win32(void);
		~IBCFileFind_win32(void);

		bool Find(std::string File);
		bool FindNext();
		std::string GetTitle();
		std::string GetName();
		std::string GetFullPath();
		std::string GetExtName();
		bool isDir();
		bool isReadOnly();
		bool isHidden();
		bool isDot();
		bool isSystem();
		bool isTemp();
		bool isEncrypted();
		bool isCompressed();

		chen::TimeFace GetCreateTime();
		chen::TimeFace GetLastWriteTime();
		chen::TimeFace GetLastAccessTime();

		unsigned int GetLength(unsigned int &highUint32);
		unsigned int GetRawAttirb();


	protected:
		void InitData()
		{
			m_hHandle=INVALID_HANDLE_VALUE;
			memset(&m_ffd,0,sizeof(WIN32_FIND_DATA));
			m_strFile="";
		}
		void Destory()
		{
			if(m_hHandle!=INVALID_HANDLE_VALUE)
			{
				FindClose(m_hHandle);
				m_hHandle=INVALID_HANDLE_VALUE;
			}
		}

		std::string m_strFile;
		WIN32_FIND_DATA m_ffd;
		HANDLE m_hHandle;


	};

	struct st_fpos
	{
		unsigned int lowSize;
		unsigned int highsize;
	};

	typedef LARGE_INTEGER	IBFILEPOS,*LPIBFILEPOS;

#define IBCF_OK								1
#define IBCF_FAILED							0
#define IBCF_ERROR_NOOPEN					10
#define IBCF_ERROR_ALREADYOPEN				11
	class IBCFile_win32
	{
	public:
		IBCFile_win32(void);
		~IBCFile_win32(void);

		enum SeekPosition { begin = 0x0, current = 0x1, end = 0x2 };

#define CHEN_FFATTRIB_READONLY		FILE_ATTRIBUTE_READONLY
#define CHEN_FFATTRIB_HIDDEN		FILE_ATTRIBUTE_HIDDEN
#define CHEN_FFATTRIB_SYSTEM		FILE_ATTRIBUTE_SYSTEM
#define CHEN_FFATTRIB_DIRECTORY		FILE_ATTRIBUTE_DIRECTORY
#define CHEN_FFATTRIB_ARCHIVE		FILE_ATTRIBUTE_ARCHIVE
#define CHEN_FFATTRIB_DEVICE		FILE_ATTRIBUTE_DEVICE
#define CHEN_FFATTRIB_NORMAL		FILE_ATTRIBUTE_NORMAL
#define CHEN_FFATTRIB_TEMPORARY		FILE_ATTRIBUTE_TEMPORARY
#define CHEN_FFATTRIB_SPARSE_FILE	FILE_ATTRIBUTE_SPARSE_FILE
#define CHEN_FFATTRIB_REPARSE_POINT	FILE_ATTRIBUTE_REPARSE_POINT
#define CHEN_FFATTRIB_COMPRESSED	FILE_ATTRIBUTE_COMPRESSED
#define CHEN_FFATTRIB_OFFLINE		FILE_ATTRIBUTE_OFFLINE
#define CHEN_FFATTRIB_NOT_CONTENT_INDEXED		FILE_ATTRIBUTE_NOT_CONTENT_INDEXED
#define CHEN_FFATTRIB_ENCRYPTED		FILE_ATTRIBUTE_ENCRYPTED



#define CHEN_FFLAG_OPENEXIST		0x00000001
#define CHEN_FFLAG_CREATENEW		0x00000002
#define CHEN_FFLAG_READONLY			0x00000004
#define CHEN_FFLAG_OPENALWAYS		0x00000008
#define CHEN_FFLAG_CREATEALWAYS		0x00000010
#define CHEN_FFLAG_SHAREWRITE		0x00000020
#define CHEN_FFLAG_SHAREREAD		0x00000040
#define CHEN_FFLAG_SHAREDELETE		0x00000080



		int Open(std::string FileName,unsigned int nFlag=CHEN_FFLAG_OPENEXIST,unsigned int nAttirb=CHEN_FFATTRIB_NORMAL);
		int GetLength(IBFILEPOS &size);
		int Seek(IBFILEPOS	fpos,unsigned char from);
		int GetCurrentPos(IBFILEPOS &fpos);
		int Write(IBFILEPOS fpos,const char *pBuf,unsigned int nBlen);
		int Read(IBFILEPOS fpos,char *pBuf,unsigned int nBlen);
		int SeekToBegin();
		int SeekToEnd();
		int ResetSize(IBFILEPOS size);

		static int DeleteFile(std::string strFileName);
		static int Rename(std::string oldFileName,std::string newFileName);
		static int SetTime(std::string strFileName,chen::TimeFace createTime,chen::TimeFace lastWriteTime,chen::TimeFace lastAccessTime);


		static int SetFileAttirbute(std::string strFileName,unsigned int nFlag);
		static int CreateDir(std::string strDirName,unsigned int nFlag);
		static int DeleteEmptyDir(std::string strDir);
		static int DeleteDirTree(std::string strDir);

		int Append(const char *pBuf,unsigned int nLen);
		int AppendString(std::string str);
		int Lock(IBFILEPOS pos,IBFILEPOS nCount);
		int UnLock(IBFILEPOS pos,IBFILEPOS nCount);
		int Close();
		int Flush();

	protected:
		void InitData()
		{
			m_hFile=INVALID_HANDLE_VALUE;
			m_FilePath="";
		}
		void Destory()
		{
			if(m_hFile!=INVALID_HANDLE_VALUE)
				::CloseHandle(m_hFile);
		}
		HANDLE m_hFile;
		std::string m_FilePath;
	};
}

#endif
