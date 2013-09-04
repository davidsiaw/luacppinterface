#include "luacoroutine.h"

LuaCoroutine::LuaCoroutine(std::tr1::shared_ptr<lua_State> state, int index) : LuaReference(state, index)
{
	status = LUA_OK;
	assert(GetType() == LuaType::thread);
}

std::string LuaCoroutine::RunScript(std::string script)
{
	PushToStack();
	lua_State* thread = lua_tothread(state.get(), -1);
	lua_pop(state.get(), 1);
	status = luaL_loadstring(thread, script.c_str());
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
	if (!CanResume())
	{
		return "Thread is not resumable";
	}

	PushToStack();
	lua_State* thread = lua_tothread(state.get(), -1);
	lua_pop(state.get(), 1);
	status = lua_resume(thread, NULL, 0);
	if (status != LUA_OK && status != LUA_YIELD)
	{
		const char* r = lua_tostring(thread, -1);
		return r;
	}
	return "No errors";
}

bool LuaCoroutine::CanResume() const
{
	return status == LUA_YIELD;
}
