#include "luacppinterface.h"
#include "luauserdata.h"

#include <sstream>

std::string LuaGetLastError(lua_State* state)
{
	std::stringstream ss;
	for (int level = 1; level <= lua_gettop(state); level++)
	{
		const char* errorMessage = lua_tostring(state, level);
		if (errorMessage)
		{
			ss << "Error: " << errorMessage << std::endl;
		}
	}

	lua_Debug debugInfo;
	for (int level = 0; lua_getstack(state, level, &debugInfo); level++)
	{
		lua_getinfo(state, "nSlf", &debugInfo);
		ss << "Line: " << debugInfo.currentline << std::endl;
		ss << "Source: " << debugInfo.source << std::endl;
		
		const char* function = lua_tostring(state, -1);
		if (function)
		{
			ss << "Function: " << function << std::endl;
		}
	}

	return ss.str();
}

Lua::Lua() : 
	state(luaL_newstate(), lua_close),
	registry(LuaTable(state, LUA_REGISTRYINDEX)),
	globals(registry.Get<LuaTable>(LUA_RIDX_GLOBALS))
{
}

Lua::Lua(std::tr1::shared_ptr<lua_State> state) :
	state(state),
	registry(LuaTable(state, LUA_REGISTRYINDEX)),
	globals(registry.Get<LuaTable>(LUA_RIDX_GLOBALS))

{
}
	
void Lua::LoadStandardLibraries()
{
	luaL_openlibs(state.get());
}

LuaTable Lua::GetRegistry() const
{
	return registry;
}

LuaTable Lua::GetGlobalEnvironment() const
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

LuaCoroutine Lua::CreateCoroutine()
{
	lua_newthread(state.get());
	LuaCoroutine thread(state, -1);
	lua_pop(state.get(), 1);
	return thread;
}

std::string Lua::RunScript(std::string script)
{
	int err = luaL_dostring(state.get(), script.c_str());
	if (err != LUA_OK)
	{
		return LuaGetLastError(state.get());
	}
	return "No errors";
}

Lua::~Lua()
{
}
