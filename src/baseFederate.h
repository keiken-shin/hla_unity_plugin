#pragma once
#include <RTI/NullFederateAmbassador.h>
#include <RTI/RTIambassadorFactory.h>
#include <RTI/RTIambassador.h>
#include <string>
#include <memory>
#include "Debug.h"
#include "StringUtils.h"
#include "BoxObject.h"

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
    
    vector<BoxObject> _boxes;  
    
public:
    // Constructor
    baseFederate();

    // Destructor
    ~baseFederate();

    // RTI connect/disconnect methods
    void connect(wstring federationName, wstring federateName, wstring fomFilePath);
    void disconnect();

    // Get Units
    vector<BoxObject> getBoxObject();

    // Publish object event
    void publishUnit();

    // Create object
    int createUnit();

    // Update object
    void updateUnit(BoxObjectData boxObjectData);

    // Remove object
    void removeUnit(BoxObjectData BoxObjectData);

    // Subscribe object
    void subscribeUnit();

    ////////////////////////////////////////////////////////
	//  Implementation methods to handle discovery event //
	///////////////////////////////////////////////////////
	void discoveryObjectImplementation(
        ObjectInstanceHandle theObject, 
        ObjectClassHandle theObjectClass)
        throw (FederateInternalError);

    ////////////////////////////////////////////////////////
	//  Implementation methods to handle reflect event //
	///////////////////////////////////////////////////////
    void reflectAttributeValuesImpl(
        ObjectInstanceHandle theObject,
        AttributeHandleValueMap const & theAttributeValues)
        throw (FederateInternalError);

    ////////////////////////////////////////////////////////////
    //  Implementation methods to handle remove object event //
    ///////////////////////////////////////////////////////////
    void removeObjectInstanceImpl(
        ObjectInstanceHandle theObject)
        throw (FederateInternalError);

    ////////////////////////////////////////////////////////////////
	//  Implementation methods to handle provide Attribute event //
	///////////////////////////////////////////////////////////////
    void provideAttributeValueUpdateImpl(
        ObjectInstanceHandle theObject,
        AttributeHandleSet const & theAttributes)
        throw (FederateInternalError);

    //////////////////
	//  Discovery  //
	/////////////////
	 void discoverObjectInstance(
		ObjectInstanceHandle theObject,
		ObjectClassHandle theObjectClass,
		std::wstring const & theObjectInstanceName)
		throw (
			FederateInternalError);

	 void discoverObjectInstance(
		ObjectInstanceHandle theObject,
		ObjectClassHandle theObjectClass,
		std::wstring const & theObjectInstanceName,
		FederateHandle producingFederate)
		throw (
			FederateInternalError);

    ////////////////
	//  Reflect  //
	///////////////
    void reflectAttributeValues(
        ObjectInstanceHandle theObject,
        AttributeHandleValueMap const & theAttributeValues,
        VariableLengthData const & theUserSuppliedTag,
        OrderType sentOrder,
        TransportationType theType,
        SupplementalReflectInfo theReflectInfo)
        throw (FederateInternalError);

    void reflectAttributeValues(
        ObjectInstanceHandle theObject,
        AttributeHandleValueMap const & theAttributeValues,
        VariableLengthData const & theUserSuppliedTag,
        OrderType sentOrder,
        TransportationType theType,
        LogicalTime const & theTime,
        OrderType receivedOrder,
        SupplementalReflectInfo theReflectInfo)
        throw (FederateInternalError);

    void reflectAttributeValues(
        ObjectInstanceHandle theObject,
        AttributeHandleValueMap const & theAttributeValues,
        VariableLengthData const & theUserSuppliedTag,
        OrderType sentOrder,
        TransportationType theType,
        LogicalTime const & theTime,
        OrderType receivedOrder,
        MessageRetractionHandle theHandle,
        SupplementalReflectInfo theReflectInfo)
        throw (FederateInternalError);

    //////////////
	//  Remove  //
	/////////////
    void removeObjectInstance(
        ObjectInstanceHandle theObject,
        VariableLengthData const & theUserSuppliedTag,
        OrderType sentOrder,
        SupplementalRemoveInfo theRemoveInfo)
        throw (FederateInternalError);

    void removeObjectInstance(
        ObjectInstanceHandle theObject,
        VariableLengthData const & theUserSuppliedTag,
        OrderType sentOrder,
        LogicalTime const & theTime,
        OrderType receivedOrder,
        SupplementalRemoveInfo theRemoveInfo)
        throw (FederateInternalError);

    void removeObjectInstance(
        ObjectInstanceHandle theObject,
        VariableLengthData const & theUserSuppliedTag,
        OrderType sentOrder,
        LogicalTime const & theTime,
        OrderType receivedOrder,
        MessageRetractionHandle theHandle,
        SupplementalRemoveInfo theRemoveInfo)
        throw (FederateInternalError);

    ///////////////
	//  Provide  //
	//////////////
    void provideAttributeValueUpdate(
        ObjectInstanceHandle theObject,
        AttributeHandleSet const & theAttributes,
        VariableLengthData const & theUserSuppliedTag)
        throw (FederateInternalError);
};