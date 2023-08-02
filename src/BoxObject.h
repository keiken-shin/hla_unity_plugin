#pragma once
#include <RTI/encoding/BasicDataElements.h>
#include <RTI/RTIambassador.h>
#include "DataInterface.h"
#include "Debug.h"

using namespace std;
using namespace rti1516e;
namespace RTI = rti1516e;

class BoxObject
{
public:
    static HLAfloat32LE floatDecoder;
    static int idCount;
    static ObjectClassHandle boxObjectHandle;

    static AttributeHandle positionXHandle;
    static AttributeHandle positionYHandle;

    static bool initiated;

    static void init(shared_ptr<RTIambassador> _rtiAmbassador);
    static void getAttributeSet(AttributeHandleSet *attributeSet);

    BoxObject();
    BoxObject(ObjectInstanceHandle hlaInstanceHandle);
    ~BoxObject();

    void updateAttributes(AttributeHandleValueMap const & theAttributeValue);
    void getAttributeMap(AttributeHandleSet const & theAttributes, AttributeHandleValueMap* attributeMap);
    void getAttributeMap(AttributeHandleValueMap* attributeMap);

    void setBoxObject(BoxObjectData boxObjectData);
    BoxObjectData getBoxObjectData();

    ObjectInstanceHandle hlaInstanceHandle; // Used to recognize hlaObject

    int id; // Use to recognize object in out simulation. Can be different in other simulation.
    float positionX;
    float positionY;
};