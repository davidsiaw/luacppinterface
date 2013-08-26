#ifndef LUAFUNCTION_H
#define LUAFUNCTION_H

#include "luagenericfunction.h"

template<typename SIG>
class LuaFunction : public LuaGenericFunction<SIG>
{
	typedef typename std::tr1::shared_ptr< std::tr1::function<SIG> > funcPtr;
	funcPtr func;

public:
	LuaFunction(std::tr1::shared_ptr<lua_State> state, int index, funcPtr func = funcPtr()) : LuaGenericFunction<SIG>(state, index), func(func)
	{
	}
};

#endif // LUAFUNCTION_H
