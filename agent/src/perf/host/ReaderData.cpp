/**********************************************************
 * File: ReaderData.cpp
 * Function: 
 *********************************************************/
#include "ReaderData.h"

#include "XmlUtils.h"
#include "ScriptAction.h"






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

    if (xml.ParseFile("agent_apps.xml") < 0)
    {
        return;
    }

    nodeRoot = xml.GetRootNode();
    if (nodeRoot.CheckNodeIsNULL())
    {
        return;
    }

    if (nodeRoot.GetNodeName() == "config")
    {
        nodeLv1 = nodeRoot.GetChildren();
        if (nodeLv1.CheckNodeIsNULL())
        {
            return;
        }

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
    string fileName;
    CXMLUtils xml;
    CXMLElement nodeRoot;
    CXMLElement nodeLv1;

    if (pConfScript == NULL)
    {
        return;
    }

    string strConfScript(pConfScript);
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



















