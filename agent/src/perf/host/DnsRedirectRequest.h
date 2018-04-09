/**********************************************************
 * File: DnsRedirectRequest.h
 * Function: 
 *********************************************************/
#pragma once

#include <cstring>
#include <string>

#include "MacroDefine.h"
#include "Timer.h"




class CDnsRedirectRequest : public CTimerBase
{
public:
    CDnsRedirectRequest(){};
    ~CDnsRedirectRequest(){};


    void Run();


};














