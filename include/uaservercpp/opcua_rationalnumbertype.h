/******************************************************************************
** opcua_rationalnumbertype.h
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

#ifndef __OPCUA_RATIONALNUMBERTYPE_H__
#define __OPCUA_RATIONALNUMBERTYPE_H__

#include "opcua_basedatavariabletype.h"
#include "opcua_identifiers.h"

// Namespace for the UA information model http://opcfoundation.org/UA/
namespace OpcUa {

class BaseDataVariableType;

/** Implements OPC UA Variables of the type RationalNumberType
 *
 *  **Variable members of the RationalNumberType:**
 *
 *  Browse Name | DataType | TypeDefinition       | Modelling Rule | See Also
 *  ------------|----------|----------------------|----------------|-----------------------------------------
 *  Denominator | UInt32   | BaseDataVariableType | Mandatory      | \ref getDenominator, \ref setDenominator
 *  Numerator   | Int32    | BaseDataVariableType | Mandatory      | \ref getNumerator, \ref setNumerator
 *
 */
class SERVER_CORE_EXPORT RationalNumberType:
    public OpcUa::BaseDataVariableType
{
    UA_DISABLE_COPY(RationalNumberType);
protected:
    virtual ~RationalNumberType();
public:
    RationalNumberType(
        UaNode*            pParentNode,
        UaVariable*        pInstanceDeclarationVariable,
        NodeManagerConfig* pNodeConfig,
        UaMutexRefCounted* pSharedMutex = NULL);
    RationalNumberType(
        const UaNodeId&    nodeId,
        const UaString&    name,
        OpcUa_UInt16       browseNameNameSpaceIndex,
        const UaVariant&   initialValue,
        OpcUa_Byte         accessLevel,
        NodeManagerConfig* pNodeConfig,
        UaMutexRefCounted* pSharedMutex = NULL);
    RationalNumberType(
        UaBase::Variable*  pBaseNode,
        XmlUaNodeFactoryManager*   pFactory,
        NodeManagerConfig* pNodeConfig,
        UaMutexRefCounted* pSharedMutex = NULL);

    static void createTypes();
    static void clearStaticMembers();

    virtual UaNodeId       typeDefinitionId() const;

    virtual void setDenominator(OpcUa_UInt32 Denominator);
    virtual OpcUa_UInt32 getDenominator() const;

    virtual void setNumerator(OpcUa_Int32 Numerator);
    virtual OpcUa_Int32 getNumerator() const;

    virtual OpcUa::BaseDataVariableType* getDenominatorNode();
    virtual const OpcUa::BaseDataVariableType* getDenominatorNode() const;
    virtual OpcUa::BaseDataVariableType* getNumeratorNode();
    virtual const OpcUa::BaseDataVariableType* getNumeratorNode() const;

    // NodeAccessInfo management
    virtual void useAccessInfoFromType();
    void useAccessInfoFromInstance(RationalNumberType *pInstance);

protected:
    // Variable nodes
    // Variable Denominator
    static OpcUa::BaseDataVariableType*  s_pDenominator;
    OpcUa::BaseDataVariableType*  m_pDenominator;
    // Variable Numerator
    static OpcUa::BaseDataVariableType*  s_pNumerator;
    OpcUa::BaseDataVariableType*  m_pNumerator;


private:
    void initialize(NodeManagerConfig* pNodeConfig);

private:
    static bool s_typeNodesCreated;
};

} // End namespace for the UA information model http://opcfoundation.org/UA/

#endif // #ifndef __OPCUA_RATIONALNUMBERTYPE_H__

