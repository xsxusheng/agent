#include "../utils/sv_log.h"
#include "../utils/ProtoBufPacker.h"
#include "../app/AppScriptAction.h"
#include "../msg/AmqpMessageSendProcessor.h"
#include "AppControlProcess.h"

int AppControlProcess::ControlProcess(CtrlAppData &ctrlApp)
{
	CtrlAppRstResponse ctrlResponse;
	CommonResponse* commResponse = ctrlResponse.mutable_res();
	AppScriptAction scriptAction;
	
	if(ctrlApp.ctrltype() == CtrlAppData::START)
	{
		SV_LOG("***start***");
	}
	else if(ctrlApp.ctrltype() == CtrlAppData::STOP)
	{
		SV_LOG("***stop***");
	}
	else if(ctrlApp.ctrltype() == CtrlAppData::RESTART)
	{
		SV_LOG("***restart***");
	}
	else if(ctrlApp.ctrltype() == CtrlAppData::HASTART)
	{
		SV_LOG("***hastart***");
	}
	else if(ctrlApp.ctrltype() == CtrlAppData::HARESTART)
	{
		SV_LOG("***harestart***");
	}
	else
	{
		SV_LOG("unkown ctrl");
	}

	ctrlResponse.set_uniqueid(ctrlApp.uniqueid());
	Major major = ProtoBufPacker::PackAppEntity(ProtoBufPacker::SerializeToArray<CtrlAppRstResponse>(ctrlResponse));
	AmqpMessageSendProcessor::GetInstance()->SendMessageToFums(major);
	return 0;
}
