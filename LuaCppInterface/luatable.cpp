#include "luatable.h"


LuaTable::LuaTable(std::tr1::shared_ptr<lua_State> state, int index) : LuaReference(state, index)
{
	assert(GetType() == LuaType::table);
}

void LuaTable::SetTable(std::string key, const LuaTable& value)
{
	PushToStack();
	lua_pushlstring(state.get(), key.c_str(), key.size());
	value.PushToStack();
	lua_settable(state.get(), -3);
	lua_pop(state.get(), 1);
}

void LuaTable::SetTable(int key, const LuaTable& value)
{
	PushToStack();
	lua_pushinteger(state.get(), key);
	value.PushToStack();
	lua_settable(state.get(), -3);
	lua_pop(state.get(), 1);
}

void LuaTable::SetInteger(std::string key, const int value)
{
	PushToStack();
	lua_pushlstring(state.get(), key.c_str(), key.size());
	lua_pushinteger(state.get(), value);
	lua_settable(state.get(), -3);
	lua_pop(state.get(), 1);
}

void LuaTable::SetInteger(int key, const int value)
{
	PushToStack();
	lua_pushinteger(state.get(), key);
	lua_pushinteger(state.get(), value);
	lua_settable(state.get(), -3);
	lua_pop(state.get(), 1);
}

void LuaTable::SetString(std::string key, const std::string value)
{
	PushToStack();
	lua_pushlstring(state.get(), key.c_str(), key.size());
	lua_pushlstring(state.get(), value.c_str(), value.length());
	lua_settable(state.get(), -3);
	lua_pop(state.get(), 1);
}

void LuaTable::SetString(int key, const std::string value)
{
	PushToStack();
	lua_pushinteger(state.get(), key);
	lua_pushlstring(state.get(), value.c_str(), value.length());
	lua_settable(state.get(), -3);
	lua_pop(state.get(), 1);
}

void LuaTable::SetFunction(std::string key, const LuaFunction value)
{
	PushToStack();
	lua_pushlstring(state.get(), key.c_str(), key.size());
	value.PushToStack();
	lua_settable(state.get(), -3);
	lua_pop(state.get(), 1);
}

void LuaTable::SetFunction(int key, const LuaFunction value)
{
	PushToStack();
	lua_pushinteger(state.get(), key);
	value.PushToStack();
	lua_settable(state.get(), -3);
	lua_pop(state.get(), 1);
}

LuaTable LuaTable::GetTable(std::string key) const
{
	PushToStack();
	lua_pushlstring(state.get(), key.c_str(), key.size());
	lua_gettable(state.get(), -2);

	LuaTable table = LuaTable(state, -1);

	lua_pop(state.get(), 2);
	return table;
}

LuaTable LuaTable::GetTable(int key) const
{
	PushToStack();
	lua_pushinteger(state.get(), key);
	lua_gettable(state.get(), -2);

	LuaTable table = LuaTable(state, -1);

	lua_pop(state.get(), 2);
	return table;
}

int LuaTable::GetInteger(std::string key) const
{
	PushToStack();
	lua_pushlstring(state.get(), key.c_str(), key.size());
	lua_gettable(state.get(), -2);

	int res = lua_tointeger(state.get(), -1);

	lua_pop(state.get(), 2);
	return res;
}

int LuaTable::GetInteger(int key) const
{
	PushToStack();
	lua_pushinteger(state.get(), key);
	lua_gettable(state.get(), -2);

	int res = lua_tointeger(state.get(), -1);

	lua_pop(state.get(), 2);
	return res;
}

std::string LuaTable::GetString(std::string key) const
{
	PushToStack();
	lua_pushlstring(state.get(), key.c_str(), key.size());
	lua_gettable(state.get(), -2);

	std::string res = std::string(lua_tostring(state.get(), -1));

	lua_pop(state.get(), 2);
	return res;
}

std::string LuaTable::GetString(int key) const
{
	PushToStack();
	lua_pushinteger(state.get(), key);
	lua_gettable(state.get(), -2);

	std::string res = std::string(lua_tostring(state.get(), -1));

	lua_pop(state.get(), 2);
	return res;
}

LuaFunction LuaTable::GetFunction(std::string key) const
{
	PushToStack();
	lua_pushlstring(state.get(), key.c_str(), key.size());
	lua_gettable(state.get(), -2);

	LuaFunction res = LuaFunction(state, -1);

	lua_pop(state.get(), 2);
	return res;
}

LuaFunction LuaTable::GetFunction(int key) const
{
	PushToStack();
	lua_pushinteger(state.get(), key);
	lua_gettable(state.get(), -2);

	LuaFunction res = LuaFunction(state, -1);

	lua_pop(state.get(), 2);
	return res;
}
