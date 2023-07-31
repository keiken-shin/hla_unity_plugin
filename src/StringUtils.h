#ifndef STRING_UTILS_H
#define STRING_UTILS_H

#include <iostream>
#include <string>
#include <locale>
#include <codecvt>
#include <sstream>
#include <algorithm>

using namespace std;

namespace StringUtils
{
    // convert string to type T
    template<class T>
    T fromString(const string& s)
    {
        istringstream stream(s);
        T t;
        stream >> t;
        return t;
    }

    // convert string to type T
    template<class T>
    T fromWString(const wstring& ws)
    {
        wistringstream wstream(ws);
        T t;
        wstream >> t;
        return t;
    }

    // convert type T to wstring
    template<class T>
    wstring toWString(T t)
    {
        wstringstream wss;
        wss << t;
        return wss.str();
    }

    // convert string to wstring
    wstring str2wstr(const string& s);

    // convert wstring to string
    string wstr2str(const wstring& s);
}

#endif