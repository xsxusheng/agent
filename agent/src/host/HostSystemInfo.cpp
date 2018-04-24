/*************************************************************************
* File Name : HostSystemInfo.cpp
* Author : xus103
* Created Time : 2018年04月11日
* Description : 处理主机系统信息查询
* CopyRight : Copyright(c) 2000-2020 fiberhome
* OtherInfo :
* ModifyLog :
 ************************************************************************/

#include "../msg/AmqpMessageSendProcessor.h"
#include "../perf/host/HostStatus.h"
#include "../utils/AgentUtils.h"
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
	AmqpMessageSendProcessor::GetInstance()->SendMessageToFums(major);
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
	
	info.set_sysdescr(CHostStatus::FetchSysDesc());
	info.set_cpuusage(CHostStatus::FetchCpuUsage());
	info.set_sysuptime(CHostStatus::FetchUpTime());
	//info.set_cpufrequency(CHostStatus::FetchCpuFrequency());
	info.set_cpufrequency(1.11);
	info.set_loadaverage(CHostStatus::FetchCpuLoadAverage());
	info.set_memorysize(CHostStatus::FetchMemorySize());
	info.set_memoryusage(CHostStatus::FetchMemUsage());
	info.set_disktotalsize(CHostStatus::FetchDiskTotal());
	
	info.set_mainfsdisksize(CHostStatus::FetchMainFSDiskSize());
	info.set_mainfsavailablesize(CHostStatus::FetchDiskAvailableSize());
	info.set_mainfsdiskuseratio(CHostStatus::GetDiskUsage());
	info.set_osname("Linux");
	info.set_osvender("1111");
	info.set_osversion("iiiii");
	info.set_cpunumbers(CHostStatus::FetchCpuNum());
	info.set_tcpnum(CHostStatus::GetTcpEstablished());
	info.set_tcptotalinbound(CHostStatus::FetchAllInputBandWidth());
	info.set_tcptotaloutbound(CHostStatus::FetchAllOutputBandWidth());
	info.set_cpumonokaryonusage(CHostStatus::FetchCpuMonokaryonUsage());
	info.set_swapusage(CHostStatus::FetchSwapUsage());
	info.set_agentversion(AgentUtils::GetAgentVersion());
	
	return info;
}

