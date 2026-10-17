/******************************************************************************
** opcuadi_devicetypebase.h
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

#ifndef __OPCUADI_DEVICETYPEBASE_H__
#define __OPCUADI_DEVICETYPEBASE_H__

#include "opcuadi_componenttype.h"
#include "opcuadi_datatypes.h"
#include "basenodes.h"
#include "opcua_basedatavariabletype.h"
#include "opcua_foldertype.h"
#include "opcua_propertytype.h"
#include "opcuadi_identifiers.h"
#include "opcuadi_instancefactory_devices.h"

// Namespace for the UA information model http://opcfoundation.org/UA/DI/
namespace OpcUaDi {

class ConnectionPointType;
class FunctionalGroupType;

/** Generated base class for a DeviceType.
 *
 *  This class contains the generated base code for the object type DeviceType
 *  representing an OPC UA ObjectType. This class is used to create the object type and to
 *  create and represent instances of the object type in the server address space.
 *
 *  **Object members of the DeviceType:**
 *
 *  Browse Name        | TypeDefinition      | Modelling Rule      | See Also
 *  -------------------|---------------------|---------------------|---------------------------
 *  \<CPIdentifier\>   | ConnectionPointType | OptionalPlaceholder | &nbsp;
 *  DeviceHealthAlarms | FolderType          | Optional            | \ref getDeviceHealthAlarms
 *  DeviceTypeImage    | FolderType          | Optional            | \ref getDeviceTypeImage
 *  Documentation      | FolderType          | Optional            | \ref getDocumentation
 *  ImageSet           | FolderType          | Optional            | \ref getImageSet
 *  ProtocolSupport    | FolderType          | Optional            | \ref getProtocolSupport
 *
 *  **Variable members of the DeviceType:**
 *
 *  Browse Name  | DataType                | TypeDefinition       | Modelling Rule | See Also
 *  -------------|-------------------------|----------------------|----------------|-------------------------------------------
 *  DeviceHealth | DeviceHealthEnumeration | BaseDataVariableType | Optional       | \ref getDeviceHealth, \ref setDeviceHealth
 *
 */
class UAMODELS_EXPORT DeviceTypeBase:
    public OpcUaDi::ComponentType
{
    UA_DISABLE_COPY(DeviceTypeBase);
protected:
    virtual ~DeviceTypeBase();
public:
    // construction / destruction
    DeviceTypeBase(const UaNodeId& nodeId, UaObject* pInstanceDeclarationObject, NodeManagerConfig* pNodeConfig, UaMutexRefCounted* pSharedMutex = NULL);
    DeviceTypeBase(const UaNodeId& nodeId, const UaString& name, OpcUa_UInt16 browseNameNameSpaceIndex, NodeManagerConfig* pNodeConfig, UaMutexRefCounted* pSharedMutex = NULL);
    DeviceTypeBase(
        UaBase::Object*    pBaseNode,
        XmlUaNodeFactoryManager*   pFactory,
        NodeManagerConfig* pNodeConfig,
        UaMutexRefCounted* pSharedMutex = NULL);
    static void createTypes();
    static void clearStaticMembers();

    virtual UaNodeId       typeDefinitionId() const;


    // DeviceClass defined by base type

    virtual void setDeviceHealth(OpcUaDi::DeviceHealthEnumeration DeviceHealth);
    virtual OpcUaDi::DeviceHealthEnumeration getDeviceHealth() const;

    // DeviceManual defined by base type

    // DeviceRevision defined by base type

    // HardwareRevision defined by base type

    // Manufacturer defined by base type

    // ManufacturerUri defined by base type

    // Model defined by base type

    // ProductCode defined by base type

    // ProductInstanceUri defined by base type

    // RevisionCounter defined by base type

    // SerialNumber defined by base type

    // SoftwareRevision defined by base type

    // <ImageIdentifier> defined at DeviceTypeImage

    // <DocumentIdentifier> defined at Documentation

    // <ImageIdentifier> defined at ImageSet

    // <ProtocolSupportIdentifier> defined at ProtocolSupport

    virtual OpcUa::BaseDataVariableType* getDeviceHealthNode();
    virtual const OpcUa::BaseDataVariableType* getDeviceHealthNode() const;
    virtual OpcUa::FolderType* getDeviceHealthAlarms();
    virtual const OpcUa::FolderType* getDeviceHealthAlarms() const;
    virtual OpcUa::FolderType* getDeviceTypeImage();
    virtual const OpcUa::FolderType* getDeviceTypeImage() const;
    virtual OpcUa::FolderType* getDocumentation();
    virtual const OpcUa::FolderType* getDocumentation() const;
    virtual OpcUa::FolderType* getImageSet();
    virtual const OpcUa::FolderType* getImageSet() const;
    virtual OpcUa::FolderType* getProtocolSupport();
    virtual const OpcUa::FolderType* getProtocolSupport() const;

// Add placeholders
    virtual UaStatus addCP(OpcUaDi::ConnectionPointType *pCP);
    virtual UaStatus addDeviceTypeImage_Image(OpcUa::BaseDataVariableType *pImage);
    virtual UaStatus addDocumentation_Document(OpcUa::BaseDataVariableType *pDocument);
    virtual UaStatus addImageSet_Image(OpcUa::BaseDataVariableType *pImage);
    virtual UaStatus addProtocolSupport_ProtocolSupport(OpcUa::BaseDataVariableType *pProtocolSupport);

    // NodeAccessInfo management
    virtual void useAccessInfoFromType();
    void useAccessInfoFromInstance(DeviceTypeBase *pInstance);

protected:
    // Object nodes
    // Object CPIdentifier
    static OpcUaDi::ConnectionPointType*  s_pCPIdentifier;
    // Object DeviceHealthAlarms
    static OpcUa::FolderType*  s_pDeviceHealthAlarms;
    OpcUa::FolderType*  m_pDeviceHealthAlarms;
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

    // Variable nodes
    // Variable DeviceClass
    static OpcUa::PropertyType*  s_pDeviceClass;
    // DeviceClass defined by base type
    // Variable DeviceHealth
    static OpcUa::BaseDataVariableType*  s_pDeviceHealth;
    OpcUa::BaseDataVariableType*  m_pDeviceHealth;
    // Variable DeviceManual
    static OpcUa::PropertyType*  s_pDeviceManual;
    // DeviceManual defined by base type
    // Variable DeviceRevision
    static OpcUa::PropertyType*  s_pDeviceRevision;
    // DeviceRevision defined by base type
    // Variable HardwareRevision
    static OpcUa::PropertyType*  s_pHardwareRevision;
    // HardwareRevision defined by base type
    // Variable Manufacturer
    static OpcUa::PropertyType*  s_pManufacturer;
    // Manufacturer defined by base type
    // Variable ManufacturerUri
    static OpcUa::PropertyType*  s_pManufacturerUri;
    // ManufacturerUri defined by base type
    // Variable Model
    static OpcUa::PropertyType*  s_pModel;
    // Model defined by base type
    // Variable ProductCode
    static OpcUa::PropertyType*  s_pProductCode;
    // ProductCode defined by base type
    // Variable ProductInstanceUri
    static OpcUa::PropertyType*  s_pProductInstanceUri;
    // ProductInstanceUri defined by base type
    // Variable RevisionCounter
    static OpcUa::PropertyType*  s_pRevisionCounter;
    // RevisionCounter defined by base type
    // Variable SerialNumber
    static OpcUa::PropertyType*  s_pSerialNumber;
    // SerialNumber defined by base type
    // Variable SoftwareRevision
    static OpcUa::PropertyType*  s_pSoftwareRevision;
    // SoftwareRevision defined by base type

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

#endif // #ifndef __OPCUADIDEVICETYPEBASE_H__


