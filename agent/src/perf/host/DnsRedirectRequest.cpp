/**********************************************************
 * File: DnsRedirectRequest.cpp
 * Function: 
 *********************************************************/
#include "DnsRedirectRequest.h"

#include "sv_log.h"
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
        SV_LOG("ExecuteScript %s error.", cmd.c_str());
        return;
    }

    reqNum = CString::StrTod(rlt);
    SV_INFO("DNS_REDIRECT_REQUEST: %ld.", reqNum);
}









