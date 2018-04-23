/*************************************************************************
* File Name : HostDiskRaidInfo.cpp
* Author : xus103
* Created Time : 2018年04月11日
* Description : 处理主机硬盘配置信息查询
* CopyRight : Copyright(c) 2000-2020 fiberhome
* OtherInfo :
* ModifyLog :
 ************************************************************************/

#include "HostDiskRaidInfo.h"

/***********************************************************************
 * FunctionName : SendDiskRaidInfo
 * Author : xus103
 * CreateDate : 2018/04/11
 * Description : 发送主机磁盘阵列信息
 * InputParam : data - 查询请求
 				type - 请求类型
 * OutputParam :
 * Return Value : 无
 * Relation : 
 * OtherInfo : 无
 ***********************************************************************/
void HostDiskRaidInfo::SendDiskRaidInfo(RealQueryHostStatusData &data, Header::DataType type)
{
	RealQueryHostStatusResponse response;
	response.set_querycfgtype(data.querycfgtype());
	response.set_data(base64_encode(ProtoBufPacker::SerializeToArray<RealDiskRaidCfgInfo>(GetDiskRaidCfgInfo())));
	string responseData = ProtoBufPacker::SerializeToArray<RealQueryHostStatusResponse>(response);
	Major major = ProtoBufPacker::PackResponseData(responseData, type, data.uniqueid());
}


/***********************************************************************
 * FunctionName : GetDiskRaidCfgInfo
 * Author : xus103
 * CreateDate : 2018/04/11
 * Description : 获取主机硬盘阵列信息
 * InputParam : 
 * OutputParam :
 * Return Value : 主机硬盘阵列信息
 * Relation : 
 * OtherInfo : 无
 ***********************************************************************/
RealDiskRaidCfgInfo HostDiskRaidInfo::GetDiskRaidCfgInfo()
{
	RealDiskRaidCfgInfo info;

	return info;
}



