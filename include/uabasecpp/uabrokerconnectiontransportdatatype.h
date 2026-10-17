/******************************************************************************
** uabrokerconnectiontransportdatatype.h
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
** Portable UaBrokerConnectionTransportDataType class.
**
******************************************************************************/
#ifndef UABROKERCONNECTIONTRANSPORTDATATYPE_H
#define UABROKERCONNECTIONTRANSPORTDATATYPE_H

#include <opcua_proxystub.h>

#include "uabase.h"
#include "uastring.h"
#include "uaarraytemplates.h"

class UaExtensionObject;
class UaVariant;
class UaDataValue;

class UABASE_EXPORT UaBrokerConnectionTransportDataTypePrivate;

/** @ingroup CppBaseLibraryClass
 *  @brief Wrapper class for the UA stack structure OpcUa_BrokerConnectionTransportDataType.
 *
 *  This class encapsulates the native OpcUa_BrokerConnectionTransportDataType structure
 *  and handles memory allocation and cleanup for you.
 *  UaBrokerConnectionTransportDataType uses implicit sharing to avoid needless copying and to boost the performance.
 *  Only if you modify a shared BrokerConnectionTransportDataType it creates a copy for that (copy-on-write).
 *  So assigning another UaBrokerConnectionTransportDataType or passing it as parameter needs constant time and is nearly as fast as assigning a pointer.
 */
class UABASE_EXPORT UaBrokerConnectionTransportDataType
{
    UA_DECLARE_PRIVATE(UaBrokerConnectionTransportDataType)
public:
    UaBrokerConnectionTransportDataType();
    UaBrokerConnectionTransportDataType(const UaBrokerConnectionTransportDataType &other);
    UaBrokerConnectionTransportDataType(const OpcUa_BrokerConnectionTransportDataType &other);
    UaBrokerConnectionTransportDataType(
        const UaString& resourceUri,
        const UaString& authenticationProfileUri
        );
    UaBrokerConnectionTransportDataType(const UaExtensionObject &extensionObject);
    UaBrokerConnectionTransportDataType(const OpcUa_ExtensionObject &extensionObject);
    UaBrokerConnectionTransportDataType(UaExtensionObject &extensionObject, OpcUa_Boolean bDetach);
    UaBrokerConnectionTransportDataType(OpcUa_ExtensionObject &extensionObject, OpcUa_Boolean bDetach);
    ~UaBrokerConnectionTransportDataType();

    void clear();

    bool operator==(const UaBrokerConnectionTransportDataType &other) const;
    bool operator!=(const UaBrokerConnectionTransportDataType &other) const;

    UaBrokerConnectionTransportDataType& operator=(const UaBrokerConnectionTransportDataType &other);

    OpcUa_BrokerConnectionTransportDataType* copy() const;
    void copyTo(OpcUa_BrokerConnectionTransportDataType *pDst) const;

    static OpcUa_BrokerConnectionTransportDataType* clone(const OpcUa_BrokerConnectionTransportDataType& source);
    static void cloneTo(const OpcUa_BrokerConnectionTransportDataType& source, OpcUa_BrokerConnectionTransportDataType& copy);

    void attach(OpcUa_BrokerConnectionTransportDataType *pValue);
    OpcUa_BrokerConnectionTransportDataType* detach(OpcUa_BrokerConnectionTransportDataType* pDst);

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

    OpcUa_StatusCode setBrokerConnectionTransportDataType(const UaExtensionObject &extensionObject);
    OpcUa_StatusCode setBrokerConnectionTransportDataType(const OpcUa_ExtensionObject &extensionObject);
    OpcUa_StatusCode setBrokerConnectionTransportDataType(UaExtensionObject &extensionObject, OpcUa_Boolean bDetach);
    OpcUa_StatusCode setBrokerConnectionTransportDataType(OpcUa_ExtensionObject &extensionObject, OpcUa_Boolean bDetach);

    void setBrokerConnectionTransportDataType(
        const UaString& resourceUri,
        const UaString& authenticationProfileUri
        );

    UaString getResourceUri() const;
    UaString getAuthenticationProfileUri() const;

    void setResourceUri(const UaString& resourceUri);
    void setAuthenticationProfileUri(const UaString& authenticationProfileUri);
};

/** @ingroup CppBaseLibraryClass
 *  @brief Array class for the UA stack structure OpcUa_BrokerConnectionTransportDataType.
 *
 *  This class encapsulates an array of the native OpcUa_BrokerConnectionTransportDataType structure
 *  and handles memory allocation and cleanup for you.
 *  @see UaBrokerConnectionTransportDataType for information about the encapsulated structure.
 */
class UABASE_EXPORT UaBrokerConnectionTransportDataTypes
{
public:
    UaBrokerConnectionTransportDataTypes();
    UaBrokerConnectionTransportDataTypes(const UaBrokerConnectionTransportDataTypes &other);
    UaBrokerConnectionTransportDataTypes(OpcUa_Int32 length, OpcUa_BrokerConnectionTransportDataType* data);
    virtual ~UaBrokerConnectionTransportDataTypes();

    UaBrokerConnectionTransportDataTypes& operator=(const UaBrokerConnectionTransportDataTypes &other);
    const OpcUa_BrokerConnectionTransportDataType& operator[](OpcUa_UInt32 index) const;
    OpcUa_BrokerConnectionTransportDataType& operator[](OpcUa_UInt32 index);

    bool operator==(const UaBrokerConnectionTransportDataTypes &other) const;
    bool operator!=(const UaBrokerConnectionTransportDataTypes &other) const;

    void attach(OpcUa_UInt32 length, OpcUa_BrokerConnectionTransportDataType* data);
    void attach(OpcUa_Int32 length, OpcUa_BrokerConnectionTransportDataType* data);
    OpcUa_BrokerConnectionTransportDataType* detach();

    void create(OpcUa_UInt32 length);
    void resize(OpcUa_UInt32 length);
    void clear();

    inline OpcUa_UInt32 length() const {return m_noOfElements;}
    inline const OpcUa_BrokerConnectionTransportDataType* rawData() const {return m_data;}
    inline OpcUa_BrokerConnectionTransportDataType* rawData() {return m_data;}

    void toVariant(UaVariant &variant) const;
    void toVariant(OpcUa_Variant &variant) const;
    void toVariant(UaVariant &variant, OpcUa_Boolean bDetach);
    void toVariant(OpcUa_Variant &variant, OpcUa_Boolean bDetach);

    void toDataValue(UaDataValue &dataValue, OpcUa_Boolean updateTimeStamps) const;
    void toDataValue(OpcUa_DataValue &dataValue, OpcUa_Boolean updateTimeStamps) const;
    void toDataValue(UaDataValue &dataValue, OpcUa_Boolean bDetach, OpcUa_Boolean updateTimeStamps);
    void toDataValue(OpcUa_DataValue &dataValue, OpcUa_Boolean bDetach, OpcUa_Boolean updateTimeStamps);

    OpcUa_StatusCode setBrokerConnectionTransportDataTypes(const UaVariant &variant);
    OpcUa_StatusCode setBrokerConnectionTransportDataTypes(const OpcUa_Variant &variant);
    OpcUa_StatusCode setBrokerConnectionTransportDataTypes(UaVariant &variant, OpcUa_Boolean bDetach);
    OpcUa_StatusCode setBrokerConnectionTransportDataTypes(OpcUa_Variant &variant, OpcUa_Boolean bDetach);
    OpcUa_StatusCode setBrokerConnectionTransportDataTypes(OpcUa_Int32 length, OpcUa_BrokerConnectionTransportDataType* data);

private:
    OpcUa_UInt32 m_noOfElements;
    OpcUa_BrokerConnectionTransportDataType* m_data;
};

#endif // UABROKERCONNECTIONTRANSPORTDATATYPE_H

