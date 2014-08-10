// Simple example of getting the registry

#include <iostream>
#include <sstream>
#include <memory>
#include <luacppinterface.h>

int main()
{
	Lua lua;

	LuaTable registry = lua.GetRegistry();

	return 0;
}
