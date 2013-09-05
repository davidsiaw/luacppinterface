#include <boost/tr1/memory.hpp>
#include <luacppinterface.h>
#include <sstream>

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

	globalTable.SetFunction("myownprint", myOwnPrint);

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
