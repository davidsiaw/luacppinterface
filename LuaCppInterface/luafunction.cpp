#include "luafunction.h"
#include "luatable.h"

LuaFunction::LuaFunction(std::tr1::shared_ptr<lua_State> state, int index) : LuaReference(state, index)
{
	auto a = GetType();
	assert(GetType() == LuaType::function);
}

LuaTableFunction::LuaTableFunction(std::tr1::shared_ptr<lua_State> state, int index) : LuaFunction(state, index)
{
	auto a = GetType();
	assert(GetType() == LuaType::function);
}

LuaTable LuaTableFunction::Invoke(LuaTable args)
{
	PushToStack();
	args.PushToStack();
	lua_call(state.get(), 1, 1);
	LuaTable table = LuaTable(state, -1);
	lua_pop(state.get(), 1);

	return table;
}
