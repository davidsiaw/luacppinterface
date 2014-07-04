// Simple example of how to use a lua function written in a script

#include <iostream>
#include <memory>
#include <luacppinterface.h>

int main()
{
	Lua lua;
	auto global = lua.GetGlobalEnvironment();
	
	// Write a function in Lua
	lua.RunScript(
		"function addTwo(a)\n"
		"  return a+2\n"
		"end\n"
	);

	auto addTwo = global.Get< LuaFunction<int(int)> >("addTwo");
	
	return addTwo.Invoke(5) != 7;
}
