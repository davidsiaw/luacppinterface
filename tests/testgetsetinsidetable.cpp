// Simple example of how to use a lua table

#include <boost/tr1/memory.hpp>
#include <luacppinterface.h>

int main()
{
	Lua lua;
	auto table = lua.CreateTable();

	table.SetString("name", "astrobunny");
	table.SetInteger("age", 15);

	table.SetString(1, "something");
	table.SetInteger(2, 100);

	// In lua numbers and strings are NOT THE SAME
	table.SetString("3", "keyIsString");
	table.SetString(3, "keyIsNumber");

	if (table.GetString("name").compare("astrobunny") != 0)
	{
		return 1;
	}
	
	if (table.GetInteger("age") != 15)
	{
		return 2;
	}

	if (table.GetString(1).compare("something") != 0)
	{
		return 3;
	}

	if (table.GetInteger(2) != 100)
	{
		return 4;
	}
	
	if (table.GetString("3").compare("keyIsString") != 0)
	{
		return 5;
	}

	if (table.GetString(3).compare("keyIsNumber") != 0)
	{
		return 6;
	}

	return 0;
}
