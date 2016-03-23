#ifndef LUACPPERROR
#define LUACPPERROR

#include "luacppinclude.h"

#include <exception>
#include <string>

class LuaError : public std::exception
{
public:
	LuaError(const char* message) : std::exception()
	{
	};
};

class LuaNil : public LuaError
{
public:
	LuaNil() : LuaError("Nil Value")
	{
	};
};

std::string LuaGetLastError(lua_State* state);

#endif // LUACPPERROR