// Simple test for creating a variable with string and reading it as wstring

#include <iostream>
#include <memory>
#include <luacppinterface.h>

int main()
{
	Lua lua;
	lua.LoadStandardLibraries();
	auto global = lua.GetGlobalEnvironment();

	global.Set("variable", "876");

	auto variable = global.Get< std::wstring >("variable");

	return variable != L"876";
}
