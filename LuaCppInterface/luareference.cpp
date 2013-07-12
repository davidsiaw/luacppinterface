#include "luareference.h"
#include "luatable.h"

LuaReference::LuaReference(std::tr1::shared_ptr<lua_State> state, int index) : state(state)
{
	lua_pushvalue(state.get(), index);
	ref = luaL_ref(state.get(), LUA_REGISTRYINDEX);;
}

LuaReference::LuaReference(const LuaReference& other)
{
	*this = other;
}

LuaReference& LuaReference::operator=(const LuaReference& other)
{ 
	state = other.state;
	other.PushToStack();
	ref = luaL_ref(state.get(), LUA_REGISTRYINDEX);
	return *this;
}

LuaReference::~LuaReference()
{
	luaL_unref(state.get(), LUA_REGISTRYINDEX, ref);
}

void LuaReference::PushToStack() const
{
	lua_rawgeti(state.get(), LUA_REGISTRYINDEX, ref);
}

LuaType::Value LuaReference::GetType() const
{
	PushToStack();
	LuaType::Value val = (LuaType::Value)lua_type(state.get(), -1);
	lua_pop(state.get(), 1);
	return val;
}

std::tr1::shared_ptr<lua_State> LuaReference::GetState()
{
	return state;
}

LuaTable LuaReference::GetMetaTable() const
{
	PushToStack();
	int res = lua_getmetatable(state.get(), -1);
	assert(res != 0);
	LuaTable table = LuaTable(state, -1);
	lua_pop(state.get(), 2);
	return table;
}
