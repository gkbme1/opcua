/******************************************************************************
** opcuadi_ivendornameplatetypebase.h
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

#ifndef __OPCUADI_IVENDORNAMEPLATETYPEBASE_H__
#define __OPCUADI_IVENDORNAMEPLATETYPEBASE_H__

#include "opcua_baseinterfacetype.h"
#include "opcuadi_datatypes.h"
#include "basenodes.h"
#include "opcua_propertytype.h"
#include "opcuadi_identifiers.h"
#include "opcuadi_instancefactory_devices.h"

// Namespace for the UA information model http://opcfoundation.org/UA/DI/
namespace OpcUaDi {


/** Generated base class for a IVendorNameplateType.
 *
 *  This class contains the generated base code for the object type IVendorNameplateType
 *  representing an OPC UA ObjectType. This class is used to create the object type and to
 *  create and represent instances of the object type in the server address space.
 *
 *  **Variable members of the IVendorNameplateType:**
 *
 *  Browse Name        | DataType      | TypeDefinition | Modelling Rule | See Also
 *  -------------------|---------------|----------------|----------------|-------------------------------------------------------
 *  DeviceClass        | String        | PropertyType   | Optional       | \ref getDeviceClass, \ref setDeviceClass
 *  DeviceManual       | String        | PropertyType   | Optional       | \ref getDeviceManual, \ref setDeviceManual
 *  DeviceRevision     | String        | PropertyType   | Optional       | \ref getDeviceRevision, \ref setDeviceRevision
 *  HardwareRevision   | String        | PropertyType   | Optional       | \ref getHardwareRevision, \ref setHardwareRevision
 *  Manufacturer       | LocalizedText | PropertyType   | Optional       | \ref getManufacturer, \ref setManufacturer
 *  ManufacturerUri    | String        | PropertyType   | Optional       | \ref getManufacturerUri, \ref setManufacturerUri
 *  Model              | LocalizedText | PropertyType   | Optional       | \ref getModel, \ref setModel
 *  ProductCode        | String        | PropertyType   | Optional       | \ref getProductCode, \ref setProductCode
 *  ProductInstanceUri | String        | PropertyType   | Optional       | \ref getProductInstanceUri, \ref setProductInstanceUri
 *  RevisionCounter    | Int32         | PropertyType   | Optional       | \ref getRevisionCounter, \ref setRevisionCounter
 *  SerialNumber       | String        | PropertyType   | Optional       | \ref getSerialNumber, \ref setSerialNumber
 *  SoftwareRevision   | String        | PropertyType   | Optional       | \ref getSoftwareRevision, \ref setSoftwareRevision
 *
 */
class UAMODELS_EXPORT IVendorNameplateTypeBase:
    public OpcUa::BaseInterfaceType
{
    UA_DISABLE_COPY(IVendorNameplateTypeBase);
protected:
    virtual ~IVendorNameplateTypeBase();
public:
    // construction / destruction
    IVendorNameplateTypeBase(const UaNodeId& nodeId, UaObject* pInstanceDeclarationObject, NodeManagerConfig* pNodeConfig, UaMutexRefCounted* pSharedMutex = NULL);
    IVendorNameplateTypeBase(const UaNodeId& nodeId, const UaString& name, OpcUa_UInt16 browseNameNameSpaceIndex, NodeManagerConfig* pNodeConfig, UaMutexRefCounted* pSharedMutex = NULL);
    IVendorNameplateTypeBase(
        UaBase::Object*    pBaseNode,
        XmlUaNodeFactoryManager*   pFactory,
        NodeManagerConfig* pNodeConfig,
        UaMutexRefCounted* pSharedMutex = NULL);
    static void createTypes();
    static void clearStaticMembers();

    virtual UaNodeId       typeDefinitionId() const;


    virtual void setDeviceClass(const UaString& DeviceClass);
    virtual UaString getDeviceClass() const;

    virtual void setDeviceManual(const UaString& DeviceManual);
    virtual UaString getDeviceManual() const;

    virtual void setDeviceRevision(const UaString& DeviceRevision);
    virtual UaString getDeviceRevision() const;

    virtual void setHardwareRevision(const UaString& HardwareRevision);
    virtual UaString getHardwareRevision() const;

    virtual void setManufacturer(const UaLocalizedText& Manufacturer);
    virtual UaLocalizedText getManufacturer(Session* pSession) const;

    virtual void setManufacturerUri(const UaString& ManufacturerUri);
    virtual UaString getManufacturerUri() const;

    virtual void setModel(const UaLocalizedText& Model);
    virtual UaLocalizedText getModel(Session* pSession) const;

    virtual void setProductCode(const UaString& ProductCode);
    virtual UaString getProductCode() const;

    virtual void setProductInstanceUri(const UaString& ProductInstanceUri);
    virtual UaString getProductInstanceUri() const;

    virtual void setRevisionCounter(OpcUa_Int32 RevisionCounter);
    virtual OpcUa_Int32 getRevisionCounter() const;

    virtual void setSerialNumber(const UaString& SerialNumber);
    virtual UaString getSerialNumber() const;

    virtual void setSoftwareRevision(const UaString& SoftwareRevision);
    virtual UaString getSoftwareRevision() const;

    virtual OpcUa::PropertyType* getDeviceClassNode();
    virtual const OpcUa::PropertyType* getDeviceClassNode() const;
    virtual OpcUa::PropertyType* getDeviceManualNode();
    virtual const OpcUa::PropertyType* getDeviceManualNode() const;
    virtual OpcUa::PropertyType* getDeviceRevisionNode();
    virtual const OpcUa::PropertyType* getDeviceRevisionNode() const;
    virtual OpcUa::PropertyType* getHardwareRevisionNode();
    virtual const OpcUa::PropertyType* getHardwareRevisionNode() const;
    virtual OpcUa::PropertyType* getManufacturerNode();
    virtual const OpcUa::PropertyType* getManufacturerNode() const;
    virtual OpcUa::PropertyType* getManufacturerUriNode();
    virtual const OpcUa::PropertyType* getManufacturerUriNode() const;
    virtual OpcUa::PropertyType* getModelNode();
    virtual const OpcUa::PropertyType* getModelNode() const;
    virtual OpcUa::PropertyType* getProductCodeNode();
    virtual const OpcUa::PropertyType* getProductCodeNode() const;
    virtual OpcUa::PropertyType* getProductInstanceUriNode();
    virtual const OpcUa::PropertyType* getProductInstanceUriNode() const;
    virtual OpcUa::PropertyType* getRevisionCounterNode();
    virtual const OpcUa::PropertyType* getRevisionCounterNode() const;
    virtual OpcUa::PropertyType* getSerialNumberNode();
    virtual const OpcUa::PropertyType* getSerialNumberNode() const;
    virtual OpcUa::PropertyType* getSoftwareRevisionNode();
    virtual const OpcUa::PropertyType* getSoftwareRevisionNode() const;

protected:
    // Variable nodes
    // Variable DeviceClass
    static OpcUa::PropertyType*  s_pDeviceClass;
    OpcUa::PropertyType*  m_pDeviceClass;
    // Variable DeviceManual
    static OpcUa::PropertyType*  s_pDeviceManual;
    OpcUa::PropertyType*  m_pDeviceManual;
    // Variable DeviceRevision
    static OpcUa::PropertyType*  s_pDeviceRevision;
    OpcUa::PropertyType*  m_pDeviceRevision;
    // Variable HardwareRevision
    static OpcUa::PropertyType*  s_pHardwareRevision;
    OpcUa::PropertyType*  m_pHardwareRevision;
    // Variable Manufacturer
    static OpcUa::PropertyType*  s_pManufacturer;
    OpcUa::PropertyType*  m_pManufacturer;
    // Variable ManufacturerUri
    static OpcUa::PropertyType*  s_pManufacturerUri;
    OpcUa::PropertyType*  m_pManufacturerUri;
    // Variable Model
    static OpcUa::PropertyType*  s_pModel;
    OpcUa::PropertyType*  m_pModel;
    // Variable ProductCode
    static OpcUa::PropertyType*  s_pProductCode;
    OpcUa::PropertyType*  m_pProductCode;
    // Variable ProductInstanceUri
    static OpcUa::PropertyType*  s_pProductInstanceUri;
    OpcUa::PropertyType*  m_pProductInstanceUri;
    // Variable RevisionCounter
    static OpcUa::PropertyType*  s_pRevisionCounter;
    OpcUa::PropertyType*  m_pRevisionCounter;
    // Variable SerialNumber
    static OpcUa::PropertyType*  s_pSerialNumber;
    OpcUa::PropertyType*  m_pSerialNumber;
    // Variable SoftwareRevision
    static OpcUa::PropertyType*  s_pSoftwareRevision;
    OpcUa::PropertyType*  m_pSoftwareRevision;



private:
    void initialize();

private:
    static bool s_typeNodesCreated;
};

} // End namespace for the UA information model http://opcfoundation.org/UA/DI/

#endif // #ifndef __OPCUADIIVENDORNAMEPLATETYPEBASE_H__


