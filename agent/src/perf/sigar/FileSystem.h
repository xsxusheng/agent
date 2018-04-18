/**********************************************************
 * File: FileSystem.h
 * Function: 
 *********************************************************/
#pragma once

#include <cstring>

#include "sigar.h"
#include "MacroDefine.h"

using namespace std;


typedef enum {
    FSTYPE_UNKNOWN,
    FSTYPE_NONE,
    FSTYPE_LOCAL_DISK,
    FSTYPE_NETWORK,
    FSTYPE_RAM_DISK,
    FSTYPE_CDROM,
    FSTYPE_SWAP,
    FSTYPE_MAX
}EFileSystemType;


#define FS_NAME_LEN SIGAR_PATH_MAX
#define FS_INFO_LEN 256

/*防止函数返回异常的值，这里做限制*/
#define MAX_FS_NUM 128


class CFileSystemInfo
{
public:
    CFileSystemInfo();
    ~CFileSystemInfo();


    char *GetDirName(){return m_cDirName;}
    char *GetDevName(){return m_cDevName;}
    char *GetTypeName(){return m_cTypeName;}
    char *GetSysTypeName(){return m_cSysTypeName;}
    char *GetOptions(){return m_cOptions;}
    EFileSystemType GetFileSystemType(){return m_eType;}
    unsigned long GetFlags(){return m_nFlags;}

    void SetDirName(char *pDirName){if(pDirName != NULL){strncpy(m_cDirName, pDirName, (FS_NAME_LEN -1));}}
    void SetDevName(char *pDevName){if(pDevName != NULL){strncpy(m_cDevName, pDevName, (FS_NAME_LEN -1));}}
    void SetTypeName(char *pTypeName){if(pTypeName != NULL){strncpy(m_cTypeName, pTypeName, (FS_INFO_LEN -1));}}
    void SetSysTypeName(char *pSysTypeName){if(pSysTypeName != NULL){strncpy(m_cSysTypeName, pSysTypeName, (FS_INFO_LEN -1));}}
    void SetOptions(char *pOptions){if(pOptions != NULL){strncpy(m_cOptions, pOptions, (FS_INFO_LEN -1));}}
    void SetFileSystemType(EFileSystemType eType){m_eType = eType;}
    void SetFlags(unsigned long flags){m_nFlags = flags;}


    unsigned long long GetDiskReads(){return m_nReads;}
    unsigned long long GetDiskWrites(){return m_nWrites;}
    unsigned long long GetDiskWriteBytes(){return m_nWriteBytes;}
    unsigned long long GetDiskReadBytes(){return m_nReadBytes;}
    unsigned long long GetDiskRtime(){return m_nRtime;}
    unsigned long long GetDiksWtime(){return m_nWtime;}
    unsigned long long GetDiskQtime(){return m_nQtime;}
    unsigned long long GetDiskTime(){return m_nTime;}
    unsigned long long GetDiskSnapTime(){return m_nSnapTime;}
    double GetDiskServiceTime(){return m_fServiceTime;}
    double GetDiskQueue(){return m_fQueue;}

    double GetFileSysUsePercent(){return m_fUsePercent;}
    unsigned long long GetFileSysTotal(){return m_nTotal;}
    unsigned long long GetFileSysFree(){return m_nFree;}
    unsigned long long GetFileSysUsed(){return m_nUsed;}
    unsigned long long GetFileSysAvail(){return m_nAvail;}
    unsigned long long GetFileSysFiles(){return m_nFiles;}
    unsigned long long GetFileSysFreeFiles(){return m_nFreeFiles;}


    void SetDiskReads(unsigned long long reads){m_nReads = reads;}
    void SetDiskWrites(unsigned long long writes){m_nWrites = writes;}
    void SetDiskWriteBytes(unsigned long long writeBytes){m_nWriteBytes = writeBytes;}
    void SetDiskReadBytes(unsigned long long readBytes){m_nReadBytes = readBytes;}
    void SetDiskRtime(unsigned long long rtime){m_nRtime = rtime;}
    void SetDiskWtime(unsigned long long wtime){m_nWtime = wtime;}
    void SetDiskQtime(unsigned long long qtime){m_nQtime = qtime;}
    void SetDiskTime(unsigned long long time){m_nTime = time;}
    void SetDiskSnapTime(unsigned long long snapTime){m_nSnapTime = snapTime;}
    void SetDiskServiceTime(double serviceTime){m_fServiceTime = serviceTime;}
    void SetDiskQueue(double queue){m_fQueue = queue;}

    void SetFileSysUsePercent(double usePercent){m_fUsePercent = usePercent;}
    void SetFileSysTotal(unsigned long long total){m_nTotal = total;}
    void SetFileSysFree(unsigned long long free){m_nFree = free;}
    void SetFileSysUsed(unsigned long long used){m_nUsed = used;}
    void SetFileSysAvail(unsigned long long avail){m_nAvail = avail;}
    void SetFileSysFiles(unsigned long long files){m_nFiles = files;}
    void SetFileSysFreeFiles(unsigned long long freeFiles){m_nFreeFiles = freeFiles;}



private:

    char m_cDirName[FS_NAME_LEN];
    char m_cDevName[FS_NAME_LEN];
    char m_cTypeName[FS_INFO_LEN]; /* e.g. "local" */
    char m_cSysTypeName[FS_INFO_LEN]; /* e.g. "ext3" */
    char m_cOptions[FS_INFO_LEN];
    EFileSystemType m_eType;
    unsigned long m_nFlags;


    unsigned long long m_nReads;
    unsigned long long m_nWrites;
    unsigned long long m_nWriteBytes;
    unsigned long long m_nReadBytes;
    unsigned long long m_nRtime;
    unsigned long long m_nWtime;
    unsigned long long m_nQtime;
    unsigned long long m_nTime;
    unsigned long long m_nSnapTime;
    double m_fServiceTime;
    double m_fQueue;

    double m_fUsePercent;
    unsigned long long m_nTotal;
    unsigned long long m_nFree;
    unsigned long long m_nUsed;
    unsigned long long m_nAvail;
    unsigned long long m_nFiles;
    unsigned long long m_nFreeFiles;

};




class CFileSystem
{
public:
    CFileSystem();
    ~CFileSystem();


    unsigned long GetFileSystemNum(){return m_nFileSystemNum;}
    void SetFileSystemNum(unsigned long num){if(num > 0){m_nFileSystemNum = num;}}

    CFileSystemInfo *GetFileSystemInfo(unsigned long index);

    void SetFileSystemInfo(sigar_file_system_t& fileSysInfo, unsigned long index);
    void SetFileSystemInfo(sigar_file_system_usage_t& fileSysInfo, unsigned long index);
    void SetFileSystemInfo(sigar_disk_usage_t& fileSysInfo, unsigned long index);


    unsigned long GetFileSystemListNum();
    int GetFileSystem();



private:

    unsigned long m_nFileSystemNum;
    CFileSystemInfo *m_pFileSystemInfo;


};





















