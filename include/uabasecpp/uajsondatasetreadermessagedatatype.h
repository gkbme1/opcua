/******************************************************************************
** uajsondatasetreadermessagedatatype.h
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
** Portable UaJsonDataSetReaderMessageDataType class.
**
******************************************************************************/
#ifndef UAJSONDATASETREADERMESSAGEDATATYPE_H
#define UAJSONDATASETREADERMESSAGEDATATYPE_H

#include <opcua_proxystub.h>

#include "uabase.h"
#include "uaarraytemplates.h"

class UaExtensionObject;
class UaVariant;
class UaDataValue;

class UABASE_EXPORT UaJsonDataSetReaderMessageDataTypePrivate;

/** @ingroup CppBaseLibraryClass
 *  @brief Wrapper class for the UA stack structure OpcUa_JsonDataSetReaderMessageDataType.
 *
 *  This class encapsulates the native OpcUa_JsonDataSetReaderMessageDataType structure
 *  and handles memory allocation and cleanup for you.
 *  UaJsonDataSetReaderMessageDataType uses implicit sharing to avoid needless copying and to boost the performance.
 *  Only if you modify a shared JsonDataSetReaderMessageDataType it creates a copy for that (copy-on-write).
 *  So assigning another UaJsonDataSetReaderMessageDataType or passing it as parameter needs constant time and is nearly as fast as assigning a pointer.
 */
class UABASE_EXPORT UaJsonDataSetReaderMessageDataType
{
    UA_DECLARE_PRIVATE(UaJsonDataSetReaderMessageDataType)
public:
    UaJsonDataSetReaderMessageDataType();
    UaJsonDataSetReaderMessageDataType(const UaJsonDataSetReaderMessageDataType &other);
    UaJsonDataSetReaderMessageDataType(const OpcUa_JsonDataSetReaderMessageDataType &other);
    UaJsonDataSetReaderMessageDataType(
        OpcUa_JsonNetworkMessageContentMask networkMessageContentMask,
        OpcUa_JsonDataSetMessageContentMask dataSetMessageContentMask
        );
    UaJsonDataSetReaderMessageDataType(const UaExtensionObject &extensionObject);
    UaJsonDataSetReaderMessageDataType(const OpcUa_ExtensionObject &extensionObject);
    UaJsonDataSetReaderMessageDataType(UaExtensionObject &extensionObject, OpcUa_Boolean bDetach);
    UaJsonDataSetReaderMessageDataType(OpcUa_ExtensionObject &extensionObject, OpcUa_Boolean bDetach);
    ~UaJsonDataSetReaderMessageDataType();

    void clear();

    bool operator==(const UaJsonDataSetReaderMessageDataType &other) const;
    bool operator!=(const UaJsonDataSetReaderMessageDataType &other) const;

    UaJsonDataSetReaderMessageDataType& operator=(const UaJsonDataSetReaderMessageDataType &other);

    OpcUa_JsonDataSetReaderMessageDataType* copy() const;
    void copyTo(OpcUa_JsonDataSetReaderMessageDataType *pDst) const;

    static OpcUa_JsonDataSetReaderMessageDataType* clone(const OpcUa_JsonDataSetReaderMessageDataType& source);
    static void cloneTo(const OpcUa_JsonDataSetReaderMessageDataType& source, OpcUa_JsonDataSetReaderMessageDataType& copy);

    void attach(OpcUa_JsonDataSetReaderMessageDataType *pValue);
    OpcUa_JsonDataSetReaderMessageDataType* detach(OpcUa_JsonDataSetReaderMessageDataType* pDst);

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

    OpcUa_StatusCode setJsonDataSetReaderMessageDataType(const UaExtensionObject &extensionObject);
    OpcUa_StatusCode setJsonDataSetReaderMessageDataType(const OpcUa_ExtensionObject &extensionObject);
    OpcUa_StatusCode setJsonDataSetReaderMessageDataType(UaExtensionObject &extensionObject, OpcUa_Boolean bDetach);
    OpcUa_StatusCode setJsonDataSetReaderMessageDataType(OpcUa_ExtensionObject &extensionObject, OpcUa_Boolean bDetach);

    void setJsonDataSetReaderMessageDataType(
        OpcUa_JsonNetworkMessageContentMask networkMessageContentMask,
        OpcUa_JsonDataSetMessageContentMask dataSetMessageContentMask
        );

    OpcUa_JsonNetworkMessageContentMask getNetworkMessageContentMask() const;
    OpcUa_JsonDataSetMessageContentMask getDataSetMessageContentMask() const;

    void setNetworkMessageContentMask(OpcUa_JsonNetworkMessageContentMask networkMessageContentMask);
    void setDataSetMessageContentMask(OpcUa_JsonDataSetMessageContentMask dataSetMessageContentMask);
};

/** @ingroup CppBaseLibraryClass
 *  @brief Array class for the UA stack structure OpcUa_JsonDataSetReaderMessageDataType.
 *
 *  This class encapsulates an array of the native OpcUa_JsonDataSetReaderMessageDataType structure
 *  and handles memory allocation and cleanup for you.
 *  @see UaJsonDataSetReaderMessageDataType for information about the encapsulated structure.
 */
class UABASE_EXPORT UaJsonDataSetReaderMessageDataTypes
{
public:
    UaJsonDataSetReaderMessageDataTypes();
    UaJsonDataSetReaderMessageDataTypes(const UaJsonDataSetReaderMessageDataTypes &other);
    UaJsonDataSetReaderMessageDataTypes(OpcUa_Int32 length, OpcUa_JsonDataSetReaderMessageDataType* data);
    virtual ~UaJsonDataSetReaderMessageDataTypes();

    UaJsonDataSetReaderMessageDataTypes& operator=(const UaJsonDataSetReaderMessageDataTypes &other);
    const OpcUa_JsonDataSetReaderMessageDataType& operator[](OpcUa_UInt32 index) const;
    OpcUa_JsonDataSetReaderMessageDataType& operator[](OpcUa_UInt32 index);

    bool operator==(const UaJsonDataSetReaderMessageDataTypes &other) const;
    bool operator!=(const UaJsonDataSetReaderMessageDataTypes &other) const;

    void attach(OpcUa_UInt32 length, OpcUa_JsonDataSetReaderMessageDataType* data);
    void attach(OpcUa_Int32 length, OpcUa_JsonDataSetReaderMessageDataType* data);
    OpcUa_JsonDataSetReaderMessageDataType* detach();

    void create(OpcUa_UInt32 length);
    void resize(OpcUa_UInt32 length);
    void clear();

    inline OpcUa_UInt32 length() const {return m_noOfElements;}
    inline const OpcUa_JsonDataSetReaderMessageDataType* rawData() const {return m_data;}
    inline OpcUa_JsonDataSetReaderMessageDataType* rawData() {return m_data;}

    void toVariant(UaVariant &variant) const;
    void toVariant(OpcUa_Variant &variant) const;
    void toVariant(UaVariant &variant, OpcUa_Boolean bDetach);
    void toVariant(OpcUa_Variant &variant, OpcUa_Boolean bDetach);

    void toDataValue(UaDataValue &dataValue, OpcUa_Boolean updateTimeStamps) const;
    void toDataValue(OpcUa_DataValue &dataValue, OpcUa_Boolean updateTimeStamps) const;
    void toDataValue(UaDataValue &dataValue, OpcUa_Boolean bDetach, OpcUa_Boolean updateTimeStamps);
    void toDataValue(OpcUa_DataValue &dataValue, OpcUa_Boolean bDetach, OpcUa_Boolean updateTimeStamps);

    OpcUa_StatusCode setJsonDataSetReaderMessageDataTypes(const UaVariant &variant);
    OpcUa_StatusCode setJsonDataSetReaderMessageDataTypes(const OpcUa_Variant &variant);
    OpcUa_StatusCode setJsonDataSetReaderMessageDataTypes(UaVariant &variant, OpcUa_Boolean bDetach);
    OpcUa_StatusCode setJsonDataSetReaderMessageDataTypes(OpcUa_Variant &variant, OpcUa_Boolean bDetach);
    OpcUa_StatusCode setJsonDataSetReaderMessageDataTypes(OpcUa_Int32 length, OpcUa_JsonDataSetReaderMessageDataType* data);

private:
    OpcUa_UInt32 m_noOfElements;
    OpcUa_JsonDataSetReaderMessageDataType* m_data;
};

#endif // UAJSONDATASETREADERMESSAGEDATATYPE_H

