#include "BoxObject.h"

HLAfloat32LE BoxObject::floatDecoder;
int BoxObject::idCount = 0;

ObjectClassHandle BoxObject::boxObjectHandle;

AttributeHandle BoxObject::positionXHandle;
AttributeHandle BoxObject::positionYHandle;

bool BoxObject::initiated = false;

// Initialize the BoxObject class
void BoxObject::init(shared_ptr<RTIambassador> _rtiAmbassador)
{
    Debug::Log("Init Box Object");

    // Get handles for object class and attributes
    boxObjectHandle = _rtiAmbassador->getObjectClassHandle(L"HLAobjectRoot.Box");
    positionXHandle = _rtiAmbassador->getAttributeHandle(boxObjectHandle, L"PositionX");
    positionYHandle = _rtiAmbassador->getAttributeHandle(boxObjectHandle, L"PositionY");
    
    initiated = true;
}

// Get the attribute set for this BoxObject
void BoxObject::getAttributeSet(AttributeHandleSet * attributeSet)
{
    Debug::Log("Get attributes & set it to box object");

    // Insert attribute handles into the provided set
    attributeSet->insert(positionXHandle);
    attributeSet->insert(positionYHandle);
}

// Default constructor
BoxObject::BoxObject() {}

// Constructor with instance handle
BoxObject::BoxObject(ObjectInstanceHandle hlaInstanceHandle)
{
    // Initialize instance-specific properties
    id = idCount;
    idCount++;

    this->hlaInstanceHandle = hlaInstanceHandle;

    positionX = 0.0;
    positionY = 0.0;
}

// Destructor
BoxObject::~BoxObject() {}

// Update attributes based on provided values
void BoxObject::updateAttributes(AttributeHandleValueMap const & theAttributeValues)
{
    Debug::Log("Update attributes of box object");

    // Update Position X attribute if provided
    AttributeHandleValueMap::const_iterator 
    toUpdate = theAttributeValues.find(positionXHandle); // Position X
    if (toUpdate != theAttributeValues.end())
    {
        floatDecoder.decode(toUpdate->second);
        positionX = floatDecoder.get();
    }
    // Update Position Y attribute if provided
    toUpdate = theAttributeValues.find(positionYHandle);
    if (toUpdate != theAttributeValues.end())
    {
        floatDecoder.decode(toUpdate->second);
        positionY = floatDecoder.get();
    }
}

// Create a map of attributes to provide
void BoxObject::getAttributeMap(AttributeHandleSet const & theAttributes, AttributeHandleValueMap * attributeMap)
{
    Debug::Log("Get attributes of box object");

    // Get and encode Position X attribute if requested
    AttributeHandleSet::const_iterator
    toProvide = theAttributes.find(positionXHandle);    // Get position X
    if (toProvide != theAttributes.end())
    {
        floatDecoder.set(positionX);
        attributeMap->insert(pair<AttributeHandle, VariableLengthData>(*toProvide, floatDecoder.encode()));
    }
    // Get and encode Position Y attribute if requested
    toProvide = theAttributes.find(positionYHandle);
    if (toProvide != theAttributes.end())
    {
        floatDecoder.set(positionY);
        attributeMap->insert(pair<AttributeHandle, VariableLengthData>(*toProvide, floatDecoder.encode()));
    }
}

// Create a map of all attributes
void BoxObject::getAttributeMap(AttributeHandleValueMap * attributeMap)
{
    Debug::Log("Get attributes of box object");

     // Encode Position X attribute and add to map
    floatDecoder.set(positionX);
    attributeMap->insert(pair<AttributeHandle, VariableLengthData>(positionXHandle, floatDecoder.encode()));
    // Encode Position Y attribute and add to map
    floatDecoder.set(positionY);
    attributeMap->insert(pair<AttributeHandle, VariableLengthData>(positionYHandle, floatDecoder.encode()));
}

// Set properties based on provided data
void BoxObject::setBoxObject(BoxObjectData boxObjectData)
{
    Debug::Log("Set box object data");

    positionX = boxObjectData.positionX;
    positionY = boxObjectData.positionY;

    Debug::Log("Begin set box data");
    Debug::_log << positionX << ", " << positionX << endl;
    Debug::Log("End set box data");
}

// Get data to send to other simulations
BoxObjectData BoxObject::getBoxObjectData()
{
    Debug::Log("Get box object data");

    BoxObjectData data;

    data.id = id;
    data.positionX = positionX;
    data.positionY = positionY;
    
    Debug::Log("Begin read box data");
    Debug::_log << data.id << ", " << data.positionX << ", " << data.positionY << endl;
    Debug::Log("End read box data");
    
    return data;
}