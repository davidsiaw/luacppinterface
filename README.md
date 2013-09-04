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

The Lua object is the starting point for using this library. The Lua object represents an instance of the Lua state. Using this object you can get the global table and the registry, and also create tables and functions for use in this state.

    // create a new Lua state
    Lua();
    
    // get the registry table
    LuaTable GetRegistry();
    
    // get the global table
    LuaTable GetGlobalEnvironment();
    
    // create a table
    LuaTable CreateTable();
    
    // create a function that can be used in Lua
    LuaFunction CreateFunction(const std::tr1::function<LuaTable(LuaTable)>* func);
    
    // run a lua script
    std::string RunScript(std::string script);


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
    
    // Associate the given key to a specified function
    void SetFunction(std::string key, const LuaFunction value);
    void SetFunction(int key, const LuaFunction value);
    
    // Get the table associated with the specified key
    LuaTable GetTable(std::string key) const;
    LuaTable GetTable(int key) const;
    
    // Get the integer associated with the specified key
    int GetInteger(std::string key) const;
    int GetInteger(int key) const;
    
    // Get the string associated with the specified key
    std::string GetString(std::string key) const;
    std::string GetString(int key) const;
    
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

TODO
====
- support other types: bool, double, wstring
- support userdata
- improve api docs
