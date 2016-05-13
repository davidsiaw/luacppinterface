// Simple test that demonstrates type morphing from int to wstring

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
		variable = 765
	)");

	auto variable = global.Get< std::wstring >("variable");
	return variable != L"765";
}
