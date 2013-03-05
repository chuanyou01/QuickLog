#ifndef CHEN_SYSINFO_WIN32_H_
#define CHEN_SYSINFO_WIN32_H_

#include <windows.h>
#include <iostream>
#include <string>

namespace chen
{
	class SysInfo_win32
	{
	public:
		SysInfo_win32(void);
		~SysInfo_win32(void);
		static bool GetVMPageSize(unsigned int &nPage);
		static bool GetCPUNumber(unsigned int &count,unsigned int activeMask);
		static bool GetDiskSpace(const char *Dir,unsigned __int64 &FreeSpace,unsigned __int64 &TotalSpace,unsigned __int64 &TotalFreeSpace);
		static bool GetPhysicalMemory(unsigned __int64 &Total,unsigned __int64 &Free,int &Load);
		static bool GetTotalVMemory(unsigned __int64 &Total,unsigned __int64 &Free);
		static bool GetDiskInfo(const char *Dir,unsigned int &SectorSize,unsigned int &SectorsPerCluster);
		static bool GetVolumeInfo(const char *RootPath,std::string &VolumeName,std::string &FileSystemName,unsigned int &SerialNumber,int &MaxFileName,unsigned int *FileSystemFlag);


	};
}

#endif
