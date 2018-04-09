/**********************************************************
 * File: DnsRedirectRequest.cpp
 * Function: 
 *********************************************************/
#include "DnsRedirectRequest.h"

#include "ScriptAction.h"
#include "StringUtils.h"





void CDnsRedirectRequest::Run()
{
    long reqNum = 0;
    string rlt("");
    string file("/opt/fonsview/NE/drs/proc/dns_statis");
    string cmd("/opt/fonsview/NE/agent/script/ucarp/dns_redirect_request.sh");

    if (CScriptAction::ExecuteScript(cmd, rlt) < 0)
    {
        return;
    }

    reqNum = CString::StrTod(rlt);
}









