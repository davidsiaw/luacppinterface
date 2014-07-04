// Simple example of how to add methods to a userdata instance
// its similar to a table.

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

	SomeClass* sc = new SomeClass(1);
	auto userdata1 = lua.CreateUserdata<SomeClass>(sc);
	
	using namespace std::placeholders;
	userdata1.Set("GetNumber", lua.CreateFunction< int() >( std::bind(&SomeClass::GetNumber, sc) ));
	
	auto global = lua.GetGlobalEnvironment();
	
	global.Set("someclass", userdata1);
	
	lua.RunScript("x = someclass.GetNumber()");
	
	return 1 - global.Get<int>("x");
}
