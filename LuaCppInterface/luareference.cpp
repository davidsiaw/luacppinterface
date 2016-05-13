#include "luareference.h"
#include "luatable.h"

LuaReference::LuaReference(std::shared_ptr<lua_State> state, int index) : state(state)
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
	other.PushToStack(state.get());
	ref = luaL_ref(state.get(), LUA_REGISTRYINDEX);
	return *this;
}

LuaReference::~LuaReference()
{
	luaL_unref(state.get(), LUA_REGISTRYINDEX, ref);
}

void LuaReference::PushToStack(lua_State* currentState) const
{
	lua_rawgeti(currentState, LUA_REGISTRYINDEX, ref);
}

LuaType::Value LuaReference::GetType() const
{
	PushToStack(state.get());
	LuaType::Value val = (LuaType::Value)lua_type(state.get(), -1);
	lua_pop(state.get(), 1);
	return val;
}

std::shared_ptr<lua_State> LuaReference::GetState()
{
	return state;
}

LuaTable LuaReference::GetMetaTable() const
{
	PushToStack(state.get());
	int res = lua_getmetatable(state.get(), -1);

	if (res == 0)
	{
		luaL_error(state.get(), "failed to get metatable");
	}

	LuaTable table = LuaTable(state, -1);
	lua_pop(state.get(), 2);
	return table;
}
