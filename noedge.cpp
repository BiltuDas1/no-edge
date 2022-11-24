#include"compn.h"

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

		// Environment Variable Temp
		envr(tmp, "tmp");
		replace_all(tmp, "\\", "\\\\");

		// Check Administrator Permission
		if(!isadmin())
		{
			cout << "Error: No Administrator Permission. Program Terminated.";
			lkey = _getch();
			exit(1);
		}

		// Check if new version to replace
		ifstream file;
		file.open(tmp + "\\\\continue");
		if (file)
		{
			string ofname;
			getline(file, ofname);
			file.close();
			delf(tmp + "\\\\continue");
			delf(ofname);
		}

		// Processor Architecture
		envr(arc, "PROCESSOR_ARCHITEW6432");
		if (arc == "AMD64")
		{
			arc = "x64";
		}
		else if (arc == "IA64")
		{
			arc = "x64";
		}
		else if (arc == "x86")
		{
			arc = "x86";
		}
		else {
			cout << "Error: Unable to detect Architecture.";
			lkey = _getch();
			exit(1);
		}

		// System32 Detection
		envr(system32, "windir");
		system32 = system32 + "\\\\System32";

		// Desktop Location
		system("reg query \"HKCU\\SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Explorer\\User Shell Folders\" /v Desktop | more +2>%tmp%\\registry");
		file.open(tmp + "\\\\registry");
		getline(file, desktop);
		file.close();
		delf(tmp + "\\\\registry");
		desktop.erase(0, 32);

		// Current Directory
		cd = _getcwd(NULL, 0);

		// No Edge Conf
		envr(noedgeconf, "programdata");
		noedgeconf = noedgeconf + "////MSEDGE";

		// EDGE Directory
		system("reg query \"HKLM\\SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\App Paths\\msedge.exe\" /ve | more +2>%tmp%\\registry");
		file.open(tmp + "\\\\registry");
		getline(file, edge);
		file.close();
		delf(tmp + "\\\\registry");
		edge.erase(0, 27);
		temp_int = edge.find_last_of("\\");
		edge.erase(temp_int);
		replace_all(edge,"\\","\\\\");
		if (!fs::is_directory(edge))
		{
			cout << "Error: MS Edge is not installed. Program Terminated.";
			lkey = _getch();
			exit(1);
		}
	}
};

class checkup
{
protected:

	bool isLatest()
	{
		// Fetching Latest Version
		system(("curl --Silent --head " + durl + " | more +5 >%tmp%\\ver").c_str());
		string fil = tmp + "\\\\ver";
		ifstream file;
		file.open(fil);
		getline(file, lver);
		file.close();
		delf(fil);
		lver.erase(0, 65);
		lver=lver.substr(0, lver.find("/", 0));
		// Getting Exe Version
		system(("powershell.exe [System.Diagnostics.FileVersionInfo]::GetVersionInfo('"+exec+"').FileVersion >%tmp%\\current").c_str());
		string fil2 = tmp + "\\\\current";
		file.open(fil2);
		getline(file, ver);
		file.close();
		delf(fil);
		// Verifying Versions
		if (versionCompare(lver, ver)==1)
			return false;
		else
			return true;
	}

	void checktool(string exef, string linku)
	{
		bool iff = false;
		Sleep(2000);
		if (filef(system32 + "\\\\" + exef) || filef(cd + "\\\\" + exef))
			iff = true;
		while (!iff)
		{
			system("CLS");
			logo();
			cout << "        " << exef << " isn't found into your PC." << endl;
			cout << "        Install " << exef << " to continue running the Program..." << endl;
			system(("start " + linku).c_str());
			while (true)
			{
				Sleep(2000);
				if (filef(system32 + "\\\\" + exef) || filef(cd + "\\\\" + exef)) {
					system("CLS");
					logo();
					cout << "        " << exef << " found! Program resume...";
					Sleep(2000);
					iff = true;
					break;
				}
			}
			if (iff)
				break;
		}
	}

	bool isinternetAvailable()
	{
		string url = "http://www.google.com";
		std::wstring stemp = std::wstring(url.begin(), url.end());
		LPCWSTR sw = stemp.c_str();
		bool bConnect = InternetCheckConnection(sw, FLAG_ICC_FORCE_CONNECTION, 0);
		if (bConnect)
			return 1;
		else
			return 0;
	}

public:
	checkup()
	{
		// Internet Connection
		if(!isinternetAvailable())
		{
			cout << "        No Internet Connection. Please check your network.";
			while (!isinternetAvailable())
				Sleep(3000);
			system("CLS");
			logo();
			cout << "        Internet Connected, Program resume...";
			Sleep(3000);
		}
		
		// Checking for Updates
		system("CLS");
		logo();
		cout << "        Checking for updates..." << endl;
		Sleep(2000);
		if (!isLatest())
		{
			system("CLS");
			logo();
			cout << "        Updating Program..." << endl;
			system(("curl --Silent -L " + durl + " --Output %tmp%\\noedge_" + lver + ".exe && move /y %tmp%\\noedge_" + lver + ".exe >nul 2>nul").c_str());
			ofstream file;
			file.open(tmp + "////continue");
			file << exec;
			file.close();
			system(("start noedge_" + lver + ".exe").c_str());
			exit(0);
		}

		// Check Curl
		system("CLS");
		logo();
		cout << "        Checking Curl..." << endl;
		checktool("curl.exe", "https://github.com/BiltuDas1/no-edge#how-to-install-curl");

		// Check jq
		system("CLS");
		logo();
		cout << "        Checking jq..." << endl;
		checktool("jq.exe", "https://github.com/BiltuDas1/no-edge#how-to-install-jq");

		// Downloading database
		system("CLS");
		logo();
		cout << "        Downloading databases..." << endl;
		system("curl --Silent -H 'Cache-Control: no-cache' https://raw.githubusercontent.com/BiltuDas1/no-edge/main/info >%tmp%\\info");
	}
};

class function1 {
public:
	function1()
	{
		// License
		while(true)
		{
			license();
			cout << "                               Are you Agree with the License?[Y/N]" << endl;
			lkey = _getch();
			if (lkey == 89 || lkey == 121)
				break;
			else if (lkey == 78 || lkey == 110)
				exit(0);
			else {
				system("CLS");
				cout << "                           Error: Invalid Option, Please try again." << endl;
				Sleep(5000);
				system("CLS");
			}
		}
		system("mode 120,30 && title NO EDGE");
		
		// 
	}
};

int main(int argc, char *argv[])
{
	exec = argv[0];
	ShowConsoleCursor(false);
    system("mode 120,30");
    system("color 0a");
    system("title NO EDGE");
    startup start;
	logo();
	checkup check;
	system("CLS");
	function1 func;
}