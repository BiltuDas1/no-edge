#include"../include/compn.h"


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
		// Remove all after &form
		if (grep(str, "&form="))
			str.erase(str.find("&form="));
		if (grep(str, "https://www.bing.com/search?q="))
		{
			// Deleting bing from url
			replace_all(str, "https://www.bing.com/search?q=", "");
			if (grep(str, "&filters"))
			{
				str.erase(0, str.find("&filters") + 8);
				str.erase(0, str.find("%22") + 3);
				str.erase(str.find("%22"));
			}
			replace_all(se, "$query$", str);
			str = se;
		}
		ShellExecuteA(NULL, "open", "rundll32.exe", ("url, OpenURL " + str).c_str(), NULL, SW_SHOW);
	}
	// Function for opening direct links
	void Direct(string str)
	{
		ShellExecuteA(NULL, "open", "rundll32.exe", ("url, OpenURL " + str).c_str(), NULL, SW_SHOW);
	}

	void Video(string str)
	{
		str.erase(0, str.find("&url=")+5);
		ShellExecuteA(NULL, "open", "rundll32.exe", ("url, OpenURL " + urlDecode(str)).c_str(), NULL, SW_SHOW);
	}

public:
	func(LPWSTR lpCmdLine)
	{
		// No Parameters
		if (lpCmdLine == NULL || lpCmdLine[0] == 0)
			ShellExecuteA(NULL, "open", "rundll32.exe", "url, OpenURL https://github.com/BiltuDas1", NULL, SW_SHOW);
		// Private Browsing
		else if (grep(lpw_s(lpCmdLine), "--inprivate"))
			failm("Private Window feature is not available into this version, Check Official repo for more information", "Information", MB_ICONINFORMATION);
		// Default Browser Parameter
		else if (grep(lpw_s(lpCmdLine), "--default-search-provider"))
			exit(0);
		// Startup Window Parameter
		else if (grep(lpw_s(lpCmdLine), "--no-startup-window"))
		{
			// Accessing registry to delete HKCU\\SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run
			winreg::RegKey key;
			winreg::RegResult g = key.TryOpen(HKEY_CURRENT_USER, L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run");
			// Checks whether key is accessable or not
			if(g)
			{
				auto kvalues = key.EnumValues();
				for (const auto& v : kvalues)
				{
					// Deleting value which contains msedge.exe
					if (grep(ws2s(key.GetStringValue(v.first)), "Microsoft\\Edge\\Application\\msedge.exe"))
					{
						key.DeleteValue(v.first);
						break;
					}
				}
				key.~RegKey();
				exit(0);
			}
			else
			{
				failm("Error: Can't access Startup registry key HKCU\\SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run", "msedge.exe", MB_ICONERROR);
				exit(1);
			}
		}
		// Single Argument
		else if (grep(lpw_s(lpCmdLine), "--single-argument"))
		{
			temp_str = lpw_s(lpCmdLine);
			temp_str.erase(0, temp_str.find(" ") + 1);
			Direct(temp_str);
		}
		// Windows Jumplist
		else if (grep(lpw_s(lpCmdLine), "--win-jumplist-action"))
		{
			temp_str = lpw_s(lpCmdLine);
			temp_str.erase(0, temp_str.find(" ") + 1);
			Direct(temp_str);
		}
		// Redirecting link to default browser
		else if (grep(lpw_s(lpCmdLine), "--edge-redirect"))
		{
			temp_str = lpw_s(lpCmdLine);
			// Decoding Url
			if (grep(temp_str, "microsoft-edge:?url="))
			{
				temp_str.erase(0, temp_str.find(" ") + 21);
				temp_str = urlDecode(temp_str);
			}
			else
			{
				temp_str.erase(0, temp_str.find(" ") + 16);
			}

			if (grep(temp_str, "https://www.bing.com/WS/redirect/"))
				Direct(temp_str);
			else if (grep(temp_str, "Microsoft.Windows.Cortana_cw5n1h2txyewy"))
				Video(temp_str);
			else
				Default(temp_str);
		}
		else
			failm("Error: Unknown Parameter\n" + lpw_s(lpCmdLine), "Error", MB_ICONERROR);
	}
};

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	startup2 start;
	func f(lpCmdLine);
	return 0;
}