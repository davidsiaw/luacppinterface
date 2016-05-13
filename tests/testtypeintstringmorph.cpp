// Simple test that demonstrates type morphing from int to string

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
		variable = 1
	)");

	auto variable = global.Get< std::string >("variable");
	return variable != "1";
}
