/*************************************************************************
* File Name : AppScriptAction.h
* Author : xus103
* Created Time : 2018年04月10日
* Description : app 脚本处理
* CopyRight : Copyright(c) 2000-2020 fiberhome
* OtherInfo :
* ModifyLog :
 ************************************************************************/

#ifndef _APPSCRIPTACTION_H_
#define _APPSCRIPTACTION_H_
#include <iostream>
#include <string>
using namespace std;

class AppScriptAction
{
public:
	/* 脚本执行的结果 */
	int exeStatus;
	/* 脚本执行退出值 */
	int rtnValCode;
	/* 脚本输出内容 */
	string outContent;
	enum Result{
		SUCCESS = 0,
		FAILED  = 1 
	};
	
public:
	AppScriptAction();
	~AppScriptAction();

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
