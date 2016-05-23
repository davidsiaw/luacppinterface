// This is how you construct a coroutine

#include <iostream>
#include <memory>
#include <luacppinterface.h>

int main()
{
	Lua lua;

	LuaCoroutine thread(lua);

	return 0;
}
