#include <cassert>
#include "luacoroutine.h"
#include "luatable.h"
#include "luatypetemplates.h"
#include "luafunction.h"

LuaFunctionBase::LuaFunctionBase(std::shared_ptr<lua_State> state, int index) : LuaReference(state, index)
{
	auto type = GetType();
	if (type != LuaType::function)
	{
		LuaTable metatable = GetMetaTable();
		if (metatable.GetTypeOfValueAt("__call") != LuaType::function)
		{
			const char *msg = lua_pushfstring(state.get(), "function or callable object expected, got %s", luaL_typename(state.get(), index));
			luaL_argerror(state.get(), index, msg);
		}
	}
}
