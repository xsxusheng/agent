#include "../utils/sv_log.h"
#include "../utils/ProtoBufPacker.h"
#include "../app/AppScriptAction.h"
#include "../app/AppManager.h"
#include "../msg/AmqpMessageSendProcessor.h"
#include "AppControlProcess.h"

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
	}
	else if(ctrlApp.ctrltype() == CtrlAppData::STOP)
	{
		SV_LOG("***stop***");
		appScriptAction.StopApp(appType);
	}
	else if(ctrlApp.ctrltype() == CtrlAppData::RESTART)
	{
		appScriptAction.RestartApp(appType);
		SV_LOG("***restart***");
	}
	else if(ctrlApp.ctrltype() == CtrlAppData::HASTART)
	{
		SV_LOG("***hastart***");
		appScriptAction.HaStartApp(appType);
	}
	else if(ctrlApp.ctrltype() == CtrlAppData::HARESTART)
	{
		SV_LOG("***harestart***");
		appScriptAction.HaRestartApp(appType);
	}
	else
	{
		SV_LOG("unkown ctrl");
		appScriptAction.rtnValCode = CommonResponse::FAILED;
	}
	
	/* 设置执行脚本的响应结果*/
	if(appScriptAction.exeStatus == AppScriptAction::SUCCESS)
	{
		SV_LOG("cmd sucess");
		commResponse->set_status(CommonResponse::SUCCESS);
	}
	else
	{	
		SV_LOG("cmd error");
		AppManager::SetStartFlag(appType, false);
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
