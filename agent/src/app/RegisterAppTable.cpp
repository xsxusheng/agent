#include "AppManager.h"
#include "RegisterAppTable.h"

unordered_map<string, App> RegisterAppTable::m_appTable;

unordered_map<string, App> RegisterAppTable::GetAppTable()
{
	return m_appTable;
}

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

bool RegisterAppTable::AppExist(App &app)
{
	bool exist = m_appTable.find(app.GetAppType()) != m_appTable.end() ? true : false;
	return exist;
}

void RegisterAppTable::ClearAllAppRecord()
{
	m_appTable.clear();
	SV_LOG("aa %d", m_appTable.size());
}

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
