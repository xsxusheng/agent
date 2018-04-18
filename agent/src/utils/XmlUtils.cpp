/**********************************************************
 * File: XmlUtils.cpp
 * Function: 
 *********************************************************/
#include "XmlUtils.h"
#include "sv_log.h"





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
	int nBufSize = 0;
	xmlChar *pXmlBuff = NULL;

    if (pFileName == NULL)
    {
        SV_ERROR("Input para is null.");
        return -1;
    }

    xmlKeepBlanksDefault(0);
    if ((m_pDoc = xmlParseFile(pFileName)) == NULL)
    {
        SV_ERROR("xmlParseFile %s error.", pFileName);
        return -1;
    }

    /*xmlDocDumpFormatMemory(m_pDoc, &pXmlBuff, &nBufSize, 1);
    if (pXmlBuff != NULL)
    {
        //SV_LOG("XML: [%s]", (char *)pXmlBuff);
        xmlFree(pXmlBuff);
        pXmlBuff = NULL;
    }*/

    return 0;
}



int CXMLUtils::ParseFile(string& strFileName)
{
    if (ParseFile(strFileName.c_str()) < 0)
    {
        SV_ERROR("ParseFile %s error.", strFileName.c_str());
        return -1;
    }
    
    return 0;
}



int CXMLUtils::ParseMemory(const char* pBuffer, int size)
{
    if (pBuffer == NULL || size <= 0)
    {
        SV_ERROR("Input para error(%d).", size);
        return -1;
    }

    xmlKeepBlanksDefault(0);
    if ((m_pDoc = xmlParseMemory(pBuffer, size)) == NULL)
    {
        SV_ERROR("xmlParseMemory %s error.", pBuffer);
        return -1;
    }

    return 0;
}



int CXMLUtils::ParseMemory(string& buffer)
{
    if (ParseMemory(buffer.c_str(), buffer.length()) < 0)
    {
        SV_ERROR("ParseMemory %s error.", buffer.c_str());
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









