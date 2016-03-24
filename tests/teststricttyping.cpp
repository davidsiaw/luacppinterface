// Test that the strict typing allows correct values

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

	auto error4 = l4.RunScript("strictlyTypedFunc(1, 'hello4', 'kitty4')");

	if (error4 == "No errors")
	{
		return 0;
	}
	std::cout << error4 << std::endl;
	return 1;
}

