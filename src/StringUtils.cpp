#include "StringUtils.h"
#include <iostream>

wstring StringUtils::str2wstr(const string& s)
{
    wstring_convert<codecvt_utf8<wchar_t>> converter;
    return converter.from_bytes(s);
}

string StringUtils::wstr2str(const wstring& s)
{
    return string(s.begin(), s.end());
}