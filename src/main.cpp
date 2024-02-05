#define DLLExport extern "C" __declspec(dllexport)

#include <iostream>
#include <string>
#include <locale>
#include <codecvt>
#include <Windows.h>
#include "Debug.h"
#include "StringUtils.h"
#include "baseFederate.h"

using namespace std;
using namespace StringUtils;

baseFederate _baseFederate;

DLLExport void Connect(const char* federationName, const char* federateName, const char* fomFilePath)
{
    Debug::init("hla_plugin_log.txt");

	_baseFederate = baseFederate();


    // Convert char* to string
    string federationNameStr(federationName);
    string federateNameStr(federateName);
    string fomFilePathStr(fomFilePath);

    // Convert string to wstring
    wstring federationNameW = str2wstr(federationNameStr);
    wstring federateNameW = str2wstr(federateNameStr);
    wstring fomFilePathW = str2wstr(fomFilePathStr);

    _baseFederate.connect(federationNameW, federateNameW, fomFilePathW);
}

DLLExport void Disconnect()
{
    _baseFederate.disconnect();

    Debug::close();
}

DLLExport void PublishUnit()
{
    _baseFederate.publishUnit();
}

DLLExport int CreateUnit()
{
    return _baseFederate.createUnit();
}

DLLExport void UpdateUnit(BoxObjectData boxObjectData)
{
    _baseFederate.updateUnit(boxObjectData);
}

DLLExport void SubscribeUnit()
{
    _baseFederate.subscribeUnit();
}

DLLExport BoxObjectData* GetBoxes(int &size) {
	vector<BoxObject> data = _baseFederate.getBoxObject();
	size = data.size();
	BoxObjectData *dataToReturn = (BoxObjectData*)CoTaskMemAlloc(sizeof(BoxObjectData) * size);


	for (int i=0; i<size; i++)
	{
		dataToReturn[i] = data[i].getBoxObjectData();
		Debug::_log << "Get box main: ID: " << dataToReturn[i].id << " pozX: " << dataToReturn[i].positionX << " pozY: " << dataToReturn[i].positionY << endl;
	}
	return dataToReturn;
}