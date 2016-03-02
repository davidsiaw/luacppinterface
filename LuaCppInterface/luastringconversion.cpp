#include "luastringconversion.h"
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

