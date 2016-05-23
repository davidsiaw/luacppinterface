// This is how you construct a function

#include <iostream>
#include <memory>
#include <luacppinterface.h>

int returnsFive()
{
	return 5;
}

int main()
{
	Lua lua;

	LuaFunction<int()> fun(lua, returnsFive);

	return fun.Invoke() != 5;
}
