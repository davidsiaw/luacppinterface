luacppinterface
===============
[![Gitter](https://badges.gitter.im/Join Chat.svg)](https://gitter.im/davidsiaw/luacppinterface?utm_source=badge&utm_medium=badge&utm_campaign=pr-badge&utm_content=badge)

A Simple C++ Interface to Lua 5.2 and above.

[![Build Status](https://img.shields.io/travis/davidsiaw/luacppinterface.svg?branch=master)](https://travis-ci.org/davidsiaw/luacppinterface)
[![Coverage Status](https://img.shields.io/coveralls/davidsiaw/luacppinterface.svg)](https://coveralls.io/r/davidsiaw/luacppinterface?branch=master)
[![Issues](https://img.shields.io/github/issues/davidsiaw/luacppinterface.svg)](https://github.com/davidsiaw/luacppinterface/issues)
[![Tag](https://img.shields.io/github/tag/davidsiaw/luacppinterface.svg)](https://github.com/davidsiaw/luacppinterface/releases)
[![Stories in Ready](https://badge.waffle.io/davidsiaw/luacppinterface.svg?label=ready&title=Ready)](http://waffle.io/davidsiaw/luacppinterface)
[![License](http://img.shields.io/badge/license-MIT-red.svg)](https://github.com/davidsiaw/luacppinterface/blob/master/LICENSE)
[![Language](https://img.shields.io/badge/language-C++-blue.svg)](https://github.com/davidsiaw/luacppinterface/wiki)

Windows Build:
[![Build status](http://img.shields.io/appveyor/ci/davidsiaw/luacppinterface.svg)](https://ci.appveyor.com/project/davidsiaw/luacppinterface)


[![Codeship Status for davidsiaw/luacppinterface](https://www.codeship.io/projects/31137300-050f-0132-6e2b-32730fef382b/status)](https://www.codeship.io/projects/30789)


This small static library offers a very simple method of interfacing with Lua from C++ by constraining (only string and integer keys are allowed on LuaTable, a limited set of types available for functions callable from both Lua and C++) and general methods to reduce the number of surprises by as much as possible.

*feel free to open issues*

## Documentation

You can find more information besides this readme on the [Wiki](https://github.com/davidsiaw/luacppinterface/wiki). The information on this readme is also important, and you should read it to get an overview of things.

## Checking out

You need to `git clone --recursive https://github.com/davidsiaw/luacppinterface` To pull the lua dependency.

## Windows build on MSVC

To build luacppinterface, use the included LuaCppInterface.sln

## Linux || Mac OS X with autotools installed || Windows with Cygwin

`autoreconf --install && ./configure && make`

## Mac OS X || iOS

You can use the included XCode projects:
- Use the luacppinterface.xcodeproj for Mac OS X.
- Use the luacppinterface-ios.xcodeproj for iOS.

## Android 

You can use this library on Android as well. Simply pull this repository as a submodule into `jni/luacppinterface`, and your `ndk-build` should pick it up.

## Testing

LuaCppInterface comes with tests. To run them type

`make check`

For more information about building, please refer to .travis.yml

The examples here are not at all extensive. You might want to refer to the [tests](https://github.com/davidsiaw/luacppinterface/tree/master/tests) for more examples.

Contents
========

* [PrimitiveTypes](#primitivetypes)
* [API](#api)
 * [Lua object](#lua-object)
 * [LuaTable object](#luatable-object)
 * [LuaFunction object](#luafunction-object)
 * [LuaCoroutine object](#luacoroutine-object)
 * [LuaUserdata object](#luauserdata-object)
* [TODO](#todo)


API Changes
===========

*API Changes on 10 August 2014*:
Removed boost dependency. LuaCppInterface no longer requires boost on the expectation that most people will by now be using gcc 4.8, clang 3.4 and VS2012 and above

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
Thanks to this change, LuaCppInterface now supports Get and Set with the *[PrimitiveTypes](#primitivetypes)*:
Note: Key types available on the table are still only std::string and int. This does not change

PrimitiveTypes
==============

LuaCppInterface defines a set of primitive types that can freely be passed between Lua and C++ via functions, Get/Set, etc... You must use these types to communicate with a Lua Script.

```
LuaTable
LuaCoroutine
LuaFunction
LuaUserdata
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

// create a userdata (the destructor parameter is optional and defaults to delete)
LuaUserdata<TYPE> CreateUserdata(TYPE* data, std::tr1::function<void(TYPE*)> destructor = [](TYPE* data){ delete data; });

// run a lua script
std::string RunScript(std::string script);
```

Ownership
---------

As with any C++ library ownership is an important part of a library's functionality.

All objects created by LuaCppInterface: Lua, LuaTable, LuaFunction, LuaUserdata and LuaCoroutine have a corresponding lua object in the Lua state. They maintain a reference to the main Lua instance and carry a reference of their corresponding object around with them (this is just an int). They register their reference with the lua garbage collector so that lua does not collect their corresponding object as long as they are alive, freeing consumers of the API from having to worry about "anchoring" objects that are created.

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
The LuaFunction<T> object represents a function in Lua. However, not all functions can be represented. Valid function signatures are signatures that contain the *[PrimitiveTypes](#primitivetypes)*

**In addition, the return type is allowed to be void**. These are meant be used for passing functions from C++ to Lua and Lua to C++.

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


LuaUserdata object
------------------
The LuaUserdata object represents an object that is not one of the [PrimitiveTypes](#primitivetypes) that you want to be able to pass around and use in a script. Such an object may be an Image object or a Window object for example. This class will allow you to treat the object as a value in Lua and bind the object's methods to it.

```C++
// Get or set a member on the Userdata that is accessible from Lua (same as a LuaTable)
void Set<OBJ>(std::string key, const OBJ& value);
OBJ Get<OBJ>(std::string key) const;

// Bind a class's member function to the userdata with a name
void Bind<MEMBERFUNCTION>(std::string name, MEMBERFUNCTION memberFunction );
```

First of all you will find that the Get and Set functions on the LuaUserdata object are similar to the LuaTable. This is because they perform the same function. There is no Get and Set for integer keys because a LuaUserdata is meant to be used with only string members. *However you can add things to its metatable directly to allow indexing numbers*.

**Each userdata object has its own unique metatable**.

The **Bind** function is a shortcut that allows you to bind a member function of a class to a Userdata, allowing easy exposure of a C++ class's member functions to the script.

Examples:

Given a class that you want to expose:

```C++
class Image
{
	char* bitmap;
public:
	Image(int width, int height);
	void DrawCircle(int xcenter, int ycenter, int radius);
	int GetWidth() const;
	int GetHeight() const;
	~Image();
};
```

Here is how you create a LuaUserdata for it:

```C++
Lua lua;
auto image = lua.CreateUserdata<Image>(new Image(100,100));
lua.GetGlobalEnvironment().Set("image", image);
```

**The memory allocated is owned entirely by the Lua script**. This means once the object passed passed into lua.CreateUserdata, the lua garbage collector will decide when to delete it with the destructor provided. Keeping an instance of LuaUserdata<Image> in scope maintains a reference to the object, preventing it from being garbage collected.

With this the image is available to the script on the variable "image". But it is useless. Here is how we can bind its functions to it:

```C++
Lua lua;

// Create the userdata instance
auto image = lua.CreateUserdata<Image>(new Image(100,100));

// Bind the functions that we want to expose
image.Bind("drawCircle", &Image::DrawCircle);
image.Bind("getWidth", &Image::GetWidth);
image.Bind("getHeight", &Image::GetHeight);

// Set the global "image" to the instance of Image
lua.GetGlobalEnvironment().Set("image", image);
```

**Bind can only work with up member functions that have 8 arguments or less**. This is because I do not intend to complicate the code to support an arbitrary number and I do not believe in functions with large numbers of arguments. It is important to restructure your code if you require more than 8 arguments. You may also pass a LuaTable or better yet, another LuaUserdata to the function.

By doing this, now we can draw a circle with a Lua script:

```lua
image.drawCircle(50,50,10)
print(image.getWidth(), image.getHeight())
```

However, this is still fairly useless because the Image has a hardcoded size. We need to be able to specify it in Lua. In order to do so, we must create a constructor. In Lua the convention is to have a table contained in the type name that contains a "new" function:

```C++
Lua lua;

// Create the constructor
auto imageConstructor = lua.CreateFunction< LuaUserdata<Image>(int, int) >(
[&](int width, int height) -> LuaUserdata<Image>
{
	// Create the userdata instance
	auto image = lua.CreateUserdata<Image>(new Image(width, height));
	
	// Bind the functions that we want to expose
	image.Bind("drawCircle", &Image::DrawCircle);
	image.Bind("getWidth", &Image::GetWidth);
	image.Bind("getHeight", &Image::GetHeight);
	
	return image;
});

// Create the "type" table in Lua
auto imageType = lua.CreateTable();
imageType.Set("new", imageConstructor);

// Make the Image "type" accessible to everyone
lua.GetGlobalEnvironment().Set("Image", imageType);
```

With this now we can freely create Image objects in Lua and use them accordingly. All instances are automatically subject to lua's normal garbage collection rules. Like all other [PrimitiveTypes](#primitivetypes), it is possible to pass instances back and forth through functions and tables.

```lua
local image = Image:new(800, 600)
image.drawCircle(100,100,50)
print(image.getWidth(), image.getHeight())
```
