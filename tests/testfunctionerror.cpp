// Test running a script that has a few functions and fails


#include <iostream>
#include <luacppinterface.h>

int main()
{
	Lua lua;
	auto global = lua.GetGlobalEnvironment();

	auto function = lua.CreateFunction< void() >([&]()
	{
		global.Set("x", 5);
		auto table = global.Get<LuaTable>("x");
		table.Set("a", 5);
	});


	auto function2 = lua.CreateFunction< void() >([&]()
	{
		global.Get< LuaFunction<void()> >("meow").Invoke();
	});


	global.Set("func", function);
	global.Set("func2", function2);

	lua.RunScript(R"(

		woof = function ()
			func2()
		end

		function meow()
			func()
		end
	)");

	try
	{
		global.Get< LuaFunction<void()> >("woof").Invoke();
		std::cout << LuaGetLastError(function.GetState().get()) << std::endl;
	}
	catch(LuaError e)
	{
		std::cout << e.GetMessage() << std::endl;
	}

	return 0;
}
