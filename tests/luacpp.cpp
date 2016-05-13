#include <iostream>
#include <sstream>
#include "luacppinterface.h"

void m()
{
	std::cout << "called function m" << std::endl;
}

void m2()
{
	std::cout << "called function m2" << std::endl;
}

class Bar
{
	int number;
public:
	Bar(int number)
	{
        std::cout << "Bar" << number << " is created" << std::endl;
		this->number = number;
	}

	int GetNumber()
	{
		return number;
	}

	~Bar()
	{
        std::cout << "Bar" << number << " is destroyed" << std::endl;
	}
};

class Foo
{
public:
    Foo(const std::string & name) : name(name)
    {
        std::cout << name << " is born" << std::endl;
    }

	std::string Identify(Bar* bar)
	{
        std::stringstream ss;
		ss << name << " number is: " << bar->GetNumber();
        return ss.str();
	}

    std::string Add(int a, int b)
    {
        std::stringstream ss;
        ss << name << ": " << a << " + " << b << " = " << (a+b);
        return ss.str();
    }

    ~Foo()
    {
        std::cout << name << " is gone" << std::endl;
    }

private:
    std::string name;
};

LuaUserdata<Foo> fooConstructor(Lua lua, std::string str)
{
	auto foo = new Foo(str);
	auto userData = lua.CreateUserdata<Foo>(foo);

	userData.Bind("add", &Foo::Add);
	userData.Bind("identify", &Foo::Identify);

	return userData;
}

LuaUserdata<Bar> barConstructor(Lua lua, int number)
{
	auto bar = new Bar(number);
	auto userData = lua.CreateUserdata<Bar>(bar);

	userData.Bind("getNumber", &Bar::GetNumber);

	return userData;
}

int main()
{
	Lua lua;
	lua.LoadStandardLibraries();
	auto global = lua.GetGlobalEnvironment();


	auto newFoo = lua.CreateFunction<LuaUserdata<Foo>(std::string)>(std::bind(&fooConstructor, lua, std::placeholders::_1));
	auto footable = lua.CreateTable();
	footable.Set("new", newFoo);
	global.Set("Foo", footable);


	auto newBar = lua.CreateFunction<LuaUserdata<Bar>(int)>(std::bind(&barConstructor, lua, std::placeholders::_1));
	auto bartable = lua.CreateTable();
	bartable.Set("new", newBar);
	global.Set("Bar", bartable);

	auto ress = lua.RunScript(
		"local foo1 = Foo:new('Hello')\n"
		"print(foo1.add(1,2))\n"
		"foo1 = Foo:new('paha1')\n"
		"print(foo1.identify(Bar:new(100)))"
		"foo1 = Foo:new('paha2')\n"
		"print(foo1.add(5,2))\n"
		"foo1 = Foo:new('paha3')\n"
		"foo1 = Foo:new('paha4')\n"
		"foo1 = nil\n"
		"collectgarbage()\n"
		);
    
    std::cout << ress << std::endl;

	auto params = lua.CreateTable();
	params.Set("big", 15);

	global.Set("name", "astrobunny");

	typedef void(*func_t)();

	func_t fun = m2;

	//omg<int()>::callfunc();
	//omg<int(std::string)>::callfunc();

	auto absolute = lua.CreateFunction<int(int)>((int(*)(int))abs);
	int magnitude = absolute.Invoke(-5);

	auto afunc = lua.CreateFunction<void()>([&]()
	{
		std::cout << "called function" << std::endl;
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
		std::cout << "momo" << std::endl;
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
    
    LuaTable tbl = lua.CreateTable();
    tbl.Set("name", "Chuck Norris");
    tbl.Set("age", 1337);
    tbl.Set("0", "divide by");
    tbl.Set(1337, "leet");
    
    int keys = 3;
    
    tbl.ForAllStringKeys([&](std::string key, LuaType::Value value)
    {
        keys--;
    });
    
	auto meow = global.Get< LuaFunction<LuaTable(LuaTable)> >("meow");

	auto result = meow.Invoke(params);
	int big = result.Get<int>("big");

	auto onetwofour = global.Get< LuaFunction<int()> >("onetwofour");
	int res = onetwofour.Invoke();

	auto getmeow = global.Get< LuaFunction<LuaFunction< LuaTable(LuaTable) >() > >("getmeow");
	auto fmeow = getmeow.Invoke();
	auto fres = fmeow.Invoke(params);

	auto number = fres.Get<int>("big");

	Lua luaInstance;
	auto globalTable = luaInstance.GetGlobalEnvironment();
	auto myOwnPrint = luaInstance.CreateYieldingFunction<void(std::string)>
		(
			[](std::string str)
			{
				std::cout << str << std::endl;
			}
		);

	globalTable.Set("myownprint", myOwnPrint);

	luaInstance.LoadStandardLibraries();

	auto cr = luaInstance.CreateCoroutine();


	auto err = cr.RunScript(
		"	myownprint 'hello'\n"
		"	myownprint 'hello2'\n"
		"	myownprint 'hello3'\n"
		);

	while (cr.CanResume())
	{
		std::cout << "yield" << std::endl;
		auto err = cr.Resume();
	}

	Lua l3;
	auto glob3 = l3.GetGlobalEnvironment();

	std::stringstream ss;

	auto formattedPrint = l3.CreateFunction<void(std::string, LuaTable)>
	(
		[&](std::string format, LuaTable objects)
		{
			int token = 1;
			std::string::size_type offset = 0;
			std::string::size_type n;
			do
			{
				n = format.substr(offset).find("%");
				ss << format.substr(offset, n);
				if (n == std::string::npos)
				{
					return;
				}
				else if (n + 1 >= format.size())
				{
					// percent at end
					ss << "%";
					return;
				}
				else if (format[offset+n+1] == 's')
				{
					// string
					ss << objects.Get<std::string>(token);
					token++;
				}
				else if (format[offset+n+1] == 'd')
				{
					// integer
					ss << objects.Get<int>(token);
					token++;
				}
				else
				{
					// unknown. Print.
					ss << format.substr(offset, 2);
				}
				offset += n+2;
			}
			while (offset < format.length());

			// remaining
			ss << format.substr(offset) << std::endl;
		}
	);

	glob3.Set("print", formattedPrint);
	auto error = l3.RunScript("print('This is %s %s %s %s %d %d %d!', {'hello', 'kitty', 'island', 'adventure', 1, 2, 3});");
	//l3.RunScript("a = {'ss', 'bb'}");

	auto resstr = ss.str();
	if (resstr.compare("This is hello kitty island adventure 1 2 3!") == 0)
	{
		int a =0;
	}


	//auto atable = glob3.GetTable("a");
	//auto str = atable.GetString(1);


	return 0;
}
