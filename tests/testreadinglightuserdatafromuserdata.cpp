// Simple test for loading a Userdata as LightUserdata

#include <iostream>
#include <memory>
#include <luacppinterface.h>

class Data
{
	int value;
public:
	Data(int value) : value(value) {}

	int GetValue() const { return value; }
};

int main()
{
	Lua lua;
	auto global = lua.GetGlobalEnvironment();

	auto userdata = lua.CreateUserdata<Data>(new Data(555));
	global.Set("data", userdata);

	auto lud = global.Get< LuaLightUserdata<Data> >("data");

	return lud->GetValue() != 555;
}
