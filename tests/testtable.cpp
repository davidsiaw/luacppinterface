// Simple example of how to create a lua table

#include <boost/tr1/memory.hpp>
#include <luacppinterface.h>

int main()
{
	Lua lua;

	auto table = lua.CreateTable();

	return 0;
}
