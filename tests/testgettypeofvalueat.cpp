// Simple example of getting the type of the value at a particular key

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
