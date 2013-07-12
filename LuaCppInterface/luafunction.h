#ifndef LUAFUNCTION_H
#define LUAFUNCTION_H

#include <string>
#include <cassert>
#include "luareference.h"

class LuaTable;
class LuaFunction : public LuaReference
{
public:
	LuaFunction(std::tr1::shared_ptr<lua_State> state, int index);
	LuaTable Invoke(LuaTable table);
};


#endif LUAFUNCTION_H
