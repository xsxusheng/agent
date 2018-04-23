/*************************************************************************
* File Name : AppScriptAction.cpp
* Author : xus103
* Created Time : 2018年04月10日
* Description : app 脚本处理
* CopyRight : Copyright(c) 2000-2020 fiberhome
* OtherInfo :
* ModifyLog :
 ************************************************************************/

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


/***********************************************************************
 * FunctionName : StartApp
 * Author : xus103
 * CreateDate : 2018/04/10
 * Description : app 启动
 * InputParam : appType ： app 类型
 * OutputParam :
 * Return Value : 无
 * Relation : 
 * OtherInfo : 无
 ***********************************************************************/
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



/***********************************************************************
 * FunctionName : StopApp
 * Author : xus103
 * CreateDate : 2018/04/10
 * Description : app 停止
 * InputParam : appType ： app 类型
 * OutputParam :
 * Return Value : 无
 * Relation : 
 * OtherInfo : 无
 ***********************************************************************/
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



/***********************************************************************
 * FunctionName : RestartApp
 * Author : xus103
 * CreateDate : 2018/04/10
 * Description : app 重启
 * InputParam : appType ： app 类型
 * OutputParam :
 * Return Value : 无
 * Relation : 
 * OtherInfo : 无
 ***********************************************************************/
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


/***********************************************************************
 * FunctionName : ViewAppStatus
 * Author : xus103
 * CreateDate : 2018/04/10
 * Description : app 状态查看
 * InputParam : appType ： app 类型
 * OutputParam :
 * Return Value : 无
 * Relation : 
 * OtherInfo : 无
 ***********************************************************************/
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



/***********************************************************************
 * FunctionName : ViewDaemonStatus
 * Author : xus103
 * CreateDate : 2018/04/10
 * Description : app daemon 状态查看
 * InputParam : appType ： app 类型
 * OutputParam :
 * Return Value : 无
 * Relation : 
 * OtherInfo : 无
 ***********************************************************************/
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


/***********************************************************************
 * FunctionName : ViewRunningVersion
 * Author : xus103
 * CreateDate : 2018/04/10
 * Description : app 运行版本查看
 * InputParam : appType ： app 类型
 * OutputParam :
 * Return Value : 无
 * Relation : 
 * OtherInfo : 无
 ***********************************************************************/
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



/***********************************************************************
 * FunctionName : HaStartApp
 * Author : xus103
 * CreateDate : 2018/04/10
 * Description : app HA 启动
 * InputParam : appType ： app 类型
 * OutputParam :
 * Return Value : 无
 * Relation : 
 * OtherInfo : 无
 ***********************************************************************/
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



/***********************************************************************
 * FunctionName : HaRestartApp
 * Author : xus103
 * CreateDate : 2018/04/10
 * Description : app HA 重启
 * InputParam : appType ： app 类型
 * OutputParam :
 * Return Value : 无
 * Relation : 
 * OtherInfo : 无
 ***********************************************************************/
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


/***********************************************************************
 * FunctionName : SwitchHa
 * Author : xus103
 * CreateDate : 2018/04/10
 * Description : app HA 切换
 * InputParam : appType ： app 类型
 * OutputParam :
 * Return Value : 无
 * Relation : 
 * OtherInfo : 无
 ***********************************************************************/
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



/***********************************************************************
 * FunctionName : ViewHaStatus
 * Author : xus103
 * CreateDate : 2018/04/10
 * Description : 查看 app HA 状态
 * InputParam : appType ： app 类型
 * OutputParam :
 * Return Value : 无
 * Relation : 
 * OtherInfo : 无
 ***********************************************************************/
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



/***********************************************************************
 * FunctionName : NotifyAppCfgUpdate
 * Author : xus103
 * CreateDate : 2018/04/10
 * Description : 通知 app 更新配置
 * InputParam : appType ： app 类型
 * OutputParam :
 * Return Value : 无
 * Relation : 
 * OtherInfo : 无
 ***********************************************************************/
void AppScriptAction::NotifyAppCfgUpdate(string &script)
{
	if(!Common::FileExist(script))
	{
		return;
	}
	ExecuteScript(script);
	return;
}



/***********************************************************************
 * FunctionName : FetchAppLoadConfFile
 * Author : xus103
 * CreateDate : 2018/04/10
 * Description :获取 app 加载配置
 * InputParam : appType ： app 类型
 * OutputParam :
 * Return Value : 无
 * Relation : 
 * OtherInfo : 无
 ***********************************************************************/
void AppScriptAction::FetchAppLoadConfFile(string &script)
{
	if(!Common::FileExist(script))
	{
		return;
	}
	ExecuteScript(script);
	return;
}


/***********************************************************************
 * FunctionName : FetchServerStatus
 * Author : xus103
 * CreateDate : 2018/04/10
 * Description :获取 服务状态
 * InputParam : appType ： app 类型
 * OutputParam :
 * Return Value : 无
 * Relation : 
 * OtherInfo : 无
 ***********************************************************************/
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


/***********************************************************************
 * FunctionName : ExecuteScript
 * Author : xus103
 * CreateDate : 2018/04/10
 * Description :执行cmd
 * InputParam : cmd ： 命令
 * OutputParam :
 * Return Value : 无
 * Relation : 
 * OtherInfo : 无
 ***********************************************************************/
void AppScriptAction::ExecuteScript(string &cmd)
{
	rtnValCode = CommonResponse::FAILED;
	exeStatus = FAILED;
	outContent = "";
	SV_LOG("cmd : %s", cmd.c_str());
	if(cmd.empty())
	{
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


