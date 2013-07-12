#include "luacppinterface.h"

Lua::Lua() : 
	state(luaL_newstate(), lua_close),
	registry(LuaTable(state, LUA_REGISTRYINDEX)),
	globals(registry.GetTable(LUA_RIDX_GLOBALS))
{
}

LuaTable Lua::GetRegistry()
{
	return registry;
}

LuaTable Lua::GetGlobalEnvironment()
{
	return globals;
}

LuaTable Lua::CreateTable()
{
	lua_newtable(state.get());
	LuaTable table = LuaTable(state, -1);
	lua_pop(state.get(), 1);
	return table;
}

int Lua::staticFunction(lua_State* state)
{
	std::tr1::function<LuaTable(LuaTable)>* func = (std::tr1::function<LuaTable(LuaTable)>*)lua_touserdata(state, lua_upvalueindex(1));
	LuaTable table(std::tr1::shared_ptr<lua_State>(state, [&](lua_State*){}), -1);
	LuaTable result = func->operator()(table);
	result.PushToStack();
	return 1;
}

struct closure
{
	std::tr1::function<LuaTable(void*, LuaTable)> func;
	void* object;
	std::tr1::function<void(void*)> cleanup;
};

LuaFunction Lua::CreateFunction(const std::tr1::function<LuaTable(LuaTable)>* func)
{
	lua_pushlightuserdata(state.get(), (void*)func);
	lua_pushcclosure(state.get(), staticFunction, 1);
	LuaFunction function = LuaFunction(state, -1);
	lua_pop(state.get(), 1);
	return function;
}

std::string Lua::RunScript(std::string script)
{
	int err = luaL_dostring(state.get(), script.c_str());
	if (err != LUA_OK)
	{
		const char* r = lua_tostring(state.get(), -1);
		return r;
	}
	return "No errors";
}

Lua::~Lua()
{
}
