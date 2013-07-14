#ifndef LUAFUNCTION_H
#define LUAFUNCTION_H

#include <string>
#include <functional>
#include <cassert>
#include "luareference.h"

class LuaTable;
class LuaFunction : public LuaReference
{
public:
	LuaFunction(std::tr1::shared_ptr<lua_State> state, int index);
};

class LuaTableFunction : public LuaFunction
{
public:
	LuaTableFunction(std::tr1::shared_ptr<lua_State> state, int index);
	LuaTable Invoke(LuaTable table);
};

class nothing {};

template<typename T>
static void pushparam(lua_State* state, T param)
{
	static_assert(false, "parameter types other than string or int not available");
}

template<typename T>
static T popretval(lua_State* state)
{
	static_assert(false, "returns types other than string, int or void not available");
}

template<>
static void pushparam<int>(lua_State* state, int param)
{
	lua_pushinteger(state, param);
}

template<>
static void pushparam<std::string>(lua_State* state, std::string param)
{
	lua_pushlstring(state, param.c_str(), param.length());
}

template<>
static void pushparam<nothing>(lua_State* state, nothing param)
{
	lua_pushnil(state);
}

template<>
static int popretval<int>(lua_State* state)
{
	return lua_tointeger(state, -1);
}

template<>
static std::string popretval<std::string>(lua_State* state)
{
	return lua_tostring(state, -1);
}

template<>
static void popretval<void>(lua_State* state)
{
}

template<typename SIG, typename T, typename T1=nothing, typename T2=nothing>
class LuaGenFunction : public LuaFunction
{
public:
	LuaGenFunction(std::tr1::shared_ptr<lua_State> state, int index) : LuaFunction(state, index)
	{
	}

	typedef T result_type;
	typedef T1 arg1_type;
	typedef T2 arg2_type;

	result_type Invoke(arg1_type a1=nothing(), arg2_type a2=nothing())
	{
		PushToStack();
		pushparam(state.get(), a1);
		pushparam(state.get(), a2);
		lua_call(state.get(), 2, 1);
		return popretval<T>(state.get());
	}
};


#endif LUAFUNCTION_H
