#include<iostream>
#include<cstdlib>
#include<conio.h>
#include<cstdio>
#include<fstream>
#include<cstring>
#include<ctype.h>
#ifdef __x86_64
#define x86_x64 64
#else
#ifdef _M_AMD64
#define x86_x64 64
#else
#define x86_x64 32
#endif
#endif
using namespace std;
string exec,tmp;

class components
{
	public:
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
};

class startup
{
	protected:
	bool isadmin(void)
	{
		bool a=false;
		string fil=tmp + "\\\\error.log";
		system("net.exe session>nul 2>%tmp%\\error.log");
		ifstream inFile(fil);
		inFile.seekg(0, ios::end);
		if (inFile.tellg() == 0)
			a=true;
		const char* fl=fil.c_str();
		remove(fl);
		return a;
	}
	public:
	startup()
	{
		if(!isadmin())
		{
			cout << "Error: No Administrator Permission. Program Terminated.";
			_getch();
			exit(0);
		}
	}
};

int main(int argc, char *argv[])
{
	components comp;
    exec=argv[0];
	char* buf = nullptr;
	size_t sz = 0;
	if (_dupenv_s(&buf, &sz, "tmp") == 0 && buf != nullptr)
	{
		printf("EnvVarName = %s\n", buf);
		tmp = buf;
		free(buf);
	}
	comp.replace_all(tmp, "\\", "\\\\");
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
    cout << "                                                                                                 Made by BiltuDas1 ";
    _getch();
}