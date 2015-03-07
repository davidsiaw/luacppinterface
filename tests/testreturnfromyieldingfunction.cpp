#include <memory>
#include <iostream>
#include <luacppinterface.h>
#include <sstream>

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
