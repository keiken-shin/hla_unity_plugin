#include "baseFederate.h"

baseFederate::baseFederate()
{
    _connect = false;
}

baseFederate::~baseFederate() {}

void baseFederate::connect(wstring federationName, wstring federateName, wstring fomFilePath)
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
    _connect = true;    // If connection established

    // Destroy pre-existing federation execution
    try {
		_rtiAmbassador->destroyFederationExecution(federationName);
	}
	catch (const rti1516e::FederatesCurrentlyJoined& e) {
        Debug::Log("------- Exception occurred, FederatesCurrentlyJoined -------");
        Debug::Log(e.what());
        Debug::Log("------- End Exception -------");
	}
	catch (const rti1516e::FederationExecutionDoesNotExist& e) {
        Debug::Log("------- Exception occurred, FederationExecutionDoesNotExist -------");
        Debug::Log(e.what());
        Debug::Log("------- End Exception -------");
	}
	catch (const rti1516e::RTIinternalError& e) {
        Debug::Log("------- Exception occurred, RTIinternalError -------");
        Debug::Log(e.what());
        Debug::Log("------- End Exception -------");
	}
    Debug::Log("After federation destroyed...");
    
    // Always try to create the federation execution.
    // This is needed, since we do not have any special federate that has the responsibility
    // to create the federation execution.
    // Make sure to catch the exception!
    try
    {
        Debug::Log(federationName);
        Debug::Log(federateName);
        Debug::Log(fomFilePath);
        _rtiAmbassador->createFederationExecution(federationName, fomFilePath);
    }
    catch(const FederationExecutionAlreadyExists&)
    {
        // The federation execution already exist, so we can ignore this part.
    }
    catch(const Exception& e)
    {
        Debug::Log("------- Exception occurred, createFederation -------");
        Debug::Log(e.what());
        Debug::Log("------- End Exception -------");
        throw;
    }
    Debug::Log("Successfully created federation execution");

    // Join the federation. If the federate name is taken,
    // add a sequence number to it to make it unique and try again.
    bool joined = false;
    int sequenceNumber = 1;
    wstring uniqueName = federateName;

    while(!joined)
    {
        try
        {
            FederateHandle federateHandle = _rtiAmbassador->joinFederationExecution(uniqueName, federationName);

            joined = true;
            federateName = uniqueName;
        }
        catch(const FederateNameAlreadyInUse&)
        {
            uniqueName = federateName + L"_" + toWString(sequenceNumber);
            ++sequenceNumber;
        }
        catch(const Exception& e)
        {
            Debug::Log(e.what());
        }
    }
    Debug::Log("Successfully joined the federation");
}

void baseFederate::disconnect()
{
    if (_connect)
    {
        // When we disconnect from the federation execution we want to: 
		//  - Cancel any pending ownership acquisitions
		//  - Delete the objects created by us
		//  - Divest any owned attributes
		try {
			_rtiAmbassador->resignFederationExecution(CANCEL_THEN_DELETE_THEN_DIVEST);

			// we don't have to handle these exceptions
		}
		catch (const rti1516e::InvalidResignAction&) {
		}
		catch (const rti1516e::OwnershipAcquisitionPending&) {
		}
		catch (const rti1516e::FederateOwnsAttributes&) {
		}
		catch (const rti1516e::FederateNotExecutionMember&) {
		}
		catch (const rti1516e::NotConnected&) {
		}
		catch (const rti1516e::CallNotAllowedFromWithinCallback&) {
		}
		catch (const rti1516e::RTIinternalError&) {
		}

		// Just as we try and create the federation execution we will try and 
		// destroy it since we cannot know if we're the last one to resign.
		try {
			_rtiAmbassador->destroyFederationExecution(_federationName);

			// we don't have to handle these exceptions
		}
		catch (const rti1516e::FederatesCurrentlyJoined&) {
		}
		catch (const rti1516e::FederationExecutionDoesNotExist&) {
		}
		catch (const rti1516e::NotConnected&) {
		}
		catch (const rti1516e::RTIinternalError&) {
		}

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

/////////////////////////////////////////////
//  Implementation methods to get objects  //
/////////////////////////////////////////////
vector<BoxObject> baseFederate::getBoxObject() 
{
    return _boxes;
}

/////////////////////////////////////////////////////
//  Implementation methods to publish object event //
/////////////////////////////////////////////////////
void baseFederate::publishUnit()
{
    Debug::Log("Start publishing unit...");

    try
    {
        if (!BoxObject::initiated)
        {
            BoxObject::init(_rtiAmbassador);
        }
        
        // Get handles for the object class and attributes
        AttributeHandleSet boxObjectAttribute;
        BoxObject::getAttributeSet(&boxObjectAttribute);

        // Publish the attributes
        _rtiAmbassador->publishObjectClassAttributes(BoxObject::boxObjectHandle, boxObjectAttribute);
        Debug::Log("Published unit");
    }
    catch(const Exception& e)
    {
        Debug::Log(e.what());
    }
    
}

////////////////////////////////////////////////////
//  Implementation methods to create object event //
////////////////////////////////////////////////////
int baseFederate::createUnit()
{
    Debug::Log("Create unit");

    try
    {
        // Create the Box object instance
        ObjectInstanceHandle obj = _rtiAmbassador->registerObjectInstance(BoxObject::boxObjectHandle);

        BoxObject newBox(obj);
        _boxes.push_back(newBox);

        Debug::Log("Created object: ", newBox.id);

        return newBox.id;
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
}

////////////////////////////////////////////////////
//  Implementation methods to update object event //
////////////////////////////////////////////////////
void baseFederate::updateUnit(BoxObjectData boxObjectData)
{
    Debug::Log("Update unit: ", boxObjectData.id);

    vector<BoxObject>::iterator it;
    it = find_if(_boxes.begin(), _boxes.end(), [&](BoxObject const & obj) 
    {
        return obj.id == boxObjectData.id;
    });

    if (it != _boxes.end())
    {
        it->setBoxObject(boxObjectData);
        AttributeHandleValueMap attributeMap;
        it->getAttributeMap(&attributeMap);
        _rtiAmbassador->updateAttributeValues(it->hlaInstanceHandle, attributeMap, VariableLengthData());

        Debug::Log("PositionX: ", boxObjectData.positionX);
        Debug::Log("PositionY: ", boxObjectData.positionY);
        Debug::Log("Updated unit");
    }
    else
    {
        Debug::Log("Unable to find any object");
    }
}

////////////////////////////////////////////////////
//  Implementation methods to remove object event //
////////////////////////////////////////////////////
void baseFederate::removeUnit(BoxObjectData boxObjectData) 
{
    Debug::Log("Remove Unit");

    vector<BoxObject>::iterator box;
    box = std::find_if(_boxes.begin(), _boxes.end(), [&](BoxObject const& obj) {
        return obj.id == boxObjectData.id;
    });

    if (box != _boxes.end()) 
    {
        _rtiAmbassador->deleteObjectInstance(box->hlaInstanceHandle, VariableLengthData());
        _boxes.erase(box);
    }
    else 
    {
        Debug::Log("No box object found");
    }
}

///////////////////////////////////////////////////////
//  Implementation methods to subscribe object event //
//////////////////////////////////////////////////////
void baseFederate::subscribeUnit()
{
    Debug::Log("Subscribe unit");

    try
    {
        if (!BoxObject::initiated)
        {
            BoxObject::init(_rtiAmbassador);

            Debug::Log("Initialized unit");
        }

        AttributeHandleSet boxAttribute;
        BoxObject::getAttributeSet(&boxAttribute);

        _rtiAmbassador->subscribeObjectClassAttributes(BoxObject::boxObjectHandle, boxAttribute);

        Debug::Log("Unit subscribed");
    }
    catch(const Exception& e)
    {
        Debug::Log(e.what());
    }
    
}


////////////////////////////////////////////////////////
//  Implementation methods to handle discovery event //
///////////////////////////////////////////////////////
void baseFederate::discoveryObjectImplementation(
	ObjectInstanceHandle theObject,
	ObjectClassHandle theObjectClass)
    throw (FederateInternalError)
{
    Debug::Log("Object discovered");

    if (theObjectClass == BoxObject::boxObjectHandle)
    {
        BoxObject newBox(theObject);
        _boxes.push_back(newBox);
    }
    else 
    {
        Debug::Log("Do not recognize object class in discover");
    }
}

//////////////////
//  Discovery  //
/////////////////
void baseFederate::discoverObjectInstance(
	ObjectInstanceHandle theObject,
	ObjectClassHandle theObjectClass,
	std::wstring const & theObjectInstanceName,
	FederateHandle producingFederate)
	throw (
		FederateInternalError){discoveryObjectImplementation(theObject, theObjectClass);}

void baseFederate::discoverObjectInstance(
	ObjectInstanceHandle theObject,
	ObjectClassHandle theObjectClass,
	std::wstring const & theObjectInstanceName)
	throw (
		FederateInternalError) {discoveryObjectImplementation(theObject, theObjectClass);}