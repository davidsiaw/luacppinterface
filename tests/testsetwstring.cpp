// Simple test for creating a variable with wstring

#include <iostream>
#include <memory>
#include <luacppinterface.h>

int main()
{
	Lua lua;
	lua.LoadStandardLibraries();
	auto global = lua.GetGlobalEnvironment();

	global.Set("variable", L"346");

	auto variable = global.Get< std::string >("variable");

	return variable != "346";
}
