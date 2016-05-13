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
		"function compute(a)\n"
		"  return a*2\n"
		"end\n"
	);

	auto originalCompute = global.Get< LuaFunction<int(int)> >("compute");
	
	// Write an alternative implementation
	
	auto alternativeCompute = lua.CreateFunction< int(int) >(
		[](int a) -> int
		{
			return a + 2;
		}
	);
	
	global.Set("compute", alternativeCompute);

	auto originalResult = originalCompute.Invoke(15);
	auto alternativeResult = alternativeCompute.Invoke(5);

	std::cout << "originalResult=" << originalResult << std::endl;
	std::cout << "alternativeResult=" << alternativeResult << std::endl;

	return originalResult != 30 || alternativeResult != 7;
}
