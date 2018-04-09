/**********************************************************
 * File: ScriptAction.h
 * Function: 
 *********************************************************/
#pragma once

#include <string>

using namespace std;




#define MAX_SCRIPT_FORMAT_LEN   256
#define MAX_SCRIPT_RESULT_LEN   256


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






































