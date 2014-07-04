// Simple example of a native function returning a table

#include <iostream>
#include <memory>
#include <luacppinterface.h>

int main()
{
	Lua lua;
	auto global = lua.GetGlobalEnvironment();
	
	auto newCar = lua.CreateFunction<LuaTable()>(
		[&]() -> LuaTable 
		{
			LuaTable table = lua.CreateTable();
			table.Set("type", "renault");
			return table;
		}
	);

	global.Set("newCar", newCar);

	// Run the script that chooses a function to return
	lua.RunScript(
		"x = newCar()['type']"
	);

	auto type = global.Get<std::string>("x");
	
	return type.compare("renault");
}
