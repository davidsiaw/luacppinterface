// Simple test showing getting a null table throws a lua error

#include <iostream>
#include <luacppinterface.h>

int main()
{
	Lua lua;
	auto global = lua.GetGlobalEnvironment();

	lua.RunScript("\
		nullTable = nil\
	");

	try
	{
		global.Get<LuaTable>("nullTable");
		return 1;
	}
	catch(LuaError e)
	{
		std::cout << e.GetMessage() << std::endl;
		return 0;
	}
	return 1;
}
