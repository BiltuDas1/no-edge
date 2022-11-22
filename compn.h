#include<string>
#include <stdio.h>

using string = std::string;
string exec, tmp, arc;

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