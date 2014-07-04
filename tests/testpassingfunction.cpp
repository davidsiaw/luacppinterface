// Simple example of passing functions around

#include <iostream>
#include <memory>
#include <luacppinterface.h>

int main()
{
	Lua lua;
	auto global = lua.GetGlobalEnvironment();
	
	auto add = lua.CreateFunction<int(int,int)>([&](int a, int b) -> int { return a + b; });
	auto multiply = lua.CreateFunction<int(int,int)>([&](int a, int b) -> int { return a * b; });

	global.Set("add", add);
	global.Set("multiply", multiply);

	// Run the script that chooses a function to return
	lua.RunScript(
		"function subtract(a,b)\n"
		"  return a - b\n"
		"end\n"
		""
		"function returnAnOperator()\n"
		"  return subtract\n"   // this can be either add, multiply or subtract
								// change it to see what happens!
		"end\n"
	);

	auto returnAnOperator = global.Get< 
			LuaFunction< 
				LuaFunction<int(int,int)>() 
			>
		>("returnAnOperator");
	
	auto anOperator = returnAnOperator.Invoke();
	auto result = anOperator.Invoke(10,10);
	
	return result;
}
