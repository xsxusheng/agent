
#include <exception>
#include "AppManager.h"
#include "../utils/sv_log.h"


list<App> AppManager::m_appList;
CMutex AppManager::sm_appListLock;

AppManager::AppManager(){}
AppManager::~AppManager(){}

void AppManager::__DoRun()
{
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
		
		sleep(20);
	}
}



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
			SV_LOG("%s  :  %s", (*iter).GetAppType().c_str(), it->first.c_str());
			if((*iter).GetAppType().compare(it->first) == 0)
			{
				break;
			}
			it++;
		}
		if(it == apps.end())
		{
			SV_LOG("erase %s", (*iter).GetAppType().c_str());
			iter = m_appList.erase(iter);
			continue;
		}
		iter++;
	}
}


void AppManager::UpdateAppStatus(App &app)
{
	AppScriptAction appScriptAction;
	string appType = app.GetAppType();

	if(AgentConstantDef::GetAppStrType(EnumDefineData::MW).compare(appType) == 0)
	{
		;
	}
	else
	{
		appScriptAction.ViewAppStatus(appType);
		if(appScriptAction.rtnValCode == AppScriptAction::SUCCESS ||
			appScriptAction.outContent.compare("started") == 0)
		{
			app.SetAppStatus(App::STARTED);
		}
		else
		{
			app.SetAppStatus(App::STOPED);
		}
	}
}


void AppManager::SetStartFlag(const string& appType, bool start)
{
	sm_appListLock.Lock();
	for (auto app : m_appList)
	{
		if(app.GetAppType().compare(appType) == 0)
		{
			app.SetIsStart(start);
			//break;
		}
	}
	sm_appListLock.UnLock();
}

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
