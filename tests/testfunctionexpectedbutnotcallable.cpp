// Simple demonstration that you will get an error if you try an extract a function from a non-callable object

#include <iostream>
#include <memory>
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
		x = {}
		setmetatable(x, {})
	)");

	try
	{
		global.Get< LuaFunction<int()> >("x");
		return 1;
	}
	catch(LuaError e)
	{
		std::cout << e.GetMessage() << std::endl;		
		return e.GetMessage() != "Error: function or callable object expected, got table\nError: bad argument #-1 (function or callable object expected, got table)\n";
	}

	return 2;
}
