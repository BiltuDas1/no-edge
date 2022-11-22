#include<iostream>
#include<cstdlib>
#include<conio.h>
#include<cstdio>
#include<fstream>
#include<string>
#include<ctype.h>
// User Defined Header File
#include"compn.h"
using namespace std;

int lkey;

class startup
{
protected:
	bool isadmin(void)
	{
		bool a = false;
		string fil=tmp + "\\\\error.log";
		system("net.exe session>nul 2>%tmp%\\error.log");
		ifstream inFile(fil);
		inFile.seekg(0, ios::end);
		if (inFile.tellg() == 0)
			a = true;
		delf(fil);
		return a;
	}
public:
	startup()
	{
		// Processor Architecture
		envr(arc, "PROCESSOR_ARCHITEW6432");
		if (arc == "AMD64")
			arc = "x64";
		else if (arc == "IA64")
			arc = "x64";
		else if (arc == "x86")
			arc = "x86";
		else {
			cout << "Error: Unable to detect Architecture.";
			lkey = _getch();
			exit(0);
		}
		
		// Environment Variable Temp
		envr(tmp, "tmp");
		replace_all(tmp, "\\", "\\\\");

		// Check Administrator Permission
		if(!isadmin())
		{
			cout << "Error: No Administrator Permission. Program Terminated.";
			lkey = _getch();
			exit(0);
		}

		// Desktop Location

	}
};

class checkup
{
protected:
	bool isLatest()
	{
		// Fetching Latest Version
		system("curl --Silent https://raw.githubusercontent.com/BiltuDas1/no-edge/main/ver --Output %tmp%\\ver");
		string fil = tmp + "\\\\ver",lver,ver;
		ifstream file;
		file.open(fil);
		getline(file, lver);
		file.close();
		delf(fil);
		// Getting Exe Version
		system(("powershell.exe [System.Diagnostics.FileVersionInfo]::GetVersionInfo('"+exec+"').FileVersion >%tmp%\\current").c_str());
		string fil2 = tmp + "\\\\current";
		file.open(fil2);
		getline(file, ver);
		file.close();
		delf(fil);
		// Verifying Versions
		if (versionCompare(lver, ver) == 1)
			return 1;
		else
			return 0;
	}
public:
	checkup()
	{
		// Checking for Updates
		cout << isLatest();
	}
};

int main(int argc, char *argv[])
{
	exec = argv[0];
    system("mode 120,30");
    system("color 0a");
    system("title NOEDGE");
    startup start;
    cout << "\n\n\n        NNNNN        NNN         OOOOOOOOO             EEEEEEEEEEEE   DDDDDDD         GGGGGGGGGGGGG    EEEEEEEEEEEE\n";
    cout << "        NNNNNNN      NNN      OOOOOOOOOOOOOO           EEEEEEEEEEE    DDDDDDDDD      GGGGGGGGGGGGGGG   EEEEEEEEEEE\n";
    cout << "        NNN  NNN     NNN     OOOO        OOOO          EEE            DDD     DDD    GGG               EEE\n";
    cout << "        NNN   NNN    NNN    OOOO          OOOO         EEEEEEEEE      DDD      DDD   GGG   GGGGGGGGG   EEEEEEEEE\n";
    cout << "        NNN    NNN   NNN    OOO            OOO         EEEEEEEE       DDD      DDD   GGG   GGGGGGGGG   EEEEEEEE\n";
    cout << "        NNN     NNN  NNN    OOOO          OOOO         EEEEEEEEE      DDD      DDD   GGG         GGG   EEEEEEEEE\n";
    cout << "        NNN      NNN NNN     OOOO        OOOO          EEE            DDD     DDD    GGG         GGG   EEE\n";
    cout << "        NNN       NNNNNN      OOOOOOOOOOOOOO           EEEEEEEEEEE    DDDDDDDDD      GGGGGGGGGGGGGGG   EEEEEEEEEEE\n";
    cout << "        NNN        NNNNN        OOOOOOOOOO             EEEEEEEEEEEE   DDDDDDD         GGGGGGGGGGGGG    EEEEEEEEEEEE\n\n";
    cout << "                                                                                                 Made by BiltuDas1\n";
	checkup check;
	lkey = _getch();
}