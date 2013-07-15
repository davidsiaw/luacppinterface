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
	void SetFunction(std::string key, const LuaFunctionBase value);
	void SetFunction(int key, const LuaFunctionBase value);

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
	template<typename SIG>
	LuaFunction<SIG> GetFunction(std::string key) const
	{
		PushToStack();
		lua_pushlstring(state.get(), key.c_str(), key.size());
		lua_gettable(state.get(), -2);

		LuaFunction<SIG> res = LuaFunction<SIG>(state, -1);
		
		lua_pop(state.get(), 2);
		return res;
	}

	template<typename SIG>
	LuaFunction<SIG> GetFunction(int key) const
	{
		PushToStack();
		lua_pushinteger(state.get(), key);
		lua_gettable(state.get(), -2);

		LuaFunction<SIG> res = LuaFunction<SIG>(state, -1);
		
		lua_pop(state.get(), 2);
		return res;
	}

	// Get the type of value at a specified key
	LuaType::Value GetTypeOfValueAt(std::string key) const;
	LuaType::Value GetTypeOfValueAt(int key) const;
};

#endif // LUATABLE_H
