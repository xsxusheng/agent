/*************************************************************************s
* File Name : Common.h
* Author : xus103
* Created Time : 2018年03月01日
* Description : common  function
* CopyRight : Copyright(c) 2000-2020 fiberhome
* OtherInfo :
* ModifyLog :
 ************************************************************************/
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_map>
using namespace std;

class Common
{
public:
	Common();
	~Common();
	
	static bool FileExist(string &filename);
	static bool CreatDir(string &path);
	static string GetFileName(string &pathFileName);
	static bool CompareFile(string &path, string &filename1, string &filename2);
	static bool IsSimilaFile(string &filename1, string &filename2);
	static bool SaveToFile(string &filename, string &content);
	static string GetCompleteFileName();
	static vector<string> GetAllFiles(string &path);
	static bool AllIsNum(const string &str);
	static void Escape(string &buffer, string escape, string goal);
	static bool DeleteFile(string &fileName);
	static string GetLatestFile(vector<string> &files, string &head, string &tail);
	static string GetLatestFile(vector<string> &files, string &similarFile);
	static string GetAbsolutePathFileName(string &path, string &fileName);
	static unordered_map<string, string> XmlToMap(string &buffer);
	//static string GetAlarmMd5(Alarm alarm);
	//static String GetMD5(String message);
	//static String BytesToHex(char *bytes);
};
