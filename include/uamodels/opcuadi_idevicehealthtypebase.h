/******************************************************************************
** opcuadi_idevicehealthtypebase.h
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

#ifndef __OPCUADI_IDEVICEHEALTHTYPEBASE_H__
#define __OPCUADI_IDEVICEHEALTHTYPEBASE_H__

#include "opcua_baseinterfacetype.h"
#include "opcuadi_datatypes.h"
#include "basenodes.h"
#include "opcua_basedatavariabletype.h"
#include "opcua_foldertype.h"
#include "opcuadi_identifiers.h"
#include "opcuadi_instancefactory_devices.h"

// Namespace for the UA information model http://opcfoundation.org/UA/DI/
namespace OpcUaDi {


/** Generated base class for a IDeviceHealthType.
 *
 *  This class contains the generated base code for the object type IDeviceHealthType
 *  representing an OPC UA ObjectType. This class is used to create the object type and to
 *  create and represent instances of the object type in the server address space.
 *
 *  **Object members of the IDeviceHealthType:**
 *
 *  Browse Name        | TypeDefinition | Modelling Rule | See Also
 *  -------------------|----------------|----------------|---------------------------
 *  DeviceHealthAlarms | FolderType     | Optional       | \ref getDeviceHealthAlarms
 *
 *  **Variable members of the IDeviceHealthType:**
 *
 *  Browse Name  | DataType                | TypeDefinition       | Modelling Rule | See Also
 *  -------------|-------------------------|----------------------|----------------|-------------------------------------------
 *  DeviceHealth | DeviceHealthEnumeration | BaseDataVariableType | Optional       | \ref getDeviceHealth, \ref setDeviceHealth
 *
 */
class UAMODELS_EXPORT IDeviceHealthTypeBase:
    public OpcUa::BaseInterfaceType
{
    UA_DISABLE_COPY(IDeviceHealthTypeBase);
protected:
    virtual ~IDeviceHealthTypeBase();
public:
    // construction / destruction
    IDeviceHealthTypeBase(const UaNodeId& nodeId, UaObject* pInstanceDeclarationObject, NodeManagerConfig* pNodeConfig, UaMutexRefCounted* pSharedMutex = NULL);
    IDeviceHealthTypeBase(const UaNodeId& nodeId, const UaString& name, OpcUa_UInt16 browseNameNameSpaceIndex, NodeManagerConfig* pNodeConfig, UaMutexRefCounted* pSharedMutex = NULL);
    IDeviceHealthTypeBase(
        UaBase::Object*    pBaseNode,
        XmlUaNodeFactoryManager*   pFactory,
        NodeManagerConfig* pNodeConfig,
        UaMutexRefCounted* pSharedMutex = NULL);
    static void createTypes();
    static void clearStaticMembers();

    virtual UaNodeId       typeDefinitionId() const;


    virtual void setDeviceHealth(OpcUaDi::DeviceHealthEnumeration DeviceHealth);
    virtual OpcUaDi::DeviceHealthEnumeration getDeviceHealth() const;

    virtual OpcUa::BaseDataVariableType* getDeviceHealthNode();
    virtual const OpcUa::BaseDataVariableType* getDeviceHealthNode() const;
    virtual OpcUa::FolderType* getDeviceHealthAlarms();
    virtual const OpcUa::FolderType* getDeviceHealthAlarms() const;

protected:
    // Object nodes
    // Object DeviceHealthAlarms
    static OpcUa::FolderType*  s_pDeviceHealthAlarms;
    OpcUa::FolderType*  m_pDeviceHealthAlarms;

    // Variable nodes
    // Variable DeviceHealth
    static OpcUa::BaseDataVariableType*  s_pDeviceHealth;
    OpcUa::BaseDataVariableType*  m_pDeviceHealth;



private:
    void initialize();

private:
    static bool s_typeNodesCreated;
};

} // End namespace for the UA information model http://opcfoundation.org/UA/DI/

#endif // #ifndef __OPCUADIIDEVICEHEALTHTYPEBASE_H__


