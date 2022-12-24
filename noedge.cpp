#include"compn.h"

class startup
{
protected:
	bool isadmin(void)
	{
		bool a = false;
		temp_str =tmp + "\\\\error.log";
		system("net.exe session>nul 2>%tmp%\\error.log");
		ifstream inFile(temp_str);
		inFile.seekg(0, ios::end);
		if (inFile.tellg() == 0)
			a = true;
		delf(temp_str);
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
			failc("Error: No Administrator Permission. Program Terminated.","");
			lkey = _getch();
			exit(1);
		}

		// Check if new version to replace
		ifstream file;
		file.open(tmp + "\\\\continue");
		if (file)
		{
			getline(file, temp_str);
			file.close();
			delf(tmp + "\\\\continue");
			delf(temp_str);
		}

		// Processor Architecture
		if(!artdet()){
			failc("Error: Unable to detect Architecture.","");
			lkey = _getch();
			exit(1);
		}

		// Getting Exe Version
		system(("powershell.exe [System.Diagnostics.FileVersionInfo]::GetVersionInfo('" + exec + "').FileVersion >%tmp%\\current").c_str());
		temp_str = tmp + "\\\\current";
		file.open(temp_str);
		getline(file, ver);
		file.close();
		delf(temp_str);

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
		cd = fs::current_path().string();

		// No Edge Conf
		envr(noedgeconf, "programdata");
		noedgeconf = noedgeconf + "\\\\MSEDGE";

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
			failc("Error: MS Edge is not installed. Program Terminated.","");
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
		temp_str = tmp + "\\\\ver";
		ifstream file;
		file.open(temp_str);
		getline(file, tver);
		file.close();
		delf(temp_str);
		tver.erase(0, 65);
		tver.erase(tver.find("/", 0));
		// Verifying Versions
		temp_int = versionCompare(ver, tver);
		if (temp_int == 1 || temp_int == 0)
			return true;
		else
			return false;
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
			failc(exef + " isn't found into your PC.", "        ");
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
		temp_str = "http://www.google.com";
		std::wstring stemp = std::wstring(temp_str.begin(), temp_str.end());
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
			failc("No Internet Connection. Please check your network.","        ");
			while (!isinternetAvailable())
				Sleep(3000);
			system("CLS");
			logo();
			cout << "        Internet Connected, Program resume...";
			Sleep(3000);
		}

		// Check Curl
		while (true)
		{
			system("CLS");
			logo();
			cout << "        Checking Curl..." << endl;
			checktool("curl.exe", "https://github.com/BiltuDas1/no-edge#how-to-install-curl");
			system(("curl --Silent -H 'Cache-Control: no-cache' https://raw.githubusercontent.com/BiltuDas1/no-edge/main/testfile > " + tmp + "\\\\testfile").c_str());
			file.open(tmp + "\\\\testfile");
			if (file)
			{
				if (file.peek() == EOF)
				{
					file.close();
					delf(tmp + "\\\\testfile");
					system("CLS");
					logo();
					failc("Error: Curl not working, Please reinstall curl to fix the problem.","        ");
					lkey = _getch();
					exit(1);
				}
				file.close();
				break;
			}
			else {
				system("CLS");
				logo();
				failc("Error: Curl not working, Please reinstall curl to fix the problem.","        ");
				lkey = _getch();
				exit(1);
			}
		}

		// If upgradeable
		system(("curl --Silent -H 'Cache-Control: no-cache' https://raw.githubusercontent.com/BiltuDas1/no-edge/main/update > " + tmp + "\\\\update").c_str());
		file.open(tmp + "\\\\update");
		getline(file, temp_str);
		if (temp_str == "false")
			upgrade=false;
		file.close();
		delf(tmp + "\\\\update");
		file.open(noedgeconf + "\\\\msedge.conf");
		while (getline(file, temp_str))
		{
			if (temp_str.find("Generated by NoEdge", 0) != string::npos)
			{
				temp_int = versionCompare(temp_str.erase(0, 20), ver);
				if (temp_int == 1 || temp_int == 0)
				{
					upgrade = false;
					break;
				}
			}
		}
		file.close();

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
			system(("curl --Silent -L " + durl + " --Output %tmp%\\noedge_" + tver + ".exe && move /y %tmp%\\noedge_" + tver + ".exe >nul 2>nul").c_str());
			myfile.open(tmp + "////continue");
			myfile << exec;
			myfile.close();
			system(("start noedge_" + tver + ".exe").c_str());
			exit(0);
		}

		// Downloading database
		system("CLS");
		logo();
		cout << "        Downloading databases..." << endl;
		system("curl --Silent https://raw.githubusercontent.com/BiltuDas1/no-edge/main/info>\"%tmp%\\info\"");
		system("CLS");
	}
};

class function1 {
protected:
	void new_install()
	{
		system("taskkill /im msedge.exe /f >nul 2>nul");
		fs::current_path(edge);
		system("takeown /f msedge.exe /A 2>nul >nul");
		system("icacls msedge.exe /inheritance:r 2>nul >nul");
		system("icacls msedge.exe /grant:r \"Administrators\":(f) 2>nul >nul");
		delf("msedge.exe");
		fs::copy(noedgeconf + "\\\\msedge.exe", fs::current_path());
		system("takeown /f msedge.exe /A 2>nul >nul");
		system("icacls msedge.exe /inheritance:r 2>nul >nul");
		system("icacls msedge.exe /grant:r \"Administrators\":(f) 2>nul >nul");
		system("icacls msedge.exe /grant:r \"ALL RESTRICTED APP PACKAGES\":(RX) 2>nul >nul");
		system("icacls msedge.exe /grant:r \"ALL APPLICATION PACKAGES\":(RX) 2>nul >nul");
		system("icacls msedge.exe /grant:r \"Users\":(RX) 2>nul >nul");
		system("icacls msedge.exe /grant:r \"System\":(RX) 2>nul >nul");
		system("icacls msedge.exe /setowner \"NT SERVICE\\TrustedInstaller\" 2>nul >nul");
		system("icacls msedge.exe /grant:r \"Administrators\":(RX) 2>nul >nul");
		fs::current_path("..");
		fs::current_path("..");
		fs::remove_all("FakeCore");
		fs::remove_all("FakeUpdate");
		lkey = rename("Core", "FakeCore");
		lkey = rename("Update", "FakeUpdate");
	}

	void hosts()
	{
		cout << "Downloading hosts file...\n";
		srand((unsigned int)time(NULL));
		temp_int = rand();
		lkey = rename((system32 + "\\\\drivers\\\\etc\\\\hosts").c_str(), (system32 + "\\\\drivers\\\\etc\\\\hosts" + (char)temp_int).c_str());
		system(("curl --Silent https://raw.githubusercontent.com/BiltuDas1/no-edge/main/hosts >\"" + system32 + "\\\\drivers\\\\etc\\\\hosts\"").c_str());
	}
public:
	function1()
	{
		// License
		while (true)
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
				failc("Error: Invalid Option, Please try again.", "                           ");
				Sleep(5000);
				system("CLS");
			}
		}
		
		// Search Engine
		system("mode 120,30");
		system("CLS && title Configuration");
		cout << "This is the list of the Modified Edge Browsers, Choose which you want by typing the number (Example.type 1 for Bing     Version";
		cout << "\n";
		file.open(tmp + "\\\\info");
		getline(file, temp_str2);
		while (getline(file, temp_str))
			cout << temp_str << "\n";
		file.close();
		ShowConsoleCursor(true);
		cout << "\n\nInput: ";
		cin >> temp_int;
		cout << endl;
		system("CLS");

		// msedge.conf
		temp_str2.erase(temp_str2.find(to_string(temp_int)));
		int ty = 0;
		for (unsigned int i = 0; i < temp_str2.length(); i++)
		{
			if (temp_str2[i] == ';')
				ty++;
		}
		++ty;
		file.open(tmp + "\\\\info");
		for (int i = 0; i <= temp_int; i++)
			getline(file, temp_str);
		file.close();
		temp_str.erase(0, temp_str.find("(")+1);
		temp_str.erase(temp_str.find(")"));
		myfile.open(noedgeconf + "\\\\msedge.conf");
		myfile << "search-engine:" << temp_str << endl;
		myfile << "type:" << ty << endl;
		myfile << "Generated by NoEdge " << ver << endl;
		myfile.close();

		// upgrade\fresh installation
		if (upgrade)
		{
			cout << "Downloading msedge.exe, It may take a while...";
			fs::create_directory(noedgeconf);
			system("curl --Silent https://raw.githubusercontent.com/BiltuDas1/no-edge/main/msedge/msedge.exe>%programdata%\\MSEDGE\\msedge.exe");
			system("certutil -hashfile %programdata%\\MSEDGE\\msedge.exe SHA256>%programdata%\\MSEDGE\\msedge.sha256");
			file.open(noedgeconf + "\\\\msedge.sha256");
			getline(file, temp_str);
			getline(file, temp_str);
			file.close();
			myfile.open(noedgeconf + "\\\\msedge.sha256");
			myfile << temp_str << "  msedge.exe" << endl;
			myfile.close();

			// Final
			new_install();
			system("CLS");
			hosts();
			system("CLS");
			cout << "Operation completed successfully." << endl;
		}
		else {
			file.open(noedgeconf + "\\\\msedge.conf");
			while (getline(file, temp_str))
			{
				if (temp_str.find("Generated by NoEdge " + ver, 0) != string::npos)
				{
					cout << "Success: Setting Applied Successfully." << endl;
					isFailed = false;
					lkey = _getch();
					exit(0);
				}
			}
			if(isFailed)
			{
				failc("Error: Something went wrong, Please restart the application.","");
				lkey = _getch();
				exit(1);
			}
		}
		delf(tmp + "\\\\info");
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
	lkey = _getch();
	return 0;
}