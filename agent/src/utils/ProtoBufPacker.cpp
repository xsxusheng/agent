/*************************************************************************
	> File Name: ProtoBufPacker.cpp
	> Author: 
	> Mail: 
	> Created Time: 2018年03月05日 星期一 15时01分06秒
 ************************************************************************/

#include<iostream>
#include "../msg/RabbitmqConfig.h"
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
	
	return major;
}

Major ProtoBufPacker::PackPerfEntity(string &body, PerfData::PERFDATATYPE type)
{
	Major major;
    return major;
}

Major ProtoBufPacker::PackAppEntity(string &body)
{
    Major major;
    return major;
}

Major ProtoBufPacker::PackAlarmEntity(string &body)
{
    Major major;
    return major;
}

Major ProtoBufPacker::PackEventEntity(string &body)
{
    Major major;
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


Major ProtoBufPacker::PackResponseDate(string &body, Header::DataType type, long uniqueId)
{
    Major major;
    return major;
}



