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
#include <unistd.h>  
#include <dirent.h>
#include <errno.h>


#include "sv_log.h"
#include "Common.h"


Common::Common()
{

}

Common::~Common()
{

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

	vector<string>::iterator it = files.begin();  
    for(; it != files.end(); ++it)  
    {
    	string fileName((*it));
		unsigned int n = fileName.find(head, 0);
		if(n == string::npos)
		{
			continue;
		}
		unsigned int m = fileName.find(tail, 0);
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


