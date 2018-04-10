/**********************************************************
 * File: SystemInfo.cpp
 * Function: 
 *********************************************************/
#include "SystemInfo.h"

#include "SigarAdapt.h"






CSystemInfo::CSystemInfo()
{
    memset(m_szName, 0, sizeof(m_szName));
    memset(m_szVersion, 0, sizeof(m_szVersion));
    memset(m_szArch, 0, sizeof(m_szArch));
    memset(m_szMachine, 0, sizeof(m_szMachine));
    memset(m_szDesc, 0, sizeof(m_szDesc));
    memset(m_szPatchLevel, 0, sizeof(m_szPatchLevel));
    memset(m_szVendor, 0, sizeof(m_szVendor));
    memset(m_szVendorVersion, 0, sizeof(m_szVendorVersion));
    memset(m_szVendorName, 0, sizeof(m_szVendorName));
    memset(m_szVendorCodeName, 0, sizeof(m_szVendorCodeName));
}




CSystemInfo::~CSystemInfo()
{
    memset(m_szName, 0, sizeof(m_szName));
    memset(m_szVersion, 0, sizeof(m_szVersion));
    memset(m_szArch, 0, sizeof(m_szArch));
    memset(m_szMachine, 0, sizeof(m_szMachine));
    memset(m_szDesc, 0, sizeof(m_szDesc));
    memset(m_szPatchLevel, 0, sizeof(m_szPatchLevel));
    memset(m_szVendor, 0, sizeof(m_szVendor));
    memset(m_szVendorVersion, 0, sizeof(m_szVendorVersion));
    memset(m_szVendorName, 0, sizeof(m_szVendorName));
    memset(m_szVendorCodeName, 0, sizeof(m_szVendorCodeName));
}





int CSystemInfo::GetSystemInfo()
{
    sigar_sys_info_t sysinfo;

    if (SIGAR_OK != sigar_sys_info_get(CSigar::GetSigar(), &sysinfo))
    {
        return -1;
    }

    SetName(sysinfo.name);
    SetVersion(sysinfo.version);
    SetArch(sysinfo.arch);
    SetMachine(sysinfo.machine);
    SetDesc(sysinfo.description);
    SetPatchLevel(sysinfo.patch_level);
    SetVendor(sysinfo.vendor);
    SetVendorVersion(sysinfo.vendor_version);
    SetVendorName(sysinfo.vendor_name);
    SetVendorCodeName(sysinfo.vendor_code_name);
    return 0;
}














