// Simple example of a lua function returning a table

#include <iostream>
#include <memory>
#include <luacppinterface.h>

int main()
{
	Lua lua;
	auto global = lua.GetGlobalEnvironment();
	
	lua.RunScript(
		"function makeNewCar()\n"
		"	return {type = 'toyota'}\n"
		"end"
	);
	
	auto makeNewCar = global.Get< LuaFunction<LuaTable()> >("makeNewCar");

	auto car = makeNewCar.Invoke();
	
	return car.Get<std::string>("type").compare("toyota");
}
