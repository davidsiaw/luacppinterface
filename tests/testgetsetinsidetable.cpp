// Simple example of how to use a lua table

#include <memory>
#include <luacppinterface.h>

int main()
{
	Lua lua;
	auto table = lua.CreateTable();

	// Test const char* specialization
	const char* thething = "something";
	table.Set("thething", thething);
	
	const char* thething2 = "something2";
	table.Set("thething2", thething2);
	
	table.Set("name", "astrobunny");
	table.Set("age", 15);

	table.Set(1, "something");
	table.Set(2, 100);

	// In lua numbers and strings are NOT THE SAME
	table.Set("3", "keyIsString");
	table.Set(3, "keyIsNumber");

	if (table.Get<std::string>("name").compare("astrobunny") != 0)
	{
		return 1;
	}
	
	if (table.Get<int>("age") != 15)
	{
		return 2;
	}

	if (table.Get<std::string>(1).compare("something") != 0)
	{
		return 3;
	}

	if (table.Get<int>(2) != 100)
	{
		return 4;
	}
	
	if (table.Get<std::string>("3").compare("keyIsString") != 0)
	{
		return 5;
	}

	if (table.Get<std::string>(3).compare("keyIsNumber") != 0)
	{
		return 6;
	}

	return 0;
}
