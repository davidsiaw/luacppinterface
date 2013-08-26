#include <iostream>

#include "luacppinterface.h"

int main()
{
	Lua lua;
	auto global = lua.GetGlobalEnvironment();
	auto params = lua.CreateTable();
	params.SetInteger("big", 15);

	//omg<int()>::callfunc();
	//omg<int(std::string)>::callfunc();

	
	auto t = lua.CreateFunction(MAKELUAFUNC(void(int), ([&](int a)
	{
	})));

	t.Invoke(5);
	
	auto t1 = lua.CreateFunction(MAKELUAFUNC(void(std::string), [&](std::string a)
	{
	}));

	t1.Invoke("meow");

	auto t2 = lua.CreateFunction(MAKELUAFUNC(void(int,std::string), [&](int a, std::string)
	{
	}));

	t2.Invoke(5,"a");

	auto t3 = lua.CreateFunction(MAKELUAFUNC(int(int,std::string), [&](int a, std::string)->int
	{
		return 10;
	}));

	t3.Invoke(5,"a");

	auto thefunc = MAKELUAFUNC(LuaTable(LuaTable), [&](LuaTable table) -> LuaTable
	{ 
		std::cout << "momo" << std::endl;
		return table;
	});
	
	auto add2 = lua.CreateFunction(MAKELUAFUNC(int(int), [&](int a) -> int
	{
		return a + 2;
	}));

	t.Invoke(5);

	auto frunc = lua.CreateFunction(thefunc);
	global.SetFunction("thefunc", frunc);
		
	global.SetFunction("attack", lua.CreateFunction(
		MAKELUAFUNC(int(int,int) , [&](int a, int b) -> int
		{
			return a + b;
		})
	));

	global.SetFunction("add2", add2);

	lua.RunScript(
		"x = thefunc({a=add2(10)})\n"
		""
		"function meow (a) \n"
		"  a.big = a.big + x.a\n"
		"  return a\n"
		"end\n"

		"function onetwofour() \n"
		"  return 124\n"
		"end\n"
		""
		"function getmeow()\n"
		"  return meow\n"
		"end\n"
		""
		"attack(1,2)"

		);
	
	auto meow = global.GetFunction<LuaTable(LuaTable)>("meow");

	auto result = meow.Invoke(params);
	int big = result.GetInteger("big");

	auto onetwofour = global.GetFunction<int()>("onetwofour");
	int res = onetwofour.Invoke();
	
	auto getmeow = global.GetFunction< LuaFunction<LuaTable(LuaTable)>() >("getmeow");
	auto fmeow = getmeow.Invoke();
	auto fres = fmeow.Invoke(params);

	auto number = fres.GetInteger("big");

	return 0;
}
