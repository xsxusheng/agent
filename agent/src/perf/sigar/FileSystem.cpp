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
    memset(m_cDirName, 0, sizeof(m_cDirName));
    memset(m_cDevName, 0, sizeof(m_cDevName));
    memset(m_cTypeName, 0, sizeof(m_cTypeName));
    memset(m_cSysTypeName, 0, sizeof(m_cSysTypeName));
    memset(m_cOptions, 0, sizeof(m_cOptions));
    m_eType = FSTYPE_UNKNOWN;
    m_nFlags = 0;
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



void CFileSystem::SetFileSystemInfo(sigar_file_system_usage_t& data, unsigned long index)
{
    if ((index >= 0) && (index < m_nFileSystemNum) && (m_pFileSystemInfo != NULL))
    {
        m_pFileSystemInfo[index].SetFileSysUsePercent(data.use_percent);
        m_pFileSystemInfo[index].SetFileSysTotal(data.total);
        m_pFileSystemInfo[index].SetFileSysFree(data.free);
        m_pFileSystemInfo[index].SetFileSysUsed(data.used);
        m_pFileSystemInfo[index].SetFileSysAvail(data.avail);
        m_pFileSystemInfo[index].SetFileSysFiles(data.files);
        m_pFileSystemInfo[index].SetFileSysFreeFiles(data.free_files);
    }
}



void CFileSystem::SetFileSystemInfo(sigar_disk_usage_t& data, unsigned long index)
{
    if ((index >= 0) && (index < m_nFileSystemNum) && (m_pFileSystemInfo != NULL))
    {
        m_pFileSystemInfo[index].SetDiskReads(data.reads);
        m_pFileSystemInfo[index].SetDiskWrites(data.writes);
        m_pFileSystemInfo[index].SetDiskWriteBytes(data.write_bytes);
        m_pFileSystemInfo[index].SetDiskReadBytes(data.read_bytes);
        m_pFileSystemInfo[index].SetDiskRtime(data.rtime);
        m_pFileSystemInfo[index].SetDiskWtime(data.wtime);
        m_pFileSystemInfo[index].SetDiskQtime(data.qtime);
        m_pFileSystemInfo[index].SetDiskTime(data.time);
        m_pFileSystemInfo[index].SetDiskSnapTime(data.snaptime);
        m_pFileSystemInfo[index].SetDiskServiceTime(data.service_time);
        m_pFileSystemInfo[index].SetDiskQueue(data.queue);
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

        SetFileSystemInfo(fsusage, i);

        if (SIGAR_OK != (ret = sigar_disk_usage_get(CSigar::GetSigar(), fslist.data[i].dev_name, &diskusage)))
        {
            printf("sigar_disk_usage_get(%s) ret = %d (%s)\n",
						fslist.data[i].dev_name, ret, sigar_strerror(CSigar::GetSigar(), ret));
            continue;
        }

        SetFileSystemInfo(diskusage, i);
    }

    sigar_file_system_list_destroy(CSigar::GetSigar(), &fslist);
    return 0;
}









