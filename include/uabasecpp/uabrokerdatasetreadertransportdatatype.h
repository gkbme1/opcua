/******************************************************************************
** uabrokerdatasetreadertransportdatatype.h
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
** Portable UaBrokerDataSetReaderTransportDataType class.
**
******************************************************************************/
#ifndef UABROKERDATASETREADERTRANSPORTDATATYPE_H
#define UABROKERDATASETREADERTRANSPORTDATATYPE_H

#include <opcua_proxystub.h>

#include "uabase.h"
#include "uastring.h"
#include "uaarraytemplates.h"

class UaExtensionObject;
class UaVariant;
class UaDataValue;

class UABASE_EXPORT UaBrokerDataSetReaderTransportDataTypePrivate;

/** @ingroup CppBaseLibraryClass
 *  @brief Wrapper class for the UA stack structure OpcUa_BrokerDataSetReaderTransportDataType.
 *
 *  This class encapsulates the native OpcUa_BrokerDataSetReaderTransportDataType structure
 *  and handles memory allocation and cleanup for you.
 *  UaBrokerDataSetReaderTransportDataType uses implicit sharing to avoid needless copying and to boost the performance.
 *  Only if you modify a shared BrokerDataSetReaderTransportDataType it creates a copy for that (copy-on-write).
 *  So assigning another UaBrokerDataSetReaderTransportDataType or passing it as parameter needs constant time and is nearly as fast as assigning a pointer.
 */
class UABASE_EXPORT UaBrokerDataSetReaderTransportDataType
{
    UA_DECLARE_PRIVATE(UaBrokerDataSetReaderTransportDataType)
public:
    UaBrokerDataSetReaderTransportDataType();
    UaBrokerDataSetReaderTransportDataType(const UaBrokerDataSetReaderTransportDataType &other);
    UaBrokerDataSetReaderTransportDataType(const OpcUa_BrokerDataSetReaderTransportDataType &other);
    UaBrokerDataSetReaderTransportDataType(
        const UaString& queueName,
        const UaString& resourceUri,
        const UaString& authenticationProfileUri,
        OpcUa_BrokerTransportQualityOfService requestedDeliveryGuarantee,
        const UaString& metaDataQueueName
        );
    UaBrokerDataSetReaderTransportDataType(const UaExtensionObject &extensionObject);
    UaBrokerDataSetReaderTransportDataType(const OpcUa_ExtensionObject &extensionObject);
    UaBrokerDataSetReaderTransportDataType(UaExtensionObject &extensionObject, OpcUa_Boolean bDetach);
    UaBrokerDataSetReaderTransportDataType(OpcUa_ExtensionObject &extensionObject, OpcUa_Boolean bDetach);
    ~UaBrokerDataSetReaderTransportDataType();

    void clear();

    bool operator==(const UaBrokerDataSetReaderTransportDataType &other) const;
    bool operator!=(const UaBrokerDataSetReaderTransportDataType &other) const;

    UaBrokerDataSetReaderTransportDataType& operator=(const UaBrokerDataSetReaderTransportDataType &other);

    OpcUa_BrokerDataSetReaderTransportDataType* copy() const;
    void copyTo(OpcUa_BrokerDataSetReaderTransportDataType *pDst) const;

    static OpcUa_BrokerDataSetReaderTransportDataType* clone(const OpcUa_BrokerDataSetReaderTransportDataType& source);
    static void cloneTo(const OpcUa_BrokerDataSetReaderTransportDataType& source, OpcUa_BrokerDataSetReaderTransportDataType& copy);

    void attach(OpcUa_BrokerDataSetReaderTransportDataType *pValue);
    OpcUa_BrokerDataSetReaderTransportDataType* detach(OpcUa_BrokerDataSetReaderTransportDataType* pDst);

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

    OpcUa_StatusCode setBrokerDataSetReaderTransportDataType(const UaExtensionObject &extensionObject);
    OpcUa_StatusCode setBrokerDataSetReaderTransportDataType(const OpcUa_ExtensionObject &extensionObject);
    OpcUa_StatusCode setBrokerDataSetReaderTransportDataType(UaExtensionObject &extensionObject, OpcUa_Boolean bDetach);
    OpcUa_StatusCode setBrokerDataSetReaderTransportDataType(OpcUa_ExtensionObject &extensionObject, OpcUa_Boolean bDetach);

    void setBrokerDataSetReaderTransportDataType(
        const UaString& queueName,
        const UaString& resourceUri,
        const UaString& authenticationProfileUri,
        OpcUa_BrokerTransportQualityOfService requestedDeliveryGuarantee,
        const UaString& metaDataQueueName
        );

    UaString getQueueName() const;
    UaString getResourceUri() const;
    UaString getAuthenticationProfileUri() const;
    OpcUa_BrokerTransportQualityOfService getRequestedDeliveryGuarantee() const;
    UaString getMetaDataQueueName() const;

    void setQueueName(const UaString& queueName);
    void setResourceUri(const UaString& resourceUri);
    void setAuthenticationProfileUri(const UaString& authenticationProfileUri);
    void setRequestedDeliveryGuarantee(OpcUa_BrokerTransportQualityOfService requestedDeliveryGuarantee);
    void setMetaDataQueueName(const UaString& metaDataQueueName);
};

/** @ingroup CppBaseLibraryClass
 *  @brief Array class for the UA stack structure OpcUa_BrokerDataSetReaderTransportDataType.
 *
 *  This class encapsulates an array of the native OpcUa_BrokerDataSetReaderTransportDataType structure
 *  and handles memory allocation and cleanup for you.
 *  @see UaBrokerDataSetReaderTransportDataType for information about the encapsulated structure.
 */
class UABASE_EXPORT UaBrokerDataSetReaderTransportDataTypes
{
public:
    UaBrokerDataSetReaderTransportDataTypes();
    UaBrokerDataSetReaderTransportDataTypes(const UaBrokerDataSetReaderTransportDataTypes &other);
    UaBrokerDataSetReaderTransportDataTypes(OpcUa_Int32 length, OpcUa_BrokerDataSetReaderTransportDataType* data);
    virtual ~UaBrokerDataSetReaderTransportDataTypes();

    UaBrokerDataSetReaderTransportDataTypes& operator=(const UaBrokerDataSetReaderTransportDataTypes &other);
    const OpcUa_BrokerDataSetReaderTransportDataType& operator[](OpcUa_UInt32 index) const;
    OpcUa_BrokerDataSetReaderTransportDataType& operator[](OpcUa_UInt32 index);

    bool operator==(const UaBrokerDataSetReaderTransportDataTypes &other) const;
    bool operator!=(const UaBrokerDataSetReaderTransportDataTypes &other) const;

    void attach(OpcUa_UInt32 length, OpcUa_BrokerDataSetReaderTransportDataType* data);
    void attach(OpcUa_Int32 length, OpcUa_BrokerDataSetReaderTransportDataType* data);
    OpcUa_BrokerDataSetReaderTransportDataType* detach();

    void create(OpcUa_UInt32 length);
    void resize(OpcUa_UInt32 length);
    void clear();

    inline OpcUa_UInt32 length() const {return m_noOfElements;}
    inline const OpcUa_BrokerDataSetReaderTransportDataType* rawData() const {return m_data;}
    inline OpcUa_BrokerDataSetReaderTransportDataType* rawData() {return m_data;}

    void toVariant(UaVariant &variant) const;
    void toVariant(OpcUa_Variant &variant) const;
    void toVariant(UaVariant &variant, OpcUa_Boolean bDetach);
    void toVariant(OpcUa_Variant &variant, OpcUa_Boolean bDetach);

    void toDataValue(UaDataValue &dataValue, OpcUa_Boolean updateTimeStamps) const;
    void toDataValue(OpcUa_DataValue &dataValue, OpcUa_Boolean updateTimeStamps) const;
    void toDataValue(UaDataValue &dataValue, OpcUa_Boolean bDetach, OpcUa_Boolean updateTimeStamps);
    void toDataValue(OpcUa_DataValue &dataValue, OpcUa_Boolean bDetach, OpcUa_Boolean updateTimeStamps);

    OpcUa_StatusCode setBrokerDataSetReaderTransportDataTypes(const UaVariant &variant);
    OpcUa_StatusCode setBrokerDataSetReaderTransportDataTypes(const OpcUa_Variant &variant);
    OpcUa_StatusCode setBrokerDataSetReaderTransportDataTypes(UaVariant &variant, OpcUa_Boolean bDetach);
    OpcUa_StatusCode setBrokerDataSetReaderTransportDataTypes(OpcUa_Variant &variant, OpcUa_Boolean bDetach);
    OpcUa_StatusCode setBrokerDataSetReaderTransportDataTypes(OpcUa_Int32 length, OpcUa_BrokerDataSetReaderTransportDataType* data);

private:
    OpcUa_UInt32 m_noOfElements;
    OpcUa_BrokerDataSetReaderTransportDataType* m_data;
};

#endif // UABROKERDATASETREADERTRANSPORTDATATYPE_H

