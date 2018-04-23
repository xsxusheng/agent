
#ifndef _APPMSGMANAGER_H_
#define _APPMSGMANAGER_H_
#include <iostream>
#include <string>
#include <unordered_map>
#include <queue>
#include <algorithm>
#include "../../proto/Msg.pb.h"
#include "../../proto/Event.pb.h"
#include "../../proto/AcsEvent.pb.h"
#include "../../proto/StbInspect.pb.h"
#include "../../utils/Thread.h"
#include "../../utils/sv_log.h"
#include "../../utils/Common.h"
#include "../../utils/Lock.h"
#include "../../utils/AgentUtils.h"
#include "../../app/App.h"
#include "../../app/RegisterAppTable.h"
#include "../AmqpMessageSendProcessor.h"
using namespace std;
using namespace com::fiberhome::fums::proto;

class RecvMsgThread : public Thread
{
public:
       	RecvMsgThread(bool ipv6);
       	~RecvMsgThread();
	
	void InitUDPSocket();
	void ReadUDPData();
	void CloseUDPSocket();

private:
       void __DoRun();
       bool m_ipv6;
       int m_socket;
};


class AppMsgManager : public Thread
{
public:	
	/* 获取APP消息管理单例*/
	static AppMsgManager* GetInstance();

	/* 初始化APP消息管理 */
	int Init();

	void AddMsg(unordered_map<string, string> &msgMap);
	
	/* 消息分发 */
	void DisPatchMsgFromApp(unordered_map<string, string> &msgMap);

	/* 处理APP事件消息 */
	void ProcessAppEventMsg(unordered_map<string, string> &msgMap);

	/* 处理APP 告警消息 */
	void ProcessAppAlarmMsg(unordered_map<string, string> &msgMap);	

	/* 处理ACS消息 */
	void ProcessAcsMsg(unordered_map<string, string> &msgMap);

	/* 处理STB监测消息 */
	void ProcessStbInspectMsg(unordered_map<string, string> &msgMap);

private:
	AppMsgManager();
	~AppMsgManager();
	void __DoRun();

	queue<unordered_map<string, string>> msgQueue;
	RecvMsgThread *m_recvIpv4Msg;
	RecvMsgThread *m_recvIpv6Msg;
	static AppMsgManager *sm_appMsgManager; 
	static CMutex sm_lock;
};

#endif
