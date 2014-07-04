// Simple example of getting and setting a global variable

#include <iostream>
#include <memory>
#include <luacppinterface.h>

int main()
{
	Lua lua;
	auto global = lua.GetGlobalEnvironment();
	
	global.Set("someThing", "five");
	
	return global.Get<std::string>("someThing").compare("five");
}
