/******************************************************************************
** uabrokerwritergrouptransportdatatype.h
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
** Portable UaBrokerWriterGroupTransportDataType class.
**
******************************************************************************/
#ifndef UABROKERWRITERGROUPTRANSPORTDATATYPE_H
#define UABROKERWRITERGROUPTRANSPORTDATATYPE_H

#include <opcua_proxystub.h>

#include "uabase.h"
#include "uastring.h"
#include "uaarraytemplates.h"

class UaExtensionObject;
class UaVariant;
class UaDataValue;

class UABASE_EXPORT UaBrokerWriterGroupTransportDataTypePrivate;

/** @ingroup CppBaseLibraryClass
 *  @brief Wrapper class for the UA stack structure OpcUa_BrokerWriterGroupTransportDataType.
 *
 *  This class encapsulates the native OpcUa_BrokerWriterGroupTransportDataType structure
 *  and handles memory allocation and cleanup for you.
 *  UaBrokerWriterGroupTransportDataType uses implicit sharing to avoid needless copying and to boost the performance.
 *  Only if you modify a shared BrokerWriterGroupTransportDataType it creates a copy for that (copy-on-write).
 *  So assigning another UaBrokerWriterGroupTransportDataType or passing it as parameter needs constant time and is nearly as fast as assigning a pointer.
 */
class UABASE_EXPORT UaBrokerWriterGroupTransportDataType
{
    UA_DECLARE_PRIVATE(UaBrokerWriterGroupTransportDataType)
public:
    UaBrokerWriterGroupTransportDataType();
    UaBrokerWriterGroupTransportDataType(const UaBrokerWriterGroupTransportDataType &other);
    UaBrokerWriterGroupTransportDataType(const OpcUa_BrokerWriterGroupTransportDataType &other);
    UaBrokerWriterGroupTransportDataType(
        const UaString& queueName,
        const UaString& resourceUri,
        const UaString& authenticationProfileUri,
        OpcUa_BrokerTransportQualityOfService requestedDeliveryGuarantee
        );
    UaBrokerWriterGroupTransportDataType(const UaExtensionObject &extensionObject);
    UaBrokerWriterGroupTransportDataType(const OpcUa_ExtensionObject &extensionObject);
    UaBrokerWriterGroupTransportDataType(UaExtensionObject &extensionObject, OpcUa_Boolean bDetach);
    UaBrokerWriterGroupTransportDataType(OpcUa_ExtensionObject &extensionObject, OpcUa_Boolean bDetach);
    ~UaBrokerWriterGroupTransportDataType();

    void clear();

    bool operator==(const UaBrokerWriterGroupTransportDataType &other) const;
    bool operator!=(const UaBrokerWriterGroupTransportDataType &other) const;

    UaBrokerWriterGroupTransportDataType& operator=(const UaBrokerWriterGroupTransportDataType &other);

    OpcUa_BrokerWriterGroupTransportDataType* copy() const;
    void copyTo(OpcUa_BrokerWriterGroupTransportDataType *pDst) const;

    static OpcUa_BrokerWriterGroupTransportDataType* clone(const OpcUa_BrokerWriterGroupTransportDataType& source);
    static void cloneTo(const OpcUa_BrokerWriterGroupTransportDataType& source, OpcUa_BrokerWriterGroupTransportDataType& copy);

    void attach(OpcUa_BrokerWriterGroupTransportDataType *pValue);
    OpcUa_BrokerWriterGroupTransportDataType* detach(OpcUa_BrokerWriterGroupTransportDataType* pDst);

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

    OpcUa_StatusCode setBrokerWriterGroupTransportDataType(const UaExtensionObject &extensionObject);
    OpcUa_StatusCode setBrokerWriterGroupTransportDataType(const OpcUa_ExtensionObject &extensionObject);
    OpcUa_StatusCode setBrokerWriterGroupTransportDataType(UaExtensionObject &extensionObject, OpcUa_Boolean bDetach);
    OpcUa_StatusCode setBrokerWriterGroupTransportDataType(OpcUa_ExtensionObject &extensionObject, OpcUa_Boolean bDetach);

    void setBrokerWriterGroupTransportDataType(
        const UaString& queueName,
        const UaString& resourceUri,
        const UaString& authenticationProfileUri,
        OpcUa_BrokerTransportQualityOfService requestedDeliveryGuarantee
        );

    UaString getQueueName() const;
    UaString getResourceUri() const;
    UaString getAuthenticationProfileUri() const;
    OpcUa_BrokerTransportQualityOfService getRequestedDeliveryGuarantee() const;

    void setQueueName(const UaString& queueName);
    void setResourceUri(const UaString& resourceUri);
    void setAuthenticationProfileUri(const UaString& authenticationProfileUri);
    void setRequestedDeliveryGuarantee(OpcUa_BrokerTransportQualityOfService requestedDeliveryGuarantee);
};

/** @ingroup CppBaseLibraryClass
 *  @brief Array class for the UA stack structure OpcUa_BrokerWriterGroupTransportDataType.
 *
 *  This class encapsulates an array of the native OpcUa_BrokerWriterGroupTransportDataType structure
 *  and handles memory allocation and cleanup for you.
 *  @see UaBrokerWriterGroupTransportDataType for information about the encapsulated structure.
 */
class UABASE_EXPORT UaBrokerWriterGroupTransportDataTypes
{
public:
    UaBrokerWriterGroupTransportDataTypes();
    UaBrokerWriterGroupTransportDataTypes(const UaBrokerWriterGroupTransportDataTypes &other);
    UaBrokerWriterGroupTransportDataTypes(OpcUa_Int32 length, OpcUa_BrokerWriterGroupTransportDataType* data);
    virtual ~UaBrokerWriterGroupTransportDataTypes();

    UaBrokerWriterGroupTransportDataTypes& operator=(const UaBrokerWriterGroupTransportDataTypes &other);
    const OpcUa_BrokerWriterGroupTransportDataType& operator[](OpcUa_UInt32 index) const;
    OpcUa_BrokerWriterGroupTransportDataType& operator[](OpcUa_UInt32 index);

    bool operator==(const UaBrokerWriterGroupTransportDataTypes &other) const;
    bool operator!=(const UaBrokerWriterGroupTransportDataTypes &other) const;

    void attach(OpcUa_UInt32 length, OpcUa_BrokerWriterGroupTransportDataType* data);
    void attach(OpcUa_Int32 length, OpcUa_BrokerWriterGroupTransportDataType* data);
    OpcUa_BrokerWriterGroupTransportDataType* detach();

    void create(OpcUa_UInt32 length);
    void resize(OpcUa_UInt32 length);
    void clear();

    inline OpcUa_UInt32 length() const {return m_noOfElements;}
    inline const OpcUa_BrokerWriterGroupTransportDataType* rawData() const {return m_data;}
    inline OpcUa_BrokerWriterGroupTransportDataType* rawData() {return m_data;}

    void toVariant(UaVariant &variant) const;
    void toVariant(OpcUa_Variant &variant) const;
    void toVariant(UaVariant &variant, OpcUa_Boolean bDetach);
    void toVariant(OpcUa_Variant &variant, OpcUa_Boolean bDetach);

    void toDataValue(UaDataValue &dataValue, OpcUa_Boolean updateTimeStamps) const;
    void toDataValue(OpcUa_DataValue &dataValue, OpcUa_Boolean updateTimeStamps) const;
    void toDataValue(UaDataValue &dataValue, OpcUa_Boolean bDetach, OpcUa_Boolean updateTimeStamps);
    void toDataValue(OpcUa_DataValue &dataValue, OpcUa_Boolean bDetach, OpcUa_Boolean updateTimeStamps);

    OpcUa_StatusCode setBrokerWriterGroupTransportDataTypes(const UaVariant &variant);
    OpcUa_StatusCode setBrokerWriterGroupTransportDataTypes(const OpcUa_Variant &variant);
    OpcUa_StatusCode setBrokerWriterGroupTransportDataTypes(UaVariant &variant, OpcUa_Boolean bDetach);
    OpcUa_StatusCode setBrokerWriterGroupTransportDataTypes(OpcUa_Variant &variant, OpcUa_Boolean bDetach);
    OpcUa_StatusCode setBrokerWriterGroupTransportDataTypes(OpcUa_Int32 length, OpcUa_BrokerWriterGroupTransportDataType* data);

private:
    OpcUa_UInt32 m_noOfElements;
    OpcUa_BrokerWriterGroupTransportDataType* m_data;
};

#endif // UABROKERWRITERGROUPTRANSPORTDATATYPE_H

