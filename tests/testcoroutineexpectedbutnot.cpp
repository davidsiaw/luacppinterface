// Simple demonstration that you will get an error if you try an extract a coroutine from a table

#include <iostream>
#include <luacppinterface.h>

class Data
{
	int value;
public:
	Data(int value) : value(value) {}

	int GetValue() const { return value; }
};

int main()
{
	Lua lua;
	lua.LoadStandardLibraries();
	auto global = lua.GetGlobalEnvironment();

	lua.RunScript(R"(
		function x()
			return "meow"
		end
	)");

	try
	{
		global.Get< LuaCoroutine >("x");
		return 1;
	}
	catch(LuaError e)
	{
		std::cout << e.GetMessage() << std::endl;
		return e.GetMessage() != "Error: thread expected, got function\nError: bad argument #-1 (thread expected, got function)\n";
	}

	return 2;
}
