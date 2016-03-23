#include "luastringconversion.h"

#if defined(_WIN32) || defined(WIN32)
#include <Windows.h>

std::wstring UTF8ToWStr(const std::string& utf8str)
{
	if (utf8str.empty())
	{
		return L"";
	}

	std::wstring wstr;
	int wlen = MultiByteToWideChar(CP_UTF8, NULL, utf8str.c_str(), (int) utf8str.size(), NULL, NULL);
	
	if (wlen == 0)
	{
		return L"String conversion error";
	}

	wstr.resize(wlen);

	wlen = MultiByteToWideChar(CP_UTF8, NULL, utf8str.c_str(), (int) utf8str.size(), (wchar_t*)wstr.data(), wlen);
	
	if (wlen == 0)
	{
		return L"String conversion error";
	}

	return wstr;
}

std::string WStrToUTF8(const std::wstring& wstr)
{
	if (wstr.empty())
	{
		return "";
	}

	std::string utf8str;
	int len = WideCharToMultiByte(CP_UTF8, NULL, wstr.c_str(), (int) wstr.size(), NULL, NULL, NULL, NULL);
	
	if (len == 0)
	{
		return "String conversion error";
	}

	utf8str.resize(len);
	len = WideCharToMultiByte(CP_UTF8, NULL, wstr.c_str(), (int) wstr.size(), (char*)utf8str.data(), len, NULL, NULL);
	
	if (len == 0)
	{
		return "String conversion error";
	}

	return utf8str;
}

#else
#include <iconv.h>
#include <errno.h>
std::wstring UTF8ToWStr(const std::string& str)
{
	size_t c_wide_len = str.size();
	size_t c_wide_bytes = c_wide_len * sizeof(wchar_t);

	size_t c_mb_len = str.size() + 1;
	size_t c_mb_bytes = c_mb_len * sizeof(char);

	wchar_t* c_wide = new wchar_t[c_wide_len];
	char* c_mb = new char[c_mb_len];

	memset(c_wide, 0, c_wide_bytes);
	memset(c_mb, 0, c_mb_bytes);
	memcpy(c_mb, str.c_str(), str.size());

	char* m_wide = (char*)c_wide;
	char* m_mb = c_mb;

	iconv_t cd = iconv_open("UTF-16LE", "UTF-8");
	size_t inbytesleft = c_mb_bytes;
	size_t outbytesleft = c_wide_bytes;
	size_t res = iconv(cd, &m_mb, &inbytesleft, &m_wide, &outbytesleft);

	std::wstring wide_result(c_wide);
	delete[] c_wide;
	delete[] c_mb;
	iconv_close(cd);

	return wide_result;
}

std::string WStrToUTF8(const std::wstring& str)
{
	size_t max_size = str.size() * 3;
	wchar_t* c_wide = new wchar_t[str.size()+1];
	char* c_mb = new char[max_size];
	memset(c_wide, 0, (str.size()+1) * sizeof(wchar_t));
	memset(c_mb, 0, max_size * sizeof(char));
	memcpy(c_wide, str.c_str(), str.size() * sizeof(wchar_t));

	char* m_wide = (char*)c_wide;
	char* m_mb = c_mb;

	iconv_t cd = iconv_open("UTF-8", "UTF-16LE");
	size_t inbytesleft = str.size() * sizeof(wchar_t);
	size_t outbytesleft = max_size * sizeof(char);
	size_t res = iconv(cd, &m_wide, &inbytesleft, &m_mb, &outbytesleft);
	//std::cout << "in:" << inbytesleft << " orig:" << str.size() * sizeof(wchar_t) << std::endl;

	std::string result(c_mb);
	delete[] c_wide;
	delete[] c_mb;
	iconv_close(cd);

	return result;
}
#endif

