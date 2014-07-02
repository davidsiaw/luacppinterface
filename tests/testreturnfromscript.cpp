// Simple example of a lua function returning

#include <iostream>
#include <memory>
#include <luacppinterface.h>

int main()
{
	Lua lua;
	auto global = lua.GetGlobalEnvironment();
	
	lua.RunScript(
		"function add(a,b)\n"
		"	return a+b\n"
		"end"
	);
	
	auto add = global.Get< LuaFunction<int(int,int)> >("add");

	auto num = add.Invoke(1,2);
	
	return num != 3;
}
