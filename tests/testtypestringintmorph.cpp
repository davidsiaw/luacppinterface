// Simple test that demonstrates type morphing from string to int

#include <iostream>
#include <memory>
#include <luacppinterface.h>

int main()
{
	Lua lua;
	lua.LoadStandardLibraries();
	auto global = lua.GetGlobalEnvironment();
	
	// Write a function in Lua
	lua.RunScript(R"(
		variable = '400'
	)");

	auto variable = global.Get< int >("variable");
	return variable != 400;
}
