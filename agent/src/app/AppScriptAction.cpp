#include "../utils/AgentConstantDef.h"
#include "../utils/ScriptAction.h"
#include "../utils/sv_log.h"
#include "../utils/Common.h"
#include "../proto/CommonDefine.pb.h"
#include "AppScriptAction.h"
using namespace com::fiberhome::fums::proto;

AppScriptAction::AppScriptAction()
{
	rtnValCode = CommonResponse::FAILED;
	exeStatus = FAILED;
}
AppScriptAction::~AppScriptAction(){}


void AppScriptAction::StartApp(string &appType)
{
	string script =  AgentConstantDef::GetStartScript(appType);
	//to 判断app是否受控，及其状态是否停止
	if(!Common::FileExist(script))
	{
		return;
	}
	ExecuteScript(script);
	return;
}

void AppScriptAction::StopApp(string &appType)
{
	string script =  AgentConstantDef::GetStopScript(appType);
	//to 判断app是否受控，及其状态是否停止
	if(!Common::FileExist(script))
	{
		return;
	}
	ExecuteScript(script);
	if(exeStatus == SUCCESS && outContent.empty())
	{
		outContent = "stoped";
	}
	return;
}

void AppScriptAction::RestartApp(string &appType)
{
	string script = AgentConstantDef::GetRestartScript(appType);
	if(!Common::FileExist(script))
	{
		return;
	}
	ExecuteScript(script);
        return;
}

void AppScriptAction::ViewAppStatus(const string &appType)
{
	string script = AgentConstantDef::GetViewStatusScript(appType);
	if(!Common::FileExist(script))
	{
		return;
	}
	//SV_LOG("script : %s", script.c_str());
	ExecuteScript(script);
	return;
}

void AppScriptAction::ViewDaemonStatus(string &appType)
{
	string script = AgentConstantDef::GetViewDaemonStatusScript(appType);
	if(!Common::FileExist(script))
	{
		return;
	}
	ExecuteScript(script);
	return;
}

void AppScriptAction::ViewRunningVersion(string &appType)
{
	string script = AgentConstantDef::GetViewRunningVersionScript(appType);
	if(!Common::FileExist(script))
	{
		return;
	}
	ExecuteScript(script);
	return;
}

void AppScriptAction::HaStartApp(string &appType)
{
	string script = AgentConstantDef::GetHaStartScript(appType);
	if(!Common::FileExist(script))
	{
		return;
	}
	ExecuteScript(script);
	return;
}


void AppScriptAction::HaRestartApp(string &appType)
{
	string script = AgentConstantDef::GetHaRestartScript(appType);
	if(!Common::FileExist(script))
	{
		return;
	}
	ExecuteScript(script);
	return;
}

void AppScriptAction::SwitchHa(string &appType)
{
	string script = AgentConstantDef::GetSwitchHaScript(appType);
	if(!Common::FileExist(script))
	{
		return;
	}
	ExecuteScript(script);
	return;
}


void AppScriptAction::ViewHaStatus(string &appType)
{
	string script = AgentConstantDef::GetSwitchHaScript(appType);
	if(!Common::FileExist(script))
	{
		return;
	}
	ExecuteScript(script);
	return;
}

void AppScriptAction::NotifyAppCfgUpdate(string &script)
{
	ExecuteScript(script);
	if(!Common::FileExist(script))
	{
		return;
	}
	return;
}


void AppScriptAction::FetchAppLoadConfFile(string &script)
{
	ExecuteScript(script);
	if(!Common::FileExist(script))
	{
		return;
	}
	return;
}

void AppScriptAction::FetchServerStatus(string &appType)
{
	string script = AgentConstantDef::GetServerStatusScript(appType);
	if(!Common::FileExist(script))
	{
		return;
	}
	ExecuteScript(script);
	return;
}

void AppScriptAction::ExecuteScript(string &cmd)
{
	SV_LOG("cmd : %s", cmd.c_str());
	if(cmd.empty())
	{
		exeStatus = FAILED;
		rtnValCode = FAILED;
		return;
	}

	outContent = "";
	int result = CScriptAction::ExecuteScript(cmd, outContent);
	SV_LOG("----------------------re %d", result);
	if(result != 0)
	{
		exeStatus = FAILED;
		rtnValCode = FAILED;
		return;
	}
	if(outContent.empty())
	{
		outContent = "unknown";
	}
	exeStatus = SUCCESS;
	rtnValCode = CommonResponse::SUCCESS;
	return;
}
/*
void AppScriptAction::ExecuteScript(string cmd)
{
	SV_LOG("cmd : %s", cmd.c_str());
}
*/


