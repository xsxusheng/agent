/*************************************************************************
* File Name : ConfManager.h
* Author : xus103
* Created Time : 2018年03月13日
* Description : config process
* CopyRight : Copyright(c) 2000-2020 fiberhome
* OtherInfo :
* ModifyLog :
 ************************************************************************/
#ifndef _CONFMANAGER_H_
#define _CONFMANAGER_H_
#include <iostream>
#include <string>
#include "../msg/Locker.h"
#include "../proto/Config.pb.h"
#include "../proto/CommonDefine.pb.h"
#include "../proto/Msg.pb.h"
#include "../utils/Lock.h"
#include "AgentConfFile.h"
#include "AppConfFile.h"
#include "NtpConfFile.h"
#include "AppRegisteredConfFile.h"

using namespace com::fiberhome::fums::proto;
using namespace std;

class ConfManager
{
public:
	static CRWLock appRegisteredConfFileRWLoc;
	static CRWLock agentConfFileRWLock;
	static CRWLock appConfFileRWLock;
	static CRWLock ntpConfFileRWLock;

	/* 获取配置管理单实例 */
	static ConfManager* GetInstance();

	/* 初始化配置管理 */
	int InitConfManager();

	/* 分析处理配置类型，分发 */
	int Analyse(ConfigData &config);
	
protected:
	ConfManager();
	~ConfManager();
	
private:
	AgentConfFile* agentConfFile;
	AppConfFile* appConfFile;
	NtpConfFile* ntpConfFile;
	AppRegisteredConfFile *appRegisteredConfFile;
	static Locker sm_lock;
	static ConfManager* sm_confManager;

};

#endif














