#include"../include/compn.h"
WinVisible w = false;

class startup2
{
public:
	startup2()
	{
		// Environment Variable Temp
		envr(tmp, "tmp");
		replace_all(tmp, "\\", "\\\\");

		// Processor Architecture
		if (!artdet()) {
			failm("Error: Unable to detect Architecture.", "NoEdge Error", MB_ICONERROR);
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
		if (!filef(noedgeconf + "\\\\msedge.ini"))
		{
			failm("Error: NO Edge configuration file isn't found. Program Terminated.", "NoEdge Error", MB_ICONERROR);
			exit(1);
		}

		// EDGE Directory
		system("reg query \"HKLM\\SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\App Paths\\msedge.exe\" /ve | more +2>%tmp%\\registry");
		file.open(tmp + "\\\\registry");
		getline(file, edge);
		file.close();
		delf(tmp + "\\\\registry");
		edge.erase(0, 27);
		temp_int = (int)edge.find_last_of("\\");
		edge.erase(temp_int);
		replace_all(edge, "\\", "\\\\");
		if (!fs::is_directory(edge))
		{
			failm("Error: MS Edge is not installed. Program Terminated.", "NoEdge Error", MB_ICONERROR);
			exit(1);
		}

		// No Edge Configuration
		msedge.load(noedgeconf + "\\\\msedge.ini");
		try{
			se = "https://" + msedge["msedge.exe"]["url"].as<string>() + msedge["msedge.exe"]["parameters"].as<string>();
		}
		catch (...)
		{
			failm("Error: Incorrect configuration found into msedge.ini. Program Terminated.", "NoEdge Error", MB_ICONERROR);
			exit(1);
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

	void Default(string str)
	{
		if (grep(str, "&form="))
			str.erase(str.find("&form="));
		if (grep(str, "https://www.bing.com/search?q="))
		{
			replace_all(str, "https://www.bing.com/search?q=", "");
			replace_all(se, "$query$", str);
			str = se;
		}
		system(("explorer.exe \"" + str + "\"").c_str());
	}

	void Redirect(string str)
	{
		system(("explorer.exe \"" + str +"\"").c_str());
	}

	void Video(string str)
	{
		str.erase(0, str.find("&url=")+5);
		system(("explorer.exe \"" + urlDecode(str) +"\"").c_str());
	}

public:
	func(int* argc, char** argv)
	{
		// No Parameters
		if(*argc == 1)
			system("explorer.exe \"https://github.com/BiltuDas1\"");
		// Default Browser Parameter
		else if (grep(argv[1], "--default-search-provider"))
			exit(0);
		// Redirecting link to default browser
		else if (grep(argv[1], "--edge-redirect"))
		{
			temp_str = argv[2];
			// Decoding Url
			if (grep(temp_str, "microsoft-edge:?url="))
			{
				temp_str.erase(0, 20);
				temp_str = urlDecode(temp_str);
			}
			else
			{
				temp_str.erase(0, 15);
			}

			if (grep(temp_str, "https://www.bing.com/WS/redirect/"))
				Redirect(temp_str);
			else if (grep(temp_str, "Microsoft.Windows.Cortana_cw5n1h2txyewy"))
				Video(temp_str);
			else
				Default(temp_str);
		}
		else
		{
			w = WinVisible(true);
			failm("Error: Unknown Parameter","Error", MB_ICONERROR);
			for (int i = 0; i < *argc; i++)
				cout << argv[i] << endl;
			lkey = _getch();
		}
	}
};

int main(int argc, char** argv)
{
	system("title Microsoft Edge debug screen");
	startup2 start;
	func f(&argc, argv);
	return 0;
}