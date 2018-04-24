/**********************************************************
 * File: ScriptAction.cpp
 * Function: 
 *********************************************************/
#include "ScriptAction.h"

#include <cstring>
#include <cstdarg>
#include "sv_log.h"


int CScriptAction::ExecuteScript(char *cmd)
{
    int ret = 0;
    FILE *fp = NULL;
    char cmdTimeout[MAX_SCRIPT_CMD_LEN] = {0};

    if (cmd == NULL)
    {
        SV_ERROR("Input para is null.");
        return -1;
    }

    strcpy(cmdTimeout, SCRIPT_CMD_TIMEOUT);
    strncat(cmdTimeout, cmd, (MAX_SCRIPT_CMD_LEN-strlen(SCRIPT_CMD_TIMEOUT)-1));
    fp = popen(cmdTimeout, "r");
    if (fp == NULL)
    {
        SV_ERROR("Popen %s error.", cmdTimeout);
        return -1;
    }

    ret = pclose(fp);
    if (ret < 0)
    {
        SV_ERROR("Pclose %s error(%d).", cmdTimeout, errno);
        return -1;
    }
    return 0;
}



int CScriptAction::ExecuteScript(string& cmd)
{
    int ret = 0;
    FILE *fp = NULL;
    char cmdTimeout[MAX_SCRIPT_CMD_LEN] = {0};

    strcpy(cmdTimeout, SCRIPT_CMD_TIMEOUT);
    strncat(cmdTimeout, cmd.c_str(), (MAX_SCRIPT_CMD_LEN-strlen(SCRIPT_CMD_TIMEOUT)-1));
    fp = popen(cmdTimeout, "r");
    if (fp == NULL)
    {
        SV_ERROR("Popen %s error.", cmdTimeout);
        return -1;
    }

    ret = pclose(fp);
    if (ret < 0)
    {
        SV_ERROR("Pclose %s error(%d).", cmdTimeout, errno);
        return -1;
    }
    return 0;
}




int CScriptAction::ExecuteScript(string& cmd, string& rlt)
{
    int ret = 0;
    FILE *fp = NULL;
    char line[MAX_SCRIPT_RESULT_LEN] = {0};
    char cmdTimeout[MAX_SCRIPT_CMD_LEN] = {0};

    strcpy(cmdTimeout, SCRIPT_CMD_TIMEOUT);
    strncat(cmdTimeout, cmd.c_str(), (MAX_SCRIPT_CMD_LEN-strlen(SCRIPT_CMD_TIMEOUT)-1));
    fp = popen(cmdTimeout, "r");
    if (fp == NULL)
    {
        SV_ERROR("Popen %s error.", cmdTimeout);
        return -1;
    }

    while(fgets(line, sizeof(line)-1, fp) != NULL)
    {
        rlt.append(line);
        memset(line, 0, sizeof(line));
    }

    ret = pclose(fp);
    if (ret < 0)
    {
        SV_ERROR("Pclose %s error(%d).", cmdTimeout, errno);
        return -1;
    }
    return 0;
}



int CScriptAction::ExecuteShellFormat(char* pShellName, char *szFormat, ...)
{
	int actLen = 0;
	char szParam[MAX_SCRIPT_FORMAT_LEN] = {0};
	char szCommand[MAX_SCRIPT_FORMAT_LEN * 2] = {0};
    
	if (pShellName == NULL || szFormat == NULL)
	{
        SV_ERROR("Input para is null.");
		return -1;
	}
	
	va_list pvList;
	va_start(pvList, szFormat); 
	actLen = vsprintf(szParam, szFormat, pvList);
	if((actLen <= 0) || (actLen >= (int)sizeof(szParam)))
	{
        SV_ERROR("vsprintf error...");
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
        SV_ERROR("Input para is null.");
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






