// Simple test showing getting a null string gives you an empty string

#include <iostream>
#include <luacppinterface.h>

int main()
{
	Lua lua;
	auto global = lua.GetGlobalEnvironment();

	lua.RunScript("\
		nullString = nil\
	");

	return global.Get<std::string>("nullString") != "";
}
