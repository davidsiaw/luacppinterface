#ifndef LUACPPINTERFACE_H
#define LUACPPINTERFACE_H

#include <boost/tr1/memory.hpp>
#include <boost/tr1/functional.hpp>
#include "luatable.h"
#include "luatypetemplates.h"
#include "luafunction.h"

class Lua
{
	std::tr1::shared_ptr<lua_State> state;
	LuaTable registry;
	LuaTable globals;

public:
	// create a new Lua state
	Lua();
	~Lua();

	// get the registry table
	LuaTable GetRegistry();

	// get the global table
	LuaTable GetGlobalEnvironment();

	// create a table
	LuaTable CreateTable();

	// run a Lua script
	std::string RunScript(std::string script);

	template<typename SIG>
	static int lua_finalizer(lua_State* state)
	{
		LuaFunction<SIG>** func = (LuaFunction<SIG>**)lua_touserdata(state, lua_upvalueindex(1));
		delete *func;
		return 0;
	};

	template<typename SIG>
	LuaFunction<SIG> CreateFunction( std::tr1::shared_ptr< std::tr1::function<SIG> > func)
	{
		LuaFunction<SIG>** ptr = (LuaFunction<SIG>**)lua_newuserdata(state.get(), sizeof(LuaFunction<SIG>**));

		lua_newtable(state.get());
		
		// make the finalizer
		lua_pushstring(state.get(), "__gc");

		lua_pushlightuserdata(state.get(), (void*)ptr);
		lua_pushcclosure(state.get(), lua_finalizer<SIG>, 1);

		lua_rawset(state.get(), -3);
		
		// make the caller
		lua_pushstring(state.get(), "__call");
		
		lua_pushlightuserdata(state.get(), (void*)func.get());
		lua_pushcclosure(state.get(), LuaFunction<SIG>::staticFunction, 1);

		lua_rawset(state.get(), -3);

		// set the metatable
		lua_setmetatable(state.get(), -2);
		LuaFunction<SIG> function = LuaFunction<SIG>(state, -1, func);

		// instantiate a luafunction that has a weak reference to the state
		// that the lua garbage collector will collect.
		*ptr = new LuaFunction<SIG>(LuaFunction<SIG>(LuaNoDestructor(state.get()), -1, func));

		lua_pop(state.get(), 1);
		return function;
	}

};

#endif // LUACPPINTERFACE
