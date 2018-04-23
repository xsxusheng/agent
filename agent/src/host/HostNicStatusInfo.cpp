/*************************************************************************
* File Name : HostNicStatusInfo.cpp
* Author : xus103
* Created Time : 2018年04月11日
* Description : 处理主机网卡状态信息查询
* CopyRight : Copyright(c) 2000-2020 fiberhome
* OtherInfo :
* ModifyLog :
 ************************************************************************/

#include "HostNicStatusInfo.h"

/***********************************************************************
 * FunctionName : SendNicStatusInfo
 * Author : xus103
 * CreateDate : 2018/04/11
 * Description : 发送主机网卡状态信息
 * InputParam : data - 查询请求
 				type - 请求类型
 * OutputParam :
 * Return Value : 无
 * Relation : 
 * OtherInfo : 无
 ***********************************************************************/
void HostNicStatusInfo::SendNicStatusInfo(RealQueryHostStatusData &data, Header::DataType type)
{
	RealQueryHostStatusResponse response;
	response.set_querycfgtype(data.querycfgtype());
	response.set_data(base64_encode(ProtoBufPacker::SerializeToArray<RealNicStatusInfo>(GetNicStatusInfo())));
	string responseData = ProtoBufPacker::SerializeToArray<RealQueryHostStatusResponse>(response);
	Major major = ProtoBufPacker::PackResponseData(responseData, type, data.uniqueid());
}


/***********************************************************************
 * FunctionName : GetRealProcessInfo
 * Author : xus103
 * CreateDate : 2018/04/11
 * Description : 获取主机网卡状态信息
 * InputParam : 
 * OutputParam :
 * Return Value : 主机进程信息
 * Relation : 
 * OtherInfo : 无
 ***********************************************************************/
RealNicStatusInfo HostNicStatusInfo::GetNicStatusInfo()
{
	RealNicStatusInfo info;

	return info;
}

