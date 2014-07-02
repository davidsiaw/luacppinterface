// Simple example of getting and setting a global variable

#include <iostream>
#include <memory>
#include <luacppinterface.h>

int main()
{
	Lua lua;
	auto global = lua.GetGlobalEnvironment();
	
	auto table = lua.CreateTable();
	table.Set("someThing", "five");
	
	global.Set("mytable", table);
	
	return global.Get<LuaTable>("mytable").Get<std::string>("someThing").compare("five");
}
