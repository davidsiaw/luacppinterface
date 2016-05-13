// Simple test that shows getting a table that is not callable as a function will yield an error

#include <iostream>
#include <memory>
#include <luacppinterface.h>

int main()
{
	Lua lua;
	auto global = lua.GetGlobalEnvironment();
	
	// Write a function in Lua
	lua.RunScript(R"(
		myTable = {}
	)");

	try
	{
		auto myFunction = global.Get< LuaFunction<void()> >("myTable");
	}
	catch(LuaError e)
	{
		std::cout << e.GetMessage() << std::endl;
		return e.GetMessage() != "Error: failed to get metatable\n";
	}
	return 0;
}
