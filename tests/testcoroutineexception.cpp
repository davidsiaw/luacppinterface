// Test running a script that will fail in a coroutine

#include <iostream>
#include <luacppinterface.h>

int main()
{
	Lua lua;
	auto global = lua.GetGlobalEnvironment();

	auto coroutine = lua.CreateCoroutine();

	auto result = coroutine.RunScript("meow()");

	std::cout << result << std::endl;

	if (result == "No errors")
	{
		return 1;
	}

	return 0;
}
