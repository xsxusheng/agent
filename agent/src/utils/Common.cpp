/*************************************************************************
* File Name : Common.cpp
* Author : xus103
* Created Time : 2018年03月01日
* Description : common operation function
* CopyRight : Copyright(c) 2000-2020 fiberhome
* OtherInfo :
* ModifyLog :
 ************************************************************************/
#include <cstdio>
#include <cstring>
#include <errno.h>
#include "sv_log.h"
#include "sv_log.h"
#include "Common.h"
extern "C" {
#include <unistd.h>  
#include <dirent.h>
#include <sys/stat.h>
#include <errno.h>
#include <libxml/xmlmemory.h>
#include <libxml/parser.h>
}


Common::Common()
{

}

Common::~Common()
{

}

bool Common::FileExist(string &filename)
{
	if(filename.empty())
	{
		return false;
	}
	if(!access(filename.c_str(), F_OK))
	{
		return true;
	}	
	return false;
}


bool Common::CreatDir(string &path)
{
	char curPath[1024] = {0};

	if(path.empty() || path[0] != '/')
	{
		return false;
	}

	strcpy(curPath, path.c_str());
	if(curPath[strlen(curPath)] != '/')
	{
		strcat(curPath, "/");
	}
	
	int len = strlen(curPath);
	for(int i = 1; i < len; i++)
	{
		if('/' == curPath[i])
		{
			curPath[i] = '\0';
			if(access(curPath, F_OK) != 0)
			{
				if(mkdir(curPath, 0755) == -1)
				{
					return false;
				}
			}
			curPath[i] = '/';
		}
	}

	return true;
}


/***********************************************************************
 * FunctionName : CompareFile
 * Author : xus103
 * CreateDate : 2018/04/16
 * Description : 比较两个绝对路径文件内容是否相同
 * InputParam : filename1 - 文件名
		filename2 - 文件名
 * OutputParam :
 * Return Value : 相同返回true, 不相同返回false 
 * Relation : 
 * OtherInfo : 无
 ***********************************************************************/
bool Common::CompareFile(string &path, string &filename1, string &filename2)
{
	if(path.empty() || filename1.empty() || filename2.empty())
	{
		return false;
	}
	
	filename1 = GetAbsolutePathFileName(path, filename1);
	filename2 = GetAbsolutePathFileName(path, filename2);
	if(!FileExist(filename1) || !FileExist(filename2))
	{
		return false;
	} 

	fstream file1;
	fstream file2;
	string line1;
	string line2;
	string content1;
	string content2;

	file1.open(filename1.c_str(), ios::in);
	if(!file1)
	{
		return false;
	}
	file2.open(filename2.c_str(), ios::in);
	if(!file2)
	{
		file1.close();
		return false;
	}
	
	while(getline(file1, line1))
	{
		content1.append(line1);
	}
	while(getline(file2, line2))
	{
		content2.append(line2);
	}
	file1.close();
	file2.close();
	SV_LOG("%s", content1.c_str());
	SV_LOG("%s", content2.c_str());
	if(content1.compare(content1) != 0)
	{
		return false;
	}
	
	return true;
}

/***********************************************************************
 * FunctionName : GetFileName
 * Author : xus103
 * CreateDate : 2018/03/20
 * Description : 从带路径的文件名中取出文件名
 * InputParam : pathFileName - 带路径的文件名
 * OutputParam :
 * Return Value : 返回文件名, 失败返回空 
 * Relation : 
 * OtherInfo : 无
 ***********************************************************************/
string Common::GetFileName(string &pathFileName)
{
	if(pathFileName.empty())
	{
		return "";
	}

	size_t pos = pathFileName.rfind('/', pathFileName.length());
	if(pos == string::npos)
	{
		return pathFileName;
	}
	string filename = pathFileName.substr(pos + 1, pathFileName.length());
	
	return filename;
}


/***********************************************************************
 * FunctionName : SaveToFile
 * Author : xus103
 * CreateDate : 2018/03/20
 * Description : 将string存到文件中，文件若不存在则创建，存在则删掉重写
 * InputParam : filename - 文件名
 				content - 存到文件中的内容
 * OutputParam :
 * Return Value : 执行成功返回true,失败返回false
 * Relation : 
 * OtherInfo : 无
 ***********************************************************************/
bool Common::SaveToFile(string &filename, string &content)
{	
	ofstream out;
	
	try{
		out.open(filename.c_str(), ios::out);
		if(!out.is_open())
		{
			SV_ERROR("open error");
			return false;
		}

		out.write(content.data(), content.size());
		out.close();
	}catch(...){
		return false;
	}

	return true;
}

bool Common::DeleteFile(string &fileName)
{
	if(fileName.empty())
	{
		return false;
	}

	if(!FileExist(fileName))
	{
		return false;
	}

	if(remove(fileName.c_str()) != 0)
	{
		return false;
   	}
	
    	return true;
}
vector<string> Common::GetAllFiles(string &path)
{
	vector<string> files;//存放文件名
	DIR *dir;  
    struct dirent *ptr;

	dir=opendir(path.c_str());
    if(dir == NULL)  
    {  
        SV_ERROR("Open dir error...");  
        return files;  
    }  
   
    while ((ptr=readdir(dir)) != NULL)
    {  
        if(strcmp(ptr->d_name,".")==0 || strcmp(ptr->d_name,"..")==0)  //current dir OR parrent dir  
                continue;  
        else if(ptr->d_type == 8)    //file   
        {
			files.push_back(ptr->d_name);
		}      
        else if(ptr->d_type == 10)   //link file  
            continue;  
        else if(ptr->d_type == 4)    //dir  
        {  
            //files.push_back(ptr->d_name);
            continue;
        }  
    }  
    closedir(dir); 

	return files;
}


bool Common::AllIsNum(const string &str)
{
	for (unsigned int i = 0; i < str.size(); i++)
    {
    	int tmp = (int)str[i];
      if (tmp >= 48 && tmp <= 57)         {
             continue;
         }
         else
         {
             return false;
         }
   	} 
   	return true;
}

bool Common::IsSimilaFile(string &filename1, string &filename2)
{
	SV_LOG("file1: %s, file2: %s", filename1.c_str(), filename2.c_str());
	size_t pos;
	if(filename1.empty() || filename2.empty())
	{
		return false;
	}

	pos = filename1.rfind('_', filename1.length());
	if(pos == string::npos)
        {
		return false;
        }
	SV_LOG("pos = %d, npos = %d", pos, string::npos);
	string head1 = filename1.substr(0, pos+1);

	pos = filename1.find('.', pos);
	SV_LOG("pos = %d", pos);
	if(pos == string::npos)
	{
		return false;
	}
	string tail1 = filename1.substr(pos, filename1.length());
	string time1 = filename1.substr(head1.size(), pos - head1.size());
	if(!AllIsNum(time1))
	{
		return false;
	}

	pos = filename2.rfind('_', filename2.length());
	if(pos == string::npos)
        {
		return false;
        }
	string head2 = filename2.substr(0, pos+1);

	pos = filename2.find('.', pos);
	if(pos == string::npos)
	{
		return false;
	}
	string tail2 = filename2.substr(pos, filename2.length());
	string time2 = filename2.substr(head2.size(), pos - head2.size());
	if(!AllIsNum(time2))
	{
		return false;
	}

	if(head1.compare(head2) != 0 || tail1.compare(tail2) != 0)
	{
		return false;
	}

	return true;
}


/***********************************************************************
 * FunctionName : GetLatestFile
 * Author : xus103
 * CreateDate : 2018/03/20
 * Description : 获取最新的文件并返回文件名,且该文件名的首尾串需等于指定的首尾串
 * InputParam : head - 首字符串
 				tail - 尾字符串
 * OutputParam :
 * Return Value : 找到返回文件名,未找到返回空串
 * Relation : 
 * OtherInfo : 无
 ***********************************************************************/
string Common::GetLatestFile(vector<string> &files, string &head, string &tail)
{
	string latestFile("");
	string date("0");

	if(files.empty() || head.empty() || tail.empty())
	{
		return "";
	}

	vector<string>::iterator it = files.begin();  
    	for(; it != files.end(); ++it)  
    	{
    		string fileName((*it));
		size_t n = fileName.find(head, 0);
		if(n == string::npos)
		{
			continue;
		}
		size_t m = fileName.find(tail, 0);
		if(m == string::npos || m <= n)
		{
			continue;
		}

		string tmp(fileName.substr(head.size(), m - head.size()));
		if(tmp.empty() || !AllIsNum(tmp))
		{
			continue;
		}

		if(tmp.length() < date.length())
		{
			continue;
		}
		else if(tmp.length() > date.length())
		{
			;
		}
		else if(tmp.compare(date) <= 0)
		{
			continue;
		}

		date = tmp;
		latestFile= fileName;
    	}
	
 	return latestFile;
}

/***********************************************************************
 * FunctionName : GetLatestFile
 * Author : xus103
 * CreateDate : 2018/04/09
 * Description : 获取最新的文件并返回文件名,且该文件名的首尾串需等于指定的相似文件一致
		例如: app_123456789.xml, 首串app_,尾串.xml
 * InputParam : files : 所有文件
		similarFile : 相似文件
 * OutputParam :
 * Return Value : 找到返回文件名,未找到返回空串
 * Relation :
 * OtherInfo : 无
 ***********************************************************************/
string Common::GetLatestFile(vector<string> &files, string &similarFile)
{
	size_t pos;

	if(files.empty() || similarFile.empty())
	{
		return "";
	}	

	pos = similarFile.rfind('_', similarFile.length());
	if(pos == string::npos)
        {
		return "";
        }
	string head = similarFile.substr(0,pos+1);

	pos = similarFile.find('.', pos);
	if(pos == string::npos)
	{
		return "";
	}
	string tail = similarFile.substr(pos, similarFile.length());
	SV_LOG("head : %s, tail : %s", head.c_str(), tail.c_str());
	return GetLatestFile(files, head, tail);
}

string Common::GetAbsolutePathFileName(string &path, string &fileName)
{
	string absolutePathFileName;

    	if (path[path.size() - 1] == '/')
    	{
        	absolutePathFileName = path + fileName;
    	}
    	else
    	{
        	absolutePathFileName = path + "/" + fileName;
    	}
	
    	return absolutePathFileName;
}


void Common::Escape(string &buffer, string escape, string goal)
{
	if(buffer.empty() || escape.empty())
	{
		return;
	}
	
	size_t pos = -1;
	while(true)
	{
		if((pos = buffer.find(escape)) != string::npos)
		{
			buffer.replace(pos, escape.length(), goal);
		}
		else
		{
			break;
		}
	}

	return;
}


unordered_map<string, string> Common::XmlToMap(string &buffer)
{
	unordered_map<string, string> xmlMap;
	xmlDocPtr doc = NULL;
	xmlChar *value = NULL;
	xmlNodePtr node_root = NULL;
	xmlNodePtr node_level1 = NULL;

	xmlMap.clear();
	if(buffer.empty())
	{
		return xmlMap;
	}
	Escape(buffer, "&", "&amp");


	doc = xmlParseMemory(buffer.c_str(), buffer.size());
	if(doc == NULL)
	{
		return xmlMap;
	}

	node_root = xmlDocGetRootElement(doc);
        if(node_root == NULL)
	{
		xmlFreeDoc(doc);
		return xmlMap;
	}

	node_level1 = node_root->xmlChildrenNode;
	while(node_level1 != NULL)
	{
		if(node_level1->name != NULL)
		{
			string nameStr((char*)node_level1->name);
			string valueStr("");
			value = xmlNodeGetContent(node_level1);
			if(value != NULL)
			{
				valueStr = (char*)value;
			}

			xmlMap.insert(unordered_map<string, string>::value_type(nameStr, valueStr));
		}
		
		node_level1 = node_level1->next;
	}
	
	xmlFreeDoc(doc);
	return xmlMap;
}
