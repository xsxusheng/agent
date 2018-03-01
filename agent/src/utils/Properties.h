#include <iostream>
#include <string>
#include <map>
using namespace std;

class Properties
{
public:
    Properties();
    ~Properties();
    int Load(string &pathName);
    string GetValue(string &key);
    string GetValue(const char *key);
    string GetPathName();

private:
    string m_pathName;
    map<string, string> m_props;
};
