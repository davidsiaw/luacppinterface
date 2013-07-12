#include <iostream>

#include "luacppinterface.h"

int main()
{
	Lua lua;
	auto global = lua.GetGlobalEnvironment();
	auto params = lua.CreateTable();
	params.SetInteger("big", 15);

	auto thefunc = new std::tr1::function<LuaTable(LuaTable)>([&](LuaTable table) -> LuaTable
	{ 
		std::cout << "momo" << std::endl;
		return table;
	});

	auto frunc = lua.CreateFunction(thefunc);
	global.SetFunction("thefunc", frunc);

	lua.RunScript(
		"x = thefunc({a=10})\n"
		""
		"function meow (a) \n"
		"  a.big = a.big + x.a\n"
		"  return a\n"
		"end\n"

		""
		);
	
	auto meow = global.GetFunction("meow");

	auto result = meow.Invoke(params);
	int big = result.GetInteger("big");

	return 0;
}
