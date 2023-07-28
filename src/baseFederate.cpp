#include "baseFederate.h"

baseFederate::baseFederate()
{
    _connect = false;
}

baseFederate::~baseFederate() {}

void baseFederate::connect(wstring federationName)
{
    Debug::Log("Starting connection...");

    _federationName = federationName;

    try
    {
        // From RTIambassadorFactor instance create RTIambassador
        shared_ptr<RTIambassadorFactory> rtiAmbassadorFactory(new RTIambassadorFactory());
        _rtiAmbassador = rtiAmbassadorFactory->createRTIambassador();

        if (_rtiAmbassador.get())
        {
            Debug::Log("Created RTI ambassador.");
        }
    }
    catch(const Exception& e)
    {
        Debug::Log(e.what());
		throw;
    }
    
    _connect = true;
}

void baseFederate::disconnect()
{
    if (_connect)
    {
        _connect = false;
        Debug::Log("Disconnected.");
    }
}