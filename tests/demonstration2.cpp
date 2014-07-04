#include <memory>
#include <luacppinterface.h>
#include <sstream>

std::stringstream ss;

void m()
{
	ss << "called function m ";
}

void m2()
{
	ss << "called function m2 ";
}

int main()
{
	Lua lua;
	auto global = lua.GetGlobalEnvironment();
	auto params = lua.CreateTable();
	params.Set("big", 15);

	typedef void(*func_t)();

	func_t fun = m2;

	//omg<int()>::callfunc();
	//omg<int(std::string)>::callfunc();

	auto absolute = lua.CreateFunction<int(int)>((int(*)(int))abs);
	int magnitude = absolute.Invoke(-5);

	auto afunc = lua.CreateFunction<void()>([&]()
	{
		ss << "called function ";
	});

	afunc.Invoke();

	auto afunc2 = lua.CreateFunction<void()>(m);
	afunc2.Invoke();

	auto afunc3 = lua.CreateFunction<void()>(fun);
	afunc3.Invoke();

	auto t = lua.CreateFunction<void(int)>([&](int a)
	{
	});

	t.Invoke(5);
	
	auto t1 = lua.CreateFunction<void(std::string)>([&](std::string a)
	{
	});

	t1.Invoke("meow");

	auto t2 = lua.CreateFunction<void(int,std::string)>([&](int a, std::string)
	{
	});

	t2.Invoke(5,"a");

	auto t3 = lua.CreateFunction<int(int,std::string)>([&](int a, std::string) -> int
	{
		return 10;
	});

	t3.Invoke(5,"a");

	auto thefunc = [&](LuaTable table) -> LuaTable
	{ 
		ss << "momo";
		return table;
	};
	
	auto add2 = lua.CreateFunction<int(int)>([&](int a) -> int
	{
		return a + 2;
	});

	t.Invoke(5);

	auto frunc = lua.CreateFunction<LuaTable(LuaTable)>(thefunc);
	global.Set("thefunc", frunc);
		
	global.Set("attack", lua.CreateFunction<int(int,int)>(
		[&](int a, int b) -> int
		{
			return a + b;
		}
	));

	global.Set("add2", add2);

	lua.RunScript(
		"x = thefunc({a=add2(10)})\n"
		""
		"function meow (a) \n"
		"  a.big = a.big + x.a\n"
		"  return a\n"
		"end\n"

		"function onetwofour() \n"
		"  return 124\n"
		"end\n"
		""
		"function getmeow()\n"
		"  return meow\n"
		"end\n"
		""
		"attack(1,2)"

		);
	
	auto meow = global.Get< LuaFunction<LuaTable(LuaTable)> >("meow");

	auto result = meow.Invoke(params);
	int big = result.Get<int>("big");

	auto onetwofour = global.Get< LuaFunction<int()> >("onetwofour");
	int res = onetwofour.Invoke();
	
	auto getmeow = global.Get< LuaFunction<LuaFunction<LuaTable(LuaTable)>()> >("getmeow");
	auto fmeow = getmeow.Invoke();
	auto fres = fmeow.Invoke(params);

	auto number = fres.Get<int>("big");
	
	if (number == 39 && 
		res == 124 &&
		ss.str().compare("called function m called function m2 called function momo")
		)
	{
		return 0;
	}
	
	return 1;
}
