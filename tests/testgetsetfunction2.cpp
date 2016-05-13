// Simple example of putting a function in C++ and taking it back out

#include <iostream>
#include <memory>
#include <luacppinterface.h>

int main()
{
	Lua lua;
	auto global = lua.GetGlobalEnvironment();
	
	auto addTwo = lua.CreateFunction< int(int) >(
		[](int a) -> int
		{
			return a + 2;
		}
	);
	global.Set("addTwo", addTwo);

	auto insideAddTwo = global.Get< LuaFunction<int(int)> >("addTwo");

	std::cout << insideAddTwo.Invoke(5) << std::endl;
	std::cout << addTwo.Invoke(15) << std::endl;
	
	
	return insideAddTwo.Invoke(5) != 7 || addTwo.Invoke(15) != 17;
}
