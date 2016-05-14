#include "luacoroutine.h"
#include "luatable.h"
#include "luatypetemplates.h"
#include "luafunction.h"

LuaTable::LuaTable(std::shared_ptr<lua_State> state, int index) : LuaReference(state, index)
{
	if (GetType() != LuaType::table)
	{
		const char *msg = lua_pushfstring(state.get(), "table expected, got %s", luaL_typename(state.get(), index));
		luaL_argerror(state.get(), index, msg);
	}
}

LuaType::Value LuaTable::GetTypeOfValueAt(std::string key) const
{
	PushToStack(state.get());
	lua_pushlstring(state.get(), key.c_str(), key.size());
	lua_gettable(state.get(), -2);
	LuaType::Value res = (LuaType::Value)lua_type(state.get(), -1);
	lua_pop(state.get(), 2);
	return res;
}

LuaType::Value LuaTable::GetTypeOfValueAt(int key) const
{
	PushToStack(state.get());
	lua_pushinteger(state.get(), key);
	lua_gettable(state.get(), -2);
	LuaType::Value res = (LuaType::Value)lua_type(state.get(), -1);
	lua_pop(state.get(), 2);
	return res;
}

void LuaTable::ForAllStringKeys(std::function<void(std::string, LuaType::Value)> stringKeys) const
{
	PushToStack(state.get());
	lua_pushnil(state.get());  /* first key */

	while (lua_next(state.get(), -2) != 0)
    {

		if ((LuaType::Value)lua_type(state.get(), -2) == LuaType::string)
		{
			const char* key = lua_tostring(state.get(), -2);
			auto valueType = (LuaType::Value)lua_type(state.get(), -1);
			stringKeys(key, valueType);
		}
		lua_pop(state.get(), 1);
	}
    lua_pop(state.get(), 1);
}

void LuaTable::ForAllIntegerKeys(std::function<void(int64_t, LuaType::Value)> integerKeys) const
{
	PushToStack(state.get());
	lua_pushnil(state.get());  /* first key */

	while (lua_next(state.get(), -2) != 0)
    {
		if ((LuaType::Value)lua_type(state.get(), -2) == LuaType::number)
		{
			int64_t key = lua_tointeger(state.get(), -2);
			auto valueType = (LuaType::Value)lua_type(state.get(), -1);
			integerKeys(key, valueType);
		}
		lua_pop(state.get(), 1);
	}
    lua_pop(state.get(), 1);
}
