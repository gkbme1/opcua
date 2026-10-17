/******************************************************************************
** opcua_frametype.h
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

#ifndef __OPCUA_FRAMETYPE_H__
#define __OPCUA_FRAMETYPE_H__

#include "opcua_basedatavariabletype.h"
#include "opcua_identifiers.h"

// Namespace for the UA information model http://opcfoundation.org/UA/
namespace OpcUa {

class BaseDataVariableType;
class CartesianCoordinatesType;
class OrientationType;
class PropertyType;

/** Implements OPC UA Variables of the type FrameType
 *
 *  **Variable members of the FrameType:**
 *
 *  Browse Name          | DataType             | TypeDefinition           | Modelling Rule | See Also
 *  ---------------------|----------------------|--------------------------|----------------|-----------------------------------------------------------
 *  BaseFrame            | NodeId               | BaseDataVariableType     | Optional       | \ref getBaseFrame, \ref setBaseFrame
 *  CartesianCoordinates | CartesianCoordinates | CartesianCoordinatesType | Mandatory      | \ref getCartesianCoordinates, \ref setCartesianCoordinates
 *  Constant             | Boolean              | PropertyType             | Optional       | \ref getConstant, \ref setConstant
 *  FixedBase            | Boolean              | PropertyType             | Optional       | \ref getFixedBase, \ref setFixedBase
 *  Orientation          | Orientation          | OrientationType          | Mandatory      | \ref getOrientation, \ref setOrientation
 *
 */
class SERVER_CORE_EXPORT FrameType:
    public OpcUa::BaseDataVariableType
{
    UA_DISABLE_COPY(FrameType);
protected:
    virtual ~FrameType();
public:
    FrameType(
        UaNode*            pParentNode,
        UaVariable*        pInstanceDeclarationVariable,
        NodeManagerConfig* pNodeConfig,
        UaMutexRefCounted* pSharedMutex = NULL);
    FrameType(
        const UaNodeId&    nodeId,
        const UaString&    name,
        OpcUa_UInt16       browseNameNameSpaceIndex,
        const UaVariant&   initialValue,
        OpcUa_Byte         accessLevel,
        NodeManagerConfig* pNodeConfig,
        UaMutexRefCounted* pSharedMutex = NULL);
    FrameType(
        UaBase::Variable*  pBaseNode,
        XmlUaNodeFactoryManager*   pFactory,
        NodeManagerConfig* pNodeConfig,
        UaMutexRefCounted* pSharedMutex = NULL);

    static void createTypes();
    static void clearStaticMembers();

    virtual UaNodeId       typeDefinitionId() const;

    virtual void setBaseFrame(const UaNodeId& BaseFrame);
    virtual UaNodeId getBaseFrame() const;

    virtual void setCartesianCoordinates(const UaExtensionObject& CartesianCoordinates);
    virtual UaExtensionObject getCartesianCoordinates() const;

    virtual void setConstant(OpcUa_Boolean Constant);
    virtual OpcUa_Boolean getConstant() const;

    virtual void setFixedBase(OpcUa_Boolean FixedBase);
    virtual OpcUa_Boolean getFixedBase() const;

    virtual void setOrientation(const UaExtensionObject& Orientation);
    virtual UaExtensionObject getOrientation() const;

    virtual OpcUa::BaseDataVariableType* getBaseFrameNode();
    virtual const OpcUa::BaseDataVariableType* getBaseFrameNode() const;
    virtual OpcUa::PropertyType* getConstantNode();
    virtual const OpcUa::PropertyType* getConstantNode() const;
    virtual OpcUa::PropertyType* getFixedBaseNode();
    virtual const OpcUa::PropertyType* getFixedBaseNode() const;

    // NodeAccessInfo management
    virtual void useAccessInfoFromType();
    void useAccessInfoFromInstance(FrameType *pInstance);

protected:
    // Variable nodes
    // Variable BaseFrame
    static OpcUa::BaseDataVariableType*  s_pBaseFrame;
    OpcUa::BaseDataVariableType*  m_pBaseFrame;
    // Variable CartesianCoordinates
    static OpcUa::CartesianCoordinatesType*  s_pCartesianCoordinates;
    OpcUa::CartesianCoordinatesType*  m_pCartesianCoordinates;
    // Variable Constant
    static OpcUa::PropertyType*  s_pConstant;
    OpcUa::PropertyType*  m_pConstant;
    // Variable FixedBase
    static OpcUa::PropertyType*  s_pFixedBase;
    OpcUa::PropertyType*  m_pFixedBase;
    // Variable Orientation
    static OpcUa::OrientationType*  s_pOrientation;
    OpcUa::OrientationType*  m_pOrientation;


private:
    void initialize(NodeManagerConfig* pNodeConfig);

private:
    static bool s_typeNodesCreated;
};

} // End namespace for the UA information model http://opcfoundation.org/UA/

#endif // #ifndef __OPCUA_FRAMETYPE_H__

