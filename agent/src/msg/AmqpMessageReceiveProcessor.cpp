/*************************************************************************
	> File Name: AmqpMessageReceiveProcessor.cpp
	> Author: 
	> Mail: 
	> Created Time: 2018年02月23日 星期五 13时33分07秒
 ************************************************************************/

#include <iostream>
#include "../utils/base64.h"
#include "../utils/sv_log.h"
#include "AmqpMessageReceiveProcessor.h"


AmqpMessageReceiveProcessor::AmqpMessageReceiveProcessor(string message) : m_message(message)
{
    
}


AmqpMessageReceiveProcessor::~AmqpMessageReceiveProcessor()
{
	
}

void AmqpMessageReceiveProcessor::__DoRun()
{
	MessageProcess();
    SV_LOG("MQ接收器线程结束");
}


/*
 * MQ消息处理
 */
int AmqpMessageReceiveProcessor::MessageProcess()
{	
	if(m_message.empty())
	{
		SV_ERROR("receive meessage is null, cant not to process");
		return -1;
	}

	Major major;
	major.ParseFromString(base64_decode(m_message));
	if(major.has_header())
	{
		SV_ERROR("parse message error");
		return -1;
	}
	Header header = major.header();
	if(header.direction() != Header::FUMSTOAGEN)
	{
		SV_ERROR("message direction error");
		return -1;
	}

	MessageDispatcher(header.type(), major.body());

	
    return 0;
}

/*
 * 根据消息类型分发处理
 */
int AmqpMessageReceiveProcessor::MessageDispatcher(Header::DataType type, const string &body)
{
	switch(type)
	{
		case Header::CTRL_APP:
			ProcessCommand(body);
			break;
		case Header::CONFIG:
			ProcessConfig(body);
			break;
		case Header::SOFTWARE:
			ProcessSoftwareInstall(body);
			break;
		case Header::REALQUERYHOSTCFG:
			ProcessRealQuery(body);
		default:
			SV_ERROR("unkonw type : %d", type);
			return -1;
	}
	
    return 0;
}

/*
 * 处理CMD命令
 */
int AmqpMessageReceiveProcessor::ProcessCommand(const string &body)
{
	CtrlAppData ctrlAppData;

	if(body.empty())
	{
		SV_ERROR("parameter error, body is empty");
		return -1;
	}

	ctrlAppData.ParseFromString(base64_decode(body));
	
    return 0;
}

/*
 * 实时查询
 */
int AmqpMessageReceiveProcessor::ProcessRealQuery(const string &body)
{
	RealQueryHostStatusData realQueryHostStatusData;

	if(body.empty())
	{
		SV_ERROR("parameter error, body is empty");
		return -1;
	}
	
	realQueryHostStatusData.ParseFromString(base64_decode(body));
    return 0;
}

/*
 * 配置下传处理
 */
int AmqpMessageReceiveProcessor::ProcessConfig(const string &body)
{
	ConfigData configData;
	
	if(body.empty())
	{
		SV_ERROR("parameter error, body is empty");
		return -1;
	}

	configData.ParseFromString(base64_decode(body));
    return 0;
}

/*
 * 软件升级处理
 */
int AmqpMessageReceiveProcessor::ProcessSoftwareInstall(const string &body)
{
	SoftwareData softwareData;
	
	if(body.empty())
	{
		SV_ERROR("parameter error, body is empty");
		return -1;
	}

	softwareData.ParseFromString(base64_decode(body));
    return 0;
}

