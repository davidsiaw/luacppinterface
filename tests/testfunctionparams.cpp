// Simple example of how to use a lua function with parameters

#include <iostream>
#include <sstream>
#include <memory>
#include <luacppinterface.h>

int main()
{
	std::stringstream ss;

	Lua lua;
	auto global = lua.GetGlobalEnvironment();
	
	// We make a print function that writes to a string stream
	auto leprint = lua.CreateFunction<void(std::string)>(
		[&](std::string str)
		{
			ss << str;
		}
	);

	// Set the global to print
	global.Set("leprint", leprint);
	
	// Use it in a script!
	lua.RunScript("leprint 'hello'");

	return ss.str().compare("hello");
}
