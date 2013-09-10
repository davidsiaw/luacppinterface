#include "luacoroutine.h"
#include "luatable.h"
#include "luatypetemplates.h"
#include "luafunction.h"

LuaTable::LuaTable(std::tr1::shared_ptr<lua_State> state, int index) : LuaReference(state, index)
{
	assert(GetType() == LuaType::table);
}

LuaType::Value LuaTable::GetTypeOfValueAt(std::string key) const
{
	PushToStack();
	lua_pushlstring(state.get(), key.c_str(), key.size());
	lua_gettable(state.get(), -2);
	LuaType::Value res = (LuaType::Value)lua_type(state.get(), -1);
	lua_pop(state.get(), 2);
	return res;
}

LuaType::Value LuaTable::GetTypeOfValueAt(int key) const
{
	PushToStack();
	lua_pushinteger(state.get(), key);
	lua_gettable(state.get(), -2);
	LuaType::Value res = (LuaType::Value)lua_type(state.get(), -1);
	lua_pop(state.get(), 2);
	return res;
}

