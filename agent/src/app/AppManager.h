/*************************************************************************
* File Name : AppManager.h
* Author : xus103
* Created Time : 2018年04月10日
* Description : app 管理
* CopyRight : Copyright(c) 2000-2020 fiberhome
* OtherInfo :
* ModifyLog :
 ************************************************************************/

#ifndef _APPMANAGER_H_
#define _APPMANAGER_H_
#include <iostream>
#include <list>
#include <unordered_map>
#include <string>
#include <unistd.h>
#include "../proto/CtrlApp.pb.h"
#include "../utils/Thread.h"
#include "../utils/Lock.h"
#include "../utils/AgentConstantDef.h"
#include "AppScriptAction.h"
#include "RegisterAppTable.h"
#include "AppControl.h"
#include "App.h"
using namespace com::fiberhome::fums::proto;
using namespace std;

class AppManager : public Thread
{
public:
	AppManager();
	~AppManager();

	/* 产生一条告警 */
	//static Alarm GetAlarm(App app);
	
	/* 更新注册的APP表 */
	static void UpdateRegisteredAppList(list<App> &apps);
	
	/* 检测APP状态 */
	static void UpdateAppStatus(App &app);

	/* 检查注册app状态 */
	static void CheckRegisteredAppStatus(App &app);

	/* 获取app版本 */	
	static string GetAppVersion(string &appType);

	/* 检查app daemon 状态 */	
	static void CheckAppDaemonStatus(App &app);

	/* 获取所有注册APP */
	static unordered_map<string, App> GetAllRegisteredApp();

	/* 更新APP列表 */
	static void UpdateAppList();

	/* 设置APP启动标识 */
	static void SetStartFlag(const string& appType, bool start);

	/* 判断APP是否在线 */
	static bool isOnline(string appType);
	
	//static list<AppControl> GetAppControlList();

private:
	void __DoRun();
	static list<App> m_appList;
	static CMutex sm_appListLock;
};

#endif
