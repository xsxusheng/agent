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

/***********************************************************************
 * FunctionName : Init
 * Author : xus103
 * CreateDate : 2018/03/16
 * Description : 初始化APP配置，系统启动后需要先执行初始化
 * InputParam : 
 * OutputParam :
 * Return Value : 成功返回0， 失败返回-1
 * Relation : 
 * OtherInfo : 无
 ***********************************************************************/
int AppConfFile::Init()
{
	return 0;
}



/***********************************************************************
 * FunctionName : DeleteExpiredConfFile
 * Author : xus103
 * CreateDate : 2018/04/16
 * Description : 删除过期的配置文件， 除了正在使用的配置文件
 * InputParam : path ： 配置文件所在路径
 				newFileName ： 新下发的文件
 				usingFileName ： 正在使用的文件
 * OutputParam :
 * Return Value : 无
 * Relation : 
 * OtherInfo : 无
 ***********************************************************************/
void AppConfFile::DeleteExpiredConfFile(string &path, string &newFileName, string &usingFileName)
{
	string tmp;
	if(path.empty() || newFileName.empty() || usingFileName.empty())
	{
		return;
	}

	try{
 		vector<string> files = Common::GetAllFiles(path);  
		vector<string>::iterator it;
		for(it = files.begin(); it != files.end(); it++)
		{
			string tmp = *it;
			if(!Common::IsSimilaFile(tmp, newFileName))
			{
				continue;
			}
			else if(tmp.compare(usingFileName) != 0)
			{
				string pathName = Common::GetAbsolutePathFileName(path, tmp);
				if(!Common::DeleteFile(pathName))
        		{
					SV_WARN("delete file:%s error", pathName.c_str());
					return;
				}
			}
		}
	}catch(...){
		SV_ERROR("delet expired file error");
	}	
	
	return;    
}


/***********************************************************************
 * FunctionName : Analyse
 * Author : xus103
 * CreateDate : 2018/03/16
 * Description : 解析处理配置下发消息
 * InputParam : config ： 下发要处理的配置消息
 				response ： 处理配置消息后返回的响应
 * OutputParam :
 * Return Value : 无
 * Relation : 
 * OtherInfo : 群组配置
 ***********************************************************************/
int AppConfFile::Analyse(ConfigData &config, ConfigUpdateResponse &response)
{
	AppScriptAction appScriptAction;
	string fileName = "error";

	/*int ret = ConfManager::appConfFileRWLock.TimeRdLock(20);
	if(0 != ret)
	{	SV_LOG("get lock error");
		return -1;
	}*/

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
		//ConfManager::appConfFileRWLock.UnLock();
		return -1;
	}
	
	if(!Common::FileExist(fileSavePath))
	{
		SV_LOG("%s not exist, to create", fileSavePath.c_str());
		if(!Common::CreatDir(fileSavePath))
		{
			SV_ERROR("create dir:%s error", fileSavePath.c_str());
			string errMsg = "creat dir:" + fileSavePath + " error";
			response.set_status(CommonResponse::FAILED);
			response.set_reason(errMsg);
 			//ConfManager::appConfFileRWLock.UnLock();
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
		//ConfManager::appConfFileRWLock.UnLock();
		return -1;
	}

	if(!Common::CompareFile(fileSavePath, newFileName, usingFileName))
	{
		string updateNotifyScript = config.updatenotifyscript();
		appScriptAction.NotifyAppCfgUpdate(updateNotifyScript);
		if(appScriptAction.exeStatus != AppScriptAction::SUCCESS)
		{
			//SV_WARN("notify app update cfg error!");
		}
	}

    //SV_LOG("%s", config.configfilecontent().c_str());
	//ConfManager::agentConfFileRWLock.UnLock();
	return 0;
}



/***********************************************************************
 * FunctionName : Analyse
 * Author : xus103
 * CreateDate : 2018/03/16
 * Description : 解析处理配置下发消息
 * InputParam : config ： 下发要处理的配置消息
 				response ： 处理配置消息后返回的响应
 * OutputParam :
 * Return Value : 无
 * Relation : 
 * OtherInfo : 网元自有配置
 ***********************************************************************/
int AppConfFile::DownloadFile(ConfigData &config, ConfigUpdateResponse &response)
{
	AppScriptAction appScriptAction;
	string fileName = "error";

	/*int ret = ConfManager::appConfFileRWLock.TimeRdLock(20);
	if(0 != ret)
	{	SV_LOG("get lock error");
		return -1;
	}*/

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
		//ConfManager::appConfFileRWLock.UnLock();
		return -1;
	}
	
	if(!Common::FileExist(fileSavePath))
	{
		SV_LOG("%s not exist, to create", fileSavePath.c_str());
		if(!Common::CreatDir(fileSavePath))
		{
			SV_ERROR("create dir:%s error", fileSavePath.c_str());
			string errMsg = "creat dir:" + fileSavePath + " error";
 			response.set_status(CommonResponse::FAILED);
			response.set_reason(errMsg);
			//ConfManager::appConfFileRWLock.UnLock();
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
		//ConfManager::appConfFileRWLock.UnLock();
		return -1;
	}

	if(!Common::CompareFile(fileSavePath, newFileName, usingFileName))
	{
		string updateNotifyScript = config.updatenotifyscript();
		appScriptAction.NotifyAppCfgUpdate(updateNotifyScript);
		if(appScriptAction.exeStatus != AppScriptAction::SUCCESS)
		{
			//SV_WARN("notify app update cfg error!");
		}
	}

	//SV_LOG("%s", config.configfilecontent().c_str());
	//ConfManager::agentConfFileRWLock.UnLock();
	return 0;
}










