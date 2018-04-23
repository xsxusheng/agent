/*************************************************************************
* File Name : AppRegisteredConfFile.cpp
* Author : xus103
* Created Time : 2018年04月03日
* Description : config process
* CopyRight : Copyright(c) 2000-2020 fiberhome
* OtherInfo :
* ModifyLog :
 ************************************************************************/
#include "../utils/sv_log.h"
#include "../utils/Common.h"
#include "../utils/AgentUtils.h"
#include "../app/App.h"
#include "ConfManager.h"
#include "AppRegisteredConfFile.h"
extern "C" {  
#include <libxml/xmlmemory.h>
#include <libxml/parser.h>  
}

AppRegisteredConfFile::AppRegisteredConfFile(){}
AppRegisteredConfFile::~AppRegisteredConfFile(){}


/***********************************************************************
 * FunctionName : Init
 * Author : xus103
 * CreateDate : 2018/03/16
 * Description : 初始化注册配置，系统启动后需要先执行初始化
 * InputParam : 
 * OutputParam :
 * Return Value : 成功返回0， 失败返回-1
 * Relation : 
 * OtherInfo : 无
 ***********************************************************************/
int AppRegisteredConfFile::Init()
{	
	list<App>* apps = NULL;

	try
	{
		int ret = ConfManager::appRegisteredConfFileRWLoc.TimeRdLock(20);
		if(0 != ret)
		{
			SV_ERROR("get lock error");
			return -1;
		}
		string path = AgentUtils::GetAgentPath();
		string filename = GetAppRegisteredConfFile(path);
		string fileNameWithPath = Common::GetAbsolutePathFileName(path, filename);
		apps = ParseConfFile(fileNameWithPath);
		if(apps != NULL)
        	{
                	//将APP注册
                	RegisterAppTable::ClearAllAppRecord();
                	list<App>::iterator iter = apps->empty() ? apps->end() : apps->begin();
                	while(iter != apps->end())
                	{
                        	if(!(*iter).GetAppType().empty())
                        	{
                                	RegisterAppTable::RegisterApp(*iter);
                        	}
                        	iter++;
                	}
        	}
	}catch(...){
		SV_LOG("AppRegisteredConfFile init error");
	}
	if(apps != NULL)
	{
       		delete apps;
		apps = NULL;
	}
	ConfManager::appRegisteredConfFileRWLoc.UnLock();

        return 0;
}



/***********************************************************************
 * FunctionName : ParseConfFile
 * Author : xus103
 * CreateDate : 2018/03/16
 * Description : 解析注册配置
 * InputParam : fileName ： 配置文件名
 * OutputParam :
 * Return Value : 成功返回app集合， 失败返回空
 * Relation : 
 * OtherInfo : 若返回的指针不为NULL, 则在外层需要delete
 ***********************************************************************/
list<App>* AppRegisteredConfFile::ParseConfFile(string &fileName)
{
	xmlDocPtr doc = NULL;
	xmlChar *value = NULL;
	xmlNodePtr node_root = NULL;
	xmlNodePtr node_level1 = NULL;
	xmlNodePtr node_level2 = NULL;
	xmlNodePtr node_level3 = NULL;
	
	if(!Common::FileExist(fileName))
	{
		return NULL;
	}

	list<App> *apps = new (std::nothrow) list<App>;
	if(apps == NULL)
	{
		return NULL;
	}

	doc = xmlParseFile(fileName.c_str());
	if(doc == NULL)
	{
		SV_ERROR("Document not parsed successfully. parse file: %s.", fileName.c_str());
		delete apps;
		return NULL;
	}
	
	node_root = xmlDocGetRootElement(doc);
	if(node_root == NULL)
	{
		SV_ERROR("empty document. parse file: %s.", fileName.c_str());
		xmlFreeDoc(doc);
		delete apps;
		return NULL;
	}	
	
	if(xmlStrcmp(node_root->name, (const xmlChar*) "config"))
	{
		SV_ERROR("document of the wrong type, roor node != config. parse file: %s.", fileName.c_str());
		xmlFreeDoc(doc);
		delete apps;
		return NULL;
	}

	node_level1 = node_root->xmlChildrenNode;
	SV_LOG("START PARSE: %s", fileName.c_str());
	while(node_level1 != NULL)
	{
		SV_LOG("applicationConfig : %s", (char *)node_level1->name);
		if(!xmlStrcmp(node_level1->name, (const xmlChar *) "applicationConfig"))
		{
			node_level2 = node_level1->xmlChildrenNode;
			while(node_level2 != NULL)
			{
				if((!xmlStrcmp(node_level2->name, (const xmlChar *) "row")))
				{
					App app;
					node_level3 = node_level2->xmlChildrenNode;
					while(node_level3 != NULL)
					{
						//SV_LOG("name = %s", (char*)node_level3->name);
						if(!xmlStrcasecmp(node_level3->name, BAD_CAST "appType"))
						{
							value = xmlNodeGetContent(node_level3);
							if(value != NULL)
							{
								string appType((char*)value);
								app.SetAppType(appType);
								xmlFree(value);
							}
						}
						else if(!xmlStrcasecmp(node_level3->name, BAD_CAST "appVersion"))
						{
							value = xmlNodeGetContent(node_level3);
							if(value != NULL)
							{
								string appVersion((char*)value);
								app.SetAppVersion(appVersion);
								xmlFree(value);
							}
						}
						node_level3 = node_level3->next;
					}
					if(!app.GetAppType().empty())
					{
						apps->push_back(app);
					}
				}
				node_level2 = node_level2->next;
			}
		}
		node_level1 = node_level1->next;
	}
	
	xmlFreeDoc(doc);
	return apps;
}



/***********************************************************************
 * FunctionName : GetAppRegisteredConfFile
 * Author : xus103
 * CreateDate : 2018/03/16
 * Description : 获取最新注册的配置文件
 * InputParam : path ： 配置文件所在的路径
 * OutputParam :
 * Return Value : 返回文件名
 * Relation : 
 * OtherInfo : 无
 ***********************************************************************/
string AppRegisteredConfFile::GetAppRegisteredConfFile(string &path)
{
	string head("agent_apps_");
	string tail(".xml");

 	if(path.empty())
 	{
		return "agent_apps.xml";
	}

	vector<string> files = Common::GetAllFiles(path);
	string alarmConfFile = Common::GetLatestFile(files, head, tail);
 	if(!alarmConfFile.empty())
	{
		return alarmConfFile;
	}

	return "agent_apps.xml";
}


/***********************************************************************
 * FunctionName : Analyse
 * Author : xus103
 * CreateDate : 2018/03/16
 * Description : 解析处理配置下发消息
 * InputParam : config ： 下发要处理的配置消息
 				response ： 处理配置消息后返回的响应
 * OutputParam :
 * Return Value : 执行成返回0， 失败返回-1
 * Relation : 
 * OtherInfo : 无
 ***********************************************************************/
int AppRegisteredConfFile::Analyse(ConfigData &config, ConfigUpdateResponse &response)
{
	
	int ret = ConfManager::appRegisteredConfFileRWLoc.TimeWrLock(20);
	if(0 != ret)
	{
		SV_ERROR("get lock error");
		return -1;
	}
	/* 文件保存路径 */
  	string fileSavePath = config.filesavepath();
  	/* 下发的新的配置文件 */
	string newFileName = config.configfilename();
   	/* 当前正在使用的配置文件 */
	string usingFileName = GetAppRegisteredConfFile(fileSavePath);

	if(!newFileName.compare(usingFileName))
	{
		string errMsg = "the same file name, newFileName:" + newFileName + ", usingFileName:" + usingFileName;
		SV_ERROR("%s", errMsg.c_str());
 		response.set_status(CommonResponse::FAILED);
		response.set_reason(errMsg);
		ConfManager::appRegisteredConfFileRWLoc.UnLock();
		return -1;
 	}

	string content = config.configfilecontent();
	string fileNameWithPath = Common::GetAbsolutePathFileName(fileSavePath, newFileName);
	if(!Common::SaveToFile(fileNameWithPath, content))
 	{
		string errMsg = "fail to save file";
		SV_ERROR("%s", errMsg.c_str());
		response.set_status(CommonResponse::FAILED);
		response.set_reason(errMsg);
		ConfManager::appRegisteredConfFileRWLoc.UnLock();

  		return -1;
	}

	string usingFileNameWithPath = Common::GetAbsolutePathFileName(fileSavePath, usingFileName);
	if(!Common::DeleteFile(usingFileNameWithPath))
	{
		SV_WARN("delete file:%s error", usingFileName.c_str());
	}
 	//SV_LOG("%s", config.configfilecontent().c_str());

	list<App> *apps = ParseConfFile(fileNameWithPath);
	if(apps == NULL)
	{	
		SV_LOG("parse app conf error");
	}
	else
	{
		//将APP注册
		RegisterAppTable::ClearAllAppRecord();
		list<App>::iterator iter = apps->empty() ? apps->end() : apps->begin();
		while(iter != apps->end())
		{
			if(!(*iter).GetAppType().empty())
			{
				RegisterAppTable::RegisterApp(*iter);
			}
			iter++;
		}

		delete apps;
	}

	
	ConfManager::appRegisteredConfFileRWLoc.UnLock();

	return 0;
}
