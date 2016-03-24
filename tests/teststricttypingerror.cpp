// Test that the strict typing throws a lua error when given the wrong values

#include <iostream>
#include <memory>
#include <luacppinterface.h>

int main()
{
	Lua l4;
	auto glob4 = l4.GetGlobalEnvironment();

	auto strictlyTypedFunc = l4.CreateFunction<void(uint32_t, std::string, std::wstring)>
		([&](uint32_t intVal, std::string stringVal, std::wstring wstringVal) -> void
		{
			std::cout << "intVal:       " << intVal << std::endl;
			std::cout << "stringVal:    " << stringVal << std::endl;
			std::wcout << L"wstringVal: " << wstringVal << std::endl;
		}
	);

	glob4.Set("strictlyTypedFunc", strictlyTypedFunc);

	auto error4 = l4.RunScript("strictlyTypedFunc(\"it\'s kitty, not a number\", 3, 3.3)");

	auto expected_error = "Error: [string \"strictlyTypedFunc(\"it's kitty, not a number\",...\"]:1: bad argument #-1 to 'strictlyTypedFunc' (string expected, got number)\n";

	if (error4 == expected_error)
	{
		return 0;
	}
	return 1;
}

