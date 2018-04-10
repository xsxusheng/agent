#include "../utils/AgentConstantDef.h"
#include "../utils/sv_log.h"
#include "AppScriptAction.h"

AppScriptAction::AppScriptAction()
{

}
AppScriptAction::~AppScriptAction(){}


void AppScriptAction::StartApp(string &appType)
{
	string script =  AgentConstantDef::GetStartScript(appType);
	//to 判断app是否受控，及其状态是否停止
	ExecuteScript(script);
	return;
}

void AppScriptAction::StopApp(string &appType)
{
	string script =  AgentConstantDef::GetStopScript(appType);
	//to 判断app是否受控，及其状态是否停止
	ExecuteScript(script);
	return;
}

void AppScriptAction::RestartApp(string &appType)
{
	string script = AgentConstantDef::GetRestartScript(appType);
	ExecuteScript(script);
        return;
}

void AppScriptAction::ViewAppStatus(const string &appType)
{
	string script = AgentConstantDef::GetViewStatusScript(appType);
	//SV_LOG("script : %s", script.c_str());
	ExecuteScript(script);
	return;
}

void AppScriptAction::ViewDaemonStatus(string &appType)
{
	string script = AgentConstantDef::GetViewDaemonStatusScript(appType);
	ExecuteScript(script);
	return;
}

void AppScriptAction::ViewRunningVersion(string &appType)
{
	string script = AgentConstantDef::GetViewRunningVersionScript(appType);
	ExecuteScript(script);
	return;
}

void AppScriptAction::HaStartApp(string &appType)
{
	string script = AgentConstantDef::GetHaStartScript(appType);
	ExecuteScript(script);
	return;
}


void AppScriptAction::HaRestartApp(string &appType)
{
	string script = AgentConstantDef::GetHaRestartScript(appType);
	ExecuteScript(script);
	return;
}

void AppScriptAction::SwitchHa(string &appType)
{
	string script = AgentConstantDef::GetSwitchHaScript(appType);
	ExecuteScript(script);
	return;
}


void AppScriptAction::ViewHaStatus(string &appType)
{
	string script = AgentConstantDef::GetSwitchHaScript(appType);
	ExecuteScript(script);
	return;
}

void AppScriptAction::NotifyAppCfgUpdate(string &script)
{
	ExecuteScript(script);
	return;
}


void AppScriptAction::FetchAppLoadConfFile(string &script)
{
	ExecuteScript(script);
	return;
}

void AppScriptAction::FetchServerStatus(string &appType)
{
	string script = AgentConstantDef::GetServerStatusScript(appType);
	ExecuteScript(script);
	return;
}

void AppScriptAction::ExecuteScript(string &cmd)
{
	SV_LOG("cmd : %s", cmd.c_str());
}
/*
void AppScriptAction::ExecuteScript(string cmd)
{
	SV_LOG("cmd : %s", cmd.c_str());
}
*/


