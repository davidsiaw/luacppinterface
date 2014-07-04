// Simple example of getting and setting a function

#include <iostream>
#include <memory>
#include <luacppinterface.h>

int main()
{
	Lua lua;
	auto global = lua.GetGlobalEnvironment();
	
	// Write a function in Lua
	lua.RunScript(
		"function addTwo(a)\n"
		"  return a*2\n"
		"end\n"
	);

	auto addTwo = global.Get< LuaFunction<int(int)> >("addTwo");
	
	// Write an alternative implementation
	
	auto myAddTwo = lua.CreateFunction< int(int) >(
		[](int a) -> int
		{
			return a + 2;
		}
	);
	
	global.Set("addTwo", myAddTwo);
	
	return myAddTwo.Invoke(5) != 7;
}
