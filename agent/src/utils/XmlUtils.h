/**********************************************************
 * File: XmlUtils.h
 * Function: 
 *********************************************************/
#pragma once

#include <libxml/parser.h>
#include <libxml/tree.h>

#include <queue>
#include <string>

#include "MacroDefine.h"

using namespace std;





class CXMLElement
{
public:
    CXMLElement();
    ~CXMLElement();


    xmlNodePtr GetNode(){return m_pNode;}

    CXMLElement GetChildren();
    bool CheckNodeIsNULL();
    int GetNextNode();

    string GetNodeName();
    string GetNodeContent();
    int GetNodeContentInt();


    friend class CXMLUtils;

private:
    xmlNodePtr m_pNode;

};




class CXMLUtils
{
public:
    CXMLUtils();
    ~CXMLUtils();


    int ParseFile(const char* pFileName);
    int ParseFile(string& strFileName);
    int ParseMemory(const char* pBuffer, int size);
    int ParseMemory(string& buffer);
    
    CXMLElement GetRootNode();


private:

    xmlDocPtr m_pDoc;

};




























