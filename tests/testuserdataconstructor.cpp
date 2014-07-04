// Simple example of how to create a userdata constructor

#include <iostream>
#include <memory>
#include <functional>
#include <luacppinterface.h>

class SomeClass
{
	int number;
public:
	SomeClass(int number)
	{
		this->number = number;
	}
	
	int GetNumber() const
	{
		return number;
	}
	
};

int main()
{
	Lua lua;

	auto global = lua.GetGlobalEnvironment();
	
	auto newSomeClass = lua.CreateFunction< LuaUserdata<SomeClass>(int) >(
	[&](int num) -> LuaUserdata<SomeClass>
	{
		auto sc = new SomeClass(num);
		auto userData = lua.CreateUserdata<SomeClass>(sc);
		
		using namespace std::placeholders;
		userData.Set("GetNumber", lua.CreateFunction< int() >( std::bind(&SomeClass::GetNumber, sc) ));
	
		return userData;
	});

	auto someClassStatic = lua.CreateTable();
	someClassStatic.Set("new", newSomeClass);

	global.Set("SomeClass", someClassStatic);
	
	lua.RunScript(
	"someclass = SomeClass:new(2)\n"
	"x = someclass.GetNumber()"
	);
	
	return 2 - global.Get<int>("x");
}
