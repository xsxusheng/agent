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
/*
	appData.set_apptype(app.GetAppType());
	appData.set_appversion(app.GetAppVersion());
	
	switch(app.GetStatus)
	{
		case AppStatusEnum::RUNNING:
		{
			appData.set_appstatus(AppData::RUNNING);
			break;
		}
		case AppStatusEnum::STOPED:
		{
			appData.set_appstatus(AppData::STOPED);
			break;
		}
		default:
		{
			SV_ERROR("unknown status");
		}
	}

	appData.set_apptryinstallingversion(app.GetAppTryInstallingVersion());
	switch(app.GetAppTryInstallingStatus())
	{
		case 
	}

	appData.set_optype(type);
	appData.set_apptryinstallingfailedreason();
	appData.set_ismaystart();
	appData.set_startcount();
	appData.set_appdaemonstatus();
*/
	Major major = ProtoBufPacker::PackAppEntity(ProtoBufPacker::SerializeToArray<AppData>(appData));
	return major;
}
