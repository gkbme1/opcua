/******************************************************************************
** opcua_threedframetype.h
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

#ifndef __OPCUA_THREEDFRAMETYPE_H__
#define __OPCUA_THREEDFRAMETYPE_H__

#include "opcua_frametype.h"
#include "opcua_identifiers.h"
#include "uathreedcartesiancoordinates.h"
#include "uathreedorientation.h"

// Namespace for the UA information model http://opcfoundation.org/UA/
namespace OpcUa {

class ThreeDCartesianCoordinatesType;
class ThreeDOrientationType;

/** Implements OPC UA Variables of the type ThreeDFrameType
 *
 */
class SERVER_CORE_EXPORT ThreeDFrameType:
    public OpcUa::FrameType
{
    UA_DISABLE_COPY(ThreeDFrameType);
protected:
    virtual ~ThreeDFrameType();
public:
    ThreeDFrameType(
        UaNode*            pParentNode,
        UaVariable*        pInstanceDeclarationVariable,
        NodeManagerConfig* pNodeConfig,
        UaMutexRefCounted* pSharedMutex = NULL);
    ThreeDFrameType(
        const UaNodeId&    nodeId,
        const UaString&    name,
        OpcUa_UInt16       browseNameNameSpaceIndex,
        const UaVariant&   initialValue,
        OpcUa_Byte         accessLevel,
        NodeManagerConfig* pNodeConfig,
        UaMutexRefCounted* pSharedMutex = NULL);
    ThreeDFrameType(
        UaBase::Variable*  pBaseNode,
        XmlUaNodeFactoryManager*   pFactory,
        NodeManagerConfig* pNodeConfig,
        UaMutexRefCounted* pSharedMutex = NULL);

    static void createTypes();
    static void clearStaticMembers();

    virtual UaNodeId       typeDefinitionId() const;

    virtual void setCartesianCoordinates3DCartesianCoordinates(const UaThreeDCartesianCoordinates& CartesianCoordinates);
    virtual UaThreeDCartesianCoordinates getCartesianCoordinates3DCartesianCoordinates() const;
    // CartesianCoordinates defined by base type

    virtual void setOrientation3DOrientation(const UaThreeDOrientation& Orientation);
    virtual UaThreeDOrientation getOrientation3DOrientation() const;
    // Orientation defined by base type

    virtual OpcUa::ThreeDCartesianCoordinatesType* getCartesianCoordinatesNode();
    virtual const OpcUa::ThreeDCartesianCoordinatesType* getCartesianCoordinatesNode() const;
    virtual OpcUa::ThreeDOrientationType* getOrientationNode();
    virtual const OpcUa::ThreeDOrientationType* getOrientationNode() const;

    // NodeAccessInfo management
    virtual void useAccessInfoFromType();
    void useAccessInfoFromInstance(ThreeDFrameType *pInstance);

protected:
    // Variable nodes
    // Variable CartesianCoordinates
    static OpcUa::ThreeDCartesianCoordinatesType*  s_pCartesianCoordinates;
    // CartesianCoordinates defined by base type
    // Variable Orientation
    static OpcUa::ThreeDOrientationType*  s_pOrientation;
    // Orientation defined by base type


private:
    void initialize(NodeManagerConfig* pNodeConfig);

private:
    static bool s_typeNodesCreated;
};

} // End namespace for the UA information model http://opcfoundation.org/UA/

#endif // #ifndef __OPCUA_THREEDFRAMETYPE_H__

