/******************************************************************************
** opcua_threedorientationtype.h
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

#ifndef __OPCUA_THREEDORIENTATIONTYPE_H__
#define __OPCUA_THREEDORIENTATIONTYPE_H__

#include "opcua_orientationtype.h"
#include "opcua_identifiers.h"

// Namespace for the UA information model http://opcfoundation.org/UA/
namespace OpcUa {

class BaseDataVariableType;

/** Implements OPC UA Variables of the type ThreeDOrientationType
 *
 *  **Variable members of the 3DOrientationType:**
 *
 *  Browse Name | DataType | TypeDefinition       | Modelling Rule | See Also
 *  ------------|----------|----------------------|----------------|---------------------
 *  A           | Double   | BaseDataVariableType | Mandatory      | \ref getA, \ref setA
 *  B           | Double   | BaseDataVariableType | Mandatory      | \ref getB, \ref setB
 *  C           | Double   | BaseDataVariableType | Mandatory      | \ref getC, \ref setC
 *
 */
class SERVER_CORE_EXPORT ThreeDOrientationType:
    public OpcUa::OrientationType
{
    UA_DISABLE_COPY(ThreeDOrientationType);
protected:
    virtual ~ThreeDOrientationType();
public:
    ThreeDOrientationType(
        UaNode*            pParentNode,
        UaVariable*        pInstanceDeclarationVariable,
        NodeManagerConfig* pNodeConfig,
        UaMutexRefCounted* pSharedMutex = NULL);
    ThreeDOrientationType(
        const UaNodeId&    nodeId,
        const UaString&    name,
        OpcUa_UInt16       browseNameNameSpaceIndex,
        const UaVariant&   initialValue,
        OpcUa_Byte         accessLevel,
        NodeManagerConfig* pNodeConfig,
        UaMutexRefCounted* pSharedMutex = NULL);
    ThreeDOrientationType(
        UaBase::Variable*  pBaseNode,
        XmlUaNodeFactoryManager*   pFactory,
        NodeManagerConfig* pNodeConfig,
        UaMutexRefCounted* pSharedMutex = NULL);

    static void createTypes();
    static void clearStaticMembers();

    virtual UaNodeId       typeDefinitionId() const;

    virtual void setA(OpcUa_Double A);
    virtual OpcUa_Double getA() const;

    virtual void setB(OpcUa_Double B);
    virtual OpcUa_Double getB() const;

    virtual void setC(OpcUa_Double C);
    virtual OpcUa_Double getC() const;

    virtual OpcUa::BaseDataVariableType* getANode();
    virtual const OpcUa::BaseDataVariableType* getANode() const;
    virtual OpcUa::BaseDataVariableType* getBNode();
    virtual const OpcUa::BaseDataVariableType* getBNode() const;
    virtual OpcUa::BaseDataVariableType* getCNode();
    virtual const OpcUa::BaseDataVariableType* getCNode() const;

    // NodeAccessInfo management
    virtual void useAccessInfoFromType();
    void useAccessInfoFromInstance(ThreeDOrientationType *pInstance);

protected:
    // Variable nodes
    // Variable A
    static OpcUa::BaseDataVariableType*  s_pA;
    OpcUa::BaseDataVariableType*  m_pA;
    // Variable B
    static OpcUa::BaseDataVariableType*  s_pB;
    OpcUa::BaseDataVariableType*  m_pB;
    // Variable C
    static OpcUa::BaseDataVariableType*  s_pC;
    OpcUa::BaseDataVariableType*  m_pC;


private:
    void initialize(NodeManagerConfig* pNodeConfig);

private:
    static bool s_typeNodesCreated;
};

} // End namespace for the UA information model http://opcfoundation.org/UA/

#endif // #ifndef __OPCUA_THREEDORIENTATIONTYPE_H__

