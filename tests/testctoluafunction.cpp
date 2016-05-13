// Simple example using a regular C function

#include <iostream>
#include <memory>
#include <luacppinterface.h>

inline int basic_call(int x) {
	return x;
}

int main()
{
	Lua lua;
	auto global = lua.GetGlobalEnvironment();
	global.Set("f", lua.CreateFunction<int(int)>(basic_call));
	
	auto f = global.Get<LuaFunction<int(int)>>("f");

	auto result = f.Invoke(5);

	std::cout << result << std::endl;
	
	return result != 5;
}
