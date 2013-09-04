luacppinterface
===============

A Simple C++ Interface to Lua 5.2 and above.

[![Build Status](https://travis-ci.org/davidsiaw/luacppinterface.png)](https://travis-ci.org/davidsiaw/luacppinterface)

This small static library offers a very simple method of interfacing with Lua from C++ using conventions (only string and integer keys are allowed on LuaTable, a limited set of types available for functions callable from both Lua and C++) and general methods to reduce the number of surprises by as much as possible.

In order to use the library, simply link in lua and luacppinterface statically. LuaCppInterface depends on Boost C++. Boost is provided as a submodule. You may also use a different version of Boost by adding the --with-boost=~/myownboost/ parameter to the configure script for building luacppinterface.

To build luacppinterface, use the included LuaCppInterface.sln if you are using Visual Studio 2010 and above, or type:

./configure && make

LuaCppInterface comes with tests. To run them type

make check

For more information about building, please refer to .travis.yml

API
===

The API for luacppinterface is easy. This is an example use of it:

    #include <functional>
    #include <iostream>
    #include <luacppinterface.h>
    
    int main()
    {
        Lua lua;
        LuaTable global = lua.GetGlobalEnvironment();
        
		// A function that prints a message
        auto printfunc = [&](std::string str)
        {
			std::cout << "message: " << str << std::endl;
    	};
        
		// Create a Lua function that a Lua script can call
        auto print = lua.CreateFunction<void(std::string)>(printfunc);

		// Set the variable "print" in the global state to the function
        global.SetFunction("print", print);
        
		// Call the function!
        lua.RunScript("print({str = 'hello world!'})");
        
        return 0;
    }

Lua object
----------

The Lua object is the starting point for using this library. The Lua object represents an instance of the Lua state. Using this object you can get the global table and the registry, and also create tables, functions and coroutines for use in this state.

    // create a new Lua state
    Lua();
    
	// load standard lua libraries into this state
	void LoadStandardLibraries();
	
    // get the registry table
    LuaTable GetRegistry();
    
    // get the global table
    LuaTable GetGlobalEnvironment();
    
    // create a table
    LuaTable CreateTable();
    
	// create a coroutine
	LuaCoroutine CreateCoroutine();

    // create a function that can be used in Lua
    LuaFunction CreateFunction(const std::tr1::function<LuaTable(LuaTable)>* func);
    
    // run a lua script
    std::string RunScript(std::string script);


Ownership
---------

As with any C++ library ownership is an important part of a library's functionality.

All objects created by LuaCppInterface: Lua, LuaTable, LuaFunction and LuaCoroutine have a corresponding lua object in the Lua state. They maintain a reference to the main Lua instance and carry a reference of their corresponding object around with them (this is just an int). They register their reference with the lua garbage collector so that lua does not collect their corresponding object as long as they are alive, freeing consumers of the API from having to worry about "anchoring" objects that are created.

Hence, every object you retrieve via the API is owned by you and you alone. When they go out of scope the objects automatically remove their own reference. If there are no more references, you can allow the lua garbage collector to collect the corresponding object in the Lua instance.

All objects hold a reference to the Lua object, so if the Lua object goes out of scope, the objects continue to work until all of them are either deleted or are out of scope.

This means you can pass all Lua objects around freely as if they were mere values without worrying that they may expire under your feet. Of course, all standard rules still apply: deleting a pointer to one of them and attempting to use that pointer them will fail.

Also, you SHOULD NOT use a Lua object created by one instance of Lua with objects created by another instance of Lua. The results will be disasterous. You can use coroutines if you wish to run lots of scripts concurrently. If you require multiple Lua instances, isolate their objects in your program from each other in any fashion you prefer.


LuaTable object
---------------

The LuaTable object is the heart of Lua's functionality, because it is such a general data structure. The Registry and Global table are both LuaTables. In order to create free functions in Lua, simply add the function to the Global table.

In order to create a new table you need to call lua.CreateTable(), or retrieve a table from Lua by having a function return it or calling GetTable from a variable in Lua.

LuaCppInterface only allows you to use strings or integers to index a table. This is because these two data structures are the most primitive data types that can be used as a key and is general among every language. Other data structures suffer from IdentityCrisis. It is also easier to think of a table that holds keys of only string or integer types.

	// Associate the given key to a specified table
	void SetTable(std::string key, const LuaTable& value);	
	void SetTable(int key, const LuaTable& value);

	// Associate the given key to a specified integer
	void SetInteger(std::string key, const int value);
	void SetInteger(int key, const int value);

	// Associate the given key to a specified string
	void SetString(std::string key, const std::string value);
	void SetString(int key, const std::string value);
	
	// Associate the given key to a specified coroutine
	void SetCoroutine(std::string key, const LuaCoroutine value);
	void SetCoroutine(int key, const LuaCoroutine value);

	// Associate the given key to a specified function
	void SetFunction(std::string key, const LuaFunctionBase value);
	void SetFunction(int key, const LuaFunctionBase value);

	// Get the table associated with the specified key
	LuaTable GetTable(std::string key) const;
	LuaTable GetTable(int key) const;

	// Get the integer associated with the specified key
	int GetInteger(std::string key) const;
	int GetInteger(int key) const;

	// Get the string associated with the specified key
	std::string GetString(std::string key) const;
	std::string GetString(int key) const;

	// Get the coroutine associated with the specified key
	LuaCoroutine GetCoroutine(std::string key) const;
	LuaCoroutine GetCoroutine(int key) const;
    
    // Get the function associated with the specified key
    LuaFunction<Signature> GetFunction<Signature>(std::string key) const;
    LuaFunction<Signature> GetFunction<Signature>(int key) const;
    
Basically, a Set function is equivalent to table[key] = value and a Get function is equivalent to value = table[key].

LuaFunction<T> object
---------------------
The LuaFunction<T> object represents a function in Lua. However, not all functions can be represented. Valid function signatures are signatures that contain the following types:

    int, std::string, LuaTable, LuaFunction<T>

In addition, the return type is allowed to be void. These to be used for passing functions from C++ to Lua and Lua to C++.

In order to create a function you need to either create one with lua.CreateFunction<>() or retrieve one from Lua. Here are some ways you can use CreateFunction:

	// Create a function from an existing C function called "abs" (available in cmath)
	auto absolute = lua.CreateFunction<int(int)>(abs);
	
	// Create a function using a C++ lambda
	auto lambdaFunc = lua.CreateFunction<void()>([&]()
	{
		std::cout << "called lambdaFunc" << std::endl;
	});

This is how you invoke the functions created above:

	// Invoke them directly from C++
    int shouldBePositiveFive = absolute.Invoke(-5);
	lambdaFunc.Invoke();
	
	// ... or set them up in a script
	lua.GetGlobalEnvironment().SetFunction("absolute", absolute);
	lua.GetGlobalEnvironment().SetFunction("lambdaFunc", lambdaFunc);
	
	// and invoke them in a script.
	lua.RunScript(
		"local shouldBePositiveFive = absolute(-5)\n"
		"lambdaFunc()\n"
		""
	);
	
You can also retrieve a function from a script to call it:
	
	// Run the script to create the function
	lua.RunScript(
		"function addTwo(a)\n"
		"  return a+2\n"
		"end\n"
	);
	
	// Call the function set up by the script.
	auto addTwo = global.GetFunction<int(int)>("addTwo");
	int shouldBeSix = addTwo.Invoke(4);
	
It is also possible to write a function that returns a function

	auto add = lua.CreateFunction<int(int,int)>([&](int a, int b) -> int { return a + b; });
	auto multiply = lua.CreateFunction<int(int,int)>([&](int a, int b) -> int { return a * b; });
	
	lua.GetGlobalEnvironment().SetFunction("add", add);
	lua.GetGlobalEnvironment().SetFunction("multiply", multiply);
	
	// Run the script that chooses a function to return
	lua.RunScript(
		"function subtract(a,b)\n"
		"  return a - b"
		"end\n"
		""
		"function returnAnOperator()\n"
		"  return multiply"		// this can be either add, multiply or subtract
								// change it to see what happens!
		"end\n"
	);
	
	auto returnAnOperator = global.GetFunction< LuaFunction<int(int,int)>() >("returnAnOperator");
	auto anOperator = returnAnOperator.Invoke();
	auto result = anOperator.Invoke(10,10);		// if we returned add result would be 20
												// if we returned multiply result would be 100
												// if we returned subtract result would be 0
	
There are many other interesting things you can do with LuaFunction<T> and hopefully this will be useful and easy to use.


LuaCoroutine object
-------------------
The LuaCoroutine object represents a Lua coroutine (or thread) for the purposes of Lua's cooperative multitasking. In order to create a LuaCoroutine simply call lua.CreateCoroutine(). The following are the things you can do with a coroutine for now:

	// run a script
	std::string RunScript(std::string script);

	// resume the yielded coroutine
	std::string Resume();

	// check if the coroutine was yielded
	bool CanResume() const;

A coroutine is different from the main lua object in the sense that its execution can be paused and resumed until its script ends. It shares the same global and registry with the main lua object.

In order to pause a script, you have the script call a "Yielding Function". A Yielding Function can be created using lua.CreateYieldingFunction()

A yielding function basically pauses execution if the script upon its completion, surrendering control back to the C++ code (causing RunScript or Resume to return). When you call LuaCoroutine::Resume(), the script will resume.

Another way to look at it is from the script's perspective, a Yielding Function blocks, and does not return until the C++ code calls Resume() again.

Besides this detail, a Yielding Function is otherwise an ordinary function. You can return information in a Yielding Function and when the Yielding Function stops blocking, it will return whatever the function returned.

It is also possible to pause execution of a coroutine by calling coroutine.yield within the script itself.

Here is an example of LuaCoroutine usage:

	Lua luaInstance;
	auto globalTable = luaInstance.GetGlobalEnvironment();
	auto myOwnPrint = luaInstance.CreateYieldingFunction<void(std::string)>
		(
			[](std::string str)
			{
				std::cout << str << std::endl;
			}
		);

	globalTable.SetFunction("myownprint", myOwnPrint);

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

The above usage creates a Yielding Function that simply prints the text passed to it to the scren. It then sets a global called myownprint as the function. We then run this coroutine with a script that deliberately calls myownprint 3 times.

Then we resume the coroutine as much as it can until it can no longer resume. We will find that the script has been paused 3 times.

The output will be 

	hello
	yield
	hello2
	yield
	hello3
	yield

Due to the script returning from RunScript and Resume 3 times from paused execution by the Yielding Function.


TODO
====
- support other types: bool, double, wstring
- support userdata
- improve api docs
