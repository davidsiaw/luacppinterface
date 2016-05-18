#include "luaerror.h"

#include <sstream>

std::string LuaGetLastError(lua_State* state)
{
	std::stringstream ss;
	for (int level = 1; level <= lua_gettop(state); level++)
	{
		const char* errorMessage = lua_tostring(state, level);
		if (errorMessage)
		{
			ss << "Error: " << errorMessage << std::endl;
		}
	}

	luaL_traceback(state, state, NULL, 1);
	printf("%s\n", lua_tostring(state, -1));

	lua_Debug debugInfo;
	for (int level = 0; lua_getstack(state, level, &debugInfo); level++)
	{
		lua_getinfo(state, "nSlf", &debugInfo);
		ss << "Line: " << debugInfo.currentline << std::endl;
		ss << "Source: " << debugInfo.short_src << std::endl;

		lua_getinfo(state, ">nS", &debugInfo);
		const char* function = debugInfo.name;
		if (function)
		{
			ss << "Function: " << function << std::endl;
		}
	}

	return ss.str();
}