// Test converting a std::wstring to std::string

#include <iostream>
#include <memory>
#include <luacppinterface.h>

int main()
{
	std::string utf8str("ABC\xCE\x99\xCE\xBF\xCF\x8D\xCE\xBD\xCE\xB9\xCE\xBA\xCE\xBF\xCE\xBD\xCF\x84\x00");
	std::wstring wstr(L"ABC\u0399\u03BF\u03CD\u03BD\u03B9\u03BA\u03BF\u03BD\u03C4");

	auto conv = WStrToUTF8(wstr);
	if (conv == utf8str)
	{
		return 0;
	}

	std::cout << "Expect: ";
	for (int i=0;i<utf8str.size();i++)
	{
		std::cout << (unsigned int)(uint8_t)utf8str[i] << " ";
	}
	std::cout << " " << utf8str.size();
	std::cout << std::endl;

	std::cout << "Result: ";
	for (int i=0;i<conv.size();i++)
	{
		std::cout << (unsigned int)(uint8_t)conv[i] << " ";
	}
	std::cout << " " << conv.size();
	std::cout << std::endl;
	return 1;
}

