/*************************************************************************
	> File Name: properties.cpp
	> Author: 
	> Mail: 
	> Created Time: 2018年02月09日 星期五 15时53分02秒
 ************************************************************************/

#include <iostream>
#include <fstream>
#include <map>
#include "Properties.h"
using namespace std;
#define LOG_WARN printf
#define LOG_ERROR printf
#define LOG_INFO printf

Properties::Properties()
{
    //SV_LOG("Properties 构造函数");
}

Properties::~Properties()
{
    //SV_LOG("Properties 析构函数");
}

/*
 * 加载配置文件
 * fileName: 配置文件路径
 */
int Properties::Load(string &fileName)
{
    fstream _file;
    string line;
    string key;
    string value;


    if(fileName.size() == 0)
    {
        LOG_INFO("%s\n", "fileName is NULL");
        return -1;
    }

    //判断文件是否存在
    _file.open(fileName.c_str(), ios::in);
    if(!_file)
    {
        //文件不存在
        LOG_ERROR("%s\n", "fileName is not exist");
        return -1;
    }
    
    this->m_props.clear();
    while(getline(_file,line))
    {
        if(line[0] == '#')
        {
            continue;
        }
        size_t n = line.find_first_of("=");
        if(n == string::npos)
        {
            continue;
        }
        key = line.substr(0, n);
        value = line.substr(n+1, line.length() - n - 1);
        this->m_props.insert(map<string, string>::value_type(key, value));
        //LOG_INFO("%s=%s\n", key.c_str(), value.c_str());
    }
    this->m_pathName = fileName;
    
    return 0;
}

string Properties::GetValue(string &key)
{
    map<string, string>::iterator iter;
    iter = this->m_props.find(key);
    if(iter != this->m_props.end())
    {
        return iter->second;
    }
    return "";
}

string Properties::GetValue(const char* key)
{
    map<string, string>::iterator iter;
    iter = this->m_props.find(key);
    if(iter != this->m_props.end())
    {
        return iter->second;
    }
    return "";
}

/*
 * 获取文件路径名
 */
string Properties::GetPathName()
{
    return this->m_pathName;
}

