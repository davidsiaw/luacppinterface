// Simple example of a native function returning

#include <iostream>
#include <memory>
#include <luacppinterface.h>

int main()
{
	Lua lua;
	auto global = lua.GetGlobalEnvironment();
	
	auto add = lua.CreateFunction<int(int,int)>([&](int a, int b) -> int { return a + b; });

	global.Set("add", add);

	// Run the script that chooses a function to return
	lua.RunScript(
		"x = add(3,5)"
	);

	auto num = global.Get<int>("x");
	
	return num != 8;
}
