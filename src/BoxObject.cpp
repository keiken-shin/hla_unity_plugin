#include "BoxObject.h"

HLAfloat32LE BoxObject::floatDecoder;
int BoxObject::idCount = 0;

ObjectClassHandle BoxObject::boxObjectHandle;

AttributeHandle BoxObject::positionXHandle;
AttributeHandle BoxObject::positionYHandle;

bool BoxObject::initiated = false;

void BoxObject::init(shared_ptr<RTIambassador> _rtiAmbassador)
{
    Debug::Log("Init Box Object");

    boxObjectHandle = _rtiAmbassador->getObjectClassHandle(L"HLAobjectRoot.Box");
    positionXHandle = _rtiAmbassador->getAttributeHandle(boxObjectHandle, L"PositionX");
    positionYHandle = _rtiAmbassador->getAttributeHandle(boxObjectHandle, L"PositionY");
    
    initiated = true;
}

void BoxObject::getAttributeSet(AttributeHandleSet * attributeSet)
{
    Debug::Log("Get attributes & set it to box object");

    attributeSet->insert(positionXHandle);
    attributeSet->insert(positionYHandle);
}

BoxObject::BoxObject() {}

BoxObject::BoxObject(ObjectInstanceHandle hlaInstanceHandle)
{
    id = idCount;
    idCount++;

    this->hlaInstanceHandle = hlaInstanceHandle;

    positionX = 0.0;
    positionY = 0.0;
}

BoxObject::~BoxObject() {}

void BoxObject::updateAttributes(AttributeHandleValueMap const & theAttributeValues)
{
    Debug::Log("Update attributes of box object");

    AttributeHandleValueMap::const_iterator 
    toUpdate = theAttributeValues.find(positionXHandle); // Position X
    if (toUpdate != theAttributeValues.end())
    {
        floatDecoder.decode(toUpdate->second);
        positionX = floatDecoder.get();
    }
    // Position Y
    toUpdate = theAttributeValues.find(positionYHandle);
    if (toUpdate != theAttributeValues.end())
    {
        floatDecoder.decode(toUpdate->second);
        positionY = floatDecoder.get();
    }
}

void BoxObject::getAttributeMap(AttributeHandleSet const & theAttributes, AttributeHandleValueMap * attributeMap)
{
    Debug::Log("Get attributes of box object");

    AttributeHandleSet::const_iterator
    toProvide = theAttributes.find(positionXHandle);    // Get position X
    if (toProvide != theAttributes.end())
    {
        floatDecoder.set(positionX);
        attributeMap->insert(pair<AttributeHandle, VariableLengthData>(*toProvide, floatDecoder.encode()));
    }
    // Get position Y
    toProvide = theAttributes.find(positionYHandle);
    if (toProvide != theAttributes.end())
    {
        floatDecoder.set(positionY);
        attributeMap->insert(pair<AttributeHandle, VariableLengthData>(*toProvide, floatDecoder.encode()));
    }
}

void BoxObject::getAttributeMap(AttributeHandleValueMap * attributeMap)
{
    Debug::Log("Get attributes of box object");

    // Position X
    floatDecoder.set(positionX);
    attributeMap->insert(pair<AttributeHandle, VariableLengthData>(positionXHandle, floatDecoder.encode()));
    // Position Y
    floatDecoder.set(positionY);
    attributeMap->insert(pair<AttributeHandle, VariableLengthData>(positionYHandle, floatDecoder.encode()));
}

void BoxObject::setBoxObject(BoxObjectData boxObjectData)
{
    Debug::Log("Set box object data");

    positionX = boxObjectData.positionX;
    positionY = boxObjectData.positionY;
}

BoxObjectData BoxObject::getBoxObjectData()
{
    Debug::Log("Get box object data");

    BoxObjectData data;

    data.id = id;
    data.positionX = positionX;
    data.positionY = positionY;

    return data;
}