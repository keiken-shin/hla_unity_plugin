#define DLLExport extern "C" __declspec(dllexport)

#include <string>
#include "Debug.h"

using namespace std;

DLLExport void Connect(const char* federationName, const char* fomFilePath)
{
    Debug::init("hla_plugin_log.txt");

    Debug::Log("Inside connect...");
}

DLLExport void Disconnect()
{
    Debug::Log("Inside disconnect...");
    
    Debug::close();
}