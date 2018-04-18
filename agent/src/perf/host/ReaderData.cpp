/**********************************************************
 * File: ReaderData.cpp
 * Function: 
 *********************************************************/
#include "ReaderData.h"

#include "sv_log.h"
#include "XmlUtils.h"
#include "ScriptAction.h"




#define XML_AGENT_APPS "./agent_apps.xml"


bool CReaderData::CheckAppListEmpty()
{
    return m_listApp.empty();
}




void CReaderData::GetApps()
{
    CXMLUtils xml;
    CXMLElement nodeRoot;
    CXMLElement nodeLv1;
    CXMLElement nodeLv2;
    CXMLElement nodeLv3;

    if (xml.ParseFile(XML_AGENT_APPS) < 0)
    {
        SV_ERROR("XML ParseFile %s error.", XML_AGENT_APPS);
        return;
    }

    nodeRoot = xml.GetRootNode();
    if (nodeRoot.CheckNodeIsNULL())
    {
        SV_ERROR("XML Get root node error.");
        return;
    }

    if (nodeRoot.GetNodeName() == "config")
    {
        nodeLv1 = nodeRoot.GetChildren();
        while (nodeLv1.CheckNodeIsNULL() == false)
        {
            if (nodeLv1.GetNodeName() == "applicationConfig")
            {
                nodeLv2 = nodeLv1.GetChildren();
                while (nodeLv2.CheckNodeIsNULL() == false)
                {
                    if (nodeLv2.GetNodeName() == "row")
                    {
                        nodeLv3 = nodeLv2.GetChildren();
                        while(nodeLv3.CheckNodeIsNULL() == false)
                        {
                            if (nodeLv3.GetNodeName() == "appType")
                            {
                                m_listApp.push_back(nodeLv3.GetNodeContent());
                            }
                            nodeLv3.GetNextNode();
                        }
                    }
                    nodeLv2.GetNextNode();
                }
            }
            nodeLv1.GetNextNode();
        }
    }
}




void CReaderData::Read(string& strConfScript)
{
    string fileName;
    CXMLUtils xml;
    CXMLElement nodeRoot;
    CXMLElement nodeLv1;

    if (CScriptAction::ExecuteScript(strConfScript, fileName) < 0)
    {
        return;
    }

    if (xml.ParseFile(fileName) < 0)
    {
        return;
    }

    nodeRoot = xml.GetRootNode();
    if (nodeRoot.CheckNodeIsNULL())
    {
        return;
    }

    if (nodeRoot.GetNodeName() == "message")
    {
        nodeLv1 = nodeRoot.GetChildren();
        while (nodeLv1.CheckNodeIsNULL() == false)
        {
            m_mapSts.insert(make_pair(nodeLv1.GetNodeName(), nodeLv1.GetNodeContent()));
            nodeLv1.GetNextNode();
        }
    }
}





void CReaderData::Read(char* pConfScript)
{
    string rltScript;
    CXMLUtils xml;
    CXMLElement nodeRoot;
    CXMLElement nodeLv1;

    if (pConfScript == NULL)
    {
        SV_ERROR("Input para is null.");
        return;
    }

    string strScript(pConfScript);
    if (CScriptAction::ExecuteScript(strScript, rltScript) < 0)
    {
        SV_ERROR("ExecuteScript %s error.", strScript.c_str());
        return;
    }

    if (xml.ParseMemory(rltScript) < 0)
    {
        SV_ERROR("XML ParseMemory %s error.", rltScript.c_str());
        return;
    }

    nodeRoot = xml.GetRootNode();
    if (nodeRoot.CheckNodeIsNULL())
    {
        SV_ERROR("XML Get root node error.");
        return;
    }

    nodeLv1 = nodeRoot.GetChildren();
    while (nodeLv1.CheckNodeIsNULL() == false)
    {
        //SV_LOG("MAP: [%s=====%s]", nodeLv1.GetNodeName().c_str(), nodeLv1.GetNodeContent().c_str());
        m_mapSts.insert(make_pair(nodeLv1.GetNodeName(), nodeLv1.GetNodeContent()));
        nodeLv1.GetNextNode();
    }
}



















