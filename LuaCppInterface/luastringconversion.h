#pragma once

#include <string>
#include <Windows.h>

std::wstring utf8str_to_wstr(const std::string& utf8str);
std::string wstr_to_utf8str(const std::wstring& wstr);