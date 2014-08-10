// Simple example of getting all the string keys in a table

#include <iostream>
#include <sstream>
#include <memory>
#include <luacppinterface.h>

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
