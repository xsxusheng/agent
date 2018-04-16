/*************************************************************************
	> File Name: ProtoBufPacker.cpp
	> Author: 
	> Mail: 
	> Created Time: 2018年03月05日 星期一 15时01分06秒
 ************************************************************************/

#include <iostream>
#include "../msg/RabbitmqConfig.h"
#include "sv_log.h"
#include "AgentUtils.h"
#include "base64.h"
#include "ProtoBufPacker.h"

Major ProtoBufPacker::PackMsgMajor(string &body, Header::DataType type, Header::DIRECTION direction)
{
	Major major;
	Header *header = major.mutable_header();
	int port = RabbitmqConfig::GetPort();
	header->set_rabbitmqinfo("rabbitmq:" + RabbitmqConfig::GetHost() + "/" + to_string(port));
	header->set_ip(AgentUtils::GetLocalIP());
	header->set_type(type);
	header->set_direction(direction);
	major.set_body(base64_encode(body));
	//SV_LOG("ip %s, info %s", header->ip().c_str(), header->rabbitmqinfo().c_str());
	return major;
}

Major ProtoBufPacker::PackPerfEntity(string data, PerfData::PERFDATATYPE type)
{
	PerfData perfData;

	perfData.set_type(type);
	perfData.set_data(base64_encode(data));
	string body =  ProtoBufPacker::SerializeToArray<PerfData>(perfData);
    	Major major = PackMsgMajor(body, Header::PERF, Header::AGENTOFUMS);

    return major;
}

Major ProtoBufPacker::PackAppEntity(string body)
{
    Major major = PackMsgMajor(body, Header::APP, Header::AGENTOFUMS);;
    return major;
}

Major ProtoBufPacker::PackAlarmEntity(string body)
{
    Major major = PackMsgMajor(body, Header::ALARM, Header::AGENTOFUMS);;
    return major;
}

Major ProtoBufPacker::PackEventEntity(string body)
{
    Major major = PackMsgMajor(body, Header::EVENT, Header::AGENTOFUMS);;
    return major;
}

Major ProtoBufPacker::PackAcsEventEntity(string body)
{
    Major major;
    return major;
}

Major ProtoBufPacker::PackStbInspectEntity(string body)
{
    Major major;
    return major;
}


Major ProtoBufPacker::PackHeartBeatData(string data)
{
	Major major = PackMsgMajor(data, Header::HEART, Header::AGENTOFUMS);
	return major;
}


Major ProtoBufPacker::PackResponseData(string data, Header::DataType type, ::google::protobuf::int64 uniqueId)
{
	ResponseData responseData;
	responseData.set_data(base64_encode(data));
	responseData.set_restype(type);
	responseData.set_uniqueid(uniqueId);

	string body = ProtoBufPacker::SerializeToArray<ResponseData>(responseData);
    Major major = PackMsgMajor(body, Header::RESPONSE, Header::AGENTOFUMS);
	
    return major;
}

string ProtoBufPacker::PrintPerf(string &body)
{
	string pStr;
	PerfData data;
	data.ParseFromString(base64_decode(body));
	
	return pStr;
}

string ProtoBufPacker::PrintCfgStr(RealQueryHostStatusData::HostCfgTypeEnum type, string data)
{
	string pStr;
	switch(type)
	{
		case RealQueryHostStatusData::SYSTEM:
		{
			
			break;
		}
		case RealQueryHostStatusData::DISKSTATUS:
		{
			
			break;
		}
		case RealQueryHostStatusData::DISKCFG:
		{
			
			break;
		}
		case RealQueryHostStatusData::DISKRAID:
		{
			
			break;
		}
		case RealQueryHostStatusData::DISKHEALTH:
		{
			
			break;
		}
		case RealQueryHostStatusData::NIC:
		{
			RealNicStatusInfo info;
			info.ParseFromString(base64_decode(data));
			for(int i = 0; i < info.singlenicinfo_size(); i++)
			{
				SingleNicPerfData nic = info.singlenicinfo(i);
				pStr.append(nic.DebugString());
                                pStr.append("\n");

			}
			break;
		}
		case RealQueryHostStatusData::PROCESS:
		{
			RealProcessStatusInfo info;
			info.ParseFromString(base64_decode(data));
			for(int i = 0; i < info.singleprocessinfo_size(); i++)
			{
				RealSingleProcessStatusInfo process = info.singleprocessinfo(i);
				pStr.append(process.DebugString());
				pStr.append("\n");
			}
			
			break;
		}
		default:
		{
			pStr.append("error realquery type:" + to_string(type) + "\n");
		}
	}
	return pStr;
}

string ProtoBufPacker::PrintResponse(string &body)
{
	string pStr;
	ResponseData responseData;
	responseData.ParseFromString(base64_decode(body));
	pStr.append("Response type:" + to_string(responseData.restype()) + "\n");
	pStr.append("unique id:" + to_string(responseData.uniqueid()) + "\n");
	string data = responseData.data();
	Header::DataType type = responseData.restype();
	switch(type)
	{
		case Header::CONFIG:
		{
			ConfigUpdateResponse res;
			res.ParseFromString(base64_decode(data));
			pStr.append(res.DebugString());
			break;
		}
		case Header::CTRL_APP:
		{
			CtrlAppRstResponse res;
			res.ParseFromString(base64_decode(data));
			pStr.append(res.DebugString());
			break;
		}
		case Header::SOFTWARE:
		{
			CtrlSoftwareStatusResponse res;
			res.ParseFromString(base64_decode(data));
			pStr.append(res.DebugString());
			break;
		}
		case Header::REALQUERYHOSTCFG:
		{
			RealQueryHostStatusResponse res;
			res.ParseFromString(base64_decode(data));
			pStr.append(PrintCfgStr(res.querycfgtype(), res.data()));
			break;
		}
		default:
		{
			break;
		}
	}
	return pStr;
}


void ProtoBufPacker::ProtoToString(Major major)
{
	string pStr("\n\n\n");
	pStr += "----------------Header-------------";
	string head = major.header().DebugString();
	pStr += head;
	pStr += "\n";
	pStr += "----------------Body-------------";
	string body = major.body();
	switch(major.header().type())
	{
		case Header::PERF:
		{
			pStr += PrintPerf(body);	
			break;
		}
		case Header::APP:
		{
			
			break;
		}
		case Header::RESPONSE:
		{
			pStr += PrintResponse(body);
			break;
		}
		case Header::UPHOSTCFG:
		{

			break;
		}
		case Header::ALARM:
		{

			break;
		}
		case Header::CONFIG:
		{

			break;
		}
		case Header::CTRL_APP:
		{

			break;
		}
		case Header::SOFTWARE:
		{
		
			break;
		}
		case Header::REALQUERYHOSTCFG:
		{

			break;
		}
		case Header::HASWITCH:
		{

			break;
		}
		case Header::HEART:
		{
			return;
			break;
		}
		default:
		{
			pStr += "type is not update, type:";
			pStr += major.header().type();
		}
	}

	pStr += "\n\n\n";
	SV_LOG("%s", pStr.c_str());
	return;
}

