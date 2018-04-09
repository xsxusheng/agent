/**********************************************************
 * File: ScriptAction.cpp
 * Function: 
 *********************************************************/
#include "ScriptAction.h"

#include <cstring>
#include <cstdarg>



int CScriptAction::ExecuteScript(char *cmd)
{
    FILE *fp = NULL;

    if (cmd == NULL)
    {
        return -1;
    }

    fp = popen(cmd, "r");
    if (fp == NULL)
    {
        return -1;
    }

    pclose(fp);
    return 0;
}



int CScriptAction::ExecuteScript(string& cmd)
{
    FILE *fp = NULL;
    const char *szCmd = NULL;

    szCmd = cmd.c_str();
    fp = popen(szCmd, "r");
    if (fp == NULL)
    {
        return -1;
    }

    pclose(fp);
    return 0;
}




int CScriptAction::ExecuteScript(string& cmd, string& rlt)
{
    char line[MAX_SCRIPT_RESULT_LEN] = {0};
    const char *szCmd = NULL;
    FILE *fp = NULL;

    szCmd = cmd.c_str();
    fp = popen(szCmd, "r");
    if (fp == NULL)
    {
        return -1;
    }

    while(fgets(line, sizeof(line)-1, fp) != NULL)
    {
        rlt.append(line);
        memset(line, 0, sizeof(line));
    }

    pclose(fp);
    return 0;
}



int CScriptAction::ExecuteShellFormat(char* pShellName, char *szFormat, ...)
{
	int actLen = 0;
	char szParam[MAX_SCRIPT_FORMAT_LEN] = {0};
	char szCommand[MAX_SCRIPT_FORMAT_LEN * 2] = {0};
    
	if (pShellName == NULL || szFormat == NULL)
	{
		return -1;
	}
	
	va_list pvList;
	va_start(pvList, szFormat); 
	actLen = vsprintf(szParam, szFormat, pvList);
	if((actLen <= 0) || (actLen >= (int)sizeof(szParam)))
	{	
		return -1;
	}
	va_end(pvList);
	
	sprintf(szCommand, "%s %s", pShellName, szParam);
	return ExecuteScript(szCommand);
}




void CScriptAction::TrimCRLF(char *pStr)
{
    int i = 0;
    int len = 0;

    if (pStr == NULL)
    {
        return;
    }

    len = strlen(pStr);
    for (i = len - 1; i >= 0; i--)
    {
        if ((pStr[i] == '\r') || (pStr[i] == '\n'))
        {
            pStr[i] = '\0';
        }
        else
        {
            break;
        }
    }
}






