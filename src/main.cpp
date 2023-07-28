#define DLLExport extern "C" __declspec(dllexport)

#include <string>
#include "Debug.h"
#include "baseFederate.h"

using namespace std;

baseFederate _baseFederate;

DLLExport void Connect(const char* federationName, const char* fomFilePath)
{
    Debug::init("hla_plugin_log.txt");

	_baseFederate = baseFederate();

    string federationNameStr(federationName);

    wstring federationNameW(federationNameStr.begin(), federationNameStr.end());

    _baseFederate.connect(federationNameW);
}

DLLExport void Disconnect()
{
    _baseFederate.disconnect();

    Debug::close();
}