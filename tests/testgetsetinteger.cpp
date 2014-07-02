// Simple example of getting and setting a global variable

#include <iostream>
#include <memory>
#include <luacppinterface.h>

int main()
{
	Lua lua;
	auto global = lua.GetGlobalEnvironment();
	
	global.Set("someThing", 5);
	
	return global.Get<int>("someThing") != 5;
}
