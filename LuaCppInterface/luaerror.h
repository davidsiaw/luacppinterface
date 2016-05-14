#ifndef LUACPPERROR
#define LUACPPERROR

#include "luacppinclude.h"

#include <exception>
#include <string>

class LuaError : public std::exception
{
	std::string msg;
public:
	LuaError(std::string msg) : msg(msg)
	{

	}

	~LuaError() throw()
	{

	}

	const std::string& GetMessage() const
	{
		return msg;
	}
};

std::string LuaGetLastError(lua_State* state);

#endif // LUACPPERROR