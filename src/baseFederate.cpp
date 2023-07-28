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
    
    try
	{
		// Call to connect to RTI -> informs the HLA runtime that the current class instance is ready to participate 
		// in the federation and specifies that it should join the federation immediately
		_rtiAmbassador->connect(*this, HLA_IMMEDIATE);
	}
	catch (const Exception& e)
	{
		Debug::Log(e.what());
		throw;
	}
	Debug::Log("Connection established successfully!");

    _connect = true;
}

void baseFederate::disconnect()
{
    if (_connect)
    {
        // Disconnect from the federation
		try
		{
			_rtiAmbassador->disconnect();
		}
		catch (const FederateIsExecutionMember&) {}
		catch (const CallNotAllowedFromWithinCallback&) {}
		catch (const RTIinternalError&) {}

        _connect = false;
        Debug::Log("Disconnected.");
    }
}