// Simple example of getting all the integer keys in a table

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
    
    int keys = 1;
    
    tbl.ForAllIntegerKeys([&](int key, LuaType::Value value)
    {
        keys--;
    });

	return keys;
}
