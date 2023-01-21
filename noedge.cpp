#include "./include/compn.h"
#include "./include/color.hpp"
#include "./include/rapidjson/document.h"
#include "./include/rapidjson/istreamwrapper.h"
#include "./include/rapidjson/writer.h"
#include "./include/rapidjson/stringbuffer.h"

using namespace rapidjson;

time_t tt;
struct tm ti;

void once();

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
	startup(bool cli)
	{

		// Environment Variable Temp
		t_temp();

		// Check Administrator Permission
		if(!isadmin())
		{
			cout << dye::red("Error: No Administrator Permission. Program Terminated.") << endl;
			if(cli){
				lkey = _getch();
			}
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
		if (!artdet()) {
			cout << dye::red("Error: Unable to detect Architecture.") << endl;
			if (cli)
			{
				lkey = _getch();
			}
			exit(1);
		}

		// Getting Exe Version
		system(("powershell.exe [System.Diagnostics.FileVersionInfo]::GetVersionInfo('" + exec + "').FileVersion >%tmp%\\current").c_str());
		file.open(tmp + "\\\\current");
		getline(file, ver);
		file.close();
		delf(tmp + "\\\\current");

		// System32 Detection
		s32();

		// Desktop Location
		desktop_loc();

		// Current Directory
		cd = fs::current_path().string();

		// No Edge Conf
		conf_noedge();

		// EDGE Directory
		edir(cli);
	}

	// User temporary directory
	static void t_temp()
	{
		envr(tmp, "tmp");
		replace_all(tmp, "\\", "\\\\");
	}

	// System32 Location
	static void s32()
	{
		envr(system32, "windir");
		system32 = system32 + "\\\\System32";
	}

	// Desktop Location
	static void desktop_loc()
	{
		winreg::RegKey key;
		winreg::RegResult g = key.TryOpen(HKEY_CURRENT_USER, L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Explorer\\User Shell Folders");
		if (g)
		{
			desktop = ws2s(key.GetStringValue(L"Desktop"));
		}
		else
		{
			cout << dye::red("Error: Unable to detect Desktop Location. Program Terminate.");
			exit(1);
		}
		key.~RegKey();
	}

	// No Edge Configuration directory
	static void conf_noedge()
	{
		envr(noedgeconf, "programdata");
		noedgeconf += "\\\\MSEDGE";
	}

	// EDGE Directory
	static void edir(bool cli)
	{
		winreg::RegKey key;
		winreg::RegResult g = key.TryOpen(HKEY_LOCAL_MACHINE, L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\App Paths\\msedge.exe");
		if (g)
		{
			edge = ws2s(key.GetStringValue(L"Path"));
		}
		else
		{
			cout << dye::red("Error: Edge is not installed. Program Terminated.") << endl;
			if (cli)
			{
				lkey = _getch();
			}
			exit(1);
		}
		key.~RegKey();
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
		Sleep(1000);
		while (!(filef(system32 + "\\\\" + exef) || filef(cd + "\\\\" + exef)))
		{
			system("CLS");
			logo();
			cout << "        " << dye::red(exef + " isn't found into your PC.") << hue::green << endl;
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
					break;
				}
			}
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
			cout << "        " << dye::red("No Internet Connection. Please check your network.") << hue::green << endl;
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
			downloadf("https://raw.githubusercontent.com/BiltuDas1/no-edge/main/update", tmp + "\\update");
			file.open(tmp + "\\\\update.tmp");
			if (file)
			{
				if (file.peek() == EOF)
				{
					file.close();
					delf(tmp + "\\\\update.tmp");
					system("CLS");
					logo();
					cout << "        " << dye::red("Error: Curl not working, Please reinstall curl to fix the problem.") << hue::green << endl;
					lkey = _getch();
					exit(1);
				}
				break;
			}
			else {
				system("CLS");
				logo();
				cout << "        " << dye::red("Error: Curl not working, Please reinstall curl to fix the problem.") << hue::green << endl;
				lkey = _getch();
				exit(1);
			}
		}

		// If upgradeable
		getline(file, temp_str);
		if (temp_str == "false")
			upgrade = false;
		else
			upgrade = true;
		file.close();
		delf(tmp + "\\\\update");
		try {
			msedge.load(noedgeconf + "\\\\msedge.ini");
			if (msedge["noedge.exe"]["upgradable"].as<bool>() == false)
				throw 1;
			if (msedge["noedge.exe"]["upgradable"].as<bool>() == false)
				upgrade = true;
		}
		catch (...)
		{
			upgrade = false;
		}
		try{
			temp_int = versionCompare(msedge["noedge.exe"]["version"].as<string>(), ver);
			if (temp_int == 1 || temp_int == 0 && upgrade == false)
				throw 1;
			else
				upgrade = true;
		}
		catch (...)
		{
			upgrade = false;
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
			if (downloadf(durl, cd + "\\noedge_" + tver + ".exe"))
			{
				myfile.open(tmp + "////continue");
				myfile << exec;
				myfile.close();
				WinVisible(false);
				if (MessageBox(NULL, L"Update Completed. Do you want to execute it now?", L"noedge.exe", MB_ICONINFORMATION + MB_YESNO) == 6)
					ShellExecuteA(NULL, "open", ("noedge_" + tver + ".exe").c_str(), NULL, NULL, SW_SHOW);
			}
			else
			{
				cout << dye::red("        Updating Failed. Please restart application and try again.") << endl;
				Sleep(5000);
			}
			exit(0);
		}

		// Downloading database
		system("CLS");
		logo();
		cout << "        Downloading databases..." << endl;
		downloadf("https://raw.githubusercontent.com/BiltuDas1/no-edge/main/search.json", tmp + "\\search.json");
		system("CLS");
	}
};

class function1 {
protected:
	void new_install()
	{
		system("taskkill /im msedge.exe /f >nul 2>nul");
		fs::current_path(edge);
		system("takeown /A /F msedge.exe 2>nul >nul");
		fs::current_path("../..");

		if (!fs::exists("Recovery"))
		{
			fs::create_directory("Recovery");
		}
		else
		{
			if (!fs::is_directory("Recovery"))
			{
				cout << dye::red("Error: Recovery path is obfuscate.");
				lkey = _getch();
				exit(1);
			}
		}


		// Creating 'noedge-recovery'
		tt = time(NULL);   // get time now
		localtime_s(&ti, &tt);
		string* tp = new string(to_string(ti.tm_mday) + '-' + to_string(ti.tm_mon + 1) + '-' + to_string(ti.tm_year + 1900) + " " + to_string(ti.tm_hour) + "." + to_string(ti.tm_min) + "." + to_string(ti.tm_sec));
		temp_str2 = "noedge-recovery" + *tp;
		fs::create_directory("Recovery/" + temp_str2);
		delete tp;
		

		// Moving all files to 'noedge-recovery'
		if (fs::exists("Edge"))
			fs::rename("Edge", "Recovery/" + temp_str2 + "/Edge");
		if (fs::exists("EdgeCore"))
			fs::rename("EdgeCore", "Recovery/" + temp_str2 + "/EdgeCore");
		if (fs::exists("EdgeUpdate"))
			fs::rename("EdgeUpdate", "Recovery/" + temp_str2 + "/EdgeUpdate");

		// Copying 'msedge.exe' from ProgramData
		fs::create_directories("Edge/Application");
		fs::current_path(edge);
		fs::copy_file(noedgeconf + "\\\\msedge.exe", edge + "\\\\msedge.exe");
		system("takeown /f msedge.exe /A 2>nul >nul");
		system("icacls msedge.exe /inheritance:r 2>nul >nul");
		system("icacls msedge.exe /grant:r \"Administrators\":(f) 2>nul >nul");
		system("icacls msedge.exe /grant:r \"ALL RESTRICTED APP PACKAGES\":(RX) 2>nul >nul");
		system("icacls msedge.exe /grant:r \"ALL APPLICATION PACKAGES\":(RX) 2>nul >nul");
		system("icacls msedge.exe /grant:r \"Users\":(RX) 2>nul >nul");
		system("icacls msedge.exe /grant:r \"System\":(RX) 2>nul >nul");
		system("icacls msedge.exe /setowner \"NT SERVICE\\TrustedInstaller\" 2>nul >nul");
		system("icacls msedge.exe /grant:r \"Administrators\":(RX) 2>nul >nul");
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
				cout << "                           " << dye::red("Error: Invalid Option, Please try again.") << hue::green << endl;
				Sleep(5000);
				system("CLS");
			}
		}
		
		// Search Engine
		system("mode 120,30");
		system("CLS && title Configuration");

		// Storing search.json into String --START-- //
		std::ifstream ifs{ (tmp + "\\\\search.json") };
		if (!ifs.is_open())
		{
			cout << dye::red("Error: Could not open file search.json. Program Terminated.") << endl;
			lkey = _getch();
			exit(1);
		}
		IStreamWrapper isw{ ifs };
		Document doc;
		doc.ParseStream(isw);
		StringBuffer buffer;
		Writer<StringBuffer> writer{ buffer };
		doc.Accept(writer);
		const string jsonStr{ buffer.GetString() };
		// Storing search.json into String --END-- //
		doc.Parse(jsonStr.c_str());
		assert(doc.IsObject());
		assert(doc.HasMember("elements"));
		assert(doc["elements"].IsArray());

		cout << "Choose Default Search Engine" << endl;

		for (unsigned int i = 0; i < doc["elements"].Size(); i++) {
			assert(doc["elements"][i]["name"].IsString());
			cout << i + 1 << ". " << doc["elements"][i]["name"].GetString() << endl;
		}

		ShowConsoleCursor(true);
		cout << "\n\nInput: ";
		cin >> temp_int;
		cout << endl;
		ShowConsoleCursor(false);
		system("CLS");

		// msedge.ini configuration
		msedge["msedge.exe"]["name"] = doc["elements"][temp_int-1]["name"].GetString();
		msedge["msedge.exe"]["url"] = doc["elements"][temp_int - 1]["domain"].GetString();
		lkey = doc["elements"][temp_int - 1]["query"].GetInt();
		msedge["msedge.exe"]["parameters"] = doc["query"][lkey-1].GetString();
		msedge["noedge.exe"]["version"] = ver;
		msedge["noedge.exe"]["upgradable"] = false;
		msedge.save(noedgeconf + "\\\\msedge.ini");

		// upgrade\fresh installation
		if (upgrade)
		{
			cout << "Downloading msedge.exe, It may take a while...";
			fs::create_directory(noedgeconf);
			downloadf(eurl, noedgeconf + "\\msedge.exe");
			if (fs::exists(noedgeconf + "/msedge.exe"))
				cout << dye::green("Done") << endl;
			else
			{
				cout << dye::red("Failed") << endl;
				lkey = _getch();
				exit(1);
			}
			system("certutil -hashfile %programdata%\\MSEDGE\\msedge.exe SHA256>%tmp%\\sha256");
			file.open(tmp + "\\\\sha256");
			getline(file, temp_str);
			getline(file, temp_str);
			file.close();
			delf(tmp + "\\\\sha256");
			msedge.load(noedgeconf + "\\\\msedge.ini");
			msedge["msedge.exe"]["hash"] = temp_str;
			msedge.save(noedgeconf + "\\\\msedge.ini");

			// Final
			new_install();
			system("CLS");
			cout << dye::green("Operation completed successfully.") << endl;
			lkey = _getch();
		}
		else {
			msedge.load(noedgeconf + "\\\\msedge.ini");
			try{
				if (msedge["noedge.exe"]["version"].as<string>() == ver)
				{
					cout << dye::green("Success: Setting Applied Successfully.") << endl;
					lkey = _getch();
				}
				else
					throw 1;
			}
			catch(...){
				cout << dye::red("Error: Something went wrong, Please restart the application.") << hue::green << endl;
				lkey = _getch();
			}
		}
		msedge.load(noedgeconf + "\\\\msedge.ini");
		try{
			if (msedge["noedge.exe"]["offline"].as<bool>())
				exit(0);
			else
				throw 1;
		}
		catch (...) {
			delf(tmp + "\\\\search.json");
		}
	}
};

class recovery
{
public:
	recovery()
	{
		fs::current_path(edge);
		fs::current_path("../..");
		fs::current_path("Recovery");

		// Listing Files
		int* i = new int(0);
		string* invalid = new string("0");
		if (fs::is_empty("."))
		{
			cout << dye::red("No backups available") << endl;
			exit(0);
		}
		cout << hue::green << "Choose the recovery date/time from the list" << endl;
		string* pth = new string;
		bool *mse = new bool(false);
		for (const auto& entry : fs::directory_iterator("."))
		{
			*pth = entry.path().u8string();
			*i += 1;
			cout << *i << ". " << pth->substr(pth->find("recovery") + 8);
			// Checks if Valid or not
			if (fs::exists(*pth + "/Edge") && fs::exists(*pth + "/EdgeCore") && fs::exists(*pth + "/EdgeUpdate"))
			{
				cout << "\n";
			}
			// Checks If only backupping up msedge.exe
			else if (distance(fs::directory_iterator(*pth), fs::directory_iterator{}) == 1 && fs::exists(*pth + "/Edge/Application/msedge.exe") && distance(fs::directory_iterator(*pth + "/Edge/Application"), fs::directory_iterator{}) == 1)
			{
				*mse = true;
				cout << dye::yellow("(msedge.exe)") << hue::green << "\n";
			}
			else
			{
				*invalid += to_string(*i);
				cout << dye::red("(Invalid)") << hue::green << "\n";
			}
		}
		delete pth;
		cout << endl;
		cout << "Choice: ";
		cin >> temp_int;
		cout << hue::reset << endl << endl;
		if (temp_int > *i || temp_int <= 0)
		{
			cout << dye::red("Invalid choice, Please try again.");
			exit(1);
		}
		if (invalid->find(to_string(temp_int)) != string::npos)
		{
			cout << dye::red("Error: Invalid backup file(s)");
			delete i, invalid;
			exit(0);
		}

		*i = 0;
		for (const auto& entry : fs::directory_iterator("."))
		{
			if (*i+1 == temp_int)
			{
				fs::current_path(entry.path());
				break;
			}
			*i += 1;
		}
		delete i;
		int* f = new int(0);
		// Recovering EdgeCore
		cout << dye::green("Recovering EdgeCore...");
		if(fs::exists("EdgeCore"))
		{
			fs::rename("EdgeCore", "../../EdgeCore");
			if (fs::is_directory("../../EdgeCore") && !fs::is_directory("EdgeCore"))
				cout << dye::green("Done") << endl;
			else
			{
				cout << dye::red("Failed") << endl;
				*f += 1;
			}
		}
		else {
			if (*mse)
			{
				cout << dye::yellow("Skipped") << endl;
			}
			else
			{
				cout << dye::red("doesn't exist") << endl;
				*f += 1;
			}
		}
		// Recovering EdgeUpdate
		cout << dye::green("Recovering EdgeUpdate...");
		if(fs::exists("EdgeUpdate"))
		{
			fs::rename("EdgeUpdate", "../../EdgeUpdate");
			if (fs::is_directory("../../EdgeUpdate") && !fs::is_directory("EdgeUpdate"))
				cout << dye::green("Done") << endl;
			else
			{
				cout << dye::red("Failed") << endl;
				*f += 1;
			}
		}
		else {
			if (*mse)
			{
				cout << dye::yellow("Skipped") << endl;
			}
			else
			{
				cout << dye::red("doesn't exist") << endl;
				*f += 1;
			}
		}


		// Swapping Old Edge with New Edge
		cout << dye::green("Replacing Edge...");
		if(fs::exists("Edge"))
		{
			if (*mse)
			{
				fs::rename("../../Edge", "./Edge_new");
				fs::rename("./Edge", "../../Edge");
				fs::rename("./Edge_new", "./Edge"); // Renaming Edge_new to Edge
				fs::rename("../../EdgeCore", "./EdgeCore");
				fs::rename("../../EdgeUpdate", "./EdgeUpdate");
				if(fs::is_directory("Edge") && fs::is_directory("../../Edge") && fs::is_directory("EdgeCore") && fs::is_directory("EdgeUpdate"))
					cout << dye::green("Done") << endl;
				else
				{
					cout << dye::red("Failed") << endl;
					*f += 1;
				}
			}
			else
			{
				fs::rename("../../Edge", "../../Edge_bak");
				fs::rename("./Edge", "../../Edge");
				if (!fs::is_directory("./Edge") && fs::is_directory("../../Edge_bak"))
				{
					fs::rename("../../Edge_bak", "./Edge");
					cout << dye::green("Done") << endl;
				}
				else
				{
					cout << dye::red("Failed") << endl;
					*f += 1;
				}
			}
		}
		else {
			cout << dye::red("doesn't exist") << endl;
			*f += 1;
		}
		cout << endl;
		if (*f > 0)
			cout << dye::red("Error(s): ") << dye::red(*f) << endl;
		else
			cout << dye::green("Operation completed successfully");
		delete f, mse;
		exit(0);
	}
};

class debug
{
public:
	debug(const int argc, const char *argv[])
	{
		string* arg2 = new string(argv[2]);
		// Parameter --upgrade
		if (*arg2 == "--upgrade")
		{
			startup::conf_noedge();
			if (argc > 3)
			{
				string* arg3 = new string(argv[3]);
				if (*arg3 == "true" || *arg3 == "1")
				{
					msedge.load(noedgeconf + "\\\\msedge.ini");
					msedge["noedge.exe"]["upgradable"] = true;
					msedge.save(noedgeconf + "\\\\msedge.ini");
				}
				else if (*arg3 == "false" || *arg3 == "0")
				{
					msedge.load(noedgeconf + "\\\\msedge.ini");
					msedge["noedge.exe"]["upgradable"] = false;
					msedge.save(noedgeconf + "\\\\msedge.ini");
				}
				else
				{
					cout << dye::red("Invalid value passed, only bool type value supported.") << endl;
				}
				delete arg3;
			}
			else
			{
				msedge.load(noedgeconf + "\\\\msedge.ini");
				try{
					if (msedge["noedge.exe"]["upgradable"].as<bool>() == false)
						msedge["noedge.exe"]["upgradable"] = true;
					else if (msedge["noedge.exe"]["upgradable"].as<bool>() == true)
						msedge["noedge.exe"]["upgradable"] = false;
					else
						msedge["noedge.exe"]["upgradable"] = false;
				}
				catch (...) {
					msedge["noedge.exe"]["upgradable"] = true;
				}
				msedge.save(noedgeconf + "\\\\msedge.ini");
				msedge.load(noedgeconf + "\\\\msedge.ini");
				cout << dye::green("upgradable value is set to ") << dye::green(msedge["noedge.exe"]["upgradable"].as<string>()) << endl;
			}
		}
		else
		{
			cout << dye::red("Error: Unknown debug parameter") << endl;
		}
		delete arg2;
	}
};

class extra
{
public:
	extra(const int argc, const char* argv[])
	{
		// Debug parameter
		string* arg = new string(argv[1]);
		if (*arg == "--debug")
		{
			if (argc > 2)
			{
				debug* d = new debug(argc, argv);
				delete d;
			}
			else
				cout << dye::red("Error: No debug parameter") << endl;
		}
		// Help parameter
		else if (*arg == "--help")
		{
			cout << hue::green;
			cout << argv[0] << " <Parameters>\n";
			cout << "Parameters:\n";
			cout << "--help           Opens help window\n";
			cout << "--offline jsonFile=<file>\n";
			cout << "                 Run noedge in offline mode, <file> is the filepath of\n";
			cout << "                 search.json, check official repo for more information.\n";
			cout << "--online         Inverse of offline\n";
			cout << "--recovery       Restores msedge to previous state";
			cout << hue::reset << endl;
		}
		// Recovery parameter
		else if (*arg == "--recovery")
		{
			startup::t_temp();
			startup::edir(false);
			recovery* recover = new recovery;
			delete recover;
		}
		// offline parameter
		else if (*arg == "--offline")
		{
			startup::conf_noedge();
			if (argc > 2)
			{
				string* arg2 = new string(argv[2]);
				*arg2 = strlow(*arg2);
				if (grep(*arg2, "jsonfile="))
				{
					replace_all(*arg2, "jsonfile=", "");
					startup::t_temp();
					startup::conf_noedge();
					try {
						if (fs::copy_file(*arg2, tmp + "\\\\search.json", fs::copy_options::overwrite_existing))
						{
							msedge.load(noedgeconf + "\\\\msedge.ini");
							msedge["noedge.exe"]["offline"] = true;
							msedge.save(noedgeconf + "\\\\msedge.ini");
							cout << dye::green("Done. Now run noedge.exe to work it as offline.") << endl;
						}
					}
					catch (...) {
						cout << dye::red("Error: Can't copy files to temp directory") << endl;
					}
				}
				else
					cout << dye::red("Error: Json file path is not provided") << endl;
				delete arg2;
			}
			else
				cout << dye::red("Error: Json file path is not provided") << endl;
		}
		// disable offline parameter
		else if (*arg == "--online")
		{
			startup::conf_noedge();
			msedge.load(noedgeconf + "\\\\msedge.ini");
			try {
				if (msedge["noedge.exe"]["offline"].as<bool>())
				{
					msedge["noedge.exe"]["offline"] = false;
					msedge.save(noedgeconf + "\\\\msedge.ini");
					cout << dye::green("Offline mode is now turned off") << endl;
				}
				else
					throw 1;
			}
			catch (...) {
				cout << dye::green("Offline mode is already off") << endl;
			}
		}
		else
			cout << dye::red("Error: Parameter not found") << endl;
		delete arg;
	}
};


int main(const int argc, const char *argv[])
{
	exec = argv[0];
	// Main Program
	if(argc > 1)
	{
		extra *e = new extra(argc, argv);
		delete e;
		return 0;
	}
	ShowConsoleCursor(false);
    system("mode 120,30");
    system("title NO EDGE");
	once();
	return 0;
}

void once()
{
	startup* start = new startup(true);
	delete start;
	msedge.load(noedgeconf + "/msedge.ini");
	cout << hue::green;
	// No Edge main program
	logo();
	try {
		if (msedge["noedge.exe"]["offline"].as<bool>())
		{
			cout << "        Loading...";
			Sleep(3000);
		}
		else
			throw 1;
	}
	catch (...) {
		checkup* check = new checkup;
		delete check;
	}
	system("CLS");
	function1 *func = new function1;
	delete func;
}