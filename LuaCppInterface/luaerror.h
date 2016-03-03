#pragma once
#ifndef LUACPPERROR
#define LUACPPERROR

#include "luacppinclude.h"

#include <exception>
#include <string>

struct LuaNil : public std::exception
{
	LuaNil::LuaNil() : std::exception("LuaNil")
	{};
};

std::string LuaGetLastError(lua_State* state);

#endif // LUACPPERROR