/******************************************************************************
** opcua_cartesiancoordinatestype.h
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
** Project: C++ OPC Server SDK information model for namespace http://opcfoundation.org/UA/
**
** Description: OPC Unified Architecture Software Development Kit.
**
******************************************************************************/

#ifndef __OPCUA_CARTESIANCOORDINATESTYPE_H__
#define __OPCUA_CARTESIANCOORDINATESTYPE_H__

#include "opcua_basedatavariabletype.h"
#include "opcua_identifiers.h"
#include "uaeuinformation.h"

// Namespace for the UA information model http://opcfoundation.org/UA/
namespace OpcUa {

class PropertyType;

/** Implements OPC UA Variables of the type CartesianCoordinatesType
 *
 *  **Variable members of the CartesianCoordinatesType:**
 *
 *  Browse Name | DataType      | TypeDefinition | Modelling Rule | See Also
 *  ------------|---------------|----------------|----------------|---------------------------------------
 *  LengthUnit  | EUInformation | PropertyType   | Optional       | \ref getLengthUnit, \ref setLengthUnit
 *
 */
class SERVER_CORE_EXPORT CartesianCoordinatesType:
    public OpcUa::BaseDataVariableType
{
    UA_DISABLE_COPY(CartesianCoordinatesType);
protected:
    virtual ~CartesianCoordinatesType();
public:
    CartesianCoordinatesType(
        UaNode*            pParentNode,
        UaVariable*        pInstanceDeclarationVariable,
        NodeManagerConfig* pNodeConfig,
        UaMutexRefCounted* pSharedMutex = NULL);
    CartesianCoordinatesType(
        const UaNodeId&    nodeId,
        const UaString&    name,
        OpcUa_UInt16       browseNameNameSpaceIndex,
        const UaVariant&   initialValue,
        OpcUa_Byte         accessLevel,
        NodeManagerConfig* pNodeConfig,
        UaMutexRefCounted* pSharedMutex = NULL);
    CartesianCoordinatesType(
        UaBase::Variable*  pBaseNode,
        XmlUaNodeFactoryManager*   pFactory,
        NodeManagerConfig* pNodeConfig,
        UaMutexRefCounted* pSharedMutex = NULL);

    static void createTypes();
    static void clearStaticMembers();

    virtual UaNodeId       typeDefinitionId() const;

    virtual void setLengthUnit(const UaEUInformation& LengthUnit);
    virtual UaEUInformation getLengthUnit() const;

    virtual OpcUa::PropertyType* getLengthUnitNode();
    virtual const OpcUa::PropertyType* getLengthUnitNode() const;

    // NodeAccessInfo management
    virtual void useAccessInfoFromType();
    void useAccessInfoFromInstance(CartesianCoordinatesType *pInstance);

protected:
    // Variable nodes
    // Variable LengthUnit
    static OpcUa::PropertyType*  s_pLengthUnit;
    OpcUa::PropertyType*  m_pLengthUnit;


private:
    void initialize(NodeManagerConfig* pNodeConfig);

private:
    static bool s_typeNodesCreated;
};

} // End namespace for the UA information model http://opcfoundation.org/UA/

#endif // #ifndef __OPCUA_CARTESIANCOORDINATESTYPE_H__

