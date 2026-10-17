/******************************************************************************
** opcua_expressionguardvariabletype.h
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

#ifndef __OPCUA_EXPRESSIONGUARDVARIABLETYPE_H__
#define __OPCUA_EXPRESSIONGUARDVARIABLETYPE_H__

#include "opcua_guardvariabletype.h"
#include "opcua_identifiers.h"
#include "uacontentfilter.h"

// Namespace for the UA information model http://opcfoundation.org/UA/
namespace OpcUa {

class PropertyType;

/** Implements OPC UA Variables of the type ExpressionGuardVariableType
 *
 *  **Variable members of the ExpressionGuardVariableType:**
 *
 *  Browse Name | DataType      | TypeDefinition | Modelling Rule | See Also
 *  ------------|---------------|----------------|----------------|---------------------------------------
 *  Expression  | ContentFilter | PropertyType   | Mandatory      | \ref getExpression, \ref setExpression
 *
 */
class SERVER_CORE_EXPORT ExpressionGuardVariableType:
    public OpcUa::GuardVariableType
{
    UA_DISABLE_COPY(ExpressionGuardVariableType);
protected:
    virtual ~ExpressionGuardVariableType();
public:
    ExpressionGuardVariableType(
        UaNode*            pParentNode,
        UaVariable*        pInstanceDeclarationVariable,
        NodeManagerConfig* pNodeConfig,
        UaMutexRefCounted* pSharedMutex = NULL);
    ExpressionGuardVariableType(
        const UaNodeId&    nodeId,
        const UaString&    name,
        OpcUa_UInt16       browseNameNameSpaceIndex,
        const UaVariant&   initialValue,
        OpcUa_Byte         accessLevel,
        NodeManagerConfig* pNodeConfig,
        UaMutexRefCounted* pSharedMutex = NULL);
    ExpressionGuardVariableType(
        UaBase::Variable*  pBaseNode,
        XmlUaNodeFactoryManager*   pFactory,
        NodeManagerConfig* pNodeConfig,
        UaMutexRefCounted* pSharedMutex = NULL);

    static void createTypes();
    static void clearStaticMembers();

    virtual UaNodeId       typeDefinitionId() const;

    virtual void setExpression(const UaContentFilter& Expression);
    virtual UaContentFilter getExpression() const;

    virtual OpcUa::PropertyType* getExpressionNode();
    virtual const OpcUa::PropertyType* getExpressionNode() const;

protected:
    // Variable nodes
    // Variable Expression
    static OpcUa::PropertyType*  s_pExpression;
    OpcUa::PropertyType*  m_pExpression;


private:
    void initialize(NodeManagerConfig* pNodeConfig);

private:
    static bool s_typeNodesCreated;
};

} // End namespace for the UA information model http://opcfoundation.org/UA/

#endif // #ifndef __OPCUA_EXPRESSIONGUARDVARIABLETYPE_H__

