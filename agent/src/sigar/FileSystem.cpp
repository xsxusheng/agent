/**********************************************************
 * File: FileSystem.cpp
 * Function: 
 *********************************************************/
#include "FileSystem.h"

#include "sigar.h"
#include "SigarAdapt.h"




CFileSystemInfo::CFileSystemInfo()
{
    memset(m_cDirName, 0, sizeof(m_cDirName));
    memset(m_cDevName, 0, sizeof(m_cDevName));
    memset(m_cTypeName, 0, sizeof(m_cTypeName));
    memset(m_cSysTypeName, 0, sizeof(m_cSysTypeName));
    memset(m_cOptions, 0, sizeof(m_cOptions));
    m_eType = FSTYPE_UNKNOWN;
    m_nFlags = 0;
}


CFileSystemInfo::~CFileSystemInfo()
{
}



CFileSystemInfo& CFileSystemInfo::operator=(CFileSystemInfo& fileSysInfo)
{
    SetDirName(fileSysInfo.GetDirName());
    SetDevName(fileSysInfo.GetDevName());
    SetTypeName(fileSysInfo.GetTypeName());
    SetSysTypeName(fileSysInfo.GetSysTypeName());
    SetOptions(fileSysInfo.GetOptions());
    SetFileSystemType(fileSysInfo.GetFileSystemType());
    SetFlags(fileSysInfo.GetFlags());
    return *this;
}




#if 0
#endif



CFileSystem::CFileSystem()
{
    unsigned long num = 0;

    m_nFileSystemNum = 0;
    m_pFileSystemInfo = NULL;
    
    num = GetFileSystemListNum();
    if (num > 0)
    {
        m_pFileSystemInfo = new CFileSystemInfo[num];
        if (m_pFileSystemInfo != NULL)
        {
            m_nFileSystemNum = num;
        }
    }
}


CFileSystem::~CFileSystem()
{
    if (m_pFileSystemInfo != NULL)
    {
        delete []m_pFileSystemInfo;
        m_pFileSystemInfo = NULL;
    }
    m_nFileSystemNum = 0;
}



unsigned long CFileSystem::GetFileSystemListNum()
{
    sigar_file_system_list_t fslist;
    
    if (SIGAR_OK == sigar_file_system_list_get(CSigar::GetSigar(), &fslist))
    {
        return -1;
    }
    
    sigar_file_system_list_destroy(CSigar::GetSigar(), &fslist);
    return fslist.number;
}



CFileSystemInfo *CFileSystem::GetFileSystemInfo(unsigned long index)
{
    if ((index >= 0) && (index < m_nFileSystemNum) && (m_pFileSystemInfo != NULL))
    {
        return &m_pFileSystemInfo[index];
    }
    return NULL;
}


void CFileSystem::SetFileSystemInfo(CFileSystemInfo& fileSysInfo, unsigned long index)
{
    if ((index >= 0) && (index < m_nFileSystemNum) && (m_pFileSystemInfo != NULL))
    {
        m_pFileSystemInfo[index] = fileSysInfo;
    }
}



void CFileSystem::SetFileSystemInfo(sigar_file_system_t& data, unsigned long index)
{
    if ((index >= 0) && (index < m_nFileSystemNum) && (m_pFileSystemInfo != NULL))
    {
        m_pFileSystemInfo[index].SetDirName(data.dir_name);
        m_pFileSystemInfo[index].SetDevName(data.dev_name);
        m_pFileSystemInfo[index].SetTypeName(data.type_name);
        m_pFileSystemInfo[index].SetSysTypeName(data.sys_type_name);
        m_pFileSystemInfo[index].SetOptions(data.options);
        m_pFileSystemInfo[index].SetFileSystemType((EFileSystemType)data.type);
        m_pFileSystemInfo[index].SetFlags(data.flags);
    }
}



int CFileSystem::GetFileSystem()
{
    int ret = 0;
    unsigned long i = 0;
    sigar_file_system_list_t fslist;
    sigar_file_system_usage_t fsusage;
    sigar_disk_usage_t diskusage;

    if (m_pFileSystemInfo == NULL)
    {
        return -1;
    }

    if (SIGAR_OK != sigar_file_system_list_get(CSigar::GetSigar(), &fslist))
    {
        return -1;
    }

    for (i = 0; i < fslist.number; i++)
    {
        SetFileSystemInfo(fslist.data[i], i);

        /*PING TEST*/
        if (SIGAR_OK != (ret = sigar_file_system_ping(CSigar::GetSigar(), &fslist.data[i])))
        {
            continue;
        }

        if (SIGAR_OK != (ret = sigar_file_system_usage_get(CSigar::GetSigar(), fslist.data[i].dir_name, &fsusage)))
        {
            printf("sigar_file_system_usage_get(%s) ret = %d (%s)\n",
						fslist.data[i].dir_name, ret, sigar_strerror(CSigar::GetSigar(), ret));
            continue;
        }

        SetFileSysUsePercent(fsusage.use_percent);
        SetFileSysTotal(fsusage.total);
        SetFileSysFree(fsusage.free);
        SetFileSysUsed(fsusage.used);
        SetFileSysAvail(fsusage.avail);
        SetFileSysFiles(fsusage.files);
        SetFileSysFreeFiles(fsusage.free_files);

        if (SIGAR_OK != (ret = sigar_disk_usage_get(CSigar::GetSigar(), fslist.data[i].dev_name, &diskusage)))
        {
            printf("sigar_disk_usage_get(%s) ret = %d (%s)\n",
						fslist.data[i].dev_name, ret, sigar_strerror(CSigar::GetSigar(), ret));
            continue;
        }

        SetDiskReads(diskusage.reads);
        SetDiskWrites(diskusage.writes);
        SetDiskWriteBytes(diskusage.write_bytes);
        SetDiskReadBytes(diskusage.read_bytes);
        SetDiskRtime(diskusage.rtime);
        SetDiskWtime(diskusage.wtime);
        SetDiskQtime(diskusage.qtime);
        SetDiskTime(diskusage.time);
        SetDiskSnapTime(diskusage.snaptime);
        SetDiskServiceTime(diskusage.service_time);
        SetDiskQueue(diskusage.queue);
    }

    sigar_file_system_list_destroy(CSigar::GetSigar(), &fslist);
    return 0;
}









