luacppinterface
===============

A Simple C++ Interface to Lua

This small static library offers a very simple method of interfacing with Lua from C++ using conventions (all functions use are LuaTable -> LuaTable and only string and integer keys are allowed) and general methods to lower the amount of thinking needed by as much as possible.


In order to use the library, simply link in lua and luacppinterface statically.

API
===

The API for luacppinterface is easy. This is an example use of it:

    #include <functional>
    #include <iostream>
    #include "luacppinterface.h"
    
    int main()
    {
        Lua lua;
        LuaTable global = lua.GetGlobalEnvironment();
        
        auto printfunc = new std::tr1::function<LuaTable(LuaTable)>([&](LuaTable args) -> LuaTable
        {
          std::cout << args.GetString("str") << std::endl;
            return lua.CreateTable();
    	});
        
        LuaFunction print = lua.CreateFunction(printfunc);

        global.SetFunction("print", print);
        
        lua.RunScript("print({str = 'hello world!'})");
        
        return 0;
    }

Lua object
----------

The Lua object represents an instance of the Lua state. Using this object you can get the global table and the registry, and also create tables and functions for use in this state.

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

The LuaTable object is arguably the most important object in this library and in Lua, because it is such a general data structure. The Registry and Global table are both LuaTables. In order to create free functions in Lua, simply add the function to the Global table.

In order to create a new table you need to call lua.CreateTable(), or return a table from Lua.

LuaCppInterface only allows you to use strings or integers to index a table. This is because these two data structures are the most primitive data types that can be used as a key and is general among every language. Other data structures suffer from IdentityCrisis. It is also easier to think of.

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
    LuaFunction GetFunction(std::string key) const;
    LuaFunction GetFunction(int key) const;
    
Basically, a Set function is equivalent to t[k] = v and a Get function is equivalent to v = t[k] where v is value, t is the table and k is the key.

LuaFunction object
------------------
The LuaFunction object represents a function in Lua. However, not all functions can be represented. The LuaFunction only allows functions with the signature:

    LuaTable Function(LuaTable)

to be used for passing functions from C++ to Lua and Lua to C++.

In this library all Lua functions used for interop with C++ must be functions that take a LuaTable and return a LuaTable.  The reason is this is the most general form of function that can be used to pass any form and any number of arguments.

*Making LuaTables all the time will be annoying too. This is a temporary situation as I am working on a way to generate code that allows us to pass types around directly.

In order to create a function you need to either create one with lua.CreateFunction(cppFunc) or get one from Lua.

    // Invoke the function
    LuaTable Invoke(LuaTable table);


TODO
====
- luacppinterface currently uses c++0x features. I will include boost to allow non-c++0x supporting compilers to use this library too
- support lua threads
- code generation for c++ from c++ headers (like tolua but better), in order to reduce usage of LuaTable
- support userdata
- improve api docs
