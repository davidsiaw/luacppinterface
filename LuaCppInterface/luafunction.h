#ifndef LUAFUNCTION_H
#define LUAFUNCTION_H

#include "luagenericfunction.h"

template<typename SIG>
class LuaFunction : public LuaGenericFunction<SIG>
{
	typedef typename std::shared_ptr< std::function<SIG> > funcPtr;
	funcPtr func;

public:
	LuaFunction(std::shared_ptr<lua_State> state, int index, funcPtr func = funcPtr()) : LuaGenericFunction<SIG>(state, index), func(func)
	{
	}
};

#endif // LUAFUNCTION_H
