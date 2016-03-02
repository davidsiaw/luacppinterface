#pragma once
#ifndef LUACPPERROR
#define LUACPPERROR

#include <stdexcept>
#include "luacppinclude.h"

struct LuaException : public std::logic_error
{
	LuaException::LuaException(const char* e = "UnknownLuaException") : std::logic_error(e)
	{};
};

struct LuaNil : public LuaException
{
	LuaNil::LuaNil() : LuaException("LuaNil")
	{};
};

std::string LuaGetLastError(lua_State* state);

#endif // LUACPPERROR