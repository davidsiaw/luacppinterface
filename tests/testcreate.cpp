// Simple example of how to start using LuaCppInterface

#include <memory>
#include <luacppinterface.h>

int main()
{
	// You can use it on the stack
	Lua lua;

	// Or as a pointer
	Lua* luap = new Lua();
	delete luap;

	// Or as a boost/c++11 shared_pointer
	std::shared_ptr<Lua> luasp(new Lua());

	return 0;
}
