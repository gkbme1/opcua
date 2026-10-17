/******************************************************************************
** opcua_threedvectortype.h
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

#ifndef __OPCUA_THREEDVECTORTYPE_H__
#define __OPCUA_THREEDVECTORTYPE_H__

#include "opcua_vectortype.h"
#include "opcua_identifiers.h"

// Namespace for the UA information model http://opcfoundation.org/UA/
namespace OpcUa {

class BaseDataVariableType;

/** Implements OPC UA Variables of the type ThreeDVectorType
 *
 *  **Variable members of the 3DVectorType:**
 *
 *  Browse Name | DataType | TypeDefinition       | Modelling Rule | See Also
 *  ------------|----------|----------------------|----------------|---------------------
 *  X           | Double   | BaseDataVariableType | Mandatory      | \ref getX, \ref setX
 *  Y           | Double   | BaseDataVariableType | Mandatory      | \ref getY, \ref setY
 *  Z           | Double   | BaseDataVariableType | Mandatory      | \ref getZ, \ref setZ
 *
 */
class SERVER_CORE_EXPORT ThreeDVectorType:
    public OpcUa::VectorType
{
    UA_DISABLE_COPY(ThreeDVectorType);
protected:
    virtual ~ThreeDVectorType();
public:
    ThreeDVectorType(
        UaNode*            pParentNode,
        UaVariable*        pInstanceDeclarationVariable,
        NodeManagerConfig* pNodeConfig,
        UaMutexRefCounted* pSharedMutex = NULL);
    ThreeDVectorType(
        const UaNodeId&    nodeId,
        const UaString&    name,
        OpcUa_UInt16       browseNameNameSpaceIndex,
        const UaVariant&   initialValue,
        OpcUa_Byte         accessLevel,
        NodeManagerConfig* pNodeConfig,
        UaMutexRefCounted* pSharedMutex = NULL);
    ThreeDVectorType(
        UaBase::Variable*  pBaseNode,
        XmlUaNodeFactoryManager*   pFactory,
        NodeManagerConfig* pNodeConfig,
        UaMutexRefCounted* pSharedMutex = NULL);

    static void createTypes();
    static void clearStaticMembers();

    virtual UaNodeId       typeDefinitionId() const;

    virtual void setX(OpcUa_Double X);
    virtual OpcUa_Double getX() const;

    virtual void setY(OpcUa_Double Y);
    virtual OpcUa_Double getY() const;

    virtual void setZ(OpcUa_Double Z);
    virtual OpcUa_Double getZ() const;

    virtual OpcUa::BaseDataVariableType* getXNode();
    virtual const OpcUa::BaseDataVariableType* getXNode() const;
    virtual OpcUa::BaseDataVariableType* getYNode();
    virtual const OpcUa::BaseDataVariableType* getYNode() const;
    virtual OpcUa::BaseDataVariableType* getZNode();
    virtual const OpcUa::BaseDataVariableType* getZNode() const;

    // NodeAccessInfo management
    virtual void useAccessInfoFromType();
    void useAccessInfoFromInstance(ThreeDVectorType *pInstance);

protected:
    // Variable nodes
    // Variable X
    static OpcUa::BaseDataVariableType*  s_pX;
    OpcUa::BaseDataVariableType*  m_pX;
    // Variable Y
    static OpcUa::BaseDataVariableType*  s_pY;
    OpcUa::BaseDataVariableType*  m_pY;
    // Variable Z
    static OpcUa::BaseDataVariableType*  s_pZ;
    OpcUa::BaseDataVariableType*  m_pZ;


private:
    void initialize(NodeManagerConfig* pNodeConfig);

private:
    static bool s_typeNodesCreated;
};

} // End namespace for the UA information model http://opcfoundation.org/UA/

#endif // #ifndef __OPCUA_THREEDVECTORTYPE_H__

