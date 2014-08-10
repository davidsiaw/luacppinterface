// Simple example of what happens with an invalid script

#include <iostream>
#include <sstream>
#include <memory>
#include <luacppinterface.h>

int main()
{
	Lua lua;
	
	// Use it in a script!
	std::string result = lua.RunScript("g % 5 lalala meow");

	if ("Error: [string \"g % 5 lalala meow\"]:1: '=' expected near '%'\n" == result)
	{
		return 0;
	}

	return 1;
}
