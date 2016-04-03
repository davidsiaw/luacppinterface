#include "luastringconversion.h"

#include <clocale>
#include <cstdlib>
#include <iostream>

std::wstring UTF8ToWStr(const std::string& utf8str)
{
	auto original_locale = setlocale(LC_ALL, NULL);
	auto loc = setlocale(LC_ALL, "en_US.UTF-8");
	wchar_t* wstr_buf = new wchar_t[utf8str.size()];
#ifdef _MSC_VER
	size_t converted;
	mbstowcs_s(&converted, wstr_buf, utf8str.size(), utf8str.c_str(), utf8str.size());
#else
	size_t converted = mbstowcs(wstr_buf, utf8str.c_str(), utf8str.size());
#endif
	std::wstring result(wstr_buf);
	delete[] wstr_buf;
	setlocale(LC_ALL, original_locale);

	return result;
}

#define MAX_UTF8_CHAR_CHAIN 5

std::string WStrToUTF8(const std::wstring& wstr)
{
	auto original_locale = setlocale(LC_ALL, NULL);
	auto loc = setlocale(LC_ALL, "en_US.UTF-8");
	size_t max_size = wstr.size() * MAX_UTF8_CHAR_CHAIN;
	char* str_buf = new char[max_size];
#ifdef _MSC_VER
	size_t converted;
	wcstombs_s(&converted, str_buf, max_size, wstr.c_str(), max_size);
#else
	size_t converted = wcstombs(str_buf, wstr.c_str(), max_size);
#endif 
	std::string result(str_buf);
	delete[] str_buf;
	setlocale(LC_ALL, original_locale);

	return result;
}
