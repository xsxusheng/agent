/*************************************************************************
* File Name : RegisterAppTable.cpp
* Author : xus103
* Created Time : 2018年04月10日
* Description : app 注册表管理
* CopyRight : Copyright(c) 2000-2020 fiberhome
* OtherInfo :
* ModifyLog :
 ************************************************************************/

#include "AppManager.h"
#include "RegisterAppTable.h"

unordered_map<string, App> RegisterAppTable::m_appTable;

/***********************************************************************
 * FunctionName : GetAppTable
 * Author : xus103
 * CreateDate : 2018/04/10
 * Description : 获取app注册表
 * InputParam : 
 * OutputParam :
 * Return Value : 返回app注册表
 * Relation : 
 * OtherInfo : 无
 ***********************************************************************/
unordered_map<string, App> RegisterAppTable::GetAppTable()
{
	return m_appTable;
}



/***********************************************************************
 * FunctionName : RegisterApp
 * Author : xus103
 * CreateDate : 2018/04/10
 * Description : 注册app
 * InputParam : app : 要注册的app
 * OutputParam :
 * Return Value : 返回app注册表
 * Relation : 
 * OtherInfo : 无
 ***********************************************************************/
void RegisterAppTable::RegisterApp(App &app)
{
	if(AppExist(app))
	{
		return;
	}
	app.SetAppTryInstallingVersion("-1");
        app.SetAppTryInstallingStatus(-1);
	app.SetAppTryInstallingFailedReason("unknown");
	m_appTable[app.GetAppType()] = app;
	Major major = AppToProtoBuf(app, AppData::ADD);
	AmqpMessageSendProcessor::GetInstance()->SendMessageToFums(major);
}


/***********************************************************************
 * FunctionName : AppExist
 * Author : xus103
 * CreateDate : 2018/04/10
 * Description : 判断app是否已注册
 * InputParam : app ： 要判断的app
 * OutputParam :
 * Return Value : 已注册返回true, 未注册返回false
 * Relation : 
 * OtherInfo : 无
 ***********************************************************************/
bool RegisterAppTable::AppExist(App &app)
{
	bool exist = m_appTable.find(app.GetAppType()) != m_appTable.end() ? true : false;
	return exist;
}



/***********************************************************************
 * FunctionName : ClearAllAppRecord
 * Author : xus103
 * CreateDate : 2018/04/10
 * Description : 清除所有APP
 * InputParam : 
 * OutputParam :
 * Return Value : 
 * Relation : 
 * OtherInfo : 无
 ***********************************************************************/
void RegisterAppTable::ClearAllAppRecord()
{
	m_appTable.clear();
}


/***********************************************************************
 * FunctionName : ModifyRegisteredApp
 * Author : xus103
 * CreateDate : 2018/04/10
 * Description : 修改注册的APP
 * InputParam : 
 * OutputParam :
 * Return Value : 
 * Relation : 
 * OtherInfo : 无
 ***********************************************************************/
void RegisterAppTable::ModifyRegisteredApp(App &app)
{
	for(auto row : m_appTable)
	{
		if(row.first.compare(app.GetAppType()) == 0)
		{
			string appType = app.GetAppType();
			string appVersion = AppManager::GetAppVersion(appType);
			app.SetAppVersion(appVersion);
			Major major = AppToProtoBuf(app, AppData::UPDATE);
			AmqpMessageSendProcessor::GetInstance()->SendMessageToFums(major);	
			break;
		}
	}
	
}


/***********************************************************************
 * FunctionName : AppToProtoBuf
 * Author : xus103
 * CreateDate : 2018/04/10
 * Description : app 生成proto格式消息
 * InputParam : app : 要上报的app
 				type : 上报类型
 * OutputParam :
 * Return Value : 返回major
 * Relation : 
 * OtherInfo : 无
 ***********************************************************************/
Major RegisterAppTable::AppToProtoBuf(App &app, AppData::APP_OP_TYPE type)
{
	AppData appData;
	string appType = app.GetAppType();

	appData.set_apptype(appType);
	appData.set_appversion(app.GetAppVersion());
	
	if(app.GetAppStatus() == App::STARTED)
	{
		appData.set_appstatus(AppData::RUNNING);
	}
	else
	{
		appData.set_appstatus(AppData::STOPPED);
	}

	appData.set_apptryinstallingversion(app.GetAppTryInstallingVersion());
	switch(app.GetAppTryInstallingStatus())
	{
		case App::INSTALLED_SUCCESS:
		{
			appData.set_apptryinstallingstatus(AppData::INSTALLED_SUCCESS);
			break;
		}
		case App::INSTALLED_FAILED:
		{
			appData.set_apptryinstallingstatus(AppData::INSTALLED_FAILED);
			break;
		}
		case App::DOWNLOAD_SUCC_NOT_INSTALL:
		{
			appData.set_apptryinstallingstatus(AppData::DOWNLOAD_SUCC_NOT_INSTALL);
			break;
		}
		case App::DOWNLOAD_FAILED:
		{
			appData.set_apptryinstallingstatus(AppData::DOWNLOAD_FAILED);
			break;
		}
	}

	appData.set_op_type(type);
	appData.set_apptryinstallingfailedreason(app.GetAppTryInstallingFailedReason());
	appData.set_ismaystart(app.GetIsStart());
	appData.set_startcount(app.GetStartCount());
	appData.set_appdemonstatus(app.GetAppDaemonStatus());

	Major major = ProtoBufPacker::PackAppEntity(ProtoBufPacker::SerializeToArray<AppData>(appData));
	return major;
}







