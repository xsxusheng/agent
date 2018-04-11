/**********************************************************
 * File: ScriptAction.h
 * Function: 
 *********************************************************/
#pragma once

#include <string>

using namespace std;




#define MAX_SCRIPT_FORMAT_LEN 1024
#define MAX_SCRIPT_RESULT_LEN 1024
#define MAX_SCRIPT_CMD_LEN 1024

#define SCRIPT_CMD_TIMEOUT "timeout 30s "

class CScriptAction
{
public:
    CScriptAction();
    ~CScriptAction();


    static int ExecuteScript(char *cmd);
    static int ExecuteScript(string& cmd);
    static int ExecuteScript(string& cmd, string& rlt);
    static int ExecuteShellFormat(char* pShellName, char *szFormat, ...);


private:

    static void TrimCRLF(char *pStr);

};






































