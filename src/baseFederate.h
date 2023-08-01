#pragma once
#include <RTI/NullFederateAmbassador.h>
#include <RTI/RTIambassadorFactory.h>
#include <RTI/RTIambassador.h>
#include <string>
#include <memory>
#include "Debug.h"
#include "StringUtils.h"

using namespace std;
using namespace StringUtils;
using namespace rti1516e;
namespace RTI = rti1516e;

class baseFederate: public NullFederateAmbassador
{
private:
    bool _connect;
    wstring _federationName;
    shared_ptr<RTIambassador> _rtiAmbassador;
    
    ObjectClassHandle boxObject;
    AttributeHandle positionXAttributeHandle;
    AttributeHandle positionYAttributeHandle;
    
public:
    // Constructor
    baseFederate();

    // Destructor
    ~baseFederate();

    // RTI connect/disconnect methods
    void connect(wstring federationName, wstring federateName, wstring fomFilePath);
    void disconnect();

    // Publish object event
    void publishUnit();
};