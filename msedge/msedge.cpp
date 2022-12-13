#include"../compn.h"

class startup
{
public:
	startup()
	{
		// Environment Variable Temp
		envr(tmp, "tmp");
		replace_all(tmp, "\\", "\\\\");

		// Processor Architecture
		if (!artdet()) {
			WinVisible(true);
			failc("Error: Unable to detect Architecture.", "");
			lkey = _getch();
			exit(1);
		}

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
		if (!filef(noedgeconf + "\\\\msedge.conf"))
		{
			WinVisible(true);
			failc("Error: NO Edge configuration file isn't found. Program Terminated.", "");
			lkey = _getch();
			exit(1);
		}

		// EDGE Directory
		system("reg query \"HKLM\\SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\App Paths\\msedge.exe\" /ve | more +2>%tmp%\\registry");
		file.open(tmp + "\\\\registry");
		getline(file, edge);
		file.close();
		delf(tmp + "\\\\registry");
		edge.erase(0, 27);
		temp_int = edge.find_last_of("\\");
		edge.erase(temp_int);
		replace_all(edge, "\\", "\\\\");
		if (!fs::is_directory(edge))
		{
			WinVisible(true);
			failc("Error: MS Edge is not installed. Program Terminated.", "");
			lkey = _getch();
			exit(1);
		}

		// No Edge Configuration
		file.open(noedgeconf + "\\\\msedge.conf");
		getline(file, se);
		se.erase(0, se.find(":")+1);
		getline(file, type);
		type.erase(0, type.find(":")+1);
		file.close();
		temp_int = stoi(type);
		switch (temp_int)
		{
		case 1:
			se = se + "/search?q=";
			break;
		case 2:
			se = se + "/?q=";
			break;
		case 3:
			se = se + "/search/?text=";
			break;
		case 4:
			se = se + "/web?query=";
			break;
		case 5:
			se = se + "/s/";
			break;
		case 6:
			se = se + "/serp?q=";
			break;
		default: exit(1);
		}
	}
};

class func
{
protected:
	string urlDecode(string& SRC) {
		string ret;
		char ch;
		unsigned int i, ii;
		for (i = 0; i < SRC.length(); i++) {
			if (SRC[i] == '%') {
				sscanf_s(SRC.substr(i + 1, 2).c_str(), "%x", &ii);
				ch = static_cast<char>(ii);
				ret += ch;
				i = i + 2;
			}
			else {
				ret += SRC[i];
			}
		}
		return (ret);
	}

	string SEngine(string str)
	{
		return str;
	}

public:
	func(int* argc, char** argv)
	{
		// No Parameters
		if(*argc == 1)
			system("explorer.exe \"https://github.com/BiltuDas1\"");
		// Default Browser Prompt
		else if (grep(argv[1], "--default-search-provider"))
			exit(0);
		// Redirecting link to default browser
		else if (grep(argv[1], "--edge-redirect"))
		{
			temp_str = argv[2];
			if (grep(temp_str, "microsoft-edge:?url="))
			{
				temp_str.erase(0, 20);
				temp_str = urlDecode(temp_str);
			}
			else
			{
				temp_str.erase(0, 15);
			}
			if(grep(temp_str, "&form="))
				temp_str.erase(temp_str.find("&form="));
			replace_all(temp_str, "www.bing.com/search?q=", se);
			if (type == "5")
				temp_str = temp_str + ".html";
			system(("explorer.exe \"" + SEngine(temp_str) + "\"").c_str());
		}
		else
		{
			WinVisible(true);
			failc("Error: Unknown Parameter","");
			for (int i = 0; i < *argc; i++)
				cout << argv[i] << endl;
			lkey = _getch();
		}
	}
};

int main(int argc, char** argv)
{
	WinVisible(false);
	startup start;
	func f(&argc, argv);
	exit(0);
}