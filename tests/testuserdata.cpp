// Simple example of how to create a userdata instance

#include <boost/tr1/memory.hpp>
#include <luacppinterface.h>

class SomeClass
{
};

int main()
{
	Lua lua;

	auto userdata = lua.CreateUserdata<SomeClass>(new SomeClass());

	return 0;
}
