#ifndef LUATABLE_H
#define LUATABLE_H

#include <cassert>
#include <string>
#include <memory>
#include "luareference.h"
#include "luafunction.h"

class LuaTable : public LuaReference
{

public:
	LuaTable(std::tr1::shared_ptr<lua_State> state, int index);

	// Associate the given key to a specified table
	void SetTable(std::string key, const LuaTable& value);	
	void SetTable(int key, const LuaTable& value);

	// Associate the given key to a specified integer
	void SetInteger(std::string key, const int value);
	void SetInteger(int key, const int value);

	// Associate the given key to a specified string
	void SetString(std::string key, const std::string value);
	void SetString(int key, const std::string value);	

	// Associate the given key to a specified function
	void SetFunction(std::string key, const LuaFunction value);
	void SetFunction(int key, const LuaFunction value);

	// Get the table associated with the specified key
	LuaTable GetTable(std::string key) const;
	LuaTable GetTable(int key) const;

	// Get the integer associated with the specified key
	int GetInteger(std::string key) const;
	int GetInteger(int key) const;

	// Get the string associated with the specified key
	std::string GetString(std::string key) const;
	std::string GetString(int key) const;

	// Get the function associated with the specified key
	LuaTableFunction GetFunction(std::string key) const;
	LuaTableFunction GetFunction(int key) const;

	

	template<typename T>
	LuaGenFunction<T(), T> GetFunction(std::string key, std::tr1::function<T()> a)
	{
		PushToStack();
		lua_pushlstring(state.get(), key.c_str(), key.size());
		lua_gettable(state.get(), -2);

		LuaGenFunction<T(), T> res = LuaGenFunction<T(), T>(state, -1);

		lua_pop(state.get(), 2);
		return res;
	}

	template<typename T, typename T1>
	LuaGenFunction<T(T1), T,T1> GetFunction(std::string key, std::tr1::function<T(T1)> a)
	{
		PushToStack();
		lua_pushlstring(state.get(), key.c_str(), key.size());
		lua_gettable(state.get(), -2);

		LuaGenFunction<T(T1), T, T1> res = LuaGenFunction<T(T1), T, T1>(state, -1);

		lua_pop(state.get(), 2);
		return res;
	}

	template<typename T, typename T1, typename T2>
	LuaGenFunction<T(T1,T2), T,T1,T2> GetFunction(std::string key, std::tr1::function<T(T1,T2)> a)
	{
		PushToStack();
		lua_pushlstring(state.get(), key.c_str(), key.size());
		lua_gettable(state.get(), -2);

		LuaGenFunction<T(T1,T2), T, T1, T2> res = LuaGenFunction<T(T1,T2), T, T1, T2>(state, -1);

		lua_pop(state.get(), 2);
		return res;
	}
};

template<>
static void pushparam<LuaTable>(lua_State* state, LuaTable param)
{
	param.PushToStack();
}

template<>
static LuaTable popretval<LuaTable>(lua_State* state)
{
	return LuaTable(std::tr1::shared_ptr<lua_State>(state, [&](lua_State*){}), -1);
}

#endif // LUATABLE_H
