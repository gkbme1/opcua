/******************************************************************************
** opcuadi_ivendornameplatetype.h
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

#ifndef __OPCUADI_IVENDORNAMEPLATETYPE_H__
#define __OPCUADI_IVENDORNAMEPLATETYPE_H__

#include "opcuadi_ivendornameplatetypebase.h"

// Namespace for the UA information model http://opcfoundation.org/UA/DI/
namespace OpcUaDi {

/** @brief Class implementing the UaObject interface for the IVendorNameplateType.
 *
 * OPC UA Objects are used to represent systems, system components, real-world objects and software
 * objects. They have the NodeClass Object. The detailed description of Objects and their attributes
 * can be found in the general description of the Object node class.
 *
 *  **Variable members of the IVendorNameplateType:**
 *
 *  Browse Name        | DataType      | TypeDefinition | Modelling Rule | See Also
 *  -------------------|---------------|----------------|----------------|-----------------------------------------------------------------------------------------------------------------------------------------------------------
 *  DeviceClass        | String        | PropertyType   | Optional       | \ref IVendorNameplateTypeBase::getDeviceClass "getDeviceClass", \ref IVendorNameplateTypeBase::setDeviceClass "setDeviceClass"
 *  DeviceManual       | String        | PropertyType   | Optional       | \ref IVendorNameplateTypeBase::getDeviceManual "getDeviceManual", \ref IVendorNameplateTypeBase::setDeviceManual "setDeviceManual"
 *  DeviceRevision     | String        | PropertyType   | Optional       | \ref IVendorNameplateTypeBase::getDeviceRevision "getDeviceRevision", \ref IVendorNameplateTypeBase::setDeviceRevision "setDeviceRevision"
 *  HardwareRevision   | String        | PropertyType   | Optional       | \ref IVendorNameplateTypeBase::getHardwareRevision "getHardwareRevision", \ref IVendorNameplateTypeBase::setHardwareRevision "setHardwareRevision"
 *  Manufacturer       | LocalizedText | PropertyType   | Optional       | \ref IVendorNameplateTypeBase::getManufacturer "getManufacturer", \ref IVendorNameplateTypeBase::setManufacturer "setManufacturer"
 *  ManufacturerUri    | String        | PropertyType   | Optional       | \ref IVendorNameplateTypeBase::getManufacturerUri "getManufacturerUri", \ref IVendorNameplateTypeBase::setManufacturerUri "setManufacturerUri"
 *  Model              | LocalizedText | PropertyType   | Optional       | \ref IVendorNameplateTypeBase::getModel "getModel", \ref IVendorNameplateTypeBase::setModel "setModel"
 *  ProductCode        | String        | PropertyType   | Optional       | \ref IVendorNameplateTypeBase::getProductCode "getProductCode", \ref IVendorNameplateTypeBase::setProductCode "setProductCode"
 *  ProductInstanceUri | String        | PropertyType   | Optional       | \ref IVendorNameplateTypeBase::getProductInstanceUri "getProductInstanceUri", \ref IVendorNameplateTypeBase::setProductInstanceUri "setProductInstanceUri"
 *  RevisionCounter    | Int32         | PropertyType   | Optional       | \ref IVendorNameplateTypeBase::getRevisionCounter "getRevisionCounter", \ref IVendorNameplateTypeBase::setRevisionCounter "setRevisionCounter"
 *  SerialNumber       | String        | PropertyType   | Optional       | \ref IVendorNameplateTypeBase::getSerialNumber "getSerialNumber", \ref IVendorNameplateTypeBase::setSerialNumber "setSerialNumber"
 *  SoftwareRevision   | String        | PropertyType   | Optional       | \ref IVendorNameplateTypeBase::getSoftwareRevision "getSoftwareRevision", \ref IVendorNameplateTypeBase::setSoftwareRevision "setSoftwareRevision"
 *
 */
class UAMODELS_EXPORT IVendorNameplateType:
    public IVendorNameplateTypeBase
{
    UA_DISABLE_COPY(IVendorNameplateType);
protected:
    // destruction
    virtual ~IVendorNameplateType();
public:
    // construction
    IVendorNameplateType(const UaNodeId& nodeId, UaObject* pInstanceDeclarationObject, NodeManagerConfig* pNodeConfig, UaMutexRefCounted* pSharedMutex = NULL);
    IVendorNameplateType(const UaNodeId& nodeId, const UaString& name, OpcUa_UInt16 browseNameNameSpaceIndex, NodeManagerConfig* pNodeConfig, UaMutexRefCounted* pSharedMutex = NULL);
    IVendorNameplateType(
        UaBase::Object*    pBaseNode,
        XmlUaNodeFactoryManager*   pFactory,
        NodeManagerConfig* pNodeConfig,
        UaMutexRefCounted* pSharedMutex = NULL);
    static void createTypes();
    static void clearStaticMembers();


protected:

private:
};

} // End namespace for the UA information model http://opcfoundation.org/UA/DI/

#endif // #ifndef __OPCUADIIVENDORNAMEPLATETYPE_H__

