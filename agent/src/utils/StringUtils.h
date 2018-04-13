/**********************************************************
 * File: StringUtils.h
 * Function: 
 *********************************************************/
#pragma once

#include <string>
#include <vector>

using namespace std;



#define MAX_STRING_FMT_LEN 1024

class CString
{
public:
    CString();
    ~CString();


    static void Split(const string& s, vector<std::string>& v, const string& c);

    static long StrTol(string& str);
    static long long StrToll(string& str);
    static unsigned long StrToul(string& str);
    static unsigned long long StrToull(string& str);
    
    static double StrTod(string& str);
    static float StrTof(string& str);

    static string ToString(int val);
    static string ToString(long val);
    static string ToString(unsigned long long val);
    static string ToString(double val);

};











