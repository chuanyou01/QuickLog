#ifndef LIBCHEN_MAPFILE_WIN32_H_
#define LIBCHEN_MAPFILE_WIN32_H_

#include <windows.h>
#include <iostream>
#include <string>

namespace chen{

#define CHEN_MFERROR_FAILED				0
#define CHEN_MFERROR_OK					1
#define CHEN_MFERROR_FILENOEXIST		2
#define CHEN_MFERROR_ALREADYOPEN		3
#define CHEN_MFERROR_OPENFILEFAILED		4
#define CHEN_MFERROR_CREATEFILEFAILED	5
#define CHEN_MFERROR_SETFILESIZEERROR	6
#define CHEN_MFERROR_OBJECTALREADYEXIST		7
#define CHEN_MFERROR_OBJECTNOEXIST			8
#define CHEN_MFERROR_NOOPEN					9
#define CHEN_MFERROR_SHARENAMEEMPTY			10

	class MapFile_win32
	{
	public:
		MapFile_win32(void);
		~MapFile_win32(void);
		MapFile_win32(std::string ShareName);
		MapFile_win32(std::string FileName,std::string ShareName);
#define CHEN_MFFLAG_OPENEXIST		0x00000001
#define CHEN_MFFLAG_CREATENEW		0x00000002
#define CHEN_MFFLAG_READONLY		0x00000004
#define CHEN_MFFLAG_ALLACCESS		0x00000008
#define CHEN_MFFLAG_NOCACHE			0x00000010
#define CHEN_MFFLAG_FF_OPENALWAYS		0x00000020
#define CHEN_MFFLAG_FF_CREATEALWAYS		0x00000040
#define CHEN_MFFLAG_FF_OPENEXIST		0x00000080
#define CHEN_MFFLAG_OPENBYNAME			0x00000100

		bool CreateMapFile(LARGE_INTEGER Size,unsigned int nFLAG=CHEN_MFFLAG_FF_OPENALWAYS|CHEN_MFFLAG_ALLACCESS);
		bool isOpenExist();
#define CHEN_MFVFLAG_READ			0x00000001
#define CHEN_MFVFLAG_WRITE			0x00000002
#define CHEN_MFVFLAG_ALLACCESS		0x00000004
		LPVOID MapViewEntire(unsigned int nFlag=CHEN_MFVFLAG_ALLACCESS);
		LPVOID MapView(LARGE_INTEGER Pos,unsigned int Size,unsigned int &offset,unsigned int nFlag=CHEN_MFVFLAG_ALLACCESS);
		bool FlushMapView(LPVOID pdata,DWORD nSize);
		
		bool UnMap(LPVOID pdata);

		LPVOID CreateShareMemory(std::string Name,unsigned int Size);

		int GetLastError();
		HANDLE GetHandle(){return m_mapHandle;}

		void CloseAll();

	protected:
		void InitData();
		void Destory();

		HANDLE m_mapHandle;
		HANDLE m_fileHandle;
		std::string m_FileName;
		std::string m_ShareName;	
		bool m_isOpenExist;
		int m_lastError;
	};

	class MapViewWrap
	{
	public:
		~MapViewWrap();

		MapViewWrap(MapFile_win32 *pMF,LARGE_INTEGER Pos,unsigned int Size,unsigned int Flag=CHEN_MFVFLAG_ALLACCESS);
		MapViewWrap(MapFile_win32 *pMF,bool mapAll=true,unsigned int Flag=CHEN_MFVFLAG_ALLACCESS);

		bool ReMapView(LARGE_INTEGER Pos,unsigned int Size,unsigned int Flag=CHEN_MFVFLAG_ALLACCESS);
		bool ReMapViewAll(unsigned int Flag);

		char *operator ->();
		char &operator *();
		operator char *();
		char &operator [](unsigned int n);

		char *GetPoint();
		LPVOID GetRawPoint();
		unsigned int GetOffset();
	protected:
		void InitData();
		void Destory();
		LPVOID m_pData;
		unsigned int m_nOffset;
		MapFile_win32 *m_pMF;

	};
}

#endif
