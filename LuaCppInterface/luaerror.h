#ifndef LUACPPERROR
#define LUACPPERROR

#include "luacppinclude.h"

#include <exception>
#include <string>

class LuaError : public std::exception
{
	std::string message;
public:
	LuaError(std::string message) : message(message), std::exception()
	{
	};

	std::string GetMessage() const
	{
		return message;
	}
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