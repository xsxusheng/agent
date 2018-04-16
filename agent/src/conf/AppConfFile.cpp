/*************************************************************************
* File Name : AppConfFile.cpp
* Author : xus103
* Created Time : 2018年03月13日
* Description : config process
* CopyRight : Copyright(c) 2000-2020 fiberhome
* OtherInfo :
* ModifyLog :
 ************************************************************************/
#include "../utils/sv_log.h"
#include "../utils/Common.h"
#include "../utils/AgentUtils.h"
#include "../app/AppScriptAction.h"
#include "ConfManager.h"
#include "AppConfFile.h"

AppConfFile::AppConfFile()
{

}

AppConfFile::~AppConfFile()
{

}

int AppConfFile::Init()
{
	return 0;
}


int AppConfFile::DeleteExpiredConfFile(string &path, string &newFileName, string &usingFileName)
{
   
	return 0;    
}


int AppConfFile::Analyse(ConfigData &config, ConfigUpdateResponse &response)
{
	AppScriptAction appScriptAction;
	string fileName = "error";

	int ret = ConfManager::appConfFileRWLock.TimeRdLock(20);
	if(0 != ret)
	{	SV_LOG("get lock error");
		return -1;
	}

	/* 文件保存路径 */
	string fileSavePath = config.filesavepath();
	/* 下发的新的配置文件 */
	string newFileName = config.configfilename();

	/* 获取app加载配置 */
	string viewConfScript = config.viewconfscript();
	appScriptAction.FetchAppLoadConfFile(viewConfScript);
	if(appScriptAction.exeStatus == AppScriptAction::SUCCESS)
	{
		fileName = appScriptAction.outContent;
	}
	string usingFileName = Common::GetFileName(fileName);
	if(!newFileName.compare(usingFileName))
	{
		string errMsg = "the same file name, newFileName:" + newFileName + ", usingFileName:" + usingFileName;
                SV_ERROR("%s", errMsg.c_str());
                response.set_status(CommonResponse::FAILED);
                response.set_reason(errMsg);
                ConfManager::appConfFileRWLock.UnLock();
                return -1;
	}
	
	if(!Common::FileExist(fileSavePath))
	{
		SV_LOG("%s not exist, to create", fileSavePath.c_str());
		if(!Common::CreatDir(fileSavePath))
		{
			SV_ERROR("create dir:%s error", fileSavePath.c_str());
			string errMsg = "creat dir:" + fileSavePath + "error";
                	response.set_status(CommonResponse::FAILED);
                	response.set_reason(errMsg);
                	ConfManager::appConfFileRWLock.UnLock();
                	return -1;
		}
	}
	
	DeleteExpiredConfFile(fileSavePath, newFileName, usingFileName);
	string content = config.configfilecontent();
        string fileNameWithPath = Common::GetAbsolutePathFileName(fileSavePath, newFileName);
        if(!Common::SaveToFile(fileNameWithPath, content))
        {
                string errMsg = "fail to save file";
                SV_ERROR("%s", errMsg.c_str());
                response.set_status(CommonResponse::FAILED);
                response.set_reason(errMsg);
                ConfManager::appConfFileRWLock.UnLock();
                return -1;
        }

	string updateNotifyScript = config.updatenotifyscript();
	string serverPath = config.serverpath();
	int id = config.uniqueid();
	int no = config.configfileno();

	SV_LOG("new file name : %s", newFileName.c_str());
        SV_LOG("view conf script :%s", viewConfScript.c_str());
        SV_LOG("fileSavePath :%s", fileSavePath.c_str());
	SV_LOG("updateNotifyScript : %s", updateNotifyScript.c_str());
	SV_LOG("serverPath : %s", serverPath.c_str());
	SV_LOG("id = %d", id);
	SV_LOG("no = %d", no);
        SV_LOG("%s", config.configfilecontent().c_str());
        SV_LOG("\n");
	ConfManager::agentConfFileRWLock.UnLock();
	return 0;
}


int AppConfFile::DownloadFile(ConfigData &config, ConfigUpdateResponse &response)
{
	string newFileName = config.configfilename();
	string viewConfScript = config.viewconfscript();
	
	SV_LOG("new file name : %s", newFileName.c_str());
	SV_LOG("view conf script :%s", viewConfScript.c_str());
	SV_LOG("%s", config.configfilecontent().c_str());
	SV_LOG("\n");
	return 0;
}










