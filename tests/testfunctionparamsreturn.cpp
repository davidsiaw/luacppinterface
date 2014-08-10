// Simple example of how to use a lua function with parameters and use the return value

#include <iostream>
#include <sstream>
#include <memory>
#include <luacppinterface.h>

int main()
{
	Lua lua;
	auto global = lua.GetGlobalEnvironment();
	
	// We make a print function that writes to a string stream
	auto strangeAdd = lua.CreateFunction<int(int, int)>(
		[&](int a, int b) -> int
		{
			return a ^ b + a;
		}
	);

	// Add our function to the global state
	global.Set("strangeAdd", strangeAdd);
	
	// Use it in a script!
	lua.RunScript("x = strangeAdd (5,6)");
	
	int x = global.Get<int>("x");

	return x != (strangeAdd.Invoke(5,6)) || x != (5^5+6);
}
