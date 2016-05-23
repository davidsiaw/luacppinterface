#include "luacppinterface.h"
#include "luauserdata.h"

#include <sstream>

static int panic_function(lua_State *state)
{
	throw LuaError(LuaGetLastError(state));
}

Lua::Lua() :
	state(luaL_newstate(), lua_close),
	registry(LuaTable(state, LUA_REGISTRYINDEX)),
	globals(registry.Get<LuaTable>(LUA_RIDX_GLOBALS))
{
	lua_atpanic(state.get(), panic_function);
}

Lua::Lua(std::shared_ptr<lua_State> state) :
	state(state),
	registry(LuaTable(state, LUA_REGISTRYINDEX)),
	globals(registry.Get<LuaTable>(LUA_RIDX_GLOBALS))
{
	// In this case the state was made somewhere else. This lua object does not own it
	// So we do not assign a panic function to it.
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
	return LuaTable(state);
}

LuaCoroutine Lua::CreateCoroutine()
{
	return LuaCoroutine(state);
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

Lua::operator std::shared_ptr<lua_State>() const
{
	return state;
}

Lua::~Lua()
{
}
