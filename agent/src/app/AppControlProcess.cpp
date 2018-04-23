/*************************************************************************
* File Name : AppControlProcess.cpp
* Author : xus103
* Created Time : 2018年04月10日
* Description : app cmd process
* CopyRight : Copyright(c) 2000-2020 fiberhome
* OtherInfo :
* ModifyLog :
 ************************************************************************/

#include "../utils/sv_log.h"
#include "../utils/ProtoBufPacker.h"
#include "../app/AppScriptAction.h"
#include "../app/AppManager.h"
#include "../msg/AmqpMessageSendProcessor.h"
#include "AppControlProcess.h"


/***********************************************************************
 * FunctionName : ControlProcess
 * Author : xus103
 * CreateDate : 2018/04/10
 * Description : 处理app命令操作
 * InputParam : 
 * OutputParam :
 * Return Value : 成功返回0， 失败返回-1
 * Relation : 
 * OtherInfo : 无
 ***********************************************************************/

int AppControlProcess::ControlProcess(CtrlAppData &ctrlApp)
{
	CtrlAppRstResponse ctrlResponse;
	CommonResponse* commResponse = ctrlResponse.mutable_res();
	AppScriptAction appScriptAction;
	string appType = ctrlApp.apptype();
	
	if(ctrlApp.ctrltype() == CtrlAppData::START)
	{
		SV_LOG("***start***");
		appScriptAction.StartApp(appType);
		/* 设置执行脚本的响应结果*/
		if(appScriptAction.exeStatus == AppScriptAction::SUCCESS)
		{
			AppManager::SetStartFlag(appType, true);
			commResponse->set_status(CommonResponse::SUCCESS);
		}
		else
		{	
			commResponse->set_status(CommonResponse::FAILED);
		}
	}
	else if(ctrlApp.ctrltype() == CtrlAppData::STOP)
	{
		SV_LOG("***stop***");
		appScriptAction.StopApp(appType);
		/* 设置执行脚本的响应结果*/
		if(appScriptAction.exeStatus == AppScriptAction::SUCCESS)
		{
			AppManager::SetStartFlag(appType, false);
			commResponse->set_status(CommonResponse::SUCCESS);
		}
		else
		{	
			commResponse->set_status(CommonResponse::FAILED);
		}
	}
	else if(ctrlApp.ctrltype() == CtrlAppData::RESTART)
	{
		appScriptAction.RestartApp(appType);
		/* 设置执行脚本的响应结果*/
		if(appScriptAction.exeStatus == AppScriptAction::SUCCESS)
		{
			AppManager::SetStartFlag(appType, true);
			commResponse->set_status(CommonResponse::SUCCESS);
		}
		else
		{	
			commResponse->set_status(CommonResponse::FAILED);
		}
		SV_LOG("***restart***");
	}
	else if(ctrlApp.ctrltype() == CtrlAppData::HASTART)
	{
		SV_LOG("***hastart***");
		appScriptAction.HaStartApp(appType);
		/* 设置执行脚本的响应结果*/
		if(appScriptAction.exeStatus == AppScriptAction::SUCCESS)
		{
			commResponse->set_status(CommonResponse::SUCCESS);
			AppManager::SetStartFlag(appType, true);
		}
		else
		{	
			commResponse->set_status(CommonResponse::FAILED);
		}
	}
	else if(ctrlApp.ctrltype() == CtrlAppData::HARESTART)
	{
		SV_LOG("***harestart***");
		appScriptAction.HaRestartApp(appType);
		/* 设置执行脚本的响应结果*/
		if(appScriptAction.exeStatus == AppScriptAction::SUCCESS)
		{
			commResponse->set_status(CommonResponse::SUCCESS);
			AppManager::SetStartFlag(appType, true);
		}
		else
		{	
			commResponse->set_status(CommonResponse::FAILED);
		}
	}
	else
	{
		appScriptAction.rtnValCode = CommonResponse::FAILED;
		commResponse->set_status(CommonResponse::FAILED);
	}
	
	commResponse->set_responsecode(appScriptAction.rtnValCode);
	commResponse->set_responsemsg(appScriptAction.outContent);
	ctrlResponse.set_uniqueid(ctrlApp.uniqueid());

	/* 发送响应给fums */
	Major major = ProtoBufPacker::PackResponseData(ProtoBufPacker::SerializeToArray<CtrlAppRstResponse>(ctrlResponse), Header::CTRL_APP ,ctrlApp.uniqueid());
	AmqpMessageSendProcessor::GetInstance()->SendMessageToFums(major);
	
	return 0;
}
