#include "luastringconversion.h"

#if defined(_WIN32) || defined(WIN32)
#include <Windows.h>

std::wstring UTF8ToWStr(const std::string& utf8str)
{
	if (utf8str.empty())
		return L"";

	std::wstring wstr;
	int wlen = MultiByteToWideChar(CP_UTF8, NULL, utf8str.c_str(), (int) utf8str.size(), NULL, NULL);
	
	if (wlen == 0)
		return L"String conversion error";

	wstr.resize(wlen);

	wlen = MultiByteToWideChar(CP_UTF8, NULL, utf8str.c_str(), (int) utf8str.size(), (wchar_t*)wstr.data(), wlen);
	
	if (wlen == 0)
		return L"String conversion error";

	return wstr;
}

std::string WStrToUTF8(const std::wstring& wstr)
{
	if (wstr.empty())
		return "";

	std::string utf8str;
	int len = WideCharToMultiByte(CP_UTF8, NULL, wstr.c_str(), (int) wstr.size(), NULL, NULL, NULL, NULL);
	
	if (len == 0)
		return "String conversion error";

	utf8str.resize(len);
	len = WideCharToMultiByte(CP_UTF8, NULL, wstr.c_str(), (int) wstr.size(), (char*)utf8str.data(), len, NULL, NULL);
	
	if (len == 0)
		return "String conversion error";

	return utf8str;
}

#else
#include <iconv.h>
// TODO: write an implimentation for Linux/MacOS
#endif

// perhaps this implementation? Should be portable, but may have problems with VS2010

/*
std::wstring UTF8ToWStr(const std::string& str)
{
	std::wstring_convert<std::codecvt_utf8<wchar_t>> conv;
	return conv.from_bytes(str);
}

std::string WStrToUTF8(const std::wstring& str)
{
	std::wstring_convert<std::codecvt_utf8<wchar_t>> conv;
	return conv.to_bytes(str);
}
*/
