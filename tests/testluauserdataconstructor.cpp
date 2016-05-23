// This is how you construct a userdata

#include <iostream>
#include <memory>
#include <luacppinterface.h>

class Cat
{
public:
	Cat()
	{

	}
};

int main()
{
	Lua lua;

	LuaUserdata<Cat> cat(lua, new Cat());

	return 0;
}
