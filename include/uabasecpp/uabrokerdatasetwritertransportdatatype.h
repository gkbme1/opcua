/******************************************************************************
** uabrokerdatasetwritertransportdatatype.h
**
** Copyright (c) 2006-2020 Unified Automation GmbH All rights reserved.
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
** Project: C++ OPC SDK base module
**
** Portable UaBrokerDataSetWriterTransportDataType class.
**
******************************************************************************/
#ifndef UABROKERDATASETWRITERTRANSPORTDATATYPE_H
#define UABROKERDATASETWRITERTRANSPORTDATATYPE_H

#include <opcua_proxystub.h>

#include "uabase.h"
#include "uastring.h"
#include "uaarraytemplates.h"

class UaExtensionObject;
class UaVariant;
class UaDataValue;

class UABASE_EXPORT UaBrokerDataSetWriterTransportDataTypePrivate;

/** @ingroup CppBaseLibraryClass
 *  @brief Wrapper class for the UA stack structure OpcUa_BrokerDataSetWriterTransportDataType.
 *
 *  This class encapsulates the native OpcUa_BrokerDataSetWriterTransportDataType structure
 *  and handles memory allocation and cleanup for you.
 *  UaBrokerDataSetWriterTransportDataType uses implicit sharing to avoid needless copying and to boost the performance.
 *  Only if you modify a shared BrokerDataSetWriterTransportDataType it creates a copy for that (copy-on-write).
 *  So assigning another UaBrokerDataSetWriterTransportDataType or passing it as parameter needs constant time and is nearly as fast as assigning a pointer.
 */
class UABASE_EXPORT UaBrokerDataSetWriterTransportDataType
{
    UA_DECLARE_PRIVATE(UaBrokerDataSetWriterTransportDataType)
public:
    UaBrokerDataSetWriterTransportDataType();
    UaBrokerDataSetWriterTransportDataType(const UaBrokerDataSetWriterTransportDataType &other);
    UaBrokerDataSetWriterTransportDataType(const OpcUa_BrokerDataSetWriterTransportDataType &other);
    UaBrokerDataSetWriterTransportDataType(
        const UaString& queueName,
        const UaString& resourceUri,
        const UaString& authenticationProfileUri,
        OpcUa_BrokerTransportQualityOfService requestedDeliveryGuarantee,
        const UaString& metaDataQueueName,
        OpcUa_Double metaDataUpdateTime
        );
    UaBrokerDataSetWriterTransportDataType(const UaExtensionObject &extensionObject);
    UaBrokerDataSetWriterTransportDataType(const OpcUa_ExtensionObject &extensionObject);
    UaBrokerDataSetWriterTransportDataType(UaExtensionObject &extensionObject, OpcUa_Boolean bDetach);
    UaBrokerDataSetWriterTransportDataType(OpcUa_ExtensionObject &extensionObject, OpcUa_Boolean bDetach);
    ~UaBrokerDataSetWriterTransportDataType();

    void clear();

    bool operator==(const UaBrokerDataSetWriterTransportDataType &other) const;
    bool operator!=(const UaBrokerDataSetWriterTransportDataType &other) const;

    UaBrokerDataSetWriterTransportDataType& operator=(const UaBrokerDataSetWriterTransportDataType &other);

    OpcUa_BrokerDataSetWriterTransportDataType* copy() const;
    void copyTo(OpcUa_BrokerDataSetWriterTransportDataType *pDst) const;

    static OpcUa_BrokerDataSetWriterTransportDataType* clone(const OpcUa_BrokerDataSetWriterTransportDataType& source);
    static void cloneTo(const OpcUa_BrokerDataSetWriterTransportDataType& source, OpcUa_BrokerDataSetWriterTransportDataType& copy);

    void attach(OpcUa_BrokerDataSetWriterTransportDataType *pValue);
    OpcUa_BrokerDataSetWriterTransportDataType* detach(OpcUa_BrokerDataSetWriterTransportDataType* pDst);

    void toVariant(UaVariant &variant) const;
    void toVariant(OpcUa_Variant &variant) const;
    void toVariant(UaVariant &variant, OpcUa_Boolean bDetach);
    void toVariant(OpcUa_Variant &variant, OpcUa_Boolean bDetach);

    void toDataValue(UaDataValue &dataValue, OpcUa_Boolean updateTimeStamps) const;
    void toDataValue(OpcUa_DataValue &dataValue, OpcUa_Boolean updateTimeStamps) const;
    void toDataValue(UaDataValue &dataValue, OpcUa_Boolean bDetach, OpcUa_Boolean updateTimeStamps);
    void toDataValue(OpcUa_DataValue &dataValue, OpcUa_Boolean bDetach, OpcUa_Boolean updateTimeStamps);

    void toExtensionObject(UaExtensionObject &extensionObject) const;
    void toExtensionObject(OpcUa_ExtensionObject &extensionObject) const;
    void toExtensionObject(UaExtensionObject &extensionObject, OpcUa_Boolean bDetach);
    void toExtensionObject(OpcUa_ExtensionObject &extensionObject, OpcUa_Boolean bDetach);

    OpcUa_StatusCode setBrokerDataSetWriterTransportDataType(const UaExtensionObject &extensionObject);
    OpcUa_StatusCode setBrokerDataSetWriterTransportDataType(const OpcUa_ExtensionObject &extensionObject);
    OpcUa_StatusCode setBrokerDataSetWriterTransportDataType(UaExtensionObject &extensionObject, OpcUa_Boolean bDetach);
    OpcUa_StatusCode setBrokerDataSetWriterTransportDataType(OpcUa_ExtensionObject &extensionObject, OpcUa_Boolean bDetach);

    void setBrokerDataSetWriterTransportDataType(
        const UaString& queueName,
        const UaString& resourceUri,
        const UaString& authenticationProfileUri,
        OpcUa_BrokerTransportQualityOfService requestedDeliveryGuarantee,
        const UaString& metaDataQueueName,
        OpcUa_Double metaDataUpdateTime
        );

    UaString getQueueName() const;
    UaString getResourceUri() const;
    UaString getAuthenticationProfileUri() const;
    OpcUa_BrokerTransportQualityOfService getRequestedDeliveryGuarantee() const;
    UaString getMetaDataQueueName() const;
    OpcUa_Double getMetaDataUpdateTime() const;

    void setQueueName(const UaString& queueName);
    void setResourceUri(const UaString& resourceUri);
    void setAuthenticationProfileUri(const UaString& authenticationProfileUri);
    void setRequestedDeliveryGuarantee(OpcUa_BrokerTransportQualityOfService requestedDeliveryGuarantee);
    void setMetaDataQueueName(const UaString& metaDataQueueName);
    void setMetaDataUpdateTime(OpcUa_Double metaDataUpdateTime);
};

/** @ingroup CppBaseLibraryClass
 *  @brief Array class for the UA stack structure OpcUa_BrokerDataSetWriterTransportDataType.
 *
 *  This class encapsulates an array of the native OpcUa_BrokerDataSetWriterTransportDataType structure
 *  and handles memory allocation and cleanup for you.
 *  @see UaBrokerDataSetWriterTransportDataType for information about the encapsulated structure.
 */
class UABASE_EXPORT UaBrokerDataSetWriterTransportDataTypes
{
public:
    UaBrokerDataSetWriterTransportDataTypes();
    UaBrokerDataSetWriterTransportDataTypes(const UaBrokerDataSetWriterTransportDataTypes &other);
    UaBrokerDataSetWriterTransportDataTypes(OpcUa_Int32 length, OpcUa_BrokerDataSetWriterTransportDataType* data);
    virtual ~UaBrokerDataSetWriterTransportDataTypes();

    UaBrokerDataSetWriterTransportDataTypes& operator=(const UaBrokerDataSetWriterTransportDataTypes &other);
    const OpcUa_BrokerDataSetWriterTransportDataType& operator[](OpcUa_UInt32 index) const;
    OpcUa_BrokerDataSetWriterTransportDataType& operator[](OpcUa_UInt32 index);

    bool operator==(const UaBrokerDataSetWriterTransportDataTypes &other) const;
    bool operator!=(const UaBrokerDataSetWriterTransportDataTypes &other) const;

    void attach(OpcUa_UInt32 length, OpcUa_BrokerDataSetWriterTransportDataType* data);
    void attach(OpcUa_Int32 length, OpcUa_BrokerDataSetWriterTransportDataType* data);
    OpcUa_BrokerDataSetWriterTransportDataType* detach();

    void create(OpcUa_UInt32 length);
    void resize(OpcUa_UInt32 length);
    void clear();

    inline OpcUa_UInt32 length() const {return m_noOfElements;}
    inline const OpcUa_BrokerDataSetWriterTransportDataType* rawData() const {return m_data;}
    inline OpcUa_BrokerDataSetWriterTransportDataType* rawData() {return m_data;}

    void toVariant(UaVariant &variant) const;
    void toVariant(OpcUa_Variant &variant) const;
    void toVariant(UaVariant &variant, OpcUa_Boolean bDetach);
    void toVariant(OpcUa_Variant &variant, OpcUa_Boolean bDetach);

    void toDataValue(UaDataValue &dataValue, OpcUa_Boolean updateTimeStamps) const;
    void toDataValue(OpcUa_DataValue &dataValue, OpcUa_Boolean updateTimeStamps) const;
    void toDataValue(UaDataValue &dataValue, OpcUa_Boolean bDetach, OpcUa_Boolean updateTimeStamps);
    void toDataValue(OpcUa_DataValue &dataValue, OpcUa_Boolean bDetach, OpcUa_Boolean updateTimeStamps);

    OpcUa_StatusCode setBrokerDataSetWriterTransportDataTypes(const UaVariant &variant);
    OpcUa_StatusCode setBrokerDataSetWriterTransportDataTypes(const OpcUa_Variant &variant);
    OpcUa_StatusCode setBrokerDataSetWriterTransportDataTypes(UaVariant &variant, OpcUa_Boolean bDetach);
    OpcUa_StatusCode setBrokerDataSetWriterTransportDataTypes(OpcUa_Variant &variant, OpcUa_Boolean bDetach);
    OpcUa_StatusCode setBrokerDataSetWriterTransportDataTypes(OpcUa_Int32 length, OpcUa_BrokerDataSetWriterTransportDataType* data);

private:
    OpcUa_UInt32 m_noOfElements;
    OpcUa_BrokerDataSetWriterTransportDataType* m_data;
};

#endif // UABROKERDATASETWRITERTRANSPORTDATATYPE_H

