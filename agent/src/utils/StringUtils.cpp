/**********************************************************
 * File: StringUtils.cpp
 * Function: 
 *********************************************************/
#include "StringUtils.h"

#include <cstdlib>











void CString::Split(const std::string& s, std::vector<std::string>& v, const std::string& c)
{
    string::size_type pos1;
    string::size_type pos2;
    
    pos1 = 0;
    pos2 = s.find(c);
    
    while(string::npos != pos2)
    {
        v.push_back(s.substr(pos1, pos2-pos1));

        pos1 = pos2 + c.size();
        pos2 = s.find(c, pos1);
    }
    
    if(pos1 != s.length())
    {
        v.push_back(s.substr(pos1));
    }
}




long CString::StrTol(string& str)
{
    long val = 0;

    val = strtol(str.c_str(), NULL, 0);
    return val;
}




long long CString::StrToll(string& str)
{
    long long val = 0;

    val = strtoll(str.c_str(), NULL, 0);
    return val;
}




unsigned long CString::StrToul(string& str)
{
    long val = 0;

    val = strtoul(str.c_str(), NULL, 0);
    return val;
}




unsigned long long CString::StrToull(string& str)
{
    long long val = 0;

    val = strtoull(str.c_str(), NULL, 0);
    return val;
}



double CString::StrTod(string& str)
{
    double val = 0.0;

    val = strtod(str.c_str(), NULL);
    return val;
}



float CString::StrTof(string& str)
{
    float val = 0;

    val = strtof(str.c_str(), NULL);
    return val;
}





string CString::ToString(int val)
{
    char tBuf[MAX_STRING_FMT_LEN] = {0};

    snprintf(tBuf, (MAX_STRING_FMT_LEN-1), "%d", val);

    string tStr(tBuf);
    return tStr;
}



string CString::ToString(long val)
{
    char tBuf[MAX_STRING_FMT_LEN] = {0};

    snprintf(tBuf, (MAX_STRING_FMT_LEN-1), "%ld", val);

    string tStr(tBuf);
    return tStr;
}



string CString::ToString(double val)
{
    char tBuf[MAX_STRING_FMT_LEN] = {0};

    snprintf(tBuf, (MAX_STRING_FMT_LEN-1), "%f", val);

    string tStr(tBuf);
    return tStr;
}












