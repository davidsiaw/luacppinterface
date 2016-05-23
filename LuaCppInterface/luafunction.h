#ifndef LUAFUNCTION_H
#define LUAFUNCTION_H

#include "luagenericfunction.h"

template<typename SIG>
class LuaFunction : public LuaGenericFunction<SIG>
{
	typedef typename std::shared_ptr< std::function<SIG> > funcPtr;
	funcPtr func;

	int pushFunction(std::shared_ptr<lua_State> state, funcPtr func, lua_CFunction cfunc)
	{
		LuaFunction<SIG>** ptr = (LuaFunction<SIG>**)lua_newuserdata(state.get(), sizeof(LuaFunction<SIG>**));

		if (ptr == NULL)
		{
			const char *msg = lua_pushfstring(state.get(), "failed to allocate memory");
			luaL_argerror(state.get(), -1, msg);
		}

		lua_newtable(state.get());

		// make the finalizer
		lua_pushstring(state.get(), "__gc");

		lua_pushlightuserdata(state.get(), (void*)ptr);
		lua_pushcclosure(state.get(), lua_finalizer, 1);

		lua_rawset(state.get(), -3);

		// make the caller
		lua_pushstring(state.get(), "__call");

		lua_pushlightuserdata(state.get(), (void*)func.get());
		lua_pushcclosure(state.get(), cfunc, 1);

		lua_rawset(state.get(), -3);

		// set the metatable
		lua_setmetatable(state.get(), -2);

		// instantiate a luafunction that has a weak reference to the state
		// that the lua garbage collector will collect.
		*ptr = new LuaFunction<SIG>(LuaFunction<SIG>(LuaNoDestructor(state.get()), -1, func));

		return -1;
	}

	static int lua_finalizer(lua_State* state)
	{
		LuaFunction<SIG>** func = (LuaFunction<SIG>**)lua_touserdata(state, lua_upvalueindex(1));
		delete *func;
		return 0;
	};

	LuaFunction(std::shared_ptr<lua_State> state, funcPtr func, lua_CFunction cfunc) :
		LuaFunction(state, pushFunction(state, func, cfunc), func)
	{
		lua_pop(state.get(), 1);
	}

	static int lua_normalFunction(lua_State* state)
	{
		int numVals = LuaFunction<SIG>::staticFunction(state);
		return numVals;
	};

public:

	LuaFunction(std::shared_ptr<lua_State> state, std::function<SIG> func) : 
		LuaFunction(state, func, lua_normalFunction)
	{ }

	LuaFunction(std::shared_ptr<lua_State> state, std::function<SIG> func, lua_CFunction cfunc) : 
		LuaFunction(state, funcPtr(new std::function<SIG>(func)), cfunc)
	{ }
	
	LuaFunction(std::shared_ptr<lua_State> state, int index, funcPtr func = funcPtr()) : 
		LuaGenericFunction<SIG>(state, index), func(func)
	{ }


};

template<typename SIG>
class LuaYieldingFunction : public LuaFunction<SIG>
{

	static int lua_yieldingFunction(lua_State* state)
	{
		int numVals = LuaFunction<SIG>::staticFunction(state);
		return lua_yield(state, numVals);
	};

public:

	LuaYieldingFunction(std::shared_ptr<lua_State> state, std::function<SIG> func) : 
		LuaFunction<SIG>(state, func, lua_yieldingFunction)
	{ }

};

#endif // LUAFUNCTION_H
