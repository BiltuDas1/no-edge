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
#pragma comment(lib,"Wininet.lib")

using namespace std;
namespace fs = std::filesystem;

string exec, tmp, arc, tver, ver, desktop, system32, cd, noedgeconf, edge, temp_str, temp_str2, type;
string durl = "https://github.com/BiltuDas1/no-edge/releases/latest/download/noedge.exe";
int lkey, temp_int;
bool upgrade = true;

void logo()
{
    std::cout << "\n\n" << std::endl;
    std::cout << "       NNNNN        NNN         OOOOOOOOO             EEEEEEEEEEEE   DDDDDDD         GGGGGGGGGGGGG    EEEEEEEEEEEE" << std::endl;
    std::cout << "       NNNNNNN      NNN      OOOOOOOOOOOOOO           EEEEEEEEEEE    DDDDDDDDD      GGGGGGGGGGGGGGG   EEEEEEEEEEE" << std::endl;
    std::cout << "       NNN  NNN     NNN     OOOO        OOOO          EEE            DDD     DDD    GGG               EEE" << std::endl;
    std::cout << "       NNN   NNN    NNN    OOOO          OOOO         EEEEEEEEE      DDD      DDD   GGG   GGGGGGGGG   EEEEEEEEE" << std::endl;
    std::cout << "       NNN    NNN   NNN    OOO            OOO         EEEEEEEE       DDD      DDD   GGG   GGGGGGGGG   EEEEEEEE" << std::endl;
    std::cout << "       NNN     NNN  NNN    OOOO          OOOO         EEEEEEEEE      DDD      DDD   GGG         GGG   EEEEEEEEE" << std::endl;
    std::cout << "       NNN      NNN NNN     OOOO        OOOO          EEE            DDD     DDD    GGG         GGG   EEE" << std::endl;
    std::cout << "       NNN       NNNNNN      OOOOOOOOOOOOOO           EEEEEEEEEEE    DDDDDDDDD      GGGGGGGGGGGGGGG   EEEEEEEEEEE" << std::endl;
    std::cout << "       NNN        NNNNN        OOOOOOOOOO             EEEEEEEEEEEE   DDDDDDD         GGGGGGGGGGGGG    EEEEEEEEEEEE\n" << std::endl;
    std::cout << "                                                                                                 Made by BiltuDas1" << std::endl;
}

void license()
{
    system("mode 96,30");
    system("title License");
    cout << "                                NO EDGE IS SIGNED UNDER THE UNLICENSE\n";
    cout << "               This is freeand unencumbered software released into the public domain.\n\n";
    cout << "               Anyone is free to copy, modify, publish, use, compile, sell, or\n";
    cout << "               distribute this software, either in source code form or as a compiled\n";
    cout << "               binary, for any purpose, commercial or non - commercial, and by any\n";
    cout << "               means.\n\n";
    cout << "               In jurisdictions that recognize copyright laws, the author or authors\n";
    cout << "               of this software dedicate any and all copyright interest in the\n";
    cout << "               software to the public domain.We make this dedication for the benefit\n";
    cout << "               of the public at largeand to the detriment of our heirsand\n";
    cout << "               successors.We intend this dedication to be an overt act of\n";
    cout << "               relinquishment in perpetuity of all presentand future rights to this\n";
    cout << "               software under copyright law.\n\n";
    cout << "               THE SOFTWARE IS PROVIDED \"AS IS\", WITHOUT WARRANTY OF ANY KIND,\n";
    cout << "               EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF\n";
    cout << "               MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.\n";
    cout << "               IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR\n";
    cout << "               OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,\n";
    cout << "               ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR\n";
    cout << "               OTHER DEALINGS IN THE SOFTWARE.\n\n";
    cout << "                    For more information, please refer to https://unlicense.org\n\n\n" << endl;
}

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

void delf(string file)
{
    const char* fl = file.c_str();
    remove(fl);
}

void ShowConsoleCursor(bool showFlag)
{
    HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);

    CONSOLE_CURSOR_INFO     cursorInfo;

    GetConsoleCursorInfo(out, &cursorInfo);
    cursorInfo.bVisible = showFlag; // set the cursor visibility
    SetConsoleCursorInfo(out, &cursorInfo);
}

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

