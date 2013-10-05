#ifndef LUATYPETEMPLATES_H
#define LUATYPETEMPLATES_H

#include <cstdint>
#include <lua.h>

template<typename SIG>
class LuaFunction;


// Refer to this define to make a type template for new things. This is used
// in the Set<>, Get<> and marshalling for functions
#define DEFINE_TYPE_TEMPLATE_FOR(type,spec,pushcommand,popcommand)			\
template<spec>																\
struct pusher<type>															\
{																			\
	static void push(std::tr1::shared_ptr<lua_State> state, type param)		\
	{																		\
		pushcommand;														\
	}																		\
};																			\
																			\
template<spec>																\
struct popper<type>															\
{																			\
	static type pop(std::tr1::shared_ptr<lua_State> state)					\
	{																		\
		popcommand;															\
		lua_pop(state.get(), 1);											\
		return res;															\
	}																		\
};


// This is the interface declaration
template<typename T>
struct pusher
{
	static void push(std::tr1::shared_ptr<lua_State> state, T param)
	{
		static_assert(sizeof(T) == 0, "parameter types other than signed or unsigned char, short, int, long, LuaCoroutine, LuaTable or LuaFunction<R(...)> not available");
	}
};

template<typename T>
struct popper
{
	static T pop(std::tr1::shared_ptr<lua_State> state)
	{
		static_assert(sizeof(T) == 0, "returns types other than signed or unsigned char, short, int, long, LuaCoroutine,, LuaTable or LuaFunction<R(...)> not available" );
	}
};


// This unusually complicated define is just for the benefit of wstring
DEFINE_TYPE_TEMPLATE_FOR(std::wstring,, 									\
																			\
		std::string s;														\
		s.assign(param.begin(), param.end());								\
		lua_pushlstring(state.get(), s.c_str(), param.length());			\
	, 																		\
																			\
		std::string ss = lua_tostring(state.get(), -1);						\
		std::wstring res;													\
		res.assign(ss.begin(), ss.end());									\
	)

template<typename TYPE>
class LuaUserdata;

// LuaCppInterface's types
DEFINE_TYPE_TEMPLATE_FOR(LuaUserdata<TYPE>, typename TYPE, param.PushToStack(), LuaUserdata<TYPE> res(state,-1))
DEFINE_TYPE_TEMPLATE_FOR(LuaFunction<SIG>, typename SIG, param.PushToStack(), LuaFunction<SIG> res(state, -1))
DEFINE_TYPE_TEMPLATE_FOR(LuaTable,, param.PushToStack(), LuaTable res(state,-1))
DEFINE_TYPE_TEMPLATE_FOR(LuaCoroutine,, param.PushToStack(), LuaCoroutine res(state,-1))

// stdlib's types
DEFINE_TYPE_TEMPLATE_FOR(std::string,, lua_pushlstring(state.get(), param.c_str(), param.length()), std::string res = lua_tostring(state.get(), -1))

// strings!
DEFINE_TYPE_TEMPLATE_FOR(const char*,, lua_pushstring(state.get(), param), const char* res = lua_tostring(state.get(), -1))
DEFINE_TYPE_TEMPLATE_FOR(char*,, lua_pushstring(state.get(), param), char* res = (char*)lua_tostring(state.get(), -1))

// primitive types
DEFINE_TYPE_TEMPLATE_FOR(int8_t,, lua_pushinteger(state.get(), param), int8_t res = lua_tointeger(state.get(), -1))
DEFINE_TYPE_TEMPLATE_FOR(int16_t,, lua_pushinteger(state.get(), param), int16_t res = lua_tointeger(state.get(), -1))
DEFINE_TYPE_TEMPLATE_FOR(int32_t,, lua_pushinteger(state.get(), param), int32_t res = lua_tointeger(state.get(), -1))
DEFINE_TYPE_TEMPLATE_FOR(int64_t,, lua_pushinteger(state.get(), param), int64_t res = lua_tointeger(state.get(), -1))

DEFINE_TYPE_TEMPLATE_FOR(uint8_t,, lua_pushunsigned(state.get(), param), uint8_t res = lua_tounsigned(state.get(), -1))
DEFINE_TYPE_TEMPLATE_FOR(uint16_t,, lua_pushunsigned(state.get(), param), uint16_t res = lua_tounsigned(state.get(), -1))
DEFINE_TYPE_TEMPLATE_FOR(uint32_t,, lua_pushunsigned(state.get(), param), uint32_t res = lua_tounsigned(state.get(), -1))
DEFINE_TYPE_TEMPLATE_FOR(uint64_t,, lua_pushunsigned(state.get(), param), uint64_t res = lua_tounsigned(state.get(), -1))

DEFINE_TYPE_TEMPLATE_FOR(float,, lua_pushnumber(state.get(), param), float res = lua_tonumber(state.get(), -1))
DEFINE_TYPE_TEMPLATE_FOR(double,, lua_pushnumber(state.get(), param), double res = lua_tonumber(state.get(), -1))

DEFINE_TYPE_TEMPLATE_FOR(bool,, lua_pushboolean(state.get(), param), bool res = lua_toboolean(state.get(), -1) != 0)


// Special type templates for string literals
template<size_t N>																
struct pusher<const char[N]>															
{																			
	static void push(std::tr1::shared_ptr<lua_State> state, const char* param)		
	{																		
		lua_pushstring(state.get(), param);														
	}																		
};																			
																			
template<size_t N>																
struct popper<const char[N]>															
{																			
	static const char* pop(std::tr1::shared_ptr<lua_State> state)					
	{					
		const char* res = lua_tostring(state.get(), -1);
		lua_pop(state.get(), 1);											
		return res;															
	}																		
};

template<size_t N>																
struct pusher<char[N]>															
{																			
	static void push(std::tr1::shared_ptr<lua_State> state, const char* param)		
	{																		
		lua_pushstring(state.get(), param);														
	}																		
};																			
																			
template<size_t N>																
struct popper<char[N]>															
{																			
	static char* pop(std::tr1::shared_ptr<lua_State> state)					
	{					
		char* res = (char*)lua_tostring(state.get(), -1);
		lua_pop(state.get(), 1);											
		return res;															
	}																		
};

#endif // LUATYPETEMPLATES_H
