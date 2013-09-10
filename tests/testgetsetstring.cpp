// Simple example of getting and setting a global variable

#include <iostream>
#include <boost/tr1/memory.hpp>
#include <luacppinterface.h>

int main()
{
	Lua lua;
	auto global = lua.GetGlobalEnvironment();
	
	global.Set("someThing", "five");
	
	return global.Get<std::string>("someThing").compare("five");
}
