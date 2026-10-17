/******************************************************************************
** opcuadi_devicehealthdiagnosticalarmtypebase.h
**
** Copyright (c) 2006-2020 Unified Automation GmbH. All rights reserved.
**
** Software License Agreement ("SLA") Version 2.7
**
** Unless explicitly acquired and licensed from Licensor under another
** license, the contents of this file are subject to the Software License
** Agreement ("SLA") Version 2.7, or subsequent versions
** as allowed by the SLA, and You may not copy or use this file in either
** source code or executable form, except in compliance with the terms and
** conditions of the SLA.
**
** All software distributed under the SLA is provided strictly on an
** "AS IS" basis, WITHOUT WARRANTY OF ANY KIND, EITHER EXPRESS OR IMPLIED,
** AND LICENSOR HEREBY DISCLAIMS ALL SUCH WARRANTIES, INCLUDING WITHOUT
** LIMITATION, ANY WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR
** PURPOSE, QUIET ENJOYMENT, OR NON-INFRINGEMENT. See the SLA for specific
** language governing rights and limitations under the SLA.
**
** The complete license agreement can be found here:
** http://unifiedautomation.com/License/SLA/2.7/
**
** Project: C++ OPC Server SDK information model for namespace http://opcfoundation.org/UA/DI/
**
** Description: OPC Unified Architecture Software Development Kit.
**
******************************************************************************/

#ifndef __OPCUADI_DEVICEHEALTHDIAGNOSTICALARMTYPEBASE_H__
#define __OPCUADI_DEVICEHEALTHDIAGNOSTICALARMTYPEBASE_H__

#include "opcua_instrumentdiagnosticalarmtype.h"
#include "opcuadi_datatypes.h"
#include "basenodes.h"
#include "opcuadi_datatypes.h"
#include "opcuadi_identifiers.h"
#include "opcuadi_instancefactory_devices.h"

// Namespace for the UA information model http://opcfoundation.org/UA/DI/
namespace OpcUaDi {

class DeviceHealthDiagnosticAlarmTypeBase;

/** Generated event data class for a DeviceHealthDiagnosticAlarmType.
 *
 *  This class contains the auto generated code for the object type DeviceHealthDiagnosticAlarmType
 *  providing UaEventData interface for the access to event data containing the current state of the
 *  condition for events sent to the client. The class is used for condition events if the condition has
 *  no nodes in the address space or for condition branches created as snapshot of the main branch.

 */
class UAMODELS_EXPORT DeviceHealthDiagnosticAlarmTypeData:
    public OpcUa::InstrumentDiagnosticAlarmTypeData
{
    UA_DISABLE_COPY(DeviceHealthDiagnosticAlarmTypeData);
protected:
    virtual ~DeviceHealthDiagnosticAlarmTypeData();
public:
    DeviceHealthDiagnosticAlarmTypeData();
    void initializeAsBranch(DeviceHealthDiagnosticAlarmTypeBase* pCondition);
    void initializeAsBranch(DeviceHealthDiagnosticAlarmTypeData* pConditionData);
    virtual void getFieldData(OpcUa_UInt32 index, Session* pSession, OpcUa_Variant& data);


private:
    void initialize();

private:
    UaObjectPointerArray<UaVariant> m_FieldValues;
};


/** Generated base class for a DeviceHealthDiagnosticAlarmType.
 *
 *  This class contains the auto generated code for the object type DeviceHealthDiagnosticAlarmType
 *  representing an OPC UA condition type. This class is used to create the condition type and to
 *  create and represent the condition object in the server address space. It provides also the UaEventData
 *  interface for the access to event data containing the current state of the condition for events sent to
 *  the client.
 *
 */
class UAMODELS_EXPORT DeviceHealthDiagnosticAlarmTypeBase:
    public OpcUa::InstrumentDiagnosticAlarmType
{
    friend class DeviceHealthDiagnosticAlarmTypeData;
    UA_DISABLE_COPY(DeviceHealthDiagnosticAlarmTypeBase);
protected:
    // destruction
    virtual ~DeviceHealthDiagnosticAlarmTypeBase();
public:
    // construction
    DeviceHealthDiagnosticAlarmTypeBase(const UaNodeId& nodeId, UaObject* pInstanceDeclarationObject, NodeManagerConfig* pNodeConfig, const UaNodeId& sourceNode, const UaString& sourceName, UaMutexRefCounted* pSharedMutex = NULL);
    DeviceHealthDiagnosticAlarmTypeBase(const UaNodeId& nodeId, const UaString& name, OpcUa_UInt16 browseNameNameSpaceIndex, NodeManagerConfig* pNodeConfig, const UaNodeId& sourceNode, const UaString& sourceName, UaMutexRefCounted* pSharedMutex = NULL);
    DeviceHealthDiagnosticAlarmTypeBase(
        UaBase::Object*    pBaseNode,
        XmlUaNodeFactoryManager*   pFactory,
        NodeManagerConfig* pNodeConfig,
        UaMutexRefCounted* pSharedMutex = NULL);

    static void createTypes();
    static void clearStaticMembers();
    virtual UaNodeId typeDefinitionId() const;
    static void registerEventFields();
    static OpcUa_UInt32 registerOptionalEventFields(const UaString& fieldName);
    virtual void getFieldData(OpcUa_UInt32 index, Session* pSession, OpcUa_Variant& data);
    void clearFieldData();
    UaNodeId createBranch();


    virtual UaStatus triggerEvent(
        const UaDateTime&   time,
        const UaDateTime&   receiveTime,
        const UaByteString& eventId);

    virtual void getDeviceHealthDiagnosticAlarmTypeOptionalFieldData(OpcUa_UInt32 index, Session* pSession, OpcUa_Variant& data);

protected:


private:
    void initialize();
    void createChildren();

private:
    static bool                                 s_typeNodesCreated;
    static std::map<OpcUa_UInt32, OpcUa_UInt32> s_DeviceHealthDiagnosticAlarmTypeDataFields;
    UaObjectPointerArray<UaVariant>             m_FieldValues;
};

} // End namespace for the UA information model http://opcfoundation.org/UA/DI/

#endif // #ifndef __OPCUADIDEVICEHEALTHDIAGNOSTICALARMTYPEBASE_H__

