#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <netdb.h>
#include "../../app/App.h"
#include "../../app/RegisterAppTable.h"
#include "AppMsgManager.h"

//带参构造函数
//ipv6 为true, 启动ipv6消息线程,否则启动ipv4线程
RecvMsgThread::RecvMsgThread(bool ipv6)
{
	m_ipv6 = ipv6;
}

RecvMsgThread::~RecvMsgThread(){}



void RecvMsgThread::InitUDPSocket()
{
	struct addrinfo addrInfo;
	struct addrinfo *addrServer = NULL;
	struct addrinfo *addr = NULL;
	memset(&addrInfo, 0, sizeof(addrInfo));

	if(m_ipv6)
	{
		addrInfo.ai_family = AF_INET6;
	}
	else
	{
		addrInfo.ai_family = AF_INET;
	}
	addrInfo.ai_flags = AI_PASSIVE;
	addrInfo.ai_socktype = SOCK_DGRAM;
	addrInfo.ai_protocol = IPPROTO_UDP;

	int ret = getaddrinfo(NULL, AgentUtils::GetAppMsgPort().c_str(), &addrInfo, &addrServer);
	if(ret != 0)
	{
		SV_LOG("%s", gai_strerror(ret));
		throw -1;
	}	
	
	m_socket = -1;
	addr = addrServer;
	while(addr != NULL)
	{
		m_socket = socket(addrServer->ai_family, addrServer->ai_socktype, addrServer->ai_protocol);
		if(m_socket < 0)
		{
			SV_WARN("continue m_socket: %d", m_socket);
			continue;
		}
		int opt = 1;
		if(setsockopt(m_socket, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) < 0)
		{
			SV_ERROR("set reuseaddr error");
		}

		//设置超时5s
		struct timeval tv_out;
		tv_out.tv_sec = 5;
		tv_out.tv_usec = 10000;
		if(setsockopt(m_socket, SOL_SOCKET, SO_RCVTIMEO, (char *)&tv_out, sizeof(tv_out)) < 0)
		{
			SV_ERROR("set socket timeout error");
		}

		if(bind(m_socket, addrServer->ai_addr, addrServer->ai_addrlen) == 0)
		{
			break;
		}

		SV_ERROR("udp socket bind error m_socket: %d", m_socket);
		close(m_socket);
		m_socket = -1;

		addr = addr->ai_next;
	}
	freeaddrinfo(addrServer);

	return;
}

void RecvMsgThread::ReadUDPData()
{
	int BUFSIZE = 1024*1024;
	char *data = new char[BUFSIZE];


	while(1)
	{
		struct sockaddr_storage addr;
		socklen_t addrLen = sizeof(addr);
		memset(data, 0, BUFSIZE);

		ssize_t numBytesRcvd = recvfrom(m_socket, data, BUFSIZE, 0, (struct sockaddr *)&addr, &addrLen);
		if(numBytesRcvd > 0)
		{
			string buffer(data);
			unordered_map<string, string> msgMap = Common::XmlToMap(buffer);
			AppMsgManager::GetInstance()->AddMsg(msgMap);
		}	
		//if(strlen(data) < BUFSIZE)

		{
			SV_LOG("receive app msg: %s", data);
		}
	} 
	return;
}

void RecvMsgThread::CloseUDPSocket()
{
	close(m_socket);

	return;
}


void RecvMsgThread::__DoRun()
{
	SV_LOG("RecvMsgThread ------------- %d", GetThreadId());
	while(1)
	{
		try
		{
			InitUDPSocket();
			ReadUDPData();
		}catch(...)
		{
			CloseUDPSocket();
			SV_ERROR("Read UDP data error");
		}
	}

	return;
}




AppMsgManager* AppMsgManager::sm_appMsgManager = NULL;
CMutex AppMsgManager::sm_lock;

AppMsgManager::AppMsgManager() : Thread(true)
{
	m_recvIpv4Msg =  NULL;
	m_recvIpv6Msg =  NULL;
}
AppMsgManager::~AppMsgManager()
{
}

AppMsgManager* AppMsgManager::GetInstance()
{
	if(sm_appMsgManager == NULL)
	{
		sm_lock.Lock();
		if(sm_appMsgManager == NULL)
		{
			sm_appMsgManager = new (std::nothrow) AppMsgManager();
		}
		sm_lock.UnLock();
	}	
	
	return sm_appMsgManager;
}

int AppMsgManager::Init()
{
	//启动IPV6接收线程
	if(m_recvIpv6Msg == NULL && AgentUtils::UseIPV6())
	{
		m_recvIpv6Msg = new (std::nothrow) RecvMsgThread(true);
		if(m_recvIpv6Msg == NULL)
		{
			SV_ERROR("new error");
			return -1;
		}
		m_recvIpv6Msg->Start();
	}

	//启动IPV4接收线程
	if(m_recvIpv4Msg == NULL)
	{
		m_recvIpv4Msg = new (std::nothrow) RecvMsgThread(false);
		if(m_recvIpv4Msg == NULL)
		{
			SV_ERROR("new error");
			return -1;
		}
		m_recvIpv4Msg->Start();
	}


	return 0;
}


void AppMsgManager::__DoRun()
{
	SV_LOG("AppMsgManager ------------- %d", GetThreadId());
	unordered_map<string, string> msgMap;
	while(1)
	{
		try
		{
			//SV_LOG("dispatch---------------------");
			sm_lock.Lock();
			if(!msgQueue.empty())
			{
				msgMap = msgQueue.front();
				msgQueue.pop();	
				sm_lock.UnLock();
			}
			else
			{
				sm_lock.UnLock();
				usleep(100000);
				continue;
			}
		
			if(!msgMap.empty())
			{
				DisPatchMsgFromApp(msgMap);	
				msgMap.clear();
			}
		}catch(...){
			SV_ERROR("app msg dispatch error");
		}
		
		//sleep(1);
	}
	
}

void AppMsgManager::AddMsg(unordered_map<string, string> &msgMap)
{
	sm_lock.Lock();
	msgQueue.push(msgMap);
	sm_lock.UnLock();
}

void AppMsgManager::DisPatchMsgFromApp(unordered_map<string, string> &msgMap)
{
	if(msgMap.empty())
	{
		return;
	}

	string msgType = msgMap["MessageType"];
	if(msgType.compare("alarm"))
	{
		//告警
		ProcessAppAlarmMsg(msgMap);
	}
	else if(msgType.compare("event"))
	{
		//事件
		ProcessAppEventMsg(msgMap);
	}
	else if(msgType.compare("ACS_EVENT"))
	{
		//ACS事件
		ProcessAcsMsg(msgMap);
	}
	else if(msgType.compare("stb_inspect"))
	{
		//STB监控消息
		ProcessStbInspectMsg(msgMap);
	}
	else
	{
		SV_ERROR("parse app msg error : unknown %s", msgType.c_str());
	}
	
	return;
}

void AppMsgManager::ProcessAppEventMsg(unordered_map<string, string> &msgMap)
{
	EventData eventData;
	/*
	eventData.set_evententityinstance(msgMap["EntityInstance"]);
	eventData.set_eventprobablecause(msgMap["ProbableCause"]);
	eventData.set_eventmessage(msgMap["Message"]);
	eventData.set_eventoccurtime();//需填写
	eventData.set_eventseqno(0);
	if(msgMap["ProbableCause"].compare("appstart"))
	{
		App app;
		string appType = msgMap["EntityInstance"];
		transform(appType.begin(), appType.end(), appType.begin(), ::toupper);
		app.SetAppType(appType);
		app.SetAppStatus(App::STARTED);
		app.SetAppDaemonStatus(App::STARTED);

		//获取APP版本
		string version;
		size_t pos = msgMap["Message"].rfind('=', msgMap["Message"].length())
		if(pos == string::npos)
		{
			version = msgMap["Message"];
		}
		else
		{
			version = msgMap["Message"].substr(pos+1, msgMap["Message"].length());
		}
		app.SetAppVersion(version);
		app.SetAppTryInstallingVersion(version);
		app.SetAppTryInstallingFailedReason("success");
		app.SetSetAppTryInstallingStatus(App::INSTALLED_SUCCESS)

		if(!RegisterAppTable::AppExist(app))
		{
			RegisterAppTable::RegisterApp(app);
		}
		else
		{
			RegisterAppTable::ModifyRegisteredApp(app);
		}

		//删除APP告警
		eventData.set_type();//
	}
	else if(msgMap["ProbableCause"].compare("haStateChanged"))
	{
		eventData.set_type();//
	}
	else
	{
		eventData.set_type();//
	}

	
	*/

	Major major = ProtoBufPacker::PackEventEntity(ProtoBufPacker::SerializeToArray<EventData>(eventData));
	AmqpMessageSendProcessor::GetInstance()->SendMessageToFums(major);
	return;
}

void AppMsgManager::ProcessAppAlarmMsg(unordered_map<string, string> &msgMap)
{
	string alarmType("app");
	return;
}

void AppMsgManager::ProcessAcsMsg(unordered_map<string, string> &msgMap)
{
	AcsEventData acsEventData;

	acsEventData.set_messagetype(msgMap["MessageType"]);
	acsEventData.set_probablecause(msgMap["ProbableCause"]);
	acsEventData.set_uniqueno(msgMap["UniqueNo"]);
	acsEventData.set_stb(msgMap["STB"]);
	acsEventData.set_createtime(msgMap["CreateTime"]);
	acsEventData.set_entityinstance(msgMap["EntityInstance"]);
	acsEventData.set_messageformat(msgMap["MessageFormat"]);
	acsEventData.set_message(msgMap["Message"]);
	acsEventData.set_desp(msgMap["Description"]);

	if(msgMap["ProbableCause"].compare("periodic"))
	{
		acsEventData.set_ctrltype(AcsEventData::STB_HEARTBIT);
	}
	else
	{
		acsEventData.set_ctrltype(AcsEventData::CTRL_TM_RST);
	}

	Major major = ProtoBufPacker::PackAcsEventEntity(ProtoBufPacker::SerializeToArray<AcsEventData>(acsEventData));
	AmqpMessageSendProcessor::GetInstance()->SendMessageToFums(major);
	return;
}

void AppMsgManager::ProcessStbInspectMsg(unordered_map<string, string> &msgMap)
{
	StbInspectData stbInspectData;

	stbInspectData.set_messagetype(msgMap["MessageType"]);
	stbInspectData.set_entitytype(msgMap["EntityType"]);
	stbInspectData.set_desp(msgMap["Desp"]);
	stbInspectData.set_entityinstance(msgMap["EntityInstance"]);
	stbInspectData.set_operarglist(msgMap["OperArgList"]);
	stbInspectData.set_operdirect(msgMap["OperDirect"]);
	stbInspectData.set_opername(msgMap["OperName"]);
	stbInspectData.set_operoccurtime(msgMap["OperOccurTime"]);
	stbInspectData.set_operrst(msgMap["OperRst"]);
	stbInspectData.set_stbip(msgMap["StbIp"]);

	Major major = ProtoBufPacker::PackStbInspectEntity(ProtoBufPacker::SerializeToArray<StbInspectData>(stbInspectData));
        AmqpMessageSendProcessor::GetInstance()->SendMessageToFums(major);
	return;
}







