#pragma once

#ifdef HLAPLUGIN_EXPORTS
    #define HLAPLUGIN_API __declspec(dllexport)
#else
    #define HLAPLUGIN_API __declspec(dllimport)
#endif

struct HLAPLUGIN_API BoxObjectData
{
    int id;
    float positionX;
    float positionY;
};