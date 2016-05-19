#include "luastringconversion.h"

#include <clocale>
#include <cstdlib>
#include <iostream>

#ifdef _MSC_VER
#include <windows.h>
#endif

std::wstring UTF8ToWStr(const std::string& utf8str)
{
#ifdef _MSC_VER
	// Because windows does not accept UTF-8 as a locale, we have to use its
	// other functions that do
	std::wstring wstr;
	int wlen = MultiByteToWideChar(CP_UTF8, NULL, utf8str.c_str(), utf8str.size(), NULL, NULL);
	
	if (wlen == 0)
	{
		return L"String conversion error";
	}

	wstr.resize(wlen);

	wlen = MultiByteToWideChar(CP_UTF8, NULL, utf8str.c_str(), utf8str.size(), (wchar_t*)wstr.data(), wlen);
	
	if (wlen == 0)
	{
		return L"String conversion error";
	}

	return wstr;
#else
	auto original_locale = setlocale(LC_ALL, NULL);
	auto loc = setlocale(LC_ALL, "en_US.UTF-8");
	if (loc == NULL)
	{
		return L"String conversion error: locale en_US.UTF-8 not supported";
	}
	size_t wstr_buf_size = utf8str.size() + 1;  // +1 because there is a null-terminator
	wchar_t* wstr_buf = new wchar_t[wstr_buf_size];
	size_t converted = mbstowcs(wstr_buf, utf8str.c_str(), wstr_buf_size);
	std::wstring result(wstr_buf);
	delete[] wstr_buf;
	setlocale(LC_ALL, original_locale);

	return result;
#endif
}

#define MAX_UTF8_CHAR_CHAIN 5

std::string WStrToUTF8(const std::wstring& wstr)
{
#ifdef _MSC_VER
	std::string utf8str;
	int len = WideCharToMultiByte(CP_UTF8, NULL, wstr.c_str(), wstr.size(), NULL, NULL, NULL, NULL);
	
	if (len == 0)
	{
		return "String conversion error";
	}

	utf8str.resize(len);
	len = WideCharToMultiByte(CP_UTF8, NULL, wstr.c_str(), wstr.size(), (char*)utf8str.data(), len, NULL, NULL);
	
	if (len == 0)
	{
		return "String conversion error";
	}

	return utf8str;
#else
	auto original_locale = setlocale(LC_ALL, NULL);
	auto loc = setlocale(LC_ALL, "en_US.UTF-8");
	if (loc == NULL)
	{
		return "String conversion error: locale en_US.UTF-8 not supported";
	}
	size_t max_size = wstr.size() * MAX_UTF8_CHAR_CHAIN + 1;   // +1 for the null terminator
	char* str_buf = new char[max_size];
	size_t converted = wcstombs(str_buf, wstr.c_str(), max_size);
	std::string result(str_buf);
	delete[] str_buf;
	setlocale(LC_ALL, original_locale);

	return result;
#endif 
}
