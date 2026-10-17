/******************************************************************************
** opcua_dictionaryentrytype.h
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

#ifndef __OPCUA_DICTIONARYENTRYTYPE_H__
#define __OPCUA_DICTIONARYENTRYTYPE_H__

#include "opcua_baseobjecttype.h"
#include "basenodes.h"
#include "opcua_dictionaryentrytype.h"
#include "opcua_identifiers.h"

// Namespace for the UA information model http://opcfoundation.org/UA/
namespace OpcUa {

class DictionaryEntryType;

/** Generated base class for a DictionaryEntryType.
 *
 *  This class contains the generated base code for the object type DictionaryEntryType
 *  representing an OPC UA ObjectType. This class is used to create the object type and to
 *  create and represent instances of the object type in the server address space.
 *
 *  **Object members of the DictionaryEntryType:**
 *
 *  Browse Name             | TypeDefinition      | Modelling Rule      | See Also
 *  ------------------------|---------------------|---------------------|---------
 *  \<DictionaryEntryName\> | DictionaryEntryType | OptionalPlaceholder | &nbsp;
 *
 */
class SERVER_CORE_EXPORT DictionaryEntryType:
    public OpcUa::BaseObjectType
{
    UA_DISABLE_COPY(DictionaryEntryType);
protected:
    virtual ~DictionaryEntryType();
public:
    // construction / destruction
    DictionaryEntryType(const UaNodeId& nodeId, UaObject* pInstanceDeclarationObject, NodeManagerConfig* pNodeConfig, UaMutexRefCounted* pSharedMutex = NULL);
    DictionaryEntryType(const UaNodeId& nodeId, const UaString& name, OpcUa_UInt16 browseNameNameSpaceIndex, NodeManagerConfig* pNodeConfig, UaMutexRefCounted* pSharedMutex = NULL);
    DictionaryEntryType(
        UaBase::Object*    pBaseNode,
        XmlUaNodeFactoryManager*   pFactory,
        NodeManagerConfig* pNodeConfig,
        UaMutexRefCounted* pSharedMutex = NULL);
    static void createTypes();
    static void clearStaticMembers();

    virtual UaNodeId       typeDefinitionId() const;



// Add placeholders
    virtual UaStatus addDictionaryEntryName_Placeholder(OpcUa::DictionaryEntryType *pDictionaryEntryName_Placeholder);

    // NodeAccessInfo management
    virtual void useAccessInfoFromType();
    void useAccessInfoFromInstance(DictionaryEntryType *pInstance);

protected:
    // Object nodes
    // Object DictionaryEntryName_Placeholder
    static OpcUa::DictionaryEntryType*  s_pDictionaryEntryName_Placeholder;



private:
    void initialize();

private:
    static bool s_typeNodesCreated;
};

} // End namespace for the UA information model http://opcfoundation.org/UA/

#endif // #ifndef __OPCUADICTIONARYENTRYTYPE_H__


