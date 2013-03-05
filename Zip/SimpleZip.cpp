#include "StdAfx.h"
#include ".\simplezip.h"
#include "ZipArchive.h"
#include "ZipPlatform.h"
#include <stdlib.h>
#include "list"
#include <time.h>
#include <stdio.h>
using namespace std;

CSimpleZip::CSimpleZip(void)
{
}

CSimpleZip::~CSimpleZip(void)
{
}



ZIPSTRINGCOMPARE pZipComp;


struct CZipAddFileInfo
{
	CZipAddFileInfo(const CZipString& szFilePath, const CZipString& szFileNameInZip)
		:m_szFilePath(szFilePath),	m_szFileNameInZip(szFileNameInZip)
	{
		int is = szFileNameInZip.GetLength();
		m_iSeparators = 0;
		for (int i = 0; i < is; i++)
			if (CZipPathComponent::IsSeparator(szFileNameInZip[i]))
				m_iSeparators++;
	}
	CZipString m_szFilePath, m_szFileNameInZip;
	
	bool CheckOrder(const CZipString& sz1, const CZipString& sz2, 
		int iSep1, int iSep2, bool bCheckTheBeginning = false) const
	{
		if (iSep1)
		{
			if (iSep2)
			{
				if (iSep1 == iSep2)
					return (sz1.*pZipComp)(sz2) < 0;

				if (bCheckTheBeginning)
				{

					int is = sz1.GetLength() > sz2.GetLength() ? sz2.GetLength() : sz1.GetLength();
					int iSeparators = 0;
					// find the common path beginning
					int iLastSepPos = -1;
					for (int i = 0; i < is; i++)
					{
						CZipString sz = sz2.Mid(i, 1);
						if ((sz1.Mid(i, 1).*pZipComp)(sz) != 0) // must be Mid 'cos of case sens. here
							break;
						else if (CZipPathComponent::IsSeparator(sz[0]))
						{
							iLastSepPos = i;
							iSeparators++;
						}
					}
					
					// if necessary remove the common path beginning and check again
					if (iLastSepPos != -1)
						return CheckOrder(sz1.Mid(iLastSepPos), sz2.Mid(iLastSepPos), iSep1 - iSeparators, iSep2 - iSeparators);
							
				}
				return (sz1.*pZipComp)(sz2) < 0;		
			} 
			else
				return false;
		}
		else
			if (iSep2)
				return true;
			else
				return (sz1.*pZipComp)(sz2) < 0;
	}
	bool operator>(const CZipAddFileInfo& wz) const
	{
		bool b = CheckOrder(m_szFileNameInZip, wz.m_szFileNameInZip,
			m_iSeparators, wz.m_iSeparators, true);
		return b;
	}
protected:
	int m_iSeparators; // for a sorting puroposes
};


typedef list<CZipString> FILELIST;
typedef list<CZipString>::iterator FILELISTIT;
typedef list<struct CZipAddFileInfo> FILELISTADD;
typedef list<struct CZipAddFileInfo>::iterator FILELISTADDIT;

struct AddDirectoryInfo
{
	AddDirectoryInfo(FILELIST& l):m_l(l){}
	FILELIST& m_l;
	CZipString m_lpszFile;
	bool m_bRecursive;
	bool m_bAddEmpty;
};


char ReadKey()
{
	fflush (stdin);
	char c = (char) tolower(getchar());
	return c;
}

struct SpanCallback : public CZipSpanCallback
{
	bool Callback(int iProgress)
	{
		printf ("Insert disk number %d and hit ENTER to contuniue \n or press 'n' key followed by ENTER to abort (code = %d)\n", m_uDiskNeeded, iProgress);	
		return ReadKey() != 'n';
	}
};

void FillFromFile(FILELIST& l, LPCTSTR lpszFile, bool bCheck)
{
	FILE* f;
#if _MSC_VER >= 1400
	if (fopen_s(&f, lpszFile, "rt") != 0)
		f = NULL;
#else
	f = fopen(lpszFile, "rt");
#endif
	
	if (!f)
	{
		printf ("File %s could not be opened\n", lpszFile);
		return;
	}
	fseek(f, 0, SEEK_END);
	int iSize = ftell(f);
	fseek(f, 0, SEEK_SET);
	CZipAutoBuffer buf(iSize + 1);
	iSize = fread(buf, 1, iSize, f);
	fclose(f);
	char* sEnd = buf + iSize;
	char* sBeg = buf;
	for (char* pos = buf; ; pos++)
	{
		bool bEnd = pos == sEnd; // there may be no newline at the end
		if (strncmp(pos, "\n", 1) == 0 || bEnd)
		{
			*pos = '\0';
			CZipString s = sBeg;
			s.TrimLeft(" ");
			s.TrimRight(" ");
			if (!s.IsEmpty() && (!bCheck || ZipPlatform::FileExists(s) != 0))
				l.push_back(s);
			if (bEnd)
				break;
			sBeg = pos + 1;			
		}
	}
}




bool IsDots(LPCTSTR lpsz)
{
	return strcmp(lpsz, ".") == 0 || strcmp(lpsz, "..") == 0;
}

void AddDirectory(CZipString szPath, struct AddDirectoryInfo& info, bool bDoNotAdd)
{
	if (!szPath.IsEmpty())
		CZipPathComponent::AppendSeparator(szPath);

	bool bPathAdded = info.m_bAddEmpty || bDoNotAdd;
	if (info.m_bAddEmpty && !szPath.IsEmpty() && !bDoNotAdd)
		info.m_l.push_back(szPath);

#ifdef __GNUC__
	DIR* dp = opendir(szPath.IsEmpty() ? "." : szPath);
	if (!dp)
		return;
	struct dirent* entry;
	while (entry = readdir(dp))
	{
		struct stat sStats;
		CZipString szFullFileName = szPath + entry->d_name;
		if (stat(szFullFileName, &sStats) == -1)
			continue;
		if (S_ISDIR(sStats.st_mode))
		{
			if (info.m_bRecursive)
			{
				if (IsDots(entry->d_name))
					continue;
				
				AddDirectory(szFullFileName, info, false);
			}
		}
		else if (fnmatch(info.m_lpszFile, entry->d_name, FNM_NOESCAPE |FNM_PATHNAME) == 0)
		{
			if (!bPathAdded)
			{
				if (!szPath.IsEmpty())
					info.m_l.push_back(szPath);
				bPathAdded = true;
			}
			info.m_l.push_back(szPath + entry->d_name);
		}
	}
	closedir(dp);

#else
    CZipString szFullFileName = szPath + info.m_lpszFile;
	struct _finddata_t c_file;
	long hFile;
	if( (hFile = _findfirst( szFullFileName, &c_file )) != -1L )
	{
		do
		{
			if (!(c_file.attrib & FILE_ATTRIBUTE_DIRECTORY))
			{
				// add it when the first file comes
				if (!bPathAdded)
				{
					if (!szPath.IsEmpty())
						info.m_l.push_back(szPath);
					bPathAdded = true;
				}
				info.m_l.push_back(szPath + c_file.name);
			}
		}
		while (_findnext(hFile, &c_file) == 0L);
	}
	_findclose(hFile);

	if (info.m_bRecursive)
	{
		szFullFileName = szPath + "*";
		if( (hFile = _findfirst( szFullFileName, &c_file )) != -1L )
		{
			do
			{
				if (c_file.attrib & FILE_ATTRIBUTE_DIRECTORY)
				{
					if (IsDots(c_file.name))
						continue;
					szFullFileName = szPath + c_file.name;
					AddDirectory(szFullFileName, info, false);
				}
			}
			while (_findnext(hFile, &c_file) == 0L);
		}
		_findclose(hFile);		
	}
#endif
}
 
void ExpandFile(FILELIST& l, LPCTSTR lpszPath, 
			 	bool bRecursive, bool bAddEmpty, bool bFullPath)
{
// check if we need to expand it
//         size_t pos = strcspn(lpszFile, "*?");
//         if (pos == strlen(lpszFile))
//         {
//                 l.push_back(lpszFile);
//                 return;
//         }

	CZipPathComponent zpc(lpszPath);
	CZipString szDir = zpc.GetFilePath();
// 	if (szDir.IsEmpty())
// 		if (!ZipPlatform::GetCurrentDirectory(szDir))
// 			return;
	struct AddDirectoryInfo adi(l);
	adi.m_bAddEmpty = bAddEmpty;
	adi.m_bRecursive = bRecursive;
	adi.m_lpszFile = zpc.GetFileName();
	AddDirectory(szDir, adi, !bFullPath); // when not full path is specified for a single file with a path, do not add a directory then

		
}


void FindInZip(CZipArchive& zip, FILELIST& l, CZipWordArray& n)
{

	for (FILELISTIT it = l.begin(); it != l.end(); ++it)
		zip.FindMatches(*it, n);
}

//--------------------Àý×Ó´úÂë-----------------------------------------------



bool CSimpleZip::Add(std::string strZipFile,std::list<std::string>& lstFile,std::string strRootPath,bool bFullPath)
{
	CZipArchive zip;

	
	CZipString szArchive;
	int iVolumeSize = 0;
	int iMode = CZipArchive::zipOpen;
	
	szArchive =CZipString(strZipFile);
	if (!ZipPlatform::FileExists(szArchive))
					iMode = CZipArchive::zipCreate;


	CZipPathComponent zpc(szArchive);
	SpanCallback span;
	zip.SetSpanCallback(&span);
	try
	{
		zip.Open(szArchive, iMode, iVolumeSize);
	}
	catch(...)
	{
		return FALSE;
	}
	zip.SetRootPath(strRootPath.c_str());

	FILELIST lFiles;
	
	for(std::list<std::string>::iterator it =lstFile.begin();it!=lstFile.end();it++)
	{
		std::string strFileName;
		strFileName =*it;
		lFiles.push_back(CZipString(strFileName));
	}
	FILELISTADD rev;
	for (FILELISTIT it = lFiles.begin(); it != lFiles.end(); ++it)				
	{
		CZipString sz = zip.PredictFileNameInZip(*it, bFullPath);
		if (!sz.IsEmpty())
			rev.push_back(CZipAddFileInfo(*it, sz));
	}
	lFiles.clear();
//	rev.sort(std::greater<CZipAddFileInfo>());
	FILELISTADDIT it1;
	int iSmartLevel = CZipArchive::zipsmSafeSmart;


	for (it1 = rev.begin(); it1 != rev.end(); ++it1)
	{	
		if (zip.AddNewFile((*it1).m_szFilePath, 5, bFullPath, iSmartLevel))
		{
			
			printf ("%s added\n", (LPCTSTR)(*it1).m_szFileNameInZip);
		}
		else
			printf ("%s not added\n", (LPCTSTR)(*it1).m_szFilePath);
	}

	zip.Close();
	return TRUE;
}

bool CSimpleZip::Extract(std::string strDest,std::string strZipFile)
{
	CZipString szArchive;
	szArchive=CZipString(strZipFile);
	CZipString szPath = CZipString(strDest);

	CZipArchive zip;
	
	int iVolumeSize = 0;
	int iMode = CZipArchive::zipOpen;


	try
	{
		zip.Open(szArchive, iMode, iVolumeSize);
	}
	catch(...)
	{
		return FALSE;
	}

	bool ok=true;
	for (int k = 0; k < zip.GetCount(); ++k)
	{
		
		try
		{
			ok = zip.ExtractFile(k, szPath, FALSE);
		}
		catch (...)
		{					
			ok = false;
			break;
		}
	}
	zip.Close();
	return ok;
}