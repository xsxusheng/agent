/**********************************************************
 * File: SystemInfo.h
 * Function: 
 *********************************************************/
#pragma once

#include <string>
#include <cstring>

using namespace std;




#define MAX_SYSTEM_INFO_LEN 256


class CSystemInfo
{
public:
    CSystemInfo();
    ~CSystemInfo();


    char* GetName(){return m_szName;}
    void SetName(char* name){if (name != NULL){strncpy(m_szName, name, (sizeof(m_szName)-1));}}

    char* GetVersion(){return m_szVersion;}
    void SetVersion(char* version){if (version != NULL){strncpy(m_szVersion, version, (sizeof(m_szVersion)-1));}}

    char* GetArch(){return m_szArch;}
    void SetArch(char* arch){if (arch != NULL){strncpy(m_szArch, arch, (sizeof(m_szArch)-1));}}

    char* GetMachine(){return m_szMachine;}
    void SetMachine(char* machine){if (machine != NULL){strncpy(m_szMachine, machine, (sizeof(m_szMachine)-1));}}

    char* GetDesc(){return m_szDesc;}
    void SetDesc(char* desc){if (desc != NULL){strncpy(m_szDesc, desc, (sizeof(m_szDesc)-1));}}

    char* GetPatchLevel(){return m_szPatchLevel;}
    void SetPatchLevel(char* level){if (level != NULL){strncpy(m_szPatchLevel, level, (sizeof(m_szPatchLevel)-1));}}

    char* GetVendor(){return m_szVendor;}
    void SetVendor(char* vendor){if (vendor != NULL){strncpy(m_szVendor, vendor, (sizeof(m_szVendor)-1));}}

    char* GetVendorVersion(){return m_szVendorVersion;}
    void SetVendorVersion(char* version){if (version != NULL){strncpy(m_szVendorVersion, version, (sizeof(m_szVendorVersion)-1));}}

    char* GetVendorName(){return m_szVendorName;}
    void SetVendorName(char* name){if (name != NULL){strncpy(m_szVendorName, name, (sizeof(m_szVendorName)-1));}}

    char* GetVendorCodeName(){return m_szVendorCodeName;}
    void SetVendorCodeName(char* name){if (name != NULL){strncpy(m_szVendorCodeName, name, (sizeof(m_szVendorCodeName)-1));}}


    int GetSystemInfo();



private:
    char m_szName[MAX_SYSTEM_INFO_LEN]; /* canonicalized sysname */
    char m_szVersion[MAX_SYSTEM_INFO_LEN]; /* utsname.release */
    char m_szArch[MAX_SYSTEM_INFO_LEN];
    char m_szMachine[MAX_SYSTEM_INFO_LEN];
    char m_szDesc[MAX_SYSTEM_INFO_LEN];
    char m_szPatchLevel[MAX_SYSTEM_INFO_LEN];
    char m_szVendor[MAX_SYSTEM_INFO_LEN];
    char m_szVendorVersion[MAX_SYSTEM_INFO_LEN];
    char m_szVendorName[MAX_SYSTEM_INFO_LEN];  /* utsname.sysname */
    char m_szVendorCodeName[MAX_SYSTEM_INFO_LEN];

};
















