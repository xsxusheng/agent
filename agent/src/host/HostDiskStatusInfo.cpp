/*************************************************************************
* File Name : HostDiskStatusInfo.cpp
* Author : xus103
* Created Time : 2018年04月11日
* Description : 处理主机硬盘状态查询
* CopyRight : Copyright(c) 2000-2020 fiberhome
* OtherInfo :
* ModifyLog :
 ************************************************************************/

#include "../msg/AmqpMessageSendProcessor.h"
#include "HostDiskStatusInfo.h"

/***********************************************************************
 * FunctionName : SendDiskStatusInfo
 * Author : xus103
 * CreateDate : 2018/04/11
 * Description : 发送主机磁盘状态信息
 * InputParam : data - 查询请求
 				type - 请求类型
 * OutputParam :
 * Return Value : 无
 * Relation : 
 * OtherInfo : 无
 ***********************************************************************/
void HostDiskStatusInfo::SendDiskStatusInfo(RealQueryHostStatusData &data, Header::DataType type)
{
	RealQueryHostStatusResponse response;
	response.set_querycfgtype(data.querycfgtype());
	response.set_data(base64_encode(ProtoBufPacker::SerializeToArray<RealDiskStatusInfo>(GetDiskStatusInfo())));
	string responseData = ProtoBufPacker::SerializeToArray<RealQueryHostStatusResponse>(response);
	Major major = ProtoBufPacker::PackResponseData(responseData, type, data.uniqueid());
	AmqpMessageSendProcessor::GetInstance()->SendMessageToFums(major);
}


/***********************************************************************
 * FunctionName : GetDiskStatusInfo
 * Author : xus103
 * CreateDate : 2018/04/11
 * Description : 获取主机磁盘状态信息
 * InputParam : 
 * OutputParam :
 * Return Value : 主机磁盘状态信息
 * Relation : 
 * OtherInfo : 无
 ***********************************************************************/
RealDiskStatusInfo HostDiskStatusInfo::GetDiskStatusInfo()
{
	RealDiskStatusInfo info;
	

	return info;
}


