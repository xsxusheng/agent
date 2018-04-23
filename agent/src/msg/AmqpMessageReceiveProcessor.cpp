/*************************************************************************
	> File Name: AmqpMessageReceiveProcessor.cpp
	> Author: 
	> Mail: 
	> Created Time: 2018年02月23日 星期五 13时33分07秒
 ************************************************************************/

#include <iostream>
#include <unistd.h>
#include "../utils/base64.h"
#include "../utils/sv_log.h"
#include "../conf/ConfManager.h"
#include "../app/AppControlProcess.h"
#include "../host/HostSystemInfo.h"
#include "../host/HostRealProcessInfo.h"
#include "../host/HostNicStatusInfo.h"
#include "../host/HostDiskStatusInfo.h"
#include "../host/HostDiskSmartCtrlInfo.h"
#include "../host/HostDiskRaidInfo.h"
#include "../host/HostDiskCfgInfo.h"
#include "TaskManager.h"
#include "Task.h"
#include "AmqpMessageReceiveProcessor.h"


AmqpMessageReceiveProcessor::AmqpMessageReceiveProcessor() : Thread(true)
{
    
}


AmqpMessageReceiveProcessor::~AmqpMessageReceiveProcessor()
{
	SV_LOG("~AmqpMessageReceiveProcessor");
}

void AmqpMessageReceiveProcessor::__DoRun()
{
	int ret = 0;
	TaskManager* taskManager = NULL;
	Task* task = NULL;

	usleep(5000);
	while(1)
	{
		taskManager = TaskManager::GetInstance();
		if(taskManager == NULL)
		{
			SV_LOG("get task manager instance error");
			break;
		}
		task = taskManager->GetTaskByThreadId(GetThreadId());
		if(task == NULL)
		{
			SV_LOG("NULL");
			break;
		}
		
		
		if(task->GetState() == Task::TASK_IDLE)
		{
			task->SetState(Task::TASK_RUNNING);
			ret = TaskProcess(task->GetMessage());
			if(ret == 0)
			{
				task->SetState(Task::TASK_SUCCESS);
			}
			else
			{
				task->SetState(Task::TASK_FAILED);
			}
		}
		break;
	}

	this->Detach();
}


/*
 * MQ消息处理
 */
int AmqpMessageReceiveProcessor::TaskProcess(const string &message)
{	
	if(message.empty())
	{
		return -1;
	}
	
	Major major;
	major.ParseFromString(base64_decode(message));
	if(!major.has_header())
	{
		SV_ERROR("parse message error");
		return -1;
	}
	Header header = major.header();
	if(header.direction() != Header::FUMSTOAGEN)
	{	
		SV_ERROR("message director error");
		return -1;
	}

    return TaskDispatcher(header.type(), major.body());
}

/*
 * 根据消息类型分发处理
 */
int AmqpMessageReceiveProcessor::TaskDispatcher(Header::DataType type, const string &body)
{
	int ret = 0;

	switch(type)
	{
		case Header::CTRL_APP:
			ret = ProcessCommand(body);
			break;
		case Header::CONFIG:
			ret = ProcessConfig(body);
			break;
		case Header::SOFTWARE:
			ret = ProcessSoftwareInstall(body);
			break;
		case Header::REALQUERYHOSTCFG:
			ret = ProcessRealQuery(body);
			break;
		default:
			SV_ERROR("unkonw type : %d", type);
			ret = -1;
	}
	
    return ret;
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
	AppControlProcess::ControlProcess(ctrlAppData);
	
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

	switch(realQueryHostStatusData.querycfgtype())
	{
		case RealQueryHostStatusData::SYSTEM:
		{
			SV_LOG("--- query type : SYSTEM ---");
			HostSystemInfo::SendSystemInfo(realQueryHostStatusData, Header::REALQUERYHOSTCFG);
			break;
		}
		case RealQueryHostStatusData::DISKSTATUS:
		{
			SV_LOG("--- query type : DISKSTATUS ---");
			HostDiskStatusInfo::SendDiskStatusInfo(realQueryHostStatusData, Header::REALQUERYHOSTCFG);
			break;
		}
		case RealQueryHostStatusData::DISKCFG:
		{
			SV_LOG("--- query type : DISKCFG ---");
			HostDiskCfgInfo::SendDiskCfgInfo(realQueryHostStatusData, Header::REALQUERYHOSTCFG);
			break;
		}
		case RealQueryHostStatusData::DISKHEALTH:
		{
			SV_LOG("--- query type : DISKHEALTH ---");
			HostDiskSmartCtrlInfo::SendDiskSmartCtlInfo(realQueryHostStatusData, Header::REALQUERYHOSTCFG);
			break;
		}
		case RealQueryHostStatusData::DISKRAID:
		{
			SV_LOG("--- query type : DISKRAID ---");
			HostDiskRaidInfo::SendDiskRaidInfo(realQueryHostStatusData, Header::REALQUERYHOSTCFG);
			break;
		}
		case RealQueryHostStatusData::NIC:
		{
			SV_LOG("--- query type : NIC ---");
			HostNicStatusInfo::SendNicStatusInfo(realQueryHostStatusData, Header::REALQUERYHOSTCFG);
			break;
		}
		case RealQueryHostStatusData::PROCESS:
		{
			SV_LOG("--- query type : PROCESS ---");
			HostRealProcessInfo::SendRealProcessInfo(realQueryHostStatusData, Header::REALQUERYHOSTCFG);
			break;
		}
		default:
		{
			SV_ERROR("unknown query type:%d", realQueryHostStatusData.querycfgtype());
			return -1;
		}
	}
	
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
	ConfManager::GetInstance()->Analyse(configData);
	
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

