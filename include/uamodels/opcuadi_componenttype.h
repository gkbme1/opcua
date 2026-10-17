/******************************************************************************
** opcuadi_componenttype.h
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

#ifndef __OPCUADI_COMPONENTTYPE_H__
#define __OPCUADI_COMPONENTTYPE_H__

#include "opcuadi_componenttypebase.h"

// Namespace for the UA information model http://opcfoundation.org/UA/DI/
namespace OpcUaDi {

/** @brief Class implementing the UaObject interface for the ComponentType.
 *
 * OPC UA Objects are used to represent systems, system components, real-world objects and software
 * objects. They have the NodeClass Object. The detailed description of Objects and their attributes
 * can be found in the general description of the Object node class.
 *
 *  **Variable members of the ComponentType:**
 *
 *  Browse Name        | DataType      | TypeDefinition | Modelling Rule | See Also
 *  -------------------|---------------|----------------|----------------|---------------------------------------------------------------------------------------------------------------------------------------------
 *  AssetId            | String        | PropertyType   | Optional       | \ref ComponentTypeBase::getAssetId "getAssetId", \ref ComponentTypeBase::setAssetId "setAssetId"
 *  ComponentName      | LocalizedText | PropertyType   | Optional       | \ref ComponentTypeBase::getComponentName "getComponentName", \ref ComponentTypeBase::setComponentName "setComponentName"
 *  DeviceClass        | String        | PropertyType   | Optional       | \ref ComponentTypeBase::getDeviceClass "getDeviceClass", \ref ComponentTypeBase::setDeviceClass "setDeviceClass"
 *  DeviceManual       | String        | PropertyType   | Optional       | \ref ComponentTypeBase::getDeviceManual "getDeviceManual", \ref ComponentTypeBase::setDeviceManual "setDeviceManual"
 *  DeviceRevision     | String        | PropertyType   | Optional       | \ref ComponentTypeBase::getDeviceRevision "getDeviceRevision", \ref ComponentTypeBase::setDeviceRevision "setDeviceRevision"
 *  HardwareRevision   | String        | PropertyType   | Optional       | \ref ComponentTypeBase::getHardwareRevision "getHardwareRevision", \ref ComponentTypeBase::setHardwareRevision "setHardwareRevision"
 *  Manufacturer       | LocalizedText | PropertyType   | Optional       | \ref ComponentTypeBase::getManufacturer "getManufacturer", \ref ComponentTypeBase::setManufacturer "setManufacturer"
 *  ManufacturerUri    | String        | PropertyType   | Optional       | \ref ComponentTypeBase::getManufacturerUri "getManufacturerUri", \ref ComponentTypeBase::setManufacturerUri "setManufacturerUri"
 *  Model              | LocalizedText | PropertyType   | Optional       | \ref ComponentTypeBase::getModel "getModel", \ref ComponentTypeBase::setModel "setModel"
 *  ProductCode        | String        | PropertyType   | Optional       | \ref ComponentTypeBase::getProductCode "getProductCode", \ref ComponentTypeBase::setProductCode "setProductCode"
 *  ProductInstanceUri | String        | PropertyType   | Optional       | \ref ComponentTypeBase::getProductInstanceUri "getProductInstanceUri", \ref ComponentTypeBase::setProductInstanceUri "setProductInstanceUri"
 *  RevisionCounter    | Int32         | PropertyType   | Optional       | \ref ComponentTypeBase::getRevisionCounter "getRevisionCounter", \ref ComponentTypeBase::setRevisionCounter "setRevisionCounter"
 *  SerialNumber       | String        | PropertyType   | Optional       | \ref ComponentTypeBase::getSerialNumber "getSerialNumber", \ref ComponentTypeBase::setSerialNumber "setSerialNumber"
 *  SoftwareRevision   | String        | PropertyType   | Optional       | \ref ComponentTypeBase::getSoftwareRevision "getSoftwareRevision", \ref ComponentTypeBase::setSoftwareRevision "setSoftwareRevision"
 *
 */
class UAMODELS_EXPORT ComponentType:
    public ComponentTypeBase
{
    UA_DISABLE_COPY(ComponentType);
protected:
    // destruction
    virtual ~ComponentType();
public:
    // construction
    ComponentType(const UaNodeId& nodeId, UaObject* pInstanceDeclarationObject, NodeManagerConfig* pNodeConfig, UaMutexRefCounted* pSharedMutex = NULL);
    ComponentType(const UaNodeId& nodeId, const UaString& name, OpcUa_UInt16 browseNameNameSpaceIndex, NodeManagerConfig* pNodeConfig, UaMutexRefCounted* pSharedMutex = NULL);
    ComponentType(
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

#endif // #ifndef __OPCUADICOMPONENTTYPE_H__

