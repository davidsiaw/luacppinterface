// Simple test to get state from object

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

	lua.RunScript(R"(
		function retfive()
			return 123
		end
	)");

	auto table = lua.CreateTable();

	{
		Lua second(table.GetState());
		auto global = second.GetGlobalEnvironment();

		return global.Get< LuaFunction<int()> >("retfive").Invoke() != 123;
	}

}
