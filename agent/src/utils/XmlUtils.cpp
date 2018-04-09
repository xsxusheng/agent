/**********************************************************
 * File: XmlUtils.cpp
 * Function: 
 *********************************************************/
#include "XmlUtils.h"






CXMLElement::CXMLElement()
{
    m_pNode = NULL;
}


CXMLElement::~CXMLElement()
{
    m_pNode = NULL;
}



CXMLElement CXMLElement::GetChildren()
{
    CXMLElement element;

    if (m_pNode != NULL)
    {
        element.m_pNode = m_pNode->xmlChildrenNode;
    }

    return element;
}



bool CXMLElement::CheckNodeIsNULL()
{
    if (m_pNode == NULL)
    {
        return true;
    }

    return false;
}



string CXMLElement::GetNodeName()
{
    if (m_pNode != NULL)
    {
        return (char *)m_pNode->name;
    }
    return "";
}



string CXMLElement::GetNodeContent()
{
    string tStr("");
    xmlChar *key = NULL;

    if (m_pNode == NULL)
    {
        return "";
    }

    key = xmlNodeGetContent(m_pNode);
    if (key != NULL)
    {
        tStr = (char *)key;
        xmlFree(key);
        key = NULL;
    }

    return tStr;
}



int CXMLElement::GetNodeContentInt()
{
    int tVal = 0;
    xmlChar *key = NULL;

    if (m_pNode == NULL)
    {
        return 0;
    }

    key = xmlNodeGetContent(m_pNode);
    if (key != NULL)
    {
        tVal = atoi((char *)key);
        xmlFree(key);
        key = NULL;
    }

    return tVal;
}



int CXMLElement::GetNextNode()
{
    if (m_pNode != NULL)
    {
        m_pNode = m_pNode->next;
        return 0;
    }

    return -1;
}






#if 0
#endif




CXMLUtils::CXMLUtils()
{
    m_pDoc = NULL;
}



CXMLUtils::~CXMLUtils()
{
    if (m_pDoc != NULL)
    {
        xmlFreeDoc(m_pDoc);
    }
    m_pDoc = NULL;
}




int CXMLUtils::ParseFile(const char* pFileName)
{
    if (pFileName == NULL)
    {
        return -1;
    }

    if ((m_pDoc = xmlParseFile(pFileName)) == NULL)
    {
        return -1;
    }
    
    return 0;
}



int CXMLUtils::ParseFile(string& strFileName)
{
    if (ParseFile(strFileName.c_str()) < 0)
    {
        return -1;
    }
    
    return 0;
}



int CXMLUtils::ParseMemory(const char* pBuffer, int size)
{
    if (pBuffer == NULL || size <= 0)
    {
        return -1;
    }

    if ((m_pDoc = xmlParseMemory(pBuffer, size)) == NULL)
    {
        return -1;
    }

    return 0;
}




CXMLElement CXMLUtils::GetRootNode()
{
    CXMLElement element;

    if (m_pDoc == NULL)
    {
        return element;
    }

    /*不需要判NULL，本来就可能为NULL*/
    element.m_pNode = xmlDocGetRootElement(m_pDoc);
    return element;
}









