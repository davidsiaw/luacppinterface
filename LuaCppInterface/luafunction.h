#ifndef LUAFUNCTION_H
#define LUAFUNCTION_H

#include "luagenericfunction.h"

template<typename SIG>
class LuaFunction : public LuaGenericFunction<SIG>
{
	typedef typename std::tr1::shared_ptr< std::tr1::function<SIG> > funcPtr;
	funcPtr func;

public:
	LuaFunction(std::tr1::shared_ptr<lua_State> state, int index, funcPtr func = funcPtr()) : LuaGenericFunction(state, index), func(func)
	{
	}
};

#define MAKELUAFUNC(functype, func) std::tr1::shared_ptr< std::tr1::function<functype> >(new std::tr1::function<functype>(func))

#endif LUAFUNCTION_H
