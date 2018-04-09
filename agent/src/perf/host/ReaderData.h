/**********************************************************
 * File: ReaderData.h
 * Function: 
 *********************************************************/
#pragma once

#include <cstring>
#include <string>
#include <list>
#include <map>

#include <libxml/parser.h>
#include <libxml/tree.h>

#include "MacroDefine.h"

using namespace std;




class CReaderData
{
public:
    CReaderData(){}
    ~CReaderData(){}


    bool CheckAppListEmpty();


    void GetApps();
    void Read(string& strConfScript);
    void Read(char* pConfScript);


public:
    list<string> m_listApp;
    map<string, string> m_mapSts;

};




















