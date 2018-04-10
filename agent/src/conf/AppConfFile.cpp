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

string AppConfFile::GetAppConfFile(string &path, string &similarFile)
{
        if(path.empty() || similarFile.empty())
        
                return "";
       

        vector<string> files = Common::GetAllFiles(path);
        string alarmConfFile = Common::GetLatestFile(files, similarFile);
        if(!alarmConfFile.empty())
        {
                return alarmConfFile;
        }

        return "";
}


int AppConfFile::Analyse(ConfigData &config, ConfigUpdateResponse &response)
{
	int ret = ConfManager::agentConfFileRWLock.TimeRdLock(20);
	if(0 != ret)
	{	SV_LOG("get lock error");
		return -1;
	}

	/* 文件保存路径 */
	string fileSavePath = config.filesavepath();
	/* 下发的新的配置文件 */
	string newFileName = config.configfilename();
	/* 当前正在使用的配置文件 */
	string usingFileName = GetAppConfFile(fileSavePath, newFileName);
	
	string viewConfScript = config.viewconfscript();
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










