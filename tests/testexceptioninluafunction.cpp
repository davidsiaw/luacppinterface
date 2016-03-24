// Exception in a lua function

#include <iostream>
#include <sstream>
#include <memory>
#include <luacppinterface.h>

int main()
{
	Lua lua;
	
	auto coroutine = lua.CreateCoroutine();
	
	// Use it in a script!
	std::string result = coroutine.RunScript(
		"function blow_up()\n"
		"  meow()\n"
		"end\n"
		"blow_up()"
		);

	std::cout << result << std::endl;

	if ("No Errors" == result)
	{
		return 1;
	}

	return 0;
}
