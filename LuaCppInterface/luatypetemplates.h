#ifndef LUATYPETEMPLATES_H
#define LUATYPETEMPLATES_H

template<typename T>
struct pusher
{
	static void push(std::tr1::shared_ptr<lua_State> state, T param)
	{
		static_assert(sizeof(T) == 0, "parameter types other than string, int, LuaTable or LuaFunction<R(...)> not available");
	}
};

template<typename T>
struct popper
{
	static T pop(std::tr1::shared_ptr<lua_State> state)
	{
		static_assert(sizeof(T) == 0, "returns types other than string, int, void, LuaTable or LuaFunction<R(...)> not available" );
	}
};

template<>
struct pusher<LuaTable>
{
	static void push(std::tr1::shared_ptr<lua_State> state, LuaTable param)
	{
		param.PushToStack();
	}
};

template<>
struct popper<LuaTable>
{
	static LuaTable pop(std::tr1::shared_ptr<lua_State> state)
	{
		LuaTable res(state, -1);
		lua_pop(state.get(), 1);
		return res;
	}
};

template<typename SIG>
struct pusher< LuaFunction<SIG> >
{
	static void push(std::tr1::shared_ptr<lua_State> state, LuaFunction<SIG> param)		
	{
		param.PushToStack();
	}
};

template<typename SIG>
struct popper< LuaFunction<SIG> >
{
	static LuaFunction<SIG> pop(std::tr1::shared_ptr<lua_State> state)
	{
		LuaFunction<SIG> res(state, -1);
		lua_pop(state.get(), 1);
		return res;
	}
};

template<>
struct pusher<int>
{
	static void push(std::tr1::shared_ptr<lua_State> state, int param)
	{
		lua_pushinteger(state.get(), param);
	}
};

template<>
struct pusher<std::string>
{
	static void push(std::tr1::shared_ptr<lua_State> state, std::string param)
	{
		lua_pushlstring(state.get(), param.c_str(), param.length());
	}
};

template<>
struct popper<int>
{
	static int pop(std::tr1::shared_ptr<lua_State> state)
	{
		int res = lua_tointeger(state.get(), -1);
		lua_pop(state.get(), 1);
		return res;
	}
};

template<>
struct popper<std::string>
{
	static std::string pop(std::tr1::shared_ptr<lua_State> state)
	{
		std::string res = lua_tostring(state.get(), -1);
		lua_pop(state.get(), 1);
		return res;
	}
};


#endif // LUATYPETEMPLATES_H
