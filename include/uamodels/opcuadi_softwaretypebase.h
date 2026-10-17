/******************************************************************************
** opcuadi_softwaretypebase.h
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

#ifndef __OPCUADI_SOFTWARETYPEBASE_H__
#define __OPCUADI_SOFTWARETYPEBASE_H__

#include "opcuadi_componenttype.h"
#include "opcuadi_datatypes.h"
#include "basenodes.h"
#include "opcua_propertytype.h"
#include "opcuadi_identifiers.h"
#include "opcuadi_instancefactory_devices.h"

// Namespace for the UA information model http://opcfoundation.org/UA/DI/
namespace OpcUaDi {


/** Generated base class for a SoftwareType.
 *
 *  This class contains the generated base code for the object type SoftwareType
 *  representing an OPC UA ObjectType. This class is used to create the object type and to
 *  create and represent instances of the object type in the server address space.
 *
 */
class UAMODELS_EXPORT SoftwareTypeBase:
    public OpcUaDi::ComponentType
{
    UA_DISABLE_COPY(SoftwareTypeBase);
protected:
    virtual ~SoftwareTypeBase();
public:
    // construction / destruction
    SoftwareTypeBase(const UaNodeId& nodeId, UaObject* pInstanceDeclarationObject, NodeManagerConfig* pNodeConfig, UaMutexRefCounted* pSharedMutex = NULL);
    SoftwareTypeBase(const UaNodeId& nodeId, const UaString& name, OpcUa_UInt16 browseNameNameSpaceIndex, NodeManagerConfig* pNodeConfig, UaMutexRefCounted* pSharedMutex = NULL);
    SoftwareTypeBase(
        UaBase::Object*    pBaseNode,
        XmlUaNodeFactoryManager*   pFactory,
        NodeManagerConfig* pNodeConfig,
        UaMutexRefCounted* pSharedMutex = NULL);
    static void createTypes();
    static void clearStaticMembers();

    virtual UaNodeId       typeDefinitionId() const;


    // Manufacturer defined by base type

    // Model defined by base type

    // SoftwareRevision defined by base type


protected:
    // Variable nodes
    // Variable Manufacturer
    static OpcUa::PropertyType*  s_pManufacturer;
    // Manufacturer defined by base type
    // Variable Model
    static OpcUa::PropertyType*  s_pModel;
    // Model defined by base type
    // Variable SoftwareRevision
    static OpcUa::PropertyType*  s_pSoftwareRevision;
    // SoftwareRevision defined by base type



private:
    void initialize();

private:
    static bool s_typeNodesCreated;
};

} // End namespace for the UA information model http://opcfoundation.org/UA/DI/

#endif // #ifndef __OPCUADISOFTWARETYPEBASE_H__


