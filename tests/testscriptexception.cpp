// Simple example of catching a script exception

#include <iostream>
#include <sstream>
#include <memory>
#include <luacppinterface.h>

int main()
{

	Lua lua;
	
	// Use it in a script!
	std::string result = lua.RunScript(
		"a = nil\n"
		"a.x = 5"
		);

	std::cout << result << std::endl;


	if ("Error: [string \"a = nil...\"]:2: attempt to index global 'a' (a nil value)\n" == result)
	{
		return 0;
	}

	return 1;
}
