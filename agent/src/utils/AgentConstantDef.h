#ifndef _AGENTCONSTANTDEF_H_
#define _AGENTCONSTANTDEF_H_
#include <iostream>
#include <unordered_map>
#include <string>
using namespace std;
class AgentConstantDef
{
public:
	static string GetAppStrType(const int appType);
	static string GetStartScript(const string &appType);
	static string GetStopScript(const string &appType);
	static string GetRestartScript(const string &appType);
	static string GetViewStatusScript(const string &appType);
	static string GetViewDaemonStatusScript(const string &appType);
	static string GetViewRunningVersionScript(const string &appType);
	static string GetHaStartScript(const string &appType);
	static string GetHaRestartScript(const string &appType);
	static string GetSwitchHaScript(const string &appType);
	static string GetServerStatusScript(const string &appType);
private:
	static unordered_map<string, string> S_START_SCRIPTS_MAP;
	static unordered_map<string, string> S_STOP_SCRIPTS_MAP;
	static unordered_map<string, string> S_RESTART_SCRIPTS_MAP;
	static unordered_map<string, string> S_VIEW_STATUS_SCRIPTS_MAP;
	static unordered_map<string, string> S_APP_TYPE_STR_MAP_ENUM;
	static unordered_map<string, string> S_VIEW_DAEMON_STATUS_SCRIPTS_MAP;
	static unordered_map<string, string> S_VIEW_VERSION_SCRIPTS_MAP;
	static unordered_map<string, string> S_HA_START_SCRIPTS_MAP;
	static unordered_map<string, string> S_HA_RESTART_SCRIPTS_MAP;
	static unordered_map<string, string> S_SWITCH_HA_SCRIPTS_MAP;
	static unordered_map<string, string> S_VIEW_HA_SCRIPTS_MAP;
	static unordered_map<string, string> S_SERVER_STATUS_SCRIPTS_MAP;
};


#endif
