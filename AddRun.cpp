// AddRun.cpp : Defines the entry point for the console application.
//

#include <string>
#include <array>
#include <memory>
#include <Windows.h>
#include <vector>
#include <fstream>
#include <iostream>

using namespace std;



vector<wchar_t> to_LPCWSTR(const char* charArray)
{
	auto w_str = vector<wchar_t>(4096);
    MultiByteToWideChar(CP_ACP, 0, charArray, -1, w_str.data(), 4096);
    return w_str;
}

bool dir_does_exist(const string& dirname)
{
	DWORD ftype = GetFileAttributesA(dirname.c_str());
	if(ftype == INVALID_FILE_ATTRIBUTES)
		return false;
	if(ftype & FILE_ATTRIBUTE_DIRECTORY)
		return true;
	return false; 


}

int main()
{

	CreateDirectory(to_LPCWSTR("C:\\Program Files (x86)\\AddToRun").data(),NULL); // if it exists, nothing will happen, otherwise the directory is created
	
	cout << "Enter the name of the desired run command" << endl;
	string base_str("SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\App Paths\\");
	string new_cmd;
	getline(cin,new_cmd);

	//string bat_file(dir_base);
	string bat_location("C:\\Program\ Files\ (x86)\\AddToRun");
	bat_location.append("\\").append(new_cmd).append(".bat");

	
	ofstream bat_f(bat_location);
	
	auto run_cmd(base_str);
	run_cmd.append(new_cmd);

	// .exe is 4 chars, take away 1 more for indexing
	if(run_cmd.substr(run_cmd.length()-5,4).compare(".exe") != 0)
	{
		run_cmd.append(".exe");
	}
	HKEY key;
	DWORD dwDisp;
	auto lp_str = to_LPCWSTR(run_cmd.c_str());
	if(RegCreateKeyEx(HKEY_LOCAL_MACHINE,lp_str.data(),0,NULL,REG_OPTION_NON_VOLATILE,KEY_ALL_ACCESS,NULL,&key,NULL) != ERROR_SUCCESS)
	{
		cout << "Unable to open" << endl;
	}
	else
	{
		cout << "Enter path of executable" << endl;
		string exectuable;
		getline(cin,exectuable);

		if(exectuable[exectuable.length()-1] != '\"')
		{
			exectuable.push_back('\"');
		}
		if(exectuable[0] != '\"')
			exectuable.insert(0,"\"");

		
		bat_f << "@echo off" << endl;
		bat_f << "start \"\" " << exectuable << " ";
		cout << "Enter additional options/switches" << endl;
		string ops;
		getline(cin,ops);

		bat_f << ops << endl;
		bat_f.flush();
		bat_f.close();

		auto w_new = to_LPCWSTR(bat_location.c_str());
		if(RegSetValue(key,NULL,REG_SZ,w_new.data(),0) == ERROR_SUCCESS)
		{

			
			w_new = to_LPCWSTR(exectuable.substr(exectuable.find_last_of("\\")).c_str());
			if(RegSetValue(key,L"Path",REG_SZ,w_new.data(),0) == ERROR_SUCCESS)
			{
				cout << "Done!" << endl;
			}
		}
	}
	cout << "Enter any key to finish..." << endl;
	cin.ignore(1);
}

