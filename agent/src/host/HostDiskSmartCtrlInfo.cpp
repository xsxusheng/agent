/*************************************************************************
* File Name : HostDiskSmartCtrlInfo.cpp
* Author : xus103
* Created Time : 2018年04月11日
* Description : 处理主机硬盘SMART信息查询
* CopyRight : Copyright(c) 2000-2020 fiberhome
* OtherInfo :
* ModifyLog :
 ************************************************************************/
#include "HostDiskSmartCtrlInfo.h"

/***********************************************************************
 * FunctionName : SendDiskRaidInfo
 * Author : xus103
 * CreateDate : 2018/04/11
 * Description : 发送主机硬盘SMART信息查询
 * InputParam : data - 查询请求
 				type - 请求类型
 * OutputParam :
 * Return Value : 无
 * Relation : 
 * OtherInfo : 无
 ***********************************************************************/
void HostDiskSmartCtrlInfo::SendDiskSmartCtlInfo(RealQueryHostStatusData &data, Header::DataType type)
{
	RealQueryHostStatusResponse response;
	response.set_querycfgtype(data.querycfgtype());
	response.set_data(base64_encode(ProtoBufPacker::SerializeToArray<RealDiskHealthInfo>(GetDiskHealthInfo())));
	string responseData = ProtoBufPacker::SerializeToArray<RealQueryHostStatusResponse>(response);
	Major major = ProtoBufPacker::PackResponseData(responseData, type, data.uniqueid());
}


/***********************************************************************
 * FunctionName : HostDiskSmartCtrlInfo
 * Author : xus103
 * CreateDate : 2018/04/11
 * Description : 获取主机硬盘SMART信息
 * InputParam : 
 * OutputParam :
 * Return Value : 主机硬盘SMART信息
 * Relation : 
 * OtherInfo : 无
 ***********************************************************************/
RealDiskHealthInfo HostDiskSmartCtrlInfo::GetDiskHealthInfo()
{
	RealDiskHealthInfo info;

	return info;
}




