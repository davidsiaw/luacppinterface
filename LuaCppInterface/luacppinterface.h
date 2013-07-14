#ifndef LUACPPINTERFACE_H
#define LUACPPINTERFACE_H

#include <memory>
#include <functional>
#include "luatable.h"
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

	
	template<typename SIG, typename T, typename T1, typename T2>
	struct sgf
	{
		static int staticGenFunction(lua_State* state)
		{
			std::tr1::function<SIG>* func = (std::tr1::function<SIG>*)lua_touserdata(state, lua_upvalueindex(1));
			
			T1 arg1 = popretval<T1>(state);
			T2 arg2 = popretval<T2>(state);

			T retval = func->operator()(arg1,arg2);
			pushparam(state, retval);
			return 1;
		}
	};
	
	template<typename SIG, typename T, typename T1>
	struct sgf<SIG, T, T1, nothing>
	{
		static int staticGenFunction(lua_State* state)
		{
			std::tr1::function<SIG>* func = (std::tr1::function<SIG>*)lua_touserdata(state, lua_upvalueindex(1));

			T1 arg1 = popretval<T1>(state);

			T retval = func->operator()(arg1);
			pushparam(state, retval);

			return 1;
		}
	};

	template<typename SIG, typename T>
	struct sgf<SIG, T, nothing, nothing>
	{
		static int staticGenFunction(lua_State* state)
		{
			// todo pull parameters

			std::tr1::function<SIG>* func = (std::tr1::function<SIG>*)lua_touserdata(state, lua_upvalueindex(1));
			
			// causes errors when T is void
			T retval = func->operator()();
			pushparam(state, retval);
			
			return 1;
		}
	};


	template<typename SIG, typename T1, typename T2>
	struct sgf<SIG, void, T1, T2>
	{
		static int staticGenFunction(lua_State* state)
		{
			// todo pull parameters

			std::tr1::function<SIG>* func = (std::tr1::function<SIG>*)lua_touserdata(state, lua_upvalueindex(1));
			return 0;
		}
	};
	
	template<typename SIG, typename T1>
	struct sgf<SIG, void, T1, nothing>
	{
		static int staticGenFunction(lua_State* state)
		{
			// todo pull parameters

			std::tr1::function<SIG>* func = (std::tr1::function<SIG>*)lua_touserdata(state, lua_upvalueindex(1));
			return 0;
		}
	};
	
	template<typename SIG>
	struct sgf<SIG, void, nothing, nothing>
	{
		static int staticGenFunction(lua_State* state)
		{
			// todo pull parameters

			std::tr1::function<SIG>* func = (std::tr1::function<SIG>*)lua_touserdata(state, lua_upvalueindex(1));
			return 0;
		}
	};

	template<typename T>
	LuaGenFunction<T(), T> CreateFunction(std::tr1::function<T()>* func)
	{
		lua_pushlightuserdata(state.get(), (void*)func);
		lua_pushcclosure(state.get(), sgf<T(), T, nothing, nothing>::staticGenFunction, 1);
		LuaGenFunction<T(), T> function = LuaGenFunction<T(), T>(state, -1);
		lua_pop(state.get(), 1);
		return function;
	}

	template<typename T, typename T1>
	LuaGenFunction<T(T1), T,T1> CreateFunction(std::tr1::function<T(T1)>* func)
	{
		lua_pushlightuserdata(state.get(), (void*)func);
		lua_pushcclosure(state.get(), sgf<T(T1), T, T1, nothing>::staticGenFunction, 1);
		LuaGenFunction<T(T1), T,T1> function = LuaGenFunction<T(T1), T,T1>(state, -1);
		lua_pop(state.get(), 1);
		return function;
	}

	template<typename T, typename T1, typename T2>
	LuaGenFunction<T(T1,T2), T,T1,T2> CreateFunction(std::tr1::function<T(T1,T2)>* func)
	{
		lua_pushlightuserdata(state.get(), (void*)func);
		lua_pushcclosure(state.get(), sgf<T(T1,T2), T,T1,T2>::staticGenFunction, 1);
		LuaGenFunction<T(T1,T2), T,T1,T2> function = LuaGenFunction<T(T1,T2), T,T1,T2>(state, -1);
		lua_pop(state.get(), 1);
		return function;
	}

};

#endif // LUACPPINTERFACE
