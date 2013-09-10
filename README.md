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

The examples here are not at all extensive. You might want to refer to the [tests](https://github.com/davidsiaw/luacppinterface/tree/master/tests) for more examples.

API Changes
===========

*API Changes on 11 September 2013*:
The following methods on LuaTable have been replaced by nicer template methods that allow you to specify more precisely the type you want to use. Here are some find/replace transformations that you will find helpful.
```
* SetTable -> Set<LuaTable>
* SetInteger -> Set<int>
* SetString -> Set<std::string>
* SetCoroutine -> Set<LuaCoroutine>
* SetFunction -> Set< LuaFunction<rettype(signature)> >
* GetTable -> Get<LuaTable>
* GetInteger -> Get<int>
* GetCoroutine -> Get<LuaCoroutine>
* GetString -> Get<std::string>
* GetFunction -> Get< LuaFunction<rettype(signature)> >
```
Thanks to C++'s new type inferencing, if your compiler supports it you can just go:
```C++
LuaFunction<void(int,int)> theFunction;
table.Set(theFunction);
```
Thanks to this change, LuaCppInterface now supports Get and Set with the *PrimitiveTypes*:
Note: Key types available on the table are still only std::string and int. This does not change

PrimitiveTypes
==============

LuaCppInterface defines a set of primitive types that can freely be passed between Lua and C++ via functions, Get/Set, etc... You must use these types to communicate with a Lua Script.

```
LuaTable
LuaCoroutine
LuaFunction
float
double
bool
signed char
unsigned char
short
unsigned short
int
unsigned int
long
unsigned long
long long
unsigned long long
char*
const char*
std::string
std::wstring
```

API
===

The API for luacppinterface is easy. This is an example use of it:

```C++
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
	global.Set("print", print);
	
	// Call the function!
	lua.RunScript("print({str = 'hello world!'})");
	
	return 0;
}
```

Lua object
----------

The Lua object is the starting point for using this library. The Lua object represents an instance of the Lua state. Using this object you can get the global table and the registry, and also create tables, functions and coroutines for use in this state.

```C++
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
LuaFunction<SIGNATURE> CreateFunction<SIGNATURE>(const std::tr1::function<SIGNATURE>* func);

// run a lua script
std::string RunScript(std::string script);
```

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

Values can only be one of the *PrimitiveTypes*

```C++
// Set the key to map to a value
void Set<TYPE>(std::string key, const TYPE& value);	
void Set<TYPE>(int key, const TYPE& value);

// Get the value mapped to the key (TYPE says what type you expect the value to be)
TYPE GetFunction<TYPE>(std::string key) const;
TYPE GetFunction<TYPE>(int key) const;

// Get the type of value at a specified key
LuaType::Value GetTypeOfValueAt(std::string key) const;
LuaType::Value GetTypeOfValueAt(int key) const;
```

You can also perform some error checking by using GetTypeOfValueAt to determine if the script performed correctly and has provided the correct value at the key you are interested in.

Basically, a Set function is equivalent to table[key] = value and a Get function is equivalent to value = table[key].

LuaFunction<T> object
---------------------
The LuaFunction<T> object represents a function in Lua. However, not all functions can be represented. Valid function signatures are signatures that contain the *PrimitiveTypes*

In addition, the return type is allowed to be void. These to be used for passing functions from C++ to Lua and Lua to C++.

In order to create a function you need to either create one with lua.CreateFunction<>() or retrieve one from Lua. Here are some ways you can use CreateFunction:

```C++
// Create a function from an existing C function called "abs" (available in cmath)
auto absolute = lua.CreateFunction<int(int)>(abs);

// Create a function using a C++ lambda
auto lambdaFunc = lua.CreateFunction<void()>([&]()
{
	std::cout << "called lambdaFunc" << std::endl;
});
```

This is how you invoke the functions created above:

```C++
// Invoke them directly from C++
int shouldBePositiveFive = absolute.Invoke(-5);
lambdaFunc.Invoke();

// ... or set them up in a script
lua.GetGlobalEnvironment().Set("absolute", absolute);
lua.GetGlobalEnvironment().Set("lambdaFunc", lambdaFunc);

// and invoke them in a script.
lua.RunScript(
	"local shouldBePositiveFive = absolute(-5)\n"
	"lambdaFunc()\n"
	""
);
```
	
You can also retrieve a function from a script to call it:
	
```C++
// Run the script to create the function
lua.RunScript(
	"function addTwo(a)\n"
	"  return a+2\n"
	"end\n"
);

// Call the function set up by the script.
auto addTwo = global.Get< LuaFunction<int(int)> >("addTwo");
int shouldBeSix = addTwo.Invoke(4);
```
	
It is also possible to write a function that returns a function

```C++
auto add = lua.CreateFunction<int(int,int)>([&](int a, int b) -> int { return a + b; });
auto multiply = lua.CreateFunction<int(int,int)>([&](int a, int b) -> int { return a * b; });

lua.GetGlobalEnvironment().Set("add", add);
lua.GetGlobalEnvironment().Set("multiply", multiply);

// Run the script that chooses a function to return
lua.RunScript(
	"function subtract(a,b)\n"
	"  return a - b\n"
	"end\n"
	""
	"function returnAnOperator()\n"
	"  return multiply\n"				// this can be either add, multiply or subtract
							// change it to see what happens!
	"end\n"
);

auto returnAnOperator = global.Get< LuaFunction< LuaFunction<int(int,int)>() > >("returnAnOperator");
auto anOperator = returnAnOperator.Invoke();
auto result = anOperator.Invoke(10,10);		// if we returned add result would be 20
						// if we returned multiply result would be 100
						// if we returned subtract result would be 0
```
	
There are many other interesting things you can do with LuaFunction<T> and hopefully this will be useful and easy to use.


LuaCoroutine object
-------------------
The LuaCoroutine object represents a Lua coroutine (or thread) for the purposes of Lua's cooperative multitasking. In order to create a LuaCoroutine simply call lua.CreateCoroutine(). The following are the things you can do with a coroutine for now:

```C++
// run a script
std::string RunScript(std::string script);

// resume the yielded coroutine
std::string Resume();

// check if the coroutine was yielded
bool CanResume() const;
```

A coroutine is different from the main lua object in the sense that its execution can be paused and resumed until its script ends. It shares the same global and registry with the main lua object.

In order to pause a script, you have the script call a "Yielding Function". A Yielding Function can be created using lua.CreateYieldingFunction()

A yielding function basically pauses execution if the script upon its completion, surrendering control back to the C++ code (causing RunScript or Resume to return). When you call LuaCoroutine::Resume(), the script will resume.

Another way to look at it is from the script's perspective, a Yielding Function blocks, and does not return until the C++ code calls Resume() again.

Besides this detail, a Yielding Function is otherwise an ordinary function. You can return information in a Yielding Function and when the Yielding Function stops blocking, it will return whatever the function returned.

It is also possible to pause execution of a coroutine by calling coroutine.yield within the script itself.

Here is an example of LuaCoroutine usage:

```C++
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
```

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
- support userdata
- improve api docs
