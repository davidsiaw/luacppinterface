// This is how you construct a table

#include <iostream>
#include <memory>
#include <luacppinterface.h>

int main()
{
	Lua lua;

	LuaTable table(lua);

	table.Set("cat", "55");

	return table.Get<int>("cat") != 55;
}
