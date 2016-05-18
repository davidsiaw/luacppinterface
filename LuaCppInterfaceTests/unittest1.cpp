#include "stdafx.h"
#include "CppUnitTest.h"

#include <iostream>
#include <memory>
#include <luacppinterface.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace LuaCppInterfaceTests
{		
	TEST_CLASS(UnitTests)
	{
	public:
		
		TEST_METHOD(testchartowideconvert)
		{
			std::string utf8str("ABC\xCE\x99\xCE\xBF\xCF\x8D\xCE\xBD\xCE\xB9\xCE\xBA\xCE\xBF\xCE\xBD\xCF\x84\x00");
			std::wstring wstr(L"ABC\u0399\u03BF\u03CD\u03BD\u03B9\u03BA\u03BF\u03BD\u03C4");

			auto conv = UTF8ToWStr(utf8str);
			if (conv == wstr)
			{
				return Assert::IsFalse(0);
			}

			std::cout << "Expect: ";
			for (int i=0;i<wstr.size();i++)
			{
				std::cout << (unsigned int)wstr[i] << " ";
			}
			std::cout << " " << wstr.size();
			std::cout << std::endl;

			std::cout << "Result: ";
			for (int i=0;i<conv.size();i++)
			{
				std::cout << (unsigned int)conv[i] << " ";
			}
			std::cout << " " << conv.size();
			std::cout << std::endl;
			return Assert::IsFalse(1);
		}

	};
}