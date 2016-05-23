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
		return LuaUserdata<TYPE>(state, data);
	}

	// create a userdata
	template<typename TYPE>
	LuaUserdata<TYPE> CreateUserdata(TYPE* data, std::function<void(TYPE*)> destructor)
    {
		return LuaUserdata<TYPE>(state, data, destructor);
	}

	// create a lua-callable function
	template<typename SIG>
	LuaFunction<SIG> CreateFunction(std::function<SIG> func)
	{
		return LuaFunction<SIG>(state, func);
	}

	// create a lua-callable function that pauses execution once complete
	template<typename SIG>
	LuaFunction<SIG> CreateYieldingFunction(std::function<SIG> func)
	{
		return LuaYieldingFunction<SIG>(state, func);
	}

    void CollectGarbage()
    {
        lua_gc(state.get(), LUA_GCCOLLECT, 0);
    }

    // This object can also be used as the lua state object
    operator std::shared_ptr<lua_State>() const;

};

#include "luauserdatabindtemplates.h"

#endif // LUACPPINTERFACE
