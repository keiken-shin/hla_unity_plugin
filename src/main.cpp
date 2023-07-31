#define DLLExport extern "C" __declspec(dllexport)

#include <iostream>
#include <string>
#include <locale>
#include <codecvt>
#include "Debug.h"
#include "baseFederate.h"

using namespace std;

baseFederate _baseFederate;

wstring stringToWstring(const std::string& str) {
    std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
    return converter.from_bytes(str);
}

DLLExport void Connect(const char* federationName, const char* federateName, const char* fomFilePath)
{
    Debug::init("hla_plugin_log.txt");

	_baseFederate = baseFederate();


    // Convert char* to string
    string federationNameStr(federationName);
    string federateNameStr(federateName);
    string fomFilePathStr(fomFilePath);

    // Convert string to wstring
    wstring federationNameW = stringToWstring(federationNameStr);
    wstring federateNameW = stringToWstring(federateNameStr);
    wstring fomFilePathW = stringToWstring(fomFilePathStr);

    _baseFederate.connect(federationNameW, federateNameW, fomFilePathW);
}

DLLExport void Disconnect()
{
    _baseFederate.disconnect();

    Debug::close();
}