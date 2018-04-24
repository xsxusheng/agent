/*************************************************************************
* File Name : AppManager.cpp
* Author : xus103
* Created Time : 2018年04月10日
* Description : app 管理
* CopyRight : Copyright(c) 2000-2020 fiberhome
* OtherInfo :
* ModifyLog :
 ************************************************************************/

#include <exception>
#include "AppManager.h"
#include "../utils/sv_log.h"


list<App> AppManager::m_appList;
CMutex AppManager::sm_appListLock;

AppManager::AppManager(){}
AppManager::~AppManager(){}



/***********************************************************************
 * FunctionName : __DoRun
 * Author : xus103
 * CreateDate : 2018/04/10
 * Description : app 管理线程注册函数
 * InputParam : 
 * OutputParam :
 * Return Value : 无
 * Relation : 
 * OtherInfo : 无
 ***********************************************************************/
void AppManager::__DoRun()
{
	SV_LOG("AppManager ---------- %d", GetThreadId());
	SV_LOG("start app manager");
	while(1)
	{
		try
		{
			UpdateAppList();
			int i = 0;
			for (auto app : m_appList)
			{
				SV_LOG("-------%d-------", i++);
				SV_LOG("app type : %s", app.GetAppType().c_str());
				UpdateAppStatus(app);
				if(0)
				{

				}
				else
				{
					//尝试产生一条告警
					//
				}
				RegisterAppTable::ModifyRegisteredApp(app);
			}
		}catch(...){
			SV_ERROR("Exception: ");
		}
		
		sleep(300);
	}
}


/***********************************************************************
 * FunctionName : UpdateAppList
 * Author : xus103
 * CreateDate : 2018/04/10
 * Description : 更新app管理列表
 * InputParam : 
 * OutputParam :
 * Return Value : 无
 * Relation : 
 * OtherInfo : 无
 ***********************************************************************/
void AppManager::UpdateAppList()
{
	SV_LOG("update app list");
	list<App>::iterator iter;
	unordered_map<string, App>::iterator it;
	
	/* 将注册表中有的网元加入到网元管理 */
	unordered_map<string, App> apps = RegisterAppTable::GetAppTable();
	it = apps.empty() ? apps.end() : apps.begin();
	while(it != apps.end())
	{
		iter = m_appList.empty() ? m_appList.end() : m_appList.begin();
		while(iter != m_appList.end())
		{
			if((*iter).GetAppType().compare(it->first) == 0)
			{
				break;
			}
			iter++;
		}

		if(iter == m_appList.end())
		{
			m_appList.push_back(it->second);
		}
		it++;	
	}
	
	/* 将注册表中没有的网元删除 */
	iter = m_appList.empty() ? m_appList.end() : m_appList.begin();
	while(iter != m_appList.end())
	{
		it = apps.empty() ? apps.end() : apps.begin();
		while(it != apps.end())
		{
			if((*iter).GetAppType().compare(it->first) == 0)
			{
				break;
			}
			it++;
		}
		if(it == apps.end())
		{
			iter = m_appList.erase(iter);
			continue;
		}
		iter++;
	}

	return;
}


/***********************************************************************
 * FunctionName : UpdateAppList
 * Author : xus103
 * CreateDate : 2018/04/10
 * Description : 更新app管理列表
 * InputParam : 
 * OutputParam :
 * Return Value : 无
 * Relation : 
 * OtherInfo : 无
 ***********************************************************************/
void AppManager::UpdateAppStatus(App &app)
{
	AppScriptAction appScriptAction;
	string appType = app.GetAppType();

	if(AgentConstantDef::GetAppStrType(EnumDefineData::MW).compare(appType) == 0)
	{
		;//todo
	}
	else
	{
		appScriptAction.ViewAppStatus(appType);
		if(appScriptAction.rtnValCode == AppScriptAction::SUCCESS &&
			appScriptAction.outContent.compare("started") == 0)
		{
			app.SetAppStatus(App::STARTED);
		}
		else
		{
			app.SetAppStatus(App::STOPED);
		}
	}

	return;
}



/***********************************************************************
 * FunctionName : SetStartFlag
 * Author : xus103
 * CreateDate : 2018/04/10
 * Description : 设置app启动标志
 * InputParam : appType ： app类型
 				start : true表示app启动， false表示未启动
 * OutputParam :
 * Return Value : 无
 * Relation : 
 * OtherInfo : 无
 ***********************************************************************/
void AppManager::SetStartFlag(const string& appType, bool start)
{
	sm_appListLock.Lock();
	for (auto app : m_appList)
	{
		if(app.GetAppType().compare(appType) == 0)
		{
			app.SetIsStart(start);
			break;
		}
	}
	sm_appListLock.UnLock();

	return;
}



/***********************************************************************
 * FunctionName : GetAppVersion
 * Author : xus103
 * CreateDate : 2018/04/10
 * Description : 获取app版本
 * InputParam : appType ： app类型
 * OutputParam :
 * Return Value : 返回版本
 * Relation : 
 * OtherInfo : 无
 ***********************************************************************/
string AppManager::GetAppVersion(string &appType)
{
	AppScriptAction appScriptAction;
	appScriptAction.ViewRunningVersion(appType);

	if(appScriptAction.exeStatus == AppScriptAction::SUCCESS)
	{
		return appScriptAction.outContent;
	}

	return "unknown";
}



/***********************************************************************
 * FunctionName : CheckAppDaemonStatus
 * Author : xus103
 * CreateDate : 2018/04/10
 * Description : 检查app daemon状态
 * InputParam : app ： app
 * OutputParam :
 * Return Value : 无
 * Relation : 
 * OtherInfo : 无
 ***********************************************************************/
void AppManager::CheckAppDaemonStatus(App &app)
{
	AppScriptAction appScriptAction;
	string appType = app.GetAppType();
	appScriptAction.ViewDaemonStatus(appType);

	if(appScriptAction.exeStatus == AppScriptAction::SUCCESS)
	{
		if(appScriptAction.outContent.compare("started"))
		{
			app.SetAppDaemonStatus(App::STARTED);
			return;
		}
	}
	app.SetAppDaemonStatus(App::STOPED);
	
	return;
}
