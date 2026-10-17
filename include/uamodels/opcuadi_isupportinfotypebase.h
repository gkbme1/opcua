/******************************************************************************
** opcuadi_isupportinfotypebase.h
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

#ifndef __OPCUADI_ISUPPORTINFOTYPEBASE_H__
#define __OPCUADI_ISUPPORTINFOTYPEBASE_H__

#include "opcua_baseinterfacetype.h"
#include "opcuadi_datatypes.h"
#include "basenodes.h"
#include "opcua_basedatavariabletype.h"
#include "opcua_foldertype.h"
#include "opcuadi_identifiers.h"
#include "opcuadi_instancefactory_devices.h"

// Namespace for the UA information model http://opcfoundation.org/UA/DI/
namespace OpcUaDi {


/** Generated base class for a ISupportInfoType.
 *
 *  This class contains the generated base code for the object type ISupportInfoType
 *  representing an OPC UA ObjectType. This class is used to create the object type and to
 *  create and represent instances of the object type in the server address space.
 *
 *  **Object members of the ISupportInfoType:**
 *
 *  Browse Name     | TypeDefinition | Modelling Rule | See Also
 *  ----------------|----------------|----------------|------------------------
 *  DeviceTypeImage | FolderType     | Optional       | \ref getDeviceTypeImage
 *  Documentation   | FolderType     | Optional       | \ref getDocumentation
 *  ImageSet        | FolderType     | Optional       | \ref getImageSet
 *  ProtocolSupport | FolderType     | Optional       | \ref getProtocolSupport
 *
 */
class UAMODELS_EXPORT ISupportInfoTypeBase:
    public OpcUa::BaseInterfaceType
{
    UA_DISABLE_COPY(ISupportInfoTypeBase);
protected:
    virtual ~ISupportInfoTypeBase();
public:
    // construction / destruction
    ISupportInfoTypeBase(const UaNodeId& nodeId, UaObject* pInstanceDeclarationObject, NodeManagerConfig* pNodeConfig, UaMutexRefCounted* pSharedMutex = NULL);
    ISupportInfoTypeBase(const UaNodeId& nodeId, const UaString& name, OpcUa_UInt16 browseNameNameSpaceIndex, NodeManagerConfig* pNodeConfig, UaMutexRefCounted* pSharedMutex = NULL);
    ISupportInfoTypeBase(
        UaBase::Object*    pBaseNode,
        XmlUaNodeFactoryManager*   pFactory,
        NodeManagerConfig* pNodeConfig,
        UaMutexRefCounted* pSharedMutex = NULL);
    static void createTypes();
    static void clearStaticMembers();

    virtual UaNodeId       typeDefinitionId() const;


    // <ImageIdentifier> defined at DeviceTypeImage

    // <DocumentIdentifier> defined at Documentation

    // <ImageIdentifier> defined at ImageSet

    // <ProtocolSupportIdentifier> defined at ProtocolSupport

    virtual OpcUa::FolderType* getDeviceTypeImage();
    virtual const OpcUa::FolderType* getDeviceTypeImage() const;
    virtual OpcUa::FolderType* getDocumentation();
    virtual const OpcUa::FolderType* getDocumentation() const;
    virtual OpcUa::FolderType* getImageSet();
    virtual const OpcUa::FolderType* getImageSet() const;
    virtual OpcUa::FolderType* getProtocolSupport();
    virtual const OpcUa::FolderType* getProtocolSupport() const;

// Add placeholders
    virtual UaStatus addDeviceTypeImage_Image(OpcUa::BaseDataVariableType *pImage);
    virtual UaStatus addDocumentation_Document(OpcUa::BaseDataVariableType *pDocument);
    virtual UaStatus addImageSet_Image(OpcUa::BaseDataVariableType *pImage);
    virtual UaStatus addProtocolSupport_ProtocolSupport(OpcUa::BaseDataVariableType *pProtocolSupport);

protected:
    // Object nodes
    // Object DeviceTypeImage
    static OpcUa::FolderType*  s_pDeviceTypeImage;
    OpcUa::FolderType*  m_pDeviceTypeImage;
    // Object Documentation
    static OpcUa::FolderType*  s_pDocumentation;
    OpcUa::FolderType*  m_pDocumentation;
    // Object ImageSet
    static OpcUa::FolderType*  s_pImageSet;
    OpcUa::FolderType*  m_pImageSet;
    // Object ProtocolSupport
    static OpcUa::FolderType*  s_pProtocolSupport;
    OpcUa::FolderType*  m_pProtocolSupport;

    // Variable DeviceTypeImage ImageIdentifier
    static OpcUa::BaseDataVariableType* s_pDeviceTypeImage_ImageIdentifier;
    // Variable Documentation DocumentIdentifier
    static OpcUa::BaseDataVariableType* s_pDocumentation_DocumentIdentifier;
    // Variable ImageSet ImageIdentifier
    static OpcUa::BaseDataVariableType* s_pImageSet_ImageIdentifier;
    // Variable ProtocolSupport ProtocolSupportIdentifier
    static OpcUa::BaseDataVariableType* s_pProtocolSupport_ProtocolSupportIdentifier;


private:
    void initialize();

private:
    static bool s_typeNodesCreated;
};

} // End namespace for the UA information model http://opcfoundation.org/UA/DI/

#endif // #ifndef __OPCUADIISUPPORTINFOTYPEBASE_H__


