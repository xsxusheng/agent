#ifndef _APPSCRIPTACTION_H_
#define _APPSCRIPTACTION_H_
#include <iostream>
#include <string>
using namespace std;

class AppScriptAction
{
	int m_exeProcessCode;
	int m_rtnValCode;
	string m_outConten;
public:
	AppScriptAction();
	~AppScriptAction();

//	int GetExeProcessCode();
//	int GetRtnValCode();

	/* 获取脚本输出内容 */
//	string GetOutConten();

	/* 启动APP */
	void StartApp(string &appType);

	/* 停止APP */
	void StopApp(string &appType);

	/* 重启APP */
	void RestartApp(string &appType);

	/* 查看APP状态 */
	void ViewAppStatus(const string &appType);
	
	/* 查看daemon状态 */
	void ViewDaemonStatus(string &appType);

	/* 查看APP的运行版本 */
	void ViewRunningVersion(string &appType);

	void HaStartApp(string &appType);
	void HaRestartApp(string &appType);
	void SwitchHa(string &appType);
	void ViewHaStatus(string &appType);

	/* 通知APP更新配置 */
	void NotifyAppCfgUpdate(string &script);
	
	/* 获取APP加载配置文件 */
	void FetchAppLoadConfFile(string &script);

	/* 获取服务器状态 */
	void FetchServerStatus(string &appType);

	
	//bool IsValid(RtnValue &val);
	/* 执行脚本 */
	void ExecuteScript(string &cmd);
	//void ExecuteScript(string cmd);
};

#endif
