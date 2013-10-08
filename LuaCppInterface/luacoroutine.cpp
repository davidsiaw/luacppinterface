#include "luacoroutine.h"

LuaCoroutine::LuaCoroutine(std::tr1::shared_ptr<lua_State> state, int index) : LuaReference(state, index)
{
	assert(GetType() == LuaType::thread);
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
		const char* r = lua_tostring(thread, -1);
		return r;
	}
	return "No errors";
}

std::string LuaCoroutine::Resume()
{
	PushToStack(state.get());
	lua_State* thread = lua_tothread(state.get(), -1);
	lua_pop(state.get(), 1);
	int status = lua_resume(thread, NULL, 0);
	if (status != LUA_OK && status != LUA_YIELD)
	{
		const char* r = lua_tostring(thread, -1);
		return r;
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
