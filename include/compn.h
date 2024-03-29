#include<cstdlib>
#include<conio.h>
#include<cstdio>
#include<string>
#include<ctype.h>
#include<iostream>
#include<windows.h>
#include<stdio.h>
#include<fstream>
#include<wininet.h>
#include<direct.h>
#include<filesystem>
#include<ctime>
#include"inicpp.h"
#include"WinReg.hpp"
#pragma comment(lib,"Wininet.lib")
#pragma comment(lib, "urlmon.lib")
#pragma once

using namespace std;
namespace fs = std::filesystem;

string exec, tmp, arc, tver, ver, desktop, system32, cd, noedgeconf, edge, temp_str, temp_str2, type, se;
const string durl = "https://github.com/BiltuDas1/no-edge/releases/latest/download/noedge.exe";
const string eurl = "https://github.com/BiltuDas1/no-edge/releases/latest/download/msedge.exe";
int lkey, temp_int;
bool upgrade, isFailed = true;

ifstream file;
ofstream myfile;
ini::IniFile msedge;

// Prints noedge logo
void logo()
{
    printf("\n\n\n");
    printf("       NNNNN        NNN         OOOOOOOOO             EEEEEEEEEEEE   DDDDDDD         GGGGGGGGGGGGG    EEEEEEEEEEEE\n");
    printf("       NNNNNNN      NNN      OOOOOOOOOOOOOO           EEEEEEEEEEE    DDDDDDDDD      GGGGGGGGGGGGGGG   EEEEEEEEEEE\n");
    printf("       NNN  NNN     NNN     OOOO        OOOO          EEE            DDD     DDD    GGG               EEE\n");
    printf("       NNN   NNN    NNN    OOOO          OOOO         EEEEEEEEE      DDD      DDD   GGG   GGGGGGGGG   EEEEEEEEE\n");
    printf("       NNN    NNN   NNN    OOO            OOO         EEEEEEEE       DDD      DDD   GGG   GGGGGGGGG   EEEEEEEE\n");
    printf("       NNN     NNN  NNN    OOOO          OOOO         EEEEEEEEE      DDD      DDD   GGG         GGG   EEEEEEEEE\n");
    printf("       NNN      NNN NNN     OOOO        OOOO          EEE            DDD     DDD    GGG         GGG   EEE\n");
    printf("       NNN       NNNNNN      OOOOOOOOOOOOOO           EEEEEEEEEEE    DDDDDDDDD      GGGGGGGGGGGGGGG   EEEEEEEEEEE\n");
    printf("       NNN        NNNNN        OOOOOOOOOO             EEEEEEEEEEEE   DDDDDDD         GGGGGGGGGGGGG    EEEEEEEEEEEE\n\n");
    printf("                                                                                                 Made by BiltuDas1\n");
}

// Shows license screen of noedge
void license()
{
    system("mode 96,30");
    system("title License");
    printf("                                NO EDGE IS SIGNED UNDER THE UNLICENSE\n");
    printf("               This is freeand unencumbered software released into the public domain.\n\n");
    printf("               Anyone is free to copy, modify, publish, use, compile, sell, or\n");
    printf("               distribute this software, either in source code form or as a compiled\n");
    printf("               binary, for any purpose, commercial or non - commercial, and by any\n");
    printf("               means.\n\n");
    printf("               In jurisdictions that recognize copyright laws, the author or authors\n");
    printf("               of this software dedicate any and all copyright interest in the\n");
    printf("               software to the public domain.We make this dedication for the benefit\n");
    printf("               of the public at largeand to the detriment of our heirsand\n");
    printf("               successors.We intend this dedication to be an overt act of\n");
    printf("               relinquishment in perpetuity of all presentand future rights to this\n");
    printf("               software under copyright law.\n\n");
    printf("               THE SOFTWARE IS PROVIDED \"AS IS\", WITHOUT WARRANTY OF ANY KIND,\n");
    printf("               EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF\n");
    printf("               MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.\n");
    printf("               IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR\n");
    printf("               OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,\n");
    printf("               ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR\n");
    printf("               OTHER DEALINGS IN THE SOFTWARE.\n\n");
    printf("                    For more information, please refer to https://unlicense.org\n\n\n\n");
}

// Replace a specific text with a text
// inside a string
void replace_all(
	std::string& s,
	std::string const& toReplace,
	std::string const& replaceWith
)
{
	std::string buf;
	std::size_t pos = 0;
	std::size_t prevPos;
	buf.reserve(s.size());

	while (true) {
		prevPos = pos;
		pos = s.find(toReplace, pos);
		if (pos == std::string::npos)
			break;
		buf.append(s, prevPos, pos - prevPos);
		buf += replaceWith;
		pos += toReplace.size();
	}

	buf.append(s, prevPos, s.size() - prevPos);
	s.swap(buf);
}

// Assign Environment variable to a variable
void envr(string &var, const char* env)
{
	char* buf = nullptr;
	size_t sz = 0;
	if (_dupenv_s(&buf, &sz, env) == 0 && buf != nullptr)
	{
		var = buf;
		free(buf);
	}
}

// Compares two versions
// Returns 1 if v2 is smaller, -1 if v1 is smaller, 0 if equal 
int versionCompare(string v1, string v2)
{
    // vnum stores each numeric 
    // part of version 
    int vnum1 = 0, vnum2 = 0;

    // loop until both string are 
    // processed 
    unsigned int i = 0, j = 0;
    while(i < v1.length()
        || j < v2.length()) {
        // storing numeric part of 
        // version 1 in vnum1 
        while (i < v1.length() && v1[i] != '.') {
            vnum1 = vnum1 * 10 + (v1[i] - '0');
            i++;
        }

        // storing numeric part of 
        // version 2 in vnum2 
        while (j < v2.length() && v2[j] != '.') {
            vnum2 = vnum2 * 10 + (v2[j] - '0');
            j++;
        }

        if (vnum1 > vnum2)
            return 1;
        if (vnum2 > vnum1)
            return -1;

        // if equal, reset variables and 
        // go for next numeric part 
        vnum1 = vnum2 = 0;
        i++;
        j++;
    }
    return 0;
}

// Delete file from hard disk
void delf(string file)
{
    const char* fl = file.c_str();
    remove(fl);
}

// Show or hide Console Cursor
void ShowConsoleCursor(bool showFlag)
{
    HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);

    CONSOLE_CURSOR_INFO     cursorInfo;

    GetConsoleCursorInfo(out, &cursorInfo);
    cursorInfo.bVisible = showFlag; // set the cursor visibility
    SetConsoleCursorInfo(out, &cursorInfo);
}

// Checks if file exist
bool filef(string f)
{
    std::ifstream file;
    file.open(f);
    if (file) {
        file.close();
        return 1;
    }
    else {
        return 0;
    }
}

// Sends a messagebox to the user
inline void failm(string a, string b, unsigned int er)
{
    wstring c = wstring(a.begin(), a.end());
    wstring d = wstring(b.begin(), b.end());
    LPCWSTR e = c.c_str();
    LPCWSTR f = d.c_str();
    MessageBox(NULL, e, f, er);
}

// Detect Architecture and returns
// true if x64, returns false if x86
bool artdet()
{
    envr(arc, "PROCESSOR_ARCHITEW6432");
    if (arc == "AMD64")
    {
        arc = "x64";
        return 1;
    }
    else if (arc == "IA64")
    {
        arc = "x64";
        return 1;
    }
    else if (arc == "x86")
    {
        arc = "x86";
        return 1;
    }
    else {
        return 0;
    }
}

// Helps to find text into string and
// returns true if found any.
bool grep(string str, string find)
{
    size_t found = str.find(find);
    if (found != string::npos)
        return 1;
    else
        return 0;
}

// Show or Hides the Current window
void WinVisible(bool val)
{
   HWND Window = GetConsoleWindow();
   if (val)
       ShowWindow(Window, SW_SHOW);
   else
       ShowWindow(Window, SW_HIDE);
}

// Converts all string to lowercase
string strlow(string eb)
{
    for (unsigned int i = 0;i < eb.length();i++)
    {
        eb[i] = tolower(eb[i]);
    }
    return eb;
}

// Converts LPWSTR to String
string lpw_s(LPWSTR a)
{
    wstring ws = a;
    return string(ws.begin(), ws.end());
}

// Converts String to LPCWSTR
LPCWSTR str_lpw(string a)
{
    wstring b(a.begin(), a.end());
    LPCWSTR k = b.c_str();
    return k;
}

// Downloads a file into PC
bool downloadf(string url, string file)
{
    wstring u = wstring(url.begin(), url.end());
    wstring f = wstring(file.begin(), file.end());
    const wchar_t* ur = u.c_str();
    const wchar_t* fi = f.c_str();
    DeleteUrlCacheEntry(ur);
    if (S_OK == URLDownloadToFile(NULL, ur, fi, 0, NULL))
        return true;
    else
        return false;
}

// Converts Wstring to string
string ws2s(const wstring& wstr)
{
    string str;
    size_t size;
    str.resize(wstr.length());
    wcstombs_s(&size, &str[0], str.size() + 1, wstr.c_str(), wstr.size());
    return str;
}