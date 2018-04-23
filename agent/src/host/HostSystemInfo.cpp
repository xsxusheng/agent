/*************************************************************************
* File Name : HostSystemInfo.cpp
* Author : xus103
* Created Time : 2018年04月11日
* Description : 处理主机系统信息查询
* CopyRight : Copyright(c) 2000-2020 fiberhome
* OtherInfo :
* ModifyLog :
 ************************************************************************/

#include "HostSystemInfo.h"

/***********************************************************************
 * FunctionName : SendSystemInfo
 * Author : xus103
 * CreateDate : 2018/04/11
 * Description : 发送主机系统信息
 * InputParam : data - 查询请求
 		type - 请求类型
 * OutputParam :
 * Return Value : 无
 * Relation : 
 * OtherInfo : 无
 ***********************************************************************/
void HostSystemInfo::SendSystemInfo(RealQueryHostStatusData &data, Header::DataType type)
{
	RealQueryHostStatusResponse response;
	response.set_querycfgtype(data.querycfgtype());
	response.set_data(base64_encode(ProtoBufPacker::SerializeToArray<RealSystemInfo>(GetSystemInfo())));
	string responseData = ProtoBufPacker::SerializeToArray<RealQueryHostStatusResponse>(response);
	Major major = ProtoBufPacker::PackResponseData(responseData, type, data.uniqueid());
}


/***********************************************************************
 * FunctionName : GetSystemInfo
 * Author : xus103
 * CreateDate : 2018/04/11
 * Description : 获取主机系统信息
 * InputParam : 
 * OutputParam :
 * Return Value : 主机系统信息
 * Relation : 
 * OtherInfo : 无
 ***********************************************************************/
RealSystemInfo HostSystemInfo::GetSystemInfo()
{
	RealSystemInfo info;
	/*
	info.set_sysdescr();
	info.set_cpuusage();
	info.set_sysuptime();
	info.set_cpufrequency();
	info.set_loadaverage();
	info.set_memorysize();
	info.set_memorysize();
	info.set_disktotalsize();
	info.set_mainfsdisksize();
	info.set_mainfsavailablesize();
	info.set_mainfsdiskuseratio();
	info.set_osname();
	info.set_osvender();
	info.set_cpunumbers();
	info.set_tcpnum();
	info.set_tcptotalinbound();
	info.set_tcptotaloutbound();
	info.set_cpumonokaryonusage();
	info.set_swapmonokaryonusage();
	*/
	return info;
}

