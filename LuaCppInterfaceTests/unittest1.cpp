#include "stdafx.h"
#include "CppUnitTest.h"

#define FAIL_IF(x) return Assert::IsFalse(x);

// ============================================================================
// WARNING: THIS FILE IS GENERATED FROM THE TEST SOURCES IN THE tests FOLDER. 
// Run generate.rb to update
// ============================================================================

#include <memory>

#include <luacppinterface.h>

#include <sstream>

#include <iostream>


#include <sstream>


#include <fstream>

#include <streambuf>

#include <string>

#include <iostream>

#include <luacppinterface.h>


#include <iostream>

#include <memory>

#include <luacppinterface.h>


#include <sstream>

#include <luacppinterface.h>

#include <sstream>


#include <functional>


using namespace Microsoft::VisualStudio::CppUnitTestFramework;


namespace section_demonstration1
{
	int main()
	{
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
						ss<< "%";
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
				std::cout << format.substr(offset) << std::endl;
			}
		);
		
		glob3.Set("print", formattedPrint);
		auto error = l3.RunScript("print('This is %s %s %s %s %d %d %d!', {'hello', 'kitty', 'island', 'adventure', 1, 2, 3});");
		
		auto resstr = ss.str();
		
		return resstr.compare("This is hello kitty island adventure 1 2 3!");
	}

}

namespace section_demonstration2
{
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

}

namespace section_demonstration3
{
	int main()
	{
		Lua luaInstance;
		std::stringstream ss;
		auto globalTable = luaInstance.GetGlobalEnvironment();
		auto myOwnPrint = luaInstance.CreateYieldingFunction<void(std::string)>
			(
				[&](std::string str)
				{
					ss << str;
				}
			);
	
		globalTable.Set("myownprint", myOwnPrint);
	
		luaInstance.LoadStandardLibraries();
	
		auto cr = luaInstance.CreateCoroutine();
	
		auto err = cr.RunScript(
			"	myownprint 'hello '\n"
			"	myownprint 'hello2 '\n"
			"	myownprint 'hello3 '\n"
			);
		
		while (cr.CanResume())
		{
			ss << "yield ";
			auto err = cr.Resume();
		}
		
		auto resstr = ss.str();
		
		return resstr.compare("hello yield hello2 yield hello3 yield ");
	}

}

namespace section_demonstration4
{
	int main()
	{
	  std::ifstream file("config.lua");
	  std::string script((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
	  Lua lua;
	  lua.RunScript(script);
	  int width = lua.GetGlobalEnvironment().Get<int>("width");    // get the width
	  int height = lua.GetGlobalEnvironment().Get<int>("height");  // get the height
	  std::string windowTitle = lua.GetGlobalEnvironment().Get<std::string>("windowTitle");
	
	  return width != 640 || height != 480 || windowTitle.compare("Lua Rocks");
	}

}

namespace section_luacpp
{
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

}

namespace section_testcallabletable
{
	// Simple test that shows that a table can be a function
	
	int main()
	{
		Lua lua;
		lua.LoadStandardLibraries();
		auto global = lua.GetGlobalEnvironment();
		
		// Write a function in Lua
		lua.RunScript("\
			mt = {\
				__call = function ()\
					return 4;\
				end\
			}\
			\
			myTable = {}\
			setmetatable(myTable, mt)\
		");
	
		auto myFunction = global.Get< LuaFunction<int()> >("myTable");
		return myFunction.Invoke() != 4;
	}

}

namespace section_testchartowideconvert
{
	// Test converting a std::string to std::wstring
	
	int main()
	{
		std::string utf8str("ABC\xCE\x99\xCE\xBF\xCF\x8D\xCE\xBD\xCE\xB9\xCE\xBA\xCE\xBF\xCE\xBD\xCF\x84\x00");
		std::wstring wstr(L"ABC\u0399\u03BF\u03CD\u03BD\u03B9\u03BA\u03BF\u03BD\u03C4");
	
		auto conv = UTF8ToWStr(utf8str);
		if (conv == wstr)
		{
			return 0;
		}
	
	
		std::cout << "Expect: ";
		for (int i=0;i<wstr.size();i++)
		{
			std::cout << (unsigned int)wstr[i] << " ";
		}
		std::cout << " " << wstr.size();
		std::cout << std::endl;
	
		std::cout << "Result: ";
		for (int i=0;i<conv.size();i++)
		{
			std::cout << (unsigned int)conv[i] << " ";
		}
		std::cout << " " << conv.size();
		std::cout << std::endl;
		return 1;
	}

}

namespace section_testcoroutineexception
{
	// Test running a script that will fail in a coroutine
	
	int main()
	{
		Lua lua;
		auto global = lua.GetGlobalEnvironment();
	
		auto coroutine = lua.CreateCoroutine();
	
		auto result = coroutine.RunScript("meow()");
	
		std::cout << result << std::endl;
	
		if (result == "No errors")
		{
			return 1;
		}
	
		return 0;
	}

}

namespace section_testcoroutineexpectedbutnot
{
	// Simple demonstration that you will get an error if you try an extract a coroutine from a table
	
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
		lua.LoadStandardLibraries();
		auto global = lua.GetGlobalEnvironment();
	
		lua.RunScript("\
			function x()\
				return \"meow\"\
			end\
		");
	
		try
		{
			global.Get< LuaCoroutine >("x");
			return 1;
		}
		catch(LuaError e)
		{
			std::cout << e.GetMessage() << std::endl;
			return e.GetMessage() != "Error: thread expected, got function\nError: bad argument #-1 (thread expected, got function)\n";
		}
	
		return 2;
	}

}

namespace section_testcreate
{
	// Simple example of how to start using LuaCppInterface
	
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

}

namespace section_testctoluafunction
{
	// Simple example using a regular C function
	
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

}

namespace section_testexceptioninluafunction
{
	// Exception in a lua function
	
	int main()
	{
		Lua lua;
		
		auto coroutine = lua.CreateCoroutine();
		
		// Use it in a script!
		std::string result = coroutine.RunScript(
			"function blow_up()\n"
			"  meow()\n"
			"end\n"
			"blow_up()"
			);
	
		std::cout << result << std::endl;
	
		if ("No Errors" == result)
		{
			return 1;
		}
	
		return 0;
	}

}

namespace section_testextractingasfunctionbutistable
{
	// Simple test that shows getting a table that is not callable as a function will yield an error
	
	int main()
	{
		Lua lua;
		auto global = lua.GetGlobalEnvironment();
		
		// Write a function in Lua
		lua.RunScript("\
			myTable = {}\
		");
	
		try
		{
			auto myFunction = global.Get< LuaFunction<void()> >("myTable");
		}
		catch(LuaError e)
		{
			std::cout << e.GetMessage() << std::endl;
			return e.GetMessage() != "Error: failed to get metatable\n";
		}
		return 0;
	}

}

namespace section_testfunction
{
	// Simple example of how to use a lua function
	
	int main()
	{
		std::stringstream ss;
	
		Lua lua;
		auto global = lua.GetGlobalEnvironment();
		
		// We make a print function that writes to a string stream
		auto leprint = lua.CreateFunction<void()>(
			[&]()
			{
				ss << "ROFLMAO";
			}
		);
	
		// Set the global to print
		global.Set("leprint", leprint);
		
		// Use it in a script!
		lua.RunScript("leprint ()");
	
		return ss.str().compare("ROFLMAO");
	}

}

namespace section_testfunctionerror
{
	// Test running a script that has a few functions and fails
	
	
	int main()
	{
		Lua lua;
		auto global = lua.GetGlobalEnvironment();
	
		auto function = lua.CreateFunction< void() >([&]()
		{
			global.Set("x", 5);
			auto table = global.Get<LuaTable>("x");
			table.Set("a", 5);
		});
	
	
		auto function2 = lua.CreateFunction< void() >([&]()
		{
			global.Get< LuaFunction<void()> >("meow").Invoke();
		});
	
	
		global.Set("func", function);
		global.Set("func2", function2);
	
		lua.RunScript("\
			\
			woof = function ()\
				func2()\
			end\
			\
			function meow()\
				func()\
			end\
		");
	
		try
		{
			global.Get< LuaFunction<void()> >("woof").Invoke();
			std::cout << LuaGetLastError(function.GetState().get()) << std::endl;
		}
		catch(LuaError e)
		{
			std::cout << e.GetMessage() << std::endl;
		}
	
		return 0;
	}

}

namespace section_testfunctionexpectedbutnotcallable
{
	// Simple demonstration that you will get an error if you try an extract a function from a non-callable object
	
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
		lua.LoadStandardLibraries();
		auto global = lua.GetGlobalEnvironment();
	
		lua.RunScript("\
			x = {}\
			setmetatable(x, {})\
		");
	
		try
		{
			global.Get< LuaFunction<int()> >("x");
			return 1;
		}
		catch(LuaError e)
		{
			std::cout << e.GetMessage() << std::endl;		
			return e.GetMessage() != "Error: function or callable object expected, got table\nError: bad argument #-1 (function or callable object expected, got table)\n";
		}
	
		return 2;
	}

}

namespace section_testfunctionparams
{
	// Simple example of how to use a lua function with parameters
	
	int main()
	{
		std::stringstream ss;
	
		Lua lua;
		auto global = lua.GetGlobalEnvironment();
		
		// We make a print function that writes to a string stream
		auto leprint = lua.CreateFunction<void(std::string)>(
			[&](std::string str)
			{
				ss << str;
			}
		);
	
		// Set the global to print
		global.Set("leprint", leprint);
		
		// Use it in a script!
		lua.RunScript("leprint 'hello'");
	
		return ss.str().compare("hello");
	}

}

namespace section_testfunctionparamsreturn
{
	// Simple example of how to use a lua function with parameters and use the return value
	
	int main()
	{
		Lua lua;
		auto global = lua.GetGlobalEnvironment();
		
		// We make a print function that writes to a string stream
		auto strangeAdd = lua.CreateFunction<int(int, int)>(
			[&](int a, int b) -> int
			{
				return a ^ b + a;
			}
		);
	
		// Add our function to the global state
		global.Set("strangeAdd", strangeAdd);
		
		// Use it in a script!
		lua.RunScript("x = strangeAdd (5,6)");
		
		int x = global.Get<int>("x");
	
		return x != (strangeAdd.Invoke(5,6)) || x != (5^5+6);
	}

}

namespace section_testfunctionreturn
{
	// Simple example of how to use a lua function written in a script
	
	int main()
	{
		Lua lua;
		auto global = lua.GetGlobalEnvironment();
		
		// Write a function in Lua
		lua.RunScript(
			"function addTwo(a)\n"
			"  return a+2\n"
			"end\n"
		);
	
		auto addTwo = global.Get< LuaFunction<int(int)> >("addTwo");
		
		return addTwo.Invoke(5) != 7;
	}

}

namespace section_testgetmetatableonclosedstate
{
	// Try and get a metatable of a table that was unreffed (abuse)
	
	int main()
	{
		Lua lua;
	
		auto table = lua.CreateTable();
	
		auto state = table.GetState();
		table.PushToStack(state.get());
		auto ref = luaL_ref(state.get(), LUA_REGISTRYINDEX);
		luaL_unref(state.get(), LUA_REGISTRYINDEX, ref);
		luaL_unref(state.get(), LUA_REGISTRYINDEX, ref);
	
		try
		{
			auto metatable = table.GetMetaTable();
		}
		catch(LuaError e)
		{
			std::cout << e.GetMessage() << std::endl;
			return e.GetMessage() != "Error: failed to get metatable\n";
		}
	
		return 1;
	}

}

namespace section_testgetnullstring
{
	// Simple test showing getting a null string gives you an empty string
	
	int main()
	{
		Lua lua;
		auto global = lua.GetGlobalEnvironment();
	
		lua.RunScript("\
			nullString = nil\
		");
	
		return global.Get<std::string>("nullString") != "";
	}

}

namespace section_testgetnulltable
{
	// Simple test showing getting a null table throws a lua error
	
	int main()
	{
		Lua lua;
		auto global = lua.GetGlobalEnvironment();
	
		lua.RunScript("\
			nullTable = nil\
		");
	
		try
		{
			global.Get<LuaTable>("nullTable");
			return 1;
		}
		catch(LuaError e)
		{
			std::cout << e.GetMessage() << std::endl;
			return 0;
		}
		return 1;
	}

}

namespace section_testgetnullwstring
{
	// Simple test showing getting a null string gives you an empty string
	
	int main()
	{
		Lua lua;
		auto global = lua.GetGlobalEnvironment();
	
		lua.RunScript("\
			nullString = nil\
		");
	
		return global.Get<std::wstring>("nullString") != L"";
	}

}

namespace section_testgetsetfunction
{
	// Simple example of getting and setting a function
	
	int main()
	{
		Lua lua;
		auto global = lua.GetGlobalEnvironment();
		
		// Write a function in Lua
		lua.RunScript(
			"function compute(a)\n"
			"  return a*2\n"
			"end\n"
		);
	
		auto originalCompute = global.Get< LuaFunction<int(int)> >("compute");
		
		// Write an alternative implementation
		
		auto alternativeCompute = lua.CreateFunction< int(int) >(
			[](int a) -> int
			{
				return a + 2;
			}
		);
		
		global.Set("compute", alternativeCompute);
	
		auto originalResult = originalCompute.Invoke(15);
		auto alternativeResult = alternativeCompute.Invoke(5);
	
		std::cout << "originalResult=" << originalResult << std::endl;
		std::cout << "alternativeResult=" << alternativeResult << std::endl;
	
		return originalResult != 30 || alternativeResult != 7;
	}

}

namespace section_testgetsetfunction2
{
	// Simple example of putting a function in C++ and taking it back out
	
	int main()
	{
		Lua lua;
		auto global = lua.GetGlobalEnvironment();
		
		auto addTwo = lua.CreateFunction< int(int) >(
			[](int a) -> int
			{
				return a + 2;
			}
		);
		global.Set("addTwo", addTwo);
	
		auto insideAddTwo = global.Get< LuaFunction<int(int)> >("addTwo");
	
		std::cout << insideAddTwo.Invoke(5) << std::endl;
		std::cout << addTwo.Invoke(15) << std::endl;
		
		
		return insideAddTwo.Invoke(5) != 7 || addTwo.Invoke(15) != 17;
	}

}

namespace section_testgetsetinsidetable
{
	// Simple example of how to use a lua table
	
	int main()
	{
		Lua lua;
		auto table = lua.CreateTable();
	
		// Test const char* specialization
		const char* thething = "something";
		table.Set("thething", thething);
		
		const char* thething2 = "something2";
		table.Set("thething2", thething2);
		
		table.Set("name", "astrobunny");
		table.Set("age", 15);
	
		table.Set(1, "something");
		table.Set(2, 100);
	
		// In lua numbers and strings are NOT THE SAME
		table.Set("3", "keyIsString");
		table.Set(3, "keyIsNumber");
	
		if (table.Get<std::string>("name").compare("astrobunny") != 0)
		{
			return 1;
		}
		
		if (table.Get<int>("age") != 15)
		{
			return 2;
		}
	
		if (table.Get<std::string>(1).compare("something") != 0)
		{
			return 3;
		}
	
		if (table.Get<int>(2) != 100)
		{
			return 4;
		}
		
		if (table.Get<std::string>("3").compare("keyIsString") != 0)
		{
			return 5;
		}
	
		if (table.Get<std::string>(3).compare("keyIsNumber") != 0)
		{
			return 6;
		}
	
		return 0;
	}

}

namespace section_testgetsetinteger
{
	// Simple example of getting and setting a global variable
	
	int main()
	{
		Lua lua;
		auto global = lua.GetGlobalEnvironment();
		
		global.Set("someThing", 5);
		
		return global.Get<int>("someThing") != 5;
	}

}

namespace section_testgetsetstring
{
	// Simple example of getting and setting a global variable
	
	int main()
	{
		Lua lua;
		auto global = lua.GetGlobalEnvironment();
		
		global.Set("someThing", "five");
		
		return global.Get<std::string>("someThing").compare("five");
	}

}

namespace section_testgetsettable
{
	// Simple example of getting and setting a global variable
	
	int main()
	{
		Lua lua;
		auto global = lua.GetGlobalEnvironment();
		
		auto table = lua.CreateTable();
		table.Set("someThing", "five");
		
		global.Set("mytable", table);
		
		return global.Get<LuaTable>("mytable").Get<std::string>("someThing").compare("five");
	}

}

namespace section_testgetstate
{
	// Simple test to get state from object
	
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
	
		lua.RunScript("\
			function retfive()\
				return 123\
			end\
		");
	
		auto table = lua.CreateTable();
	
		{
			Lua second(table.GetState());
			auto global = second.GetGlobalEnvironment();
	
			return global.Get< LuaFunction<int()> >("retfive").Invoke() != 123;
		}
	
	}

}

namespace section_testgettypeofvalueat
{
	// Simple example of getting the type of the value at a particular key
	
	int main()
	{
		Lua lua;
	
		LuaTable tbl = lua.CreateTable();
		tbl.Set("name", "Chuck Norris");
		tbl.Set("age", 1337);
		tbl.Set("0", "divide by");
		tbl.Set(1337, "leet");
	
		LuaType::Value nameType = tbl.GetTypeOfValueAt("name");
		LuaType::Value ageType = tbl.GetTypeOfValueAt("age");
		LuaType::Value zeroType = tbl.GetTypeOfValueAt("0");
		LuaType::Value leetType = tbl.GetTypeOfValueAt(1337);
	
		bool nameTypeIsCorrect = nameType == LuaType::string;
		bool ageTypeIsCorrect = ageType == LuaType::number;
		bool zeroTypeIsCorrect = zeroType == LuaType::string;
		bool leetTypeIsCorrect = leetType == LuaType::string;
	
		std::cout << "value of name is correct: " << nameTypeIsCorrect << std::endl;
		std::cout << "value of age is correct: " << ageTypeIsCorrect << std::endl;
		std::cout << "value of zero is correct: " << zeroTypeIsCorrect << std::endl;
		std::cout << "value of 1337 is correct: " << leetTypeIsCorrect << std::endl;
	
		if (nameTypeIsCorrect && 
			ageTypeIsCorrect && 
			zeroTypeIsCorrect && 
			leetTypeIsCorrect)
		{
			return 0;
		}
	
		return 1;
	}

}

namespace section_testinvalidscript
{
	// Simple example of what happens with an invalid script
	
	int main()
	{
		Lua lua;
		
		// Use it in a script!
		std::string result = lua.RunScript("g % 5 lalala meow");
	
		if ("Error: [string \"g % 5 lalala meow\"]:1: '=' expected near '%'\n" == result)
		{
			return 0;
		}
	
		return 1;
	}

}

namespace section_testluacoroutineconstructor
{
	// This is how you construct a coroutine
	
	int main()
	{
		Lua lua;
	
		LuaCoroutine thread(lua);
	
		return 0;
	}

}

namespace section_testluafunctionconstructor
{
	// This is how you construct a function
	
	int returnsFive()
	{
		return 5;
	}
	
	int main()
	{
		Lua lua;
	
		LuaFunction<int()> fun(lua, returnsFive);
	
		return fun.Invoke() != 5;
	}

}

namespace section_testluatableconstructor
{
	// This is how you construct a table
	
	int main()
	{
		Lua lua;
	
		LuaTable table(lua);
	
		table.Set("cat", "55");
	
		return table.Get<int>("cat") != 55;
	}

}

namespace section_testluauserdataconstructor
{
	// This is how you construct a userdata
	
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

}

namespace section_testpassingfunction
{
	// Simple example of passing functions around
	
	int main()
	{
		Lua lua;
		auto global = lua.GetGlobalEnvironment();
		
		auto add = lua.CreateFunction<int(int,int)>([&](int a, int b) -> int { return a + b; });
		auto multiply = lua.CreateFunction<int(int,int)>([&](int a, int b) -> int { return a * b; });
	
		global.Set("add", add);
		global.Set("multiply", multiply);
	
		// Run the script that chooses a function to return
		lua.RunScript(
			"function subtract(a,b)\n"
			"  return a - b\n"
			"end\n"
			""
			"function returnAnOperator()\n"
			"  return subtract\n"   // this can be either add, multiply or subtract
									// change it to see what happens!
			"end\n"
		);
	
		auto returnAnOperator = global.Get< 
				LuaFunction< 
					LuaFunction<int(int,int)>() 
				>
			>("returnAnOperator");
		
		auto anOperator = returnAnOperator.Invoke();
		auto result = anOperator.Invoke(10,10);
		
		return result;
	}

}

namespace section_testreadinglightuserdatafromuserdata
{
	// Simple test for loading a Userdata as LightUserdata
	
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

}

namespace section_testregistry
{
	// Simple example of getting the registry
	
	int main()
	{
		Lua lua;
	
		LuaTable registry = lua.GetRegistry();
	
		return 0;
	}

}

namespace section_testresumenoscript
{
	// Test that resuming a coroutine with no script will not work
	
	int main()
	{
		Lua lua;
		auto global = lua.GetGlobalEnvironment();
	
		auto coroutine = lua.CreateCoroutine();
	
		auto result = coroutine.Resume();
	
		std::cout << result << std::endl;
	
		if (result == "Error: attempt to call a nil value\nError: attempt to call a nil value\n")
		{
			return 0;
		}
	
		return 1;
	}

}

namespace section_testreturnfromnative
{
	// Simple example of a native function returning
	
	int main()
	{
		Lua lua;
		auto global = lua.GetGlobalEnvironment();
		
		auto add = lua.CreateFunction<int(int,int)>([&](int a, int b) -> int { return a + b; });
	
		global.Set("add", add);
	
		// Run the script that chooses a function to return
		lua.RunScript(
			"x = add(3,5)"
		);
	
		auto num = global.Get<int>("x");
		
		return num != 8;
	}

}

namespace section_testreturnfromscript
{
	// Simple example of a lua function returning
	
	int main()
	{
		Lua lua;
		auto global = lua.GetGlobalEnvironment();
		
		lua.RunScript(
			"function add(a,b)\n"
			"	return a+b\n"
			"end"
		);
		
		auto add = global.Get< LuaFunction<int(int,int)> >("add");
	
		auto num = add.Invoke(1,2);
		
		return num != 3;
	}

}

namespace section_testreturnfromyieldingfunction
{
	int main()
	{
		Lua luaInstance;
	
		auto globalTable = luaInstance.GetGlobalEnvironment();
		std::stringstream ss;
	
		auto myOwnPrint = luaInstance.CreateYieldingFunction<void(std::string)>
			(
				[&](std::string str)
				{
					ss << str;
				}
			);
	
		auto lengthOf = luaInstance.CreateYieldingFunction<int(std::string)>
			(
				[](std::string str) -> int
				{
					return str.size();
				}
			);
	
		globalTable.Set("myOwnPrint", myOwnPrint);
		globalTable.Set("lengthOf", lengthOf);
	
		luaInstance.LoadStandardLibraries();
	
		auto cr = luaInstance.CreateCoroutine();
	
		auto err = cr.RunScript(
			"x = lengthOf('haha')\n"
			"myOwnPrint ('size:' .. x)\n"
			);
		
		while (cr.CanResume())
		{
			ss << ";yield;";
			err = cr.Resume();
		}
		
		auto resstr = ss.str();
		
		return resstr.compare(";yield;size:4;yield;");
	}

}

namespace section_testreturntablefromlua
{
	// Simple example of a lua function returning a table
	
	int main()
	{
		Lua lua;
		auto global = lua.GetGlobalEnvironment();
		
		lua.RunScript(
			"function makeNewCar()\n"
			"	return {type = 'toyota'}\n"
			"end"
		);
		
		auto makeNewCar = global.Get< LuaFunction<LuaTable()> >("makeNewCar");
	
		auto car = makeNewCar.Invoke();
		
		return car.Get<std::string>("type").compare("toyota");
	}

}

namespace section_testreturntablefromnative
{
	// Simple example of a native function returning a table
	
	int main()
	{
		Lua lua;
		auto global = lua.GetGlobalEnvironment();
		
		auto newCar = lua.CreateFunction<LuaTable()>(
			[&]() -> LuaTable 
			{
				LuaTable table = lua.CreateTable();
				table.Set("type", "renault");
				return table;
			}
		);
	
		global.Set("newCar", newCar);
	
		// Run the script that chooses a function to return
		lua.RunScript(
			"x = newCar()['type']"
		);
	
		auto type = global.Get<std::string>("x");
		
		return type.compare("renault");
	}

}

namespace section_testscriptexception
{
	// Simple example of catching a script exception
	
	int main()
	{
	
		Lua lua;
		
		// Use it in a script!
		std::string result = lua.RunScript(
			"a = nil\n"
			"a.x = 5"
			);
	
		std::cout << result << std::endl;
	
	
		if ("Error: [string \"a = nil...\"]:2: attempt to index global 'a' (a nil value)\n" == result)
		{
			return 0;
		}
	
		return 1;
	}

}

namespace section_testsetstring
{
	// Simple test for creating a variable with string and reading it as wstring
	
	int main()
	{
		Lua lua;
		lua.LoadStandardLibraries();
		auto global = lua.GetGlobalEnvironment();
	
		global.Set("variable", "876");
	
		auto variable = global.Get< std::wstring >("variable");
	
		for (size_t i=0;i<variable.size();i++)
		{
			std::wcout << (int)variable[i] << L" ";
		}
		std::wcout << std::endl;
		std::wcout << variable << std::endl;
	
		return variable != L"876";
	}

}

namespace section_testsetwstring
{
	// Simple test for creating a variable with wstring
	
	int main()
	{
		Lua lua;
		lua.LoadStandardLibraries();
		auto global = lua.GetGlobalEnvironment();
	
		global.Set("variable", L"346");
	
		auto variable = global.Get< std::string >("variable");
	
		std::cout << variable << std::endl;
	
		return variable != "346";
	}

}

namespace section_testtable
{
	// Simple example of how to create a lua table
	
	int main()
	{
		Lua lua;
	
		auto table = lua.CreateTable();
	
		return 0;
	}

}

namespace section_testtableexpectedbutnotable
{
	// Simple demonstration that you will get an error if you try an extract a table from a function
	
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
		lua.LoadStandardLibraries();
		auto global = lua.GetGlobalEnvironment();
	
		lua.RunScript("\
			function x()\
				return 'meow'\
			end\
		");
	
		try
		{
			global.Get< LuaTable >("x");
			return 1;
		}
		catch(LuaError e)
		{
			std::cout << e.GetMessage() << std::endl;
			return e.GetMessage() != "Error: table expected, got function\nError: bad argument #-1 (table expected, got function)\n";
		}
	
		return 2;
	}

}

namespace section_testtableforeachintegerkey
{
	// Simple example of getting all the integer keys in a table
	
	int main()
	{
		Lua lua;
	
		LuaTable tbl = lua.CreateTable();
		tbl.Set("name", "Chuck Norris");
		tbl.Set("age", 1337);
		tbl.Set("0", "divide by");
		tbl.Set(1337, "leet");
	
		int keys = 1;
	
		tbl.ForAllIntegerKeys([&](int key, LuaType::Value value)
		{
			keys--;
		});
	
		return keys;
	}

}

namespace section_testtableforeachstringkey
{
	// Simple example of getting all the string keys in a table
	
	int main()
	{
		Lua lua;
	
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
	
		return keys;
	}

}

namespace section_testtypeintstringmorph
{
	// Simple test that demonstrates type morphing from int to string
	
	int main()
	{
		Lua lua;
		lua.LoadStandardLibraries();
		auto global = lua.GetGlobalEnvironment();
		
		// Write a function in Lua
		lua.RunScript("\
			variable = 1\
		");
	
		auto variable = global.Get< std::string >("variable");
		return variable != "1";
	}

}

namespace section_testtypemorphintwstring
{
	// Simple test that demonstrates type morphing from int to wstring
	
	int main()
	{
		Lua lua;
		lua.LoadStandardLibraries();
		auto global = lua.GetGlobalEnvironment();
		
		// Write a function in Lua
		lua.RunScript("\
			variable = 765\
		");
	
		auto variable = global.Get< std::wstring >("variable");
		std::wcout << variable << std::endl;
		return variable != L"765";
	}

}

namespace section_testtypestringintmorph
{
	// Simple test that demonstrates type morphing from string to int
	
	int main()
	{
		Lua lua;
		lua.LoadStandardLibraries();
		auto global = lua.GetGlobalEnvironment();
		
		// Write a function in Lua
		lua.RunScript("\
			variable = '400'\
		");
	
		auto variable = global.Get< int >("variable");
		return variable != 400;
	}

}

namespace section_testuserdata
{
	// Simple example of how to create a userdata instance
	
	class SomeClass
	{
	};
	
	int main()
	{
		Lua lua;
	
		auto userdata = lua.CreateUserdata<SomeClass>(new SomeClass());
	
		return 0;
	}

}

namespace section_testuserdataconstructor
{
	// Simple example of how to create a userdata constructor
	
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

}

namespace section_testuserdatadispose
{
	// Test that the userdata is destroyed when neccessary
	
	int x = 0;
	
	class SomeClass
	{
		int number;
	public:
		SomeClass(int number)
		{
			this->number = number;
		}
		
		~SomeClass()
		{
			x = 100;
		}
		
		int GetNumber() const
		{
			return number;
		}
	};
	
	int main()
	{
		Lua lua;
		lua.LoadStandardLibraries();
		
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
		"someclass = nil\n"
		"collectgarbage()\n"
		);
		
		return 100 - x;
	}

}

namespace section_testuserdatamethod
{
	// Simple example of how to add methods to a userdata instance
	// its similar to a table.
	
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

}

namespace section_testwidetocharconvert
{
	// Test converting a std::wstring to std::string
	
	int main()
	{
		std::string utf8str("ABC\xCE\x99\xCE\xBF\xCF\x8D\xCE\xBD\xCE\xB9\xCE\xBA\xCE\xBF\xCE\xBD\xCF\x84\x00");
		std::wstring wstr(L"ABC\u0399\u03BF\u03CD\u03BD\u03B9\u03BA\u03BF\u03BD\u03C4");
	
		auto conv = WStrToUTF8(wstr);
		if (conv == utf8str)
		{
			return 0;
		}
	
		std::cout << "Expect: ";
		for (int i=0;i<utf8str.size();i++)
		{
			std::cout << (unsigned int)(uint8_t)utf8str[i] << " ";
		}
		std::cout << " " << utf8str.size();
		std::cout << std::endl;
	
		std::cout << "Result: ";
		for (int i=0;i<conv.size();i++)
		{
			std::cout << (unsigned int)(uint8_t)conv[i] << " ";
		}
		std::cout << " " << conv.size();
		std::cout << std::endl;
		return 1;
	}
	

}


namespace LuaCppInterfaceTests
{		
	TEST_CLASS(UnitTests)
	{
	public:

		TEST_METHOD(demonstration1)
		{
			Assert::IsTrue(section_demonstration1::main() == 0);
		}

		TEST_METHOD(demonstration2)
		{
			Assert::IsTrue(section_demonstration2::main() == 0);
		}

		TEST_METHOD(demonstration3)
		{
			Assert::IsTrue(section_demonstration3::main() == 0);
		}

		TEST_METHOD(demonstration4)
		{
			Assert::IsTrue(section_demonstration4::main() == 0);
		}

		TEST_METHOD(luacpp)
		{
			Assert::IsTrue(section_luacpp::main() == 0);
		}

		TEST_METHOD(testcallabletable)
		{
			Assert::IsTrue(section_testcallabletable::main() == 0);
		}

		TEST_METHOD(testchartowideconvert)
		{
			Assert::IsTrue(section_testchartowideconvert::main() == 0);
		}

		TEST_METHOD(testcoroutineexception)
		{
			Assert::IsTrue(section_testcoroutineexception::main() == 0);
		}

		TEST_METHOD(testcoroutineexpectedbutnot)
		{
			Assert::IsTrue(section_testcoroutineexpectedbutnot::main() == 0);
		}

		TEST_METHOD(testcreate)
		{
			Assert::IsTrue(section_testcreate::main() == 0);
		}

		TEST_METHOD(testctoluafunction)
		{
			Assert::IsTrue(section_testctoluafunction::main() == 0);
		}

		TEST_METHOD(testexceptioninluafunction)
		{
			Assert::IsTrue(section_testexceptioninluafunction::main() == 0);
		}

		TEST_METHOD(testextractingasfunctionbutistable)
		{
			Assert::IsTrue(section_testextractingasfunctionbutistable::main() == 0);
		}

		TEST_METHOD(testfunction)
		{
			Assert::IsTrue(section_testfunction::main() == 0);
		}

		TEST_METHOD(testfunctionerror)
		{
			Assert::IsTrue(section_testfunctionerror::main() == 0);
		}

		TEST_METHOD(testfunctionexpectedbutnotcallable)
		{
			Assert::IsTrue(section_testfunctionexpectedbutnotcallable::main() == 0);
		}

		TEST_METHOD(testfunctionparams)
		{
			Assert::IsTrue(section_testfunctionparams::main() == 0);
		}

		TEST_METHOD(testfunctionparamsreturn)
		{
			Assert::IsTrue(section_testfunctionparamsreturn::main() == 0);
		}

		TEST_METHOD(testfunctionreturn)
		{
			Assert::IsTrue(section_testfunctionreturn::main() == 0);
		}

		TEST_METHOD(testgetmetatableonclosedstate)
		{
			Assert::IsTrue(section_testgetmetatableonclosedstate::main() == 0);
		}

		TEST_METHOD(testgetnullstring)
		{
			Assert::IsTrue(section_testgetnullstring::main() == 0);
		}

		TEST_METHOD(testgetnulltable)
		{
			Assert::IsTrue(section_testgetnulltable::main() == 0);
		}

		TEST_METHOD(testgetnullwstring)
		{
			Assert::IsTrue(section_testgetnullwstring::main() == 0);
		}

		TEST_METHOD(testgetsetfunction)
		{
			Assert::IsTrue(section_testgetsetfunction::main() == 0);
		}

		TEST_METHOD(testgetsetfunction2)
		{
			Assert::IsTrue(section_testgetsetfunction2::main() == 0);
		}

		TEST_METHOD(testgetsetinsidetable)
		{
			Assert::IsTrue(section_testgetsetinsidetable::main() == 0);
		}

		TEST_METHOD(testgetsetinteger)
		{
			Assert::IsTrue(section_testgetsetinteger::main() == 0);
		}

		TEST_METHOD(testgetsetstring)
		{
			Assert::IsTrue(section_testgetsetstring::main() == 0);
		}

		TEST_METHOD(testgetsettable)
		{
			Assert::IsTrue(section_testgetsettable::main() == 0);
		}

		TEST_METHOD(testgetstate)
		{
			Assert::IsTrue(section_testgetstate::main() == 0);
		}

		TEST_METHOD(testgettypeofvalueat)
		{
			Assert::IsTrue(section_testgettypeofvalueat::main() == 0);
		}

		TEST_METHOD(testinvalidscript)
		{
			Assert::IsTrue(section_testinvalidscript::main() == 0);
		}

		TEST_METHOD(testluacoroutineconstructor)
		{
			Assert::IsTrue(section_testluacoroutineconstructor::main() == 0);
		}

		TEST_METHOD(testluafunctionconstructor)
		{
			Assert::IsTrue(section_testluafunctionconstructor::main() == 0);
		}

		TEST_METHOD(testluatableconstructor)
		{
			Assert::IsTrue(section_testluatableconstructor::main() == 0);
		}

		TEST_METHOD(testluauserdataconstructor)
		{
			Assert::IsTrue(section_testluauserdataconstructor::main() == 0);
		}

		TEST_METHOD(testpassingfunction)
		{
			Assert::IsTrue(section_testpassingfunction::main() == 0);
		}

		TEST_METHOD(testreadinglightuserdatafromuserdata)
		{
			Assert::IsTrue(section_testreadinglightuserdatafromuserdata::main() == 0);
		}

		TEST_METHOD(testregistry)
		{
			Assert::IsTrue(section_testregistry::main() == 0);
		}

		TEST_METHOD(testresumenoscript)
		{
			Assert::IsTrue(section_testresumenoscript::main() == 0);
		}

		TEST_METHOD(testreturnfromnative)
		{
			Assert::IsTrue(section_testreturnfromnative::main() == 0);
		}

		TEST_METHOD(testreturnfromscript)
		{
			Assert::IsTrue(section_testreturnfromscript::main() == 0);
		}

		TEST_METHOD(testreturnfromyieldingfunction)
		{
			Assert::IsTrue(section_testreturnfromyieldingfunction::main() == 0);
		}

		TEST_METHOD(testreturntablefromlua)
		{
			Assert::IsTrue(section_testreturntablefromlua::main() == 0);
		}

		TEST_METHOD(testreturntablefromnative)
		{
			Assert::IsTrue(section_testreturntablefromnative::main() == 0);
		}

		TEST_METHOD(testscriptexception)
		{
			Assert::IsTrue(section_testscriptexception::main() == 0);
		}

		TEST_METHOD(testsetstring)
		{
			Assert::IsTrue(section_testsetstring::main() == 0);
		}

		TEST_METHOD(testsetwstring)
		{
			Assert::IsTrue(section_testsetwstring::main() == 0);
		}

		TEST_METHOD(testtable)
		{
			Assert::IsTrue(section_testtable::main() == 0);
		}

		TEST_METHOD(testtableexpectedbutnotable)
		{
			Assert::IsTrue(section_testtableexpectedbutnotable::main() == 0);
		}

		TEST_METHOD(testtableforeachintegerkey)
		{
			Assert::IsTrue(section_testtableforeachintegerkey::main() == 0);
		}

		TEST_METHOD(testtableforeachstringkey)
		{
			Assert::IsTrue(section_testtableforeachstringkey::main() == 0);
		}

		TEST_METHOD(testtypeintstringmorph)
		{
			Assert::IsTrue(section_testtypeintstringmorph::main() == 0);
		}

		TEST_METHOD(testtypemorphintwstring)
		{
			Assert::IsTrue(section_testtypemorphintwstring::main() == 0);
		}

		TEST_METHOD(testtypestringintmorph)
		{
			Assert::IsTrue(section_testtypestringintmorph::main() == 0);
		}

		TEST_METHOD(testuserdata)
		{
			Assert::IsTrue(section_testuserdata::main() == 0);
		}

		TEST_METHOD(testuserdataconstructor)
		{
			Assert::IsTrue(section_testuserdataconstructor::main() == 0);
		}

		TEST_METHOD(testuserdatadispose)
		{
			Assert::IsTrue(section_testuserdatadispose::main() == 0);
		}

		TEST_METHOD(testuserdatamethod)
		{
			Assert::IsTrue(section_testuserdatamethod::main() == 0);
		}

		TEST_METHOD(testwidetocharconvert)
		{
			Assert::IsTrue(section_testwidetocharconvert::main() == 0);
		}

	};
}
