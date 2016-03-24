// Test that resuming a coroutine with no script will not work

#include <iostream>
#include <luacppinterface.h>

int main()
{
	Lua lua;
	auto global = lua.GetGlobalEnvironment();

	auto coroutine = lua.CreateCoroutine();

	auto result = coroutine.Resume();

	std::cout << result << std::endl;

	if (result == "Error: attempt to call a nil value\nError: attempt to call a nil value\n")
	{
		return 0;
	}

	return 1;
}
