// Try and get a metatable of a table that was unreffed (abuse)

#include <iostream>
#include <sstream>
#include <memory>
#include <luacppinterface.h>

int main()
{
	Lua lua;

	auto table = lua.CreateTable();

	auto state = table.GetState();
	table.PushToStack(state.get());
	auto ref = luaL_ref(state.get(), LUA_REGISTRYINDEX);
	luaL_unref(state.get(), LUA_REGISTRYINDEX, ref);
	luaL_unref(state.get(), LUA_REGISTRYINDEX, ref);

	try
	{
		auto metatable = table.GetMetaTable();
	}
	catch(LuaError e)
	{
		std::cout << e.GetMessage() << std::endl;
		return e.GetMessage() != "Error: failed to get metatable\n";
	}

	return 1;
}
