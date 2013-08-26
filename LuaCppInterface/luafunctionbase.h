#ifndef LUAFUNCTIONBASE_H
#define LUAFUNCTIONBASE_H

#include <string>

#include "luareference.h"

class LuaFunctionBase : public LuaReference
{
public:
	LuaFunctionBase(std::tr1::shared_ptr<lua_State> state, int index);
};

#endif // LUAFUNCTIONBASE_H
