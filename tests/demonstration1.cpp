#include <memory>
#include <luacppinterface.h>
#include <sstream>
#include <iostream>

int main()
{
	Lua l3;
	auto glob3 = l3.GetGlobalEnvironment();

	std::stringstream ss;

	auto formattedPrint = l3.CreateFunction<void(std::string, LuaTable)>
	(
		[&](std::string format, LuaTable objects)
		{
			int token = 1;
			std::string::size_type offset = 0;
			std::string::size_type n;
			do
			{
				n = format.substr(offset).find("%");
				ss << format.substr(offset, n);
				if (n == std::string::npos)
				{
					return;
				}
				else if (n + 1 >= format.size())
				{
					// percent at end
					ss<< "%";
					return;
				}
				else if (format[offset+n+1] == 's')
				{
					// string
					ss << objects.Get<std::string>(token);
					token++;
				}
				else if (format[offset+n+1] == 'd')
				{
					// integer
					ss << objects.Get<int>(token);
					token++;
				}
				else
				{
					// unknown. Print.
					ss << format.substr(offset, 2);
				}
				offset += n+2;
			}
			while (offset < format.length());
			
			// remaining
			std::cout << format.substr(offset) << std::endl;
		}
	);
	
	glob3.Set("print", formattedPrint);
	auto error = l3.RunScript("print('This is %s %s %s %s %d %d %d!', {'hello', 'kitty', 'island', 'adventure', 1, 2, 3});");
	
	auto resstr = ss.str();
	
	return resstr.compare("This is hello kitty island adventure 1 2 3!");
}
