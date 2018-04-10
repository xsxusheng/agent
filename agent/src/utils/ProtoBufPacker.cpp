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

Major ProtoBufPacker::PackPerfEntity(string &data, PerfData::PERFDATATYPE type)
{
	PerfData perfData;

	perfData.set_type(type);
	perfData.set_data(base64_encode(data));
	string body =  ProtoBufPacker::SerializeToArray<PerfData>(perfData);
    	Major major = PackMsgMajor(body, Header::PERF, Header::AGENTOFUMS);

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
Major ProtoBufPacker::PackAppEntity(string &body)
{
    Major major = PackMsgMajor(body, Header::APP, Header::AGENTOFUMS);;
    return major;
}

Major ProtoBufPacker::PackAppEntity(string body)
{
    Major major = PackMsgMajor(body, Header::APP, Header::AGENTOFUMS);;
    return major;
}
Major ProtoBufPacker::PackAlarmEntity(string &body)
{
    Major major = PackMsgMajor(body, Header::ALARM, Header::AGENTOFUMS);;
    return major;
}

Major ProtoBufPacker::PackEventEntity(string &body)
{
    Major major = PackMsgMajor(body, Header::EVENT, Header::AGENTOFUMS);;
    return major;
}

Major ProtoBufPacker::PackAcsEventEntity(string &body)
{
    Major major;
    return major;
}

Major ProtoBufPacker::PackStbInspectEntity(string &body)
{
    Major major;
    return major;
}

Major ProtoBufPacker::PackHeartBeatData(string data)
{
	Major major = PackMsgMajor(data, Header::HEART, Header::AGENTOFUMS);
	return major;
}

Major ProtoBufPacker::PackHeartBeatData(string &data)
{
	Major major = PackMsgMajor(data, Header::HEART, Header::AGENTOFUMS);
	return major;
}

Major ProtoBufPacker::PackResponseData(string &data, Header::DataType type, long uniqueId)
{
	ResponseData responseData;
	responseData.set_data(base64_encode(data));
	responseData.set_restype(type);
	responseData.set_uniqueid(uniqueId);

	string body = ProtoBufPacker::SerializeToArray<ResponseData>(responseData);
    Major major = PackMsgMajor(body, Header::RESPONSE, Header::AGENTOFUMS);
	
    return major;
}



