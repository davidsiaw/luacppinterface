#ifndef LUACPPINTERFACE_H
#define LUACPPINTERFACE_H

#include <memory>
#include <functional>
#include <cstring>

#include "luacoroutine.h"
#include "luatable.h"
#include "luatypetemplates.h"
#include "luafunction.h"
#include "luauserdata.h"
#include "lualightuserdata.h"
#include "luastringconversion.h"
#include "luaerror.h"

class Lua
{
	std::shared_ptr<lua_State> state;
	LuaTable registry;
	LuaTable globals;

	template<typename SIG>
	LuaFunction<SIG> internalCreateFunction( std::shared_ptr< std::function<SIG> > func, lua_CFunction cfunc)
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
		lua_pushcclosure(state.get(), cfunc, 1);

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

	template<typename SIG>
	static int lua_finalizer(lua_State* state)
	{
		LuaFunction<SIG>** func = (LuaFunction<SIG>**)lua_touserdata(state, lua_upvalueindex(1));
		delete *func;
		return 0;
	};

	template<typename SIG>
	static int lua_yieldingFunction(lua_State* state)
	{
		int numVals = LuaFunction<SIG>::staticFunction(state);
		return lua_yield(state, numVals);
	};

	template<typename SIG>
	static int lua_normalFunction(lua_State* state)
	{
		int numVals = LuaFunction<SIG>::staticFunction(state);
		return numVals;
	};

public:
	// create a new Lua state
	Lua();

	Lua(std::shared_ptr<lua_State> state);

	~Lua();

	// load standard lua libraries into this state
	void LoadStandardLibraries();

	// get the registry table
	LuaTable GetRegistry() const;

	// get the global table
	LuaTable GetGlobalEnvironment() const;

	// create a table
	LuaTable CreateTable();

	// create a coroutine
	LuaCoroutine CreateCoroutine();

	// run a Lua script
	std::string RunScript(std::string script);
    
    // create a userdata using a default operator delete destructor
	template<typename TYPE>
	LuaUserdata<TYPE> CreateUserdata(TYPE* data)
	{
		return CreateUserdata<TYPE>(data, [](TYPE* data){ delete data; });
	}

	// create a userdata
	template<typename TYPE>
	LuaUserdata<TYPE> CreateUserdata(TYPE* data, std::function<void(TYPE*)> destructor)
    {
		typename LuaUserdata<TYPE>::UserdataWrapper* wrap = (typename LuaUserdata<TYPE>::UserdataWrapper*)lua_newuserdata(state.get(), sizeof(typename LuaUserdata<TYPE>::UserdataWrapper));
        
		memset(wrap, 0, sizeof(typename LuaUserdata<TYPE>::UserdataWrapper));
        
		wrap->actualData = data;
		wrap->destructor = new std::function<void(TYPE*)> (destructor);

		LuaUserdata<TYPE> user(state, -1);

		lua_newtable(state.get());

		// make the finalizer
		lua_pushstring(state.get(), "__gc");
		lua_pushlightuserdata(state.get(), (void*)wrap);
		lua_pushcclosure(state.get(), LuaUserdata<TYPE>::lua_userdata_finalizer, 1);
		lua_rawset(state.get(), -3);

		// assign table to self
		lua_pushstring(state.get(), "__index");
		lua_pushvalue(state.get(), -2);
		lua_rawset(state.get(), -3);

		lua_setmetatable(state.get(), -2);

		lua_pop(state.get(), 1);
		return user;
	}

	// create a lua-callable function
	template<typename SIG>
	LuaFunction<SIG> CreateFunction(std::function<SIG> func)
	{
		return internalCreateFunction(std::shared_ptr<std::function<SIG>>(new std::function<SIG>(func)), lua_normalFunction<SIG>);
	}

	// create a lua-callable function that pauses execution once complete
	template<typename SIG>
	LuaFunction<SIG> CreateYieldingFunction(std::function<SIG> func)
	{
		return internalCreateFunction(std::shared_ptr<std::function<SIG>>(new std::function<SIG>(func)), lua_yieldingFunction<SIG>);
	}

    void CollectGarbage()
    {
        lua_gc(state.get(), LUA_GCCOLLECT, 0);
    }

};

#include "luauserdatabindtemplates.h"

#endif // LUACPPINTERFACE
