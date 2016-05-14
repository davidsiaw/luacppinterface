#include "luacoroutine.h"
#include "luaerror.h"

LuaCoroutine::LuaCoroutine(std::shared_ptr<lua_State> state, int index) : LuaReference(state, index)
{
	if (GetType() != LuaType::thread)
	{
		const char *msg = lua_pushfstring(state.get(), "thread expected, got %s", luaL_typename(state.get(), index));
		luaL_argerror(state.get(), index, msg);
	}
}

std::string LuaCoroutine::RunScript(std::string script)
{
	PushToStack(state.get());
	lua_State* thread = lua_tothread(state.get(), -1);
	lua_pop(state.get(), 1);
	int status = luaL_loadstring(thread, script.c_str());
	status = lua_resume(thread, NULL, 0);

	if (status != LUA_OK && status != LUA_YIELD)
	{
		return LuaGetLastError(thread);
	}
	return "No errors";
}

std::string LuaCoroutine::Resume()
{
	PushToStack(state.get());
	lua_State* thread = lua_tothread(state.get(), -1);
	lua_pop(state.get(), 1);
	int status = lua_resume(thread, NULL, lua_gettop(thread));

	if (status != LUA_OK && status != LUA_YIELD)
	{
		return LuaGetLastError(thread);
	}
	return "No errors";
}

bool LuaCoroutine::CanResume() const
{
	PushToStack(state.get());
	lua_State* thread = lua_tothread(state.get(), -1);
	lua_pop(state.get(), 1);
	if (lua_status(thread) == LUA_YIELD)
	{
		return true;
	}
	return false;
}
