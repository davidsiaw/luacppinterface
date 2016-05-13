// Simple test that shows that a table can be a function

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
		mt = {
			__call = function ()
				return 4;
			end
		}

		myTable = {}
		setmetatable(myTable, mt)
	)");

	auto myFunction = global.Get< LuaFunction<int()> >("myTable");
	return myFunction.Invoke() != 4;
}
