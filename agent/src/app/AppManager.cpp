
#include <exception>
#include "AppManager.h"
#include "../utils/sv_log.h"


AppManager::AppManager(){}
AppManager::~AppManager(){}
list<App> AppManager::m_appList;


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
	AppScriptAction action;
	string appType = app.GetAppType();
	action.ViewAppStatus(appType);
}
