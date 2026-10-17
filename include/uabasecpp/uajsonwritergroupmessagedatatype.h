/******************************************************************************
** uajsonwritergroupmessagedatatype.h
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
** Portable UaJsonWriterGroupMessageDataType class.
**
******************************************************************************/
#ifndef UAJSONWRITERGROUPMESSAGEDATATYPE_H
#define UAJSONWRITERGROUPMESSAGEDATATYPE_H

#include <opcua_proxystub.h>

#include "uabase.h"
#include "uaarraytemplates.h"

class UaExtensionObject;
class UaVariant;
class UaDataValue;

class UABASE_EXPORT UaJsonWriterGroupMessageDataTypePrivate;

/** @ingroup CppBaseLibraryClass
 *  @brief Wrapper class for the UA stack structure OpcUa_JsonWriterGroupMessageDataType.
 *
 *  This class encapsulates the native OpcUa_JsonWriterGroupMessageDataType structure
 *  and handles memory allocation and cleanup for you.
 *  UaJsonWriterGroupMessageDataType uses implicit sharing to avoid needless copying and to boost the performance.
 *  Only if you modify a shared JsonWriterGroupMessageDataType it creates a copy for that (copy-on-write).
 *  So assigning another UaJsonWriterGroupMessageDataType or passing it as parameter needs constant time and is nearly as fast as assigning a pointer.
 */
class UABASE_EXPORT UaJsonWriterGroupMessageDataType
{
    UA_DECLARE_PRIVATE(UaJsonWriterGroupMessageDataType)
public:
    UaJsonWriterGroupMessageDataType();
    UaJsonWriterGroupMessageDataType(const UaJsonWriterGroupMessageDataType &other);
    UaJsonWriterGroupMessageDataType(const OpcUa_JsonWriterGroupMessageDataType &other);
    UaJsonWriterGroupMessageDataType(
        OpcUa_JsonNetworkMessageContentMask networkMessageContentMask
        );
    UaJsonWriterGroupMessageDataType(const UaExtensionObject &extensionObject);
    UaJsonWriterGroupMessageDataType(const OpcUa_ExtensionObject &extensionObject);
    UaJsonWriterGroupMessageDataType(UaExtensionObject &extensionObject, OpcUa_Boolean bDetach);
    UaJsonWriterGroupMessageDataType(OpcUa_ExtensionObject &extensionObject, OpcUa_Boolean bDetach);
    ~UaJsonWriterGroupMessageDataType();

    void clear();

    bool operator==(const UaJsonWriterGroupMessageDataType &other) const;
    bool operator!=(const UaJsonWriterGroupMessageDataType &other) const;

    UaJsonWriterGroupMessageDataType& operator=(const UaJsonWriterGroupMessageDataType &other);

    OpcUa_JsonWriterGroupMessageDataType* copy() const;
    void copyTo(OpcUa_JsonWriterGroupMessageDataType *pDst) const;

    static OpcUa_JsonWriterGroupMessageDataType* clone(const OpcUa_JsonWriterGroupMessageDataType& source);
    static void cloneTo(const OpcUa_JsonWriterGroupMessageDataType& source, OpcUa_JsonWriterGroupMessageDataType& copy);

    void attach(OpcUa_JsonWriterGroupMessageDataType *pValue);
    OpcUa_JsonWriterGroupMessageDataType* detach(OpcUa_JsonWriterGroupMessageDataType* pDst);

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

    OpcUa_StatusCode setJsonWriterGroupMessageDataType(const UaExtensionObject &extensionObject);
    OpcUa_StatusCode setJsonWriterGroupMessageDataType(const OpcUa_ExtensionObject &extensionObject);
    OpcUa_StatusCode setJsonWriterGroupMessageDataType(UaExtensionObject &extensionObject, OpcUa_Boolean bDetach);
    OpcUa_StatusCode setJsonWriterGroupMessageDataType(OpcUa_ExtensionObject &extensionObject, OpcUa_Boolean bDetach);

    void setJsonWriterGroupMessageDataType(
        OpcUa_JsonNetworkMessageContentMask networkMessageContentMask
        );

    OpcUa_JsonNetworkMessageContentMask getNetworkMessageContentMask() const;

    void setNetworkMessageContentMask(OpcUa_JsonNetworkMessageContentMask networkMessageContentMask);
};

/** @ingroup CppBaseLibraryClass
 *  @brief Array class for the UA stack structure OpcUa_JsonWriterGroupMessageDataType.
 *
 *  This class encapsulates an array of the native OpcUa_JsonWriterGroupMessageDataType structure
 *  and handles memory allocation and cleanup for you.
 *  @see UaJsonWriterGroupMessageDataType for information about the encapsulated structure.
 */
class UABASE_EXPORT UaJsonWriterGroupMessageDataTypes
{
public:
    UaJsonWriterGroupMessageDataTypes();
    UaJsonWriterGroupMessageDataTypes(const UaJsonWriterGroupMessageDataTypes &other);
    UaJsonWriterGroupMessageDataTypes(OpcUa_Int32 length, OpcUa_JsonWriterGroupMessageDataType* data);
    virtual ~UaJsonWriterGroupMessageDataTypes();

    UaJsonWriterGroupMessageDataTypes& operator=(const UaJsonWriterGroupMessageDataTypes &other);
    const OpcUa_JsonWriterGroupMessageDataType& operator[](OpcUa_UInt32 index) const;
    OpcUa_JsonWriterGroupMessageDataType& operator[](OpcUa_UInt32 index);

    bool operator==(const UaJsonWriterGroupMessageDataTypes &other) const;
    bool operator!=(const UaJsonWriterGroupMessageDataTypes &other) const;

    void attach(OpcUa_UInt32 length, OpcUa_JsonWriterGroupMessageDataType* data);
    void attach(OpcUa_Int32 length, OpcUa_JsonWriterGroupMessageDataType* data);
    OpcUa_JsonWriterGroupMessageDataType* detach();

    void create(OpcUa_UInt32 length);
    void resize(OpcUa_UInt32 length);
    void clear();

    inline OpcUa_UInt32 length() const {return m_noOfElements;}
    inline const OpcUa_JsonWriterGroupMessageDataType* rawData() const {return m_data;}
    inline OpcUa_JsonWriterGroupMessageDataType* rawData() {return m_data;}

    void toVariant(UaVariant &variant) const;
    void toVariant(OpcUa_Variant &variant) const;
    void toVariant(UaVariant &variant, OpcUa_Boolean bDetach);
    void toVariant(OpcUa_Variant &variant, OpcUa_Boolean bDetach);

    void toDataValue(UaDataValue &dataValue, OpcUa_Boolean updateTimeStamps) const;
    void toDataValue(OpcUa_DataValue &dataValue, OpcUa_Boolean updateTimeStamps) const;
    void toDataValue(UaDataValue &dataValue, OpcUa_Boolean bDetach, OpcUa_Boolean updateTimeStamps);
    void toDataValue(OpcUa_DataValue &dataValue, OpcUa_Boolean bDetach, OpcUa_Boolean updateTimeStamps);

    OpcUa_StatusCode setJsonWriterGroupMessageDataTypes(const UaVariant &variant);
    OpcUa_StatusCode setJsonWriterGroupMessageDataTypes(const OpcUa_Variant &variant);
    OpcUa_StatusCode setJsonWriterGroupMessageDataTypes(UaVariant &variant, OpcUa_Boolean bDetach);
    OpcUa_StatusCode setJsonWriterGroupMessageDataTypes(OpcUa_Variant &variant, OpcUa_Boolean bDetach);
    OpcUa_StatusCode setJsonWriterGroupMessageDataTypes(OpcUa_Int32 length, OpcUa_JsonWriterGroupMessageDataType* data);

private:
    OpcUa_UInt32 m_noOfElements;
    OpcUa_JsonWriterGroupMessageDataType* m_data;
};

#endif // UAJSONWRITERGROUPMESSAGEDATATYPE_H

